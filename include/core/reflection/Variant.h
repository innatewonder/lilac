/*
*  FILE          Variant.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for variant structures for type reflection.
*/
#pragma once

namespace Meta
{
  class MetaData;
  class VariantValue;
  class VariantReference;
  class VariantCommon
  {
    protected:
      VariantCommon();
      VariantCommon(const MetaData* meta_, void* data_);

    public:
      const MetaData* Meta(void) const;
      template <typename T> T& Value(void);
      template <typename T> const T& Value(void) const;
      void* Data(void) const;

    protected:
      const MetaData* meta;
      void* data;
  };

  class VariantValue : public VariantCommon
  {
    public:
      VariantValue();
      VariantValue(const VariantValue& rhs);
      VariantValue(const VariantReference& rhs);
      VariantValue(const MetaData* meta_, void* data_);

      template <typename T>
      VariantValue(const T& value);

      VariantValue& operator=(const VariantValue& rhs);
      VariantValue& operator=(const VariantReference& rhs);

      template <typename T>
      VariantValue& operator=(const T& rhs);
  };

  class VariantReference : public VariantCommon
  {
    public:
      VariantReference();
      VariantReference(const VariantReference& rhs);
      VariantReference(const VariantValue& rhs);
      VariantReference(const MetaData* meta_, void* data_);

      template <typename T>
      VariantReference(const T& value);

      VariantReference& operator=(const VariantReference& rhs);
      VariantReference& operator=(const VariantValue& rhs);

      template <typename T>
      VariantReference& operator=(const T& rhs);
  };
}

#include "Variant.hpp"