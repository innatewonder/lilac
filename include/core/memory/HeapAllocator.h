#pragma once

namespace Memory
{
  class HeapAllocator : public Allocator
  {
  public:
    HeapAllocator();
    ~HeapAllocator();

    virtual void* Allocate(u32 size);
    virtual void Deallocate(void* ptr);
    virtual void Log();

  private:
    u32 m_totalAllocations;
    u32 m_currentAllocations;
    u32 m_avgSize;
    u32 m_memInUse;
  };
}