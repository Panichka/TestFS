#ifndef __vfs__FSController_h__
#define __vfs__FSController_h__

#include <list>
#include <memory>
#include <boost/filesystem/path.hpp>

#include "FSEntity.h"

namespace NFileSystem
{
   using Path = boost::filesystem::path;
   using ManagedArray = std::pair<std::unique_ptr<uint8_t[]>, uint64_t>;

   struct Controller final
   {
      Controller();
      ~Controller();	

      void Create(const Path& path, Entity::Category category);
      void Delete(const Path& path);

      bool Exists(const Path& path);

      std::list<std::wstring> List(const Path& path);

      uint64_t Size(const Path& path);

      ManagedArray Read(const Path& path, uint64_t count);
      void Write(const Path& path, const uint8_t* buffer, uint64_t count);
   };
} // namespace NFileSystem

#endif // __vfs__FSController_h__
