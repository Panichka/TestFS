#include <atomic>

#include <boost/filesystem.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>

#include "FSController.h"
#include "FSExceptions.h"

namespace NFileSystem
{
   struct Controller::FSInfo
   {
      FSInfo() 
         : Root(std::make_shared<Directory>())
         , Contents({ std::weak_ptr<Entity>(Root) })
         , Count(0u)
      {}

      void EmplaceBack(Entities::value_type&&);

      EntityHandle Handle(EntityHandle location, std::shared_ptr<Entity> value) const;

      std::shared_ptr<Directory> Root;
      Entities Contents;
      EntityHandle Last = Contents.begin();
      std::atomic<size_t> Count;
   };

   void Controller::FSInfo::EmplaceBack(Entities::value_type&& value)
   {
      Contents.emplace_after(Last, std::move(value));
      Last++;
      Count++;
   }

   EntityHandle Controller::FSInfo::Handle(EntityHandle location, std::shared_ptr<Entity> value) const
   {
      auto entity = std::find_if(location, Contents.end(),
         [&value](const EntityHandle::value_type& it)
      {
         return !it.expired() && it.lock().get() == value.get();
      });

      assert(Contents.end() != entity);
      return entity;
   }

   struct Controller::FSInfoStorage
   {
      static const Path& PhysicalFileName()
      {
         static boost::system::error_code eCode;
         static const Path path(boost::filesystem::current_path(eCode) /= "fs.rawdata");

         if (boost::system::errc::success != eCode)
            throw Exception(ErrorCode::InternalError);

         return path;
      }

      void LoadFSInfo(Controller& owner);
      void SaveFSInfo(const Controller& owner);

      uint64_t InfoBlockSize = 0u;
      uint64_t DataBlockSize = 0u;
      uint64_t DataBlockPos = 0u;
   };

   template <class UIntType>
   UIntType AlignedOffset(UIntType offset)
   {
      return offset - offset % boost::iostreams::mapped_file::alignment();
   }

   template <class UIntType>
   UIntType RelativeOffset(UIntType offset)
   {
      return offset % boost::iostreams::mapped_file::alignment();
   }

   void Controller::FSInfoStorage::LoadFSInfo(Controller& owner)
   {
      constexpr auto foremostBlockSize =
         sizeof(InfoBlockSize) + sizeof(DataBlockSize) + sizeof(DataBlockPos);

      boost::iostreams::mapped_file_source file;
      try
      {
         file.open(PhysicalFileName(), foremostBlockSize);

         auto fileData = file.data();
         InfoBlockSize = *reinterpret_cast<const decltype(InfoBlockSize)*>(fileData);
         fileData += sizeof(InfoBlockSize);
         DataBlockSize = *reinterpret_cast<const decltype(DataBlockSize)*>(fileData);
         fileData += sizeof(DataBlockSize);
         DataBlockPos = *reinterpret_cast<const decltype(DataBlockPos)*>(fileData);

         if (0u == InfoBlockSize)
            return;

         file.close();

         file.open(PhysicalFileName(), InfoBlockSize);
         fileData += foremostBlockSize;

         std::function<void(std::shared_ptr<Directory>)> serialize =
            [&owner, &fileData, &serialize](std::shared_ptr<Directory> dir) -> void
         {
            auto countInDir = *reinterpret_cast<const uint64_t*>(fileData);
            fileData += sizeof(uint64_t);

            for (auto index = 0u; index < countInDir; index++)
            {
               auto category = *reinterpret_cast<const EntityCategory*>(fileData);
               fileData += sizeof(category);

               std::wstring name(reinterpret_cast<const std::wstring::value_type*>(fileData));
               fileData += name.size() * sizeof(std::wstring::value_type);

               std::shared_ptr<Entity> entity;
               if (EntityCategory::File == category)
               {
                  auto size = *reinterpret_cast<const uint64_t*>(fileData);
                  fileData += sizeof(uint64_t);
                  auto offset = *reinterpret_cast<const uint64_t*>(fileData);
                  fileData += sizeof(uint64_t);
                  entity = std::make_shared<File>(offset, size);
               }
               else if (EntityCategory::Directory == category)
               {
                  auto tmp = std::make_shared<Directory>();
                  serialize(tmp);
                  entity = std::move(tmp);
               }
               else
               {
                  assert(false);
               }

               Directory::AddEntity(dir, name, entity);

               if (!entity->Parent().lock())
                  continue;

               owner.m_info->EmplaceBack(entity);
            }
         };

         serialize(owner.m_info->Root);
      }
      catch(...)
      {
         //if (file.is_open())
            //file.close();

         throw Exception(ErrorCode::InternalError);
      }      
   }

