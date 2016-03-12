/*
 *  FILE          TestMath.cpp
 *  AUTHOR        Brendon Clifford
 *  DESCRIPTION
 *    Test math functionality.
 */
#include "CommonPrecompiled.h"
#include "TestMath.h"

namespace Test
{
  void Test_Math(void)
  {
    Test_MathCommon();
    Test_NumericVector();
    Test_NumericPoint();
    Test_Matrix();
    Test_Quaternion();
    Test_Segment();
    Test_Ray();
    Test_Sphere();
    Test_AABB();
    Test_Color();
  }
}