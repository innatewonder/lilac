/*
*  FILE          InterfaceSystem.cpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for interface system containing gui components.
*/
#include "CommonPrecompiled.h"
#include "InterfaceSystem.h"

#include "WindowComponent.h"

namespace GUI
{
  InterfaceSystem::InterfaceSystem()
  { }

  InterfaceSystem::~InterfaceSystem()
  { }

  bool InterfaceSystem::Initialize(ArgParser& args)
  {
    // ObjectEditor = Factory::MakeObject();
    // ObjectEditor->AddComponent(Comp::ObjectEditorComponent);
    //ObjectEditor->AddComponent(Comp::ConsoleComponent);

    return true;
  }

  void InterfaceSystem::Destroy()
  { }

  void InterfaceSystem::Test()
  { }

  void InterfaceSystem::Tick(f32 dt)
  { }

  void InterfaceSystem::HandleMessage(Message* msg)
  { }

  void InterfaceSystem::Display(void)
  {
    for(Containers::List<Component*>::iterator it = m_components.begin(); it != m_components.end(); ++it)
    {
      if(WindowComponent* window = DYNCAST(WindowComponent*, *it))
      {
        window->Begin();
        window->Display();
        window->End();
      }
    }
  }
}