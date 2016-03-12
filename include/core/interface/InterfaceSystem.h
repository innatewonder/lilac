/*
*  FILE          InterfaceSystem.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for interface system containing gui components.
*/
#pragma once

namespace GUI
{
  class InterfaceSystem : public System
  {
    public:
      InterfaceSystem();
      ~InterfaceSystem();

      virtual bool Initialize(ArgParser& args);
      virtual void Destroy();
      virtual void Test();

      virtual void Tick(f32 dt);
      virtual void HandleMessage(Message* msg);
      void Display(void);

    private:
      Object* ObjectEditor;
  };
}