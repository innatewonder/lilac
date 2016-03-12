#include "CommonPrecompiled.h"
#include "Component.h"

Component::Component()
  : m_id(gCoreUtils->NextUID()), m_typeID(Comp::NUM_COMPONENTS),
  m_parent(nullptr)
{
}

Component::~Component()
{
  // Factory::DestroyComponent(this);
}

void Component::SetType(Comp::ComponentDef type)
{
  if(m_typeID == Comp::NUM_COMPONENTS)
    m_typeID = type;
}

void Component::SetParent(Object* parent)
{
  m_parent = parent;
}

Object* Component::GetParent() const
{
  return m_parent;
}

UID Component::GetUID() const
{
  return m_id;
}

Comp::ComponentDef Component::GetTypeID() const
{
  return m_typeID;
}

const String& Component::GetName() const
{
  return Factory::GetCompName(m_typeID);
}
