/*
*  FILE          Scale.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for non-uniform 3D scaling values.
*/
#pragma once

namespace Math
{
  class Scale
  {
    public:
      Scale();
      Scale(f32 uniform_scale);
      Scale(const NumericVector4<f32>& nonuniform_scale);

      Scale operator*(const Scale& rhs);
      Scale& operator*=(const Scale& rhs);

      friend std::ostream& operator<<(std::ostream& os, const Scale& obj);
      friend std::istream& operator>>(std::istream& is, Scale& obj);

      Scale Inverse(void) const;
      NumericVector4<f32>& GetVector(void);

      FORCEINLINE f32 UniformScale(void) const;
      FORCEINLINE f32 Min(void) const;
      FORCEINLINE f32 Max(void) const;
      FORCEINLINE bool& Uniform(void);

      static const Scale IDENTITY;

      NumericVector4<f32> scale;
      bool uniform;
  };

  FORCEINLINE f32 Scale::UniformScale(void) const
  {
    return scale.w;
  }

  FORCEINLINE f32 Scale::Min(void) const
  {
    return Math::Min(scale.x, scale.y, scale.z);
  }

  FORCEINLINE f32 Scale::Max(void) const
  {
    return Math::Max(scale.x, scale.y, scale.z);
  }

  FORCEINLINE bool& Scale::Uniform(void)
  {
    return uniform;
  }
}