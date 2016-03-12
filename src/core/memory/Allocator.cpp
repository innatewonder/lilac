#include "CommonPrecompiled.h"
#include "HeapAllocator.h"

namespace Memory
{
  char buffer[sizeof(HeapAllocator)];
  HeapAllocator* lNewDeleteAllocator = nullptr;
  HeapAllocator* lDefaultInternal = nullptr;
  TraceAllocator* gDefaultAllocator = nullptr;
  bool useCustom;

  Allocator::Allocator()
    : m_memInUse(0) 
  {}

  void Initialize(ArgParser& args)
  {
    useCustom = args.Has("-mg");

    lNewDeleteAllocator = new(buffer)HeapAllocator();
    lDefaultInternal = lNewDeleteAllocator->New<HeapAllocator>();
    gDefaultAllocator = lNewDeleteAllocator->New<TraceAllocator>("Global", lDefaultInternal);
  }

  void Destroy()
  {
    lNewDeleteAllocator->Delete(gDefaultAllocator);
    gDefaultAllocator = nullptr;

    lNewDeleteAllocator->Delete(lDefaultInternal);
    lDefaultInternal = nullptr;

    lNewDeleteAllocator->Log();
    lNewDeleteAllocator->~HeapAllocator();
    lNewDeleteAllocator = nullptr;
  }

  void* MovePtr(void* ptr, s32 bytes)
  {
    return (char*)ptr + bytes;
  }
}

void* operator new(std::size_t size)
{
  if(Memory::lNewDeleteAllocator && Memory::useCustom)
  {
    return Memory::lNewDeleteAllocator->Allocate(size);
  }
  return malloc(size);
}

void* operator new[](std::size_t size)
{
  if(Memory::lNewDeleteAllocator && Memory::useCustom)
  {
    return Memory::lNewDeleteAllocator->Allocate(size);
  }
  return malloc(size);
}

void* operator new(std::size_t size, const std::nothrow_t& tag)
{
  try
  {
    if(Memory::lNewDeleteAllocator && Memory::useCustom)
    {
      return Memory::lNewDeleteAllocator->Allocate(size);
    }
    return malloc(size);
  }
  catch(...)
  {
    assertion(false);
  }
  return nullptr;
}

void* operator new[](std::size_t size, const std::nothrow_t& tag)
{
  try
  {
    if(Memory::lNewDeleteAllocator && Memory::useCustom)
    {
      return Memory::lNewDeleteAllocator->Allocate(size);
    }
    return malloc(size);
  }
  catch(...)
  {
    assertion(false);
  }
  return nullptr;
}

void operator delete(void* ptr) NOEXCEPT
{
  if(Memory::lNewDeleteAllocator && Memory::useCustom)
  {
    Memory::lNewDeleteAllocator->Deallocate(ptr);
    return;
  }
  free(ptr);
}

void operator delete[](void* ptr) NOEXCEPT
{
  if(Memory::lNewDeleteAllocator && Memory::useCustom)
  {
    Memory::lNewDeleteAllocator->Deallocate(ptr);
    return;
  }
  free(ptr);
}

void operator delete(void* ptr, const std::nothrow_t& tag)
{
  try
  {
    if(Memory::lNewDeleteAllocator && Memory::useCustom)
    {
      Memory::lNewDeleteAllocator->Deallocate(ptr);
      return;
    }
    free(ptr);
  }
  catch(...)
  {
    assertion(false);
  }
}

void operator delete[](void* ptr, const std::nothrow_t& tag)
{
  try
  {
    if(Memory::lNewDeleteAllocator && Memory::useCustom)
    {
      Memory::lNewDeleteAllocator->Deallocate(ptr);
      return;
    }
    free(ptr);
  }
  catch(...)
  {
    assertion(false);
  }
}