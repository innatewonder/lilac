#include "CommonPrecompiled.h"
#include "Object.h"

Object::Object()
  : m_uid(gCoreUtils->NextUID()), m_shouldDestroy(false)
{
  Core::gCore->RegisterObject(this);
}

Object::~Object()
{
  for(Component* comp : m_components)
  {
    Factory::DestroyComponent(comp);
  }
  m_components.clear();
}

void Object::Kill()
{
  m_shouldDestroy = true;
  Core::gCore->MarkObjectForDeath(this);
}

bool Object::MarkedForDeath()
{
  return m_shouldDestroy;
}

bool Object::AddComponent(Component* comp)
{
  if(Factory::IsUniqueType(comp->GetTypeID())
    && GetComponent(comp->GetTypeID()))
    return false;

  comp->SetParent(this);
  m_components.push_back(comp);
  return true;
}

Component* Object::AddComponent(Comp::ComponentDef type)
{
  if(Factory::IsUniqueType(type)
    && GetComponent(type))
    return nullptr;

  Component* newComp = Factory::MakeComponent(type);
  newComp->SetParent(this);
  m_components.push_back(newComp);
  return newComp;
}

bool Object::RemoveComponent(Component* comp)
{
  for(auto it = m_components.begin(); it != m_components.end(); ++it)
  {
    if((*it)->GetUID() == comp->GetUID())
    {
      Factory::DestroyComponent(*it);
      m_components.erase(it);
      return true;
    }
  }
  return false;
}

bool Object::RemoveComponent(UID id)
{
  for(auto it = m_components.begin(); it != m_components.end(); ++it)
  {
    if((*it)->GetUID() == id)
    {
      Factory::DestroyComponent(*it);
      m_components.erase(it);
      return true;
    }
  }
  return false;
}

bool Object::RemoveComponent(Comp::ComponentDef type)
{
  for(auto it = m_components.begin(); it != m_components.end(); ++it)
  {
    if((*it)->GetTypeID() == type)
    {
      Factory::DestroyComponent(*it);
      m_components.erase(it);
      return true;
    }
  }
  return false;
}

Component* Object::GetComponent(Comp::ComponentDef type)
{
  for(auto comp : m_components)
  {
    if(comp->GetTypeID() == type)
    {
      return comp;
    }
  }
  return nullptr;
}

Containers::List<Component*> Object::GetComponentType(Comp::ComponentDef type)
{
  Containers::List<Component*> ret;
  for(auto comp : m_components)
  {
    if(comp->GetTypeID() == type)
    {
      ret.push_back(comp);
    }
  }
  return ret;
}

Containers::List<Component*>& Object::GetComponents(void)
{
  return m_components;
}

UID Object::GetUID() const
{
  return m_uid;
}
