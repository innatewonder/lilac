/*
*  FILE          MetaCommon.hpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for common meta template functions.
*/

#include "TextSerialization.h"
#include "InterfaceReflectionWrapper.h"

namespace Meta
{
  template<typename T>
  void TypeSingleton<T>::Register(const MetaData* meta)
  {
    CCAST(MetaData*, meta)->SetSerializationFunction(TextSerialize);
    CCAST(MetaData*, meta)->SetDisplayFunction(GUI::Display<T>);
  }
}