#pragma once
#include "BankEntity.hpp"
#include <mutex>

class Account : public BankEntity {
private:
    double* transactions;
    int nrTransactions;
    mutable std::mutex m;  // mutex RAII-protected zone

public:
    Account(std::string name, double initialAmount);
    virtual ~Account();

    Account(const Account& other);
    Account(Account&& other) noexcept;

    Account& operator=(const Account& other);
    Account& operator=(Account&& other) noexcept;

    void deposit(double sum) override;
    void withdraw(double sum) override;

    void showTransactions() const;
};
