#ifndef __vfs__FSController_h__
#define __vfs__FSController_h__

#include <cstdint>
#include <unordered_map>
#include <list>
#include <memory>
#include <boost/optional.hpp>

namespace NFileSystem
{
   class AlreadyExists : public std::exception
   {
   public:
      explicit AlreadyExists() noexcept = default;

      virtual const char* what() const noexcept
      {
         return "Entity already exists in this location";
      }
   };

   class DoesNotExists : public std::exception
   {
   public:
      explicit DoesNotExists() noexcept = default;

      virtual const char* what() const noexcept
      {
         return "Entity doen't exists in this location";
      }
   };

   class IsLocked : public std::exception
   {
   public:
      explicit IsLocked() noexcept = default;

      virtual const char* what() const noexcept
      {
         return "Entity is locked by another process";
      }
   };

   //for compatibility with std::optional that has not specialization for T&
   template <class T>
   using OptionalReference = boost::optional<std::reference_wrapper< T >>;

   class Controller final
   {
   public:

      Controller();
      ~Controller();

      struct Entity
      {
         virtual uint32_t Size() const = 0;
         virtual ~Entity() = default;

         enum class Category { File, Directory };
         const Category category;

         Entity(Category cat)
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
         uint32_t m_size = 0ul;
         uint64_t m_offset = 0ull;
      };

      struct Directory : Entity
      {
         using Entity::Entity;
         Directory() = delete;

         uint32_t Size() const override;

         void AddEntity(std::string, std::unique_ptr<Entity>);
         void RemoveEntity(const std::string&);

         OptionalReference<const Entity> FindEntity(const std::string&) const;
         OptionalReference<Entity> FindEntity(const std::string&);

      private:
         std::unordered_map<std::string, std::unique_ptr<Entity>> m_Contents;
      };	

      void Create(const std::string& path, Entity::Category category);
      void Delete(const std::string& path);

      bool Exists(const std::string& path);

      std::list<std::string> List(const std::string& path);

      unsigned int Size(const std::string& path);

      std::unique_ptr<uint8_t[]> Read(const std::string& path);
      void Write(const std::string& path, const std::unique_ptr<uint8_t[]>& buffer);

   private:

      struct ControlBlock
      {
         ControlBlock()
            : Root(Entity::Category::Directory)
         {}

         Directory Root;
      };
      ControlBlock m_controlBlock;

      void LoadControlBlock();
      void FlushControlBlock();
   };
} // namespace NFileSystem

#endif // __vfs__FSController_h__
