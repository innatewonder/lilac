#include "CommonPrecompiled.h"
#include "PoolAllocator.h"

namespace Memory
{
  /*
  page:
  nextPagePtr[h:d][h:d]
  */
  struct DataHeader
  {
    enum State : u08
    {
      NONE = 0,
      FREE = 1,
      IN_USE = 2
    } field;
    void* nextPtr;

    DataHeader(State s, void* next)
      : field(s), nextPtr(next)
      {}

    static DataHeader* FromHeadPtr(void* ptr)
    {
      return SCAST(DataHeader*, ptr);
    }

    static DataHeader* FromDataPtr(void* ptr)
    {
      return SCAST(DataHeader*, MovePtr(ptr, -s32(sizeof(DataHeader))));
    }
  };

  PoolAllocator::PoolAllocator(u32 objSize, u32 objsPerPage, Allocator* toUse)
    : m_pageSize(0), m_objsPerPage(objsPerPage), m_allocator(toUse)
    , m_freeHead(nullptr), m_pageHead(nullptr), m_pageTail(nullptr)
    , m_currentObjs(0), m_totalObjs(0)
  {
    m_dataSize = objSize + sizeof(DataHeader);
    m_pageSize = m_objsPerPage * m_dataSize + sizeof(void*);
    m_freeHead = NewPage();
  }

  PoolAllocator::~PoolAllocator()
  {
    assertion(m_currentObjs == 0);
    //deallocate all the pages
    while(m_pageHead)
    {
      void* temp = m_pageHead;
      memcpy(&m_pageHead, m_pageHead, sizeof(void*));
      m_allocator->Deallocate(temp);
    }
  }

  void* PoolAllocator::Allocate(u32 size)
  {
    assertion(size <= m_dataSize - sizeof(DataHeader));
    ++m_totalObjs;
    ++m_currentObjs;

    if(!m_freeHead)
    {
      m_freeHead = NewPage();
    }

    DataHeader* header = DataHeader::FromHeadPtr(m_freeHead);
    void* ret = MovePtr(m_freeHead, sizeof(DataHeader));
    
    m_freeHead = header->nextPtr;
    header->nextPtr = nullptr;
    header->field = DataHeader::IN_USE;
    
    return ret;
  }

  void PoolAllocator::Deallocate(void* data)
  {
    --m_currentObjs;

    DataHeader* header = DataHeader::FromDataPtr(data);
    header->nextPtr = m_freeHead;
    m_freeHead = header;
    header->field = DataHeader::FREE;
  }

  void PoolAllocator::Log()
  {
    LOG("\n::Pool Allocator Log::");
    LOG("Current Objs: " << m_currentObjs);
    LOG("Total Objs: " << m_totalObjs);
  }

  ///// private
  void* PoolAllocator::NewPage()
  {
    u32 ptrSize = sizeof(void*);
    char* page = SCAST(char*, m_allocator->Allocate(m_pageSize));
    //page = (void*)nullptr;
    memset(page, 0, ptrSize);

    // init all the obj next ptrs
    char* initPtr = page + ptrSize;
    for(u32 i = 0; i < m_objsPerPage; ++i)
    {
      DataHeader* h = DataHeader::FromHeadPtr(initPtr);
      h->nextPtr = initPtr + m_dataSize;
      h->field = DataHeader::FREE;
      initPtr += m_dataSize;
    }
    DataHeader::FromHeadPtr(initPtr - m_dataSize)->nextPtr = nullptr;

    // set page pointers
    if(!m_pageHead)
    {
      m_pageHead = page;
      m_pageTail = page;
    }
    else
    {
      memcpy(m_pageTail, &page, ptrSize);
      m_pageTail = page;
    }

    return page + ptrSize;
  }
}
