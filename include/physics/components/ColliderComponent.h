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

    void SetCollider(Collider* col, f32 mass);

    void AllowCollisions(bool allow = true);
    void AllowForces(bool allow = true);
    void SetActive(bool active = true); // sets both collisions and forces

    // applies to collider origin
    void ApplyImpulse(const Math::Vector3& dir);

  protected:
    enum State {
      CAN_COLLIDE = 0x01,
      ALLOW_FORCE = 0x10,
    };

    void AlterState(State s, bool on);

    u32 m_state;
    Collider* m_collider;
  };
}