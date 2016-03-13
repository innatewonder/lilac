/*
*  FILE          Delegate.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for delegate core utility.
*/

#define DELEGATE_BASE   BaseDelegate
#define DELEGATE_GLOBAL CONCATENATE(GlobalDelegate, DELEGATE_SUFFIX)
#define DELEGATE_METHOD CONCATENATE(MethodDelegate, DELEGATE_SUFFIX)

#if DELEGATE_CONST
  #define DELEGATE_QUALIFIER const
#else
  #define DELEGATE_QUALIFIER
#endif

namespace Core
{
  template <typename return_type = void, typename ParameterList = EMPTY_PARAMETERS, typename PayloadList = EMPTY_PAYLOAD>
  class DELEGATE_GLOBAL
  { };

  template <typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  class DELEGATE_GLOBAL<return_type, argument_template<parameters...>, argument_template<payload...>> : public DELEGATE_BASE<return_type, parameters...>
  {
    public:
      typedef return_type(*FunctionPointer)(parameters..., payload...);

      DELEGATE_GLOBAL(FunctionPointer function_, payload... payload_);

      virtual bool SafeCall(parameters...) const override;
      virtual return_type operator()(parameters... arguments) const override;
      virtual return_type Call(parameters... arguments) const override;

      virtual bool Equal(const DELEGATE_BASE<return_type, parameters...>* rhs) const override;

      INLINE virtual DelegateType::Type GetType(void) const override;
      INLINE virtual void* GetFunctionPointer(void) const override;
      INLINE virtual void* GetObjectPointer(void) const override;
      INLINE virtual std::string GetFunctionName(void) const override;

      template<s32 S>
      INLINE typename std::tuple_element<S, Containers::PayloadList<payload...>>::type const& Get(void) const;

      template<s32 S>
      INLINE void Set(typename std::tuple_element<S, Containers::PayloadList<payload...>>::type val);

      INLINE void Pack(payload... arguments);
      INLINE void Unpack(payload&... arguments) const;

    private:
      template<s32... S>
      return_type CallUnpackPayload(parameters... arguments, Containers::SequenceIndex<S...>) const;

      FunctionPointer function;
      Containers::PayloadList<payload...> Payload;
  };


  template <typename reciever, typename return_type = void, typename ParameterList = EMPTY_PARAMETERS, typename PayloadList = EMPTY_PAYLOAD>
  class DELEGATE_METHOD
  { };

  template <typename reciever, typename return_type, typename... parameters, typename... payload, template<typename...> class argument_template>
  class DELEGATE_METHOD<reciever, return_type, argument_template<parameters...>, argument_template<payload...>> : public DELEGATE_BASE<return_type, parameters...>
  {
    public:
      typedef return_type(reciever::*MethodPointer)(parameters..., payload...) DELEGATE_QUALIFIER;

      DELEGATE_METHOD(reciever*, MethodPointer function, payload...);

      void Bind(reciever* object);
      void Unbind(void);
      bool IsBound(void) const;

      virtual bool SafeCall(parameters...) const override;

      virtual return_type operator()(parameters...) const override;
      virtual return_type Call(parameters...) const override;
      virtual bool Equal(const DELEGATE_BASE<return_type, parameters...>* rhs) const override;

      INLINE virtual DelegateType::Type GetType(void) const override;
      INLINE virtual void* GetFunctionPointer(void) const override;
      INLINE virtual void* GetObjectPointer(void) const override;
      INLINE virtual std::string GetFunctionName(void) const override;

      template<s32 S>
      INLINE typename std::tuple_element<S, Containers::PayloadList<payload...>>::type const& Get(void) const;

      template<s32 S>
      INLINE void Set(typename std::tuple_element<S, Containers::PayloadList<payload...>>::type val);

      INLINE void Pack(payload... arguments);
      INLINE void Unpack(payload&... arguments) const;

    private:
      template<s32... S>
      return_type CallUnpackPayload(parameters... arguments, Containers::SequenceIndex<S...>) const;

      reciever* object;
      MethodPointer function;
      Containers::PayloadList<payload...> Payload;
  };
}

#include "Delegate.hpp"


#undef DELEGATE_QUALIFIER

#undef DELEGATE_BASE
#undef DELEGATE_GLOBAL
#undef DELEGATE_METHOD
