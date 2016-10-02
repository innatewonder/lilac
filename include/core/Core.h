#pragma once

#include "Object.h"

void Run(ArgParser ars);

namespace Core
{
  class Core : public System
  {
  public:
    Core();
    ~Core();

    void PreInitialize(ArgParser& args);

    virtual bool Initialize(ArgParser& args);
    virtual void Destroy();
    virtual void Test();
    virtual void Tick(f32 dt);

    void RegisterObject(Object* obj);
    void MarkObjectForDeath(Object* obj);

    u32 NumObjects() const;

    void Run();
    void Quit();
    void AddSystem(System* sys);
    System* GetSystem(Sys::SystemDef sysId) const;

    void SendMessage(Message* msg);

    virtual void HandleMessage(Message* msg);

    void Pool(ThreadJob* job);
    void WaitForPool() const;
  private:
    Containers::Vector<System*> m_systems;
    Containers::List<Object*> m_objects;
    Containers::List<Object*> m_toDestroy;

    ThreadPool* m_threadPool;

    bool m_quit;
  };

  extern Core* gCore;
}

#define GETSYSTEM(sys) RECAST(sys*, Core::gCore->GetSystem(Sys::sys))
