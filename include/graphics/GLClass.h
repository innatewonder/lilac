#pragma once

#include "IGraphicsAPI.h"

namespace Graphics 
{
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
    virtual GraphicsWindow* GetWindow() const;

  private:
    GraphicsWindow* m_window;
    s32 m_width, m_height;
  };

  typedef GLClass GraphicsAPI;
}
