/*
*  FILE          Color.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for Color class.
*/
#pragma once

#include "Vector.h"

namespace Math
{
  class Color;

  /* 16-byte floating-point RGBA color. High Dynamic Range Support. */
  class LinearColor
  {
    public:
      LinearColor(void);
      LinearColor(f32 r_, f32 g_, f32 b_, f32 a_ = 1.0f);
      LinearColor(const LinearColor& rhs);

      explicit LinearColor(const Color& rhs);
      explicit LinearColor(const NumericVector4<f32>& rhs);

      LinearColor operator+(const LinearColor& rhs) const;
      LinearColor operator-(const LinearColor& rhs) const;
      LinearColor operator*(f32 scalar) const;
      LinearColor operator/(f32 scalar) const;
      LinearColor& operator=(const LinearColor& rhs);
      LinearColor& operator+=(const LinearColor& rhs);
      LinearColor& operator-=(const LinearColor& rhs);
      LinearColor& operator*=(f32 scalar);
      LinearColor& operator/=(f32 scalar);

      f32 operator[](u32 n) const;
      f32& operator[](u32 n);

      friend std::ostream& operator<<(std::ostream& os, const LinearColor& obj);
      friend std::istream& operator>>(std::istream& is, LinearColor& obj);

      LinearColor& Clamp(f32 min = 0.0f, f32 max = 1.0f);
      LinearColor GetClamped(f32 min = 0.0f, f32 max = 1.0f) const;


      LinearColor ConvertLinearColorToHSV(void) const;
      LinearColor ConvertHSVToLinearColor(void) const;
      Color ConvertLinearColorToColor(void) const;
      LinearColor Desaturate(f32 factor) const;

      static LinearColor BuildRandomColor(f32 alpha = 1.0f);

      static const LinearColor WHITE;
      static const LinearColor BLACK;
      static const LinearColor GREY;
      static const LinearColor BROWN;

      static const LinearColor RED;
      static const LinearColor ORANGE;
      static const LinearColor YELLOW;
      static const LinearColor GREEN;
      static const LinearColor BLUE;
      static const LinearColor VIOLET;

      union
      {
        struct { f32 r, g, b, a; };
        f32 v[4];
      };
  };

  /* 4-byte unsigned char RGBA color. Low Dynamic Range Support. */
  class Color
  {
    public:
      Color(void);
      Color(u08 r_, u08 g_, u08 b_, u08 a_ = 255);
      Color(const Color& rhs);

      explicit Color(const LinearColor& rhs);

      Color operator+(const Color& rhs) const;
      Color operator-(const Color& rhs) const;
      Color& operator=(const Color& rhs);
      Color& operator+=(const Color& rhs);
      Color& operator-=(const Color& rhs);

      friend std::ostream& operator<<(std::ostream& os, const Color& obj);
      friend std::istream& operator>>(std::istream& is, Color& obj);

      LinearColor ConvertColorToLinearColor(void) const;

      static const Color WHITE;
      static const Color BLACK;
      static const Color GREY;
      static const Color BROWN;

      static const Color RED;
      static const Color ORANGE;
      static const Color YELLOW;
      static const Color GREEN;
      static const Color BLUE;
      static const Color VIOLET;

      union
      {
        struct { u08 r, g, b, a; };
        u08 v[4];
      };
  };
}