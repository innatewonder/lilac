#pragma once

class Message
{
public:
  enum MessageType
  {
    MSG_KEY,
    MSG_WINDOW,
    MSG_RESIZE,
    MSG_MOUSE,
    MSG_MOUSE_BUTTON,
    MSG_SCROLL,
  };

  Message(MessageType type);
  ~Message();

  void AddData(const void* data, s32 dataSize);

  template <typename T>
  void AddData(const T data)
  {
    AddData(&data, sizeof(T));
  }

  MessageType GetType();
  void Reset();

  template <typename T>
  T* GetFormatedData()
  {
    T* ret = SCAST(T*, (void*)m_dataPtr);
    m_dataPtr += sizeof(T);
    return ret;
  }

private:
  MessageType m_type;

  char*       m_data;
  char*       m_dataPtr;
  s32         m_dataSize;
};

#define MESSAGE(type) Memory::New<Message>(type)
#define DAT(x) &x, sizeof(x)
