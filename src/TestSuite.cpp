#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "bank_server.h"
#include "bank_server_real.h"
#include "bank_server_stub.h"
#include "atm_machine.h"
#include "stdio.h"
#include <tuple>
using ::testing::Return;
using ::testing::NiceMock;

// Demonstrate some basic assertions.
TEST(HelloTest, RealTest) {
  // Expect two strings not to be equal.
  BankServerReal bankServer;
  AtmMachine a(&bankServer);
  EXPECT_EQ(a.GetVal(), 2);
}

TEST(HelloTest, StubTest) {
  // Expect two strings not to be equal.
  BankServerStub bankServer;
  AtmMachine a(&bankServer);
  EXPECT_EQ(a.GetVal(), 3);
}

class BankServerMock : public BankServer {
public: 
    BankServerMock(){};
    MOCK_METHOD(void, Connect, (), (override));
    MOCK_METHOD(void, Disconnect, (), (override));
    MOCK_METHOD(void, Credit, (int, int), (override));
    MOCK_METHOD(void, Debit, (int, int), (override));
    MOCK_METHOD(bool, DoubleTransaction, (int, int, int), (override));
    MOCK_METHOD(int, GetBalance, (int), (override));
};

TEST(HelloTest, MockTest) {
  // Expect two strings not to be equal.
  BankServerMock bankServer;
  AtmMachine atm(&bankServer);
  bool withdraw_result = atm.Withdraw(1234,1000);
  EXPECT_FALSE(withdraw_result);
}

// ON Call doesnt have defintion for account_num + 1 so results in default
// Behaviour, returns 0 balance for unknown account
TEST(HelloTest, OnCallTest) {
  int account_number = 1234;
  BankServerMock bankServer;
  ON_CALL(bankServer, GetBalance(account_number)).WillByDefault(Return(2000));
  AtmMachine atm(&bankServer);
  bool withdraw_result1 = atm.Withdraw(account_number, 1000);
  bool withdraw_result2 = atm.Withdraw(account_number + 1, 1000);
  EXPECT_TRUE(withdraw_result1);
  EXPECT_FALSE(withdraw_result2);
}

// ON Call using matcher for any value as arg  "_"
// up at top can do   using testing::_
TEST(HelloTest, OnCallAnyValueTest) {
  BankServerMock bankServer;
  ON_CALL(bankServer, GetBalance(testing::_)).WillByDefault(Return(2000));
  AtmMachine atm(&bankServer);
  bool result = atm.Withdraw(9999, 1000);
  // should still pass because ON_CALL is now specified for any value
  EXPECT_TRUE(result);
}

// ON Call using matcher testing::Gt
// will be specified for any account# > 1000
TEST(HelloTest, OnCallGreaterThantest) {
  BankServerMock bankServer;
  ON_CALL(bankServer, GetBalance(testing::Gt(1000))).WillByDefault(Return(2000));
  AtmMachine atm(&bankServer);
  bool result = atm.Withdraw(9999, 1000);
  // should still pass because ON_CALL is now specified for any value
  EXPECT_TRUE(result);
}


TEST(HelloTest, ExpectCalls) {
  using testing::_;
  BankServerMock bankServer;
  int account_number = 1234;
  int amount = 1000;

  EXPECT_CALL(bankServer, Connect())
    .Times(1);

  EXPECT_CALL(bankServer, GetBalance(_))
    .Times(1)
    .WillOnce(Return(2000));

  EXPECT_CALL(bankServer, Debit(_,_))
    .Times(1);

  EXPECT_CALL(bankServer, Disconnect())
    .Times(1);

  AtmMachine atm(&bankServer);
  bool result = atm.Withdraw(account_number, amount);

  EXPECT_TRUE(result);
}

