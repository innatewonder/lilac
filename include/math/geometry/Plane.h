/*
*  FILE          Plane.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for plane geometry class.
*/
#pragma once

#include "Segment.h"
#include "Ray.h"

namespace Math
{
  class Plane
  {
    public:
      Plane(f32 a_ = 0.0f, f32 b_ = 0.0f, f32 c_ = 0.0f, f32 d_ = 0.0f);
      Plane(const NumericVector4<f32>& v0_, const NumericVector4<f32>& v1_);
      Plane(const NumericVector4<f32>& normal_, const NumericPoint4<f32>& position_);
      Plane(const NumericPoint4<f32>& p0_, const NumericPoint4<f32>& p1_, const NumericPoint4<f32>& p2_);
      Plane(const Plane& rhs);

      FORCEINLINE NumericPoint4<f32> Origin(void) const;
      FORCEINLINE NumericVector4<f32> Normal(void) const;
      FORCEINLINE f32 Constant(void) const;
      Plane& Flip(void);

      INLINE void Basis(NumericVector4<f32>& v0, NumericVector4<f32>& v1) const;

      Plane operator-(void) const;
      Plane operator+(const NumericVector4<f32>& rhs) const;
      Plane operator-(const NumericVector4<f32>& rhs) const;
      Plane operator*(const Quaternion& rhs) const;

      Plane& operator+=(const NumericVector4<f32>& rhs);
      Plane& operator-=(const NumericVector4<f32>& rhs);
      Plane& operator*=(const Quaternion& rhs);

      Plane& operator=(const Plane& rhs);

      bool operator==(const Plane& rhs) const;
      bool operator!=(const Plane& rhs) const;

      f32 Distance(const NumericPoint4<f32>& rhs) const;
      NumericPoint4<f32> Projection(const NumericPoint4<f32>& rhs) const;
      NumericPoint4<f32> Projection(const LineSegment3D& rhs) const;

      enum class PointIntersectionStatus { eIntersects, eFront, eBack };
      PointIntersectionStatus Intersects(const NumericPoint4<f32>& rhs, f32 epsilon = EPSILON) const;

      enum class SegmentIntersectionStatus { eIntersects, eParallel, eFront, eBack, eInside };
      SegmentIntersectionStatus Intersects(const LineSegment3D& rhs, NumericPoint4<f32>& intersection) const;

      enum class RayIntersectionStatus { eIntersects, eParallel, eInside };
      RayIntersectionStatus Intersects(const Ray3D& rhs, NumericPoint4<f32>& intersection) const;

      Ray3D Reflect(const Ray3D& rhs) const;

      static const Plane XY;
      static const Plane XZ;
      static const Plane YZ;

      f32 a, b, c, d;
  };
}