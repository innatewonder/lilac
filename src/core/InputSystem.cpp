#include "CommonPrecompiled.h"
#include "InputSystem.h"
#if USE_GRAPHICS
  #include "InterfaceContext.h"
#endif

namespace Core
{
  namespace
  {
#if USE_GRAPHICS
    void KeyCallback(GraphicsWindow *window, int key, int scancode, int action, int mods)
    {
      Message* m = MESSAGE(Message::MSG_KEY);

      m->AddData(DAT(key));
      m->AddData(DAT(action));

      gCore->SendMessage(m);

      GUI::InterfaceKeyCallback(window, key, scancode, action, mods);
    }

    void CharCallback(GraphicsWindow *window, unsigned key)
    {
      GUI::InterfaceCharCallback(window, key);
    }

    void MouseButtonCallback(GraphicsWindow *window, int button, int action, int mods)
    {
      Message* m = MESSAGE(Message::MSG_MOUSE_BUTTON);

      m->AddData(DAT(button));
      m->AddData(DAT(action));

      gCore->SendMessage(m);

      GUI::InterfaceMouseButtonCallback(window, button, action, mods);
    }

    void CursorPosCallback(GraphicsWindow *window, double x, double y)
    {
      Message* m = MESSAGE(Message::MSG_MOUSE);

      s32 ix = (s32)x;
      s32 iy = (s32)y;

      m->AddData(DAT(x));
      m->AddData(DAT(y));

      //localSys->SetMouse(ix, iy);
      gCore->SendMessage(m);
    }

    void CursorEnterCallback(GraphicsWindow *window, int entered)
    {

    }

    void ScrollCallback(GraphicsWindow *window, double xoffset, double yoffset)
    {
      Message* m = MESSAGE(Message::MSG_SCROLL);

      m->AddData(DAT(xoffset));
      m->AddData(DAT(yoffset));

      gCore->SendMessage(m);

      GUI::InterfaceScrollCallback(window, xoffset, yoffset);
    }

    void ResizeCallback(GraphicsWindow* window, int width, int height)
    {
      Message* m = MESSAGE(Message::MSG_RESIZE);
      m->AddData(DAT(width));
      m->AddData(DAT(height));
      gCore->SendMessage(m);
    }
#endif
  }

  InputSystem* localSys = nullptr;

  InputSystem::InputSystem()
  {
    localSys = this;
  }

  InputSystem::~InputSystem()
  {
    localSys = nullptr;
  }

  bool InputSystem::Initialize(ArgParser& args)
  {
    return true;
  }

  void InputSystem::Destroy()
  {
  }

  void InputSystem::Test()
  {
  }

  void InputSystem::Tick(f32 dt)
  {
#if USE_GRAPHICS
    glfwPollEvents();
#endif
  }

  void InputSystem::HandleMessage(Message* msg)
  {
    switch(msg->GetType())
    {
#if USE_GRAPHICS
      case Message::MSG_WINDOW:
      {
        LOG("InputSystem handling new window message");
        s32 width = *msg->GetFormatedData<s32>();
        s32 height = *msg->GetFormatedData<s32>();
        m_window = *msg->GetFormatedData<GraphicsWindow*>();
        glfwGetCursorPos(m_window, &m_mouseX, &m_mouseY);
        m_mousePX = m_mouseX;
        m_mousePY = m_mouseY;
        glfwSetKeyCallback(m_window, &KeyCallback);
        glfwSetCharCallback(m_window, &CharCallback);
        glfwSetMouseButtonCallback(m_window, &MouseButtonCallback);
        glfwSetCursorPosCallback(m_window, &CursorPosCallback);
        glfwSetCursorEnterCallback(m_window, &CursorEnterCallback);
        glfwSetScrollCallback(m_window, &ScrollCallback);
        glfwSetWindowSizeCallback(m_window, &ResizeCallback);
        break;
      }
#endif
      default:
        break;
    }
  }
}
