/*
 *  FILE          TestNumericVector.cpp
 *  AUTHOR        Brendon Clifford
 *  DESCRIPTION
 *    Test numeric vector functionality.
 */
#include "CommonPrecompiled.h"
#include "TestMath.h"

namespace Test
{
  typedef ::testing::Types <f32, u32, s32, f64> Implementations;

  template<class T>
  class NumericVector2Test : public testing::Test { };
  TYPED_TEST_CASE(NumericVector2Test, Implementations);

  TYPED_TEST(NumericVector2Test, Vector_Static_Members)
  {
    EXPECT_TRUE(Compare(Math::NumericVector2<TypeParam>::ZERO, TypeParam(0), TypeParam(0)));
    EXPECT_TRUE(Compare(Math::NumericVector2<TypeParam>::ONE, TypeParam(1), TypeParam(1)));
    EXPECT_TRUE(Compare(Math::NumericVector2<TypeParam>::UNIT_X, TypeParam(1), TypeParam(0)));
    EXPECT_TRUE(Compare(Math::NumericVector2<TypeParam>::UNIT_Y, TypeParam(0), TypeParam(1)));
  }

  TYPED_TEST(NumericVector2Test, Vector_Constructor)
  {
    Math::NumericVector2<TypeParam> default_constructor;
    EXPECT_TRUE(Compare(default_constructor, TypeParam(0), TypeParam(0)));

    Math::NumericVector2<TypeParam> element_constructor(TypeParam(2), TypeParam(4.5));
    EXPECT_TRUE(Compare(element_constructor, TypeParam(2), TypeParam(4.5)));

    Math::NumericVector2<TypeParam> copy_constructor(element_constructor);
    EXPECT_TRUE(Compare(copy_constructor, TypeParam(2), TypeParam(4.5)));
  }

  TYPED_TEST(NumericVector2Test, Vector_Comparisson)
  {
    TypeParam a0 = TypeParam(2.5), b0 = TypeParam(3.5);
    {
      Math::NumericVector2<TypeParam> lhs(a0, b0);
      Math::NumericVector2<TypeParam> rhs(b0, a0);

      EXPECT_FALSE(lhs == rhs);
      EXPECT_TRUE(lhs != rhs);
    }

    {
      Math::NumericVector2<TypeParam> lhs(a0, b0);
      Math::NumericVector2<TypeParam> rhs(a0, b0);

      EXPECT_TRUE(lhs == rhs);
      EXPECT_FALSE(lhs != rhs);
    }
  }

  TYPED_TEST(NumericVector2Test, Vector_Arithmetic_Addition)
  {
    TypeParam a0 = TypeParam(1.5), b0 = TypeParam(2.5);
    TypeParam a1 = TypeParam(2.5), b1 = TypeParam(3.5);
    Math::NumericVector2<TypeParam> lhs(a0, b0);
    Math::NumericVector2<TypeParam> rhs(a1, b1);

    Math::NumericVector2<TypeParam> result = lhs + rhs;
    EXPECT_TRUE(Compare(lhs, a0, b0));
    EXPECT_TRUE(Compare(rhs, a1, b1));
    EXPECT_TRUE(Compare(result, a0 + a1, b0 + b1));

    lhs += rhs;
    EXPECT_TRUE(Compare(rhs, a1, b1));
    EXPECT_TRUE(Compare(lhs, a0 + a1, b0 + b1));
  }

  TYPED_TEST(NumericVector2Test, Vector_Arithmetic_Subtraction)
  {
    TypeParam a0 = TypeParam(1.5), b0 = TypeParam(2.5);
    TypeParam a1 = TypeParam(2.5), b1 = TypeParam(3.5);
    Math::NumericVector2<TypeParam> lhs(a0, b0);
    Math::NumericVector2<TypeParam> rhs(a1, b1);

    Math::NumericVector2<TypeParam> result = lhs - rhs;
    EXPECT_TRUE(Compare(lhs, a0, b0));
    EXPECT_TRUE(Compare(rhs, a1, b1));
    EXPECT_TRUE(Compare(result, a0 - a1, b0 - b1));

    lhs -= rhs;
    EXPECT_TRUE(Compare(rhs, a1, b1));
    EXPECT_TRUE(Compare(lhs, a0 - a1, b0 - b1));
  }

