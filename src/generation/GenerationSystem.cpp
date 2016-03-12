#include "CommonPrecompiled.h"
#include "GenerationSystem.h"

namespace Generation
{
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
  {}

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