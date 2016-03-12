#include "CommonPrecompiled.h"
#include "System.h"

void System::RegisterComponent(Component* comp)
{
  m_components.push_back(comp);
}

void System::UnregisterComponent(Component* comp)
{
  m_components.remove(comp);
}

u32 System::NumComponents() const
{
  return m_components.size();
}
