/*
*  FILE          MetaInterface.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for meta interface features.
*/
#pragma once

#include "InterfaceCommon.h"

namespace Meta
{
  class MetaReflectionDefinition
  {
    public:
      template<typename... Arguments>
      explicit MetaReflectionDefinition(Arguments... args);

      MetaReflectionDefinition(const MetaReflectionDefinition& rhs);

      explicit MetaReflectionDefinition(s32 data_);

      INLINE void Set(s32 argument, bool active = true);
      INLINE void Enable(s32 argument);
      INLINE void Disable(s32 argument);
      INLINE void Toggle(s32 argument);

      INLINE bool IsEnabled(s32 argument) const;
      INLINE bool IsDisabled(s32 argument) const;

    private:

      void Enable(const Containers::InitializerList<s32>& arguments);

      s32 data;
  };

  class MetaInterface
  {
    public:
      MetaInterface(const MetaReflectionDefinition& definiton_,
                    const c08* label_ = "",
                    const c08* category_ = "",
                    const c08* format_ = "%.2f",
                    const c08* help_ = "",
                    f32 min_ = -FLT_MAX,
                    f32 max_ = FLT_MAX,
                    f32 speed_ = 1.0f,
                    f32 power_ = 1.0f,
                    f32 step_min_ = 1.0f,
                    f32 step_max_ = 100.0f);

      FORCEINLINE const MetaReflectionDefinition& Definition(void) const;
      FORCEINLINE const c08* Label(void) const;
      FORCEINLINE const c08* Category(void) const;
      FORCEINLINE const c08* Format(void) const;
      FORCEINLINE const c08* Help(void) const;

      template<typename T>
      FORCEINLINE T Min(void) const;
      template<typename T>
      FORCEINLINE T Max(void) const;
      template<typename T>
      FORCEINLINE Math::NumericVector2<T> Range(void) const;

      FORCEINLINE f32 Speed(void) const;
      FORCEINLINE f32 Power(void) const;

      template<typename T>
      FORCEINLINE T StepMin(void) const;
      template<typename T>
      FORCEINLINE T StepMax(void) const;

    private:
      const MetaReflectionDefinition definition;

      std::string label;
      std::string category;
      std::string format;
      std::string help;

      const f32 min;
      const f32 max;
      const f32 speed;
      const f32 power;

      const f32 step_min;
      const f32 step_max;
  };
}
#include "MetaInterface.hpp"