  TYPED_TEST(NumericVector2Test, Vector_Arithmetic_Multiplication)
  {
    TypeParam a0 = TypeParam(1.5), b0 = TypeParam(2.5);
    TypeParam scalar = TypeParam(4.11);
    Math::NumericVector2<TypeParam> lhs(a0, b0);

    Math::NumericVector2<TypeParam> result = lhs * scalar;
    EXPECT_TRUE(Compare(lhs, a0, b0));
    EXPECT_TRUE(Compare(result, a0 * scalar, b0 * scalar));

    lhs *= scalar;
    EXPECT_TRUE(Compare(lhs, a0 * scalar, b0 * scalar));
  }

  TYPED_TEST(NumericVector2Test, Vector_Arithmetic_Division)
  {
    TypeParam a0 = TypeParam(1.5), b0 = TypeParam(2.5);
    TypeParam scalar = TypeParam(4.11);
    Math::NumericVector2<TypeParam> lhs(a0, b0);

    Math::NumericVector2<TypeParam> result = lhs / scalar;
    EXPECT_TRUE(Compare(lhs, a0, b0));
    EXPECT_TRUE(Compare(result, a0 / scalar, b0 / scalar));

    lhs /= scalar;
    EXPECT_TRUE(Compare(lhs, a0 / scalar, b0 / scalar));
  }

  TYPED_TEST(NumericVector2Test, Vector_Arithmetic_Equal)
  {
    TypeParam a0 = TypeParam(1.5), b0 = TypeParam(2.5);
    TypeParam a1 = TypeParam(2.5), b1 = TypeParam(3.5);
    Math::NumericVector2<TypeParam> lhs(a0, b0);
    Math::NumericVector2<TypeParam> rhs(a1, b1);

    EXPECT_FALSE(lhs == rhs);
    lhs = rhs;
    EXPECT_TRUE(lhs == rhs);
  }

  TYPED_TEST(NumericVector2Test, Vector_Compare_Result_Parallel)
  {
    EXPECT_TRUE(Math::NumericVector2<TypeParam>::UNIT_Y.IsParallel(Math::NumericVector2<TypeParam>::UNIT_Y));
    EXPECT_TRUE(Math::NumericVector2<TypeParam>::UNIT_Y.IsParallel(-Math::NumericVector2<TypeParam>::UNIT_Y));

    EXPECT_FALSE(Math::NumericVector2<TypeParam>::UNIT_Y.IsParallel(Math::NumericVector2<TypeParam>::UNIT_X));
  }

  TYPED_TEST(NumericVector2Test, Vector_Compare_Result_Orthogonal)
  {
    EXPECT_FALSE(Math::NumericVector2<TypeParam>::UNIT_Y.IsOrthogonal(Math::NumericVector2<TypeParam>::UNIT_Y));
    EXPECT_TRUE(Math::NumericVector2<TypeParam>::UNIT_Y.IsOrthogonal(-Math::NumericVector2<TypeParam>::UNIT_X));
    EXPECT_FALSE(Math::NumericVector2<TypeParam>::UNIT_Y.IsOrthogonal(Math::NumericVector2<TypeParam>(TypeParam(1), TypeParam(1))));
  }

