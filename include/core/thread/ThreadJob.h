#pragma once

class ThreadJob
{
public:
  ThreadJob(bool postOnMainThread = false, const String& name = "")
    : m_postMainThread(postOnMainThread)
    , m_name(name)
  {}

  virtual void Execute() {};
  virtual void PostExecute() {};

  bool IsPostOnMainThread()
  {
    return m_postMainThread;
  }

  String Name()
  {
    return m_name;
  }

protected:
  String m_name;

private:
  bool m_postMainThread;
};
