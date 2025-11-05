#include <Account.hpp>
#include <iostream>

Account::Account(std::string name, double initialAmount)
    : accountHolder(name), sold(initialAmount), nrTransactions(0)
{
    transactions = new double[100];
    std::cout << "Cont creat pentru " << accountHolder << " cu soldul de " << sold << " lei.\n";
}

Account::~Account()
{
    if(!accountHolder.empty())
    {
        std::cout << "Free memory for account holder: " << accountHolder << ".\n";
    } else {
        std::cout << "Free memory for an empty (moved-from) account.\n";
    }
    delete[] transactions;
}

Account::Account(const Account &other)
    : accountHolder(other.accountHolder), sold(other.sold), nrTransactions(other.nrTransactions)
{
    transactions = new double[100];

    for (int i = 0; i < nrTransactions; i++)
    {
        transactions[i] = other.transactions[i];
    }

    std::cout << " Copie creata pentru contul " << accountHolder << ".\n";
}

Account::Account(Account&& other)
    :accountHolder(std::move(other.accountHolder)), 
    sold(other.sold), 
    transactions(other.transactions), 
    nrTransactions(other.nrTransactions)
{
    other.transactions = nullptr;
    other.sold = 0;
    other.nrTransactions = 0;
    std::cout << "Resurse mutate de la contul: "<< accountHolder << std::endl;
}

void Account::deposit(double sum)
{
    if (sum > 0 && nrTransactions < 100)
    {
        transactions[nrTransactions++] = sum;
        sold = sold + sum;
        std::cout << "A transaction was made in your account. New sold: " << sold << "lei." << std::endl;
    }
    else
    {
        std::cout << "Deposit value must be a possitive number or you've reached the maximum number of transactions" << std::endl;
    }
}

void Account::withdraw(double sum)
{
    if (sum > 0 && nrTransactions <= 100)
    {
        if (sum > sold)
        {
            std::cout << "Insufficient funds!!!" << std::endl;
        }
        else
        {
            sold = sold - sum;
            transactions[nrTransactions++] = -sum;
            std::cout << "A transaction was made in your account. The remained sold is: " << sold << " lei" << std::endl;
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