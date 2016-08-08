#ifndef __vfs__FSController_h__
#define __vfs__FSController_h__
//
//! @brief Single-file virtual file system controller
//! @details Physical file consists of f.s. info block and data block
//! Data block contains siquential data of all saved files.
//! Directories don't hold any data in data block. A position and a size
//! of file are specified in info block as described bellow
//! @verbatim
//!    +-------------------+-----------------+-------------------+-----------------+
//!    | uint64_t          | uint64_t        | uint64_t          | ...             |
//!    +-------------------+-----------------+-------------------+-----------------+
//!    | data block offset | data block size | count of entities | entities info   |
//!    |                   |                 | in root (not rec.)|                 |
//!    +-------------------+-----------------+-------------------+-----------------+
//! @endverbatim
//! 
//! Entities info may contain siquence either of files info:
//! @verbatim
//!    +----------------------+-----------------+---------------------+
//!    | EntityCategory       | uint64_t        | uint64_t            |
//!    +----------------------+-----------------+---------------------+
//!    | EntityCategory::File | size of file    | file absolute offset|
//!    +----------------------+-----------------+---------------------+
//! @endverbatim
//! or directories info:
//! @verbatim
//!    +---------------------------+-------------------+-------------+
//!    | EntityCategory            | uint64_t          | ...         |
//!    +---------------------------+-------------------+-------------+
//!    | EntityCategory::Directory | count of entities | same as for |
//!    |                           | in dir (not rec.) | root        |
//!    +---------------------------+-------------------+-------------+
//! @endverbatim

#include <forward_list>
#include <memory>
#include <boost/filesystem/path.hpp>

#include "FSEntity.h"

namespace boost
{
   class shared_mutex;
}

namespace NFileSystem
{
   using Path = boost::filesystem::path;
   using ManagedArray = std::pair<std::unique_ptr<uint8_t[]>, size_t>;

   using Entities = std::forward_list<std::weak_ptr<Entity>>;
   using EntityHandle = Entities::const_iterator;

   class Controller final
   {
   public:

      Controller();
      ~Controller();	
      
      EntityHandle Root() const;

      EntityHandle Create(EntityHandle location, const std::wstring& name, EntityCategory category);
      void Delete(EntityHandle handle);

      bool Exists(EntityHandle location, const std::wstring& name) const;
      std::list<std::wstring> List(EntityHandle handle) const;

      EntityHandle Handle(EntityHandle location, const std::wstring& name) const;
      std::wstring Name(EntityHandle handle) const;
      EntityCategory Category(EntityHandle handle) const;
      EntityCategory Category(EntityHandle location, const std::wstring& name) const;
      size_t Size(EntityHandle handle) const;

      ManagedArray Read(EntityHandle handle, size_t count, size_t position = 0) const;
      void Write(EntityHandle handle, const uint8_t* buffer, size_t count, size_t position = 0);

      size_t Count() const;

      struct FSInfo;
      struct FSInfoStorage;

   private:
      OptionalShared<Entity> ExistingEntity(EntityHandle handle) const;

      template <typename  T>
      OptionalShared<T> ExistingEntity(EntityHandle handle) const
      {
         auto entity = ExistingEntity(handle);
         if (!entity || typename T::Category() != entity.value()->Category)
            return boost::none;

         return boost::make_optional(std::static_pointer_cast<T>(entity.value()));
      }

      std::unique_ptr<boost::shared_mutex> m_mutex;
      std::unique_ptr<FSInfo> m_info;
      std::unique_ptr<FSInfoStorage> m_infoStrage;
   };
} // namespace NFileSystem

#endif // __vfs__FSController_h__
