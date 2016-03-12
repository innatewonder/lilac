/*
*  FILE          AABB.cpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for Axis Aligned Bounding Box structures (2D and 3D).
*/
#include "CommonPrecompiled.h"
#include "AABB.h"

namespace Math
{
  AxisAlignedBoundingBox3D::AxisAlignedBoundingBox3D(const NumericPoint4<f32>& min_, const NumericPoint4<f32>& max_)
    : min(min_), max(max_)
  { }

  AxisAlignedBoundingBox3D::AxisAlignedBoundingBox3D(const AxisAlignedBoundingBox3D& rhs)
    : min(rhs.min), max(rhs.max)
  { }

  AxisAlignedBoundingBox3D::AxisAlignedBoundingBox3D(const NumericPoint4<f32>& center_, NumericVector4<f32> extent_)
    : min(center_ - extent_ * 0.5f), max(center_ + extent_ * 0.5f)
  { }

  FORCEINLINE const NumericPoint4<f32>& AxisAlignedBoundingBox3D::Min(void) const
  {
    return min;
  }

  FORCEINLINE const NumericPoint4<f32>& AxisAlignedBoundingBox3D::Max(void) const
  {
    return max;
  }

  FORCEINLINE NumericPoint4<f32> AxisAlignedBoundingBox3D::Center(void) const
  {
    return min + (max - min) * 0.5f;
  }
  
  FORCEINLINE f32 AxisAlignedBoundingBox3D::Width(void) const
  {
    return max.x - min.x;
  }

  FORCEINLINE f32 AxisAlignedBoundingBox3D::Height(void) const
  {
    return max.y - min.y;
  }

  FORCEINLINE f32 AxisAlignedBoundingBox3D::Depth(void) const
  {
    return max.z - min.z;
  }

  FORCEINLINE f32 AxisAlignedBoundingBox3D::HalfWidth(void) const
  {
    return Width() * 0.5f;
  }

  FORCEINLINE f32 AxisAlignedBoundingBox3D::HalfHeight(void) const
  {
    return Height() * 0.5f;
  }

  FORCEINLINE f32 AxisAlignedBoundingBox3D::HalfDepth(void) const
  {
    return Depth() * 0.5f;
  }

  FORCEINLINE f32 AxisAlignedBoundingBox3D::Diagonal(void) const
  {
    return (max - min).Length();
  }

  AxisAlignedBoundingBox3D AxisAlignedBoundingBox3D::operator+(const NumericVector4<f32>& rhs) const
  {
    return AxisAlignedBoundingBox3D(min + rhs, max + rhs);
  }

  AxisAlignedBoundingBox3D AxisAlignedBoundingBox3D::operator-(const NumericVector4<f32>& rhs) const
  {
    return AxisAlignedBoundingBox3D(min - rhs, max - rhs);
  }

  AxisAlignedBoundingBox3D AxisAlignedBoundingBox3D::operator*(const Scale& rhs) const
  {
    NumericPoint4<f32> center = Center();
    NumericVector4<f32> extent(HalfWidth() * rhs.scale.x, HalfHeight() * rhs.scale.y, HalfDepth() * rhs.scale.z);
    return AxisAlignedBoundingBox3D(center - extent, center + extent);
  }

  AxisAlignedBoundingBox3D AxisAlignedBoundingBox3D::operator*(const Matrix& rhs) const
  {
    return *this * rhs.GetScale() + rhs.GetTransposeTranslation();
  }

  AxisAlignedBoundingBox3D& AxisAlignedBoundingBox3D::operator+=(const NumericVector4<f32>& rhs)
  {
    min += rhs;
    max += rhs;
    return *this;
  }

  AxisAlignedBoundingBox3D& AxisAlignedBoundingBox3D::operator-=(const NumericVector4<f32>& rhs)
  {
    min -= rhs;
    max -= rhs;
    return *this;
  }

