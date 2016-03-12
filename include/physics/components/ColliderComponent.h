#pragma once

/******************************

Units of measurement

Length: meters
Mass: kilograms
Time: seconds

******************************/
#include "Collider.h"

namespace Physics
{
  class ColliderComponent : public Component
  {
  public:
    ColliderComponent();
    ~ColliderComponent();

    virtual void Initialize() {};

    void SetCollider(Collider* col, f32 mass, 
      const Vec3& pos = Vec3(0, 0, 0), 
      const Quaternion& rot = Quaternion(0, 0, 0, 1));

    void AllowCollisions(bool allow = true);
    void AllowForces(bool allow = true);
    void TurnOn(bool on = true); // sets both collisions and forces

    // applies to collider origin
    void ApplyImpulse(const Vec3& dir);

    RigidBody* GetRigidBody() const;

  protected:
    void Init(const RigidBodyInfo& info);

    RigidBody* m_rigidBody;
    Collider* m_collider;
  };
}