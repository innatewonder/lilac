#include "CommonPrecompiled.h"
#include "BulletIncludes.h"
#include "PhysicsSystem.h"

#include "ColliderComponent.h"
#include "TransformComponent.h"

namespace Physics
{
  PhysicsSystem::PhysicsSystem()
  {}

  PhysicsSystem::~PhysicsSystem()
  {}

  bool PhysicsSystem::Initialize(ArgParser& args)
  {
    m_ground = nullptr;
    gCollisionShapeMgr = Memory::New<CollisionShapeManager>();

    m_broadInterface = Memory::New<btDbvtBroadphase>();

    m_collisionConfig = Memory::New<DefaultConfig>();
    m_collisionDispatch = Memory::New<CollisionDispatcher>(m_collisionConfig);

    m_solver = Memory::New<SequentialImpulseSolver>();

    m_world = new DiscreteDynWorld(m_collisionDispatch, m_broadInterface, m_solver, m_collisionConfig);
    m_world->setGravity(btVector3(0, -10, 0));
    return true;
  }

  void  PhysicsSystem::Destroy()
  {
    if(m_ground)
    {
      RemoveBody(m_ground);
      Memory::Delete(m_ground->getMotionState());
      Memory::Delete(m_ground);
      Memory::Delete(m_shape);
    }

    Memory::Delete(gCollisionShapeMgr);

    delete m_world;
    Memory::Delete(m_solver);
    Memory::Delete(m_collisionConfig);
    Memory::Delete(m_collisionDispatch);
    Memory::Delete(m_broadInterface);
  }

  void PhysicsSystem::Test()
  {
    // Object* obj = Factory::MakeObject();
    // // make ball
    // obj->AddComponent(Comp::TransformComponent);
    // ColliderComponent* col = RECAST(ColliderComponent*, obj->AddComponent(Comp::ColliderComponent));
    // col->SetCollider(Memory::New<SphereCollider>(), 1);
  }

  void PhysicsSystem::Tick(f32 dt)
  {
    m_world->stepSimulation(dt, 10);
  }

  void PhysicsSystem::HandleMessage(Message* msg)
  {
  }

  void PhysicsSystem::RegisterComponent(Component* comp)
  {
    System::RegisterComponent(comp);

    if(comp->GetTypeID() == Comp::TransformComponent)
    {
      TransformComponent* trans = RECAST(TransformComponent*, comp);
      AddBody(trans->GetRigidBody());
    }
  }

  void PhysicsSystem::UnregisterComponent(Component* comp)
  {
    System::UnregisterComponent(comp);

    if(comp->GetTypeID() == Comp::TransformComponent)
    {
      TransformComponent* trans = RECAST(TransformComponent*, comp);
      RemoveBody(trans->GetRigidBody());
    }
  }

  void PhysicsSystem::AddBody(RigidBody* body)
  {
    if(body)
      m_world->addRigidBody(body);
  }

  void PhysicsSystem::RemoveBody(RigidBody* body)
  {
    if(body)
      m_world->removeRigidBody(body);
  }

  void PhysicsSystem::MakeGround(const Vec3& pos)
  {
    m_shape = Memory::New<StaticPlaneShape>(Vec3(0, 1, 0), 1.f);
    DefaultMotionState* groundMotionState = Memory::New<DefaultMotionState>(Transform(Quaternion(0, 0, 0, 1), pos));
    RigidBodyInfo info(0, groundMotionState, m_shape, Vec3(0, 0, 0));
    m_ground = Memory::New<RigidBody>(info);

    AddBody(m_ground);
  }

}
