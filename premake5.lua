solution "mythril"
  configurations { "Debug", "Release" }
  platforms {"x64"}

  configuration { "Debug" }
    targetdir "bin/debug"

  configuration { "Release" }
    targetdir "bin/release"

  if _ACTION == "clean" then
    os.rmdir("bin/debug", "bin/release")
  end

------------------------
------EXE
------------------------
  project "mythril"
    language "C++"
    kind     "ConsoleApp"

    files  {"src/*.cpp", "src/core/**.cpp",
     "include/**.h", "include/**.hpp",
    }
    links  { 
    "glew32",
    "Test",
    "GraphicsSystem",
    "PhysicsSystem",
    "GenerationSystem",
    "Math",
    "NetworkingSystem",
    
    "AudioSystem",
    "fmod64_vc",

      "gmock", 
      --"liblua52", 
    }

    libdirs { "lib/",
    }

    if(os.get() == "windows") then
      debugenvs "PATH=%PATH%;$(ProjectDir)"
      links { 
        "opengl32", 
        "glfw3", 
        "wsock32",
        "Ws2_32"
      }

    elseif(os.get() == "linux") then
      buildoptions { "-std=c++11" }
      links {
      "glfw3", 
      "GLU", 
      
      "rt", 
      "Xrandr", 
      "Xi", 
      "Xxf86vm", 
      "m", 
      "GL", 
      "dl", 
      "pthread", 
      "X11",
      "Xcursor",
      "Xinerama",
      }
    end

    defines{
    "_VARIADIC_MAX=10",
    }

    includedirs {
    "include",
    "include/**", "$(EXTERNALSROOT)/gmock-1.7.0/include",
    "$(EXTERNALSROOT)/gmock-1.7.0/gtest/include"
    }


    if(_ACTION == "gmake") then
      buildoptions {"-std=c++11"}

      pchheader ( "include/CommonPrecompiled.h" )
    else
      pchheader ( "CommonPrecompiled.h" )
    end
    pchsource ( "src/CommonPrecompiled.cpp" )


    flags { 
    "NoIncrementalLink", "StaticRuntime",
    "Unicode"}

    configuration { "Debug*" }
      defines { "_DEBUG", "DEBUG", "GLEW_STATIC", }
      flags   { "Symbols" }
      libdirs { "lib/debug",
      }

      if(_ACTION == "gmake") then
        libdirs {"$(EXTERNALSROOT)/gmock-1.7.0/lib/"}
      else
        libdirs {"$(EXTERNALSROOT)/gmock-1.7.0/msvc/2013/x64/$(Configuration)"}
      end

    configuration { "Release*" }
      defines { "NDEBUG", "GLEW_STATIC", }
      libdirs { "lib/release",
      }

      if(_ACTION == "gmake") then
        libdirs {"$(EXTERNALSROOT)/gmock-1.7.0/lib/"}
      else
        libdirs {"$(EXTERNALSROOT)/gmock-1.7.0/msvc/2013/x64/$(Configuration)"}
      end

------------------------
------GraphicsSystem LIB
------------------------
  project "GraphicsSystem"
    location "settings"
    language "C++"
    kind     "StaticLib"
    objdir "!obj/%{cfg.platform}/%{cfg.buildcfg}/libObjs"

    files  { 
    "src/CommonPrecompiled.cpp",
 "src/graphics/**.cpp", "include/**.h", "include/**.hpp" }

    defines{
      "_CRT_SECURE_NO_WARNINGS",
    }

    includedirs {
    "include",
    "include/**", "$(EXTERNALSROOT)/gmock-1.7.0/include",
    "$(EXTERNALSROOT)/gmock-1.7.0/gtest/include",
    }

    if(_ACTION == "gmake") then
      buildoptions {"-std=c++11"}

      pchheader ( "../include/CommonPrecompiled.h" )
    else
      pchheader ( "CommonPrecompiled.h" )
    end
    pchsource ( "src/CommonPrecompiled.cpp" )
    
    flags { "NoIncrementalLink", "StaticRuntime",
    "Unicode"}

    configuration { "Debug*" }
      defines { "_DEBUG", "DEBUG" }
      flags   { "Symbols" }
      libdirs { "lib/debug", 
      }

    configuration { "Release*" }
      defines { "NDEBUG" }
      libdirs { "lib/release",       }

