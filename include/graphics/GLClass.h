#ifndef GL_CLASS_H
#define GL_CLASS_H

#include "IGraphicsAPI.h"
class GLClass : public IGraphicsAPI
{
public:
  GLClass();
  ~GLClass();

  virtual bool Initialize();
  virtual void StartFrame();
  virtual void EndFrame();
  virtual void Teardown();

  virtual void Handle(Message* m);

  virtual bool MakeWindow(s32 width, s32 height, bool fullscreen = false);
  virtual GLFWwindow* GetWindow() const;

private:
  GLFWwindow* m_window;
  s32 m_width, m_height;
};

#endif
