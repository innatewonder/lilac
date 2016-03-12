/*
 *  FILE          Plane.cpp
 *  AUTHOR        Brendon Clifford
 *  DESCRIPTION
 *    Implementation for Plane structures.
 */
#include "CommonPrecompiled.h"
#include "Plane.h"

namespace Math
{
  const Plane Plane::XY(0.0f, 0.0f, 1.0f, 0.0f);
  const Plane Plane::XZ(0.0f, 1.0f, 0.0f, 0.0f);
  const Plane Plane::YZ(1.0f, 0.0f, 0.0f, 0.0f);

  Plane::Plane(f32 a_, f32 b_, f32 c_, f32 d_)
    : a(a_), b(b_), c(c_), d(d_)
  { }

  Plane::Plane(const NumericVector4<f32>& v0_, const NumericVector4<f32>& v1_)
  { }

  Plane::Plane(const NumericVector4<f32>& normal_, const NumericPoint4<f32>& position_)
    : a(normal_.x), b(normal_.y), c(normal_.z), d(-(normal_.Dot(position_)))
  { }

  Plane::Plane(const NumericPoint4<f32>& p0_, const NumericPoint4<f32>& p1_, const NumericPoint4<f32>& p2_)
  { }

  Plane::Plane(const Plane& rhs)
    : a(rhs.a), b(rhs.b), c(rhs.c), d(rhs.d)
  { }

  FORCEINLINE NumericPoint4<f32> Plane::Origin(void) const
  {
    return NumericPoint4<f32>::ORIGIN + Normal() * Constant();
  }

  FORCEINLINE NumericVector4<f32> Plane::Normal(void) const
  {
    return NumericVector4<f32>(a, b, c);
  }

  FORCEINLINE f32 Plane::Constant(void) const
  {
    return d;
  }

  Plane& Plane::Flip(void)
  {
    a = -a;
    b = -b;
    c = -c;
    d = -d;
    return *this;
  }

  INLINE void Plane::Basis(NumericVector4<f32>& v0, NumericVector4<f32>& v1) const
  {

  }

  Plane Plane::operator-(void) const
  {
    return Plane(-a, -b, -c, -d);
  }

  Plane Plane::operator+(const NumericVector4<f32>& rhs) const
  {
    return Plane(a, b, c, d - Normal().Dot(rhs));
  }

  Plane Plane::operator-(const NumericVector4<f32>& rhs) const
  {
    return Plane(a, b, c, d + Normal().Dot(rhs));
  }

  Plane Plane::operator*(const Quaternion& rhs) const
  {
    return Plane();
  }

  Plane& Plane::operator+=(const NumericVector4<f32>& rhs)
  {
    d += -Normal().Dot(rhs);
    return *this;
  }

  Plane& Plane::operator-=(const NumericVector4<f32>& rhs)
  {
    d -= Normal().Dot(rhs);
    return *this;
  }

  Plane& Plane::operator*=(const Quaternion& rhs)
  {
    return *this;
  }

  Plane& Plane::operator=(const Plane& rhs)
  {
    a = rhs.a;
    b = rhs.b;
    c = rhs.c;
    d = rhs.d;
    return *this;
  }

  bool Plane::operator==(const Plane& rhs) const
  {
    return Equal(a, rhs.a) && Equal(b, rhs.b) && Equal(c, rhs.c) && Equal(d, rhs.d);
  }

  bool Plane::operator!=(const Plane& rhs) const
  {
    return !(*this == rhs);
  }

  f32 Plane::Distance(const NumericPoint4<f32>& rhs) const
  {
    return d + Normal().Dot(rhs);
  }

  NumericPoint4<f32> Plane::Projection(const NumericPoint4<f32>& rhs) const
  {
    NumericVector4<f32> v = rhs - (NumericPoint4<f32>::ORIGIN + Normal() * d);
    f32 distance = v.Dot(Normal());
    return rhs - Normal() * distance;
  }

  NumericPoint4<f32> Plane::Projection(const LineSegment3D& rhs) const
  {
    return NumericPoint4<f32>();
  }

  Plane::PointIntersectionStatus Plane::Intersects(const NumericPoint4<f32>& rhs, f32 epsilon) const
  {
    f32 distance = Distance(rhs);
    if(Equal(distance, 0.0f, epsilon))
      return PointIntersectionStatus::eIntersects;
    else if(distance < 0.0f)
      return PointIntersectionStatus::eBack;
    else
      return PointIntersectionStatus::eFront;
  }

  Plane::SegmentIntersectionStatus Plane::Intersects(const LineSegment3D& rhs, NumericPoint4<f32>& intersection) const
  {
    intersection = NumericPoint4<f32>::ORIGIN;

    NumericVector4<f32> U = rhs.Head() - Origin();
    NumericVector4<f32> V = rhs.GetVector();

    f32 NoU = Dot(Normal(), U);
    f32 NoV = Dot(Normal(), V);

    if(Equal(NoV, 0.0f))
    {
      if(Equal(NoU, 0.0f))
        return SegmentIntersectionStatus::eInside;
      else
        return SegmentIntersectionStatus::eParallel;
    }

    f32 t = NoU / NoV;
    if(t < 0.0f)
      return SegmentIntersectionStatus::eBack;
    else if(t > 1.0f)
      return SegmentIntersectionStatus::eFront;

    intersection = rhs.Head() + U * t;
    return SegmentIntersectionStatus::eIntersects;
  }

  Plane::RayIntersectionStatus Plane::Intersects(const Ray3D& rhs, NumericPoint4<f32>& intersection) const
  {
    intersection = NumericPoint4<f32>::ORIGIN;

    NumericVector4<f32> U = rhs.Origin() - Origin();
    NumericVector4<f32> V = rhs.Direction();

    f32 NoU = Dot(Normal(), U);
    f32 NoV = Dot(Normal(), V);

    if(Equal(NoV, 0.0f))
    {
      if(Equal(NoU, 0.0f))
        return RayIntersectionStatus::eInside;
      else
        return RayIntersectionStatus::eParallel;
    }

    intersection = rhs.Origin() + U * (NoU / NoV);
    return RayIntersectionStatus::eIntersects;
  }

  Ray3D Plane::Reflect(const Ray3D& rhs) const
  {
    NumericPoint4<f32> intersection;
    if(Intersects(rhs, intersection) == RayIntersectionStatus::eIntersects)
      return Ray3D(intersection, Math::Reflect(Normal(), rhs.Direction()));
    else
      return rhs;
  }
}