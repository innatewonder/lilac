#pragma once

namespace Physics
{
  class TransformComponent;
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

    void MakeGround(const Vec3& pos = Vec3(0, -1, 0));

    void AddBody(RigidBody* body);
    void RemoveBody(RigidBody* body);

  private:
    BroadphaseInterface* m_broadInterface;
    DefaultConfig* m_collisionConfig;
    CollisionDispatcher* m_collisionDispatch;
    SequentialImpulseSolver* m_solver;
    DiscreteDynWorld* m_world;

    RigidBody* m_ground;
    CollisionShape* m_shape;
  };
}