/////////////////
//IT IS HIGHLY SUGGESTED THAT THIS FILE IS IN A PRECOMPILED HEADER
/////////////////

#pragma once
/////////////////
//Some Default Includes
#include <iostream>
#include <string>
#include <chrono>
#include <functional>

typedef std::string String;
const String EMPTY_STRING = "";

// containers
#include "ContainerDefinitions.h"

#define PLAT_WINDOWS  1
#define PLAT_MAC      2
#define PLAT_UNIX     3

#if defined(_WIN32)
  #define PLATFORM PLAT_WINDOWS
#elif defined(__APPLE__)
  #define PLATFORM PLAT_MAC
#else
  #define PLATFORM PLAT_UNIX
#endif

/////////////////
//WARNING SUPRESSIONS
#pragma warning( disable : 4267 )

/////////////////
//ASSERTIONS
#include <cassert>

#ifdef _DEBUG
  #define BREAK __debugbreak()
#else
  #define BREAK 
#endif

#ifdef _USE_CONTROL_ADV_ASSERT_
  #ifdef _DEBUG
    #define assertion(x) \
    { \
      if(!(x)) \
      { \
        std::cout << "Assert " << __FILE__ << ":" << __LINE__ << "(" << #x << ")\n"; \
        BREAK; \
      } \
    }
  #else
    #define assertion(x) {}
  #endif//_DEBUG
#else
  #define assertion(x) assert(x)
#endif //_USE_CONTROL_ADV_ASSERT_

#define SOFTASSERT(statement, msg, retval) \
  if(!(statement)) \
  { \
    std::cerr << "::SoftAssert::" << __FILE__ << ":" << __LINE__ << " " << msg << std::endl; \
    return retval; \
  }

/////////////////
//SUPER HELPFUL FOR VS TODO OUTPUT
#define STRINGIZE_(X) #X
#define STRINGIZE(X) STRINGIZE_(X)

#if PLATFORM == PLAT_WINDOWS
  #define TODO(X) \
    __pragma(message(__FILE__ "(" STRINGIZE(__LINE__) "): TODO " X))
#else
  #define TODO_MSG(X) _Pragma(#X)
  #define TODO(X) TODO_MSG(message("TODO " X))
#endif

/////////////////
//LOGGER
#define LOG(x) std::cout << x << std::endl;
#define WARN(x) std::cout << "[WARNING]: " << x << std::endl;
#define ERR(x) std::cout << "::[ERROR]:: " << x << std::endl; BREAK;

/////////////////
//DEFAULT TYPE DEFINITIONS
#include <stdint.h>

typedef char      c08;

typedef int8_t    s08;
typedef uint8_t   u08;

typedef int16_t   s16;
typedef uint16_t  u16;

typedef int32_t   s32;
typedef uint32_t  u32;

typedef int64_t   s64;
typedef uint64_t  u64;

typedef float     f32;
typedef double    f64;

/////////////////
//WRAPPERS FOR CASTS
#define DYNCAST(newClass, var) dynamic_cast<newClass>(var)
#define RECAST(newClass, var) reinterpret_cast<newClass>(var)
#define SCAST(newType, var) static_cast<newType>(var)
#define CCAST(newType, var) const_cast<newType>(var)

#define CONCATENATE_REAL(A, B) A ## B
#define CONCATENATE(A, B) CONCATENATE_REAL(A, B)

#define INLINE inline
#if PLATFORM == PLAT_WINDOWS
  #define FORCEINLINE __forceinline
#else
  #define FORCEINLINE inline
#endif

#if PLATFORM == PLAT_WINDOWS
  #define NOEXCEPT _NOEXCEPT
#else
  #define NOEXCEPT noexcept
#endif

#define POINTER_OFFSET(PTR, OFFSET) \
  ((void*)(((c08*)(PTR)) + (OFFSET)))
