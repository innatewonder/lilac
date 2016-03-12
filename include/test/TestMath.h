#pragma once

template<typename T>
static bool Compare(const Math::NumericVector2<T>& v, T x, T y)
{
  return Math::Equal(v.x, x) && Math::Equal(v.y, y);
}

template<typename T>
static bool Compare(const Math::NumericVector3<T>& v, T x, T y, T z)
{
  return Math::Equal(v.x, x) && Math::Equal(v.y, y) && Math::Equal(v.z, z);
}

template<typename T>
static bool Compare(const Math::NumericVector4<T>& v, T x, T y, T z, T w)
{
  return Math::Equal(v.x, x) && Math::Equal(v.y, y) && Math::Equal(v.z, z) && Math::Equal(v.w, w);
}

namespace Test
{
  void Test_MathCommon(void);
  void Test_NumericVector(void);
  void Test_NumericPoint(void);
  void Test_Matrix(void);
  void Test_Quaternion(void);
  void Test_Segment(void);
  void Test_Ray(void);
  void Test_Sphere(void);
  void Test_AABB(void);
  void Test_Color(void);

  void Test_Math(void);
}