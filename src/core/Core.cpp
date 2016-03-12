#include "CommonPrecompiled.h"
#include "Core.h"

namespace Core
{
#define SYS_LOOP_MULTI for(System* sys : m_systems)
#define SYS_LOOP_SINGLE(inLoop) SYS_LOOP_MULTI inLoop

  Core* gCore = nullptr;
  
  Core::Core()
  {
    gCore = this;
  }

  Core::~Core()
  {
    gCore = nullptr;
  }

  bool Core::Initialize(ArgParser& args)
  {
    m_quit = args.Has("-ro");
    bool ret = true;
    m_threadPool = Memory::New<ThreadPool>();
    SYS_LOOP_MULTI
    {
      ret = ret ? sys->Initialize(args) : false;
    }
    return ret;
  }

  void Core::Destroy()
  {
    //clean up objects to destroy
    Tick(0);
    for(auto it = m_objects.begin(); it != m_objects.end(); ++it)
    {
      Factory::DestroyObject(*it);
    }

    Memory::Delete(m_threadPool);
    SYS_LOOP_MULTI
    {
      sys->Destroy();
      Memory::Delete(sys);
    }
  }

  void Core::Test()
  {
    SYS_LOOP_SINGLE(sys->Test());
  }

  void Core::AddSystem(System* sys)
  {
    m_systems.push_back(sys);
  }

  System* Core::GetSystem(Sys::SystemDef sysId) const
  {
    assertion(sysId < Sys::NUM_SYSTEMS);
    return m_systems[sysId];
  }

  void Core::PreInitialize(ArgParser& args)
  {}

  void Core::Tick(f32 dt)
  {
    m_threadPool->Update();
    for(auto it = m_toDestroy.begin(); it != m_toDestroy.end(); ++it)
    {
      Factory::DestroyObject(*it);
    }
    m_toDestroy.clear();
  }

  void Core::RegisterObject(Object* obj)
  {
    m_objects.push_back(obj);
  }

  void Core::MarkObjectForDeath(Object* obj)
  {
    m_objects.remove(obj);
    m_toDestroy.push_back(obj);
  }

  u32 Core::NumObjects() const
  {
    return m_objects.size();
  }

  void Core::Run()
  {
    Timer time;
    time.Start();

    do
    {
      f32 dt = time.GetDT_Sec();
      time.Step();

      SYS_LOOP_SINGLE(sys->Tick(dt));
      Tick(dt);
    } while(!m_quit);
  }

  void Core::Quit()
  {
    m_quit = true;
  }

  void Core::SendMessage(Message* msg)
  {
    RECAST(MessageSystem*, GetSystem(Sys::MessageSystem))->SendMessage(msg);
  }

  void Core::HandleMessage(Message* msg)
  {
    SYS_LOOP_MULTI
    {
      msg->Reset();
      sys->HandleMessage(msg);
    }
  }

  void Core::Pool(ThreadJob *job)
  {
    m_threadPool->AddJob(job);
  }

  void Core::WaitForPool() const
  {
    m_threadPool->SyncPoint();
  }

}
