#pragma once

namespace Physics
{
  class TransformComponent : public Component
  {
  public:
    TransformComponent();
    ~TransformComponent();

    virtual void Initialize();
    // note - you don't need to call this, collision is set up through collider components
    void Initialize(const RigidBodyInfo& info);

    Vec3 GetPosition() const;
    Quaternion GetRotation() const;

    void SetPosition(const Vec3& pos);
    void SetRotation(const Quaternion& rot);

    RigidBody* GetRigidBody() const;

  private:
    bool CleanUp();

    RigidBody* m_rigidBody;
  };
}
