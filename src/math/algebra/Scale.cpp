/*
*  FILE          Scale.cpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for non-uniform 3D scaling values.
*/
#include "CommonPrecompiled.h"
#include "Scale.h"

namespace Math
{
  const Scale Scale::IDENTITY(NumericVector4<f32>::ONE);

  Scale::Scale()
    : scale(NumericVector4<f32>::ONE), uniform(false)
  { }

  Scale::Scale(f32 uniform_scale)
    : scale(uniform_scale, uniform_scale, uniform_scale), uniform(true)
  { }

  Scale::Scale(const NumericVector4<f32>& nonuniform_scale)
    : scale(nonuniform_scale), uniform(false)
  { }

  Scale Scale::operator*(const Scale& rhs)
  {
    return Scale(NumericVector4<f32>(scale.x * rhs.scale.x, scale.y * rhs.scale.y, scale.z * rhs.scale.z));
  }

  Scale& Scale::operator*=(const Scale& rhs)
  {
    scale.x *= rhs.scale.x;
    scale.y *= rhs.scale.y;
    scale.z *= rhs.scale.z;
    return *this;
  }

  std::ostream& operator<<(std::ostream& os, const Scale& obj)
  {
    os << obj.scale.x << obj.scale.y << obj.scale.z << obj.scale.w;
    return os;
  }

  std::istream& operator>>(std::istream& is, Scale& obj)
  {
    is >> obj.scale.x >> obj.scale.y >> obj.scale.z >> obj.scale.w;
    return is;
  }

  Scale Scale::Inverse(void) const
  {
    return Scale(NumericVector4<f32>(1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z));
  }

  NumericVector4<f32>& Scale::GetVector(void)
  {
    return scale;
  }
}