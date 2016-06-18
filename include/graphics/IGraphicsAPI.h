#ifndef IGRAPHICS_API_H
#define IGRAPHICS_API_H

namespace Graphics
{
  class Model;
  class IGraphicsAPI
  {
  public:
    virtual bool Initialize() = 0;
    virtual void StartFrame() = 0;
    virtual void EndFrame() = 0;
    virtual void Teardown() = 0;

    virtual bool MakeWindow(s32 width, s32 height, bool fullscreen = false) = 0;

    virtual void Handle(Message* m) = 0;

    TODO("This needs to be universal");
    virtual GLFWwindow* GetWindow() const = 0;
  };
}
#endif
