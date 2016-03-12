#include "CommonPrecompiled.h"
#include "Collider.h"

namespace Physics
{
  CollisionShapeManager* gCollisionShapeMgr = nullptr;

  CollisionShapeManager::~CollisionShapeManager()
  {
    ClearAllShapes();
  }

  void CollisionShapeManager::SetColliderShape(Collider* col)
  {
    switch(col->type)
    {
      case Collider::C_EMPTY:
      {
        col->shape = 
        Loop([](Collider* c)->bool{return c->type == Collider::C_EMPTY;},
          [=]()->CollisionShape*{
            auto toSave = Memory::New<Collider>(Collider::C_EMPTY, false);
            return this->NewCollider(toSave, Memory::New<btEmptyShape>());
          });
      }
      break;
      case Collider::C_CUBE:
      {
        CubeCollider* cube = RECAST(CubeCollider*, col);
        col->shape = 
        Loop([=](Collider* c)->bool
          {
            if(c->type == Collider::C_CUBE)
            {
              CubeCollider* tst = RECAST(CubeCollider*, c);
              return tst->axis == cube->axis;
            }
            return false;
          },
          [=]()->CollisionShape*
          {
            auto toSave = Memory::New<CubeCollider>(cube->axis, false);
            return this->NewCollider(toSave, Memory::New<CubeShape>(cube->axis));
          }
        );
      }
      break;
      case Collider::C_SPHERE:
      {
        SphereCollider* sphere = RECAST(SphereCollider*, col);
        col->shape = 
        Loop([=](Collider* c)->bool
          {
            if(c->type == Collider::C_SPHERE)
            {
              SphereCollider* tst = RECAST(SphereCollider*, c);
              return tst->rad == sphere->rad;
            }
            return false;
          },
          [=]()->CollisionShape*
          {
            auto toSave = Memory::New<SphereCollider>(sphere->rad, false);
            return this->NewCollider(toSave, Memory::New<SphereShape>(sphere->rad));
          }
        );
      }
      break;
      case Collider::C_CAPSULE:
      {
        CapsuleCollider* cap = RECAST(CapsuleCollider*, col);
        col->shape = 
        Loop([=](Collider* c)->bool
          {
            if(c->type == Collider::C_CAPSULE)
            {
              CapsuleCollider* tst = RECAST(CapsuleCollider*, c);
              return tst->rad == cap->rad && tst->ht == cap->ht;
            }
            return false;
          },
          [=]()->CollisionShape*
          {
            auto toSave = Memory::New<CapsuleCollider>(cap->rad, cap->ht, false);
            return this->NewCollider(toSave, Memory::New<CapsuleShape>(cap->rad, cap->ht));
          }
        );
      }
      break;
      default:
        assert(false);
    }
  }

  CollisionShape* CollisionShapeManager::GetEmptyShape()
  {
    for(auto it = m_colliders.begin(); it != m_colliders.end(); ++it)
    {
      if((*it)->type == Collider::C_EMPTY)
        return (*it)->shape;
    }

    auto toSave = Memory::New<Collider>(Collider::C_EMPTY, false);
    return NewCollider(toSave, Memory::New<btEmptyShape>());
  }

  void CollisionShapeManager::ClearAllShapes()
  {
    for(auto it = m_colliders.begin(); it != m_colliders.end(); ++it)
    {
      Memory::Delete((*it)->shape);
      Memory::Delete(*it);
    }
    m_colliders.clear();
  }

  CollisionShape* CollisionShapeManager::NewCollider(Collider* c, CollisionShape* shape)
  {
    c->shape = shape;
    m_colliders.push_back(c);
    return shape;
  }

  CollisionShape* CollisionShapeManager::Loop(const std::function<bool(Collider*)>& fcn, 
      const std::function<CollisionShape*(void)>& makeFunc)
  {
    for(auto it = m_colliders.begin(); it != m_colliders.end(); ++it)
    {
      if(fcn(*it))
        return (*it)->shape;
    }
    return makeFunc();
  }

  Collider::Collider(Type t)
    : type(t)
  {
    gCollisionShapeMgr->SetColliderShape(this);
  }

  Collider::Collider(Type t, bool wasCalled)
    : type(t)
  {
    assert(!wasCalled);
  }

  Collider::~Collider()
  {

  }
}
