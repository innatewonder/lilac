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
    GLFWwindow* m_window;
    
    double m_mouseX, m_mouseY;
    double m_mousePX, m_mousePY;

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void CharCallback(GLFWwindow* window, unsigned key);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void CursorPosCallback(GLFWwindow* window, double x, double y);
    static void CursorEnterCallback(GLFWwindow* window, int entered);
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void ResizeCallback(GLFWwindow* window, int width, int height);
  };

}