#include "CommonPrecompiled.h"
#include "HeapAllocator.h"

namespace Memory
{
  struct Header
  {
    Header(u32 size) : size(size) {}

    static Header* FromHeaderPtr(void* ptr)
    {
      return SCAST(Header*, ptr);
    }

    static Header* FromDataPtr(void* ptr)
    {
      return SCAST(Header*, MovePtr(ptr, -s32(sizeof(Header))));
    }

    u32 size;
  };

  HeapAllocator::HeapAllocator()
    : m_totalAllocations(0), m_currentAllocations(0)
    , m_avgSize(0), m_memInUse(0)
  {}

  HeapAllocator::~HeapAllocator()
  {
    assertion(m_currentAllocations == 0);
  }

  void* HeapAllocator::Allocate(u32 size)
  {
    m_avgSize = (m_avgSize * m_totalAllocations + size) / (m_totalAllocations + 1);
    ++m_totalAllocations;
    ++m_currentAllocations;
    m_memInUse += size;

    void* ret = malloc(size + sizeof(Header));
    Header::FromHeaderPtr(ret)->size = size;
    return MovePtr(ret, sizeof(Header));
  }

  void HeapAllocator::Deallocate(void* ptr)
  {
    if(!ptr) return;
    if(m_currentAllocations == 0)
    {
      LOG("WAT");
      free(ptr);
      return;
    }
    --m_currentAllocations;
    m_memInUse -= Header::FromDataPtr(ptr)->size;
    free(MovePtr(ptr, -s32(sizeof(Header))));
  }

  void HeapAllocator::Log()
  {
    LOG("\n::Heap Allocator Log::");
    LOG("Total Allocations: " << m_totalAllocations);
    LOG("Average Allocation Size: " << m_avgSize);
    LOG("Current Allocations: " << m_currentAllocations);
    LOG("Current Memory In Use: " << m_memInUse);
  }
}