   namespace
   {
      void ResizeFile(uint64_t newSize)
      {
         boost::filesystem::resize_file(Controller::FSInfoStorage::PhysicalFileName(), newSize);
      }

      void ReplaceData(uint64_t replaceFrom, uint64_t replaceTo, uint64_t dataSize)
      {
         auto fileSize = boost::filesystem::file_size(Controller::FSInfoStorage::PhysicalFileName());
         if(fileSize < replaceTo + dataSize)
            ResizeFile(replaceTo + dataSize);

         auto fromOffset = AlignedOffset(replaceFrom);
         auto toOffset = AlignedOffset(replaceTo);
         
         auto Replace = [&fromOffset, &toOffset](uint64_t portion = 0)
         {
            boost::iostreams::mapped_file_source from(
               Controller::FSInfoStorage::PhysicalFileName(),
               portion,
               fromOffset);

            boost::iostreams::mapped_file_sink to(
               Controller::FSInfoStorage::PhysicalFileName(),
               portion,
               toOffset);

            memcpy_s(to.data(), to.size(), from.data(), from.size());
         };

         auto enougth = AlignedOffset(replaceTo + dataSize);
         auto portionSize = boost::iostreams::mapped_file::alignment();

         while (fromOffset < enougth)
         {
            Replace(portionSize);
            fromOffset += portionSize;
            toOffset += portionSize;
         }

         Replace();
      }

      void EnlargeFile(uint64_t oldSize, uint64_t newSize, uint64_t copyFromPos)
      {
         assert(copyFromPos < oldSize && oldSize < newSize);

         if (oldSize == newSize)
            return;

         ResizeFile(newSize);

         auto portionSize = boost::iostreams::mapped_file::alignment();

         boost::iostreams::mapped_file_source from;
         boost::iostreams::mapped_file_sink to;

         auto fromOffset = AlignedOffset(oldSize - 1u);
         auto toOffset = AlignedOffset(newSize - 1u);
         auto enougth = AlignedOffset(copyFromPos);

         while (fromOffset > enougth)
         {
            from.open(
               Controller::FSInfoStorage::PhysicalFileName(),
               portionSize,
               fromOffset);

            to.open(
               Controller::FSInfoStorage::PhysicalFileName(),
               portionSize,
               toOffset);

            memcpy_s(to.data(), to.size(), from.data(), from.size());

            to.close();
            from.close();

            fromOffset -= portionSize;
            toOffset -= portionSize;
         }
      }
   }

   void Controller::FSInfoStorage::SaveFSInfo(const Controller& owner)
   {
      boost::iostreams::mapped_file_sink file;
      auto infoBlockMaxSize =
         sizeof(InfoBlockSize) + sizeof(DataBlockSize) + sizeof(DataBlockPos) +          
         owner.Count() *
            (sizeof(uint64_t) + 256u + sizeof(uint64_t) + sizeof(uint64_t));
      
      auto totalMaxSize = infoBlockMaxSize + owner.m_info->Root->Size();
      try
      {
         auto fileSize = boost::filesystem::file_size(PhysicalFileName());
         if (InfoBlockSize < infoBlockMaxSize)
            EnlargeFile(fileSize, totalMaxSize, DataBlockPos);

         file.open(PhysicalFileName(), infoBlockMaxSize);

         auto fileData = file.data();
         auto shiftData = totalMaxSize - fileSize;

         std::function<void(std::shared_ptr<Directory>)> deserialize =
            [&fileData, &deserialize, shiftData](std::shared_ptr<Directory> dir) -> void
         {
            *reinterpret_cast<uint64_t*>(fileData) = dir->Count();
            fileData += sizeof(uint64_t);

            for (const auto& item : *dir)
            {
               *reinterpret_cast<EntityCategory*>(fileData) = item.second->Category;
               fileData += sizeof(item.second->Category);

               auto nameSize = item.first.size() * sizeof(std::wstring::value_type);
               memcpy(fileData, item.first.c_str(), nameSize);
               fileData += nameSize;

               if (EntityCategory::File == item.second->Category)
               {
                  auto& entity = *static_cast<const File*>(item.second.get());
                  *reinterpret_cast<uint64_t*>(fileData) = entity.Size();
                  fileData += sizeof(uint64_t);
                  *reinterpret_cast<uint64_t*>(fileData) = entity.Offset() + shiftData;
                  fileData += sizeof(uint64_t);
               }
               else if (EntityCategory::Directory == item.second->Category)
               {
                  deserialize(std::static_pointer_cast<Directory>(item.second));
               }
               else
               {
                  assert(false);
               }
            }
         };         

         deserialize(owner.m_info->Root);

         InfoBlockSize = fileData - file.data();

         fileData = file.data();
         *reinterpret_cast<decltype(InfoBlockSize)*>(fileData) = InfoBlockSize;
         fileData += sizeof(InfoBlockSize);
         *reinterpret_cast<decltype(DataBlockSize)*>(fileData) = DataBlockSize;
         fileData += sizeof(DataBlockSize);
         *reinterpret_cast<decltype(DataBlockPos)*>(fileData) = DataBlockPos;
      }
      catch (...)
      {
         throw Exception(ErrorCode::InternalError);
      }
   }

