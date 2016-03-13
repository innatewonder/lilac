#pragma once

namespace Core
{
  class InputSystem : public System
  {
  public:
    InputSystem();
    ~InputSystem();

    virtual bool Initialize(ArgParser& args);
    virtual void Destroy();
    virtual void Test();
    virtual void HandleMessage(Message* msg);

    virtual void Tick(f32 dt);

  private:
    GraphicsWindow* m_window;
    
    double m_mouseX, m_mouseY;
    double m_mousePX, m_mousePY;
  };

}