#pragma once

//bullet
#include <btBulletDynamicsCommon.h>
#include <btGImpactCollisionAlgorithm.h>

typedef btDefaultMotionState DefaultMotionState;

typedef btRigidBody RigidBody;
typedef btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo;

typedef btCollisionShape CollisionShape;
typedef btStaticPlaneShape StaticPlaneShape;
typedef btSphereShape SphereShape;
typedef btBoxShape CubeShape;
typedef btCapsuleShape CapsuleShape;

typedef btBroadphaseInterface BroadphaseInterface;
typedef btDefaultCollisionConfiguration DefaultConfig;
typedef btCollisionDispatcher CollisionDispatcher;
typedef btSequentialImpulseConstraintSolver SequentialImpulseSolver;
typedef btDiscreteDynamicsWorld DiscreteDynWorld;