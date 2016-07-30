#include <boost/filesystem.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

#include "FSController.h"
#include "FSExceptions.h"

namespace NFileSystem
{
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
      void SaveFSInfo(const Controller& owner) const;

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

         uint64_t totalCount = 0u;

         std::function<void(std::shared_ptr<Directory>)> serialize =
            [&owner, &fileData, &totalCount, &serialize](std::shared_ptr<Directory> dir) -> void
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

               dir->AddEntity(name, entity);
               entity->Parent(dir);

               auto handle = static_cast<EntityHandle>(totalCount);
               owner.m_contents[handle] = entity;

               ++totalCount;
            }
         };

         serialize(owner.m_root);
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

   void Controller::FSInfoStorage::SaveFSInfo(const Controller& owner) const
   {
      boost::iostreams::mapped_file_sink file;
      auto infoBlockMaxSize =
         sizeof(InfoBlockSize) + sizeof(DataBlockSize) + sizeof(DataBlockPos) +          
         owner.m_contents.size() *
            (sizeof(uint64_t) + 256u + sizeof(uint64_t) + sizeof(uint64_t));
      
      auto totalMaxSize = infoBlockMaxSize + owner.m_root->Size();
      try
      {
         auto fileSize = boost::filesystem::file_size(PhysicalFileName());
         if (fileSize < infoBlockMaxSize)
            EnlargeFile(fileSize, totalMaxSize, DataBlockPos);

         file.open(PhysicalFileName(), infoBlockMaxSize);

         auto fileData = file.data();

         std::function<void(std::shared_ptr<Directory>)> deserialize =
            [&fileData, &deserialize](std::shared_ptr<Directory> dir) -> void
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
                  *reinterpret_cast<uint64_t*>(fileData) = entity.Offset();
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

         deserialize(owner.m_root);

         uint64_t totalCount = fileData - file.data();
         fileData = file.data();
         *reinterpret_cast<decltype(totalCount)*>(fileData) = totalCount;
         fileData += sizeof(totalCount);
         *reinterpret_cast<decltype(DataBlockSize)*>(fileData) = DataBlockSize;
         fileData += sizeof(DataBlockSize);
         *reinterpret_cast<decltype(DataBlockPos)*>(fileData) = DataBlockPos;

         file.close();
         ResizeFile(totalCount);
      }
      catch (...)
      {
         throw Exception(ErrorCode::InternalError);
      }
   }

   constexpr Controller::EntityHandle rootHandle = 0u;

   Controller::Controller()
      : m_infoStrage(std::make_unique<FSInfoStorage>())
      , m_root(std::make_shared<Directory>())
      , m_contents({ std::make_pair(rootHandle, std::weak_ptr<Entity>(m_root)) })
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
         m_infoStrage->SaveFSInfo(*this);
      }
      catch(...)
      {
         //my imaginary logger puts a message in log here
      }
   }

   namespace
   {
      using TIter = boost::filesystem::path::const_iterator;
      OptionalShared<const Entity> Find(TIter iter, TIter end, const Directory& location)
      {
         auto optEntity = location.FindEntity(iter->wstring());

         if (++iter != end)
         {
            if (optEntity && EntityCategory::Directory == optEntity->get()->Category)
               return Find(iter, end, static_cast<const Directory&>(*optEntity->get()));

            return boost::none;
         }
         
         return optEntity;
      }

      OptionalShared<const Entity> RecursiveFind(const boost::filesystem::path& path, const Directory& dir)
      {
         return path.empty() ? boost::none : Find(path.begin(), path.end(), dir);
      }

      OptionalShared<Entity> RecursiveFind(const boost::filesystem::path& path, Directory& dir)
      {
         auto constResult = RecursiveFind(path, const_cast<const Directory&>(dir));
         if (constResult)
            return boost::make_optional(std::const_pointer_cast<Entity>(constResult.get()));

         return boost::none;
      }
   }

   void Controller::CleanUp(Controller::EntityHandle from)
   {
      auto it = m_contents.find(from);

      for (;it != m_contents.end();)
      {
         if (it->second.expired())
            it = m_contents.erase(it);
         else
            ++it;
      }
   }

   OptionalShared<Entity> Controller::ExistingEntity(Controller::EntityHandle handle) const
   {
      auto it = m_contents.find(handle);
      if (m_contents.end() == it)
         return boost::none;

      auto entity = it->second.lock();
      if (!entity)
         return boost::none;

      return boost::make_optional(entity);
   }

   OptionalShared<Directory> Controller::ExistingDir(Controller::EntityHandle handle) const
   {
      auto entity = ExistingEntity(handle);
      if (!entity || EntityCategory::Directory != entity.value()->Category)
         return boost::none;

      return boost::make_optional(std::static_pointer_cast<Directory>(entity.value()));
   }

   Controller::EntityHandle Controller::Root() const
   {
      return rootHandle;
   }

   Controller::EntityHandle Controller::Create(EntityHandle location, const std::wstring& name, EntityCategory category)
   {
      auto optDir = ExistingDir(location);
      if (!optDir)
         throw Exception(ErrorCode::DoesNotExists);

      std::shared_ptr<Entity> created;
      if (EntityCategory::File == category)
         created = std::make_shared<File>(m_root->Size());
      else if (EntityCategory::Directory == category)
         created = std::make_shared<Directory>();
      else
         assert(false);

      optDir.value()->AddEntity(name, created);
      created->Parent(optDir.value());

      auto handle = static_cast<EntityHandle>(m_contents.size());
      m_contents[handle] = created;
      return handle;
   }

   void Controller::Delete(Controller::EntityHandle handle)
   {
      if (rootHandle == handle)
         return;

      auto optEntity = ExistingEntity(handle);
      if (!optEntity)
         throw Exception(ErrorCode::DoesNotExists);

      auto parent = optEntity.value()->Parent().lock();
      assert(parent);
      parent->FindEntity(*optEntity.value()).value();

      CleanUp();
   }

   bool Controller::Exists(EntityHandle location, const std::wstring& name) const
   {
      auto optDir = ExistingDir(location);
      if (!optDir)
         return false;

      return optDir.value()->FindEntity(name).is_initialized();
   }

   std::list<std::wstring> Controller::List(Controller::EntityHandle handle) const
   {
      auto optDir = ExistingDir(handle);
      if (!optDir)
         throw Exception(ErrorCode::DoesNotExists);

      return optDir.value()->List();
   }

   std::wstring Controller::Name(EntityHandle handle) const
   {
      if (rootHandle == handle)
         return std::wstring();

      auto optEntity = ExistingEntity(handle);
      if (!optEntity)
         throw Exception(ErrorCode::DoesNotExists);

      auto parent = optEntity.value()->Parent().lock();
      assert(parent);
      return parent->FindEntity(*optEntity.value()).value();
   }

   uint64_t Controller::Size(Controller::EntityHandle handle) const
   {
      auto optEntity = ExistingEntity(handle);
      if (!optEntity)
         throw Exception(ErrorCode::DoesNotExists);

      return optEntity.value()->Size();
   }

   ManagedArray Controller::Read(Controller::EntityHandle handle, uint64_t count) const
   {
      return ManagedArray(std::make_pair(nullptr, 0u));
   }

   void Controller::Write(Controller::EntityHandle handle, const uint8_t* buffer, uint64_t count)
   {}
} // namespace NFileSystem