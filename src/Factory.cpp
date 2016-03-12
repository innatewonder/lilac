#include "CommonPrecompiled.h"
#include "Factory.h"

#include "SystemIncludes.h"
#include "ComponentIncludes.h"

#define COMPONENT_DEF(space, comp, sys, unique) #comp,
  static const String l_compNames[] = {
    #include "ComponentDefines.h"
  };
#undef COMPONENT_DEF

#define SYSTEM_DEF(space, sys) #sys,
  static const String l_sysNames[] = {
    #include "SystemDefines.h"
  };
#undef SYSTEM_DEF

struct CompMeta
{
  CompMeta(Sys::SystemDef s, u32 sz, bool u)
    : sys(s), size(sz), unique(u) 
  {}
  Sys::SystemDef sys;
  u32 size;
  bool unique;
};

#define COMPONENT_DEF(space, comp, sys, unique) \
  CompMeta(Sys::sys, sizeof(space::comp), unique),

  static const Containers::Vector<CompMeta> l_compMeta = {
    #include "ComponentDefines.h"
  };
#undef COMPONENT_DEF
  
Memory::PoolAllocator* Factory::m_objectPool = nullptr;
Containers::Vector<Memory::PoolAllocator*> Factory::m_componentPools = Containers::Vector<Memory::PoolAllocator*>();
Containers::UnorderedMap<u32, std::function<Component*(void)>> Factory::m_compConstructors;

void Factory::Initialize()
{
  m_objectPool = Memory::New<Memory::PoolAllocator>(sizeof(Object));

  for(u32 i = 0; i < Sys::NUM_SYSTEMS; ++i)
  {
    u32 sysCompMaxSize = 0;
    for(u32 j = 0; j < Comp::NUM_COMPONENTS; ++j)
    {
      if(GetCompSys(Comp::ComponentDef(j)) == i)
      {
        sysCompMaxSize = Math::Max(sysCompMaxSize, GetCompSize(Comp::ComponentDef(j)));
      }
    }

    if(sysCompMaxSize > 0)
    {
      LOG(GetSysName(Sys::SystemDef(i)) << " max comp size: " << sysCompMaxSize);
      m_componentPools.push_back(Memory::New<Memory::PoolAllocator>(sysCompMaxSize));
    }
    else m_componentPools.push_back(nullptr);
  }

#define COMPONENT_DEF(space, comp, sys, unique) \
  {Comp::comp, [](void)->Component*{return m_componentPools[Sys::sys]->New<space::comp>();}},

  m_compConstructors.insert(
  {
#include "ComponentDefines.h"
  });
#undef COMPONENT_DEF

}

void Factory::Destroy()
{
  Memory::Delete(m_objectPool);
  for(u32 i = 0; i < Sys::NUM_SYSTEMS; ++i)
  {
    Memory::Delete(m_componentPools[i]);
  }
}

Object* Factory::MakeObject()
{
  return m_objectPool->New<Object>();
}

void Factory::DestroyObject(Object* ptr)
{
  m_objectPool->Delete(ptr);
}

const String& Factory::GetSysName(Sys::SystemDef sys)
{
  if(sys >= Sys::NUM_SYSTEMS)
    return EMPTY_STRING;
  return l_sysNames[sys];
}

Component* Factory::MakeComponent(Comp::ComponentDef index)
{
  Sys::SystemDef sys = GetCompSys(index);
  Component* ret = m_compConstructors[index]();

  ret->SetType(index);
  ret->Initialize();
  Core::gCore->GetSystem(sys)->RegisterComponent(ret);
  return ret;
}

void Factory::DestroyComponent(Component* toDestroy)
{
  Comp::ComponentDef type = toDestroy->GetTypeID();
  Sys::SystemDef sys = GetCompSys(type);

  Core::gCore->GetSystem(sys)->UnregisterComponent(toDestroy);
  m_componentPools[sys]->Delete(toDestroy);
}

const String& Factory::GetCompName(Comp::ComponentDef comp)
{
  if(comp == Comp::NUM_COMPONENTS)
    return EMPTY_STRING;
  return l_compNames[comp];
}

u32 Factory::GetCompSize(Comp::ComponentDef comp)
{
  return l_compMeta[comp].size;
}

Sys::SystemDef Factory::GetCompSys(Comp::ComponentDef comp)
{
  return l_compMeta[comp].sys;
}

bool Factory::IsUniqueType(Comp::ComponentDef type)
{
  return l_compMeta[type].unique;
}
