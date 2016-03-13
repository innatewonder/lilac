/*
  This is where all systems should be added, as well as to SystemIncludes

  The define is Namespace, ClassName
  The systems will be included and updated in this order
*/

SYSTEM_DEF(Test, TestSystem)
SYSTEM_DEF(Core, InputSystem)
SYSTEM_DEF(Physics, PhysicsSystem)
SYSTEM_DEF(Core, MessageSystem)

#ifdef USE_GRAPHICS
  SYSTEM_DEF(Graphics, GraphicsSystem)
#endif

SYSTEM_DEF(Audio, AudioSystem)

SYSTEM_DEF(Generation, GenerationSystem)
SYSTEM_DEF(Networking, NetworkingSystem)
SYSTEM_DEF(GUI, InterfaceSystem)
