#pragma once

namespace Memory
{
  class TraceAllocator : public Allocator
  {
  public:
    TraceAllocator(const String& name, Allocator* toUse);
    ~TraceAllocator();

    virtual void* Allocate(u32 size);
    virtual void Deallocate(void* data);
    virtual void Log();

  private:
    Allocator* m_allocator;
    String m_name;

    u32 m_totalAllocations;
    u32 m_currentAllocations;
    u32 m_memInUse;
  };
  extern TraceAllocator* gDefaultAllocator;
}
