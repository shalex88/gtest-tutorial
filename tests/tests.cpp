#include <ostream>
#include "gtest/gtest.h"
/* Add your project include files here */
#include "BankAccount.h"

/* 1 - Simple test */
TEST(AccountTest, AccountStartsEmpty) {
  BankAccount account;
  EXPECT_EQ(0, account.balance_);
}

/* 2 - Test fixture for multiple tests */
class BankAccountTestFixture : public testing::Test {
 public:
  BankAccount* account_;
  BankAccountTestFixture() {
    account_ = new BankAccount;
  }
  ~BankAccountTestFixture() override {
    delete account_;
  }
};

TEST_F(BankAccountTestFixture, AccountStartsEmpty) {
  EXPECT_EQ(0, account_->balance_);
}

TEST_F(BankAccountTestFixture, CanDeposit) {
  account_->deposit(20);
  EXPECT_EQ(20, account_->balance_);
}

TEST_F(BankAccountTestFixture, CanWithdraw) {
  account_->withdraw(20);
  EXPECT_EQ(0, account_->balance_);
}

/* 3 - Test suite for multiple tests */
struct account_state {
  int initial_balance;
  int amount;
  int final_balance;
  bool success;
  friend std::ostream &operator<<(std::ostream &os, const account_state &state) {
    os << "initial_balance: " << state.initial_balance << " amount: " << state.amount << " final_balance: "
       << state.final_balance << " success: " << state.success;
    return os;
  }
};

class WithdrawAccountTestFixture : public BankAccountTestFixture, public testing::WithParamInterface<account_state> {
 public:
  WithdrawAccountTestFixture() {
    account_->balance_ = GetParam().initial_balance;
  }
};

INSTANTIATE_TEST_SUITE_P(Default, WithdrawAccountTestFixture,
                         testing::Values(
                             account_state{100, 50, 50, true},
                             account_state{100, 200, 100, false}
                         ));

TEST_P(WithdrawAccountTestFixture, FinalBalance) {
  auto as = GetParam();
  auto success = account_->withdraw(as.amount);
  EXPECT_EQ(as.final_balance, account_->balance_);
  EXPECT_EQ(as.success, success);
}

