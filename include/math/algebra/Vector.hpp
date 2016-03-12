/*
*  FILE          Vector.hpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for Vector Template class.
*/


namespace Math
{
  template<class T> const NumericVector2<T> NumericVector2<T>::ZERO(T(0), T(0));
  template<class T> const NumericVector2<T> NumericVector2<T>::ONE(T(1), T(1));
  template<class T> const NumericVector2<T> NumericVector2<T>::UNIT_X(T(1), T(0));
  template<class T> const NumericVector2<T> NumericVector2<T>::UNIT_Y(T(0), T(1));

  template<class T>
  NumericVector2<T>::NumericVector2(T x_, T y_)
    : x(x_), y(y_)
  { }

  template<class T>
  NumericVector2<T>::NumericVector2(const NumericVector2<T>& rhs)
    : x(rhs.x), y(rhs.y)
  { }

  template<class T>
  f32 NumericVector2<T>::Distance(const NumericVector2<T>& point) const
  {
    return (*this - point).Length();
  }

  template<class T>
  NumericVector2<T> NumericVector2<T>::Midpoint(const NumericVector2<T>& point) const
  {
    return NumericVector2<T>((x + point.x) * 0.5f, (y + point.y) * 0.5f);
  }

  template<class T>
  T NumericVector2<T>::Dot(const NumericVector2<T>& rhs) const
  {
    return x * rhs.x + y * rhs.y;
  }

  template<class T>
  T NumericVector2<T>::Cross(const NumericVector2<T>& rhs) const
  {
    return x * rhs.y - y * rhs.x;
  }

  template<class T>
  NumericVector2<T> NumericVector2<T>::Reflect(const NumericVector2<T>& incident) const
  {
    return incident - *this * (2.0f * Dot(*this, incident));
  }

  template<class T>
  NumericVector2<T> NumericVector2<T>::Refract(const NumericVector2<T>& incident, const f32 n1, const f32 n2) const
  {
    f32 RefractionIndex = n1 / n2;
    f32 IncidentAngle = -Dot(*this, incident);
    f32 SinT2 = RefractionIndex * RefractionIndex * (1.0f - IncidentAngle * IncidentAngle);
    SinT2 = Math::Clamp<f32>(SinT2, 0.0f, 1.0f);

    f32 RefractionAngle = sqrt(1.0f - SinT2);
    return incident * RefractionIndex + *this * (RefractionIndex * IncidentAngle - RefractionAngle);
  }

  template<class T>
  bool NumericVector2<T>::IsZero(void) const
  {
    return Equal(x, T(0)) && Equal(y, T(0));
  }

  template<class T>
  bool NumericVector2<T>::IsParallel(const NumericVector2<T>& rhs) const
  {
    return Equal(Cross(rhs), T(0));
  }

  template<class T>
  bool NumericVector2<T>::IsOrthogonal(const NumericVector2<T>& rhs) const
  {
    return Equal(Dot(rhs), T(0));
  }

  template<class T>
  f32 NumericVector2<T>::Length(void) const
  {
    return sqrtf(f32(x * x + y * y));
  }

  template<class T>
  T NumericVector2<T>::LengthSquared(void) const
  {
    return Dot(*this);
  }

  template<class T>
  NumericVector2<T>& NumericVector2<T>::Normalize(void)
  {
    f32 length = Length();
    if(length == 0.0f)
      *this = NumericVector2<T>::ZERO;
    else
      *this /= length;

    return *this;
  }

  template<class T>
  NumericVector2<T> NumericVector2<T>::operator-(void) const
  {
    return NumericVector2<T>(x * T(-1), y * T(-1));
  }

  template<class T>
  NumericVector2<T> NumericVector2<T>::operator+(const NumericVector2<T>& rhs) const
  {
    return NumericVector2<T>(x + rhs.x, y + rhs.y);
  }

  template<class T>
  NumericVector2<T> NumericVector2<T>::operator-(const NumericVector2<T>& rhs) const
  {
    return NumericVector2<T>(x - rhs.x, y - rhs.y);
  }

  template<class T>
  NumericVector2<T> NumericVector2<T>::operator*(T scalar) const
  {
    return NumericVector2<T>(x * scalar, y * scalar);
  }