------------------------
------testing LIB
------------------------
  project "Test"
    location "settings"
    language "C++"
    kind     "StaticLib"
    objdir "!obj/%{cfg.platform}/%{cfg.buildcfg}/libObjs"

    files  { 
    "src/CommonPrecompiled.cpp",
 "src/test/**.cpp", "include/**.h", "include/**.hpp" }

    defines{
    "_CRT_SECURE_NO_WARNINGS",
    }

    includedirs {
    "include",
    "include/**", "$(EXTERNALSROOT)/gmock-1.7.0/include",
    "$(EXTERNALSROOT)/gmock-1.7.0/gtest/include",
    }

    if(_ACTION == "gmake") then
      buildoptions {"-std=c++11"}

      pchheader ( "../include/CommonPrecompiled.h" )
    else
      pchheader ( "CommonPrecompiled.h" )
    end
    pchsource ( "src/CommonPrecompiled.cpp" )
    
    flags { "NoIncrementalLink", "StaticRuntime",
    "Unicode"}

    configuration { "Debug*" }
      defines { "_DEBUG", "DEBUG" }
      flags   { "Symbols" }
      libdirs { "lib/debug", 
      }

    configuration { "Release*" }
      defines { "NDEBUG" }
      libdirs { "lib/release",       }


------------------------
------physics LIB
------------------------
  project "PhysicsSystem"
    location "settings"
    language "C++"
    kind     "StaticLib"
    objdir "!obj/%{cfg.platform}/%{cfg.buildcfg}/libObjs"

    files  { 
    "src/CommonPrecompiled.cpp",
 "src/physics/**.cpp", "include/**.h", "include/**.hpp" }

    defines{
    "_CRT_SECURE_NO_WARNINGS",
    }

    includedirs {
    "include",
    "include/**", "$(EXTERNALSROOT)/gmock-1.7.0/include",
    "$(EXTERNALSROOT)/gmock-1.7.0/gtest/include",
    }

    if(_ACTION == "gmake") then
      buildoptions {"-std=c++11"}

      pchheader ( "../include/CommonPrecompiled.h" )
    else
      pchheader ( "CommonPrecompiled.h" )
    end
    pchsource ( "src/CommonPrecompiled.cpp" )
    
    flags { "NoIncrementalLink", "StaticRuntime",
    "Unicode"}

    configuration { "Debug*" }
      defines { "_DEBUG", "DEBUG" }
      flags   { "Symbols" }
      libdirs { "lib/debug", 
      }

    configuration { "Release*" }
      defines { "NDEBUG" }
      libdirs { "lib/release",       }

------------------------
------testing LIB
------------------------
  project "Test"
    location "settings"
    language "C++"
    kind     "StaticLib"
    objdir "!obj/%{cfg.platform}/%{cfg.buildcfg}/libObjs"

    files  { 
    "src/CommonPrecompiled.cpp",
 "src/test/**.cpp", "include/**.h", "include/**.hpp" }

    defines{
    "_CRT_SECURE_NO_WARNINGS",
    }

    includedirs {
    "include",
    "include/**", "$(EXTERNALSROOT)/gmock-1.7.0/include",
    "$(EXTERNALSROOT)/gmock-1.7.0/gtest/include",
    }

    if(_ACTION == "gmake") then
      buildoptions {"-std=c++11"}

      pchheader ( "../include/CommonPrecompiled.h" )
    else
      pchheader ( "CommonPrecompiled.h" )
    end
    pchsource ( "src/CommonPrecompiled.cpp" )
    
    flags { "NoIncrementalLink", "StaticRuntime",
    "Unicode"}

    configuration { "Debug*" }
      defines { "_DEBUG", "DEBUG" }
      flags   { "Symbols" }
      libdirs { "lib/debug", 
      }

    configuration { "Release*" }
      defines { "NDEBUG" }
      libdirs { "lib/release",       }

------------------------
------Generation LIB
------------------------
  project "GenerationSystem"
    location "settings"
    language "C++"
    kind     "StaticLib"
    objdir "!obj/%{cfg.platform}/%{cfg.buildcfg}/libObjs"

    files  { 
    "src/CommonPrecompiled.cpp",
 "src/generation/**.cpp", "include/**.h", "include/**.hpp" }

    defines{
    "_CRT_SECURE_NO_WARNINGS",
    }

    includedirs {
    "include",
    "include/**", "$(EXTERNALSROOT)/gmock-1.7.0/include",
    "$(EXTERNALSROOT)/gmock-1.7.0/gtest/include",
    }

    if(_ACTION == "gmake") then
      buildoptions {"-std=c++11"}

      pchheader ( "../include/CommonPrecompiled.h" )
    else
      pchheader ( "CommonPrecompiled.h" )
    end
    pchsource ( "src/CommonPrecompiled.cpp" )
    
    flags { "NoIncrementalLink", "StaticRuntime",
    "Unicode"}

    configuration { "Debug*" }
      defines { "_DEBUG", "DEBUG" }
      flags   { "Symbols" }
      libdirs { "lib/debug", 
      }

    configuration { "Release*" }
      defines { "NDEBUG" }
      libdirs { "lib/release",       }
      
