/*
 *  FILE          Vector.h
 *  AUTHOR        Brendon Clifford
 *  DESCRIPTION
 *    Declaration for Vector Template class.
 */
#pragma once

const u32 X = 0;
const u32 Y = 1;
const u32 Z = 2;
const u32 W = 3;

namespace Math
{
  template<class T, u32 N>
  class NumericVectorN
  {
    public:
      T v[N];
  };

  template<class T>
  class NumericVector2
  {
    public:
      NumericVector2(T x_ = T(0), T y_ = T(0));
      NumericVector2(const NumericVector2<T>& rhs);

      f32 Distance(const NumericVector2<T>& point) const;
      NumericVector2<T> Midpoint(const NumericVector2<T>& point) const;

      T Dot(const NumericVector2<T>& rhs) const;
      T Cross(const NumericVector2<T>& rhs) const;
      NumericVector2<T> Reflect(const NumericVector2<T>& incident) const;
      NumericVector2<T> Refract(const NumericVector2<T>& incident, const f32 n1, const f32 n2) const;

      bool IsZero(void) const;
      bool IsParallel(const NumericVector2<T>& rhs) const;
      bool IsOrthogonal(const NumericVector2<T>& rhs) const;

      f32 Length(void) const;
      T LengthSquared(void) const;

      NumericVector2<T>& Normalize(void);

      NumericVector2<T> operator-(void) const;
      NumericVector2<T> operator+(const NumericVector2<T>& rhs) const;
      NumericVector2<T> operator-(const NumericVector2<T>& rhs) const;
      NumericVector2<T> operator*(T scalar) const;
      NumericVector2<T> operator/(T scalar) const;
      NumericVector2<T>& operator=(const NumericVector2<T>& rhs);
      NumericVector2<T>& operator+=(const NumericVector2<T>& rhs);
      NumericVector2<T>& operator-=(const NumericVector2<T>& rhs);
      NumericVector2<T>& operator*=(T scalar);
      NumericVector2<T>& operator/=(T scalar);

      T operator[](u32 n) const;
      T& operator[](u32 n);

      bool operator==(const NumericVector2<T>& rhs) const;
      bool operator!=(const NumericVector2<T>& rhs) const;

      template<class I>
      friend std::ostream& operator<<(std::ostream& os, const NumericVector2<I>& obj);

      template<class I>
      friend std::istream& operator>>(std::istream& is, NumericVector2<I>& obj);

      static const NumericVector2<T> ZERO;
      static const NumericVector2<T> ONE;
      static const NumericVector2<T> UNIT_X;
      static const NumericVector2<T> UNIT_Y;

    private:

      template<u32 a, u32 b>
      class NumericVector2Swizzle
      {
        public:
          NumericVector2<T>& operator=(const NumericVector2<T>& rhs);
          operator NumericVector2<T>();

        private:
          T v[2];
      };

    public:

      template<u32 a, u32 b> NumericVector2<T> Swizzle(void) const;

      union
      {
        struct { T x, y; };
        struct { T min, max; };
        T v[2];
        NumericVector2Swizzle<0, 0> xx;
        NumericVector2Swizzle<0, 1> xy;
        NumericVector2Swizzle<1, 0> yx;
        NumericVector2Swizzle<1, 1> yy;
      };
  };

  typedef NumericVector2<f32> Vector2;

  
  


  template<class T>
  class NumericVector3
  {
    public:
      NumericVector3(T x_ = T(0), T y_ = T(0), T z_ = T(0));
      NumericVector3(const NumericVector3<T>& rhs);

      T Dot(const NumericVector3<T>& rhs) const;
      NumericVector3<T> Cross(const NumericVector3<T>& rhs) const;
      NumericVector3<T> Reflect(const NumericVector3<T>& incident) const;
      NumericVector3<T> Refract(const NumericVector3<T>& incident, const f32 n1, const f32 n2) const;

      bool IsZero(void) const;
      bool IsParallel(const NumericVector3<T>& rhs) const;
      bool IsOrthogonal(const NumericVector3<T>& rhs) const;

      f32 Length(void) const;
      T LengthSquared(void) const;

      NumericVector3<T>& Normalize(void);

      NumericVector3<T> operator-(void) const;
      NumericVector3<T> operator+(const NumericVector3<T>& rhs) const;
      NumericVector3<T> operator-(const NumericVector3<T>& rhs) const;
      NumericVector3<T> operator*(T scalar) const;
      NumericVector3<T> operator/(T scalar) const;
      NumericVector3<T>& operator=(const NumericVector3<T>& rhs);
      NumericVector3<T>& operator+=(const NumericVector3<T>& rhs);
      NumericVector3<T>& operator-=(const NumericVector3<T>& rhs);
      NumericVector3<T>& operator*=(T scalar);
      NumericVector3<T>& operator/=(T scalar);

