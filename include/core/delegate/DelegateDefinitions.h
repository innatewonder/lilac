/*
*  FILE          DelegateDefinitions.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for every delegate and event type.
*/
#pragma once

namespace Core
{
  namespace DelegateType
  {
    enum Type
    {
      Global,
      ClassMethod,
      ObjectMethod,
      ReflectedFunction,
      Functor,
    };
  }

  template <typename return_type = void, typename... parameters>
  class BaseDelegate
  {
    public:
      virtual bool SafeCall(parameters...) const = 0;

      virtual return_type operator()(parameters...) const = 0;
      virtual return_type Call(parameters...) const = 0;
      virtual bool Equal(const BaseDelegate* rhs) const = 0;

      virtual DelegateType::Type GetType(void) const = 0;
      virtual void* GetFunctionPointer(void) const = 0;
      virtual void* GetObjectPointer(void) const = 0;
      virtual std::string GetFunctionName(void) const = 0;
  };
}

#define DELEGATE_SUFFIX
#define DELEGATE_CONST 0

#include "Delegate.h"

#undef DELEGATE_SUFFIX
#undef DELEGATE_CONST

#define DELEGATE_SUFFIX Const
#define DELEGATE_CONST 1

#include "Delegate.h"

#undef DELEGATE_SUFFIX
#undef DELEGATE_CONST