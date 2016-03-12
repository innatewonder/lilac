#pragma once

class Component
{
public:
  Component();
  virtual ~Component();

  virtual void Initialize() {};
  void SetType(Comp::ComponentDef type);
  void SetParent(Object* parent);

  UID GetUID() const;
  Comp::ComponentDef GetTypeID() const;
  Object* GetParent() const;
  const String& GetName() const;
protected:
  Object* m_parent;

private:
  Comp::ComponentDef m_typeID;
  UID m_id;
};
