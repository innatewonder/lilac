/*
*  FILE          Matrix.cpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for Matrix structure.
*/
#include "CommonPrecompiled.h"
#include "Matrix.h"

namespace Math
{
  const Matrix Matrix::ZERO(0.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 0.0f);

  const Matrix Matrix::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 1.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 1.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 1.0f);

  Matrix::Matrix(void)
  { }

  Matrix::Matrix(f32 m00_, f32 m01_, f32 m02_, f32 m03_,
                 f32 m10_, f32 m11_, f32 m12_, f32 m13_,
                 f32 m20_, f32 m21_, f32 m22_, f32 m23_,
                 f32 m30_, f32 m31_, f32 m32_, f32 m33_)
    : m00(m00_), m01(m01_), m02(m02_), m03(m03_),
      m10(m10_), m11(m11_), m12(m12_), m13(m13_),
      m20(m20_), m21(m21_), m22(m22_), m23(m23_),
      m30(m30_), m31(m31_), m32(m32_), m33(m33_)
  { }

  Matrix::Matrix(const Matrix& rhs)
    : m00(rhs.m00), m01(rhs.m01), m02(rhs.m02), m03(rhs.m03),
      m10(rhs.m10), m11(rhs.m11), m12(rhs.m12), m13(rhs.m13),
      m20(rhs.m20), m21(rhs.m21), m22(rhs.m22), m23(rhs.m23),
      m30(rhs.m30), m31(rhs.m31), m32(rhs.m32), m33(rhs.m33)
  { }

  Matrix::Matrix(f32 pitch, f32 yaw, f32 roll, bool radians)
  {
    f32 sinYaw, cosYaw, sinPitch, cosPitch, sinRoll, cosRoll;

    if(radians)
    {
      GetSinCos(yaw, sinYaw, cosYaw);
      GetSinCos(pitch, sinPitch, cosPitch);
      GetSinCos(roll, sinRoll, cosRoll);
    }
    else
    {
      GetSinCos(yaw * DEG_TO_RAD, sinYaw, cosYaw);
      GetSinCos(pitch * DEG_TO_RAD, sinPitch, cosPitch);
      GetSinCos(roll * DEG_TO_RAD, sinRoll, cosRoll);
    }

    m00 = cosYaw * cosRoll;
    m01 = sinPitch * sinYaw * cosRoll - cosPitch * sinRoll;
    m02 = cosPitch * sinYaw * cosRoll + sinPitch * sinRoll;

    m10 = cosYaw * sinRoll;
    m11 = sinPitch * sinYaw * sinRoll + cosPitch * cosRoll;
    m12 = cosPitch * sinYaw * sinRoll - sinPitch * cosRoll;

    m20 = -sinYaw;
    m21 = sinPitch * cosYaw;
    m22 = cosPitch * cosYaw;
    m33 = 1.0f;
  }

  Matrix Matrix::operator+(const Matrix& rhs) const
  {
    return Matrix(m00 + rhs.m00, m01 + rhs.m01, m02 + rhs.m02, m03 + rhs.m03,
                  m10 + rhs.m10, m11 + rhs.m11, m12 + rhs.m12, m13 + rhs.m13,
                  m20 + rhs.m20, m21 + rhs.m21, m22 + rhs.m22, m23 + rhs.m23,
                  m30 + rhs.m30, m31 + rhs.m31, m32 + rhs.m32, m33 + rhs.m33);
  }

  Matrix Matrix::operator-(const Matrix& rhs) const
  {
    return Matrix(m00 - rhs.m00, m01 - rhs.m01, m02 - rhs.m02, m03 - rhs.m03,
                  m10 - rhs.m10, m11 - rhs.m11, m12 - rhs.m12, m13 - rhs.m13,
                  m20 - rhs.m20, m21 - rhs.m21, m22 - rhs.m22, m23 - rhs.m23,
                  m30 - rhs.m30, m31 - rhs.m31, m32 - rhs.m32, m33 - rhs.m33);
  }

  NumericVector4<f32> Matrix::operator*(const NumericVector4<f32>& rhs) const
  {
    return NumericVector4<f32>(rhs.x * m00 + rhs.y * m01 + rhs.z * m02 + rhs.w * m03,
                               rhs.x * m10 + rhs.y * m11 + rhs.z * m12 + rhs.w * m13,
                               rhs.x * m20 + rhs.y * m21 + rhs.z * m22 + rhs.w * m23,
                               rhs.x * m30 + rhs.y * m31 + rhs.z * m32 + rhs.w * m33);
  }

  Matrix Matrix::operator*(const Matrix& rhs) const
  {
    return Matrix(m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20 + m03 * rhs.m30,
                  m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21 + m03 * rhs.m31,
                  m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22 + m03 * rhs.m32,
                  m00 * rhs.m03 + m01 * rhs.m13 + m02 * rhs.m23 + m03 * rhs.m33,
                  m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20 + m13 * rhs.m30,
                  m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31,
                  m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32,
                  m10 * rhs.m03 + m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33,
                  m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20 + m23 * rhs.m30,
                  m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31,
                  m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32,
                  m20 * rhs.m03 + m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33,
                  m30 * rhs.m00 + m31 * rhs.m10 + m32 * rhs.m20 + m33 * rhs.m30,
                  m30 * rhs.m01 + m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31,
                  m30 * rhs.m02 + m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32,
                  m30 * rhs.m03 + m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33);
  }

  Matrix Matrix::operator*(f32 scalar) const
  {
    return Matrix(m00 * scalar, m01 * scalar, m02 * scalar, m03 * scalar,
                  m10 * scalar, m11 * scalar, m12 * scalar, m13 * scalar,
                  m20 * scalar, m21 * scalar, m22 * scalar, m23 * scalar,
                  m30 * scalar, m31 * scalar, m32 * scalar, m33 * scalar);
  }

  Matrix Matrix::operator/(f32 scalar) const
  {
    f32 inverse_scalar = 1.0f / scalar;
    return Matrix(m00 * inverse_scalar, m01 * inverse_scalar, m02 * inverse_scalar, m03 * inverse_scalar,
                  m10 * inverse_scalar, m11 * inverse_scalar, m12 * inverse_scalar, m13 * inverse_scalar,
                  m20 * inverse_scalar, m21 * inverse_scalar, m22 * inverse_scalar, m23 * inverse_scalar,
                  m30 * inverse_scalar, m31 * inverse_scalar, m32 * inverse_scalar, m33 * inverse_scalar);
  }

  Matrix& Matrix::operator+=(const Matrix& rhs)
  {
    m00 += rhs.m00; m01 += rhs.m01; m02 += rhs.m02; m03 += rhs.m03;
    m10 += rhs.m10; m11 += rhs.m11; m12 += rhs.m12; m13 += rhs.m13;
    m20 += rhs.m20; m21 += rhs.m21; m22 += rhs.m22; m23 += rhs.m23;
    m30 += rhs.m30; m31 += rhs.m31; m32 += rhs.m32; m33 += rhs.m33;
    return *this;
  }

  Matrix& Matrix::operator-=(const Matrix& rhs)
  {
    m00 -= rhs.m00; m01 -= rhs.m01; m02 -= rhs.m02; m03 -= rhs.m03;
    m10 -= rhs.m10; m11 -= rhs.m11; m12 -= rhs.m12; m13 -= rhs.m13;
    m20 -= rhs.m20; m21 -= rhs.m21; m22 -= rhs.m22; m23 -= rhs.m23;
    m30 -= rhs.m30; m31 -= rhs.m31; m32 -= rhs.m32; m33 -= rhs.m33;
    return *this;
  }

  Matrix& Matrix::operator*=(f32 scalar)
  {
    m00 *= scalar; m01 *= scalar; m02 *= scalar; m03 *= scalar;
    m10 *= scalar; m11 *= scalar; m12 *= scalar; m13 *= scalar;
    m20 *= scalar; m21 *= scalar; m22 *= scalar; m23 *= scalar;
    m30 *= scalar; m31 *= scalar; m32 *= scalar; m33 *= scalar;
    return *this;
  }

  Matrix& Matrix::operator/=(f32 scalar)
  {
    f32 inverse_scalar = 1.0f / scalar;
    m00 *= inverse_scalar; m01 *= inverse_scalar; m02 *= inverse_scalar; m03 *= inverse_scalar;
    m10 *= inverse_scalar; m11 *= inverse_scalar; m12 *= inverse_scalar; m13 *= inverse_scalar;
    m20 *= inverse_scalar; m21 *= inverse_scalar; m22 *= inverse_scalar; m23 *= inverse_scalar;
    m30 *= inverse_scalar; m31 *= inverse_scalar; m32 *= inverse_scalar; m33 *= inverse_scalar;
    return *this;
  }

  bool Matrix::operator==(const Matrix& rhs)
  {
    return Equal(m00, rhs.m00) && Equal(m01, rhs.m01) && Equal(m02, rhs.m02) && Equal(m03, rhs.m03) &&
           Equal(m10, rhs.m10) && Equal(m11, rhs.m11) && Equal(m12, rhs.m12) && Equal(m13, rhs.m13) &&
           Equal(m20, rhs.m20) && Equal(m21, rhs.m21) && Equal(m22, rhs.m22) && Equal(m23, rhs.m23) &&
           Equal(m30, rhs.m30) && Equal(m31, rhs.m31) && Equal(m32, rhs.m32) && Equal(m33, rhs.m33);
  }

  Matrix& Matrix::operator=(const Matrix& rhs)
  {
    m00 = rhs.m00; m01 = rhs.m01; m02 = rhs.m02; m03 = rhs.m03;
    m10 = rhs.m10; m11 = rhs.m11; m12 = rhs.m12; m13 = rhs.m13;
    m20 = rhs.m20; m21 = rhs.m21; m22 = rhs.m22; m23 = rhs.m23;
    m30 = rhs.m30; m31 = rhs.m31; m32 = rhs.m32; m33 = rhs.m33;
    return *this;
  }

  bool Matrix::operator!=(const Matrix& rhs)
  {
    return !(*this == rhs);
  }

  void Matrix::SetRow(s32 row, const NumericVector4<f32>& r)
  {
    m[row][0] = r.x;
    m[row][1] = r.y;
    m[row][2] = r.z;
    m[row][3] = r.w;
  }

  void Matrix::SetColumn(s32 column, const NumericVector4<f32>& c)
  {
    m[0][column] = c.x;
    m[1][column] = c.y;
    m[2][column] = c.z;
    m[3][column] = c.w;
  }

  NumericVector4<f32> Matrix::GetRow(s32 row) const
  {
    return NumericVector4<f32>(m[row][0], m[row][1], m[row][2], m[row][3]);
  }

  NumericVector4<f32> Matrix::GetColumn(s32 column) const
  {
    return NumericVector4<f32>(m[0][column], m[1][column], m[2][column], m[3][column]);
  }

  Vector3 Matrix::GetEulerAngles(bool radians) const
  {
    f32 pitch = atan2(m21, m22);
    f32 yaw = atan2(-m20, sqrt(m00 * m00 + m10 * m10));
    f32 roll = atan2(sin(pitch) * m02 - cos(pitch) * m01, cos(pitch) * m11 - sin(pitch) * m12);

    return Vector3(pitch, yaw, roll) * (radians ? 1.0f : RAD_TO_DEG);
  }  

  Matrix Matrix::GetTranspose(void) const
  {
    return Matrix(m00, m10, m20, m30,
                  m01, m11, m21, m31,
                  m02, m12, m22, m32,
                  m03, m13, m23, m33);
  }
  
  Matrix Matrix::GetInverse(void) const
  {
    f32 a0 = m00 * m11 - m01 * m10;
    f32 a1 = m00 * m12 - m02 * m10;
    f32 a2 = m00 * m13 - m03 * m10;
    f32 a3 = m01 * m12 - m02 * m11;
    f32 a4 = m01 * m13 - m03 * m11;
    f32 a5 = m02 * m13 - m03 * m12;
    f32 b0 = m20 * m31 - m21 * m30;
    f32 b1 = m20 * m32 - m22 * m30;
    f32 b2 = m20 * m33 - m23 * m30;
    f32 b3 = m21 * m32 - m22 * m31;
    f32 b4 = m21 * m33 - m23 * m31;
    f32 b5 = m22 * m33 - m23 * m32;

    f32 det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
    if(Abs(det) > EPSILON)
    {
      f32 invDet = 1.0f / det;
      return Matrix((m11 * b5 - m12 * b4 + m13 * b3) * invDet, (-m01 * b5 + m02 * b4 - m03 * b3) * invDet, (m31 * a5 - m32 * a4 + m33 * a3) * invDet, (-m21 * a5 + m22 * a4 - m23 * a3) * invDet,
                    (-m10 * b5 + m12 * b2 - m13 * b1) * invDet, (m00 * b5 - m02 * b2 + m03 * b1) * invDet, (-m30 * a5 + m32 * a2 - m33 * a1) * invDet, (m20 * a5 - m22 * a2 + m23 * a1) * invDet,
                    (m10 * b4 - m11 * b2 + m13 * b0) * invDet, (-m00 * b4 + m01 * b2 - m03 * b0) * invDet, (m30 * a4 - m31 * a2 + m33 * a0) * invDet, (-m20 * a4 + m21 * a2 - m23 * a0) * invDet,
                    (-m10 * b3 + m11 * b1 - m12 * b0) * invDet, (m00 * b3 - m01 * b1 + m02 * b0) * invDet, (-m30 * a3 + m31 * a1 - m32 * a0) * invDet, (m20 * a3 - m21 * a1 + m22 * a0) * invDet);
    }

    return ZERO;
  }

  Matrix Matrix::GetAdjoint(void) const
  {
    f32 a0 = m00 * m11 - m01 * m10;
    f32 a1 = m00 * m12 - m02 * m10;
    f32 a2 = m00 * m13 - m03 * m10;
    f32 a3 = m01 * m12 - m02 * m11;
    f32 a4 = m01 * m13 - m03 * m11;
    f32 a5 = m02 * m13 - m03 * m12;
    f32 b0 = m20 * m31 - m21 * m30;
    f32 b1 = m20 * m32 - m22 * m30;
    f32 b2 = m20 * m33 - m23 * m30;
    f32 b3 = m21 * m32 - m22 * m31;
    f32 b4 = m21 * m33 - m23 * m31;
    f32 b5 = m22 * m33 - m23 * m32;

    return Matrix(m11 * b5 - m12 * b4 + m13 * b3, -m01 * b5 + m02 * b4 - m03 * b3, m31 * a5 - m32 * a4 + m33 * a3, -m21 * a5 + m22 * a4 - m23 * a3,
                  -m10 * b5 + m12 * b2 - m13 * b1, m00 * b5 - m02 * b2 + m03 * b1, -m30 * a5 + m32 * a2 - m33 * a1, m20 * a5 - m22 * a2 + m23 * a1,
                  m10 * b4 - m11 * b2 + m13 * b0, -m00 * b4 + m01 * b2 - m03 * b0, m30 * a4 - m31 * a2 + m33 * a0, -m20 * a4 + m21 * a2 - m23 * a0,
                  -m10 * b3 + m11 * b1 - m12 * b0, m00 * b3 - m01 * b1 + m02 * b0, -m30 * a3 + m31 * a1 - m32 * a0, m20 * a3 - m21 * a1 + m22 * a0);
  }

  NumericVector4<f32> Matrix::GetTranslation(void) const
  {
    return NumericVector4<f32>(m30, m31, m32);
  }

  NumericVector4<f32> Matrix::GetTransposeTranslation(void) const
  {
    return NumericVector4<f32>(m03, m13, m23);
  }

  Quaternion Matrix::GetOrientation(void) const
  {
    Matrix m = *this;
    Scale scale = GetScale();
    m.SetColumn(0, m.GetColumn(0) /= scale.GetVector().x);
    m.SetColumn(1, m.GetColumn(1) /= scale.GetVector().y);
    m.SetColumn(2, m.GetColumn(2) /= scale.GetVector().z);
    Quaternion orientation;
    orientation.FromRotationMatrix(m);
    return orientation;
  }

  Scale Matrix::GetScale(void) const
  {
    return Scale(NumericVector4<f32>(sqrtf(m00*m00 + m01*m01 + m02*m02), sqrtf(m10*m10 + m11*m11 + m12*m12), sqrtf(m20*m20 + m21*m21 + m22*m22)));
  }

  TranslationMatrix Matrix::GetTranslationMatrix(void) const
  {
    return TranslationMatrix(GetTranslation());
  }

  TranslationMatrix Matrix::GetTransposeTranslationMatrix(void) const
  {
    return TranslationMatrix(GetTransposeTranslation());
  }

  OrientationMatrix Matrix::GetOrientationMatrix(void) const
  {
    return OrientationMatrix(GetOrientation());
  }

  ScaleMatrix Matrix::GetScaleMatrix(void) const
  {
    return ScaleMatrix(GetScale());
  }

  Matrix& Matrix::Zero(void)
  {
    memset(&v, 0, sizeof(f32) * 16);
    return *this;
  }

  Matrix& Matrix::Identity(void)
  {
    Zero();
    m00 = m11 = m22 = m33 = 1.0f;
    return *this;
  }

  Matrix& Matrix::Transpose(void)
  {
    *this = Matrix(m00, m10, m20, m30,
                   m01, m11, m21, m31,
                   m02, m12, m22, m32,
                   m03, m13, m23, m33);
    return *this;
  }

  Matrix& Matrix::Inverse(void)
  {
    *this = GetInverse();
    return *this;
  }

  Matrix& Matrix::Adjoint(void)
  {
    *this = GetAdjoint();
    return *this;
  }

  f32 Matrix::Determinant(void)
  {
    return ((m00 * m11 - m01 * m10) * (m22 * m33 - m23 * m32)) -
           ((m00 * m12 - m02 * m10) * (m21 * m33 - m23 * m31)) +
           ((m00 * m13 - m03 * m10) * (m21 * m32 - m22 * m31)) +
           ((m01 * m12 - m02 * m11) * (m20 * m33 - m23 * m30)) -
           ((m01 * m13 - m03 * m11) * (m20 * m32 - m22 * m30)) +
           ((m02 * m13 - m03 * m12) * (m20 * m31 - m21 * m30));
  }



  TranslationMatrix::TranslationMatrix(const NumericVector4<f32>& delta, bool transpose)
    : Matrix(1.0f, 0.0f, 0.0f, delta.x,
             0.0f, 1.0f, 0.0f, delta.y,
             0.0f, 0.0f, 1.0f, delta.z,
             0.0f, 0.0f, 0.0f, 1.0f)
  {
    if(transpose)
      Transpose();
  }

  TranslationMatrix& TranslationMatrix::Inverse(void)
  {
    m03 = -m03;
    m13 = -m13;
    m23 = -m23;
    m30 = -m30;
    m31 = -m31;
    m32 = -m32;
    return *this;
  }

  Matrix TranslationMatrix::Build(const NumericVector4<f32>& delta)
  {
    return TranslationMatrix(delta);
  }



  OrientationMatrix::OrientationMatrix(const Quaternion& rotation)
  { }

  Matrix OrientationMatrix::Build(const Quaternion& rotation)
  {
    return OrientationMatrix(rotation);
  }



  ScaleMatrix::ScaleMatrix(f32 uniform_scale)
    : Matrix(uniform_scale, 0.0f, 0.0f, 0.0f,
             0.0f, uniform_scale, 0.0f, 0.0f,
             0.0f, 0.0f, uniform_scale, 0.0f,
             0.0f, 0.0f, 0.0f, 1.0f)
  { }

  ScaleMatrix::ScaleMatrix(const Scale& scale)
    : Matrix(scale.scale.x, 0.0f, 0.0f, 0.0f,
             0.0f, scale.scale.y, 0.0f, 0.0f,
             0.0f, 0.0f, scale.scale.z, 0.0f,
             0.0f, 0.0f, 0.0f, 1.0f)
  { }

  ScaleMatrix& ScaleMatrix::Inverse(void)
  {
    m00 = 1.0f / m00;
    m11 = 1.0f / m11;
    m22 = 1.0f / m22;
    return *this;
  }

  Matrix ScaleMatrix::Build(f32 uniform_scale)
  {
    return ScaleMatrix(uniform_scale);
  }

  Matrix ScaleMatrix::Build(const Scale& scale)
  {
    return ScaleMatrix(scale);
  }



  TransformMatrix::TransformMatrix(const NumericVector4<f32>& delta, const Quaternion& rotation, const Scale& scale)
    : Matrix(TranslationMatrix(delta) * OrientationMatrix(rotation) * ScaleMatrix(scale))
  { }

  TransformMatrix::TransformMatrix(const TranslationMatrix& delta, const OrientationMatrix& rotation, const ScaleMatrix& scale)
    : Matrix(delta * rotation * scale)
  { }

  Matrix TransformMatrix::Build(const NumericVector4<f32>& delta, const Quaternion& rotation, const Scale& scale)
  {
    return Matrix(TranslationMatrix(delta) * OrientationMatrix(rotation) * ScaleMatrix(scale));
  }



  PerspectiveMatrix::PerspectiveMatrix(f32 fov, f32 aspect, f32 near, f32 far)
    : Matrix(1.0f / (aspect * tanf(fov * DEG_TO_RAD * 0.5f)), 0.0f, 0.0f, 0.0f,
             0.0f, 1.0f / tanf(fov * DEG_TO_RAD * 0.5f), 0.0f, 0.0f,
             0.0f, 0.0f, (far + near) / (near - far), -1.0f,
             0.0f, 0.0f, (2.0f * far * near) / (near - far), 0.0f)
  { }

  Matrix PerspectiveMatrix::Build(f32 fov, f32 aspect, f32 near, f32 far)
  {
    return PerspectiveMatrix(fov, aspect, near, far);
  }



  OrthographicMatrix::OrthographicMatrix(f32 width, f32 height, f32 near, f32 far)
    : Matrix(width ? 2.0f / width : 1.0f, 0.0f, 0.0f, 0.0f,
             0.0f, height ? 2.0f / height : 1.0f, 0.0f, 0.0f,
             0.0f, 0.0f, -1.0f / (far - near), 0.0f,
             0.0f, 0.0f, near / (near - far), 1.0f)
  { }

  Matrix OrthographicMatrix::Build(f32 fov, f32 aspect, f32 near, f32 far)
  {
    return OrthographicMatrix(fov, aspect, near, far);
  }



  ViewMatrix::ViewMatrix(const NumericPoint4<f32>& eye, const NumericVector4<f32>& look, const NumericVector4<f32>& up, const NumericVector4<f32>& right)
    : Matrix(look.x, up.x, right.x, 0.0f,
             look.y, up.y, right.y, 0.0f,
             look.z, up.z, right.z, 0.0f,
             -Dot(eye, look), -Dot(eye, up), -Dot(eye, right), 1.0f)
  { }

  ViewMatrix::ViewMatrix(const NumericPoint4<f32>& eye, const NumericPoint4<f32>& destination, const NumericVector4<f32>& up)
  {
    Math::NumericVector4<f32> Z = (eye - destination).Normalize();
    Math::NumericVector4<f32> X = (up.Cross(Z)).Normalize();
    Math::NumericVector4<f32> Y = (Z.Cross(X)).Normalize();

    m00 = X.x;
    m01 = Y.x;
    m02 = Z.x;
    m03 = 0.0f;

    m10 = X.y;
    m11 = Y.y;
    m12 = Z.y;
    m13 = 0.0f;

    m20 = X.z;
    m21 = Y.z;
    m22 = Z.z;
    m23 = 0.0f;

    m30 = -Dot(eye, X);
    m31 = -Dot(eye, Y);
    m32 = -Dot(eye, Z);
    m33 = 1.0f;
  }

  Matrix ViewMatrix::Build(const NumericPoint4<f32>& eye, const NumericVector4<f32>& look, const NumericVector4<f32>& up, const NumericVector4<f32>& right)
  {
    return ViewMatrix(eye, look, up, right);
  }

  Matrix ViewMatrix::Build(const NumericPoint4<f32>& eye, const NumericPoint4<f32>& destination, const NumericVector4<f32>& up)
  {
    return ViewMatrix(eye, destination, up);
  }
}
