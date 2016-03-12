/*
*  FILE          MathRandom.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for Random functions.
*/
#pragma once

namespace Math
{
  template <typename T>
  inline T Random(const T &min, const T &max);

  template <>
  inline s32 Random(const s32 &min, const s32 &max);

  template <>
  inline u32 Random(const u32 &min, const u32 &max);

  inline f32 Random(void);

  namespace Gaussian
  {
    inline f32 RandomCentralLimitTheorem(f32 mean, f32 variance);
  }
}

#include "MathRandom.hpp"