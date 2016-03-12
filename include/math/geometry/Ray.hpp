/*
 *  FILE          Ray.hpp
 *  AUTHOR        Brendon Clifford
 *  DESCRIPTION
 *    Implementation for Ray structures.
 */

namespace Math
{
  template<class NumericPoint, class NumericVector> const Ray<NumericPoint, NumericVector> Ray<NumericPoint, NumericVector>::ZERO(NumericPoint::ORIGIN, NumericVector::ZERO);
  template<class NumericPoint, class NumericVector> const Ray<NumericPoint, NumericVector> Ray<NumericPoint, NumericVector>::X_AXIS(NumericPoint::ORIGIN, NumericVector::UNIT_X);
  template<class NumericPoint, class NumericVector> const Ray<NumericPoint, NumericVector> Ray<NumericPoint, NumericVector>::Y_AXIS(NumericPoint::ORIGIN, NumericVector::UNIT_Y);
  template<class NumericPoint, class NumericVector> const Ray<NumericPoint, NumericVector> Ray<NumericPoint, NumericVector>::Z_AXIS(NumericPoint::ORIGIN, NumericVector::UNIT_Z);

  template<class NumericPoint, class NumericVector>
  Ray<NumericPoint, NumericVector>::Ray(const NumericPoint& origin_, const NumericVector& direction_)
    : origin(origin_), direction(direction_)
  { }

  template<class NumericPoint, class NumericVector>
  Ray<NumericPoint, NumericVector>::Ray(const NumericPoint& origin_, const NumericPoint& destination_)
    : origin(origin_), direction((destination_ - origin_).Normalize())
  { }

  template<class NumericPoint, class NumericVector>
  Ray<NumericPoint, NumericVector>::Ray(const Ray<NumericPoint, NumericVector>& rhs)
    : origin(rhs.origin), direction(rhs.direction)
  { }

  template<class NumericPoint, class NumericVector>
  Ray<NumericPoint, NumericVector>::Ray(const LineSegment<NumericPoint, NumericVector>& line_)
    : origin(line_.Head()), direction(line_.Direction())
  { }

  template<class NumericPoint, class NumericVector>
  FORCEINLINE const NumericPoint& Ray<NumericPoint, NumericVector>::Origin(void) const
  {
    return origin;
  }

  template<class NumericPoint, class NumericVector>
  FORCEINLINE const NumericVector& Ray<NumericPoint, NumericVector>::Direction(void) const
  {
    return direction;
  }

  template<class NumericPoint, class NumericVector>
  Ray<NumericPoint, NumericVector>& Ray<NumericPoint, NumericVector>::Flip(void) const
  {
    direction = -direction;
    return *this;
  }

  template<class NumericPoint, class NumericVector>
  Ray<NumericPoint, NumericVector> Ray<NumericPoint, NumericVector>::operator-(void) const
  {
    return Ray<NumericPoint, NumericVector>(origin, -direction);
  }

  template<class NumericPoint, class NumericVector>
  Ray<NumericPoint, NumericVector> Ray<NumericPoint, NumericVector>::operator+(const NumericVector& rhs) const
  {
    return Ray<NumericPoint, NumericVector>(origin + rhs, direction);
  }

  template<class NumericPoint, class NumericVector>
  Ray<NumericPoint, NumericVector> Ray<NumericPoint, NumericVector>::operator-(const NumericVector& rhs) const
  {
    return Ray<NumericPoint, NumericVector>(origin - rhs, direction);
  }

  template<class NumericPoint, class NumericVector>
  Ray<NumericPoint, NumericVector> Ray<NumericPoint, NumericVector>::operator*(const Quaternion& rhs) const
  {
    return Ray<NumericPoint, NumericVector>(origin, rhs * direction);
  }

  template<class NumericPoint, class NumericVector>
  Ray<NumericPoint, NumericVector>& Ray<NumericPoint, NumericVector>::operator+=(const NumericVector& rhs)
  {
    origin += rhs;
    return *this;
  }

  template<class NumericPoint, class NumericVector>
  Ray<NumericPoint, NumericVector>& Ray<NumericPoint, NumericVector>::operator-=(const NumericVector& rhs)
  {
    origin -= rhs;
    return *this;
  }

  template<class NumericPoint, class NumericVector>
  Ray<NumericPoint, NumericVector>& Ray<NumericPoint, NumericVector>::operator*=(const Quaternion& rhs)
  {
    direction = rhs * direction;
    return *this;
  }

  template<class NumericPoint, class NumericVector>
  Ray<NumericPoint, NumericVector>& Ray<NumericPoint, NumericVector>::operator=(const Ray& rhs)
  {
    origin = rhs.origin;
    direction = rhs.direction;
    return *this;
  }

  template<class NumericPoint, class NumericVector>
  bool Ray<NumericPoint, NumericVector>::operator==(const Ray<NumericPoint, NumericVector>& rhs) const
  {
    return origin == rhs.origin && direction == rhs.direction;
  }

  template<class NumericPoint, class NumericVector>
  bool Ray<NumericPoint, NumericVector>::operator!=(const Ray<NumericPoint, NumericVector>& rhs) const
  {
    return !(*this == rhs);
  }

  template<class NumericPoint, class NumericVector>
  bool Ray<NumericPoint, NumericVector>::IsParallel(const Ray<NumericPoint, NumericVector>& rhs) const
  {
    return direction.IsParallel(rhs.direction);
  }

  template<class NumericPoint, class NumericVector>
  bool Ray<NumericPoint, NumericVector>::IsOrthogonal(const Ray<NumericPoint, NumericVector>& rhs) const
  {
    return direction.IsOrthogonal(rhs.direction);
  }

  template<class NumericPoint, class NumericVector>
  f32 Ray<NumericPoint, NumericVector>::Distance(const NumericPoint& rhs) const
  {
    return Math::Distance(rhs, Projection(rhs, true));
  }

  template<class NumericPoint, class NumericVector>
  NumericPoint Ray<NumericPoint, NumericVector>::Projection(const NumericPoint& rhs) const
  {
    const f32 length_squared = direction.LengthSquared();
    if(Equal(length_squared, 0.0f))
      return origin;

    return origin + direction * (Dot(rhs - origin, direction) / length_squared);
  }

  template<class NumericPoint, class NumericVector>
  LineSegment<NumericPoint, NumericVector> Ray<NumericPoint, NumericVector>::Segment(f32 extent) const
  {
    return LineSegment<NumericPoint, NumericVector>(origin, origin + direction * extent);
  }
}