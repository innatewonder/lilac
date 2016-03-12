#pragma once

#include "Camera.h"

class IGraphicsAPI;
class Shader;
#define GRAPHICS_API_OPENGL

namespace Graphics
{
  class RenderableComponent;
  class GraphicsSystem : public System
  {
  public:
    GraphicsSystem();
    ~GraphicsSystem();

    virtual bool Initialize(ArgParser& args);
    virtual void Destroy();
    virtual void Test();

    virtual void RegisterComponent(Component* comp);
    virtual void UnregisterComponent(Component* comp);

    virtual void Tick(f32 dt);

    virtual void HandleMessage(Message* msg);
    
  private:
    IGraphicsAPI* m_api;

    Containers::List<RenderableComponent*> m_renderables;

    Shader* m_defaultShader;

    Camera m_camera;
    f32 m_front;
    s32 m_height, m_width;
    bool m_fullscreen;

    f32 m_desiredFR;
    f32 m_dt;
  };
}
