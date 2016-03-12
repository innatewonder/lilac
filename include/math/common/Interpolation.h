/*
*  FILE          Interpolation.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Represents common functions for interpolation methods.
*/

#pragma once

namespace Math
{
  template <typename T>
  inline T LinearInterp(const T& start, const T& end, f32 t)
  {
    return (start + (end - start) * Clamp(t, 0.0f, 1.0f));
  }

  template <typename T>
  inline T LinearInterpUnlocked(const T& start, const T& end, f32 t)
  {
    return (start + (end - start) * t);
  }

  template<class T, class U>
  inline T CubicInterp(const T& P0, const T& T0, const T& P1, const T& T1, const U& A)
  {
    const f32 A2 = A * A;
    const f32 A3 = A2 * A;

    return (T)(P0 * ((2.0f * A3) - (3.0f * A2) + 1.0f)) + (T0 * (A3 - (2.0f * A2) + A)) + (T1 * (A3 - A2)) + (P1 * ((-2.0f * A3) + (3.0f * A2)));
  }
}