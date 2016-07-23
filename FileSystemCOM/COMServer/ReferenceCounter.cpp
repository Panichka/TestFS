#include <atomic>
#include "ReferenceCounter.h"

namespace NCOMServer
{
   struct ReferenceCounter::AtomicCounter final
   {
      explicit AtomicCounter(uint32_t initWith = 0u)
         : Value(initWith)
      {}

      AtomicCounter(const AtomicCounter&) = delete;
      void operator=(const AtomicCounter&) = delete;
      ~AtomicCounter() = default;

      std::atomic<uint32_t> Value;
   };

   ReferenceCounter::ReferenceCounter(uint32_t initWith)
      : m_counter(std::make_unique<AtomicCounter>(initWith))
   {}

   uint32_t ReferenceCounter::operator++()
   {
      return ++m_counter->Value;
   }

   uint32_t ReferenceCounter::operator--()
   {
      auto current = m_counter->Value.load();

      while (!(0u == current || m_counter->Value.compare_exchange_strong(current, current - 1)))
      { ; }

      return current;
   }

   bool ReferenceCounter::operator==(const uint32_t& to) const
   {
      auto current = to;
      return m_counter->Value.compare_exchange_strong(current, to);
   }

   //need for deletion of pointer to incomplete type
   ReferenceCounter::~ReferenceCounter()
   {}
} // NCOMServer