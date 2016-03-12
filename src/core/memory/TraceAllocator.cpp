#include "CommonPrecompiled.h"
#include "TraceAllocator.h"

namespace Memory
{
  TraceAllocator::TraceAllocator(const String& name, Allocator* toUse)
    : m_totalAllocations(0), m_currentAllocations(0), m_memInUse(0)
    , m_name(name), m_allocator(toUse)
  {}

  TraceAllocator::~TraceAllocator()
  {
    assertion(m_currentAllocations == 0);
  }

  void* TraceAllocator::Allocate(u32 size)
  {
    ++m_currentAllocations;
    m_memInUse += size;
    ++m_totalAllocations;
    return m_allocator->Allocate(size);
  }

  void TraceAllocator::Deallocate(void* data)
  {
    m_allocator->Deallocate(data);
    --m_currentAllocations;
  }

  void TraceAllocator::Log()
  {
    LOG("\n::" << m_name << " Memory Log::");
    LOG("Total Allocations: " << m_totalAllocations);
    LOG("Current Allocations: " << m_currentAllocations);
    //LOG("Current Memory In Use: " << m_memInUse);
  }
}
