#pragma once

#include "RenderableComponent.h"

namespace Graphics
{
  class ProcModelComponent : public RenderableComponent
  {
  public:
    ProcModelComponent();
    ~ProcModelComponent();

    virtual void Initialize() override;
    virtual void Draw(u32 shaderID) override;
    
  private:

  };
}
