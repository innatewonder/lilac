#include "CommonPrecompiled.h"
#include "CoreUtils.h"
#include "TestSystem.h"

#include "TestComponent.h"
#include "TestMath.h"
#include "TestNetworking.h"

namespace Test
{
  TestSystem::TestSystem()
  {}

  TestSystem::~TestSystem()
  {}

  TEST(ObjectTest, Make_Destroy_Object)
  {
    EXPECT_EQ(0, Core::gCore->NumObjects());
    Object* obj = Factory::MakeObject();

    EXPECT_EQ(1, Core::gCore->NumObjects());
    obj->Kill();
    Core::gCore->Tick(0);
    EXPECT_EQ(0, Core::gCore->NumObjects());
  }

  TEST(ComponentTest, Make_Destroy_Component)
  {
    System* testSys = Core::gCore->GetSystem(Sys::TestSystem);
    EXPECT_EQ(0, testSys->NumComponents());
    Component* c1 = Factory::MakeComponent(Comp::TestComponent);

    EXPECT_EQ(sizeof(TestComponent), sizeof(*c1));
    EXPECT_EQ("TestComponent", c1->GetName());
    EXPECT_EQ(1, testSys->NumComponents());

    Factory::DestroyComponent(c1);
    EXPECT_EQ(0, testSys->NumComponents());
  }

  TEST(ComponentTest, Make_Unique_Should_Allow_1)
  {
    Object* obj = Factory::MakeObject();
    EXPECT_TRUE(obj->AddComponent(Comp::TestComponent) != nullptr);
    EXPECT_FALSE(obj->AddComponent(Comp::TestComponent) != nullptr);

    obj->RemoveComponent(Comp::TestComponent);
    EXPECT_TRUE(obj->AddComponent(Comp::TestComponent) != nullptr);
  }

  TEST(RandomTest, Test_Min_Max_10000)
  {
    Generation::Random random;

    u32 min = 7;
    u32 max = 45;
    for(int i = 0; i < 10000; ++i)
    {
      u32 num = random.Get(min, max);
      EXPECT_LE(min, num);
      EXPECT_GE(max, num);
    }
  }

  TEST(RandomTest, Test_Float_10000)
  {
    Generation::Random random;

    for(int i = 0; i < 10000; ++i)
    {
      f32 num = random.Getf();
      EXPECT_LE(0.0f, num);
      EXPECT_GE(1.0f, num);
    }
  }

  struct testStruct
  {
    int i, v;
    float f, s;
  };

  TEST(PoolTest, Allocate_1)
  {
    Memory::PoolAllocator p = Memory::PoolAllocator(sizeof(testStruct));
    testStruct* one = p.New<testStruct>();
    p.Delete(one);
    p.Log();
  }

  TEST(PoolTest, Reallocate)
  {
    Memory::PoolAllocator p = Memory::PoolAllocator(sizeof(testStruct));
    testStruct* one = p.New<testStruct>();
    p.Delete(one);
    one = p.New<testStruct>();
    p.Delete(one);
    p.Log();
  }

  TEST(PoolTest, Allocate100)
  {
    Containers::Vector<testStruct*> cont;
    cont.reserve(100);
    Memory::PoolAllocator p = Memory::PoolAllocator(sizeof(testStruct));
    for(u32 i = 0; i < 100; ++i)
    {
      cont.push_back(p.New<testStruct>());
    }
    for(u32 i = 0; i < 100; ++i)
    {
      p.Delete(cont[i]);
    }
    p.Log();
  }

  TEST(PoolTest, RandomAccess100)
  {
    Containers::Vector<testStruct*> cont;
    cont.reserve(100);
    Memory::PoolAllocator p = Memory::PoolAllocator(sizeof(testStruct));
    for(u32 i = 0; i < 100; ++i)
    {
      cont.push_back(p.New<testStruct>());
    }
    for(u32 i = 0; i < 100; i += 10)
    {
      p.Delete(cont[i]);
    }
    for(u32 i = 0; i < 100; i += 10)
    {
      cont[i] = p.New<testStruct>();
    }
    for(u32 i = 0; i < 100; ++i)
    {
      p.Delete(cont[i]);
    }
    p.Log();
  }

  bool TestSystem::Initialize(ArgParser& args)
  {
    int argc = args.GetArgC();
    testing::InitGoogleMock(&argc, args.GetArgV());

    return true;
  }

  void TestSystem::Destroy()
  {}

  void TestSystem::Test()
  {
    // get rid of warning on linux about unused ret
    u32 ret = RUN_ALL_TESTS();
    //Test_Math();
    TestNetworking();
  }

  void TestSystem::Tick(f32 dt)
  {}

  void TestSystem::HandleMessage(Message* msg)
  {}

}
