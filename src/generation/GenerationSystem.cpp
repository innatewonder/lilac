#include "CommonPrecompiled.h"
#include "GenerationSystem.h"

namespace Generation
{
  void Hexagon(s32 h1, s32 h2, s32 h3, s32 h4, s32 h5, s32 h6)
  {

  }


  GenerationSystem::GenerationSystem()
  {}

  GenerationSystem::~GenerationSystem()
  {}

  bool GenerationSystem::Initialize(ArgParser& args)
  {
    return true;
  }

  void GenerationSystem::Destroy()
  {}

  void GenerationSystem::Test()
  {
    Hexagon(0, 0, 0, 0, 0, 0);
  }

  void GenerationSystem::Tick(f32 dt)
  {}

  void GenerationSystem::HandleMessage(Message* msg)
  {}

  void GenerationSystem::SetSeed(u32 seed)
  {
    m_random.SetSeed(seed);
  }

  u32 GenerationSystem::Seed() const
  {
    return m_random.Seed();
  }

}