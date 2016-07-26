#ifndef __vfs__ReferenceCounter_h__
#define __vfs__ReferenceCounter_h__

#include <cstdint>
#include <memory>

namespace NCOMServer
{
   class ReferenceCounter final
   {
   public:
      explicit ReferenceCounter(uint32_t initWith = 0u);
      ReferenceCounter(const ReferenceCounter&) = delete;
      void operator=(const ReferenceCounter&) = delete;
      ~ReferenceCounter(); //= default;

      uint32_t operator++();
      uint32_t operator--();

      bool operator==(uint32_t) const;

   private:
      struct AtomicCounter;
      std::unique_ptr<AtomicCounter> m_counter;
   };
} // NCOMServer

#endif // __vfs__ReferenceCounter_h__
