#pragma once
#include <iostream>
#include <string>

class Account {
    private:
        std::string accountHolder;
        double sold;
        double* transactions;
        int nrTransactions;
    public:
        Account(std::string name, double initialAmount);
        ~Account();
        Account(const Account& other); // copy-constructor
        Account(Account&& other); // move constructor

        void deposit(double sum);
        void withdraw(double sum);
        double getSold() const;
        std::string getAccountHolder() const;
        void showTransactions() const;
};