   Controller::Controller()
      : m_mutex(std::make_unique<boost::shared_mutex>())
      , m_info(std::make_unique<FSInfo>())
      , m_infoStrage(std::make_unique<FSInfoStorage>())
   {
      namespace fs = boost::filesystem;
      if (!fs::exists(FSInfoStorage::PhysicalFileName()))
      {
         fs::ofstream tmp(FSInfoStorage::PhysicalFileName(), std::ios_base::binary);
         if ((tmp.rdstate() & std::ofstream::failbit) != 0)
            throw Exception(ErrorCode::InternalError);
      }
      else
      {
         if (!fs::is_regular_file(FSInfoStorage::PhysicalFileName()))
            throw Exception(ErrorCode::InternalError);

         if (!fs::is_empty(FSInfoStorage::PhysicalFileName()))
            m_infoStrage->LoadFSInfo(*this);
      }
   }

   Controller::~Controller()
   {
      namespace fs = boost::filesystem;
      if (!fs::exists(FSInfoStorage::PhysicalFileName()))
      {
         fs::ifstream tmp(FSInfoStorage::PhysicalFileName(), std::ios_base::binary);
         if ((tmp.rdstate() & std::ifstream::failbit) != 0)
            return;
      }

      if (!fs::is_regular_file(FSInfoStorage::PhysicalFileName()))
            return;

      try
      {
         if (Count() > 1u) //something besides root
            m_infoStrage->SaveFSInfo(*this);
      }
      catch(...)
      {
         //my imaginary logger puts a message in log here
      }
   }

   size_t Controller::Count() const
   {
      return m_info->Count.load();
   }

   OptionalShared<Entity> Controller::ExistingEntity(EntityHandle handle) const
   {
      if (m_info->Contents.end() == handle)
         return boost::none;

      auto entity = handle->lock();
      if (!entity)
         return boost::none;

      return boost::make_optional(entity);
   }

   EntityHandle Controller::Root() const
   {
      return m_info->Contents.begin();
   }

   EntityHandle Controller::Create(EntityHandle location, const std::wstring& name, EntityCategory category)
   {
      boost::upgrade_lock<boost::shared_mutex> lock(*m_mutex);

      auto optDir = ExistingEntity<Directory>(location);
      if (!optDir)
         throw Exception(ErrorCode::DoesNotExists);

      boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

      std::shared_ptr<Entity> created;
      if (EntityCategory::File == category)
         created = std::make_shared<File>(m_info->Root->Size());
      else if (EntityCategory::Directory == category)
         created = std::make_shared<Directory>();
      else
         assert(false);

      Directory::AddEntity(optDir.value(), name, created);
      if (!created->Parent().lock())
         return m_info->Handle(location, created);

      m_info->EmplaceBack(created);
      return m_info->Last;
   }

   void Controller::Delete(EntityHandle handle)
   {
      if (Root() == handle)
         return;

      boost::upgrade_lock<boost::shared_mutex> lock(*m_mutex);

      auto optEntity = ExistingEntity(handle);
      if (!optEntity)
         throw Exception(ErrorCode::DoesNotExists);

      auto parent = optEntity.value()->Parent().lock();
      assert(parent);

      auto name = parent->FindEntity(*optEntity.value()).value();

      boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

      parent->RemoveEntity(name);
   }

   bool Controller::Exists(EntityHandle location, const std::wstring& name) const
   {
      boost::shared_lock<boost::shared_mutex> lock(*m_mutex);

      auto optDir = ExistingEntity<Directory>(location);
      if (!optDir)
         return false;

      return optDir.value()->FindEntity(name).is_initialized();
   }

   std::list<std::wstring> Controller::List(EntityHandle handle) const
   {
      boost::shared_lock<boost::shared_mutex> lock(*m_mutex);

      auto optDir = ExistingEntity<Directory>(handle);
      if (!optDir)
         throw Exception(ErrorCode::DoesNotExists);

      return optDir.value()->List();
   }

