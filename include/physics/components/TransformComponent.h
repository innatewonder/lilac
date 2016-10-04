#pragma once

namespace Physics
{
  class TransformComponent : public Component
  {
  public:
    TransformComponent();
    ~TransformComponent();

    virtual void Initialize();

    Math::Vector3 GetPosition() const;
    Math::Quaternion GetRotation() const;

    void SetPosition(const Math::Vector3& pos);
    void SetRotation(const Math::Quaternion& rot);

  private:
    Math::Quaternion m_rot;
    Math::Vector3 m_pos;
  };
}
