/*
*  FILE          Color.cpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for Color structures.
*/
#include "CommonPrecompiled.h"
#include "Color.h"

namespace Math
{
  const LinearColor LinearColor::WHITE(1.0f, 1.0f, 1.0f, 1.0f);
  const LinearColor LinearColor::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
  const LinearColor LinearColor::GREY(0.5f, 0.5f, 0.5f, 1.0f);
  const LinearColor LinearColor::BROWN(0.8f, 0.4f, 0.1f, 1.0f);

  const LinearColor LinearColor::RED(1.0f, 0.0f, 0.0f, 1.0f);
  const LinearColor LinearColor::ORANGE(1.0f, 0.7f, 0.0f, 1.0f);
  const LinearColor LinearColor::YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
  const LinearColor LinearColor::GREEN(0.0f, 1.0f, 0.0f, 1.0f);
  const LinearColor LinearColor::BLUE(0.0f, 0.0f, 1.0f, 1.0f);
  const LinearColor LinearColor::VIOLET(1.0f, 0.2f, 0.7f, 1.0f);

  LinearColor::LinearColor(void)
    : r(0.0f), g(0.0f), b(0.0f), a(1.0f)
  { }

  LinearColor::LinearColor(f32 r_, f32 g_, f32 b_, f32 a_)
    : r(r_), g(g_), b(b_), a(a_)
  { }

  LinearColor::LinearColor(const LinearColor& rhs)
    : r(rhs.r), g(rhs.g), b(rhs.b), a(rhs.a)
  { }

  LinearColor::LinearColor(const Color& rhs)
    : r(rhs.r / 255.0f), g(rhs.g / 255.0f), b(rhs.b / 255.0f), a(rhs.a / 255.0f)
  { }

  LinearColor::LinearColor(const NumericVector4<f32>& rhs)
    : r(rhs.x), g(rhs.y), b(rhs.z), a(rhs.w)
  { }

  LinearColor LinearColor::operator+(const LinearColor& rhs) const
  {
    return LinearColor(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a);
  }

  LinearColor LinearColor::operator-(const LinearColor& rhs) const
  {
    return LinearColor(r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a);
  }

  LinearColor LinearColor::operator*(f32 scalar) const
  {
    return LinearColor(r * scalar, g * scalar, b * scalar, a * scalar);
  }

  LinearColor LinearColor::operator/(f32 scalar) const
  {
    f32 inverse_scalar = 1.0f / scalar;
    return LinearColor(r * inverse_scalar, g * inverse_scalar, b * inverse_scalar, a * inverse_scalar);
  }

  LinearColor& LinearColor::operator=(const LinearColor& rhs)
  {
    r = rhs.r;
    g = rhs.g;
    b = rhs.b;
    a = rhs.a;
    return *this;
  }

  LinearColor& LinearColor::operator+=(const LinearColor& rhs)
  {
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;
    a += rhs.a;
    return *this;
  }

  LinearColor& LinearColor::operator-=(const LinearColor& rhs)
  {
    r -= rhs.r;
    g -= rhs.g;
    b -= rhs.b;
    a -= rhs.a;
    return *this;
  }

  LinearColor& LinearColor::operator*=(f32 scalar)
  {
    r *= scalar;
    g *= scalar;
    b *= scalar;
    a *= scalar;
    return *this;
  }

  LinearColor& LinearColor::operator/=(f32 scalar)
  {
    f32 inverse_scalar = 1.0f / scalar;
    r *= inverse_scalar;
    g *= inverse_scalar;
    b *= inverse_scalar;
    a *= inverse_scalar;
    return *this;
  }

  f32 LinearColor::operator[](u32 n) const
  {
    return v[n];
  }

  f32& LinearColor::operator[](u32 n)
  {
    return v[n];
  }

  std::ostream& operator<<(std::ostream& os, const LinearColor& obj)
  {
    os << obj.r << obj.g << obj.b << obj.a;
    return os;
  }

  std::istream& operator>>(std::istream& is, LinearColor& obj)
  {
    is >> obj.r >> obj.g >> obj.b >> obj.a;
    return is;
  }

  LinearColor& LinearColor::Clamp(f32 min, f32 max)
  {
    r = Math::Clamp(r, min, max);
    g = Math::Clamp(g, min, max);
    b = Math::Clamp(b, min, max);
    a = Math::Clamp(a, min, max);
    return *this;
  }

