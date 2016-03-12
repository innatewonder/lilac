#include "CommonPrecompiled.h"
#include "UpdateType.h"
UpdateTypeManager* UpdateMan = nullptr;

UpdateTypeManager::UpdateTypeManager()
{
  UpdateMan = this;
}

void UpdateTypeManager::Register(UpdateTypeBase* t)
{
  m_vals.push_back(t);
}

void UpdateTypeManager::Update()
{
  auto it = m_vals.begin();
  for(; it != m_vals.end(); ++it)
  {
    (*it)->Update();
  }
}
