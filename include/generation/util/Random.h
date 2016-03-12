#pragma once

namespace Generation
{
  class RandomGenerator
  {
  public:
    virtual void Initialize(u32 seed) = 0;
    virtual u32 Get() = 0;
  };

  class Xor128 : public RandomGenerator
  {
  public:
    virtual void Initialize(u32 seed);
    virtual u32 Get();
  private:
    u32 m_x;
    u32 m_y;
    u32 m_z;
    u32 m_seed;
  };

  class MersenneTwister : public RandomGenerator
  {
  public:
    virtual void Initialize(u32 seed);
    virtual u32 Get();
  private:
    void Generate();
    u64 twisterState[623];
    u64 twisterIndex;
  };

  class Random
  {
  private:
    typedef u32 (*Generator)(u32 seed, u32 last);

  public:
    Random();
    ~Random();

    void SetSeed(u32 seed);
    u32 Seed() const;

    u32 operator()();
    u32 Get();
    u32 Get(u32 min, u32 max);

    // 0-1
    f32 Getf();
    u32 GetLast() const;

  private:
    RandomGenerator* m_generator;
    u32 m_seed;
    u32 m_last;
  };
}
