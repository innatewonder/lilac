/*
*  FILE          Quaternion.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for the Quaternion orientation class
*/
#pragma once

/* Macro for Safe Slerp (No Inversion) */
#define SLERP(p, q, t) Math::Quaternion::SlerpNoInversion(p, q, t)

namespace Math
{
  /* User Defined Constants */
  const f32 SLERP_EPSILON = 0.00001f;

  /* Declaration of Template Storage Structures */
  typedef std::vector<Quaternion> Quaternions;
  typedef Quaternions::iterator   QuaternionIter;

  /**********************************************************************************
  PURPOSE:
  Quaternion class to represent rotations in 3D space without gimbal-lock issues.
  NOTES:
  ASSUMPTIONS:
  **********************************************************************************/
  class Quaternion
  {
    public:
      Quaternion(void);
      Quaternion(f32 ww, f32 xx, f32 yy, f32 zz);
      Quaternion(f32 x, f32 y, f32 z);
      Quaternion(const Matrix &rotation);
      Quaternion(const NumericVector4<f32> &axis, f32 angle);

      f32 Length(void) const;
      f32 SquaredLength(void) const;

      Quaternion QuaternionProduct(const Quaternion &rhs) const;
      f32 DotProduct(const Quaternion &rhs) const;

      Quaternion& Normalize(void);
      Quaternion& NormalizeQuick(void);

      Quaternion Inverse(void) const;
      Quaternion InverseQuick(void) const;

      f32 GetScalar() const;
      Vector3 GetVector() const;
      Quaternion Conjugate(void) const;
      Quaternion Exp(void) const;
      Quaternion Log(void) const;

      void AddScaledVector(const NumericVector4<f32> &vec, f32 scale);

      f32 operator[](u32 index) const;
      f32& operator[](u32 index);

      Quaternion& operator=(const Quaternion &rhs);
      bool operator==(const Quaternion &rhs) const;
      bool operator!=(const Quaternion &rhs) const;

      Quaternion operator+(const Quaternion &rhs) const;
      Quaternion operator-(const Quaternion &rhs) const;
      Quaternion operator*(const Quaternion &rhs) const;
      NumericVector4<f32> operator*(const NumericVector4<f32> &vec) const;
      Quaternion operator*(f32 scalar) const;
      Quaternion operator/(f32 scalar) const;
      Quaternion operator-(void) const;

      Quaternion& operator+=(const Quaternion &rhs);
      Quaternion& operator-=(const Quaternion &rhs);
      Quaternion& operator*=(f32 scalar);
      Quaternion& operator/=(f32 scalar);

      friend std::ostream& operator<<(std::ostream& os, const Quaternion& obj);
      friend std::istream& operator>>(std::istream& is, Quaternion& obj);

      Quaternion& FromEulerAngles(f32 pitch, f32 yaw, f32 roll, bool radians = true);
      Vector3 GetEulerAngles(bool asRadians = true) const;

      void FromRotationMatrix(const Matrix &rotation);
      void ToRotationMatrix(Matrix &rotation) const;

      void FromAxisAngle(const NumericVector4<f32> &axis, f32 angle);
      void ToAxisAngle(NumericVector4<f32> &axis, f32 &angle) const;
      NumericVector4<f32> Rotate(const NumericVector4<f32> &vec) const;
      friend Quaternion operator*(f32 scalar, const Quaternion &rhs);

      static Quaternion VectorToVector(const NumericVector4<f32> &vec1, const NumericVector4<f32> &vec2);

      static Quaternion Bisect(const Quaternion& p, const Quaternion& q);
      static Quaternion Double(const Quaternion& p, const Quaternion& q);

      static Quaternion Lerp(const Quaternion& p, const Quaternion& q, f32 t);
      static Quaternion Slerp(const Quaternion& p, const Quaternion& q, f32 t);
      static Quaternion SlerpNoInversion(const Quaternion& p, const Quaternion& q, f32 t);

      static const Quaternion ZERO;
      static const Quaternion IDENTITY;

    public:
      union
      {
        struct { f32 w, x, y, z; };
        f32 v[4];
      };
  };
}