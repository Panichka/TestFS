#include "FSExceptions.h"

namespace NFileSystem
{
   Exception::Exception(ErrorCode code) noexcept
      : Code(code)
   {}

   const char* Exception::what() const noexcept
   {
      return Message(Code).c_str();
   }

   namespace
   {
      const std::string& DefaultMsg()
      {
         static const std::string msg("Unknown error");
         return msg;
      }

      const std::string& InternalErrorMsg()
      {
         static const std::string msg("Controller internal error");
         return msg;
      }

      const std::string& AlreadyExistsMsg()
      {
         static const std::string msg("Entity already exists in this location");
         return msg;
      }

      const std::string& DoesNotExistsMsg()
      {
         static const std::string msg("Entity doen't exists in this location");
         return msg;
      }

      const std::string& InvalidArgumentMsg()
      {
         static const std::string msg("Invalid argument");
         return msg;
      }
   }

   const std::string& Exception::Message(ErrorCode code)
   {
      switch (code)
      {
      case ErrorCode::InternalError: return InternalErrorMsg();
      case ErrorCode::AlreadyExists: return AlreadyExistsMsg();
      case ErrorCode::DoesNotExists: return DoesNotExistsMsg();
      case ErrorCode::InvalidArgument: return InvalidArgumentMsg();
      default: return DefaultMsg();
      }
   }

} // namespace NFileSystem
