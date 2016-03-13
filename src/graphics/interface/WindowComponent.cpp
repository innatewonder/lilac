/*
*  FILE          WindowComponent.cpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for global wrapper functions used to define a window context.
*/
#include "CommonPrecompiled.h"
#include "WindowComponent.h"
#include "imgui.h"

namespace GUI
{
  WindowComponent::WindowComponent()
    : title("WINDOW TITLE MISSING"), flags(0), alpha(0.5f), initial_position(0.0f, 0.0f), initial_size(64.0f, 64.0f), fixed(true)
  { }

  void WindowComponent::Begin(void)
  {
    static bool opened = false;
    ImGui::Begin(title.c_str(), &opened, ImVec2(initial_size.x, initial_size.y), alpha, flags);
    Setup();
  }

  void WindowComponent::Setup(void)
  {
    if(fixed)
    {
      ImGui::SetWindowPos(ImVec2(initial_position.x, initial_position.y));
      ImGui::SetWindowSize(ImVec2(initial_size.x, initial_size.y));
    }

    current_position = Math::Vector2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
    current_size = Math::Vector2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
    is_collapsed = ImGui::GetWindowCollapsed();
    is_focused = ImGui::GetWindowIsFocused();
  }

  void WindowComponent::End(void)
  {
    ImGui::End();
  }

  INLINE std::string WindowComponent::GetWindowTitle(void) const
  {
    return title;
  }

  INLINE Math::Vector2 WindowComponent::GetInitialWindowSize(void) const
  {
    return initial_size;
  }

  INLINE Math::Vector2 WindowComponent::GetInitialWindowPosition(void) const
  {
    return initial_position;
  }

  INLINE f32 WindowComponent::GetWindowAlpha(void) const
  {
    return alpha;
  }

  INLINE void WindowComponent::SetWindowTitle(const std::string& name)
  { }

  INLINE void WindowComponent::SetWindowSize(const Math::Vector2& size)
  {
    ImGui::SetWindowSize(title.c_str(), ImVec2(size.x, size.y));
  }

  INLINE void WindowComponent::SetWindowPosition(const Math::Vector2& position)
  {
    ImGui::SetWindowPos(title.c_str(), ImVec2(position.x, position.y));
  }

  INLINE void WindowComponent::SetWindowAlpha(f32 a)
  {
    alpha = a;
  }

  INLINE void WindowComponent::SetWindowCollapsed(bool collapsed)
  {
    ImGui::SetWindowCollapsed(title.c_str(), collapsed);
  }

  INLINE void WindowComponent::SetWindowFocused(void)
  {
    ImGui::SetWindowFocus(title.c_str());
  }

  INLINE void WindowComponent::Set(s32 argument, bool active)
  {
    if(active)
      Enable(argument);
    else
      Disable(argument);
  }

  INLINE void WindowComponent::Enable(s32 argument)
  {
    flags |= argument;
  }

  INLINE void WindowComponent::Disable(s32 argument)
  {
    flags &= ~argument;
  }

  INLINE void WindowComponent::Toggle(s32 argument)
  {
    flags ^= argument;
  }

  INLINE bool WindowComponent::IsEnabled(s32 argument) const
  {
    return (flags & argument) == 1;
  }

  INLINE bool WindowComponent::IsDisabled(s32 argument) const
  {
    return (flags & argument) == 0;
  }

  INLINE Math::Vector2 WindowComponent::GetWindowSize(void) const
  {
    return current_size;
  }

  INLINE Math::Vector2 WindowComponent::GetWindowPosition(void) const
  {
    return current_position;
  }

  INLINE bool WindowComponent::IsCollapsed(void) const
  {
    return is_collapsed;
  }

  INLINE bool WindowComponent::IsFocused(void) const
  {
    return is_focused;
  }
}