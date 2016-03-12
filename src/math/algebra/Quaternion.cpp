/*
*  FILE          Quaternion.cpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for the Quaternion orientation class.
*/
#include "CommonPrecompiled.h"
#include "Quaternion.h"

namespace Math
{
  const Quaternion Quaternion::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
  const Quaternion Quaternion::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f);

  Quaternion::Quaternion(void)
    : w(1.0f), x(0.0f), y(0.0f), z(0.0f)
  { }

  Quaternion::Quaternion(f32 ww, f32 xx, f32 yy, f32 zz)
    : w(ww), x(xx), y(yy), z(zz)
  { }

  Quaternion::Quaternion(f32 x, f32 y, f32 z)
  {
    *this = Quaternion(NumericVector4<f32>::UNIT_Z, z) * Quaternion(NumericVector4<f32>::UNIT_Y, y) * Quaternion(NumericVector4<f32>::UNIT_X, x);
  }

  Quaternion::Quaternion(const Matrix &rotation)
  {
    FromRotationMatrix(rotation);
  }

  Quaternion::Quaternion(const NumericVector4<f32> &axis, f32 angle)
  {
    FromAxisAngle(axis, angle);
  }

  f32 Quaternion::Length(void) const
  {
    return sqrt(w * w + x * x + y * y + z * z);
  }

  f32 Quaternion::SquaredLength(void) const
  {
    return (w * w + x * x + y * y + z * z);
  }

  Quaternion Quaternion::QuaternionProduct(const Quaternion &rhs) const
  {
    return (*this) * rhs;
  }

  f32 Quaternion::DotProduct(const Quaternion &rhs) const
  {
    return (w * rhs.w + x * rhs.x + y * rhs.y + z * rhs.z);
  }

  Quaternion& Quaternion::Normalize(void)
  {
    f32 norm = Length();

    if(norm < EPSILON)
      norm = w = x = y = z = 0.0f;
    else
    {
      norm = 1.0f / norm;
      w *= norm;
      x *= norm;
      y *= norm;
      z *= norm;
    }
    return *this;
  }

  Quaternion& Quaternion::NormalizeQuick(void)
  {
    f32 normalize = Length();
    assertion(normalize == 0);

    normalize = 1.0f / normalize;
    w *= normalize;
    x *= normalize;
    y *= normalize;
    z *= normalize;

    return *this;
  }

  Quaternion Quaternion::Inverse(void) const
  {
    f32 normalize = Length();
    if(normalize == 0.0f)
      return Quaternion(0.0f, 0.0f, 0.0f, 0.0f);

    normalize = 1.0f / normalize;
    return Quaternion(w * normalize, -x * normalize, -y * normalize, -z * normalize);
  }

  Quaternion Quaternion::InverseQuick(void) const
  {
    f32 normalize = Length();
    assertion(normalize == 0);

    normalize = 1.0f / normalize;
    return Quaternion(w * normalize, -x * normalize, -y * normalize, -z * normalize);
  }

  Quaternion Quaternion::Conjugate(void) const
  {
    return Quaternion(w, -x, -y, -z);
  }

  void Quaternion::AddScaledVector(const NumericVector4<f32> &vec, f32 scale)
  {
    Quaternion q(0.0f, vec.x * scale, vec.y * scale, vec.z * scale);

    q = q * (*this);
    w += q.w * 0.5f;
    x += q.x * 0.5f;
    y += q.y * 0.5f;
    z += q.z * 0.5f;
  }

  f32 Quaternion::operator[](u32 index) const
  {
    return v[index];
  }

  f32& Quaternion::operator[](u32 index)
  {
    return v[index];
  }

  Quaternion& Quaternion::operator=(const Quaternion &rhs)
  {
    w = rhs.w;
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }

  bool Quaternion::operator==(const Quaternion &rhs) const
  {
    return Equal(x, rhs.x) && Equal(y, rhs.y) && Equal(z, rhs.z) && Equal(w, rhs.w);
  }

  bool Quaternion::operator!=(const Quaternion &rhs) const
  {
    return !(*this == rhs);
  }

  Quaternion Quaternion::operator+(const Quaternion &rhs) const
  {
    return Quaternion(w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z);
  }

  Quaternion Quaternion::operator-(const Quaternion &rhs) const
  {
    return Quaternion(w - rhs.w, x - rhs.x, y - rhs.y, z - rhs.z);
  }

  Quaternion Quaternion::operator*(const Quaternion &rhs) const
  {
    return Quaternion(w*rhs.w - x*rhs.x - y*rhs.y - z*rhs.z,
      w*rhs.x + x*rhs.w + y*rhs.z - z*rhs.y,
      w*rhs.y - x*rhs.z + y*rhs.w + z*rhs.x,
      w*rhs.z + x*rhs.y - y*rhs.x + z*rhs.w);
  }

  NumericVector4<f32> Quaternion::operator*(const NumericVector4<f32> &vec) const
  {
    NumericVector4<f32> uv, uuv;
    NumericVector4<f32> qvec(x, y, z);

    uv = qvec.Cross(vec);
    uuv = qvec.Cross(uuv);
    uv *= (2.0f * w);
    uuv *= 2.0f;

    return vec + uv + uuv;
  }

  Quaternion Quaternion::operator*(f32 scalar) const
  {
    return Quaternion(w*scalar, x*scalar, y*scalar, z*scalar);
  }

  Quaternion Quaternion::operator/(f32 scalar) const
  {
    if(scalar == 0.0f)
      return Quaternion(MAX_FLOAT, MAX_FLOAT, MAX_FLOAT, MAX_FLOAT);

    scalar = 1.0f / scalar;
    return Quaternion(w*scalar, x*scalar, y*scalar, z*scalar);
  }

  Quaternion Quaternion::operator-(void) const
  {
    return Quaternion(-w, -x, -y, -z);
  }

  Quaternion& Quaternion::operator+=(const Quaternion &rhs)
  {
    w += rhs.w;
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return (*this);
  }

  Quaternion& Quaternion::operator-=(const Quaternion &rhs)
  {
    w -= rhs.w;
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return (*this);
  }

  Quaternion& Quaternion::operator*=(f32 scalar)
  {
    w *= scalar;
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return (*this);
  }

  Quaternion& Quaternion::operator/=(f32 scalar)
  {
    if(scalar == 0.0f)
      w = x = y = z = MAX_FLOAT;
    else
    {
      scalar = 1.0f / scalar;
      w *= scalar;
      x *= scalar;
      y *= scalar;
      z *= scalar;
    }
    return (*this);
  }

  std::ostream& operator<<(std::ostream& os, const Quaternion& obj)
  {
    os << obj.w << obj.x << obj.y << obj.z;
    return os;
  }

  std::istream& operator>>(std::istream& is, Quaternion& obj)
  {
    is >> obj.w >> obj.x >> obj.y >> obj.z;
    return is;
  }

  Quaternion& Quaternion::FromEulerAngles(f32 pitch, f32 yaw, f32 roll, bool radians)
  {
    Matrix mat(pitch, yaw, roll, radians);
    FromRotationMatrix(mat);
    return (*this);
  }

  Vector3 Quaternion::GetEulerAngles(bool asRadians) const
  {
    Matrix mat;
    ToRotationMatrix(mat);
    return mat.GetEulerAngles(asRadians);
  }

  Quaternion operator*(f32 scalar, const Quaternion &rhs)
  {
    return (rhs * scalar);
  }

  void Quaternion::FromRotationMatrix(const Matrix &rotation)
  {
    const s32 next[3] = { 1, 2, 0 };

    f32 trace = rotation.m[0][0] + rotation.m[1][1] + rotation.m[2][2];
    f32 root;

    if(trace > 0.0f)
    {
      root = sqrt(trace + 1.0f);
      w = 0.5f * root;
      root = 0.5f / root;
      x = (rotation.m[2][1] - rotation.m[1][2]) * root;
      y = (rotation.m[0][2] - rotation.m[2][0]) * root;
      z = (rotation.m[1][0] - rotation.m[0][1]) * root;
    }
    else
    {
      s32 i = 0;
      if(rotation.m[1][1] > rotation.m[0][0])
        i = 1;

      if(rotation.m[2][2] > rotation.m[i][i])
        i = 2;

      s32 j = next[i];
      s32 k = next[j];

      root = sqrt(rotation.m[i][i] - rotation.m[j][j] - rotation.m[k][k] + 1.0f);
      f32 *quat[3] = { &x, &y, &z };
      *quat[i] = 0.5f * root;
      root = 0.5f / root;
      v[0] = (rotation.m[k][j] - rotation.m[j][k]) * root;
      *quat[j] = (rotation.m[j][i] + rotation.m[i][j]) * root;
      *quat[k] = (rotation.m[k][i] + rotation.m[i][k]) * root;
    }
  }

  void Quaternion::ToRotationMatrix(Matrix &rotation) const
  {
    f32 twoX = 2.0f * v[1];
    f32 twoY = 2.0f * v[2];
    f32 twoZ = 2.0f * v[3];
    f32 twoWX = twoX * v[0];
    f32 twoWY = twoY * v[0];
    f32 twoWZ = twoZ * v[0];
    f32 twoXX = twoX * v[1];
    f32 twoXY = twoY * v[1];
    f32 twoXZ = twoZ * v[1];
    f32 twoYY = twoY * v[2];
    f32 twoYZ = twoZ * v[2];
    f32 twoZZ = twoZ * v[3];

    rotation.m[0][0] = 1.0f - (twoYY + twoZZ);
    rotation.m[0][1] = twoXY - twoWZ;
    rotation.m[0][2] = twoXZ + twoWY;
    rotation.m[0][3] = 0.0f;
    rotation.m[1][0] = twoXY + twoWZ;
    rotation.m[1][1] = 1.0f - (twoXX + twoZZ);
    rotation.m[1][2] = twoYZ - twoWX;
    rotation.m[1][3] = 0.0f;
    rotation.m[2][0] = twoXZ - twoWY;
    rotation.m[2][1] = twoYZ + twoWX;
    rotation.m[2][2] = 1.0f - (twoXX + twoYY);
    rotation.m[2][3] = 0.0f;
    rotation.m[3][0] = 0.0f;
    rotation.m[3][1] = 0.0f;
    rotation.m[3][2] = 0.0f;
    rotation.m[3][3] = 1.0f;
  }

  void Quaternion::FromAxisAngle(const NumericVector4<f32> &axis, f32 angle)
  {
    f32 halfAngle = 0.5f * angle;
    f32 sina, cosa;
    GetSinCos(halfAngle, sina, cosa);

    w = cosa;
    x = sina * axis.x;
    y = sina * axis.y;
    z = sina * axis.z;
    Normalize();
  }

  void Quaternion::ToAxisAngle(NumericVector4<f32> &axis, f32 &angle) const
  {
    f32 sqrLen = x*x + y*y + z*z;

    if(sqrLen > 0.0f)
    {
      angle = 2.0f * acos(w);
      f32 invLength = 1.0f / sqrt(sqrLen);
      axis.x = x * invLength;
      axis.y = y * invLength;
      axis.z = z * invLength;
    }
    else
    {
      angle = 0.0f;
      axis.x = 1.0f;
      axis.y = 0.0f;
      axis.z = 0.0f;
    }
  }

  NumericVector4<f32> Quaternion::Rotate(const NumericVector4<f32> &vec) const
  {
    Matrix rotation;
    ToRotationMatrix(rotation);
    return (rotation * vec);
  }

  Quaternion Quaternion::VectorToVector(const NumericVector4<f32> &vec1, const NumericVector4<f32> &vec2)
  {
    f32 mod = sqrt(vec1.LengthSquared() * vec2.LengthSquared());
    f32 angle = vec1.Dot(vec2) / mod;
    /* Vectors Parallel */
    if(angle >= 1.0f - EPSILON)
      return Quaternion::IDENTITY;
    /* Vectors Opposite and Parallel */
    else if(angle <= -1.0f + EPSILON)
      return Quaternion(Math::NumericVector4<f32>::UNIT_Y, PI);
    else if(Abs(angle + 1.0f) < EPSILON)
    {
      NumericVector4<f32> arbitrary = Math::Abs(vec1.Dot(NumericVector4<f32>::UNIT_X)) < 1.0 ? NumericVector4<f32>::UNIT_X : NumericVector4<f32>::UNIT_Y;
      NumericVector4<f32> cross = vec1.Cross(arbitrary); cross.Normalize();
      return Quaternion(cross, PI);
    }
    NumericVector4<f32> cross = vec1.Cross(vec2);
    return Quaternion(vec1.Dot(vec2) + mod, cross.x, cross.y, cross.z).Normalize();
  }

  f32 Quaternion::GetScalar() const
  {
    return w;
  }

  Vector3 Quaternion::GetVector() const
  {
    return Vector3(x, y, z);
  }

  Quaternion Quaternion::Exp(void) const
  {
    float Theta = GetVector().Length();
    float SinTheta = sinf(Theta);
    float CosTheta = cosf(Theta);
    float SinThetaOverTheta = SinTheta / Theta;

    if(Theta > 0)
      return Quaternion(CosTheta, x*SinThetaOverTheta, y*SinThetaOverTheta, z*SinThetaOverTheta);
    else
      return Quaternion(CosTheta, 0.0f, 0.0f, 0.0f);
  }

  Quaternion Quaternion::Log(void) const
  {
    float Theta = acos(w);
    float SinTheta = sin(Theta);
    float ThetaOverSinTheta = Theta / SinTheta;

    if(SinTheta > 0)
      return Quaternion(0.0f, x*ThetaOverSinTheta, y*ThetaOverSinTheta, z*ThetaOverSinTheta);
    else
      return Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
  }

  Quaternion Quaternion::Bisect(const Quaternion& p, const Quaternion& q)
  {
    return (p + q).Normalize();
  }

  Quaternion Quaternion::Double(const Quaternion& p, const Quaternion& q)
  {
    /* Method One: ((2.0f*(p.q))*q - p) */
    return (q * (p.DotProduct(q) * 2.0f)) - p;

    /* Method Two: q * p^-1 * q */
    return (q.QuaternionProduct(p.Inverse())).QuaternionProduct(q);
  }

  Quaternion Quaternion::Lerp(const Quaternion& p, const Quaternion& q, f32 t)
  {
    f32 sign = p.DotProduct(q) < 0.0f ? -1.0f : 1.0f;

    return (p*(1.0f - t) + q*(sign*t));
  }

  Quaternion Quaternion::Slerp(const Quaternion& p, const Quaternion& q, f32 t)
  {
    f32 CosTheta = p.DotProduct(q);

    f32 sign = 1.0f;
    if(CosTheta < 0.0f)
    {
      CosTheta = -CosTheta;
      sign = -1.0f;
    }

    f32 Theta = acos(CosTheta);
    f32 SinTheta = sin(Theta);

    return (p*(sin((1.0f - t)*Theta) / SinTheta) + q*(sign*sin(t*Theta) / SinTheta));
  }

  Quaternion Quaternion::SlerpNoInversion(const Quaternion& p, const Quaternion& q, f32 t)
  {
    if((1.0f - Math::Abs(p.DotProduct(q))) > SLERP_EPSILON)
      return Slerp(p, q, t);
    else
      return Lerp(p, q, t);
  }
}