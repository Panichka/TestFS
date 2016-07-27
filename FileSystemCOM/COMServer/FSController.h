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
      
      bool Exists(const Path& path);

      EntityHandle Create(const Path& path, Entity::Category category);
      void Delete(EntityHandle handle);

      std::list<std::wstring> List(EntityHandle handle);

      uint64_t Size(EntityHandle handle);

      ManagedArray Read(EntityHandle handle, uint64_t count);
      void Write(EntityHandle handle, const uint8_t* buffer, uint64_t count);

   private:
      std::unordered_map<EntityHandle, std::weak_ptr<Entity>> m_contents;
   };
} // namespace NFileSystem

#endif // __vfs__FSController_h__
