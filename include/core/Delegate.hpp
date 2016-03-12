/*
*  FILE          Delegate.hpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for delegate core utility.
*/

namespace Core
{
  template <typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  DELEGATE_GLOBAL<return_type, argument_template<parameters...>, argument_template<payload...>>::DELEGATE_GLOBAL(FunctionPointer function_, payload... payload_)
    : function(function_), Payload(payload_...)
  { }

  template <typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  bool DELEGATE_GLOBAL<return_type, argument_template<parameters...>, argument_template<payload...>>::SafeCall(parameters... arguments) const
  {
    Call(arguments...);
    return true;
  }

  template <typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  return_type DELEGATE_GLOBAL<return_type, argument_template<parameters...>, argument_template<payload...>>::operator()(parameters... arguments) const
  {
    Call(arguments...);
  }

  template <typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  return_type DELEGATE_GLOBAL<return_type, argument_template<parameters...>, argument_template<payload...>>::Call(parameters... arguments) const
  {
    return CallUnpackPayload(arguments..., typename Containers::Sequence<sizeof...(payload)>::type());
  }

  template <typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template> template<s32... S>
  return_type DELEGATE_GLOBAL<return_type, argument_template<parameters...>, argument_template<payload...>>::CallUnpackPayload(parameters... arguments, Containers::SequenceIndex<S...>) const
  {
    return function(arguments..., std::get<S>(Payload) ...);
  }

  template <typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  bool DELEGATE_GLOBAL<return_type, argument_template<parameters...>, argument_template<payload...>>::Equal(const DELEGATE_BASE* rhs) const
  {
    return GetFunctionPointer() == rhs->GetFunctionPointer() && GetObjectPointer() == rhs->GetObjectPointer();
  }

  template <typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  DelegateType::Type DELEGATE_GLOBAL<return_type, argument_template<parameters...>, argument_template<payload...>>::GetType(void) const
  {
    return DelegateType::Global;
  }

  template <typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  void* DELEGATE_GLOBAL<return_type, argument_template<parameters...>, argument_template<payload...>>::GetFunctionPointer(void) const
  {
    return *(void**)&function;
  }

  template <typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  void* DELEGATE_GLOBAL<return_type, argument_template<parameters...>, argument_template<payload...>>::GetObjectPointer(void) const
  {
    return nullptr;
  }

  template <typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  std::string DELEGATE_GLOBAL<return_type, argument_template<parameters...>, argument_template<payload...>>::GetFunctionName(void) const
  {
    return "";
  }

  template <typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template> template<s32 S>
  typename std::tuple_element<S, Containers::PayloadList<payload...>>::type const& DELEGATE_GLOBAL<return_type, argument_template<parameters...>, argument_template<payload...>>::Get(void) const
  {
    return std::get<S>(Payload);
  }

  template <typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template> template<s32 S>
  void DELEGATE_GLOBAL<return_type, argument_template<parameters...>, argument_template<payload...>>::Set(typename std::tuple_element<S, Containers::PayloadList<payload...>>::type val)
  {
    std::get<S>(Payload) = val;
  }

  template <typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  void DELEGATE_GLOBAL<return_type, argument_template<parameters...>, argument_template<payload...>>::Pack(payload... arguments)
  {
    Payload = std::make_tuple(arguments...);
  }

  template <typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  void DELEGATE_GLOBAL<return_type, argument_template<parameters...>, argument_template<payload...>>::Unpack(payload&... arguments) const
  {
    std::tie(arguments...) = Payload;
  }




  template <typename reciever, typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  DELEGATE_METHOD<reciever, return_type, argument_template<parameters...>, argument_template<payload...>>::DELEGATE_METHOD(reciever* object_, MethodPointer function_, payload... payload_)
    : object(object_), function(function_), Payload(payload_...)
  { }

  template <typename reciever, typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  bool DELEGATE_METHOD<reciever, return_type, argument_template<parameters...>, argument_template<payload...>>::SafeCall(parameters... arguments) const
  {
    if(object)
    {
      Call(arguments...);
      return true;
    }

    return false;
  }

  template <typename reciever, typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  return_type DELEGATE_METHOD<reciever, return_type, argument_template<parameters...>, argument_template<payload...>>::operator()(parameters... arguments) const
  {
    return Call(arguments...);
  }

  template <typename reciever, typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  return_type DELEGATE_METHOD<reciever, return_type, argument_template<parameters...>, argument_template<payload...>>::Call(parameters... arguments) const
  {
    assertion(object);
    return CallUnpackPayload(arguments..., typename Containers::Sequence<sizeof...(payload)>::type());
  }

  template <typename reciever, typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template> template<s32... S>
  return_type DELEGATE_METHOD<reciever, return_type, argument_template<parameters...>, argument_template<payload...>>::CallUnpackPayload(parameters... arguments, Containers::SequenceIndex<S...>) const
  {
    return (object->*function)(arguments..., std::get<S>(Payload) ...);
  }

  template <typename reciever, typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  bool DELEGATE_METHOD<reciever, return_type, argument_template<parameters...>, argument_template<payload...>>::Equal(const DELEGATE_BASE* rhs) const
  {
    return GetFunctionPointer() == rhs->GetFunctionPointer() && GetObjectPointer() == rhs->GetObjectPointer();
  }

  template <typename reciever, typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  DelegateType::Type DELEGATE_METHOD<reciever, return_type, argument_template<parameters...>, argument_template<payload...>>::GetType(void) const
  {
    return DelegateType::ObjectMethod;
  }

  template <typename reciever, typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  void* DELEGATE_METHOD<reciever, return_type, argument_template<parameters...>, argument_template<payload...>>::GetFunctionPointer(void) const
  {
    return *(void**)&function;
  }

  template <typename reciever, typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  void* DELEGATE_METHOD<reciever, return_type, argument_template<parameters...>, argument_template<payload...>>::GetObjectPointer(void) const
  {
    return object;
  }

  template <typename reciever, typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  std::string DELEGATE_METHOD<reciever, return_type, argument_template<parameters...>, argument_template<payload...>>::GetFunctionName(void) const
  {
    return "";
  }

  template <typename reciever, typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template> template<s32 S>
  typename std::tuple_element<S, Containers::PayloadList<payload...>>::type const& DELEGATE_METHOD<reciever, return_type, argument_template<parameters...>, argument_template<payload...>>::Get(void) const
  {
    return std::get<S>(Payload);
  }

  template <typename reciever, typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template> template<s32 S>
  void DELEGATE_METHOD<reciever, return_type, argument_template<parameters...>, argument_template<payload...>>::Set(typename std::tuple_element<S, Containers::PayloadList<payload...>>::type val)
  {
    std::get<S>(Payload) = val;
  }

  template <typename reciever, typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  void DELEGATE_METHOD<reciever, return_type, argument_template<parameters...>, argument_template<payload...>>::Pack(payload... arguments)
  {
    Payload = std::make_tuple(arguments...);
  }

  template <typename reciever, typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  void DELEGATE_METHOD<reciever, return_type, argument_template<parameters...>, argument_template<payload...>>::Unpack(payload&... arguments) const
  {
    std::tie(arguments...) = Payload;
  }
}