  TYPED_TEST(NumericVector2Test, Vector_Swizzle)
  {
    Math::NumericVector2<TypeParam> test(TypeParam(0), TypeParam(1));
    EXPECT_TRUE(Compare(test.xy.operator Math::NumericVector2<TypeParam>(), TypeParam(0), TypeParam(1)));
    EXPECT_TRUE(Compare(test.xx.operator Math::NumericVector2<TypeParam>(), TypeParam(0), TypeParam(0)));
    EXPECT_TRUE(Compare(test.yx.operator Math::NumericVector2<TypeParam>(), TypeParam(1), TypeParam(0)));
    EXPECT_TRUE(Compare(test.yy.operator Math::NumericVector2<TypeParam>(), TypeParam(1), TypeParam(1)));

    EXPECT_TRUE(Compare(test.template Swizzle<0, 1>(), TypeParam(0), TypeParam(1)));
    EXPECT_TRUE(Compare(test.template Swizzle<0, 0>(), TypeParam(0), TypeParam(0)));
    EXPECT_TRUE(Compare(test.template Swizzle<1, 0>(), TypeParam(1), TypeParam(0)));
    EXPECT_TRUE(Compare(test.template Swizzle<1, 1>(), TypeParam(1), TypeParam(1)));

    //EXPECT_DEATH(Compare(test.template Swizzle<0, 2>(), TypeParam(0), TypeParam(1)), "a < 2 && b < 2");
  }

  TYPED_TEST(NumericVector2Test, Vector_Product_Operations)
  {
    Math::NumericVector2<TypeParam> lhs(Math::NumericVector2<TypeParam>::UNIT_X);
    Math::NumericVector2<TypeParam> rhs(Math::NumericVector2<TypeParam>::UNIT_Y);

    EXPECT_EQ(lhs.Dot(rhs), TypeParam(0.0));
    EXPECT_EQ(lhs.Cross(rhs), TypeParam(1.0));
  }






  template<class T>
  class NumericVector3Test : public testing::Test { };
  TYPED_TEST_CASE(NumericVector3Test, Implementations);

  TYPED_TEST(NumericVector3Test, Vector_Static_Members)
  {
    EXPECT_TRUE(Compare(Math::NumericVector3<TypeParam>::ZERO, TypeParam(0), TypeParam(0), TypeParam(0)));
    EXPECT_TRUE(Compare(Math::NumericVector3<TypeParam>::ONE, TypeParam(1), TypeParam(1), TypeParam(1)));
    EXPECT_TRUE(Compare(Math::NumericVector3<TypeParam>::UNIT_X, TypeParam(1), TypeParam(0), TypeParam(0)));
    EXPECT_TRUE(Compare(Math::NumericVector3<TypeParam>::UNIT_Y, TypeParam(0), TypeParam(1), TypeParam(0)));
    EXPECT_TRUE(Compare(Math::NumericVector3<TypeParam>::UNIT_Z, TypeParam(0), TypeParam(0), TypeParam(1)));
  }

  TYPED_TEST(NumericVector3Test, Vector_Constructor)
  {
    Math::NumericVector3<TypeParam> default_constructor;
    EXPECT_TRUE(Compare(default_constructor, TypeParam(0), TypeParam(0), TypeParam(0)));

    Math::NumericVector3<TypeParam> element_constructor(TypeParam(2), TypeParam(4.5), TypeParam(8.5));
    EXPECT_TRUE(Compare(element_constructor, TypeParam(2), TypeParam(4.5), TypeParam(8.5)));

    Math::NumericVector3<TypeParam> copy_constructor(element_constructor);
    EXPECT_TRUE(Compare(copy_constructor, TypeParam(2), TypeParam(4.5), TypeParam(8.5)));
  }

  TYPED_TEST(NumericVector3Test, Vector_Comparisson)
  {
    TypeParam a0 = TypeParam(2.5), b0 = TypeParam(3.5), c0 = TypeParam(4.5);
    {
      Math::NumericVector3<TypeParam> lhs(a0, b0, c0);
      Math::NumericVector3<TypeParam> rhs(c0, b0, a0);

      EXPECT_FALSE(lhs == rhs);
      EXPECT_TRUE(lhs != rhs);
    }

    {
      Math::NumericVector3<TypeParam> lhs(a0, b0, c0);
      Math::NumericVector3<TypeParam> rhs(a0, b0, c0);

      EXPECT_TRUE(lhs == rhs);
      EXPECT_FALSE(lhs != rhs);
    }
  }

