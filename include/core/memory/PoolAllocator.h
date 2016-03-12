#pragma once

namespace Memory
{
  class PoolAllocator : public Allocator
  {
  public:
    PoolAllocator(u32 objSize, u32 objsPerPage = 10,
      Allocator* toUse = gDefaultAllocator);
    ~PoolAllocator();

    virtual void* Allocate(u32 size);
    virtual void Deallocate(void* data);
    virtual void Log();

  private:
    //returns first free obj ptr
    void* NewPage();

    u32 m_pageSize;
    u32 m_dataSize;
    u32 m_objsPerPage;

    Allocator* m_allocator;

    void* m_freeHead;
    void* m_pageHead;
    void* m_pageTail;

    u32 m_currentObjs;
    u32 m_totalObjs;
  };
}
