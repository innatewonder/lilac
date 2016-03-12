#pragma once

#include "RenderableComponent.h"
namespace Graphics
{
  class UIComponent : public RenderableComponent
  {
  public:
    UIComponent();
    ~UIComponent();

    virtual void Initialize();
    virtual void Draw(u32 shaderID);

  private:
  };
}
