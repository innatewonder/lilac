/*
*  FILE          ContainerDefinitions.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for forward declaration container types.
*/
#pragma once

#include <list>
#include <vector>
#include <unordered_map>
#include <map>
#include <tuple>
#include <array>
#include <stack>
#include <initializer_list>

namespace Containers
{
  template<class T>
  using List = std::list<T>;

  template<class T>
  using Vector = std::vector<T>;

  template<class Key, class T>
  using UnorderedMap = std::unordered_map<Key, T>;

  template<class Key, class T, class Hash>
  using UnorderedMapUserHash = std::unordered_map<Key, T, Hash>;

  template<class Key, class T>
  using Map = std::map<Key, T>;

  template<class T, size_t size>
  using Array = std::array<T, size>;



  template<class... arguments>
  using Tuple = std::tuple<arguments...>;
  
  template<class... arguments>
  using ParameterList = std::tuple<arguments...>;

  template<class... arguments>
  using ArgumentList = std::tuple<arguments...>;

  template<class... arguments>
  using PayloadList = std::tuple<arguments...>;

  template<std::size_t T, class... arguments>
  using TupleElement = std::tuple_element<T, std::tuple<arguments...>>;

  template<std::size_t T, class... arguments>
  using TupleElementType = typename std::tuple_element<T, std::tuple<arguments...>>::type;



  template<class T>
  using Stack = std::stack<T>;

  template<class T>
  using InitializerList = std::initializer_list<T>;

  template<class T1, class T2>
  using Pair = std::pair<T1, T2>;


  template<int...> struct SequenceIndex {};
  template<int N, int... S> struct Sequence : Sequence<N - 1, N - 1, S...> {};
  template<int...S> struct Sequence<0, S...> { typedef SequenceIndex<S...> type; };
}


#define EMPTY_PARAMETERS  Containers::Tuple<>
#define EMPTY_ARGUMENTS   Containers::Tuple<>
#define EMPTY_PAYLOAD     Containers::Tuple<>