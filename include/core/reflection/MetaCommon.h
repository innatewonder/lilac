/*
*  FILE          MetaCommon.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for common meta features.
*/
#pragma once

#define CLASS(...)

#define FIELD(...)

#define FUNCTION(...)

#define ENUM(...)

#define ENUM_META(...)

#define GENERATED_CLASS_BODY(...)                                   \
INLINE static const Meta::MetaData* GetMetaData(void);              \
INLINE virtual const Meta::MetaData* GetReflectionData(void) const  \
{                                                                   \
  return GetMetaData();                                             \
}                                                                   \

#define GENERATED_STRUCT_BODY(...) \
static INLINE const Meta::MetaData* GetMetaData(void);

#define METATYPE(T) (Meta::TypeSingleton<Meta::TypeSingleton<T>::Type>::Get())

#define META_INTEGRAL_TYPE(T)                                                           \
template <>                                                                             \
class TypeSingleton <T>                                                                 \
{                                                                                       \
  public:                                                                               \
    typedef T Type;                                                                     \
                                                                                        \
    static const MetaData* Get(void)                                                    \
    {                                                                                   \
      static Meta::MetaData meta(#T, sizeof(T), nullptr, 0, nullptr, nullptr);          \
      Register(&meta);                                                                  \
      return &meta;                                                                     \
    }                                                                                   \
                                                                                        \
    static Type* NullCast(void) { return nullptr; }                                     \
                                                                                        \
    static void Register(const MetaData* meta)                                          \
    {                                                                                   \
      CCAST(Meta::MetaData*, meta)->SetSerializationFunction(TextSerializeIntegral<T>); \
      CCAST(Meta::MetaData*, meta)->SetDisplayFunction(GUI::Display<T>);                \
    }                                                                                   \
};                                                                                      \

namespace Meta
{
  class VariantReference;
  class MetaProperty;
  typedef void(*SerializeFn)(std::ostream&, Meta::VariantReference&);
  typedef void(*DeserializeFn)(std::istream&, Meta::VariantReference&);
  typedef void(*DisplayFn)(Meta::VariantReference&, const Meta::MetaProperty*);

  class MetaData;

  template <typename T>
  class TypeSingleton
  {
    public:
      typedef T Type;

      static const MetaData* Get(void)
      {
        const MetaData* meta = Type::GetMetaData();
        Register(meta);
        return meta;
      }

      static Type* NullCast(void) { return RECAST(Type*, nullptr); }

      static void Register(const MetaData* meta);
  };

  template<typename T>
  class TypeSingleton<const T> : public TypeSingleton<T>
  { };

  template<typename T>
  class TypeSingleton<T&> : public TypeSingleton<T>
  { };

  template<typename T>
  class TypeSingleton<const T&> : public TypeSingleton<T>
  { };

  template<typename T>
  class TypeSingleton<T*> : public TypeSingleton<T>
  { };

  template<typename T>
  class TypeSingleton<const T*> : public TypeSingleton<T>
  { }; 
}


template <typename T>
class IsValue           { static const bool value = true; };

template <typename T>
class IsValue<T*>       { static const bool value = false; };

template <typename T>
class IsValue<T&>       { static const bool value = false; };


template <typename T>
class IsPointer         { static const bool value = false; };

template <typename T>
class IsPointer<T*>     { static const bool value = true; };

template <typename T>
class IsPointer<T&>     { static const bool value = false; };


template <typename T>
class IsReference       { static const bool value = false; };

template <typename T>
class IsReference<T*>   { static const bool value = false; };

template <typename T>
class IsReference<T&>   { static const bool value = true; };


template <typename T>
class IsConst           { static const bool value = false; };

template <typename T>
class IsConst<const T>  { static const bool value = true; };

template <typename T>
class IsConst<T*>       { static const bool value = false; };

template <typename T>
class IsConst<const T*> { static const bool value = true; };

template <typename T>
class IsConst<T&>       { static const bool value = false; };

template <typename T>
class IsConst<const T&> { static const bool value = true; };

#include "MetaCommon.hpp"