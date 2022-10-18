#ifndef GTEST_TUTORIAL_INCLUDE_BANKACCOUNT_H_
#define GTEST_TUTORIAL_INCLUDE_BANKACCOUNT_H_

class BankAccount {
 public:
  int balance_{0};
  BankAccount() = default;
  explicit BankAccount(int amount) {
    balance_ = amount;
  }
  void deposit(int amount) {
    balance_ += amount;
  }
  bool withdraw(int amount) {
    bool success{false};
    if(amount < balance_) {
      balance_ -= amount;
      success = true;
    }

    return success;
  }
};

#endif //GTEST_TUTORIAL_INCLUDE_BANKACCOUNT_H_
