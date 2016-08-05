#ifndef __vfs__FSController_h__
#define __vfs__FSController_h__

#include <list>
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

   using Entities = std::list<std::weak_ptr<Entity>>;
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

      size_t Count() const { return m_contents.size(); }
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

      EntityHandle Handle(EntityHandle location, std::shared_ptr<Entity> value) const;

      std::unique_ptr<boost::shared_mutex> m_mutex;
      std::unique_ptr<FSInfoStorage> m_infoStrage;

      std::shared_ptr<Directory> m_root;
      std::list<std::weak_ptr<Entity>> m_contents;
   };
} // namespace NFileSystem

#endif // __vfs__FSController_h__
