#ifndef __vfs__FSExceptions_h__
#define __vfs__FSExceptions_h__

#include <exception>

namespace NFileSystem
{
   class InternalError : public std::exception
   {
   public:
      explicit InternalError() noexcept = default;

      const char* what() const noexcept override
      {
         return "Controller internal error";
      }
   };

   class AlreadyExists : public std::exception
   {
   public:
      explicit AlreadyExists() noexcept = default;

      const char* what() const noexcept override
      {
         return "Entity already exists in this location";
      }
   };

   class DoesNotExists : public std::exception
   {
   public:
      explicit DoesNotExists() noexcept = default;

      const char* what() const noexcept override
      {
         return "Entity doen't exists in this location";
      }
   };

   class IsLocked : public std::exception
   {
   public:
      explicit IsLocked() noexcept = default;

      const char* what() const noexcept override
      {
         return "Entity is locked by another process";
      }
   };
} // namespace NFileSystem

#endif // __vfs__FSExceptions_h__