  TYPED_TEST(NumericVector3Test, Vector_Arithmetic_Addition)
  {
    TypeParam a0 = TypeParam(1.5), b0 = TypeParam(2.5), c0 = TypeParam(4.5);
    TypeParam a1 = TypeParam(2.5), b1 = TypeParam(3.5), c1 = TypeParam(4.5);
    Math::NumericVector3<TypeParam> lhs(a0, b0, c0);
    Math::NumericVector3<TypeParam> rhs(a1, b1, c1);

    Math::NumericVector3<TypeParam> result = lhs + rhs;
    EXPECT_TRUE(Compare(lhs, a0, b0, c0));
    EXPECT_TRUE(Compare(rhs, a1, b1, c1));
    EXPECT_TRUE(Compare(result, a0 + a1, b0 + b1, c0 + c1));

    lhs += rhs;
    EXPECT_TRUE(Compare(rhs, a1, b1, c1));
    EXPECT_TRUE(Compare(lhs, a0 + a1, b0 + b1, c0 + c1));
  }

  TYPED_TEST(NumericVector3Test, Vector_Arithmetic_Subtraction)
  {
    TypeParam a0 = TypeParam(1.5), b0 = TypeParam(2.5), c0 = TypeParam(4.5);
    TypeParam a1 = TypeParam(2.5), b1 = TypeParam(3.5), c1 = TypeParam(4.5);
    Math::NumericVector3<TypeParam> lhs(a0, b0, c0);
    Math::NumericVector3<TypeParam> rhs(a1, b1, c1);

    Math::NumericVector3<TypeParam> result = lhs - rhs;
    EXPECT_TRUE(Compare(lhs, a0, b0, c0));
    EXPECT_TRUE(Compare(rhs, a1, b1, c1));
    EXPECT_TRUE(Compare(result, a0 - a1, b0 - b1, c0 - c1));

    lhs -= rhs;
    EXPECT_TRUE(Compare(rhs, a1, b1, c1));
    EXPECT_TRUE(Compare(lhs, a0 - a1, b0 - b1, c0 - c1));
  }

  TYPED_TEST(NumericVector3Test, Vector_Arithmetic_Multiplication)
  {
    TypeParam a0 = TypeParam(1.5), b0 = TypeParam(2.5), c0 = TypeParam(4.5);
    TypeParam scalar = TypeParam(4.11);
    Math::NumericVector3<TypeParam> lhs(a0, b0, c0);

    Math::NumericVector3<TypeParam> result = lhs * scalar;
    EXPECT_TRUE(Compare(lhs, a0, b0, c0));
    EXPECT_TRUE(Compare(result, a0 * scalar, b0 * scalar, c0 * scalar));

    lhs *= scalar;
    EXPECT_TRUE(Compare(lhs, a0 * scalar, b0 * scalar, c0 * scalar));
  }

  TYPED_TEST(NumericVector3Test, Vector_Arithmetic_Division)
  {
    TypeParam a0 = TypeParam(1.5), b0 = TypeParam(2.5), c0 = TypeParam(4.5);
    TypeParam scalar = TypeParam(4.11);
    Math::NumericVector3<TypeParam> lhs(a0, b0, c0);

    Math::NumericVector3<TypeParam> result = lhs / scalar;
    EXPECT_TRUE(Compare(lhs, a0, b0, c0));
    EXPECT_TRUE(Compare(result, a0 / scalar, b0 / scalar, c0 / scalar));

    lhs /= scalar;
    EXPECT_TRUE(Compare(lhs, a0 / scalar, b0 / scalar, c0 / scalar));
  }

