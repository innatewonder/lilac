#include "CommonPrecompiled.h"
#include "Camera.h"

Camera::Camera()
{
  m_position = Math::Point4(0, -30, 50);
}

void Camera::SetPosition(Math::Point4 &pos)
{
  m_position = pos;
}

Math::Point4& Camera::GetPosition()
{
  return m_position;
}

void Camera::Resize(s32 width, s32 height)
{
}

Math::Matrix &Camera::MakeView()
{
  Math::Vector4 up(0.0f, 1.0f, 0.0f);
  Math::Point4 look(0.0f, 0.0f, 0.0f);

  m_view = Math::ViewMatrix::Build(m_position, look, up);
  return m_view;
}

Math::Matrix &Camera::GetView()
{
  return m_view;
}
