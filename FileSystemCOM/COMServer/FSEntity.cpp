#include "FSEntity.h"
#include "FSExceptions.h"

namespace NFileSystem
{
   File::File()
      : Entity(Category::File)
   {}

   File::File(const File& src)
      : Entity(Category::File)
      , m_size(src.m_size)
      , m_offset(src.m_offset)
   {}

   File& File::operator=(const File& src)
   {
      m_size = src.m_size;
      m_offset = src.m_offset;
      return *this;
   }

   Directory::Directory()
      : Entity(Category::Directory)
   {}

   Directory::Directory(const Directory& src)
      : Entity(Category::Directory)
      , m_contents(src.m_contents)
   {}

   Directory::Directory(Directory&& src)
      : Entity(Category::Directory)
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

   uint64_t Directory::Size() const
   {
      uint64_t totalSize = 0ul;
      for (const auto& item : m_contents)
         totalSize += item.second->Size();

      return totalSize;
   }

   void Directory::AddEntity(std::wstring name, std::shared_ptr<Entity> entity)
   {
      if (!m_contents.emplace(std::move(name), std::move(entity)).second)
         throw Exception(ErrorCode::AlreadyExists);
   }

   void Directory::RemoveEntity(const std::wstring& name)
   {
      m_contents.erase(name);
   }

   OptionalReference<const Entity> Directory::FindEntity(const std::wstring& name) const
   {
      auto it = m_contents.find(name);
      if (m_contents.cend() != it)
         return boost::make_optional(std::cref(*it->second));

      return boost::none;
   }

   OptionalReference<Entity> Directory::FindEntity(const std::wstring& name)
   {
      auto constResult = const_cast<const Directory&>(*this).FindEntity(name);
      if (constResult)
         return boost::make_optional(std::ref(const_cast<Entity&>(constResult->get())));

      return boost::none;
   }
} // namespace NFileSystem