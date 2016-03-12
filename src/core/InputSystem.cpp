#include "CommonPrecompiled.h"
#include "InputSystem.h"
#include "InterfaceContext.h"

namespace Core
{
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
    glfwPollEvents();
  }

  void InputSystem::HandleMessage(Message* msg)
  {
    switch(msg->GetType())
    {
      case Message::MSG_WINDOW:
      {
        LOG("InputSystem handling new window message");
        s32 width = *msg->GetFormatedData<s32>();
        s32 height = *msg->GetFormatedData<s32>();
        m_window = *msg->GetFormatedData<GLFWwindow*>();
        glfwGetCursorPos(m_window, &m_mouseX, &m_mouseY);
        m_mousePX = m_mouseX;
        m_mousePY = m_mouseY;
        glfwSetKeyCallback(m_window, &InputSystem::KeyCallback);
        glfwSetCharCallback(m_window, &InputSystem::CharCallback);
        glfwSetMouseButtonCallback(m_window, &InputSystem::MouseButtonCallback);
        glfwSetCursorPosCallback(m_window, &InputSystem::CursorPosCallback);
        glfwSetCursorEnterCallback(m_window, &InputSystem::CursorEnterCallback);
        glfwSetScrollCallback(m_window, &InputSystem::ScrollCallback);
        glfwSetWindowSizeCallback(m_window, &InputSystem::ResizeCallback);
        break;
      }
    }
  }

  /////////
  //PRIVATE
  void InputSystem::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
  {
    Message* m = MESSAGE(Message::MSG_KEY);

    m->AddData(DAT(key));
    m->AddData(DAT(action));

    gCore->SendMessage(m);

    GUI::InterfaceKeyCallback(window, key, scancode, action, mods);
  }

  void InputSystem::CharCallback(GLFWwindow *window, unsigned key)
  {
    GUI::InterfaceCharCallback(window, key);
  }

  void InputSystem::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
  {
    Message* m = MESSAGE(Message::MSG_MOUSE_BUTTON);

    m->AddData(DAT(button));
    m->AddData(DAT(action));

    gCore->SendMessage(m);

    GUI::InterfaceMouseButtonCallback(window, button, action, mods);
  }

  void InputSystem::CursorPosCallback(GLFWwindow *window, double x, double y)
  {
    Message* m = MESSAGE(Message::MSG_MOUSE);

    s32 ix = (s32)x;
    s32 iy = (s32)y;

    m->AddData(DAT(x));
    m->AddData(DAT(y));

    //localSys->SetMouse(ix, iy);
    gCore->SendMessage(m);
  }

  void InputSystem::CursorEnterCallback(GLFWwindow *window, int entered)
  {

  }

  void InputSystem::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
  {
    Message* m = MESSAGE(Message::MSG_SCROLL);

    m->AddData(DAT(xoffset));
    m->AddData(DAT(yoffset));

    gCore->SendMessage(m);

    GUI::InterfaceScrollCallback(window, xoffset, yoffset);
  }

  void InputSystem::ResizeCallback(GLFWwindow* window, int width, int height)
  {
    Message* m = MESSAGE(Message::MSG_RESIZE);
    m->AddData(DAT(width));
    m->AddData(DAT(height));
    gCore->SendMessage(m);
  }
}
