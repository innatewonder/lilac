#pragma once
#include "Random.h"

namespace Generation
{
  class GenerationSystem : public System
  {
  public:
    GenerationSystem();
    ~GenerationSystem();

    virtual bool Initialize(ArgParser& args);
    virtual void Destroy();
    virtual void Test();
    virtual void Tick(f32 dt);
    virtual void HandleMessage(Message* msg);

    void SetSeed(u32 seed);
    u32 Seed() const;

  private:
    Random m_random;
  };
}
