/*
*  FILE          Sphere.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for Sphere geometry class.
*/
#include "CommonPrecompiled.h"
#include "Sphere.h"

namespace Math
{
  Sphere::Sphere(const NumericPoint4<f32>& center_, f32 radius_)
    : center(center_), radius(radius_)
  { }

  Sphere::Sphere(const Sphere& sphere_)
    : center(sphere_.center), radius(sphere_.radius)
  { }

  FORCEINLINE const NumericPoint4<f32>& Sphere::Center(void) const
  {
    return center;
  }

  FORCEINLINE const f32& Sphere::Radius(void) const
  {
    return radius;
  }

  FORCEINLINE f32 Sphere::Diameter(void) const
  {
    return 2.0f * radius;
  }

  FORCEINLINE f32 Sphere::Circumference(void) const
  {
    return TWO_PI * radius;
  }

  FORCEINLINE f32 Sphere::Area(void) const
  {
    return PI * radius * radius;
  }

  FORCEINLINE f32 Sphere::SurfaceArea(void) const
  {
    return 4.0f * PI * radius * radius;
  }

  FORCEINLINE f32 Sphere::Volume(void) const
  {
    return 4.0f / 3.0f * PI * radius * radius * radius;
  }

  Sphere Sphere::operator+(const NumericVector4<f32>& rhs) const
  {
    return Sphere(center + rhs, radius);
  }

  Sphere Sphere::operator-(const NumericVector4<f32>& rhs) const
  {
    return Sphere(center - rhs, radius);
  }

  Sphere Sphere::operator*(const Matrix& rhs) const
  {
    return Sphere(center + rhs.GetTranslation(), radius * rhs.GetScale().Max());
  }

  Sphere& Sphere::operator+=(const NumericVector4<f32>& rhs)
  {
    center += rhs;
    return *this;
  }

  Sphere& Sphere::operator-=(const NumericVector4<f32>& rhs)
  {
    center -= rhs;
    return *this;
  }

  Sphere& Sphere::operator*=(const Matrix& rhs)
  {
    center += rhs.GetTranslation();
    radius *= rhs.GetScale().Max();
    return *this;
  }

  Sphere& Sphere::operator=(const Sphere& rhs)
  {
    center = rhs.center;
    radius = rhs.radius;
    return *this;
  }

  bool Sphere::operator==(const Sphere& rhs) const
  {
    return center == rhs.center && Equal(radius, rhs.radius);
  }

  bool Sphere::operator!=(const Sphere& rhs) const
  {
    return !(*this == rhs);
  }

  f32 Sphere::DistanceBetweenCenter(const Sphere& rhs) const
  {
    return center.Distance(rhs.center);
  }

  f32 Sphere::DistanceBetweenSurface(const Sphere& rhs) const
  {
    return Max(center.Distance(rhs.center) - radius - rhs.radius, 0.0f);
  }

  f32 Sphere::DistanceToCenter(const NumericPoint4<f32>& rhs) const
  {
    return center.Distance(rhs);
  }

  f32 Sphere::DistanceToSurface(const NumericPoint4<f32>& rhs) const
  {
    return Abs(center.Distance(rhs) - radius);
  }

  bool Sphere::IsInside(const NumericPoint4<f32>& rhs, f32 epsilon) const
  {
    return center.Distance(rhs) <= radius + epsilon;
  }

  bool Sphere::IsInside(const Sphere& rhs, f32 epsilon) const
  {
    return center.Distance(rhs.center) + rhs.radius <= radius + epsilon;
  }

  bool Sphere::Intersects(const Sphere& rhs, f32 epsilon) const
  {
    return Equal(Max(DistanceBetweenCenter(rhs) - (radius + rhs.radius), 0.0f), 0.0f, epsilon);
  }
}