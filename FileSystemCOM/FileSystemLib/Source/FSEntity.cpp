#include "FSEntity.h"
#include "FSExceptions.h"
#include <iterator>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>

namespace NFileSystem
{
   void Entity::Parent(std::weak_ptr<Directory> parent)
   {
      m_parent = parent;
   }

   std::weak_ptr<Directory> Entity::Parent()
   {
      return m_parent;
   }

   std::weak_ptr<const Directory> Entity::Parent() const
   {
      return m_parent;
   }

   File::File(size_t offset, size_t size, std::shared_ptr<Directory> parent)
      : Entity(Category(), parent)
      , m_size(size)
      , m_offset(offset)
   {}

   File::File(const File& src)
      : Entity(Category(), nullptr)
      , m_size(src.m_size)
      , m_offset(src.m_offset)
   {}

   File& File::operator=(const File& src)
   {
      m_size = src.m_size;
      m_offset = src.m_offset;
      return *this;
   }

   Directory::Directory(std::shared_ptr<Directory> parent)
      : Entity(Category(), parent)
   {}

   Directory::Directory(const Directory& src)
      : Entity(Category(), nullptr)
      , m_contents(src.m_contents)
   {}

   Directory::Directory(Directory&& src)
      : Entity(Category(), nullptr)
      , m_contents(std::move(src.m_contents))
   {
      src.m_contents.clear();
   }

   Directory& Directory::operator=(Directory&& src)
   {
      m_contents = std::move(src.m_contents);
      src.m_contents.clear();
      return *this;
   }

   Directory& Directory::operator=(const Directory& src)
   {
      m_contents = src.m_contents;
      return *this;
   }

   size_t Directory::Count() const
   {
      return m_contents.size();
   }

   size_t Directory::Size() const
   {
      size_t totalSize = 0ul;
      for (const auto& item : m_contents)
         totalSize += item.second->Size();

      return totalSize;
   }

   std::list<std::wstring> Directory::List() const
   {
      std::list<std::wstring> keys;
      boost::copy(m_contents | boost::adaptors::map_keys, std::back_inserter(keys));
      return keys;
   }

   void Directory::AddEntity(std::shared_ptr<Directory> dir, std::wstring name, std::shared_ptr<Entity> entity)
   {
      assert(dir && entity);

      auto inserted = dir->m_contents.emplace(std::move(name), std::move(entity));
      if (inserted.second)
         inserted.first->second->Parent(dir);
   }

   void Directory::RemoveEntity(const std::wstring& name)
   {
      m_contents.erase(name);
   }

   void Directory::RemoveEntity(const Entity& value)
   {
      auto it = std::find_if(m_contents.begin(), m_contents.end(),
         [&value](const std::pair<std::wstring, std::shared_ptr<Entity>>& item)
      {
         return item.second && (&value == item.second.get());
      });

      if (m_contents.end() != it)
         m_contents.erase(it);
   }

   OptionalShared<const Entity> Directory::FindEntity(const std::wstring& name) const
   {
      auto it = m_contents.find(name);
      if (m_contents.cend() != it)
         return boost::make_optional(std::const_pointer_cast<const Entity>(it->second));

      return boost::none;
   }

   OptionalShared<Entity> Directory::FindEntity(const std::wstring& name)
   {
      auto constResult = const_cast<const Directory&>(*this).FindEntity(name);
      if (constResult)
         return boost::make_optional(std::const_pointer_cast<Entity>(constResult.get()));

      return boost::none;
   }

   boost::optional<std::wstring> Directory::FindEntity(const Entity& value) const
   {
      auto it = std::find_if(m_contents.begin(), m_contents.end(),
         [&value](const std::pair<std::wstring, std::shared_ptr<Entity>>& item)
      {
         return item.second && (&value == item.second.get());
      });

      if (m_contents.cend() != it)
         return boost::make_optional(it->first);

      return boost::none;      
   }

   Directory::Contents::const_iterator Directory::begin() const
   {
      return m_contents.begin();
   }

   Directory::Contents::const_iterator Directory::end() const
   {
      return m_contents.end();
   }
} // namespace NFileSystem