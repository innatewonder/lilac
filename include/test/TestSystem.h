#pragma once

namespace Test
{
  class TestSystem : public System
  {
  public:
    TestSystem();
    ~TestSystem();

    virtual bool Initialize(ArgParser& args);
    virtual void Destroy();
    virtual void Test();

    virtual void Tick(f32 dt);

    virtual void HandleMessage(Message* msg);

  private:
  };
}
