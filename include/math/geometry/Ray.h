/*
 *  FILE          Ray.h
 *  AUTHOR        Brendon Clifford
 *  DESCRIPTION
 *    Declaration for Ray structures.
 */
#pragma once

namespace Math
{
  template<class NumericPoint, class NumericVector>
  class Ray
  {
    public:
      Ray(const NumericPoint& origin_ = NumericPoint::ORIGIN, const NumericVector& direction_ = NumericVector::ZERO);
      Ray(const NumericPoint& origin_, const NumericPoint& destination_);
      Ray(const Ray& rhs);
      explicit Ray(const LineSegment<NumericPoint, NumericVector>& line_);

      FORCEINLINE const NumericPoint& Origin(void) const;
      FORCEINLINE const NumericVector& Direction(void) const;

      Ray& Flip(void) const;

      Ray operator-(void) const;

      Ray operator+(const NumericVector& rhs) const;
      Ray operator-(const NumericVector& rhs) const;
      Ray operator*(const Quaternion& rhs) const;

      Ray& operator+=(const NumericVector& rhs);
      Ray& operator-=(const NumericVector& rhs);
      Ray& operator*=(const Quaternion& rhs);

      Ray& operator=(const Ray& rhs);

      bool operator==(const Ray& rhs) const;
      bool operator!=(const Ray& rhs) const;

      bool IsParallel(const Ray& rhs) const;
      bool IsOrthogonal(const Ray& rhs) const;

      f32 Distance(const NumericPoint& rhs) const;
      NumericPoint Projection(const NumericPoint& rhs) const;
      LineSegment<NumericPoint, NumericVector> Segment(f32 extent) const;

      static const Ray ZERO;
      static const Ray X_AXIS;
      static const Ray Y_AXIS;
      static const Ray Z_AXIS;

      NumericPoint origin;
      NumericVector direction;
  };

  typedef Ray<NumericPoint2<f32>, NumericVector2<f32>> Ray2D;
  typedef Ray<NumericPoint4<f32>, NumericVector4<f32>> Ray3D;
}

#include "Ray.hpp"