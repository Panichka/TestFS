#include <boost/filesystem.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

#include "FSController.h"
#include "FSExceptions.h"

namespace NFileSystem
{
   namespace
   {
      const Path& PhysicalFileName()
      {
         static boost::system::error_code eCode;
         static const Path path(boost::filesystem::current_path(eCode) /= "fsdata");

         if (boost::system::errc::success != eCode)
            throw Exception(ErrorCode::InternalError);

         return path;
      }
   }

   constexpr Controller::EntityHandle rootHandle = 0u;

   Controller::Controller()
      : m_root(std::make_shared<Directory>())
      , m_contents({ std::make_pair(rootHandle, std::weak_ptr<Entity>(m_root)) })
   {
      if (boost::filesystem::exists(PhysicalFileName()))
         ;
   }

   Controller::~Controller()
   {

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
      else
         created = std::make_shared<Directory>();

      optDir.value()->AddEntity(name, created);

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