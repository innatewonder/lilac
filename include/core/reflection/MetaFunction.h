/*
*  FILE          MetaFunction.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for core meta functions.
*/
#pragma once

namespace Meta
{
  /* Invalid Function */
  template<class T> struct MetaFunction;

  /* Global Function Pointer */
  template<class return_type, class... arguments>
  struct MetaFunction<return_type(*)(arguments...)> : public MetaFunction<return_type(arguments...)>
  { };

  /* Global Meta Function */
  template<class return_type, class... arguments>
  struct MetaFunction<return_type(arguments...)>
  {
    static const u32 arity = sizeof...(arguments);

    template<u32 N>
    struct argument
    {
      static_assert(N < arity, "error: invalid parameter index.");
      typedef typename std::tuple_element<N, std::tuple<arguments...>>::type type;
    };

    std::tuple<arguments...> a;
  };
}







