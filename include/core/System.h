#pragma once

class System
{
public:
  virtual ~System() {};

  virtual bool Initialize(ArgParser& args) = 0;
  virtual void Destroy() = 0;
  virtual void Test() = 0;
  virtual void Tick(f32 dt) = 0;
  virtual void HandleMessage(Message* msg) = 0;

  virtual void RegisterComponent(Component* comp);
  virtual void UnregisterComponent(Component* comp);
  virtual u32  NumComponents() const;

protected:
  Containers::List<Component*> m_components;
};
