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
      virtual uint64_t Size() const = 0;
      virtual ~Entity() = default;

      enum class Category { File, Directory };
      const Category category;

      explicit Entity(Category cat)
         : category(cat)
      {}

     Entity() = delete;
	  Entity(const Entity&) = delete;
	  void operator=(const Entity&) = delete;
   };

   struct File : Entity
   {
      File();
      File(const File& src); 
      File& operator=(const File& src);

      uint64_t Size() const override { return m_size; }
      uint64_t Offset() const { return m_offset; }

   private:
      uint64_t m_size = 0u;
      uint64_t m_offset = 0ull;
   };

   struct Directory : Entity
   {
      Directory();

      Directory(const Directory& src);
      Directory(Directory&& src);

      Directory& operator=(const Directory& src);
      Directory& operator=(Directory&& src);

      uint64_t Size() const override;

      void AddEntity(std::wstring, std::shared_ptr<Entity>);
      void RemoveEntity(const std::wstring&);

      OptionalReference<const Entity> FindEntity(const std::wstring&) const;
      OptionalReference<Entity> FindEntity(const std::wstring&);

   private:
      std::unordered_map<std::wstring, std::shared_ptr<Entity>> m_contents;
   };
} // namespace NFileSystem

#endif // __vfs__FSEntity_h__
