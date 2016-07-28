#ifndef __vfs__FSController_h__
#define __vfs__FSController_h__

#include <list>
#include <memory>
#include <boost/filesystem/path.hpp>

#include "FSEntity.h"
#include <set>

namespace NFileSystem
{
   using Path = boost::filesystem::path;
   using ManagedArray = std::pair<std::unique_ptr<uint8_t[]>, uint64_t>;

   class Controller final
   {
   public:
      Controller();
      ~Controller();	

      using EntityHandle = uint32_t;
      
      EntityHandle Root() const;

      EntityHandle Create(EntityHandle location, const std::wstring& name, EntityCategory category);
      void Delete(EntityHandle handle);

      bool Exists(EntityHandle location, const std::wstring& name) const;
      std::list<std::wstring> List(EntityHandle handle) const;

      std::wstring Name(EntityHandle handle) const;
      uint64_t Size(EntityHandle handle) const;

      ManagedArray Read(EntityHandle handle, uint64_t count) const;
      void Write(EntityHandle handle, const uint8_t* buffer, uint64_t count);

   private:
      OptionalShared<Directory> ExistingDir(EntityHandle handle) const;
      OptionalShared<Entity> ExistingEntity(EntityHandle handle) const;
      void CleanUp();

      std::shared_ptr<Directory> m_root;
      std::unordered_map<EntityHandle, std::weak_ptr<Entity>> m_contents;
   };
} // namespace NFileSystem

#endif // __vfs__FSController_h__
