#pragma once

namespace Memory
{
  template<typename T, class ... ArgTypes>
  T* Allocator::New(ArgTypes ... args)
  {
    return new (Allocate(sizeof(T))) T(args...);
  }

  template<typename T>
  void Allocator::Delete(T* ptr)
  {
    if(ptr)
    {
      ptr->~T();
      Deallocate(ptr);
    }
  }

  template<typename T, class ... ArgTypes>
  T* New(ArgTypes ... args)
  {
    return gDefaultAllocator->New<T>(args...);
  }

  template<typename T>
  void Delete(T* ptr)
  {
    gDefaultAllocator->Delete(ptr);
  }
}
