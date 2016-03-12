/*
*  FILE          MathCommon.hpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for core math functions.
*/

namespace Math
{
  template <typename T>
  inline void Swap(T& a, T& b)
  {
    T temp = a;
    a = b;
    b = temp;
  }

  template <typename T>
  inline T Min(const T& a, const T& b)
  {
    return a < b ? a : b;
  }

  template <typename T>
  inline T Min(const T& a, const T& b, const T& c)
  {
    return Min(Min(a, b), Min(b, c));
  }

  template <typename T>
  inline T Max(const T& a, const T& b)
  {
    return a > b ? a : b;
  }

  template <typename T>
  inline T Max(const T& a, const T& b, const T& c)
  {
    return Max(Max(a, b), Max(b, c));
  }

  template <typename T>
  inline T Clamp(const T& val, const T& min, const T& max)
  {
    return Max(Min(val, max), min);
  }

  template <typename T>
  inline s32 Ceiling(const T& val)
  {
    if(val == s32(val))
      return s32(val);
    else if(val < T(0))
      return s32(val);
    else
      return (s32(val) + 1);
  }

  template <typename T>
  inline s32 Floor(const T& val)
  {
    if(val == s32(val))
      return s32(val);
    else if(val < T(0))
      return (s32(val) - 1);
    else
      return s32(val);
  }

  inline f32 Fraction(f32 val)
  {
    return val - Floor(val);
  }

  template <typename T>
  inline s32 Round(const T& val)
  {
    if(val < T(0))
      return (T(-0.5f) < val - s32(val) ? s32(val) : s32(val - 1));
    else
      return (val - s32(val) < T(0.5f) ? s32(val) : s32(val + 1));
  }

  template <typename T>
  inline T Abs(const T& val)
  {
    return (val < T(0) ? -val : val);
  }

  template<typename T>
  inline NumericVector2<T> Abs(const NumericVector2<T>& val)
  {
    return NumericVector2<T>(Abs(val.x), Abs(val.y));
  }

  template<typename T>
  inline NumericVector3<T> Abs(const NumericVector3<T>& val)
  {
    return NumericVector2<T>(Abs(val.x), Abs(val.y), Abs(val.z));
  }

  template<typename T>
  inline NumericVector4<T> Abs(const NumericVector4<T>& val)
  {
    return NumericVector2<T>(Abs(val.x), Abs(val.y), Abs(val.z), Abs(val.w));
  }

  template <typename T>
  inline s32 Sign(const T& val)
  {
    return (val < T(0) ? NEGATIVE : POSITIVE);
  }

  inline void ZeroIfZero(f32 &val)
  {
    if(Equal(val, 0.0f))
      val = 0.0f;
  }

  inline f32 RadiansToDegrees(f32 radians)
  {
    return radians * RAD_TO_DEG;
  }

  inline f32 DegreesToRadians(f32 degrees)
  {
    return degrees * DEG_TO_RAD;
  }

  inline void GetSinCos(f32 angle, f32& sina, f32& cosa)
  {
    sina = sin(angle);
    cosa = cos(angle);
    ZeroIfZero(sina);
    ZeroIfZero(cosa);
  }

  template <typename T>
  inline bool Equal(T a, T b)
  {
    return a == b;
  }

  inline bool Equal(f32 a, f32 b, f32 diff)
  {
    return (a <= b + diff && a >= b - diff);
  }

  template <typename T>
  inline bool NotEqual(T a, T b)
  {
    return a != b;
  }

  inline bool NotEqual(f32 a, f32 b, f32 diff)
  {
    return !(a <= b + diff && a >= b - diff);
  }
}