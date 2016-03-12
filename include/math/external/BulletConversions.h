/*
 *  FILE          BulletConversions.h
 *  AUTHOR        Brendon Clifford
 *  DESCRIPTION
 *    Includes conversion functions to interface between bullet math and engine math.
 */
#pragma once

#include "BulletIncludes.h"

namespace Math
{
  namespace Bullet
  {
    // -- Bullet Physics Math Library -> Mythril Numeric Math Library Conversions --  
    FORCEINLINE NumericVector3<f32> Convert(const btVector3& v)
    {
      return NumericVector3<f32>(v.x(), v.y(), v.z());
    }

    FORCEINLINE NumericVector4<f32> Convert(const btVector4& v)
    {
      return NumericVector4<f32>(v.x(), v.y(), v.z(), v.w());
    }

    FORCEINLINE Quaternion Convert(const btQuaternion& q)
    {
      return Quaternion(q.w(), q.x(), q.y(), q.z());
    }

    FORCEINLINE Matrix Convert(const btMatrix3x3& m)
    {
      return Matrix(m.getRow(0).x(), m.getRow(0).y(), m.getRow(0).z(), 0.0f,
                    m.getRow(1).x(), m.getRow(1).y(), m.getRow(1).z(), 0.0f,
                    m.getRow(2).x(), m.getRow(2).y(), m.getRow(2).z(), 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
    }

    FORCEINLINE Matrix Convert(const btTransform& t)
    {
      return TransformMatrix::Build(NumericVector4<f32>(Convert(t.getOrigin())), Convert(t.getRotation()), NumericVector4<f32>::ONE);
    }



    // -- Mythril Numeric Math Library -> Bullet Physics Math Library Conversions --
    FORCEINLINE btVector3 Convert(const NumericVector3<f32>& v)
    {
      return btVector3(v.x, v.y, v.z);
    }

    FORCEINLINE btVector4 Convert(const NumericVector4<f32>& v)
    {
      return btVector4(v.x, v.y, v.z, v.w);
    }

    FORCEINLINE btQuaternion Convert(const Quaternion& q)
    {
      return btQuaternion(q.x, q.y, q.z, q.w);
    }

    FORCEINLINE btMatrix3x3 Convert(const Matrix& m)
    {
      assert(m.GetScale().GetVector() == NumericVector4<f32>::ONE); // Bullet matrices are assumed uniformally scaled at one.
      return btMatrix3x3(m.m00, m.m01, m.m02,
                         m.m10, m.m11, m.m12,
                         m.m20, m.m21, m.m22);
    }

    FORCEINLINE btTransform Convert(const NumericVector3<f32>& v, const Quaternion& q)
    {
      return btTransform(Convert(q), Convert(v));
    }
  }
}
