#include "CommonPrecompiled.h"
#include "ColliderComponent.h"

#include "TransformComponent.h"

namespace Physics
{
  ColliderComponent::ColliderComponent()
    : m_collider(nullptr)
  {}

  ColliderComponent::~ColliderComponent()
  {
    if(m_collider)
      Memory::Delete(m_collider);
  }

  void ColliderComponent::SetCollider(Collider* col, f32 mass)
  {
    if(m_collider)
      Memory::Delete(m_collider);
    m_collider = col;
  }

  void ColliderComponent::AllowCollisions(bool allow)
  {
    AlterState(State::CAN_COLLIDE, allow);
  }

  void ColliderComponent::AllowForces(bool allow)
  {
    AlterState(State::ALLOW_FORCE, allow);
  }

  void ColliderComponent::SetActive(bool active)
  {
    AllowCollisions(active);
    AllowForces(active);
  }

  void ColliderComponent::ApplyImpulse(const Math::Vector3& dir)
  {
    // m_rigidBody->applyCentralImpulse(dir);
  }

  //////////////
  // protected
  void ColliderComponent::AlterState(State s, bool on)
  {
    if(on) 
    {
      m_state |= s;
    }
    else
    {
      m_state &= s;
    }
  }
}
