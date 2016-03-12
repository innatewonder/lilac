#pragma once

namespace Core
{
  class CoreUtils
  {
  public:
    CoreUtils();
    ~CoreUtils();

    UID NextUID();

  private:
    ThreadSafeVar<UID> m_nextUID;
  };
}

extern Core::CoreUtils* gCoreUtils;
