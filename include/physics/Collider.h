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

    Collider(Type t = C_EMPTY);
    ~Collider();

    //do not call this constructor
    Collider(Type t, bool wasCalled);

    CollisionShape* shape;
    Type type;
  };

  class CubeCollider : public Collider
  {
  public:
    CubeCollider(const Vec3& halfLens = Vec3(1, 1, 1))
      : Collider(Collider::C_CUBE), axis(halfLens)
    {}

    CubeCollider(const Vec3& halfLens, bool called)
      : Collider(Collider::C_CUBE, called), axis(halfLens)
    {}
    
    Vec3 axis;
  };

  class SphereCollider : public Collider
  {
  public:
    SphereCollider(f32 radius = 1)
      : Collider(Collider::C_SPHERE), rad(radius) 
    {}

    SphereCollider(f32 radius, bool called)
      : Collider(Collider::C_SPHERE, called), rad(radius) 
    {}

    f32 rad;
  };

  class CapsuleCollider : public Collider
  {
  public:
    CapsuleCollider(f32 radius = 1, f32 height = 1)
      : Collider(Collider::C_CAPSULE)
      , rad(radius), ht(height)
    {}

    CapsuleCollider(f32 radius, f32 height, bool called)
      : Collider(Collider::C_CAPSULE, called)
      , rad(radius), ht(height)
    {}
    f32 rad;
    f32 ht;
  };

  class CollisionShapeManager
  {
  public:
    ~CollisionShapeManager();
    
    CollisionShape* GetEmptyShape();
    void SetColliderShape(Collider* col);
    void ClearAllShapes();

  private:
    CollisionShape* NewCollider(Collider* c, CollisionShape* shape);
    CollisionShape* Loop(const std::function<bool(Collider*)>& fcn, 
      const std::function<CollisionShape*(void)>& makeFunc);

    Containers::List<Collider*> m_colliders;
  };
  extern CollisionShapeManager* gCollisionShapeMgr;
}