  AxisAlignedBoundingBox3D& AxisAlignedBoundingBox3D::operator*=(const Scale& rhs)
  {
    NumericPoint4<f32> center = Center();
    NumericVector4<f32> extent(HalfWidth() * rhs.scale.x, HalfHeight() * rhs.scale.y, HalfDepth() * rhs.scale.z);
    min = center - extent;
    max = center + extent;
    return *this;
  }

  AxisAlignedBoundingBox3D& AxisAlignedBoundingBox3D::operator*=(const Matrix& rhs)
  {
    return (*this *= rhs.GetScale()) += rhs.GetTransposeTranslation();
  }

  AxisAlignedBoundingBox3D& AxisAlignedBoundingBox3D::operator=(const AxisAlignedBoundingBox3D& rhs)
  {
    min = rhs.min;
    max = rhs.max;
    return *this;
  }

  bool AxisAlignedBoundingBox3D::operator==(const AxisAlignedBoundingBox3D& rhs) const
  {
    return min == rhs.min && max == rhs.max;
  }

  bool AxisAlignedBoundingBox3D::operator!=(const AxisAlignedBoundingBox3D& rhs) const
  {
    return !(*this == rhs);
  }

  bool AxisAlignedBoundingBox3D::HasXAxisOverlap(const AxisAlignedBoundingBox3D& rhs, f32 epsilon) const
  {
    return rhs.min.x <= max.x + epsilon && min.x - epsilon <= rhs.max.x;
  }

  bool AxisAlignedBoundingBox3D::HasYAxisOverlap(const AxisAlignedBoundingBox3D& rhs, f32 epsilon) const
  {
    return rhs.min.y <= max.y + epsilon && min.y - epsilon <= rhs.max.y;
  }

  bool AxisAlignedBoundingBox3D::HasZAxisOverlap(const AxisAlignedBoundingBox3D& rhs, f32 epsilon) const
  {
    return rhs.min.z <= max.z + epsilon && min.z - epsilon <= rhs.max.z;
  }

  bool AxisAlignedBoundingBox3D::HasXAxisEncapsulation(const AxisAlignedBoundingBox3D& rhs, f32 epsilon) const
  {
    return rhs.max.x <= max.x + epsilon && rhs.min.x >= min.x - epsilon;
  }

  bool AxisAlignedBoundingBox3D::HasYAxisEncapsulation(const AxisAlignedBoundingBox3D& rhs, f32 epsilon) const
  {
    return rhs.max.y <= max.y + epsilon && rhs.min.y >= min.y - epsilon;
  }

  bool AxisAlignedBoundingBox3D::HasZAxisEncapsulation(const AxisAlignedBoundingBox3D& rhs, f32 epsilon) const
  {
    return rhs.max.z <= max.z + epsilon && rhs.min.z >= min.z - epsilon;
  }

  bool AxisAlignedBoundingBox3D::IsInside(const NumericPoint4<f32>& rhs, f32 epsilon) const
  {
    return rhs.x >= min.x + epsilon && rhs.x <= max.x - epsilon &&
           rhs.y >= min.y + epsilon && rhs.y <= max.y - epsilon &&
           rhs.z >= min.z + epsilon && rhs.z <= max.z - epsilon;
  }

  bool AxisAlignedBoundingBox3D::IsInside(const AxisAlignedBoundingBox3D& rhs, f32 epsilon) const
  {
    return HasXAxisEncapsulation(rhs, epsilon) && HasYAxisEncapsulation(rhs, epsilon) && HasZAxisEncapsulation(rhs, epsilon);
  }

  bool AxisAlignedBoundingBox3D::Intersects(const AxisAlignedBoundingBox3D& rhs, f32 epsilon) const
  {
    return HasXAxisOverlap(rhs, epsilon) && HasYAxisOverlap(rhs, epsilon) && HasZAxisOverlap(rhs, epsilon);
  }

