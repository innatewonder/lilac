/*
*  FILE          MetaData.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration of functions for retrieving type reflection information.
*/
#pragma once

u32 StringHash(const c08* inString);

template <typename T>
inline std::string GetTypeName(void)
{ }

template <typename T>
inline u32 GetTypeID(void)
{
  static u32 typeID = StringHash(GetTypeName<T>().c_str());
  return typeID;
}

inline u32 HashThisString(const std::string &instring)
{
  return StringHash(instring.c_str());
}