  TYPED_TEST(NumericVector3Test, Vector_Arithmetic_Equal)
  {
    TypeParam a0 = TypeParam(1.5), b0 = TypeParam(2.5), c0 = TypeParam(4.5);
    TypeParam a1 = TypeParam(2.5), b1 = TypeParam(3.5), c1 = TypeParam(4.5);
    Math::NumericVector3<TypeParam> lhs(a0, b0, c0);
    Math::NumericVector3<TypeParam> rhs(a1, b1, c1);

    EXPECT_FALSE(lhs == rhs);
    lhs = rhs;
    EXPECT_TRUE(lhs == rhs);
  }

  TYPED_TEST(NumericVector3Test, Vector_Compare_Result_Parallel)
  {
    EXPECT_TRUE(Math::NumericVector3<TypeParam>::UNIT_Y.IsParallel(Math::NumericVector3<TypeParam>::UNIT_Y));
    EXPECT_TRUE(Math::NumericVector3<TypeParam>::UNIT_Y.IsParallel(-Math::NumericVector3<TypeParam>::UNIT_Y));

    EXPECT_FALSE(Math::NumericVector3<TypeParam>::UNIT_Y.IsParallel(Math::NumericVector3<TypeParam>::UNIT_X));
  }

  TYPED_TEST(NumericVector3Test, Vector_Compare_Result_Orthogonal)
  {
    EXPECT_FALSE(Math::NumericVector3<TypeParam>::UNIT_Y.IsOrthogonal(Math::NumericVector3<TypeParam>::UNIT_Y));
    EXPECT_TRUE(Math::NumericVector3<TypeParam>::UNIT_Y.IsOrthogonal(-Math::NumericVector3<TypeParam>::UNIT_X));
    EXPECT_FALSE(Math::NumericVector3<TypeParam>::UNIT_Y.IsOrthogonal(Math::NumericVector3<TypeParam>(TypeParam(1), TypeParam(1), TypeParam(1))));
  }

  TYPED_TEST(NumericVector3Test, Vector_Swizzle)
  {
    Math::NumericVector3<TypeParam> test(TypeParam(0), TypeParam(1), TypeParam(2));
    EXPECT_TRUE(Compare(test.xyz.operator Math::NumericVector3<TypeParam>(), TypeParam(0), TypeParam(1), TypeParam(2)));
    EXPECT_TRUE(Compare(test.zyx.operator Math::NumericVector3<TypeParam>(), TypeParam(2), TypeParam(1), TypeParam(0)));
    EXPECT_TRUE(Compare(test.xy.operator Math::NumericVector2<TypeParam>(), TypeParam(0), TypeParam(1)));
    EXPECT_TRUE(Compare(test.yz.operator Math::NumericVector2<TypeParam>(), TypeParam(1), TypeParam(2)));
    EXPECT_TRUE(Compare(test.xz.operator Math::NumericVector2<TypeParam>(), TypeParam(0), TypeParam(2)));

    EXPECT_TRUE(Compare(test.template Swizzle<1, 0>(), TypeParam(1), TypeParam(0)));
    EXPECT_TRUE(Compare(test.template Swizzle<2, 2>(), TypeParam(2), TypeParam(2)));

    EXPECT_TRUE(Compare(test.template Swizzle<1, 0, 1>(), TypeParam(1), TypeParam(0), TypeParam(1)));
    EXPECT_TRUE(Compare(test.template Swizzle<1, 1, 2>(), TypeParam(1), TypeParam(1), TypeParam(2)));
  }

  TYPED_TEST(NumericVector3Test, Vector_Product_Operations)
  {
    Math::NumericVector3<TypeParam> lhs(Math::NumericVector3<TypeParam>::UNIT_Z);
    Math::NumericVector3<TypeParam> rhs(Math::NumericVector3<TypeParam>::UNIT_X);

    EXPECT_EQ(lhs.Dot(rhs), TypeParam(0));
    EXPECT_EQ(lhs.Cross(rhs), Math::NumericVector3<TypeParam>::UNIT_Y);
  }







