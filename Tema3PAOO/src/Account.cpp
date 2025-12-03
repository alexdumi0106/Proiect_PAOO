#include "Account.hpp"
#include <iostream>
#include <utility>

// -------------------------------------
// Constructor / Destructor — RAII
// -------------------------------------
Account::Account(const std::string& owner, double initialValue)
    : BankEntity(owner),       // <--- apelăm constructorul bazei
      balance(initialValue),
      transactions(nullptr),
      nrTransactions(0)
{
    transactions = new double[100];
}

Account::~Account() {
    delete[] transactions;
}

// -------------------------------------
// COPY CONSTRUCTOR — deep copy (Item 14)
// -------------------------------------
Account::Account(const Account& other)
    : BankEntity(other),  // copiem și baza
      balance(other.balance),
      transactions(nullptr),
      nrTransactions(other.nrTransactions)
{
    transactions = new double[100];
    for (int i = 0; i < nrTransactions; i++)
        transactions[i] = other.transactions[i];
}

// -------------------------------------
// COPY ASSIGNMENT
// -------------------------------------
Account& Account::operator=(const Account& other)
{
    if (this != &other) {
        BankEntity::operator=(other); // copiem și partea de bază

        delete[] transactions;

        balance = other.balance;
        nrTransactions = other.nrTransactions;

        transactions = new double[100];
        for (int i = 0; i < nrTransactions; i++)
            transactions[i] = other.transactions[i];
    }
    return *this;
}

// -------------------------------------
// MOVE CONSTRUCTOR
// -------------------------------------
Account::Account(Account&& other) noexcept
    : BankEntity(std::move(other)), // mutăm și partea de bază
      balance(other.balance),
      transactions(other.transactions),
      nrTransactions(other.nrTransactions)
{
    other.transactions = nullptr;
    other.nrTransactions = 0;
    other.balance = 0.0;
}

// -------------------------------------
// MOVE ASSIGNMENT
// -------------------------------------
Account& Account::operator=(Account&& other) noexcept
{
    if (this != &other) {
        BankEntity::operator=(std::move(other)); // mutăm baza

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

// ------------------------------------------------------
// Deposit protejat cu std::mutex (std::lock_guard)
// ------------------------------------------------------
void Account::deposit(double amount)
{
    std::lock_guard<std::mutex> lg(stdMutex); // RAII standard

    balance += amount;
    if (nrTransactions < 100)
        transactions[nrTransactions++] = amount;
    else
        std::cerr << "Transaction array full!\n";


}

// ------------------------------------------------------
// Withdraw protejat cu std::mutex (obligatoriu pentru a nu fi abstractă)
// ------------------------------------------------------
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

// ------------------------------------------------------
// Fără protecție -> Race condition (caz "NU funcționează")
// ------------------------------------------------------
void Account::unsafeDeposit(double amount)
{
    balance += amount;   // Fără mutex
    if (nrTransactions < 100) // ADĂUGAT
        transactions[nrTransactions++] = amount;
    else // ADĂUGAT
        std::cerr << "Transaction array full (unsafe)!\n"; // ADĂUGAT
}

// ------------------------------------------------------
// Folosind mutex-ul custom + LockGuardRAII (Item 14)
// ------------------------------------------------------
void Account::customDeposit(double amount)
{
    LockGuardRAII lock(&customMutex); // RAII custom

    balance += amount;
    if (nrTransactions < 100) // ADĂUGAT
        transactions[nrTransactions++] = amount;
    else // ADĂUGAT
        std::cerr << "Transaction array full (custom)!\n"; // ADĂUGAT
}

double Account::getBalance() const {
    return balance;
}
