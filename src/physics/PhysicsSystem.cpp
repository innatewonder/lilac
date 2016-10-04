#include "CommonPrecompiled.h"
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
    return true;
  }

  void  PhysicsSystem::Destroy()
  {
  }

  void PhysicsSystem::Test()
  {
  }

  void PhysicsSystem::Tick(f32 dt)
  {
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
      // AddBody(trans->GetRigidBody());
    }
  }

  void PhysicsSystem::UnregisterComponent(Component* comp)
  {
    System::UnregisterComponent(comp);

    if(comp->GetTypeID() == Comp::TransformComponent)
    {
      TransformComponent* trans = RECAST(TransformComponent*, comp);
      // RemoveBody(trans->GetRigidBody());
    }
  }

  // void PhysicsSystem::AddBody(RigidBody* body)
  // {
  //   if(body)
  //     m_world->addRigidBody(body);
  // }

  // void PhysicsSystem::RemoveBody(RigidBody* body)
  // {
  //   if(body)
  //     m_world->removeRigidBody(body);
  // }

}
