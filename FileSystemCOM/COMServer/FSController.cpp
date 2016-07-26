#include <boost/filesystem.hpp>

#include "FSController.h"
#include "FSExceptions.h"

namespace NFileSystem
{
   struct ControlBlock
   {
      static ControlBlock& Instance()
      {
         static ControlBlock instance;
         return instance;
      }

      static const Path& PhysicalFileName()
      {
         static boost::system::error_code eCode;
         static const Path path(boost::filesystem::current_path(eCode) /= "fsdata");

         if (boost::system::errc::success != eCode)
            throw InternalError();

         return path;
      }

      Directory Root;

   private:
      ControlBlock();

      ControlBlock(const ControlBlock&) = delete;
      void operator=(const ControlBlock&) = delete;
   };

   ControlBlock::ControlBlock()
      : Root(Entity::Category::Directory)
   {
      if (boost::filesystem::exists(PhysicalFileName()))
         ;
   }

   Controller::Controller()
   {

   }

   Controller::~Controller()
   {

   }

   void Controller::Create(const Path& path, Entity::Category category)
   {}

   void Controller::Delete(const Path& path)
   {}

   bool Controller::Exists(const Path& path)
   {
      return false;
   }

   std::list<std::wstring> Controller::List(const Path& path)
   {
      return std::list<std::wstring>();
   }

   uint64_t Controller::Size(const Path& path)
   {
      return 0u;
   }

   ManagedArray Controller::Read(const Path& path, uint64_t count)
   {
      return ManagedArray(std::make_pair(nullptr, 0u));
   }

   void Controller::Write(const Path& path, const uint8_t* buffer, uint64_t count)
   {}
} // namespace NFileSystem