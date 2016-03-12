#pragma once

class Object
{
public:
  Object();
  ~Object();

  void Kill();
  bool MarkedForDeath();

  bool AddComponent(Component* comp);
  Component* AddComponent(Comp::ComponentDef type);

  //Note: Objects own components, so components will be deleted upon removal
  bool RemoveComponent(Component* comp);
  bool RemoveComponent(UID id);
  bool RemoveComponent(Comp::ComponentDef type);

  Component* GetComponent(Comp::ComponentDef type);
  Containers::List<Component*> GetComponentType(Comp::ComponentDef type);
  Containers::List<Component*>& GetComponents(void);

  UID GetUID() const;

private:
  Containers::List<Component*> m_components;
  UID m_uid;

  bool m_shouldDestroy;
};
