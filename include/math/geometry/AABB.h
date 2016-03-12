/*
*  FILE          AABB.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for Axis Aligned Bounding Box structures (2D and 3D).
*/
#pragma once

namespace Math
{
  class AxisAlignedBoundingBox3D
  {
    public:
      AxisAlignedBoundingBox3D(const NumericPoint4<f32>& min_ = NumericPoint4<f32>::ORIGIN, const NumericPoint4<f32>& max_ = NumericPoint4<f32>::ORIGIN);
      AxisAlignedBoundingBox3D(const AxisAlignedBoundingBox3D& rhs);
      explicit AxisAlignedBoundingBox3D(const NumericPoint4<f32>& center_, NumericVector4<f32> extent_);

      FORCEINLINE const NumericPoint4<f32>& Min(void) const;
      FORCEINLINE const NumericPoint4<f32>& Max(void) const;

      FORCEINLINE NumericPoint4<f32> Center(void) const;
      FORCEINLINE f32 Width(void) const;
      FORCEINLINE f32 Height(void) const;
      FORCEINLINE f32 Depth(void) const;

      FORCEINLINE f32 HalfWidth(void) const;
      FORCEINLINE f32 HalfHeight(void) const;
      FORCEINLINE f32 HalfDepth(void) const;

      FORCEINLINE f32 Diagonal(void) const;

      AxisAlignedBoundingBox3D operator+(const NumericVector4<f32>& rhs) const;
      AxisAlignedBoundingBox3D operator-(const NumericVector4<f32>& rhs) const;
      AxisAlignedBoundingBox3D operator*(const Scale& rhs) const;
      AxisAlignedBoundingBox3D operator*(const Matrix& rhs) const;

      AxisAlignedBoundingBox3D& operator+=(const NumericVector4<f32>& rhs);
      AxisAlignedBoundingBox3D& operator-=(const NumericVector4<f32>& rhs);
      AxisAlignedBoundingBox3D& operator*=(const Scale& rhs);
      AxisAlignedBoundingBox3D& operator*=(const Matrix& rhs);

      AxisAlignedBoundingBox3D& operator=(const AxisAlignedBoundingBox3D& rhs);

      bool operator==(const AxisAlignedBoundingBox3D& rhs) const;
      bool operator!=(const AxisAlignedBoundingBox3D& rhs) const;

      bool HasXAxisOverlap(const AxisAlignedBoundingBox3D& rhs, f32 epsilon = EPSILON) const;
      bool HasYAxisOverlap(const AxisAlignedBoundingBox3D& rhs, f32 epsilon = EPSILON) const;
      bool HasZAxisOverlap(const AxisAlignedBoundingBox3D& rhs, f32 epsilon = EPSILON) const;

      bool HasXAxisEncapsulation(const AxisAlignedBoundingBox3D& rhs, f32 epsilon = EPSILON) const;
      bool HasYAxisEncapsulation(const AxisAlignedBoundingBox3D& rhs, f32 epsilon = EPSILON) const;
      bool HasZAxisEncapsulation(const AxisAlignedBoundingBox3D& rhs, f32 epsilon = EPSILON) const;

      bool IsInside(const NumericPoint4<f32>& rhs, f32 epsilon = EPSILON) const;
      bool IsInside(const AxisAlignedBoundingBox3D& rhs, f32 epsilon = EPSILON) const;

      bool Intersects(const AxisAlignedBoundingBox3D& rhs, f32 epsilon = EPSILON) const;
      bool Intersection(const AxisAlignedBoundingBox3D& rhs, AxisAlignedBoundingBox3D& intersection, f32 epsilon = EPSILON) const;

      NumericPoint4<f32> min, max;
  };
  typedef AxisAlignedBoundingBox3D AABB3;



  class AxisAlignedBoundingBox2D
  {
  public:
    AxisAlignedBoundingBox2D(const NumericVector2<f32>& min_ = NumericVector2<f32>::ZERO, const NumericVector2<f32>& max_ = NumericVector2<f32>::ZERO);
    AxisAlignedBoundingBox2D(const AxisAlignedBoundingBox2D& rhs);
    explicit AxisAlignedBoundingBox2D(const NumericVector2<f32>& center_, f32 width_, f32 height_);

    FORCEINLINE const NumericVector2<f32>& Min(void) const;
    FORCEINLINE const NumericVector2<f32>& Max(void) const;

    FORCEINLINE NumericVector2<f32> Center(void) const;
    FORCEINLINE f32 Width(void) const;
    FORCEINLINE f32 Height(void) const;

    FORCEINLINE f32 HalfWidth(void) const;
    FORCEINLINE f32 HalfHeight(void) const;

    FORCEINLINE f32 Diagonal(void) const;

    AxisAlignedBoundingBox2D operator+(const NumericVector2<f32>& rhs) const;
    AxisAlignedBoundingBox2D operator-(const NumericVector2<f32>& rhs) const;
    AxisAlignedBoundingBox2D operator*(const Scale& rhs) const;
    AxisAlignedBoundingBox2D operator*(const Matrix& rhs) const;

    AxisAlignedBoundingBox2D& operator+=(const NumericVector2<f32>& rhs);
    AxisAlignedBoundingBox2D& operator-=(const NumericVector2<f32>& rhs);
    AxisAlignedBoundingBox2D& operator*=(const Scale& rhs);
    AxisAlignedBoundingBox2D& operator*=(const Matrix& rhs);

    AxisAlignedBoundingBox2D& operator=(const AxisAlignedBoundingBox2D& rhs);

    bool operator==(const AxisAlignedBoundingBox2D& rhs) const;
    bool operator!=(const AxisAlignedBoundingBox2D& rhs) const;

    bool HasXAxisOverlap(const AxisAlignedBoundingBox2D& rhs, f32 epsilon = EPSILON) const;
    bool HasYAxisOverlap(const AxisAlignedBoundingBox2D& rhs, f32 epsilon = EPSILON) const;

    bool HasXAxisEncapsulation(const AxisAlignedBoundingBox2D& rhs, f32 epsilon = EPSILON) const;
    bool HasYAxisEncapsulation(const AxisAlignedBoundingBox2D& rhs, f32 epsilon = EPSILON) const;

    bool IsInside(const NumericVector2<f32>& point, f32 epsilon = EPSILON) const;
    bool IsInside(const AxisAlignedBoundingBox2D& box, f32 epsilon = EPSILON) const;

    bool Intersects(const AxisAlignedBoundingBox2D& rhs, f32 epsilon = EPSILON) const;
    bool Intersection(const AxisAlignedBoundingBox2D& rhs, AxisAlignedBoundingBox2D& intersection, f32 epsilon = EPSILON) const;

    NumericVector2<f32> min, max;
  };
  typedef AxisAlignedBoundingBox2D AABB2;
}