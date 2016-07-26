#include "FSEntity.h"
#include "FSExceptions.h"

namespace NFileSystem
{
   uint32_t Directory::Size() const
   {
      uint32_t totalSize = 0ul;
      for (const auto& item : m_Contents)
         totalSize += item.second->Size();

      return totalSize;
   }

   void Directory::AddEntity(std::wstring name, std::unique_ptr<Entity> entity)
   {
      if (!m_Contents.emplace(std::move(name), std::move(entity)).second)
         throw AlreadyExists();
   }

   void Directory::RemoveEntity(const std::wstring& name)
   {
      m_Contents.erase(name);
   }

   OptionalReference<const Directory::Entity> Directory::FindEntity(const std::wstring& name) const
   {
      auto it = m_Contents.find(name);
      if (m_Contents.cend() != it)
         return boost::make_optional(std::cref(*it->second));

      return boost::none;
   }

   OptionalReference<Directory::Entity> Directory::FindEntity(const std::wstring& name)
   {
      auto constResult = const_cast<const Directory&>(*this).FindEntity(name);
      if (constResult)
         return boost::make_optional(std::ref(const_cast<Entity&>(constResult->get())));

      return boost::none;
   }
} // namespace NFileSystem