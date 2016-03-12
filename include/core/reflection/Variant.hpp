/*
*  FILE          Variant.hpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Implementation for variant structure template functions.
*/

namespace Meta
{
  template <typename T>
  T& VariantCommon::Value(void)
  {
    return *RECAST(T*, data);
  }

  template <typename T>
  const T& VariantCommon::Value(void) const
  {
    return *RECAST(T*, data);
  }



  template <typename T>
  VariantValue::VariantValue(const T& value)
    : VariantCommon(METATYPE(T), nullptr)
  {
    data = meta->New(&value);
  }

  template <typename T>
  VariantValue& VariantValue::operator=(const T& rhs)
  {
    if(meta != METATYPE(T))
    {
      meta->Delete(data);

      meta = METATYPE(T);
      assertion(meta);
      data = meta->New(&rhs);
    }
    else
    {
      meta->Copy(&rhs, data);
    }
    return *this;
  }



  template <typename T>
  VariantReference::VariantReference(const T& value)
    : VariantCommon(METATYPE(T), CCAST(T*, &value))
  { }

  template <typename T>
  VariantReference& VariantReference::operator=(const T& rhs)
  {
    meta = METATYPE(T);
    data = CCAST(T*, &rhs);
    return *this;
  }
}