#include "CommonPrecompiled.h"
#include "Address.h"
#include "Socket.h"
#include "Packet.h"

namespace Test
{
  using namespace Networking;
  // TEST(AddressTest, ConstructAddress_ShouldDefaultToLoopback)
  // {
  //   Address SUT;
  //   String loopback("127.0.0.1:0");
  //   EXPECT_EQ(loopback, SUT.ToString());
  // }

  // TEST(AddressTest, ConstructWithAddress_ShouldHaveCorrectString)
  // {
  //   String str("8.8.8.8:9456");
  //   Address SUT("8.8.8.8", "9456");
  //   EXPECT_EQ(str, SUT.ToString());
  // }

/////////////////////////////////////////////
  // SOCKET
  class SocketTest : public ::testing::Test
  {
  protected:
    void Create(SocketType type)
    {
      Address addr;
      SUT = new Socket(type, addr);
    }

    virtual void TearDown()
    {
      delete SUT;
    }

    Socket* SUT;
  };

  TEST_F(SocketTest, UDP_CreateSocket_ShouldSignalCorrectType)
  {
    Create(SOCK_UDP);
    EXPECT_EQ(SOCK_UDP, SUT->Type());
  }

  TEST_F(SocketTest, UDP_OpenSocket_ShouldSignalOpen)
  {
    Create(SOCK_UDP);
    SUT->Open();
    EXPECT_EQ(true, SUT->IsOpen());
  }

  TEST_F(SocketTest, UDP_TryAccept_ShouldReturnError)
  {
    Create(SOCK_UDP);
    EXPECT_EQ(nullptr, SUT->Accept());
  }

  ////////////
  //TCP CLIENT
  TEST_F(SocketTest, TCPClient_CreateSocket_ShouldSignalCorrectType)
  {
    Create(SOCK_TCP_CLIENT);
    EXPECT_EQ(SOCK_TCP_CLIENT, SUT->Type());
  }

  // TEST_F(SocketTest, TCPClient_OpenSocket_ShouldSignalOpen)
  // {
  //   Create(SOCK_TCP_CLIENT);
  //   SUT->Open();
  //   EXPECT_EQ(true, SUT->IsOpen());
  // }

  TEST_F(SocketTest, TCPClient_TryAccept_ShouldReturnError)
  {
    Create(SOCK_TCP_CLIENT);
    EXPECT_EQ(nullptr, SUT->Accept());
  }

  ////////////
  //TCP SERVER
  TEST_F(SocketTest, TCPServer_CreateSocket_ShouldSignalCorrectType)
  {
    Create(SOCK_TCP_SERVER);
    EXPECT_EQ(SOCK_TCP_SERVER, SUT->Type());
  }

  TEST_F(SocketTest, TCPServer_OpenSocket_ShouldSignalOpen)
  {
    Create(SOCK_TCP_SERVER);
    SUT->Open();
    EXPECT_EQ(true, SUT->IsOpen());
  }

  TEST_F(SocketTest, TCPServer_TryAccept_ShouldSignalNoConnections)
  {
    Create(SOCK_TCP_SERVER);
    EXPECT_EQ(nullptr, SUT->Accept());
  }

////////////////////////////////////
  // PACKET
  class PacketTest : public ::testing::Test
  {
  protected:
    virtual void SetUp()
    {
      testSize = 10;
      testData = new c08[testSize];

      for(s32 i = 0; i < testSize; ++i)
      {
        testData[i] = i + 1;
      }
    }

    virtual void TearDown()
    {
      delete SUT;
      delete[] testData;
    }

    void IsTestData(const c08* buff, s32 size)
    {
      EXPECT_EQ(testSize, size);
      for(s32 i = 0; i < size; ++i)
      {
        EXPECT_EQ(testData[i], buff[i]);
      }
    }

    Packet* SUT;
    s32  testSize;
    c08* testData;
  };


  TEST_F(PacketTest, Create_Empty_ShouldNotContainData)
  {
    SUT = new Packet();
    EXPECT_EQ(nullptr, SUT->GetData());
    EXPECT_EQ(0, SUT->GetSize());
    EXPECT_EQ(Packet::EMPTY, SUT->GetState());
  }

  TEST_F(PacketTest, Create_WithState_ShouldHaveCorrectState)
  {
    SUT = new Packet(Packet::ERR);
    EXPECT_EQ(Packet::ERR, SUT->GetState());
  }

  TEST_F(PacketTest, Create_WithString_ShouldContainStringData)
  {
    String testString("This is a string");
    SUT = new Packet(testString);

    EXPECT_EQ(testString.size(), SUT->GetSize());
    EXPECT_EQ(Packet::OK, SUT->GetState());

    String outData;
    outData.assign(SUT->GetData(), SUT->GetSize());
    EXPECT_EQ(testString, outData);
  }

  TEST_F(PacketTest, Create_WithData_ShouldContainSameData)
  {
    SUT = new Packet(testData, testSize);

    IsTestData(SUT->GetData(), SUT->GetSize());
  }

  TEST_F(PacketTest, Create_CopyConstruct_ShouldBeExactCopy)
  {
    Packet testPacket(testData, testSize);
    SUT = new Packet(testPacket);

    IsTestData(SUT->GetData(), SUT->GetSize());
    EXPECT_EQ(testPacket.GetPriority(), SUT->GetPriority());
    EXPECT_EQ(testPacket.GetState(), SUT->GetState());
  }

  TEST_F(PacketTest, Append_ToEmptyPacket_ShouldHaveOnlyAddedData)
  {
    SUT = new Packet();

    SUT->AppendData(testData, testSize);
    IsTestData(SUT->GetData(), SUT->GetSize());
  }

  TEST_F(PacketTest, Append_WithData_ShouldContainAllInformation)
  {
    SUT = new Packet(testData, testSize);
    SUT->AppendData(testData, testSize);

    EXPECT_EQ(testSize * 2, SUT->GetSize());
    IsTestData(SUT->GetData(), testSize);
    IsTestData(SUT->GetData() + testSize, testSize);
  }

  void TestNetworking()
  {
    
  }
}