// Testing that .WillOnce() is specified for just one call
TEST(HelloTest, CanWithdrawSpecifyTimesReturnOnce) {
  using testing::_;
  // Arrange
  BankServerMock bankServer;
  int account_number = 1234;
  int amount = 1000;

  // EXPECTATIONS
  // Will return 2000 the first time, but not specified for
  // 2nd call so will return 0 on second call
  EXPECT_CALL(bankServer, GetBalance(_))
    .Times(testing::AtMost(10))
    .WillOnce(Return(2000));

  AtmMachine atm(&bankServer);
  bool result1 = atm.Withdraw(account_number, amount);
  bool result2 = atm.Withdraw(account_number, amount);

  EXPECT_TRUE(result1);
  EXPECT_FALSE(result2); 
}

// Testing that .WillOnce() is specified twice
TEST(HelloTest, CanWithdrawSpecifyTimesReturnTwice) {
  using testing::_;
  // Arrange
  NiceMock<BankServerMock> bankServer;
  int account_number = 1234;
  int amount = 1000;

  // EXPECTATIONS
  // Will return 2000 the first time, but not specified for
  // 2nd call so will return 0 on second call
  EXPECT_CALL(bankServer, GetBalance(_))
    .Times(testing::AtMost(10))

    .WillOnce(Return(2000))
    .WillOnce(Return(5000));

  AtmMachine atm(&bankServer);
  bool result1 = atm.Withdraw(account_number, amount);
  bool result2 = atm.Withdraw(account_number, amount);

  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2) << "Not Enough money in account"; 
}

// Testing that .WillOnce() is specified twice
TEST(HelloTest, CanWithdrawExpectForcePartialOrder) {
  using testing::_;
  using testing::Sequence;

  Sequence s1;
  // Arrange
  NiceMock<BankServerMock> bankServer;
  int account_number = 1234;
  int amount = 1000;

  // EXPECTATIONS
  EXPECT_CALL(bankServer, Connect())
    .Times(1).InSequence(s1);

  EXPECT_CALL(bankServer, Debit(_, _))
    .Times(1);

  EXPECT_CALL(bankServer, GetBalance(_))
    .Times(1)
    .WillOnce(testing::Return(1000));

  EXPECT_CALL(bankServer, Disconnect())
    .Times(1)
    .InSequence(s1);

  AtmMachine atm(&bankServer);
  bool result1 = atm.Withdraw(account_number, amount);
  EXPECT_TRUE(result1);
}


TEST(HelloTest, CanWithdrawForceSequence) {
  using testing::_;
  using testing::InSequence;

  //Forces Expects to happen in order of listing
  InSequence seq;
  // Arrange
  NiceMock<BankServerMock> bankServer;
  int account_number = 1234;
  int amount = 1000;

  // EXPECTATIONS
  EXPECT_CALL(bankServer, Connect())
    .Times(1);
  EXPECT_CALL(bankServer, GetBalance(_))
    .Times(1)
    .WillOnce(testing::Return(1000));

  EXPECT_CALL(bankServer, Debit(_, _))
  .Times(1);

  EXPECT_CALL(bankServer, Disconnect())
    .Times(1);


  AtmMachine atm(&bankServer);
  bool result = atm.Withdraw(account_number, amount);
  EXPECT_TRUE(result);
}

TEST(HelloTest, CanWithdrawSequenceInScope) {
  using testing::_;
  using testing::InSequence;

  //Can use Scopes to enforce sequence of a subset of calls

  // Arrange
  NiceMock<BankServerMock> bankServer;
  int account_number = 1234;
  int amount = 1000;

  {
  InSequence seq;
  EXPECT_CALL(bankServer, Connect())
    .Times(1);

  EXPECT_CALL(bankServer, Debit(_, _))
  .Times(1);
  }

  {
  InSequence seq;
  EXPECT_CALL(bankServer, GetBalance(_))
    .Times(1)
    .WillOnce(testing::Return(1000));

  EXPECT_CALL(bankServer, Disconnect())
    .Times(1);

  }

  AtmMachine atm(&bankServer);
  bool result = atm.Withdraw(account_number, amount);
  EXPECT_TRUE(result);
}