  bool AxisAlignedBoundingBox3D::Intersection(const AxisAlignedBoundingBox3D& rhs, AxisAlignedBoundingBox3D& intersection, f32 epsilon) const
  {
    if(!Intersects(rhs, epsilon))
      return false;

    intersection.max.x = (max.x <= rhs.max.x ? max.x : rhs.max.x);
    intersection.max.y = (max.y <= rhs.max.y ? max.y : rhs.max.y);
    intersection.max.z = (max.z <= rhs.max.z ? max.z : rhs.max.z);
    intersection.min.x = (min.x <= rhs.min.x ? rhs.min.x : min.x);
    intersection.min.y = (min.y <= rhs.min.y ? rhs.min.y : min.y);
    intersection.min.z = (min.z <= rhs.min.z ? rhs.min.z : min.z);
    return true;
  }




  AxisAlignedBoundingBox2D::AxisAlignedBoundingBox2D(const NumericVector2<f32>& min_, const NumericVector2<f32>& max_)
    : min(min_), max(max_)
  { }

  AxisAlignedBoundingBox2D::AxisAlignedBoundingBox2D(const AxisAlignedBoundingBox2D& rhs)
    : min(rhs.min), max(rhs.max)
  { }
  
  AxisAlignedBoundingBox2D::AxisAlignedBoundingBox2D(const NumericVector2<f32>& center_, f32 width_, f32 height_)
    : min(center_ - NumericVector2<f32>(width_, height_) * 0.5f), max(center_ + NumericVector2<f32>(width_, height_) * 0.5f)
  { }

  FORCEINLINE const NumericVector2<f32>& AxisAlignedBoundingBox2D::Min(void) const
  {
    return min;
  }

  FORCEINLINE const NumericVector2<f32>& AxisAlignedBoundingBox2D::Max(void) const
  {
    return max;
  }

  FORCEINLINE NumericVector2<f32> AxisAlignedBoundingBox2D::Center(void) const
  {
    return min + (max - min) * 0.5f;
  }

  FORCEINLINE f32 AxisAlignedBoundingBox2D::Width(void) const
  {
    return max.x - min.x;
  }

  FORCEINLINE f32 AxisAlignedBoundingBox2D::Height(void) const
  {
    return max.y - min.y;
  }

  FORCEINLINE f32 AxisAlignedBoundingBox2D::HalfWidth(void) const
  {
    return Width() * 0.5f;
  }

  FORCEINLINE f32 AxisAlignedBoundingBox2D::HalfHeight(void) const
  {
    return Height() * 0.5f;
  }

  FORCEINLINE f32 AxisAlignedBoundingBox2D::Diagonal(void) const
  {
    return (max - min).Length();
  }

  AxisAlignedBoundingBox2D AxisAlignedBoundingBox2D::operator+(const NumericVector2<f32>& rhs) const
  {
    return AxisAlignedBoundingBox2D(min + rhs, max + rhs);
  }

  AxisAlignedBoundingBox2D AxisAlignedBoundingBox2D::operator-(const NumericVector2<f32>& rhs) const
  {
    return AxisAlignedBoundingBox2D(min - rhs, max - rhs);
  }

  AxisAlignedBoundingBox2D AxisAlignedBoundingBox2D::operator*(const Scale& rhs) const
  {
    NumericVector2<f32> center = Center();
    NumericVector2<f32> extent(HalfWidth() * rhs.scale.x, HalfHeight() * rhs.scale.y);
    return AxisAlignedBoundingBox2D(center - extent, center + extent);
  }

  AxisAlignedBoundingBox2D AxisAlignedBoundingBox2D::operator*(const Matrix& rhs) const
  {
    return *this * rhs.GetScale() + rhs.GetTransposeTranslation().xy;
  }

  AxisAlignedBoundingBox2D& AxisAlignedBoundingBox2D::operator+=(const NumericVector2<f32>& rhs)
  {
    min += rhs;
    max += rhs;
    return *this;
  }

