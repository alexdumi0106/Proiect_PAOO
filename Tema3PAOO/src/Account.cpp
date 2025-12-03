#include "Account.hpp"
#include <iostream>
#include <utility>


// Constructor / Destructor — RAII
Account::Account(const std::string& owner, double initialValue)
    : BankEntity(owner),       
      balance(initialValue),
      transactions(nullptr),
      nrTransactions(0)
{
    transactions = new double[100];
}

Account::~Account() {
    delete[] transactions;
}


// COPY CONSTRUCTOR — deep copy (Item 14)
Account::Account(const Account& other)
    : BankEntity(other), 
      balance(other.balance),
      transactions(nullptr),
      nrTransactions(other.nrTransactions)
{
    transactions = new double[100];
    for (int i = 0; i < nrTransactions; i++)
        transactions[i] = other.transactions[i];
}


// COPY ASSIGNMENT
Account& Account::operator=(const Account& other)
{
    if (this != &other) {
        BankEntity::operator=(other);

        delete[] transactions;

        balance = other.balance;
        nrTransactions = other.nrTransactions;

        transactions = new double[100];
        for (int i = 0; i < nrTransactions; i++)
            transactions[i] = other.transactions[i];
    }
    return *this;
}

// MOVE CONSTRUCTOR
Account::Account(Account&& other) noexcept
    : BankEntity(std::move(other)),
      balance(other.balance),
      transactions(other.transactions),
      nrTransactions(other.nrTransactions)
{
    other.transactions = nullptr;
    other.nrTransactions = 0;
    other.balance = 0.0;
}

// MOVE ASSIGNMENT
Account& Account::operator=(Account&& other) noexcept
{
    if (this != &other) {
        BankEntity::operator=(std::move(other)); 

        delete[] transactions;

        balance = other.balance;
        transactions = other.transactions;
        nrTransactions = other.nrTransactions;

        other.transactions = nullptr;
        other.nrTransactions = 0;
        other.balance = 0.0;
    }
    return *this;
}

// Deposit protejat cu std::mutex (std::lock_guard)
void Account::deposit(double amount)
{
    std::lock_guard<std::mutex> lg(stdMutex); // RAII standard

    balance += amount;
    if (nrTransactions < 100)
        transactions[nrTransactions++] = amount;
    else
        std::cerr << "Transaction array full!\n";


}

// Withdraw protejat cu std::mutex (obligatoriu pentru a nu fi abstracta)
void Account::withdraw(double amount)
{
    std::lock_guard<std::mutex> lg(stdMutex);

    if (amount > balance) {
        std::cerr << "Insufficient funds for withdrawal\n";
        return;
    }

    balance -= amount;
    if (nrTransactions < 100)
        transactions[nrTransactions++] = -amount;
    else
        std::cerr << "Transaction array full!\n";

}


// Fara protectie -> Race condition (caz -> NU functioneaza)
void Account::unsafeDeposit(double amount)
{
    balance += amount;   
    if (nrTransactions < 100) 
        transactions[nrTransactions++] = amount;
    else 
        std::cerr << "Transaction array full (unsafe)!\n"; 
}


// Folosind mutex-ul custom + LockGuardRAII (Item 14)
void Account::customDeposit(double amount)
{
    LockGuardRAII lock(&customMutex); // RAII custom

    balance += amount;
    if (nrTransactions < 100) 
        transactions[nrTransactions++] = amount;
    else 
        std::cerr << "Transaction array full (custom)!\n"; 
}

double Account::getBalance() const {
    return balance;
}
