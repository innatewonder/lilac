/*
*  FILE          MetaInterface.hpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for meta interface template features.
*/

namespace Meta
{
  template<typename... Arguments>
  MetaReflectionDefinition::MetaReflectionDefinition(Arguments... args)
    : data(0)
  {
    Enable({args...});
  }

  INLINE void MetaReflectionDefinition::Set(s32 argument, bool active)
  {
    data ^= (-(active ? 1 : 0) ^ data) & (1 << argument);
  }

  INLINE void MetaReflectionDefinition::Enable(s32 argument)
  {
    data |= 1 << argument;
  }

  INLINE void MetaReflectionDefinition::Disable(s32 argument)
  {
    data &= ~(1 << argument);
  }

  INLINE void MetaReflectionDefinition::Toggle(s32 argument)
  {
    data ^= 1 << argument;
  }

  INLINE bool MetaReflectionDefinition::IsEnabled(s32 argument) const
  {
    return (data >> argument) & 1;
  }

  INLINE bool MetaReflectionDefinition::IsDisabled(s32 argument) const
  {
    return !IsEnabled(argument);
  }



  FORCEINLINE const MetaReflectionDefinition& MetaInterface::Definition(void) const
  {
    return definition;
  }

  FORCEINLINE const c08* MetaInterface::Label(void) const
  {
    return label.c_str();
  }

  FORCEINLINE const c08* MetaInterface::Category(void) const
  {
    return category.c_str();
  }

  FORCEINLINE const c08* MetaInterface::Format(void) const
  {
    return format.c_str();
  }

  FORCEINLINE const c08* MetaInterface::Help(void) const
  {
    return help.c_str();
  }

  template<typename T>
  FORCEINLINE T MetaInterface::Min(void) const
  {
    return T(min);
  }

  template<typename T>
  FORCEINLINE T MetaInterface::Max(void) const
  {
    return T(max);
  }

  template<typename T>
  FORCEINLINE Math::NumericVector2<T> MetaInterface::Range(void) const
  {
    return Math::NumericVector2<T>(T(min), T(max));
  }

  FORCEINLINE f32 MetaInterface::Speed(void) const
  {
    return speed;
  }

  FORCEINLINE f32 MetaInterface::Power(void) const
  {
    return power;
  }

  template<typename T>
  FORCEINLINE T MetaInterface::StepMin(void) const
  {
    return T(step_min);
  }

  template<typename T>
  FORCEINLINE T MetaInterface::StepMax(void) const
  {
    return T(step_max);
  }
}