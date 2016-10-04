#include "CommonPrecompiled.h"
#include "ModelComponent.h"

#include "TransformComponent.h"

namespace Graphics
{
  ModelComponent::ModelComponent()
    : m_model(nullptr)
  {
  }
  
  ModelComponent::ModelComponent(Model* m)
    : m_model(m)
  {

  }

  ModelComponent::~ModelComponent()
  {

  }
  
  void ModelComponent::SetModel(Model* m)
  {
    m_model = m;
  }

  void ModelComponent::Draw(u32 shaderID)
  {
    if(!m_model)
      return;

    assertion(m_parent);
    auto c = GetParent()->GetComponent(Comp::TransformComponent);
    assertion(c);
    Physics::TransformComponent* transform = RECAST(Physics::TransformComponent*, c);
    auto pos = transform->GetPosition();

    int loc = glGetUniformLocation(shaderID, "ModelMatrix");

    Math::Matrix model = Math::TranslationMatrix::Build(Math::Vector4(pos));//m_translation * m_scale;
    glUniformMatrix4fv(loc, 1, GL_FALSE, (model.v));

    m_model->Draw(shaderID);

    loc = glGetUniformLocation(shaderID, "stripColor");
    glUniform4fv(loc, 1, Math::LinearColor::WHITE.v);
  }

  void ModelComponent::Initialize()
  {
  }
}