  template<class T>
  class NumericVector4Test : public testing::Test { };
  TYPED_TEST_CASE(NumericVector4Test, Implementations);

  TYPED_TEST(NumericVector4Test, Vector_Static_Members)
  {
    EXPECT_TRUE(Compare(Math::NumericVector4<TypeParam>::ZERO, TypeParam(0), TypeParam(0), TypeParam(0), TypeParam(0)));
    EXPECT_TRUE(Compare(Math::NumericVector4<TypeParam>::ONE, TypeParam(1), TypeParam(1), TypeParam(1), TypeParam(0)));
    EXPECT_TRUE(Compare(Math::NumericVector4<TypeParam>::UNIT_X, TypeParam(1), TypeParam(0), TypeParam(0), TypeParam(0)));
    EXPECT_TRUE(Compare(Math::NumericVector4<TypeParam>::UNIT_Y, TypeParam(0), TypeParam(1), TypeParam(0), TypeParam(0)));
    EXPECT_TRUE(Compare(Math::NumericVector4<TypeParam>::UNIT_Z, TypeParam(0), TypeParam(0), TypeParam(1), TypeParam(0)));
  }

  TYPED_TEST(NumericVector4Test, Vector_Constructor)
  {
    Math::NumericVector4<TypeParam> default_constructor;
    EXPECT_TRUE(Compare(default_constructor, TypeParam(0), TypeParam(0), TypeParam(0), TypeParam(0)));

    Math::NumericVector4<TypeParam> element_constructor(TypeParam(2), TypeParam(4.5), TypeParam(8.5));
    EXPECT_TRUE(Compare(element_constructor, TypeParam(2), TypeParam(4.5), TypeParam(8.5), TypeParam(0)));

    Math::NumericVector4<TypeParam> copy_constructor(element_constructor);
    EXPECT_TRUE(Compare(copy_constructor, TypeParam(2), TypeParam(4.5), TypeParam(8.5), TypeParam(0)));

    Math::NumericVector4<TypeParam> explicit_constructor(Math::NumericVector3<TypeParam>::UNIT_Z);
    EXPECT_TRUE(Compare(explicit_constructor, TypeParam(0.0), TypeParam(0.0), TypeParam(1.0), TypeParam(0.0)));
  }

  TYPED_TEST(NumericVector4Test, Vector_Comparisson)
  {
    TypeParam a0 = TypeParam(2.5), b0 = TypeParam(3.5), c0 = TypeParam(4.5);
    {
      Math::NumericVector4<TypeParam> lhs(a0, b0, c0);
      Math::NumericVector4<TypeParam> rhs(c0, b0, a0);

      EXPECT_FALSE(lhs == rhs);
      EXPECT_TRUE(lhs != rhs);
    }

    {
      Math::NumericVector4<TypeParam> lhs(a0, b0, c0);
      Math::NumericVector4<TypeParam> rhs(a0, b0, c0);

      EXPECT_TRUE(lhs == rhs);
      EXPECT_FALSE(lhs != rhs);
    }
  }

  TYPED_TEST(NumericVector4Test, Vector_Arithmetic_Addition)
  {
    TypeParam a0 = TypeParam(1.5), b0 = TypeParam(2.5), c0 = TypeParam(4.5);
    TypeParam a1 = TypeParam(2.5), b1 = TypeParam(3.5), c1 = TypeParam(4.5);
    Math::NumericVector4<TypeParam> lhs(a0, b0, c0);
    Math::NumericVector4<TypeParam> rhs(a1, b1, c1);

    Math::NumericVector4<TypeParam> result = lhs + rhs;
    EXPECT_TRUE(Compare(lhs, a0, b0, c0, TypeParam(0)));
    EXPECT_TRUE(Compare(rhs, a1, b1, c1, TypeParam(0)));
    EXPECT_TRUE(Compare(result, a0 + a1, b0 + b1, c0 + c1, TypeParam(0)));

    lhs += rhs;
    EXPECT_TRUE(Compare(rhs, a1, b1, c1, TypeParam(0)));
    EXPECT_TRUE(Compare(lhs, a0 + a1, b0 + b1, c0 + c1, TypeParam(0)));
  }

