/*
*  FILE          ConsoleComponent.cpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for console interface features.
*/
#include "CommonPrecompiled.h"
#include "ConsoleComponent.h"

namespace GUI
{
  ConsoleComponent::ConsoleComponent()
  { }

  void ConsoleComponent::Initialize(void)
  {
    static bool no_titlebar = false;
    static bool no_border = true;
    static bool no_resize = true;
    static bool no_move = true;
    static bool no_scrollbar = false;
    static bool no_collapse = false;
    static bool no_menu = false;
    static float bg_alpha = 0.65f;

    // Demonstrate the various window flags. Typically you would just use the default.
    ImGuiWindowFlags window_flags = 0;
    if(no_titlebar)  window_flags |= ImGuiWindowFlags_NoTitleBar;
    if(!no_border)   window_flags |= ImGuiWindowFlags_ShowBorders;
    if(no_resize)    window_flags |= ImGuiWindowFlags_NoResize;
    if(no_move)      window_flags |= ImGuiWindowFlags_NoMove;
    if(no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
    if(no_collapse)  window_flags |= ImGuiWindowFlags_NoCollapse;
    if(!no_menu)     window_flags |= ImGuiWindowFlags_MenuBar;

    title = "Console";
    flags = window_flags;
    initial_position = Math::Vector2(0.0f, 0.0f);
    initial_size = Math::Vector2(600.0f, 300.0f);
    alpha = 0.5f;
  }

  void ConsoleComponent::Display(void)
  {
    static ImGuiTextFilter CommandFilter;
    CommandFilter.Draw("Command");
  }

  void ConsoleComponent::Destroy(void)
  { }
}