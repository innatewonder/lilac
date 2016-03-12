#pragma once

#include "ArgParser.h"

namespace Memory
{
  class Allocator
  {
  public:
    template<typename T, class ... ArgTypes>
    T* New(ArgTypes ... args);

    template<typename T>
    void Delete(T* ptr);

    Allocator();
    virtual ~Allocator() {}

    virtual void* Allocate(u32 size) = 0;
    virtual void Deallocate(void* data) = 0;
    virtual void Log() = 0;
    
  protected:
    u32 m_memInUse;
  };

  void Initialize(ArgParser& args);
  void Destroy();

  void* MovePtr(void* ptr, s32 bytes);
}

void* operator new  (std::size_t size);
void* operator new[](std::size_t size);
void* operator new  (std::size_t size, const std::nothrow_t& t);
void* operator new[](std::size_t size, const std::nothrow_t& t);

void operator delete  (void* ptr) NOEXCEPT;
void operator delete[](void* ptr) NOEXCEPT;
void operator delete  (void* ptr, const std::nothrow_t& t);
void operator delete[](void* ptr, const std::nothrow_t& t);
