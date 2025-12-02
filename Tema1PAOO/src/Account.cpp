#include <Account.hpp>
#include <iostream>

//Constructor
Account::Account(std::string name, double initialAmount)
    : accountHolder(name), sold(initialAmount), nrTransactions(0)
{
    transactions = new double[100];
    std::cout << "Account created for user: " << accountHolder << " with sold: " << sold << " lei.\n";
}

//Destructor
Account::~Account()
{
    if (!accountHolder.empty())
    {
        std::cout << "Free memory for account holder: " << accountHolder << ".\n";
    }
    else
    {
        std::cout << "Free memory for an empty (moved-from) account.\n";
    }
    delete[] transactions;
}

//Copy-constructor
Account::Account(const Account &other)
    : accountHolder(other.accountHolder), sold(other.sold), nrTransactions(other.nrTransactions)
{
    transactions = new double[100];

    for (int i = 0; i < nrTransactions; i++)
    {
        transactions[i] = other.transactions[i];
    }

    std::cout << "Copy account created for: " << accountHolder << ".\n";
}

//Move constructor
Account::Account(Account &&other)
    : accountHolder(std::move(other.accountHolder)),
      sold(other.sold),
      transactions(other.transactions),
      nrTransactions(other.nrTransactions)
{
    other.transactions = nullptr;
    other.sold = 0;
    other.nrTransactions = 0;
    std::cout << "Moved resources from account: " << accountHolder << std::endl;
}

//Copy-assignment
Account& Account::operator=(const Account& other)
{
    if(this == &other)
    {
        std::cout<< " (From Copy-assignment) Self-assignment detected, nothing to do!\n";
        return *this;
    }

    std::cout<< " (From Copy-assignment) Copy data from account: "<< other.accountHolder << " to account "<< accountHolder << ".\n";
    
    accountHolder = other.accountHolder;
    sold = other.sold;
    nrTransactions = other.nrTransactions;

    delete[] transactions;
    transactions = new double[100];
    for (int i = 0; i < nrTransactions; i++)
    {
        transactions[i] = other.transactions[i];
    }

    return *this;
}

//Move assignment
Account& Account::operator=(Account&& other) noexcept
{
    if(this == &other)
    {
        std::cout<< "(From move-assignment) Self-assignment detected, nothing to do!\n";
        return *this;
    }
    
    std::cout<< "(From move-assignment) Move data from account: "<< other.accountHolder << " to " << accountHolder << ".\n";

    delete[] transactions;

    accountHolder = std::move(other.accountHolder);
    sold = other.sold;
    nrTransactions = other.nrTransactions;

    transactions = other.transactions;

    other.transactions = nullptr;
    other.sold = 0;
    other.nrTransactions = 0;

    return *this;
}

void Account::deposit(double sum)
{
    if (sum > 0 && nrTransactions < 100)
    {
        transactions[nrTransactions++] = sum;
        sold = sold + sum;
        std::cout << "A transaction of +" << sum << "lei was made in your account. New sold: " << sold << "lei." << std::endl;
    }
    else
    {
        std::cout << "Deposit value must be a possitive number or you've reached the maximum number of transactions" << std::endl;
    }
}

void Account::withdraw(double sum)
{
    if (sum > 0 && nrTransactions < 100)
    {
        if (sum > sold)
        {
            std::cout << "Insufficient funds!!!" << std::endl;
        }
        else
        {
            sold = sold - sum;
            transactions[nrTransactions++] = -sum;
            std::cout << "A transaction of -" << sum << "lei was made in your account. The remained sold is: " << sold << " lei" << std::endl;
        }
    }
    else
    {
        std::cout << "Withdraw value must be a possitivie number!" << std::endl;
    }
}

double Account::getSold() const
{
    return sold;
}

std::string Account::getAccountHolder() const
{
    return accountHolder;
}

void Account::showTransactions() const
{
    std::cout << "Transactions for user: " << accountHolder << ":";
    for (int i = 0; i < nrTransactions; i++)
    {
        std::cout << transactions[i] << " ";
    }
    std::cout << "\n";
}