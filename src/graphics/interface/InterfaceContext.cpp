/*
*  FILE          InterfaceWindowHandler.cpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for interface context wrapper functions.
*/
#include "CommonPrecompiled.h"
#include "InterfaceContext.h"
#include "InterfaceCommon.h"

#include "GraphicsSystem.h"

namespace GUI
{
#if defined(GRAPHICS_API_OPENGL)

#if defined(INTERFACE_IMGUI)

  static GLFWwindow*  GlobalWindow    = nullptr;
  static f32          FrameTime       = 0.0f;
  static bool         MousePressed[3] = { false, false, false };
  static f32          MouseWheel      = 0.0f;
  static u32          FontTexture     = 0;

  static void InterfaceRenderDrawList(ImDrawData* data)
  {
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnable(GL_TEXTURE_2D);

    // Setup orthographic projection matrix
    const float width = ImGui::GetIO().DisplaySize.x;
    const float height = ImGui::GetIO().DisplaySize.y;
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0f, width, height, 0.0f, -1.0f, +1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Render command lists
#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
    for(int n = 0; n < data->CmdListsCount; n++)
    {
      const ImDrawList* cmd_list = data->CmdLists[n];
      const unsigned char* vtx_buffer = (const unsigned char*)&cmd_list->VtxBuffer.front();
      const ImDrawIdx* idx_buffer = &cmd_list->IdxBuffer.front();
      glVertexPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, pos)));
      glTexCoordPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, uv)));
      glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, col)));

      for(int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); cmd_i++)
      {
        const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
        if(pcmd->UserCallback)
        {
          pcmd->UserCallback(cmd_list, pcmd);
        }
        else
        {
          glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
          glScissor((int)pcmd->ClipRect.x, (int)(height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
          glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, GL_UNSIGNED_SHORT, idx_buffer);
        }
        idx_buffer += pcmd->ElemCount;
      }
    }
#undef OFFSETOF

    // Restore modified state
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindTexture(GL_TEXTURE_2D, 0);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
  }

  static const c08* InterfaceGetClipboardText()
  {
    return glfwGetClipboardString(GlobalWindow);
  }

  static void InterfaceSetClipboardText(const c08* text)
  {
    glfwSetClipboardString(GlobalWindow, text);
  }

  void InterfaceInitialize(void* window, void* device, void* context)
  {
    GlobalWindow = RECAST(GLFWwindow*, window);

    ImGuiIO& io = ImGui::GetIO();
    io.KeyMap[ImGuiKey_Tab]         = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow]   = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow]  = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow]     = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow]   = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp]      = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown]    = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home]        = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End]         = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Delete]      = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace]   = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Enter]       = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape]      = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A]           = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C]           = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V]           = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X]           = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y]           = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z]           = GLFW_KEY_Z;

    io.RenderDrawListsFn = InterfaceRenderDrawList;
    io.SetClipboardTextFn = InterfaceSetClipboardText;
    io.GetClipboardTextFn = InterfaceGetClipboardText;
#ifdef _WIN32
    io.ImeWindowHandle = glfwGetWin32Window(GlobalWindow);
#endif
  }

  void InterfaceShutdown(void)
  {
    InterfaceInvalidateDeviceObjects();
    ImGui::Shutdown();
  }

  void InterfaceUpdate(void)
  {
    if(!FontTexture)
      InterfaceCreateDeviceObjects();

    ImGuiIO& io = ImGui::GetIO();

    // Setup display size (every frame to accommodate for window resizing)
    int w, h;
    int display_w, display_h;
    glfwGetWindowSize(GlobalWindow, &w, &h);
    glfwGetFramebufferSize(GlobalWindow, &display_w, &display_h);
    io.DisplaySize = ImVec2((float)display_w, (float)display_h);

    // Setup time step
    double current_time = glfwGetTime();
    io.DeltaTime = FrameTime > 0.0 ? (float)(current_time - FrameTime) : (float)(1.0f / 60.0f);
    FrameTime = (float)current_time;

    // Setup inputs
    // (we already got mouse wheel, keyboard keys & characters from glfw callbacks polled in glfwPollEvents())
    if(glfwGetWindowAttrib(GlobalWindow, GLFW_FOCUSED))
    {
      double mouse_x, mouse_y;
      glfwGetCursorPos(GlobalWindow, &mouse_x, &mouse_y);
      mouse_x *= (float)display_w / w;                        // Convert mouse coordinates to pixels
      mouse_y *= (float)display_h / h;
      io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);   // Mouse position, in pixels (set to -1,-1 if no mouse / on another screen, etc.)
    }
    else
    {
      io.MousePos = ImVec2(-1, -1);
    }

    for(int i = 0; i < 3; i++)
    {
      io.MouseDown[i] = MousePressed[i] || glfwGetMouseButton(GlobalWindow, i) != 0;    // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
      MousePressed[i] = false;
    }

    io.MouseWheel = MouseWheel;
    MouseWheel = 0.0f;

    // Hide OS mouse cursor if ImGui is drawing it
    glfwSetInputMode(GlobalWindow, GLFW_CURSOR, io.MouseDrawCursor ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);

    // Start the frame
    ImGui::NewFrame();
  }

  void InterfaceInvalidateDeviceObjects(void)
  {
    if(FontTexture)
    {
      glDeleteTextures(1, &FontTexture);
      ImGui::GetIO().Fonts->TexID = 0;
      FontTexture = 0;
    }
  }

  void InterfaceCreateDeviceObjects(void)
  {
    ImGuiIO& io = ImGui::GetIO();

    // Build texture
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsAlpha8(&pixels, &width, &height);

    // Create texture
    glGenTextures(1, &FontTexture);
    glBindTexture(GL_TEXTURE_2D, FontTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels);

    // Store our identifier
    io.Fonts->TexID = (void *)(intptr_t)FontTexture;

    // Cleanup (don't clear the input data if you want to append new fonts later)
    io.Fonts->ClearInputData();
    io.Fonts->ClearTexData();
  }

  void InterfaceMouseButtonCallback(GLFWwindow* window, s32 button, s32 action, s32 mods)
  {
    if(action == GLFW_PRESS && button >= 0 && button < 3)
      MousePressed[button] = true;
  }

  void InterfaceScrollCallback(GLFWwindow* window, f64 offset_x, f64 offset_y)
  {
    MouseWheel += (f32)offset_y;
  }

  void InterfaceKeyCallback(GLFWwindow* window, s32 key, s32 scancode, s32 action, s32 mods)
  {
    ImGuiIO& io = ImGui::GetIO();
    if(action == GLFW_PRESS)
      io.KeysDown[key] = true;
    if(action == GLFW_RELEASE)
      io.KeysDown[key] = false;

    (void)mods; // Modifiers are not reliable across systems
    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
  }

  void InterfaceCharCallback(GLFWwindow* window, u32 c)
  {
    ImGuiIO& io = ImGui::GetIO();
    if(c > 0 && c < 0x10000)
      io.AddInputCharacter((unsigned short)c);
  }

#else
  void InterfaceInitialize(void* window, void* device, void* context) { }
  void InterfaceShutdown(void) { }
  void InterfaceUpdate(void) { }

  void InterfaceInvalidateDeviceObjects(void) { }
  void InterfaceCreateDeviceObjects(void) { }
#endif

#endif
}