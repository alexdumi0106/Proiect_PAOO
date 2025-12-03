#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include "BankEntity.hpp"
#include <mutex>

class Account : public BankEntity {
    private:
        double balance;
        double* transactions;
        int nrTransactions;

        // mutex standard
        std::mutex stdMutex;

        // mutex custom RAII
        Mutex customMutex;

    public:
        Account(const std::string& owner, double initialValue);
        ~Account();

        Account(const Account& other);
        Account& operator=(const Account& other);

        Account(Account&& other) noexcept;
        Account& operator=(Account&& other) noexcept;

        void deposit(double amount) override;
        void withdraw(double amount) override;

        void unsafeDeposit(double amount); // Race-condition        
        void customDeposit(double amount);// RAII custom mutex

        double getBalance() const;
};

#endif
