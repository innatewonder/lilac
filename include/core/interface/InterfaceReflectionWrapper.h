/*
*  FILE          InterfaceReflectionWrapper.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for global wrapper functions used to interface with GUI libraries.
*/
#pragma once

#include "InterfaceCommon.h"

#define EXTRACT_META                                                                              \
  const Meta::MetaData*                 Meta        = ref.Meta();                                 \
  const Meta::MetaInterface*            Interface   = member->Interface();                        \
  const Meta::MetaReflectionDefinition& Definition  = Interface->Definition();                    \
  const c08* Label = Interface->Label()[0] != '\0' ? Interface->Label() : member->GetName().c_str(); \

namespace Meta
{
  class VariantReference;
  class MetaProperty;
  class MetaInterface;
}

namespace GUI
{
  // -- Common Types --
  void DisplayComment(const Meta::MetaInterface* Interface);

  void DisplaySeparator(const Meta::MetaInterface* Interface);


  // -- Meta Struct / Class Containers --
  template <typename T>
  void Display(Meta::VariantReference& ref, const Meta::MetaProperty* member);


  // -- Integral Types --
  template <>
  void Display<c08>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<s08>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<u08>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<s16>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<u16>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<s32>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<u32>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<f32>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<f64>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<bool>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<std::string>(Meta::VariantReference& ref, const Meta::MetaProperty* member);


  // -- Mythril Math Library Containers --
  template <>
  void Display<Math::Color>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<Math::LinearColor>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<Math::Vector2>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<Math::Vector3>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<Math::Vector4>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<Math::Point2>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<Math::Point4>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<Math::Quaternion>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<Math::Scale>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<Math::NumericVector2<s32>>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<Math::NumericVector3<s32>>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<Math::NumericVector4<s32>>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<Math::NumericPoint2<s32>>(Meta::VariantReference& ref, const Meta::MetaProperty* member);

  template <>
  void Display<Math::NumericPoint4<s32>>(Meta::VariantReference& ref, const Meta::MetaProperty* member);
}

#include "InterfaceReflectionWrapper.hpp"