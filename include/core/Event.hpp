/*
*  FILE          EventPayload.hpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for EventPayload core utility.
*/

namespace Core
{
  template <typename... parameters, typename... payload, template<typename...> class argument_template>
  void BaseEvent<argument_template<parameters...>, argument_template<payload...>>::operator()(parameters... arguments) const
  {
    Broadcast(arguments...);
  }

  template <typename... parameters, typename... payload, template<typename...> class argument_template>
  void BaseEvent<argument_template<parameters...>, argument_template<payload...>>::operator+=(DeletageType* function)
  {
    Register(function);
  }

  template <typename... parameters, typename... payload, template<typename...> class argument_template>
  void BaseEvent<argument_template<parameters...>, argument_template<payload...>>::operator-=(DeletageType* function)
  {
    Unregister(function);
  }

  template <typename... parameters, typename... payload, template<typename...> class argument_template>
  void BaseEvent<argument_template<parameters...>, argument_template<payload...>>::Clear(void)
  {
    listeners.clear();
  }




  template <typename... parameters, typename... payload, template<typename...> class argument_template>
  EventPayload<argument_template<parameters...>, argument_template<payload...>>::EventPayload(payload... payload_)
    : Payload(payload_...)
  { }

  template <typename... parameters, typename... payload, template<typename...> class argument_template>
  void EventPayload<argument_template<parameters...>, argument_template<payload...>>::Broadcast(parameters... arguments) const
  {
    BroadcastUnpackPayload(arguments..., typename Containers::Sequence<sizeof...(payload)>::type());
  }

  template <typename... parameters, typename... payload, template<typename...> class argument_template>
  void EventPayload<argument_template<parameters...>, argument_template<payload...>>::SafeBroadcast(parameters... arguments) const
  {
    SafeBroadcastUnpackPayload(arguments..., typename Containers::Sequence<sizeof...(payload)>::type());
  }

  template <typename... parameters, typename... payload, template<typename...> class argument_template>
  void EventPayload<argument_template<parameters...>, argument_template<payload...>>::Register(DeletageType* function)
  {
    assertion(function);
    for(ListenerList::const_iterator it = listeners.begin(); it != listeners.end(); ++it)
    {
      if((*it)->Equal(function))
      {
        WARN("Reregistering delegate to EventPayload.");
        return;
      }
    }

    listeners.push_back(function);
  }

  template <typename... parameters, typename... payload, template<typename...> class argument_template>
  void EventPayload<argument_template<parameters...>, argument_template<payload...>>::Unregister(DeletageType* function)
  {
    assertion(function);
    ListenerList::const_iterator remove = listeners.end();
    for(ListenerList::const_iterator it = listeners.begin(); it != listeners.end(); ++it)
    {
      if((*it)->Equal(function))
      {
        remove = it;
        break;
      }
    }

    if(remove != listeners.end())
      listeners.erase(remove);
    else
      WARN("Unregistering delegate that does not exist in EventPayload.");
  }

  template <typename... parameters, typename... payload, template<typename...> class argument_template>
  Containers::PayloadList<payload...>& EventPayload<argument_template<parameters...>, argument_template<payload...>>::GetPayload(void)
  {
    return Payload;
  }

  template <typename... parameters, typename... payload, template<typename...> class argument_template> template<s32 S> inline
  typename std::tuple_element<S, Containers::PayloadList<payload...> >::type const& EventPayload<argument_template<parameters...>, argument_template<payload...>>::Get(void) const
  {
    return std::get<S>(Payload);
  }

  template <typename... parameters, typename... payload, template<typename...> class argument_template> template<s32 S> inline
  void EventPayload<argument_template<parameters...>, argument_template<payload...>>::Set(typename std::tuple_element<S, Containers::PayloadList<payload...> >::type val)
  {
    std::get<S>(Payload) = val;
  }

  template <typename... parameters, typename... payload, template<typename...> class argument_template>
  void EventPayload<argument_template<parameters...>, argument_template<payload...>>::Pack(payload... arguments)
  {
    Payload = std::make_tuple(arguments...);
  }

  template <typename... parameters, typename... payload, template<typename...> class argument_template>
  void EventPayload<argument_template<parameters...>, argument_template<payload...>>::Unpack(payload&... arguments) const
  {
    std::tie(arguments...) = Payload;
  }

  template <typename... parameters, typename... payload, template<typename...> class argument_template> template<s32... S>
  void EventPayload<argument_template<parameters...>, argument_template<payload...>>::BroadcastUnpackPayload(parameters... arguments, Containers::SequenceIndex<S...>) const
  {
    for(ListenerList::const_iterator it = listeners.begin(); it != listeners.end(); ++it)
    {
      (*it)->Call(arguments..., std::get<S>(Payload) ...);
    }
  }

  template <typename... parameters, typename... payload, template<typename...> class argument_template> template<s32... S>
  void EventPayload<argument_template<parameters...>, argument_template<payload...>>::SafeBroadcastUnpackPayload(parameters... arguments, Containers::SequenceIndex<S...>) const
  {
    for(ListenerList::const_iterator it = listeners.begin(); it != listeners.end(); ++it)
    {
      (*it)->SafeCall(arguments..., std::get<S>(Payload) ...);
    }
  }

  template <typename... parameters>
  Event<parameters...>::Event()
  { }

  template <typename... parameters>
  void Event<parameters...>::Broadcast(parameters... arguments) const
  {
    for(ListenerList::const_iterator it = listeners.begin(); it != listeners.end(); ++it)
    {
      (*it)->Call(arguments...);
    }
  }

  template <typename... parameters>
  void Event<parameters...>::SafeBroadcast(parameters... arguments) const
  {
    for(ListenerList::const_iterator it = listeners.begin(); it != listeners.end(); ++it)
    {
      (*it)->SafeCall(arguments...);
    }
  }

  template <typename... parameters>
  void Event<parameters...>::Register(DeletageType* function)
  {
    assertion(function);
    for(ListenerList::const_iterator it = listeners.begin(); it != listeners.end(); ++it)
    {
      if((*it)->Equal(function))
      {
        WARN("Reregistering delegate to Event.");
        return;
      }
    }

    listeners.push_back(function);
  }

  template <typename... parameters>
  void Event<parameters...>::Unregister(DeletageType* function)
  {
    assertion(function);
    ListenerList::const_iterator remove = listeners.end();
    for(ListenerList::const_iterator it = listeners.begin(); it != listeners.end(); ++it)
    {
      if((*it)->Equal(function))
      {
        remove = it;
        break;
      }
    }

    if(remove != listeners.end())
      listeners.erase(remove);
    else
      WARN("Unregistering delegate that does not exist in Event.");
  }
}