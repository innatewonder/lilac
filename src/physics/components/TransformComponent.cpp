#include "CommonPrecompiled.h"
#include "TransformComponent.h"
#include "Collider.h"

namespace Physics
{
  TransformComponent::TransformComponent()
    : m_rigidBody(nullptr)
  {
  }

  TransformComponent::~TransformComponent()
  {
    CleanUp();
  }

  void TransformComponent::Initialize()
  {
    //default to having a sphere of radius 1 with 0 mass at the origin (ground plane is at -1)
    CollisionShape* fallShape = Physics::gCollisionShapeMgr->GetEmptyShape();
    DefaultMotionState* fallMotionState = Memory::New<DefaultMotionState>(Transform(Quaternion(0, 0, 0, 1), Vec3(0, -1, 0)));
    RigidBodyInfo info(0, fallMotionState, fallShape, Vec3(0, 0, 0));
    
    Initialize(info);

    //default to no collisions no gravity
    m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() |
      btCollisionObject::CF_NO_CONTACT_RESPONSE);
    m_rigidBody->activate(false);
  }

  void TransformComponent::Initialize(const RigidBodyInfo& info)
  {
    bool shouldAdd = CleanUp();

    m_rigidBody = Memory::New<RigidBody>(info);

    if(shouldAdd)
      GETSYSTEM(PhysicsSystem)->AddBody(m_rigidBody);
  }

  RigidBody* TransformComponent::GetRigidBody() const
  {
    return m_rigidBody;
  }

  Vec3 TransformComponent::GetPosition() const
  {
    Transform trans;
    m_rigidBody->getMotionState()->getWorldTransform(trans);
    return trans.getOrigin();
  }

  Quaternion TransformComponent::GetRotation() const
  {
    Transform trans;
    m_rigidBody->getMotionState()->getWorldTransform(trans);
    return trans.getRotation();
  }

  void TransformComponent::SetPosition(const Vec3& pos)
  {
    Transform trans(GetRotation(), pos);
    m_rigidBody->setCenterOfMassTransform(trans);
  }

  void TransformComponent::SetRotation(const Quaternion& rot)
  {
    Transform trans(rot, GetPosition());
    m_rigidBody->setCenterOfMassTransform(trans);
  }

  ////////////////////////////////
  // PRIVATE
  bool TransformComponent::CleanUp()
  {
    if(m_rigidBody)
    {
      GETSYSTEM(PhysicsSystem)->RemoveBody(m_rigidBody);
      Memory::Delete(m_rigidBody->getMotionState());
      Memory::Delete(m_rigidBody);
      return true;
    }
    return false;
  }
}