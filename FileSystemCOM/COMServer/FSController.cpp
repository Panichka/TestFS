#include "FSController.h"
namespace NFileSystem
{
   uint32_t Controller::Directory::Size() const
   {
      uint32_t totalSize = 0ul;
      for (const auto& item : m_Contents)
         totalSize += item.second->Size();

      return totalSize;
   }

   void Controller::Directory::AddEntity(std::string name, std::unique_ptr<Entity> entity)
   {
      if (!m_Contents.insert(std::make_pair(std::move(name), std::move(entity))).second)
         throw AlreadyExists();
   }

   void Controller::Directory::RemoveEntity(const std::string& name)
   {
      m_Contents.erase(name);
   }

   OptionalReference<const Controller::Directory::Entity> Controller::Directory::FindEntity(const std::string& name) const
   {
      auto it = m_Contents.find(name);
      if (m_Contents.cend() != it)
         return boost::make_optional(std::cref(*it->second));

      return boost::none;
   }

   OptionalReference<Controller::Directory::Entity> Controller::Directory::FindEntity(const std::string& name)
   {
      auto constResult = const_cast<const Directory&>(*this).FindEntity(name);
      if (constResult)
         return boost::make_optional(std::ref(const_cast<Entity&>(constResult->get())));

      return boost::none;
   }

   Controller::Controller()
      : m_controlBlock()
   {
      LoadControlBlock();
   }

   Controller::~Controller()
   {
      FlushControlBlock();
   }

   void Controller::LoadControlBlock()
   {}

   void Controller::FlushControlBlock() 
   {}
} // namespace NFileSystem