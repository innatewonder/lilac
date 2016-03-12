#pragma once

class Camera
{
  public:
    Camera();

    void SetPosition(Math::Point4& pos);
    Math::Point4& GetPosition();

    void Resize(s32 width, s32 height);

    Math::Matrix& MakeView();
    Math::Matrix& GetView();

  private:
    Math::Point4 m_position;
    Math::Vector4 m_rotation;

    Math::Matrix m_view;
};