  AxisAlignedBoundingBox2D& AxisAlignedBoundingBox2D::operator-=(const NumericVector2<f32>& rhs)
  {
    min -= rhs;
    max -= rhs;
    return *this;
  }

  AxisAlignedBoundingBox2D& AxisAlignedBoundingBox2D::operator*=(const Scale& rhs)
  {
    NumericVector2<f32> center = Center();
    NumericVector2<f32> extent(HalfWidth() * rhs.scale.x, HalfHeight() * rhs.scale.y);
    min = center - extent;
    max = center + extent;
    return *this;
  }

  AxisAlignedBoundingBox2D& AxisAlignedBoundingBox2D::operator*=(const Matrix& rhs)
  {
    return (*this *= rhs.GetScale()) += rhs.GetTransposeTranslation().xy;
  }

  AxisAlignedBoundingBox2D& AxisAlignedBoundingBox2D::operator=(const AxisAlignedBoundingBox2D& rhs)
  {
    min = rhs.min;
    max = rhs.max;
    return *this;
  }

  bool AxisAlignedBoundingBox2D::operator==(const AxisAlignedBoundingBox2D& rhs) const
  {
    return min == rhs.min && max == rhs.max;
  }

  bool AxisAlignedBoundingBox2D::operator!=(const AxisAlignedBoundingBox2D& rhs) const
  {
    return !(*this == rhs);
  }

  bool AxisAlignedBoundingBox2D::HasXAxisOverlap(const AxisAlignedBoundingBox2D& rhs, f32 epsilon) const
  {
    return rhs.min.x <= max.x + epsilon && min.x - epsilon <= rhs.max.x;
  }

  bool AxisAlignedBoundingBox2D::HasYAxisOverlap(const AxisAlignedBoundingBox2D& rhs, f32 epsilon) const
  {
    return rhs.min.y <= max.y + epsilon && min.y - epsilon <= rhs.max.y;
  }

  bool AxisAlignedBoundingBox2D::HasXAxisEncapsulation(const AxisAlignedBoundingBox2D& rhs, f32 epsilon) const
  {
    return rhs.max.x <= max.x + epsilon && rhs.min.x >= min.x - epsilon;
  }

  bool AxisAlignedBoundingBox2D::HasYAxisEncapsulation(const AxisAlignedBoundingBox2D& rhs, f32 epsilon) const
  {
    return rhs.max.y <= max.y + epsilon && rhs.min.y >= min.y - epsilon;
  }

  bool AxisAlignedBoundingBox2D::IsInside(const NumericVector2<f32>& rhs, f32 epsilon) const
  {
    return rhs.x >= min.x + epsilon && rhs.x <= max.x - epsilon &&
           rhs.y >= min.y + epsilon && rhs.y <= max.y - epsilon;
  }

  bool AxisAlignedBoundingBox2D::IsInside(const AxisAlignedBoundingBox2D& rhs, f32 epsilon) const
  {
    return HasXAxisEncapsulation(rhs, epsilon) && HasYAxisEncapsulation(rhs, epsilon);
  }

  bool AxisAlignedBoundingBox2D::Intersects(const AxisAlignedBoundingBox2D& rhs, f32 epsilon) const
  {
    return HasXAxisOverlap(rhs, epsilon) && HasYAxisOverlap(rhs, epsilon);
  }

  bool AxisAlignedBoundingBox2D::Intersection(const AxisAlignedBoundingBox2D& rhs, AxisAlignedBoundingBox2D& intersection, f32 epsilon) const
  {
    if(!Intersects(rhs, epsilon))
      return false;

    intersection.max.x = (max.x <= rhs.max.x ? max.x : rhs.max.x);
    intersection.max.y = (max.y <= rhs.max.y ? max.y : rhs.max.y);
    intersection.min.x = (min.x <= rhs.min.x ? rhs.min.x : min.x);
    intersection.min.y = (min.y <= rhs.min.y ? rhs.min.y : min.y);
    return true;
  }
}