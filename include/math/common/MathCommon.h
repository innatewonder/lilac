/*
 *  FILE          MathCommon.h
 *  AUTHOR        Brendon Clifford
 *  DESCRIPTION
 *    Declaration for core math functions.
 */
#pragma once


namespace Math
{
  const f32 EPSILON         = 1.0e-5f;
  const f32 MAX_FLOAT       = 3.402823466e+38f;
  const f32 PI              = f32(4.0 * atan(1.0));
  const f32 TWO_PI          = 2.0f * PI;
  const f32 HALF_PI         = 0.5f * PI;
  const f32 DEG_TO_RAD      = PI / 180.0f;
  const f32 RAD_TO_DEG      = 180.0f / PI;
  const s32 POSITIVE        = 1;
  const s32 NEGATIVE        = -1;
}

namespace Math
{
  template<class T> class NumericVector2;
  template<class T> class NumericVector3;
  template<class T> class NumericVector4;

  template<s32 N>
  struct Factorial
  {
    enum { Value = N * Factorial<N - 1>::Value };
  };

  template<>
  struct Factorial<0>
  {
    enum { Value = 1 };
  };

  template <typename T>
  inline void Swap(T& a, T& b);

  template <typename T>
  inline T Min(const T& a, const T& b);

  template <typename T>
  inline T Min(const T& a, const T& b, const T& c);

  template <typename T>
  inline T Max(const T& a, const T& b);

  template <typename T>
  inline T Max(const T& a, const T& b, const T& c);

  template <typename T>
  inline T Clamp(const T& val, const T& min, const T& max);

  template <typename T>
  inline s32 Ceiling(const T& val);

  template <typename T>
  inline s32 Floor(const T& val);

  inline f32 Fraction(f32 val);

  template <typename T>
  inline s32 Round(const T& val);

  template <typename T>
  inline T Abs(const T& val);

  template <typename T>
  inline s32 Sign(const T& val);

  inline void ZeroIfZero(f32 &val);

  inline f32 RadiansToDegrees(f32 radians);

  inline f32 DegreesToRadians(f32 degrees);

  inline void GetSinCos(f32 angle, f32& sina, f32& cosa);

  template <typename T>
  inline bool Equal(T a, T b);

  inline bool Equal(f32 a, f32 b, f32 diff = EPSILON);

  template <typename T>
  inline bool NotEqual(T a, T b);

  inline bool NotEqual(f32 a, f32 b, f32 diff = EPSILON);
}// Math namespace

#include "AlgebraIncludes.h"

namespace Math
{
  template<typename T>
  inline NumericVector2<T> Abs(const NumericVector2<T>& val);

  template<typename T>
  inline NumericVector3<T> Abs(const NumericVector3<T>& val);

  template<typename T>
  inline NumericVector4<T> Abs(const NumericVector4<T>& val);
}

#include "MathCommon.hpp"