  TYPED_TEST(NumericVector4Test, Vector_Arithmetic_Subtraction)
  {
    TypeParam a0 = TypeParam(1.5), b0 = TypeParam(2.5), c0 = TypeParam(4.5);
    TypeParam a1 = TypeParam(2.5), b1 = TypeParam(3.5), c1 = TypeParam(4.5);
    Math::NumericVector4<TypeParam> lhs(a0, b0, c0, TypeParam(0));
    Math::NumericVector4<TypeParam> rhs(a1, b1, c1, TypeParam(0));

    Math::NumericVector4<TypeParam> result = lhs - rhs;
    EXPECT_TRUE(Compare(lhs, a0, b0, c0, TypeParam(0)));
    EXPECT_TRUE(Compare(rhs, a1, b1, c1, TypeParam(0)));
    EXPECT_TRUE(Compare(result, a0 - a1, b0 - b1, c0 - c1, TypeParam(0)));

    lhs -= rhs;
    EXPECT_TRUE(Compare(rhs, a1, b1, c1, TypeParam(0)));
    EXPECT_TRUE(Compare(lhs, a0 - a1, b0 - b1, c0 - c1, TypeParam(0)));
  }

  TYPED_TEST(NumericVector4Test, Vector_Arithmetic_Multiplication)
  {
    TypeParam a0 = TypeParam(1.5), b0 = TypeParam(2.5), c0 = TypeParam(4.5);
    TypeParam scalar = TypeParam(4.11);
    Math::NumericVector4<TypeParam> lhs(a0, b0, c0);

    Math::NumericVector4<TypeParam> result = lhs * scalar;
    EXPECT_TRUE(Compare(lhs, a0, b0, c0, TypeParam(0)));
    EXPECT_TRUE(Compare(result, a0 * scalar, b0 * scalar, c0 * scalar, TypeParam(0)));

    lhs *= scalar;
    EXPECT_TRUE(Compare(lhs, a0 * scalar, b0 * scalar, c0 * scalar, TypeParam(0)));
  }

  TYPED_TEST(NumericVector4Test, Vector_Arithmetic_Division)
  {
    TypeParam a0 = TypeParam(1.5), b0 = TypeParam(2.5), c0 = TypeParam(4.5);
    TypeParam scalar = TypeParam(4.11);
    Math::NumericVector4<TypeParam> lhs(a0, b0, c0);

    Math::NumericVector4<TypeParam> result = lhs / scalar;
    EXPECT_TRUE(Compare(lhs, a0, b0, c0, TypeParam(0)));
    EXPECT_TRUE(Compare(result, a0 / scalar, b0 / scalar, c0 / scalar, TypeParam(0)));

    lhs /= scalar;
    EXPECT_TRUE(Compare(lhs, a0 / scalar, b0 / scalar, c0 / scalar, TypeParam(0)));
  }

  TYPED_TEST(NumericVector4Test, Vector_Arithmetic_Equal)
  {
    TypeParam a0 = TypeParam(1.5), b0 = TypeParam(2.5), c0 = TypeParam(4.5);
    TypeParam a1 = TypeParam(2.5), b1 = TypeParam(3.5), c1 = TypeParam(4.5);
    Math::NumericVector4<TypeParam> lhs(a0, b0, c0);
    Math::NumericVector4<TypeParam> rhs(a1, b1, c1);

    EXPECT_FALSE(lhs == rhs);
    lhs = rhs;
    EXPECT_TRUE(lhs == rhs);
  }

