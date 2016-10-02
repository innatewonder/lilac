#include "CommonPrecompiled.h"
#include "Shader.h"
#include "GLESClass.h"
#include "InputSystem.h"

void ErrorCallback(int error, const char* description)
{
  std::cerr << description << std::endl;
}


namespace Graphics
{
  GLESClass::GLESClass()
  {
  }

  GLESClass::~GLESClass()
  {
    //teardown in teardown
  }

  bool GLESClass::Initialize()
  {
    return true;
  }

  void GLESClass::StartFrame()
  {
    glesStartSync.Wait();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CHECK_GL_ERR;
  }

  void GLESClass::EndFrame()
  {
    CHECK_GL_ERR;

    glesEndSync.Notify();
  }

  void GLESClass::Teardown()
  {
  }

  void GLESClass::Handle(Message *m)
  {
    switch(m->GetType()) 
    {
      case Message::MSG_RESIZE:
        m_width = *m->GetFormatedData<s32>();
        m_height = *m->GetFormatedData<s32>();
        glViewport(0, 0, m_width, m_height);
      break;
    }
  }

  bool GLESClass::MakeWindow(s32 width, s32 height, bool fullscreen)
  {
    m_width = 0;
    m_height = 0;

    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
    glClearColor(0.3f, 0.3f, 0.3f, 1);

    CHECK_GL_ERR;
    return true;
  }

  GLFWwindow* GLESClass::GetWindow() const
  {
    return nullptr;
  }
}
