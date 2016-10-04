#include "CommonPrecompiled.h"
#include "TransformComponent.h"

namespace Physics
{
  TransformComponent::TransformComponent()
  {
  }

  TransformComponent::~TransformComponent()
  {
  }

  void TransformComponent::Initialize()
  {
  }

  Math::Vector3 TransformComponent::GetPosition() const
  {
    return m_pos;
  }

  Math::Quaternion TransformComponent::GetRotation() const
  {
    return m_rot;
  }

  void TransformComponent::SetPosition(const Math::Vector3& pos)
  {
    m_pos = pos;
  }

  void TransformComponent::SetRotation(const Math::Quaternion& rot)
  {
    m_rot = rot;
  }
}