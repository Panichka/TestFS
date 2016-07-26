#ifndef __vfs__FSEntity_h__
#define __vfs__FSEntity_h__

#include <cstdint>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>

namespace NFileSystem
{
   //for compatibility with std::optional that has not specialization for T&
   template <class T>
   using OptionalReference = boost::optional<std::reference_wrapper< T >>;

   struct Entity
   {
      virtual uint32_t Size() const = 0;
      virtual ~Entity() = default;

      enum class Category { File, Directory };
      const Category category;

      explicit Entity(Category cat)
         : category(cat)
      {}

      Entity() = delete;
      void operator=(const Entity&) = delete;
   };

   struct File : Entity
   {
      using Entity::Entity;
      File() = delete;

      uint32_t Size() const override { return m_size; }
      uint64_t Offset() const { return m_offset; }

   private:
      uint32_t m_size = 0u;
      uint64_t m_offset = 0ull;
   };

   struct Directory : Entity
   {
      using Entity::Entity;
      Directory() = delete;

      uint32_t Size() const override;

      void AddEntity(std::wstring, std::unique_ptr<Entity>);
      void RemoveEntity(const std::wstring&);

      OptionalReference<const Entity> FindEntity(const std::wstring&) const;
      OptionalReference<Entity> FindEntity(const std::wstring&);

   private:
      std::unordered_map<std::wstring, std::unique_ptr<Entity>> m_Contents;
   };
} // namespace NFileSystem

#endif // __vfs__FSEntity_h__