  template<class T>
  NumericVector2<T> NumericVector2<T>::operator/(T scalar) const
  {
    return NumericVector2<T>(x / scalar, y / scalar);
  }

  template<class T>
  NumericVector2<T>& NumericVector2<T>::operator=(const NumericVector2<T>& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }

  template<class T>
  NumericVector2<T>& NumericVector2<T>::operator+=(const NumericVector2<T>& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  template<class T>
  NumericVector2<T>& NumericVector2<T>::operator-=(const NumericVector2<T>& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  template<class T>
  NumericVector2<T>& NumericVector2<T>::operator*=(T scalar)
  {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  template<class T>
  NumericVector2<T>& NumericVector2<T>::operator/=(T scalar)
  {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  template<class T>
  T NumericVector2<T>::operator[](u32 n) const
  {
    return v[n];
  }

  template<class T>
  T& NumericVector2<T>::operator[](u32 n)
  {
    return v[n];
  }

  template<class T>
  bool NumericVector2<T>::operator==(const NumericVector2<T>& rhs) const
  {
    return Equal(x, rhs.x) && Equal(y, rhs.y);
  }

  template<class T>
  bool NumericVector2<T>::operator!=(const NumericVector2<T>& rhs) const
  {
    return !(*this == rhs);
  }

  template<class T>
  std::ostream& operator<<(std::ostream& os, const NumericVector2<T>& obj)
  {
    os << obj.x << obj.y;
    return os;
  }

  template<class T>
  std::istream& operator>>(std::istream& is, NumericVector2<T>& obj)
  {
    is >> obj.x >> obj.y;
    return is;
  }

  template<class T> template<u32 a, u32 b>
  NumericVector2<T> NumericVector2<T>::Swizzle(void) const
  {
    assertion(a < 2 && b < 2);
    return NumericVector2<T>(v[a], v[b]);
  }

  template<class T> template<u32 a, u32 b>
  NumericVector2<T>& NumericVector2<T>::NumericVector2Swizzle<a, b>::operator=(const NumericVector2<T>& rhs)
  {
    v[a] = rhs.x;
    v[b] = rhs.y;
    return *(NumericVector2<T>*)this;
  }

  template<class T> template<u32 a, u32 b>
  NumericVector2<T>::NumericVector2Swizzle<a, b>::operator NumericVector2<T>()
  {
    return NumericVector2<T>(v[a], v[b]);
  }



  template<class T> const NumericVector3<T> NumericVector3<T>::ZERO(T(0), T(0), T(0));
  template<class T> const NumericVector3<T> NumericVector3<T>::ONE(T(1), T(1), T(1));
  template<class T> const NumericVector3<T> NumericVector3<T>::UNIT_X(T(1), T(0), T(0));
  template<class T> const NumericVector3<T> NumericVector3<T>::UNIT_Y(T(0), T(1), T(0));
  template<class T> const NumericVector3<T> NumericVector3<T>::UNIT_Z(T(0), T(0), T(1));

  template<class T>
  NumericVector3<T>::NumericVector3(T x_, T y_, T z_)
    : x(x_), y(y_), z(z_)
  { }

  template<class T>
  NumericVector3<T>::NumericVector3(const NumericVector3<T>& rhs)
    : x(rhs.x), y(rhs.y), z(rhs.z)
  { }

  template<class T>
  T NumericVector3<T>::Dot(const NumericVector3<T>& rhs) const
  {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }

  template<class T>
  NumericVector3<T> NumericVector3<T>::Cross(const NumericVector3<T>& rhs) const
  {
    return NumericVector3<T>(y * rhs.z - rhs.y * z, rhs.x * z - x * rhs.z, x * rhs.y - rhs.x * y);
  }

  template<class T>
  NumericVector3<T> NumericVector3<T>::Reflect(const NumericVector3<T>& incident) const
  {
    return incident - *this * (2.0f * Dot(*this, incident));
  }

  template<class T>
  NumericVector3<T> NumericVector3<T>::Refract(const NumericVector3<T>& incident, const f32 n1, const f32 n2) const
  {
    f32 RefractionIndex = n1 / n2;
    f32 IncidentAngle = -Dot(*this, incident);
    f32 SinT2 = RefractionIndex * RefractionIndex * (1.0f - IncidentAngle * IncidentAngle);
    SinT2 = Math::Clamp<f32>(SinT2, 0.0f, 1.0f);

    f32 RefractionAngle = sqrt(1.0f - SinT2);
    return incident * RefractionIndex + *this * (RefractionIndex * IncidentAngle - RefractionAngle);
  }

  template<class T>
  bool NumericVector3<T>::IsZero(void) const
  {
    return Equal(x, T(0)) && Equal(y, T(0)) && Equal(z, T(0));
  }

  template<class T>
  bool NumericVector3<T>::IsParallel(const NumericVector3<T>& rhs) const
  {
    return Cross(rhs).IsZero();
  }

  template<class T>
  bool NumericVector3<T>::IsOrthogonal(const NumericVector3<T>& rhs) const
  {
    return Equal(Dot(rhs), T(0));
  }

  template<class T>
  f32 NumericVector3<T>::Length(void) const
  {
    return sqrtf(f32(x * x + y * y + z * z));
  }

  template<class T>
  T NumericVector3<T>::LengthSquared(void) const
  {
    return Dot(*this);
  }

  template<class T>
  NumericVector3<T>& NumericVector3<T>::Normalize(void)
  {
    f32 length = Length();
    if(length == 0.0f)
      *this = NumericVector3<T>::ZERO;
    else
      *this /= length;

    return *this;
  }

  template<class T>
  NumericVector3<T> NumericVector3<T>::operator-(void) const
  {
    return NumericVector3<T>(x * T(-1), y * T(-1), z * T(-1));
  }

  template<class T>
  NumericVector3<T> NumericVector3<T>::operator+(const NumericVector3<T>& rhs) const
  {
    return NumericVector3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  template<class T>
  NumericVector3<T> NumericVector3<T>::operator-(const NumericVector3<T>& rhs) const
  {
    return NumericVector3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  template<class T>
  NumericVector3<T> NumericVector3<T>::operator*(T scalar) const
  {
    return NumericVector3<T>(x * scalar, y * scalar, z * scalar);
  }

  template<class T>
  NumericVector3<T> NumericVector3<T>::operator/(T scalar) const
  {
    return NumericVector3<T>(x / scalar, y / scalar, z / scalar);
  }

  template<class T>
  NumericVector3<T>& NumericVector3<T>::operator=(const NumericVector3<T>& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }

  template<class T>
  NumericVector3<T>& NumericVector3<T>::operator+=(const NumericVector3<T>& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  template<class T>
  NumericVector3<T>& NumericVector3<T>::operator-=(const NumericVector3<T>& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  template<class T>
  NumericVector3<T>& NumericVector3<T>::operator*=(T scalar)
  {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  template<class T>
  NumericVector3<T>& NumericVector3<T>::operator/=(T scalar)
  {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
  }

  template<class T>
  T NumericVector3<T>::operator[](u32 n) const
  {
    return v[n];
  }

  template<class T>
  T& NumericVector3<T>::operator[](u32 n)
  {
    return v[n];
  }

  template<class T>
  bool NumericVector3<T>::operator==(const NumericVector3<T>& rhs) const
  {
    return Equal(x, rhs.x) && Equal(y, rhs.y) && Equal(z, rhs.z);
  }

  template<class T>
  bool NumericVector3<T>::operator!=(const NumericVector3<T>& rhs) const
  {
    return !(*this == rhs);
  }

  template<class T>
  std::ostream& operator<<(std::ostream& os, const NumericVector3<T>& obj)
  {
    os << obj.x << obj.y << obj.z;
    return os;
  }

  template<class T>
  std::istream& operator>>(std::istream& is, NumericVector3<T>& obj)
  {
    is >> obj.x >> obj.y >> obj.z;
    return is;
  }

  template<class T> template<u32 a, u32 b>
  NumericVector2<T> NumericVector3<T>::Swizzle(void) const
  {
    assertion(a < 3 && b < 3);
    return NumericVector2<T>(v[a], v[b]);
  }

  template<class T> template<u32 a, u32 b, u32 c>
  NumericVector3<T> NumericVector3<T>::Swizzle(void) const
  {
    assertion(a < 3 && b < 3 && c < 3);
    return NumericVector3<T>(v[a], v[b], v[c]);
  }

  template<class T> template<u32 a, u32 b, u32 c>
  NumericVector3<T>& NumericVector3<T>::NumericVector3Swizzle<a, b, c>::operator=(const NumericVector2<T>& rhs)
  {
    v[a] = rhs.x;
    v[b] = rhs.y;
    return *(NumericVector3<T>*)this;
  }

  template<class T> template<u32 a, u32 b, u32 c>
  NumericVector3<T>::NumericVector3Swizzle<a, b, c>::operator NumericVector2<T>()
  {
    return NumericVector2<T>(v[a], v[b]);
  }

  template<class T> template<u32 a, u32 b, u32 c>
  NumericVector3<T>& NumericVector3<T>::NumericVector3Swizzle<a, b, c>::operator=(const NumericVector3<T>& rhs)
  {
    v[a] = rhs.x;
    v[b] = rhs.y;
    v[c] = rhs.z;
    return *(NumericVector3<T>*)this;
  }

  template<class T> template<u32 a, u32 b, u32 c>
  NumericVector3<T>::NumericVector3Swizzle<a, b, c>::operator NumericVector3<T>()
  {
    return NumericVector3<T>(v[a], v[b], v[c]);
  }



  template<class T> const NumericVector4<T> NumericVector4<T>::ZERO(T(0), T(0), T(0), T(0));
  template<class T> const NumericVector4<T> NumericVector4<T>::ONE(T(1), T(1), T(1), T(0));
  template<class T> const NumericVector4<T> NumericVector4<T>::UNIT_X(T(1), T(0), T(0), T(0));
  template<class T> const NumericVector4<T> NumericVector4<T>::UNIT_Y(T(0), T(1), T(0), T(0));
  template<class T> const NumericVector4<T> NumericVector4<T>::UNIT_Z(T(0), T(0), T(1), T(0));
  template<class T> const NumericVector4<T> NumericVector4<T>::UNIT_W(T(0), T(0), T(0), T(1));

  template<class T>
  NumericVector4<T>::NumericVector4(T x_, T y_, T z_, T w_)
    : x(x_), y(y_), z(z_), w(w_)
  { }

  template<class T>
  NumericVector4<T>::NumericVector4(const NumericVector4<T>& rhs)
    : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
  { }

  template<class T>
  NumericVector4<T>::NumericVector4(const NumericVector3<T>& rhs, T w_)
    : x(rhs.x), y(rhs.y), z(rhs.z), w(w_)
  { }

  template<class T>
  T NumericVector4<T>::Dot(const NumericVector4<T>& rhs) const
  {
    return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
  }

  template<class T>
  f32 NumericVector4<T>::Length(void) const
  {
    return sqrtf(f32(x * x + y * y + z * z + w * w));
  }

  template<class T>
  T NumericVector4<T>::LengthSquared(void) const
  {
    return Dot(*this);
  }

  template<class T>
  NumericVector4<T> NumericVector4<T>::Cross(const NumericVector4<T>& rhs) const
  {
    return NumericVector4<T>(y * rhs.z - rhs.y * z, rhs.x * z - x * rhs.z, x * rhs.y - rhs.x * y);
  }

  template<class T>
  NumericVector4<T> NumericVector4<T>::Reflect(const NumericVector4<T>& incident) const
  {
    return incident - *this * (2.0f * Math::Dot(*this, incident));
  }

  template<class T>
  NumericVector4<T> NumericVector4<T>::Refract(const NumericVector4<T>& incident, const f32 n1, const f32 n2) const
  {
    f32 RefractionIndex = n1 / n2;
    f32 IncidentAngle = -Dot(*this, incident);
    f32 SinT2 = RefractionIndex * RefractionIndex * (1.0f - IncidentAngle * IncidentAngle);
    SinT2 = Math::Clamp<f32>(SinT2, 0.0f, 1.0f);

    f32 RefractionAngle = sqrt(1.0f - SinT2);
    return incident * RefractionIndex + *this * (RefractionIndex * IncidentAngle - RefractionAngle);
  }

  template<class T>
  bool NumericVector4<T>::IsZero(void) const
  {
    return Equal(x, T(0)) && Equal(y, T(0)) && Equal(z, T(0)) && Equal(w, T(0));
  }

  template<class T>
  bool NumericVector4<T>::IsParallel(const NumericVector4<T>& rhs) const
  {
    return Cross(rhs).IsZero();
  }

  template<class T>
  bool NumericVector4<T>::IsOrthogonal(const NumericVector4<T>& rhs) const
  {
    return Dot(rhs) == T(0);
  }

  template<class T>
  void NumericVector4<T>::BuildOrthonormalBasis(NumericVector4<T>& u, NumericVector4<T>& v)
  {
    if(abs(x) >= abs(y))
    {
      f32 invLen = 1.0f / sqrt(x * x + z * z);
      u.x = -z * invLen;
      u.y = 0.0f;
      u.z = x * invLen;
      v.x = y * u.z;
      v.y = z * u.x - x * u.z;
      v.z = -y * u.x;
    }
    else
    {
      f32 invLen = 1.0f / sqrt(y * y + z * z);
      u.x = 0.0f;
      u.y = z * invLen;
      u.z = -y * invLen;
      v.x = y * u.z - z * u.y;
      v.y = -x * u.z;
      v.z = x * u.y;
    }
  }

  template<class T>
  NumericVector4<T>& NumericVector4<T>::Normalize(void)
  {
    f32 length = Length();
    if(length == 0.0f)
      *this = NumericVector4<T>::ZERO;
    else
      *this /= length;

    return *this;
  }

  template<class T>
  NumericVector4<T> NumericVector4<T>::operator-(void) const
  {
    return NumericVector4<T>(x * T(-1), y * T(-1), z * T(-1), w * T(-1));
  }

  template<class T>
  NumericVector4<T> NumericVector4<T>::operator+(const NumericVector4<T>& rhs) const
  {
    return NumericVector4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
  }

  template<class T>
  NumericVector4<T> NumericVector4<T>::operator-(const NumericVector4<T>& rhs) const
  {
    return NumericVector4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
  }

  template<class T>
  NumericVector4<T> NumericVector4<T>::operator*(T scalar) const
  {
    return NumericVector4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
  }

  template<class T>
  NumericVector4<T> NumericVector4<T>::operator/(T scalar) const
  {
    return NumericVector4<T>(x / scalar, y / scalar, z / scalar, w / scalar);
  }

  template<class T>
  NumericVector4<T>& NumericVector4<T>::operator=(const NumericVector4<T>& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
  }

  template<class T>
  NumericVector4<T>& NumericVector4<T>::operator+=(const NumericVector4<T>& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
  }

  template<class T>
  NumericVector4<T>& NumericVector4<T>::operator-=(const NumericVector4<T>& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
  }

  template<class T>
  NumericVector4<T>& NumericVector4<T>::operator*=(T scalar)
  {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
  }

  template<class T>
  NumericVector4<T>& NumericVector4<T>::operator/=(T scalar)
  {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
  }

  template<class T>
  T NumericVector4<T>::operator[](u32 n) const
  {
    return v[n];
  }

  template<class T>
  T& NumericVector4<T>::operator[](u32 n)
  {
    return v[n];
  }

  template<class T>
  bool NumericVector4<T>::operator==(const NumericVector4<T>& rhs) const
  {
    return Equal(x, rhs.x) && Equal(y, rhs.y) && Equal(z, rhs.z) && Equal(w, rhs.w);
  }

  template<class T>
  bool NumericVector4<T>::operator!=(const NumericVector4<T>& rhs) const
  {
    return !(*this == rhs);
  }

  template<class T>
  std::ostream& operator<<(std::ostream& os, const NumericVector4<T>& obj)
  {
    os << obj.x << obj.y << obj.z << obj.w;
    return os;
  }

  template<class T>
  std::istream& operator>>(std::istream& is, NumericVector4<T>& obj)
  {
    is >> obj.x >> obj.y >> obj.z >> obj.w;
    return is;
  }

  template<class T> template<u32 a, u32 b>
  NumericVector2<T> NumericVector4<T>::Swizzle(void) const
  {
    assertion(a < 4 && b < 4);
    return NumericVector2<T>(v[a], v[b]);
  }

  template<class T> template<u32 a, u32 b, u32 c>
  NumericVector3<T> NumericVector4<T>::Swizzle(void) const
  {
    assertion(a < 4 && b < 4 && c < 4);
    return NumericVector3<T>(v[a], v[b], v[c]);
  }

  template<class T> template<u32 a, u32 b, u32 c, u32 d>
  NumericVector4<T> NumericVector4<T>::Swizzle(void) const
  {
    assertion(a < 4 && b < 4 && c < 4 && d < 4);
    return NumericVector4<T>(v[a], v[b], v[c], v[d]);
  }

  template<class T> template<u32 a, u32 b, u32 c, u32 d>
  NumericVector4<T>& NumericVector4<T>::NumericVector4Swizzle<a, b, c, d>::operator=(const NumericVector2<T>& rhs)
  {
    v[a] = rhs.x;
    v[b] = rhs.y;
    return *(NumericVector4<T>*)this;
  }

  template<class T> template<u32 a, u32 b, u32 c, u32 d>
  NumericVector4<T>::NumericVector4Swizzle<a, b, c, d>::operator NumericVector2<T>()
  {
    return NumericVector2<T>(v[a], v[b]);
  }

  template<class T> template<u32 a, u32 b, u32 c, u32 d>
  NumericVector4<T>& NumericVector4<T>::NumericVector4Swizzle<a, b, c, d>::operator=(const NumericVector3<T>& rhs)
  {
    v[a] = rhs.x;
    v[b] = rhs.y;
    v[c] = rhs.z;
    return *(NumericVector4<T>*)this;
  }

  template<class T> template<u32 a, u32 b, u32 c, u32 d>
  NumericVector4<T>::NumericVector4Swizzle<a, b, c, d>::operator NumericVector3<T>()
  {
    return NumericVector3<T>(v[a], v[b], v[c]);
  }

  template<class T> template<u32 a, u32 b, u32 c, u32 d>
  NumericVector4<T>& NumericVector4<T>::NumericVector4Swizzle<a, b, c, d>::operator=(const NumericVector4<T>& rhs)
  {
    v[a] = rhs.x;
    v[b] = rhs.y;
    v[c] = rhs.z;
    v[d] = rhs.w;
    return *(NumericVector4<T>*)this;
  }

  template<class T> template<u32 a, u32 b, u32 c, u32 d>
  NumericVector4<T>::NumericVector4Swizzle<a, b, c, d>::operator NumericVector4<T>()
  {
    return NumericVector4<T>(v[a], v[b], v[c], v[d]);
  }



  template<class T> const NumericPoint4<T> NumericPoint4<T>::ORIGIN(T(0), T(0), T(0), T(1));

  template<class T>
  NumericPoint4<T>::NumericPoint4(T x_, T y_, T z_, T w_)
    : NumericVector4<T>(x_, y_, z_, w_)
  { }

  template<class T>
  f32 NumericPoint4<T>::Distance(const NumericPoint4<T>& rhs) const
  {
    return (*this - rhs).Length();
  }

  template<class T>
  NumericPoint4<T> NumericPoint4<T>::Midpoint(const NumericPoint4<T>& rhs) const
  {
    return NumericPoint4<T>((this->x + rhs.x) * 0.5f, (this->y + rhs.y) * 0.5f, (this->z + rhs.z) * 0.5f, (this->w + rhs.w) * 0.5f);
  }

  template<class T>
  NumericPoint4<T> NumericPoint4<T>::operator+(const NumericVector4<T>& rhs) const
  {
    return NumericPoint4<T>(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w);
  }

  template<class T>
  NumericPoint4<T> NumericPoint4<T>::operator-(const NumericVector4<T>& rhs) const
  {
    return NumericPoint4<T>(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w);
  }

  template<class T>
  NumericVector4<T> NumericPoint4<T>::operator-(const NumericPoint4<T>& rhs) const
  {
    return NumericVector4<T>(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w);
  }

  template<class T>
  NumericPoint4<T>& NumericPoint4<T>::operator+=(const NumericVector4<T>& rhs)
  {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    this->w += rhs.w;
    return *this;
  }

  template<class T>
  NumericPoint4<T>& NumericPoint4<T>::operator-=(const NumericVector4<T>& rhs)
  {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    this->w -= rhs.w;
    return *this;
  }

  template<class T>
  std::ostream& operator<<(std::ostream& os, const NumericPoint4<T>& obj)
  {
    os << obj.x << obj.y << obj.z << obj.w;
    return os;
  }

  template<class T>
  std::istream& operator>>(std::istream& is, NumericPoint4<T>& obj)
  {
    is >> obj.x >> obj.y >> obj.z >> obj.w;
    return is;
  }




  template<class T> const NumericPoint2<T> NumericPoint2<T>::ORIGIN(T(0), T(0));

  template<class T>
  NumericPoint2<T>::NumericPoint2(T x_, T y_)
    : NumericVector2<T>(x_, y_)
  { }

  template<class T>
  f32 NumericPoint2<T>::Distance(const NumericPoint2<T>& rhs) const
  {
    return (*this - rhs).Length();
  }

  template<class T>
  NumericPoint2<T> NumericPoint2<T>::Midpoint(const NumericPoint2<T>& rhs) const
  {
    return NumericPoint2<T>((this->x + rhs.x) * 0.5f, (this->y + rhs.y) * 0.5f);
  }

  template<class T>
  NumericPoint2<T> NumericPoint2<T>::operator+(const NumericVector2<T>& rhs) const
  {
    return NumericPoint2<T>(this->x + rhs.x, this->y + rhs.y);
  }

  template<class T>
  NumericPoint2<T> NumericPoint2<T>::operator-(const NumericVector2<T>& rhs) const
  {
    return NumericPoint2<T>(this->x - rhs.x, this->y - rhs.y);
  }

  template<class T>
  NumericVector2<T> NumericPoint2<T>::operator-(const NumericPoint2<T>& rhs) const
  {
    return NumericVector2<T>(this->x - rhs.x, this->y - rhs.y);
  }

  template<class T>
  NumericPoint2<T>& NumericPoint2<T>::operator+=(const NumericVector2<T>& rhs)
  {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
  }

  template<class T>
  NumericPoint2<T>& NumericPoint2<T>::operator-=(const NumericVector2<T>& rhs)
  {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
  }

  template<class T>
  std::ostream& operator<<(std::ostream& os, const NumericPoint2<T>& obj)
  {
    os << obj.x << obj.y;
    return os;
  }

  template<class T>
  std::istream& operator>>(std::istream& is, NumericPoint2<T>& obj)
  {
    is >> obj.x >> obj.y;
    return is;
  }





  template<class T>
  FORCEINLINE NumericVector4<T> Cross(const NumericVector4<T>& lhs, const NumericVector4<T>& rhs)
  {
    return lhs.Cross(rhs);
  }

  template<typename T, template <typename> class NumericVector, template <typename> class NumericPoint>
  FORCEINLINE T Dot(const NumericVector<T>& lhs, const NumericPoint<T>& rhs)
  {
    return lhs.Dot(rhs);
  }

  template<typename T, template <typename> class NumericVector>
  FORCEINLINE T Dot(const NumericVector<T>& lhs, const NumericVector<T>& rhs)
  {
    return lhs.Dot(rhs);
  }

  template<class NumericVector>
  FORCEINLINE f32 Distance(const NumericVector& lhs, const NumericVector& rhs)
  {
    return rhs.Distance(rhs);
  }

  template<typename NumericVector>
  FORCEINLINE NumericVector Reflect(const NumericVector& normal, const NumericVector& incident)
  {
    return normal.Reflect(incident);
  }

  template<typename NumericVector>
  FORCEINLINE NumericVector Refract(const NumericVector& normal, const NumericVector& incident, const f32 n1, const f32 n2)
  {
    return normal.Refract(incident, n1, n2);
  }
}