      T operator[](u32 n) const;
      T& operator[](u32 n);

      bool operator==(const NumericVector3<T>& rhs) const;
      bool operator!=(const NumericVector3<T>& rhs) const;

      template<class I>
      friend std::ostream& operator<<(std::ostream& os, const NumericVector3<I>& obj);

      template<class I>
      friend std::istream& operator>>(std::istream& is, NumericVector3<I>& obj);

      static const NumericVector3<T> ZERO;
      static const NumericVector3<T> ONE;
      static const NumericVector3<T> UNIT_X;
      static const NumericVector3<T> UNIT_Y;
      static const NumericVector3<T> UNIT_Z;

    private:

      template<u32 a = 0, u32 b = 0, u32 c = 0>
      class NumericVector3Swizzle
      {
        public:
          NumericVector3<T>& operator=(const NumericVector2<T>& rhs);
          operator NumericVector2<T>();

          NumericVector3<T>& operator=(const NumericVector3<T>& rhs);
          operator NumericVector3<T>();

        private:
          T v[3];
      };

    public:

      template<u32 a, u32 b>
      NumericVector2<T> Swizzle(void) const;

      template<u32 a, u32 b, u32 c>
      NumericVector3<T> Swizzle(void) const;

      union
      {
        struct { T x, y, z; };
        T v[3];
        NumericVector3Swizzle<0, 1, 2> xyz;
        NumericVector3Swizzle<2, 1, 0> zyx;
        NumericVector3Swizzle<0, 1> xy;
        NumericVector3Swizzle<1, 2> yz;
        NumericVector3Swizzle<0, 2> xz;
      };
  };

  typedef NumericVector3<f32> Vector3;

  


  template<class T>
  class NumericVector4
  {
    public:
      NumericVector4(T x_ = T(0), T y_ = T(0), T z_ = T(0), T w_ = T(0));
      NumericVector4(const NumericVector4<T>& rhs);
      explicit NumericVector4(const NumericVector3<T>& rhs, T w_ = T(0));

      T Dot(const NumericVector4<T>& rhs) const;
      NumericVector4<T> Cross(const NumericVector4<T>& rhs) const;
      NumericVector4<T> Reflect(const NumericVector4<T>& incident) const;
      NumericVector4<T> Refract(const NumericVector4<T>& incident, const f32 n1, const f32 n2) const;

      bool IsZero(void) const;
      bool IsParallel(const NumericVector4<T>& rhs) const;
      bool IsOrthogonal(const NumericVector4<T>& rhs) const;

      void BuildOrthonormalBasis(NumericVector4<T>& u, NumericVector4<T>& v);

      f32 Length(void) const;
      T LengthSquared(void) const;

      NumericVector4<T>& Normalize(void);

      NumericVector4<T> operator-(void) const;
      NumericVector4<T> operator+(const NumericVector4<T>& rhs) const;
      NumericVector4<T> operator-(const NumericVector4<T>& rhs) const;
      NumericVector4<T> operator*(T scalar) const;
      NumericVector4<T> operator/(T scalar) const;
      NumericVector4<T>& operator=(const NumericVector4<T>& rhs);
      NumericVector4<T>& operator+=(const NumericVector4<T>& rhs);
      NumericVector4<T>& operator-=(const NumericVector4<T>& rhs);
      NumericVector4<T>& operator*=(T scalar);
      NumericVector4<T>& operator/=(T scalar);

      T operator[](u32 n) const;
      T& operator[](u32 n);

      bool operator==(const NumericVector4<T>& rhs) const;
      bool operator!=(const NumericVector4<T>& rhs) const;

      template<class I>
      friend std::ostream& operator<<(std::ostream& os, const NumericVector4<I>& obj);

      template<class I>
      friend std::istream& operator>>(std::istream& is, NumericVector4<I>& obj);

      static const NumericVector4<T> ZERO;
      static const NumericVector4<T> ONE;
      static const NumericVector4<T> UNIT_X;
      static const NumericVector4<T> UNIT_Y;
      static const NumericVector4<T> UNIT_Z;
      static const NumericVector4<T> UNIT_W;

    private:

      template<u32 a = 0, u32 b = 0, u32 c = 0, u32 d = 0>
      class NumericVector4Swizzle
      {
        public:
          NumericVector4<T>& operator=(const NumericVector2<T>& rhs);
          operator NumericVector2<T>();

