#pragma once

#include "IGraphicsAPI.h"

namespace Graphics
{
  Semaphore glesStartSync;
  Semaphore glesEndSync;

  class GLESClass : public IGraphicsAPI
  {
  public:
    GLESClass();
    ~GLESClass();

    virtual bool Initialize();
    virtual void StartFrame();
    virtual void EndFrame();
    virtual void Teardown();

    virtual void Handle(Message* m);

    virtual bool MakeWindow(s32 width, s32 height, bool fullscreen = false);
    virtual GraphicsWindow* GetWindow() const;

  private:
    s32 m_width, m_height;
  };

  typedef GLESClass GraphicsAPI;

}
