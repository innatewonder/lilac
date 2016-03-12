#pragma once

namespace Graphics
{
  class RenderableComponent : public Component
  {
  public:
    virtual void Draw(u32 shaderID) {};
    virtual void Initialize();
  };
}
