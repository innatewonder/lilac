#pragma once

namespace Comp
{
#define COMPONENT_DEF(space, comp, sys, unique) comp,
  enum ComponentDef
  {
#include "ComponentDefines.h"
    NUM_COMPONENTS
  };
#undef COMPONENT_DEF
}

namespace Sys
{
#define SYSTEM_DEF(space, sys) sys,
  enum SystemDef
  {
#include "SystemDefines.h"
    NUM_SYSTEMS
  };
#undef SYSTEM_DEF
}

class Component;
class Object;

class Factory
{
public:
  static void Initialize();
  static void Destroy();

  static Object* MakeObject();
  static void DestroyObject(Object* ptr);

  static const String& GetSysName(Sys::SystemDef sys);
  
  static Component* MakeComponent(Comp::ComponentDef comp);
  static void DestroyComponent(Component* comp);
  static const String& GetCompName(Comp::ComponentDef comp);
  static u32 GetCompSize(Comp::ComponentDef comp);
  static Sys::SystemDef GetCompSys(Comp::ComponentDef comp);
  static bool IsUniqueType(Comp::ComponentDef comp);

private:
  static Memory::PoolAllocator* m_objectPool;
  static Containers::Vector<Memory::PoolAllocator*> m_componentPools;
  static Containers::UnorderedMap<u32, std::function<Component*(void)>> m_compConstructors;
};
