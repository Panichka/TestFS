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
            throw Exception(ErrorCode::InternalError);

         return path;
      }

      Directory Root;

   private:
      ControlBlock();

      ControlBlock(const ControlBlock&) = delete;
      void operator=(const ControlBlock&) = delete;
   };

   ControlBlock::ControlBlock()
      : Root()
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

   Controller::EntityHandle Controller::Create(const Path& path, Entity::Category category)
   {
      return 0u;
   }

   void Controller::Delete(Controller::EntityHandle handle)
   {}

   bool Controller::Exists(const Path& path)
   {
      return false;
   }

   std::list<std::wstring> Controller::List(Controller::EntityHandle handle)
   {
      return std::list<std::wstring>();
   }

   uint64_t Controller::Size(Controller::EntityHandle handle)
   {
      return 0u;
   }

   ManagedArray Controller::Read(Controller::EntityHandle handle, uint64_t count)
   {
      return ManagedArray(std::make_pair(nullptr, 0u));
   }

   void Controller::Write(Controller::EntityHandle handle, const uint8_t* buffer, uint64_t count)
   {}
} // namespace NFileSystem