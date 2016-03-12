#pragma once
class UpdateTypeBase
{
public:
  virtual void Update() = 0;
};

class UpdateTypeManager
{
public:
  UpdateTypeManager();
  void Register(UpdateTypeBase* t);
  void Update();

private:
  std::list<UpdateTypeBase*> m_vals;
};
extern UpdateTypeManager* UpdateMan;

/*
* This type calls given callback function upon changing
* Callback is passed the new value and given metadata
*/
template<typename T, typename metaT>
class UpdateType : public UpdateTypeBase
{
public:
  typedef void (*OnUpdateFunction)(T&, metaT&);

  UpdateType(const T& initalValue, OnUpdateFunction func, metaT& metaData)
    : m_value(initalValue), m_func(func), m_lastKnownValue(initalValue), m_meta(metaData)
  {
    UpdateMan->Register(this);
  }

  UpdateType()
    : m_func(nullptr) 
  {
    UpdateMan->Register(this);
  }

  //sets the update func -- needed if using default constructor
  void SetUpdateFunc(OnUpdateFunction func, metaT& metaData)
  {
    m_func = func;
    m_meta = metaData;
  }

  virtual void Update()
  {
    if(m_lastKnownValue != m_value)
    {
      m_lastKnownValue = m_value;
      UpdateNoSet();
    }
  }

  //Update internal value without calling callback
  void SetNoUpdate(const T& t)
  {
    m_value = t;
    m_lastKnownValue = t;
  }

  //Call callback without changing value
  void UpdateNoSet()
  {
    if(m_func)
      m_func(m_value, m_meta);
  }

  void operator=(const T& rhs)
  {
    m_value = rhs;
  }

  //get address of data instead of entire type
  T* operator&()
  {
    return (T*)((char*)this + offsetof(class UpdateType, m_value));
  }

  operator T() { return m_value; }

private:
  T m_value;
  T m_lastKnownValue;
  metaT m_meta;
  OnUpdateFunction m_func;
};
