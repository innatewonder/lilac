#include "CommonPrecompiled.h"
#include "MessageSystem.h"

namespace Core
{
  MessageSystem::MessageSystem()
  {}

  MessageSystem::~MessageSystem()
  {}

  bool MessageSystem::Initialize(ArgParser& args)
  {
    return true;
  }

  void MessageSystem::Destroy()
  {
    m_messages.ClearWithDelete();
  }

  void MessageSystem::Test()
  {}

  void MessageSystem::Tick(f32 dt)
  {
    u32 num = m_messages.Size();
    for(u32 i = 0; i < num; ++i)
    {
      Message* msg = m_messages.Pop();
      gCore->HandleMessage(msg);
      Memory::Delete(msg);
    }
  }

  void MessageSystem::HandleMessage(Message* msg)
  {
  }

  void MessageSystem::SendMessage(Message* msg)
  {
    m_messages.Push(msg);
  }
}