          NumericVector4<T>& operator=(const NumericVector3<T>& rhs);
          operator NumericVector3<T>();

          NumericVector4<T>& operator=(const NumericVector4<T>& rhs);
          operator NumericVector4<T>();

        private:
          T v[4];
      };

    public:
      template<u32 a, u32 b>
      NumericVector2<T> Swizzle(void) const;

      template<u32 a, u32 b, u32 c>
      NumericVector3<T> Swizzle(void) const;

      template<u32 a, u32 b, u32 c, u32 d>
      NumericVector4<T> Swizzle(void) const;

      union
      {
        struct { T x, y, z, w; };
        T v[4];
        NumericVector4Swizzle<0, 1, 2, 3> xyzw;
        NumericVector4Swizzle<3, 2, 1, 0> wzyx;
        NumericVector4Swizzle<0, 1, 2> xyz;
        NumericVector4Swizzle<0, 1> xy;
        NumericVector4Swizzle<1, 2> yz;
        NumericVector4Swizzle<2, 3> zw;
      };
  };

  typedef NumericVector4<f32> Vector4;
  

  template<class T>
  class NumericPoint4 : public NumericVector4<T>
  {
    public:
      NumericPoint4(T x_ = T(0), T y_ = T(0), T z_ = T(0), T w_ = T(1));

      f32 Distance(const NumericPoint4<T>& rhs) const;
      NumericPoint4<T> Midpoint(const NumericPoint4<T>& rhs) const;

      NumericPoint4<T> operator+(const NumericVector4<T>& rhs) const;
      NumericPoint4<T> operator+(const NumericPoint4<T>& rhs) const = delete;

      NumericPoint4<T> operator-(const NumericVector4<T>& rhs) const;
      NumericVector4<T> operator-(const NumericPoint4<T>& rhs) const;

      NumericPoint4<T>& operator+=(const NumericVector4<T>& rhs);
      NumericPoint4<T>& operator-=(const NumericVector4<T>& rhs);

      template<class I>
      friend std::ostream& operator<<(std::ostream& os, const NumericPoint4<I>& obj);

      template<class I>
      friend std::istream& operator>>(std::istream& is, NumericPoint4<I>& obj);

      static const NumericPoint4<T> ORIGIN;
  };
  typedef NumericPoint4<f32> Point4;


  template<class T>
  class NumericPoint2 : public NumericVector2<T>
  {
    public:
      NumericPoint2(T x_ = T(0), T y_ = T(0));

      f32 Distance(const NumericPoint2<T>& rhs) const;
      NumericPoint2<T> Midpoint(const NumericPoint2<T>& rhs) const;

      NumericPoint2<T> operator+(const NumericVector2<T>& rhs) const;
      NumericPoint2<T> operator+(const NumericPoint2<T>& rhs) const = delete;

      NumericPoint2<T> operator-(const NumericVector2<T>& rhs) const;
      NumericVector2<T> operator-(const NumericPoint2<T>& rhs) const;

      NumericPoint2<T>& operator+=(const NumericVector2<T>& rhs);
      NumericPoint2<T>& operator-=(const NumericVector2<T>& rhs);

      template<class I>
      friend std::ostream& operator<<(std::ostream& os, const NumericPoint2<I>& obj);

      template<class I>
      friend std::istream& operator>>(std::istream& is, NumericPoint2<I>& obj);

      static const NumericPoint2<T> ORIGIN;
  };
  typedef NumericPoint2<f32> Point2;

  template<class T>
  FORCEINLINE NumericVector4<T> Cross(const NumericVector4<T>& lhs, const NumericVector4<T>& rhs);
  
  template<typename T, template <typename> class NumericVector, template <typename> class NumericPoint>
  FORCEINLINE T Dot(const NumericVector<T>& lhs, const NumericPoint<T>& rhs);

  template<typename T, template <typename> class NumericVector>
  FORCEINLINE T Dot(const NumericVector<T>& lhs, const NumericVector<T>& rhs);

  template<class NumericVector>
  FORCEINLINE f32 Distance(const NumericVector& lhs, const NumericVector& rhs);

  template<typename NumericVector>
  FORCEINLINE NumericVector Reflect(const NumericVector& normal, const NumericVector& incident);

  template<typename NumericVector>
  FORCEINLINE NumericVector Refract(const NumericVector& normal, const NumericVector& incident, const f32 n1, const f32 n2);
}



#include "Vector.hpp"