  LinearColor LinearColor::GetClamped(f32 min, f32 max) const
  {
    return LinearColor(Math::Clamp(r, min, max), Math::Clamp(g, min, max), Math::Clamp(b, min, max), Math::Clamp(a, min, max));
  }

  LinearColor LinearColor::ConvertLinearColorToHSV(void) const
  {
    return LinearColor();
  }

  LinearColor LinearColor::ConvertHSVToLinearColor(void) const
  {
    return LinearColor();
  }

  Color LinearColor::ConvertLinearColorToColor(void) const
  {
    return Color(GetClamped());
  }

  LinearColor LinearColor::Desaturate(f32 factor) const
  {
    return LinearColor();
  }

  LinearColor LinearColor::BuildRandomColor(f32 alpha)
  {
    return LinearColor();
  }




  const Color Color::WHITE(255, 255, 255);
  const Color Color::BLACK(0, 0, 0);
  const Color Color::GREY(128, 128, 128);
  const Color Color::BROWN(210, 105, 30);

  const Color Color::RED(255, 0, 0);
  const Color Color::ORANGE(255, 165, 0);
  const Color Color::YELLOW(255, 255, 0);
  const Color Color::GREEN(0, 255, 0);
  const Color Color::BLUE(0, 0, 255);
  const Color Color::VIOLET(205, 57, 170);

  Color::Color(void)
    : r(0), g(0), b(0), a(255)
  { }

  Color::Color(u08 r_, u08 g_, u08 b_, u08 a_)
    : r(r_), g(g_), b(b_), a(a_)
  { }

  Color::Color(const Color& rhs)
    : r(rhs.r), g(rhs.g), b(rhs.b), a(rhs.a)
  { }

  Color::Color(const LinearColor& rhs)
    : r(Math::Clamp(s32(rhs.r * 255.0f), 0, 255)), g(Math::Clamp(s32(rhs.g * 255.0f), 0, 255)), b(Math::Clamp(s32(rhs.b * 255.0f), 0, 255)), a(Math::Clamp(s32(rhs.a * 255.0f), 0, 255))
  { }

  Color Color::operator+(const Color& rhs) const
  {
    return Color(Clamp(s32(r) + s32(rhs.r), 0, 255),
                 Clamp(s32(g) + s32(rhs.g), 0, 255),
                 Clamp(s32(b) + s32(rhs.b), 0, 255),
                 Clamp(s32(a) + s32(rhs.a), 0, 255));
  }

  Color Color::operator-(const Color& rhs) const
  {
    return Color(Clamp(s32(r) - s32(rhs.r), 0, 255),
                 Clamp(s32(g) - s32(rhs.g), 0, 255),
                 Clamp(s32(b) - s32(rhs.b), 0, 255),
                 Clamp(s32(a) - s32(rhs.a), 0, 255));
  }

  Color& Color::operator=(const Color& rhs)
  {
    r = rhs.r;
    g = rhs.g;
    b = rhs.b;
    a = rhs.a;
    return *this;
  }

  Color& Color::operator+=(const Color& rhs)
  {
    r = Clamp(s32(r) + s32(rhs.r), 0, 255);
    g = Clamp(s32(g) + s32(rhs.g), 0, 255);
    b = Clamp(s32(b) + s32(rhs.b), 0, 255);
    a = Clamp(s32(a) + s32(rhs.a), 0, 255);
    return *this;
  }

  Color& Color::operator-=(const Color& rhs)
  {
    r = Clamp(s32(r) - s32(rhs.r), 0, 255);
    g = Clamp(s32(g) - s32(rhs.g), 0, 255);
    b = Clamp(s32(b) - s32(rhs.b), 0, 255);
    a = Clamp(s32(a) - s32(rhs.a), 0, 255);
    return *this;
  }

  std::ostream& operator<<(std::ostream& os, const Color& obj)
  {
    os << obj.r << obj.g << obj.b << obj.a;
    return os;
  }

  std::istream& operator>>(std::istream& is, Color& obj)
  {
    is >> obj.r >> obj.g >> obj.b >> obj.a;
    return is;
  }

  LinearColor Color::ConvertColorToLinearColor(void) const
  {
    return LinearColor(*this);
  }
}