   std::wstring Controller::Name(EntityHandle handle) const
   {
      boost::shared_lock<boost::shared_mutex> lock(*m_mutex);

      if (Root() == handle)
         return std::wstring();

      auto optEntity = ExistingEntity(handle);
      if (!optEntity)
         throw Exception(ErrorCode::DoesNotExists);

      auto parent = optEntity.value()->Parent().lock();
      assert(parent);
      return parent->FindEntity(*optEntity.value()).value();
   }

   size_t Controller::Size(EntityHandle handle) const
   {
      boost::shared_lock<boost::shared_mutex> lock(*m_mutex);

      auto optEntity = ExistingEntity(handle);
      if (!optEntity)
         throw Exception(ErrorCode::DoesNotExists);

      return optEntity.value()->Size();
   }

   EntityHandle Controller::Handle(EntityHandle location, const std::wstring& name) const
   {
      boost::shared_lock<boost::shared_mutex> lock(*m_mutex);

      auto optDir = ExistingEntity<Directory>(location);
      if (!optDir)
         throw Exception(ErrorCode::DoesNotExists);

      auto optEntity = optDir->get()->FindEntity(name);
      if (!optEntity)
         throw Exception(ErrorCode::DoesNotExists);

      return m_info->Handle(location, optEntity.get());
   }

   EntityCategory Controller::Category(EntityHandle location, const std::wstring& name) const
   {
      boost::shared_lock<boost::shared_mutex> lock(*m_mutex);

      auto optDir = ExistingEntity<Directory>(location);
      if (!optDir)
         throw Exception(ErrorCode::DoesNotExists);

      auto optEntity = optDir->get()->FindEntity(name);
      if (!optEntity)
         throw Exception(ErrorCode::DoesNotExists);

      return optEntity->get()->Category;
   }

   EntityCategory Controller::Category(EntityHandle handle) const
   {
      boost::shared_lock<boost::shared_mutex> lock(*m_mutex);

      auto optEntity = ExistingEntity(handle);
      if (!optEntity)
         throw Exception(ErrorCode::DoesNotExists);

      return optEntity->get()->Category;
   }

   ManagedArray Controller::Read(EntityHandle handle, size_t count, size_t position) const
   {
      boost::shared_lock<boost::shared_mutex> lock(*m_mutex);

      auto optFile = ExistingEntity<File>(handle);
      if (!optFile)
         throw Exception(ErrorCode::DoesNotExists);

      if (optFile.value()->Size() <= position)
         throw Exception(ErrorCode::InvalidArgument);

      if (optFile.value()->Size() < count + position)
         count = optFile.value()->Size() - position;

      boost::iostreams::mapped_file_source src;
      auto alignedOffset = AlignedOffset(optFile.value()->Offset() + position);
      auto relativeOffset = RelativeOffset(optFile.value()->Offset() + position);

      auto array = ManagedArray::first_type(new ManagedArray::first_type::element_type[count]);

      try
      {
         src.open(
            FSInfoStorage::PhysicalFileName(),
            count + relativeOffset,
            alignedOffset);

         memcpy_s(array.get(), count, src.data() + relativeOffset, src.size());
      }
      catch (...)
      {
         throw Exception(ErrorCode::InternalError);
      }

      return ManagedArray(std::make_pair(std::move(array), count));
   }

   void Controller::Write(EntityHandle handle, const uint8_t* buffer, size_t count, size_t position)
   {
      boost::upgrade_lock<boost::shared_mutex> lock(*m_mutex);

      auto optFile = ExistingEntity<File>(handle);
      if (!optFile)
         throw Exception(ErrorCode::DoesNotExists);

      if (optFile.value()->Size() <= position)
         throw Exception(ErrorCode::InvalidArgument);

      boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

      if (optFile.value()->Size() < position + count)
      {
         auto fileSize = boost::filesystem::file_size(FSInfoStorage::PhysicalFileName());
         if (0u == position || (optFile.value()->Offset() + optFile.value()->Size() == fileSize))
            ResizeFile(fileSize + position + count - optFile.value()->Size());
         else
            ReplaceData(optFile.value()->Offset(), fileSize, position);

         optFile.value()->Offset(fileSize);
         optFile.value()->Size(position + count);
      }

      boost::iostreams::mapped_file_sink dst;
      auto alignedOffset = AlignedOffset(optFile.value()->Offset() + position);
      auto relativeOffset = RelativeOffset(optFile.value()->Offset() + position);

      try
      {
         dst.open(
            FSInfoStorage::PhysicalFileName(),
            count + relativeOffset,
            alignedOffset);

         memcpy_s(dst.data() + relativeOffset, dst.size(), buffer, count);
      }
      catch (...)
      {
         throw Exception(ErrorCode::InternalError);
      }
   }
} // namespace NFileSystem