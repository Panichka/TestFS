#ifndef __vfs__FSEntity_h__
#define __vfs__FSEntity_h__

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <boost/optional.hpp>

namespace NFileSystem
{
   enum class EntityCategory : uint8_t { File, Directory };
   struct Directory;

   struct Entity
   {
      virtual uint64_t Size() const = 0;
      virtual ~Entity() = default;

      const EntityCategory Category;

      void Parent(std::weak_ptr<Directory>);
      std::weak_ptr<Directory> Parent();
      std::weak_ptr<const Directory> Parent() const;

      explicit Entity(EntityCategory cat, std::shared_ptr<Directory> parent)
         : Category(cat)
         , m_parent(parent)
      {}

      Entity() = delete;
      Entity(const Entity&) = delete;
      void operator=(const Entity&) = delete;

   private:
      std::weak_ptr<Directory> m_parent;
   };

   struct File : Entity
   {
      explicit File(uint64_t offset = 0ull, uint64_t size = 0ull, std::shared_ptr<Directory> parent = nullptr);
      File(const File& src); 
      File& operator=(const File& src);

      uint64_t Size() const override { return m_size; }
      void Size(uint64_t size) { m_size = size; }

      uint64_t Offset() const { return m_offset; }
      void Offset(uint64_t offset) { m_offset = offset; }

   private:
      uint64_t m_size = 0u;
      uint64_t m_offset = 0ull;
   };

   template <class T>
   using OptionalShared = boost::optional<std::shared_ptr<T>>;

   struct Directory : Entity
   {
      Directory(std::shared_ptr<Directory> parent = nullptr);

      Directory(const Directory& src);
      Directory(Directory&& src);

      Directory& operator=(const Directory& src);
      Directory& operator=(Directory&& src);

      uint64_t Count() const;
      uint64_t Size() const override;
      std::list<std::wstring> List() const;

      void AddEntity(std::wstring, std::shared_ptr<Entity>);
      void RemoveEntity(const std::wstring&);
      void RemoveEntity(const Entity& value);

      OptionalShared<const Entity> FindEntity(const std::wstring&) const;
      OptionalShared<Entity> FindEntity(const std::wstring&);

      boost::optional<std::wstring> FindEntity(const Entity& value) const;

      using Contents = std::unordered_map<std::wstring, std::shared_ptr<Entity>>;
      Contents::const_iterator begin() const;
      Contents::const_iterator end() const;

   private:
      Contents m_contents;
   };
} // namespace NFileSystem

#endif // __vfs__FSEntity_h__
