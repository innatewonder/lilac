/*
*  FILE          Event.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for event core utility.
*/
#pragma once

#include "DelegateDefinitions.h"

namespace Core
{
  template <typename ParameterList, typename PayloadList>
  class BaseEvent
  { };

  template <typename... parameters, typename... payload, template<typename...> class argument_template>
  class BaseEvent<argument_template<parameters...>, argument_template<payload...>>
  {
    public:
      typedef BaseDelegate<void, parameters..., payload...> DeletageType;

      virtual void Broadcast(parameters...) const = 0;
      virtual void SafeBroadcast(parameters...) const = 0;
      virtual void Register(DeletageType*) = 0;
      virtual void Unregister(DeletageType*) = 0;

      void operator()(parameters... arguments) const;
      void operator+=(DeletageType* function);
      void operator-=(DeletageType* function);

      void Clear(void);

      typedef Containers::List<DeletageType*> ListenerList;
      ListenerList listeners;
  };

  template <typename... parameters>
  class Event : public BaseEvent<Containers::ArgumentList<parameters...>, EMPTY_PAYLOAD>
  {
  public:
    Event();

    typedef typename BaseEvent<Containers::ArgumentList<parameters...>, EMPTY_PAYLOAD>::DeletageType DeletageType;

    virtual void Broadcast(parameters...) const override;
    virtual void SafeBroadcast(parameters...) const override;
    virtual void Register(DeletageType* function) override;
    virtual void Unregister(DeletageType* function) override;
  };

  template <typename ParameterList = EMPTY_ARGUMENTS, typename PayloadList = EMPTY_PAYLOAD>
  class EventPayload
  { };

  template <typename... parameters, typename... payload, template<typename...> class argument_template>
  class EventPayload<argument_template<parameters...>, argument_template<payload...>> : public BaseEvent<argument_template<parameters...>, argument_template<payload...>>
  {
    public:
      EventPayload(payload...);

      typedef typename BaseEvent<argument_template<parameters...>, argument_template<payload...>>::DeletageType DeletageType;

      virtual void Broadcast(parameters...) const override;
      virtual void SafeBroadcast(parameters...) const override;
      virtual void Register(DeletageType* function) override;
      virtual void Unregister(DeletageType* function) override;

      Containers::PayloadList<payload...>& GetPayload(void);

      template<s32 S>
      INLINE typename std::tuple_element<S, Containers::PayloadList<payload...>>::type const& Get(void) const;

      template<s32 S>
      INLINE void Set(typename std::tuple_element<S, Containers::PayloadList<payload...>>::type val);

      INLINE void Pack(payload... arguments);
      INLINE void Unpack(payload&... arguments) const;

    private:
      template<s32... S>
      void BroadcastUnpackPayload(parameters... arguments, Containers::SequenceIndex<S...>) const;

      template<s32... S>
      void SafeBroadcastUnpackPayload(parameters... arguments, Containers::SequenceIndex<S...>) const;

      Containers::PayloadList<payload...> Payload;
  };
}

#include "Event.hpp"