#include "Account.hpp"
#include <iostream>


// Constructor
Account::Account(std::string name, double initialAmount)
    : BankEntity(name, initialAmount), nrTransactions(0)
{
    transactions = new double[100];
    std::cout << "Account created for " << accountHolder << "\n";
}

// Destructor
Account::~Account() {
    delete[] transactions;
}

// Copy constructor
Account::Account(const Account& other)
    : BankEntity(other.accountHolder, other.sold),
      nrTransactions(other.nrTransactions)
{
    transactions = new double[100];
    for (int i = 0; i < nrTransactions; i++)
        transactions[i] = other.transactions[i];

    std::cout << "Copy constructor called for " << accountHolder << "\n";
}

// Move constructor
Account::Account(Account&& other) noexcept
    : BankEntity(std::move(other.accountHolder), other.sold),
      transactions(other.transactions),
      nrTransactions(other.nrTransactions)
{
    other.transactions = nullptr;
    other.sold = 0;
    other.nrTransactions = 0;

    std::cout << "Move constructor called for " << accountHolder << "\n";
}

// Copy assignment
Account& Account::operator=(const Account& other)
{
    if (this == &other)
        return *this;

    accountHolder = other.accountHolder;
    sold = other.sold;
    nrTransactions = other.nrTransactions;

    delete[] transactions;
    transactions = new double[100];

    for (int i = 0; i < nrTransactions; i++)
        transactions[i] = other.transactions[i];

    std::cout << "Copy assignment called for " << accountHolder << "\n";

    return *this;
}

// Move assignment
Account& Account::operator=(Account&& other) noexcept
{
    if (this == &other)
        return *this;

    accountHolder = std::move(other.accountHolder);
    sold = other.sold;
    nrTransactions = other.nrTransactions;

    delete[] transactions;
    transactions = other.transactions;

    other.transactions = nullptr;
    other.nrTransactions = 0;
    other.sold = 0;

    std::cout << "Move assignment called for " << accountHolder << "\n";

    return *this;
}

// Deposit & withdraw
void Account::deposit(double sum) {
    std::lock_guard<std::mutex> lock(m);
    transactions[nrTransactions++] = sum;
    sold += sum;
}
void Account::withdraw(double sum) {
    std::lock_guard<std::mutex> lock(m);
    if (sum <= sold) {
        transactions[nrTransactions++] = -sum;
        sold -= sum;
    }
}
