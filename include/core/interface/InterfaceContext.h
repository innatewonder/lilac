/*
*  FILE          InterfaceContext.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for interface context wrapper functions.
*/
#pragma once

namespace GUI
{
  void InterfaceInitialize(void* window, void* device, void* context);
  void InterfaceShutdown(void);
  void InterfaceUpdate(void);

  void InterfaceInvalidateDeviceObjects(void);
  void InterfaceCreateDeviceObjects(void);

#if defined(GRAPHICS_API_OPENGL)
  void InterfaceMouseButtonCallback(GLFWwindow* window, s32 button, s32 action, s32 mods);
  void InterfaceScrollCallback(GLFWwindow* window, f64 offset_x, f64 offset_y);
  void InterfaceKeyCallback(GLFWwindow* window, s32 key, s32 scancode, s32 action, s32 mods);
  void InterfaceCharCallback(GLFWwindow* window, u32 c);
#endif
}