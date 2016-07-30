#ifndef __vfs__FSExceptions_h__
#define __vfs__FSExceptions_h__

#include <string>

namespace NFileSystem
{
   enum class ErrorCode : uint8_t
   { InternalError, AlreadyExists, DoesNotExists, IsLocked};

   class Exception : public std::exception
   {
   public:
      explicit Exception(ErrorCode code) noexcept;

      const char* what() const noexcept override;

      static const std::string& Message(ErrorCode code);
      const ErrorCode Code;
   };
} // namespace NFileSystem

#endif // __vfs__FSExceptions_h__
