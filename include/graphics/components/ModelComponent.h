#pragma once

#include "RenderableComponent.h"
#include "Model.h"

namespace Graphics
{
  class ModelComponent : public RenderableComponent
  {
  public:
    ModelComponent();
    ModelComponent(Model* m);
    ~ModelComponent();

    void SetModel(Model* m);

    virtual void Initialize();
    virtual void Draw(u32 shaderID);

  private:
    Model* m_model;
  };
}
