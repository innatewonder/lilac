/*
*  FILE          MetaData.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for meta data structures.
*/
#pragma once

#include "InterfaceReflectionWrapper.h"
#include "TextSerialization.h"

namespace Meta
{
  class MetaInterface;

  class MetaProperty
  {
    public:
      MetaProperty(const MetaData* meta_,
                   const c08* name_,
                   const u32 offset_,
                   const MetaInterface* interface_);

      const std::string& GetName(void) const;
      u32 GetIdentifier(void) const;
      u32 GetOffset(void) const;

      const MetaData* Meta(void) const;
      const MetaProperty* Next(void) const;

      void SetNext(const MetaProperty* next_);

      const MetaInterface* Interface(void) const;

    private:
      const std::string name;
      const u32 identifier;
      const u32 offset;

      const MetaData* meta;
      const MetaProperty* next;

      const MetaInterface* gui_interface;
  };

  class MetaData
  {
    public:
      MetaData(const c08* name_,
               const u32 size_,
               const MetaProperty** properties_,
               const u32 property_count_,
               const MetaData* parent_,
               const MetaInterface* interface_);

      typedef Containers::List<const MetaProperty*> PropertyList;
      typedef Containers::Map<std::string, PropertyList> CategoryMap;
      void* New(void) const;
      void* New(const void* src) const;
      void Copy(const void* src, void* dst) const;
      void Delete(void* dst) const;

      const c08* GetName(void) const;
      u32 GetSize(void) const;
      u32 GetIdentifier(void) const;
      const MetaData* GetParent(void) const;

      const CategoryMap& Categories(void) const;
      const MetaProperty* Members(void) const;
      const MetaInterface* Interface(void) const;

      void SetSerializationFunction(SerializeFn function = nullptr);
      void SetDeserializationFunction(DeserializeFn function = nullptr);
      void SetDisplayFunction(DisplayFn function = nullptr);

      void Serialize(std::ostream& os, VariantReference& ref) const;
      void Deserialize(std::istream& is, VariantReference& ref) const;
      void Display(VariantReference& ref, const MetaProperty* def) const;

    private:
      void GeneratePropertyMap(const MetaProperty** property_list);

      CategoryMap                                         categories;
      Containers::UnorderedMap<u32, const MetaProperty*>  properties;
      const u32                                           property_count;
      const u32                                           property_count_total;
      const MetaProperty*                                 property_begin;
      

      SerializeFn   serialize;
      DeserializeFn deserialize;
      DisplayFn     display;

      const c08*      name;
      const u32       size;
      const u32       identifier;
      const MetaData* parent;

      const MetaInterface* gui_interface;
  };

  META_INTEGRAL_TYPE(u08);
  META_INTEGRAL_TYPE(c08);
  META_INTEGRAL_TYPE(u16);
  META_INTEGRAL_TYPE(s16);
  META_INTEGRAL_TYPE(u32);
  META_INTEGRAL_TYPE(s32);
  META_INTEGRAL_TYPE(u64);
  META_INTEGRAL_TYPE(s64);
  META_INTEGRAL_TYPE(f32);
  META_INTEGRAL_TYPE(f64);
  META_INTEGRAL_TYPE(bool);
  META_INTEGRAL_TYPE(std::string);

  META_INTEGRAL_TYPE(Math::Color);
  META_INTEGRAL_TYPE(Math::LinearColor);
  META_INTEGRAL_TYPE(Math::Vector2);
  META_INTEGRAL_TYPE(Math::Vector3);
  META_INTEGRAL_TYPE(Math::Vector4);
  META_INTEGRAL_TYPE(Math::Point2);
  META_INTEGRAL_TYPE(Math::Point4);
  META_INTEGRAL_TYPE(Math::Quaternion);
  META_INTEGRAL_TYPE(Math::Scale);
  META_INTEGRAL_TYPE(Math::NumericVector2<s32>);
  META_INTEGRAL_TYPE(Math::NumericVector3<s32>);
  META_INTEGRAL_TYPE(Math::NumericVector4<s32>);
  META_INTEGRAL_TYPE(Math::NumericPoint2<s32>);
  META_INTEGRAL_TYPE(Math::NumericPoint4<s32>);
}

#include "MetaInterface.h"
