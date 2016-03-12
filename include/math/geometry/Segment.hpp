/*
 *  FILE          Segment.hpp
 *  AUTHOR        Brendon Clifford
 *  DESCRIPTION
 *    Implementation for Segment structures.
 */

namespace Math
{
  template<class NumericPoint, class NumericVector>
  LineSegment<NumericPoint, NumericVector>::LineSegment(const NumericPoint& p0_, const NumericPoint& p1_)
    : p0(p0_), p1(p1_)
  { }
  
  template<class NumericPoint, class NumericVector>
  LineSegment<NumericPoint, NumericVector>::LineSegment(const NumericPoint& center_, const NumericVector& direction_, f32 extent_)
    : p0(center_ - direction_ * (extent_ * 0.5f)), p1(center_ + direction_ * (extent_ * 0.5f))
  { }

  template<class NumericPoint, class NumericVector>
  LineSegment<NumericPoint, NumericVector>::LineSegment(const LineSegment<NumericPoint, NumericVector>& rhs)
    : p0(rhs.p0), p1(rhs.p1)
  { }

  template<class NumericPoint, class NumericVector>
  FORCEINLINE const NumericPoint& LineSegment<NumericPoint, NumericVector>::Head(void) const
  {
    return p0;
  }

  template<class NumericPoint, class NumericVector>
  FORCEINLINE const NumericPoint& LineSegment<NumericPoint, NumericVector>::Tail(void) const
  {
    return p1;
  }

  template<class NumericPoint, class NumericVector>
  FORCEINLINE NumericVector LineSegment<NumericPoint, NumericVector>::GetVector(void) const
  {
    return p1 - p0;
  }

  template<class NumericPoint, class NumericVector>
  FORCEINLINE NumericPoint& LineSegment<NumericPoint, NumericVector>::Center(void) const
  {
    return p0.Midpoint(p1);
  }

  template<class NumericPoint, class NumericVector>
  FORCEINLINE NumericVector& LineSegment<NumericPoint, NumericVector>::Direction(void) const
  {
    return (p1 - p0).Normalize();
  }

  template<class NumericPoint, class NumericVector>
  FORCEINLINE f32 LineSegment<NumericPoint, NumericVector>::Length(void) const
  {
    return p0.Distance(p1);
  }

  template<class NumericPoint, class NumericVector>
  LineSegment<NumericPoint, NumericVector>& LineSegment<NumericPoint, NumericVector>::Flip(void)
  {
    NumericPoint temp = p0;
    p1 = p0;
    p0 = temp;
    return *this;
  }

  template<class NumericPoint, class NumericVector>
  LineSegment<NumericPoint, NumericVector> LineSegment<NumericPoint, NumericVector>::operator-(void) const
  {
    return LineSegment<NumericPoint, NumericVector>(p1, p0);
  }

  template<class NumericPoint, class NumericVector>
  LineSegment<NumericPoint, NumericVector> LineSegment<NumericPoint, NumericVector>::operator+(const NumericVector& rhs) const
  {
    return LineSegment<NumericPoint, NumericVector>(p0 + rhs, p1 + rhs);
  }

  template<class NumericPoint, class NumericVector>
  LineSegment<NumericPoint, NumericVector> LineSegment<NumericPoint, NumericVector>::operator+(const f32& rhs) const
  {
    NumericVector direction = Direction() * rhs;
    return LineSegment<NumericPoint, NumericVector>(p0 + direction, p1 + direction);
  }

  template<class NumericPoint, class NumericVector>
  LineSegment<NumericPoint, NumericVector> LineSegment<NumericPoint, NumericVector>::operator-(const NumericVector& rhs) const
  {
    return LineSegment<NumericPoint, NumericVector>(p0 - rhs, p1 - rhs);
  }

  template<class NumericPoint, class NumericVector>
  LineSegment<NumericPoint, NumericVector> LineSegment<NumericPoint, NumericVector>::operator-(const f32& rhs) const
  {
    NumericVector direction = Direction() * rhs;
    return LineSegment<NumericPoint, NumericVector>(p0 - direction, p1 - direction);
  }

  template<class NumericPoint, class NumericVector>
  LineSegment<NumericPoint, NumericVector>& LineSegment<NumericPoint, NumericVector>::operator+=(const NumericVector& rhs)
  {
    p0 += rhs;
    p1 += rhs;
    return *this;
  }

  template<class NumericPoint, class NumericVector>
  LineSegment<NumericPoint, NumericVector>& LineSegment<NumericPoint, NumericVector>::operator+=(const f32& rhs)
  {
    NumericVector direction = Direction() * rhs;
    p0 += direction;
    p1 += direction;
    return *this;
  }

  template<class NumericPoint, class NumericVector>
  LineSegment<NumericPoint, NumericVector>& LineSegment<NumericPoint, NumericVector>::operator-=(const NumericVector& rhs)
  {
    p0 -= rhs;
    p1 -= rhs;
    return *this;
  }

  template<class NumericPoint, class NumericVector>
  LineSegment<NumericPoint, NumericVector>& LineSegment<NumericPoint, NumericVector>::operator-=(const f32& rhs)
  {
    NumericVector direction = Direction() * rhs;
    p0 -= direction;
    p1 -= direction;
    return *this;
  }

  template<class NumericPoint, class NumericVector>
  LineSegment<NumericPoint, NumericVector>& LineSegment<NumericPoint, NumericVector>::operator=(const LineSegment<NumericPoint, NumericVector>& rhs)
  {
    p0 = rhs.p0;
    p1 = rhs.p1;
    return *this;
  }

  template<class NumericPoint, class NumericVector>
  bool LineSegment<NumericPoint, NumericVector>::operator==(const LineSegment<NumericPoint, NumericVector>& rhs) const
  {
    return p0 == rhs.p0 && p1 == rhs.p1;
  }

  template<class NumericPoint, class NumericVector>
  bool LineSegment<NumericPoint, NumericVector>::operator!=(const LineSegment<NumericPoint, NumericVector>& rhs) const
  {
    return !(*this == rhs);
  }

  template<class NumericPoint, class NumericVector>
  bool LineSegment<NumericPoint, NumericVector>::IsParallel(const LineSegment<NumericPoint, NumericVector>& rhs) const
  {
    return Direction().IsParallel(rhs.Direction());
  }

  template<class NumericPoint, class NumericVector>
  bool LineSegment<NumericPoint, NumericVector>::IsOrthogonal(const LineSegment<NumericPoint, NumericVector>& rhs) const
  {
    return Direction().IsOrthogonal(rhs.Direction());
  }

  template<class NumericPoint, class NumericVector>
  f32 LineSegment<NumericPoint, NumericVector>::Distance(const NumericPoint& rhs) const
  {
    return Math::Distance(rhs, Projection(rhs, true));
  }

  template<class NumericPoint, class NumericVector>
  NumericPoint LineSegment<NumericPoint, NumericVector>::Projection(const NumericPoint& rhs, bool clamp) const
  {
    const f32 length_squared = (p1 - p0).LengthSquared();
    if(Equal(length_squared, 0.0f))
      return p0;

    const f32 t = clamp ? Clamp<f32>(Dot(rhs - p0, p1 - p0) / length_squared, 0.0f, 1.0f) : Dot(rhs - p0, p1 - p0) / length_squared;
    return p0 + (p1 - p0) * t;
  }
}