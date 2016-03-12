/*
*  FILE          Sphere.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for Sphere geometry class.
*/
#pragma once

namespace Math
{
  class Sphere
  {
    public:
      Sphere(const NumericPoint4<f32>& center_ = NumericPoint4<f32>::ORIGIN, f32 radius_ = 0.0f);
      Sphere(const Sphere& sphere_);

      FORCEINLINE const NumericPoint4<f32>& Center(void) const;
      FORCEINLINE const f32& Radius(void) const;

      FORCEINLINE f32 Diameter(void) const;
      FORCEINLINE f32 Circumference(void) const;
      FORCEINLINE f32 Area(void) const;
      FORCEINLINE f32 SurfaceArea(void) const;
      FORCEINLINE f32 Volume(void) const;

      Sphere operator+(const NumericVector4<f32>& rhs) const;
      Sphere operator-(const NumericVector4<f32>& rhs) const;
      Sphere operator*(const Matrix& rhs) const;

      Sphere& operator+=(const NumericVector4<f32>& rhs);
      Sphere& operator-=(const NumericVector4<f32>& rhs);
      Sphere& operator*=(const Matrix& rhs);

      Sphere& operator=(const Sphere& rhs);

      bool operator==(const Sphere& rhs) const;
      bool operator!=(const Sphere& rhs) const;

      f32 DistanceBetweenCenter(const Sphere& rhs) const;
      f32 DistanceBetweenSurface(const Sphere& rhs) const;
      f32 DistanceToCenter(const NumericPoint4<f32>& rhs) const;
      f32 DistanceToSurface(const NumericPoint4<f32>& rhs) const;

      bool IsInside(const NumericPoint4<f32>& rhs, f32 epsilon = EPSILON) const;
      bool IsInside(const Sphere& rhs, f32 epsilon = EPSILON) const;

      bool Intersects(const Sphere& rhs, f32 epsilon = EPSILON) const;

      NumericPoint4<f32>  center;
      f32                 radius;
  };
}