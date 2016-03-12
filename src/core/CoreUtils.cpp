#include "CommonPrecompiled.h"
#include "CoreUtils.h"

Core::CoreUtils* gCoreUtils = nullptr;

namespace Core
{
  CoreUtils::CoreUtils()
    : m_nextUID(0)
  {
    gCoreUtils = this;
  }

  CoreUtils::~CoreUtils()
  {
    gCoreUtils = nullptr;
  }

  UID CoreUtils::NextUID()
  {
    return ++m_nextUID;
  }
}
