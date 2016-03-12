/*
*  FILE          MathRandom.hpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for random functions.
*/

namespace Math
{
  template <typename T>
  inline T Random(const T &min, const T &max)
  {
    return T(min + ((max - min) * Random()));
  }

  template <>
  inline s32 Random(const s32 &min, const s32 &max)
  {
    return Round(min + ((max - min) * Random()));
  }

  template <>
  inline u32 Random(const u32 &min, const u32 &max)
  {
    return Round(min + ((max - min) * Random()));
  }

  inline f32 Random(void)
  {
    return f32(rand()) / f32(RAND_MAX);
  }

  namespace Gaussian
  {
    inline f32 RandomCentralLimitTheorem(f32 mean, f32 variance)
    {
      static u32 N = 100;

      f32 X = 0.0f;
      for(u32 i = 0; i < N; ++i)
        X += Math::Random();

      X -= f32(N) * 0.5f;
      X *= sqrt(12.0f / f32(N));

      return mean + sqrt(variance) * X;
    }
  }
}