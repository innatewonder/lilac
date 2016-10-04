#pragma once

namespace Physics
{
  class Collider
  {
  public:
    enum Type
    {
      C_EMPTY,
      C_CUBE,
      C_SPHERE,
      C_CAPSULE,
      C_NUM_TYPES
    };

    Collider(Type t = C_EMPTY)
      : m_type(t)
    {}

    Type GetType() 
    {
      return m_type;
    }

  private:
    Type m_type;
  };

  class CubeCollider : public Collider
  {
  public:
    CubeCollider(const Math::Vector3& halfLens = Math::Vector3::ONE)
      : Collider(Collider::C_CUBE), m_axis(halfLens)
    {}

  private:
    Math::Vector3 m_axis;
  };

  class SphereCollider : public Collider
  {
  public:
    SphereCollider(f32 radius = 1)
      : Collider(Collider::C_SPHERE), m_radius(radius) 
    {}

  private:
    f32 m_radius;
  };

  class CapsuleCollider : public Collider
  {
  public:
    CapsuleCollider(f32 radius = 1, f32 height = 1)
      : Collider(Collider::C_CAPSULE), m_radius(radius), m_height(height)
    {}

  private:
    f32 m_radius;
    f32 m_height;
  };
}