------------------------
------Math LIB
------------------------
  project "Math"
    location "settings"
    language "C++"
    kind     "StaticLib"
    objdir "!obj/%{cfg.platform}/%{cfg.buildcfg}/libObjs"

    files { 
    "src/CommonPrecompiled.cpp",
    "src/math/**.cpp", "include/math/**.h", "include/math/**.hpp"
    }

    defines {
    "_CRT_SECURE_NO_WARNINGS",
    }

    includedirs {
    "include",
    "include/**", "$(EXTERNALSROOT)/gmock-1.7.0/include",
    "$(EXTERNALSROOT)/gmock-1.7.0/gtest/include",
    }

    if(_ACTION == "gmake") then
      buildoptions {"-std=c++11"}

      pchheader ( "../include/CommonPrecompiled.h" )
    else
      pchheader ( "CommonPrecompiled.h" )
    end
    pchsource ( "src/CommonPrecompiled.cpp" )
    
    flags { "NoIncrementalLink", "StaticRuntime", "Unicode"}

    configuration { "Debug*" }
      defines { "_DEBUG", "DEBUG" }
      flags   { "Symbols" }
      libdirs { "lib/debug" }

    configuration { "Release*" }
      defines { "NDEBUG" }
      libdirs { "lib/release" }

------------------------
------Networking LIB
------------------------
  project "NetworkingSystem"
    location "settings"
    language "C++"
    kind     "StaticLib"
    objdir "!obj/%{cfg.platform}/%{cfg.buildcfg}/libObjs"

    files { 
    "src/CommonPrecompiled.cpp",
    "src/networking/**.cpp", "include/networking/**.h", "include/networking/**.hpp"
    }

    defines {
    "_CRT_SECURE_NO_WARNINGS",
    "_WINSOCK_DEPRECATED_NO_WARNINGS"
    }

    includedirs {
    "include",
    "include/**", "$(EXTERNALSROOT)/gmock-1.7.0/include",
    "$(EXTERNALSROOT)/gmock-1.7.0/gtest/include",
    }

    if(_ACTION == "gmake") then
      buildoptions {"-std=c++11"}

      pchheader ( "../include/CommonPrecompiled.h" )
    else
      pchheader ( "CommonPrecompiled.h" )
    end
    pchsource ( "src/CommonPrecompiled.cpp" )
    
    flags { "NoIncrementalLink", "StaticRuntime", "Unicode"}

    configuration { "Debug*" }
      defines { "_DEBUG", "DEBUG" }
      flags   { "Symbols" }
      libdirs { "lib/debug" }

    configuration { "Release*" }
      defines { "NDEBUG" }
      libdirs { "lib/release" }

------------------------
------Audio LIB
------------------------
  project "AudioSystem"
    location "settings"
    language "C++"
    kind     "StaticLib"
    objdir "!obj/%{cfg.platform}/%{cfg.buildcfg}/libObjs"

    files { 
    "src/CommonPrecompiled.cpp",
    "src/audio/**.cpp", "include/audio/**.h", "include/audio/**.hpp"
    }

    defines {
    "_CRT_SECURE_NO_WARNINGS",
    "_WINSOCK_DEPRECATED_NO_WARNINGS"
    }

    includedirs {
    "include",
    "include/**", "$(EXTERNALSROOT)/gmock-1.7.0/include",
    "$(EXTERNALSROOT)/gmock-1.7.0/gtest/include",
    }

    if(_ACTION == "gmake") then
      buildoptions {"-std=c++11"}

      pchheader ( "../include/CommonPrecompiled.h" )
    else
      pchheader ( "CommonPrecompiled.h" )
    end
    pchsource ( "src/CommonPrecompiled.cpp" )
    
    flags { "NoIncrementalLink", "StaticRuntime", "Unicode"}

    configuration { "Debug*" }
      defines { "_DEBUG", "DEBUG" }
      flags   { "Symbols" }
      libdirs { "lib/debug" }

    configuration { "Release*" }
      defines { "NDEBUG" }
      libdirs { "lib/release" }