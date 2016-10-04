#pragma warning( disable : 4267 )

//#define GLEW_STATIC
//Common Include and Macros
#include "Config.h"
#include "SuperCommon.h"

//very helpful
#include <regex>
#include <stdlib.h>

//GMock Includes
#if PLATFORM != PLAT_ANDROID
  #include "gtest/gtest.h"
  #include "gmock/gmock.h"
#endif

//OpenGL Includes
#if PLATFORM == PLAT_ANDROID
  #include <GLES2/gl2.h>
  typedef s32 GraphicsWindow;
#else  
  #include <GL/glew.h>
  #include "GL/glfw3.h"
  typedef GLFWwindow GraphicsWindow;
#endif

#if PLATFORM == PLAT_WINDOWS
  #undef APIENTRY
  #define GLFW_EXPOSE_NATIVE_WIN32
  #define GLFW_EXPOSE_NATIVE_WGL
  #define WIN32_LEAN_AND_MEAN
  #define NOMINMAX
  #include <GL/glfw3native.h>
  #include <winsock2.h>
  #include <Ws2tcpip.h>
  #undef SetPort
  #undef near
  #undef far
#endif

//Math
#include "MathIncludes.h"

#define SLEEP_MILLI(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))

#include "Memory.h"

//ThreadLibrary
#include "HBThread.h"
#include "UpdateType.h" 

typedef u32 UID;
#include "CoreUtils.h"
#include "ArgParser.h"

// engine
#include "Factory.h"
#include "Message.h"
#include "Event.h"

#include "Timer.h"
#include "Component.h"
#include "Object.h"
#include "System.h"

#include "Core.h"
#include "SystemIncludes.h"
