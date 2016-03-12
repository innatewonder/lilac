#include "CommonPrecompiled.h"
#include "Shader.h"
#include "GLClass.h"
#include "InputSystem.h"

void ErrorCallback(int error, const char* description)
{
  std::cerr << description << std::endl;
}

GLClass::GLClass()
{
}

GLClass::~GLClass()
{
 //teardown in teardown
}

bool GLClass::Initialize()
{
  if(!glfwInit())
    return false;

  glfwSetErrorCallback(ErrorCallback);
  return true;
}

void GLClass::StartFrame()
{
  if(glfwWindowShouldClose(m_window))
    Core::gCore->Quit();

  CHECK_GL_ERR;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, m_width, m_height);
  
  CHECK_GL_ERR;
}

void GLClass::EndFrame()
{
  CHECK_GL_ERR;
  glfwSwapBuffers(m_window);
  CHECK_GL_ERR;
}

void GLClass::Teardown()
{
  glfwTerminate();
}

void GLClass::Handle(Message *m)
{
}

bool GLClass::MakeWindow(s32 width, s32 height, bool fullscreen)
{
  m_width = width;
  m_height = height;

  GLFWmonitor* monitor = NULL;
  if(fullscreen)
  {
    monitor = glfwGetPrimaryMonitor();

    //get the screen actual size
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    m_width = mode->width;
    m_height = mode->height;
  }

  m_window = glfwCreateWindow(m_width, m_height, "Mythril", monitor, NULL);
  if(!m_window)
  {
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(m_window);
  CHECK_GL_ERR;

  glewInit();
  glfwSwapInterval(0);
  glEnable (GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
  glClearColor(0.3f, 0.3f, 0.3f, 1);

  const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString(GL_VERSION); // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  //let everything know the window size
  Message* m = MESSAGE(Message::MSG_WINDOW);
  m->AddData(DAT(m_width));
  m->AddData(DAT(m_height));
  m->AddData(DAT(m_window));
  Core::gCore->SendMessage(m);

  CHECK_GL_ERR;
  return true;
}

GLFWwindow* GLClass::GetWindow() const
{
  return m_window;
}
