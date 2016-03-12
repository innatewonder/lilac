/*
*  FILE          Segment.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for Segment structures.
*/
#pragma once

namespace Math
{
  template<class NumericPoint, class NumericVector>
  class LineSegment
  {
    public:
      LineSegment(const NumericPoint& p0_ = NumericPoint::ORIGIN, const NumericPoint& p1_ = NumericPoint::ORIGIN);
      LineSegment(const NumericPoint& center_, const NumericVector& direction_, f32 extent_);
      LineSegment(const LineSegment& rhs);

      FORCEINLINE const NumericPoint& Head(void) const;
      FORCEINLINE const NumericPoint& Tail(void) const;

      FORCEINLINE NumericVector GetVector(void) const;
      FORCEINLINE NumericPoint& Center(void) const;
      FORCEINLINE NumericVector& Direction(void) const;

      FORCEINLINE f32 Length(void) const;

      LineSegment& Flip(void);

      LineSegment operator-(void) const;

      LineSegment operator+(const NumericVector& rhs) const;
      LineSegment operator+(const f32& rhs) const;
      LineSegment operator-(const NumericVector& rhs) const;
      LineSegment operator-(const f32& rhs) const;

      LineSegment& operator+=(const NumericVector& rhs);
      LineSegment& operator+=(const f32& rhs);
      LineSegment& operator-=(const NumericVector& rhs);
      LineSegment& operator-=(const f32& rhs);

      LineSegment& operator=(const LineSegment& rhs);

      bool operator==(const LineSegment& rhs) const;
      bool operator!=(const LineSegment& rhs) const;

      bool IsParallel(const LineSegment& rhs) const;
      bool IsOrthogonal(const LineSegment& rhs) const;

      f32 Distance(const NumericPoint& rhs) const;
      NumericPoint Projection(const NumericPoint& rhs, bool clamp = false) const;

      NumericPoint p0, p1;
  };

  typedef LineSegment<NumericPoint2<f32>, NumericVector2<f32>> LineSegment2D;
  typedef LineSegment<NumericPoint4<f32>, NumericVector4<f32>> LineSegment3D;
}

#include "Segment.hpp"