  TYPED_TEST(NumericVector4Test, Vector_Compare_Result_Parallel)
  {
    EXPECT_TRUE(Math::NumericVector4<TypeParam>::UNIT_Y.IsParallel(Math::NumericVector4<TypeParam>::UNIT_Y));
    EXPECT_TRUE(Math::NumericVector4<TypeParam>::UNIT_Y.IsParallel(-Math::NumericVector4<TypeParam>::UNIT_Y));

    EXPECT_FALSE(Math::NumericVector4<TypeParam>::UNIT_Y.IsParallel(Math::NumericVector4<TypeParam>::UNIT_X));
  }

  TYPED_TEST(NumericVector4Test, Vector_Compare_Result_Orthogonal)
  {
    EXPECT_FALSE(Math::NumericVector4<TypeParam>::UNIT_Y.IsOrthogonal(Math::NumericVector4<TypeParam>::UNIT_Y));
    EXPECT_TRUE(Math::NumericVector4<TypeParam>::UNIT_Y.IsOrthogonal(-Math::NumericVector4<TypeParam>::UNIT_X));
    EXPECT_FALSE(Math::NumericVector4<TypeParam>::UNIT_Y.IsOrthogonal(Math::NumericVector4<TypeParam>(TypeParam(1), TypeParam(1), TypeParam(1))));
  }

  TYPED_TEST(NumericVector4Test, Vector_Swizzle)
  {
    Math::NumericVector4<TypeParam> test(TypeParam(0), TypeParam(1), TypeParam(2), TypeParam(3));
    EXPECT_TRUE(Compare(test.xyzw.operator Math::NumericVector4<TypeParam>(), TypeParam(0), TypeParam(1), TypeParam(2), TypeParam(3)));
    EXPECT_TRUE(Compare(test.wzyx.operator Math::NumericVector4<TypeParam>(), TypeParam(3), TypeParam(2), TypeParam(1), TypeParam(0)));
    EXPECT_TRUE(Compare(test.xyz.operator Math::NumericVector3<TypeParam>(), TypeParam(0), TypeParam(1), TypeParam(2)));
    EXPECT_TRUE(Compare(test.xy.operator Math::NumericVector2<TypeParam>(), TypeParam(0), TypeParam(1)));
    EXPECT_TRUE(Compare(test.yz.operator Math::NumericVector2<TypeParam>(), TypeParam(1), TypeParam(2)));
    EXPECT_TRUE(Compare(test.zw.operator Math::NumericVector2<TypeParam>(), TypeParam(2), TypeParam(3)));

    EXPECT_TRUE(Compare(test.template Swizzle<1, 0>(), TypeParam(1), TypeParam(0)));
    EXPECT_TRUE(Compare(test.template Swizzle<2, 2>(), TypeParam(2), TypeParam(2)));

    EXPECT_TRUE(Compare(test.template Swizzle<1, 0, 1>(), TypeParam(1), TypeParam(0), TypeParam(1)));
    EXPECT_TRUE(Compare(test.template Swizzle<1, 1, 2>(), TypeParam(1), TypeParam(1), TypeParam(2)));

    EXPECT_TRUE(Compare(test.template Swizzle<1, 0, 1, 3>(), TypeParam(1), TypeParam(0), TypeParam(1), TypeParam(3)));
    EXPECT_TRUE(Compare(test.template Swizzle<1, 1, 3, 2>(), TypeParam(1), TypeParam(1), TypeParam(3), TypeParam(2)));
  }

  TYPED_TEST(NumericVector4Test, Vector_Product_Operations)
  {
    Math::NumericVector4<TypeParam> lhs(Math::NumericVector4<TypeParam>::UNIT_Z);
    Math::NumericVector4<TypeParam> rhs(Math::NumericVector4<TypeParam>::UNIT_X);

    EXPECT_EQ(lhs.Dot(rhs), TypeParam(0));
    EXPECT_EQ(lhs.Cross(rhs), Math::NumericVector4<TypeParam>::UNIT_Y);
  }

  void Test_NumericVector(void) { }
}