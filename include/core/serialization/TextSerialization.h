/*
*  FILE          TextSerialization.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for text serialization/deserialization in standard output streams and file IO.
*/
#pragma once

namespace Meta
{
  class VariantReference;
}

void TextSerialize(std::ostream& os, Meta::VariantReference& ref);

template <typename T>
void TextSerializeIntegral(std::ostream& os, Meta::VariantReference& ref)
{
  os << ref.Value<Meta::TypeSingleton<T>::Type>();
}



void TextDeserialize(std::istream& is, Meta::VariantReference& ref);

template <typename T>
void TextDeserializeIntegral(std::istream& is, Meta::VariantReference& ref)
{
  is << ref.Value<Meta::TypeSingleton<T>::Type>();
}