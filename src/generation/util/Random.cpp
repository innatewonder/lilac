#include "CommonPrecompiled.h"
#include "Random.h"

namespace Generation
{
  u32 toU32(u64 num)
  {
    return 0xFFFFFFFF & num;
  }

////////////////////
//XOR
  void Xor128::Initialize(u32 seed)
  {
    m_x = 123456789;
    m_y = 362436069;
    m_z = 521288629;
    m_seed = seed; // 88675123
  }

  u32 Xor128::Get()
  {
    u32 t = m_x ^ (m_x << 11);
    m_x = m_y; m_y = m_z; m_z = m_seed;
    return m_seed = m_seed ^ (m_seed >> 19) ^ (t ^ (t >> 8));
  }

//////////////////
// TWISTER    
  void MersenneTwister::Initialize(u32 seed)
  {
    twisterIndex = 0;
    twisterState[0] = seed;
    for(u64 i = 0; i < 623; ++i)
    {
      twisterState[i] = toU32((1812433253 * (twisterState[i - 1] ^ twisterState[i - 1] >> 30) + i));
    }
  }

  u32 MersenneTwister::Get()
  {
    if(twisterIndex == 0)
    {
      Generate();
    }

    u64 y = twisterState[twisterIndex];
    y = y ^ y >> 11;
    y = y ^ y << 7 & 2636928640; // 0x9d2c5680
    y = y ^ y << 15 & 4022730752; // 0xefc60000
    y = y ^ y >> 18;

    twisterIndex = (twisterIndex + 1) % 624;
    return toU32(y);
  }

  void MersenneTwister::Generate() 
  {
    for(u64 i = 0; i < 623; ++i)
    {
      u32 y = toU32((twisterState[i] & 0x80000000) // bit 31 (32nd bit) of twisterState[i]
             + (twisterState[(i + 1) % 624] & 0x7fffffff));   // bits 0-30 (first 31 bits) of twisterState[...]
      twisterState[i] = twisterState[(i + 397) % 624] ^ y >> 1;

      if((y % 2) != 0)
      { // y is odd
          twisterState[i] = twisterState[i] ^ (2567483615); // 0x9908b0df
      }
    }
  }
TODO("Perhaps dont make generation into classes, virtual table causes noticable slowdown in tests (~2-3 ms)");
//////////////
// RANDOM
  Random::Random()
    : m_seed(88675123),
    m_generator(Memory::New<MersenneTwister>())
  {
    m_generator->Initialize(m_seed);
  }

  Random::~Random()
  {
    Memory::Delete(m_generator);
  }

  void Random::SetSeed(u32 seed)
  {
    m_seed = seed;
    m_generator->Initialize(m_seed);
  }

  u32 Random::Seed() const
  {
    return m_seed;
  }

  u32 Random::operator()()
  {
    return Get();
  }

  u32 Random::Get()
  {
    m_last = m_generator->Get();
    return m_last;
  }

  u32 Random::Get(u32 min, u32 max)
  {
    return (Get() % (max - min)) + min;
  }

  f32 Random::Getf()
  {
    return SCAST(f32, (Get() % 100)) / 100;
  }

  u32 Random::GetLast() const
  {
    return m_last;
  }
}