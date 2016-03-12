#pragma once
#include "Message.h"

namespace Core
{
  class MessageSystem : public System
  {
  public:
    MessageSystem();
    ~MessageSystem();

    virtual bool Initialize(ArgParser& args);
    virtual void Destroy();
    virtual void Test();
    virtual void Tick(f32 dt);

    void SendMessage(Message* msg);

    virtual void HandleMessage(Message* msg);

  private:
    ThreadSafeQueue<Message*> m_messages;
  };
}
