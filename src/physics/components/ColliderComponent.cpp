#include "CommonPrecompiled.h"
#include "ColliderComponent.h"

#include "TransformComponent.h"

namespace Physics
{
  ColliderComponent::ColliderComponent()
    : m_rigidBody(nullptr), m_collider(nullptr)
  {}

  ColliderComponent::~ColliderComponent()
  {
   //dont clean up rigidbody, transform owns it
    if(m_collider)
      Memory::Delete(m_collider);
  }

  RigidBody* ColliderComponent::GetRigidBody() const
  {
    return m_rigidBody;
  }

  void ColliderComponent::SetCollider(Collider* col, f32 mass, const Vec3& pos, const Quaternion& rot)
  {
    if(m_collider)
      Memory::Delete(m_collider);
    m_collider = col;

    Vec3 fallInertia = Vec3(0, 0, 0);
    col->shape->calculateLocalInertia(mass, fallInertia);
    
    DefaultMotionState* motionState = Memory::New<DefaultMotionState>(Transform(rot, pos));
    RigidBodyInfo info(mass, motionState, col->shape, fallInertia);

    Init(info);
  }

  void ColliderComponent::AllowCollisions(bool allow)
  {
    int flags = m_rigidBody->getCollisionFlags();
    if(allow)
    {
      flags |= btCollisionObject::CF_NO_CONTACT_RESPONSE;
    }
    else
    {
      flags &= ~btCollisionObject::CF_NO_CONTACT_RESPONSE;
    }
    m_rigidBody->setCollisionFlags(flags);
  }

  void ColliderComponent::AllowForces(bool allow)
  {
    m_rigidBody->activate(allow);
  }

  void ColliderComponent::TurnOn(bool on)
  {
    AllowCollisions(on);
    AllowForces(on);
  }

  void ColliderComponent::ApplyImpulse(const Vec3& dir)
  {
    m_rigidBody->applyCentralImpulse(dir);
  }

  //////////////
  // protected
  void ColliderComponent::Init(const RigidBodyInfo& info)
  {
    // For this to work correctly, 
    //it must be made through an object that has a transform
    assertion(m_parent);
    Component* c = GetParent()->GetComponent(Comp::TransformComponent);
    assertion(c);
    TransformComponent* tran = RECAST(TransformComponent*, c);

    tran->Initialize(info);
    m_rigidBody = tran->GetRigidBody();
  }
}
