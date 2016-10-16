/*
*  FILE          Matrix.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for Matrix class.
*/
#pragma once

#include "Vector.h"

namespace Math
{
  class Quaternion;
  class Scale;

  class TranslationMatrix;
  class OrientationMatrix;
  class ScaleMatrix;

  class Matrix
  {
    public:
      Matrix(void);
      Matrix(f32 m00, f32 m01, f32 m02, f32 m03,
             f32 m10, f32 m11, f32 m12, f32 m13,
             f32 m20, f32 m21, f32 m22, f32 m23,
             f32 m30, f32 m31, f32 m32, f32 m33);
      Matrix(const Matrix& rhs);
      Matrix(f32 pitch, f32 yaw, f32 roll, bool radians);

      Matrix operator+(const Matrix& rhs) const;
      Matrix operator-(const Matrix& rhs) const;
      NumericVector4<f32> operator*(const NumericVector4<f32>& rhs) const;
      Matrix operator*(const Matrix& rhs) const;
      Matrix operator*(f32 scalar) const;
      Matrix operator/(f32 scalar) const;

      Matrix& operator+=(const Matrix& rhs);
      Matrix& operator-=(const Matrix& rhs);
      Matrix& operator*=(f32 scalar);
      Matrix& operator/=(f32 scalar);
      virtual Matrix& operator=(const Matrix& rhs);

      bool operator==(const Matrix& rhs);
      bool operator!=(const Matrix& rhs);

      void SetRow(s32 row, const NumericVector4<f32>& r);
      void SetColumn(s32 column, const NumericVector4<f32>& c);

      NumericVector4<f32> GetRow(s32 row) const;
      NumericVector4<f32> GetColumn(s32 column) const;

      Vector3 GetEulerAngles(bool radians = true) const;

      Matrix GetTranspose(void) const;
      Matrix GetInverse(void) const;
      Matrix GetAdjoint(void) const;

      NumericVector4<f32> GetTranslation(void) const;
      NumericVector4<f32> GetTransposeTranslation(void) const;
      Quaternion GetOrientation(void) const;
      Scale GetScale(void) const;

      TranslationMatrix GetTranslationMatrix(void) const;
      TranslationMatrix GetTransposeTranslationMatrix(void) const;
      OrientationMatrix GetOrientationMatrix(void) const;
      ScaleMatrix GetScaleMatrix(void) const;

      Matrix& Zero(void);
      Matrix& Identity(void);
      Matrix& Transpose(void);
      Matrix& Inverse(void);
      Matrix& Adjoint(void);
      f32 Determinant(void);

      static const Matrix ZERO;
      static const Matrix IDENTITY;

      union
      {
        struct
        {
          f32 m00, m01, m02, m03,
              m10, m11, m12, m13,
              m20, m21, m22, m23,
              m30, m31, m32, m33;
        };
        f32 m[4][4];
        f32 v[16];
      };
  };

  class TranslationMatrix : public Matrix
  {
    public:
      TranslationMatrix(const NumericVector4<f32>& delta, bool transpose = false);

      TranslationMatrix& Inverse(void);

      static Matrix Build(const NumericVector4<f32>& delta);
  };

  class OrientationMatrix : public Matrix
  {
    public:
      OrientationMatrix(const Quaternion& rotation);

      static Matrix Build(const Quaternion& rotation);
  };

  class ScaleMatrix : public Matrix
  {
    public:
      ScaleMatrix(f32 uniform_scale);
      ScaleMatrix(const Scale& scale);

      ScaleMatrix& Inverse(void);

      static Matrix Build(f32 uniform_scale);
      static Matrix Build(const Scale& scale);
  };

  class TransformMatrix : public Matrix
  {
    public:
      TransformMatrix(const NumericVector4<f32>& delta, const Quaternion& rotation, const Scale& scale);
      TransformMatrix(const TranslationMatrix& delta, const OrientationMatrix& rotation, const ScaleMatrix& scale);

      static Matrix Build(const NumericVector4<f32>& delta, const Quaternion& rotation, const Scale& scale);
  };

  class PerspectiveMatrix : public Matrix
  {
    public:
      PerspectiveMatrix(f32 fov, f32 aspect, f32 near, f32 far);

      static Matrix Build(f32 fov, f32 aspect, f32 near, f32 far);
  };

  class OrthographicMatrix : public Matrix
  {
    public:
      OrthographicMatrix(f32 width, f32 height, f32 near, f32 far);

      static Matrix Build(f32 width, f32 height, f32 near, f32 far);
  };

  class ViewMatrix : public Matrix
  {
    public:
      ViewMatrix(const NumericPoint4<f32>& eye, const NumericVector4<f32>& look, const NumericVector4<f32>& up, const NumericVector4<f32>& right);
      ViewMatrix(const NumericPoint4<f32>& eye, const NumericPoint4<f32>& destination, const NumericVector4<f32>& up);

      static Matrix Build(const NumericPoint4<f32>& eye, const NumericVector4<f32>& look, const NumericVector4<f32>& up, const NumericVector4<f32>& right);
      static Matrix Build(const NumericPoint4<f32>& eye, const NumericPoint4<f32>& destination, const NumericVector4<f32>& up);
  };
}