#pragma once

namespace Physics
{
  class PhysicsSystem : public System
  {
  public:
    PhysicsSystem();
    ~PhysicsSystem();

    virtual bool Initialize(ArgParser& args);
    virtual void Destroy();
    virtual void Test();

    virtual void Tick(f32 dt);
    virtual void RegisterComponent(Component* comp);
    virtual void UnregisterComponent(Component* comp);

    virtual void HandleMessage(Message* msg);

    // void AddBody(RigidBody* body);
    // void RemoveBody(RigidBody* body);

  private:
  };
}