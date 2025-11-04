#include <Account.hpp>
#include <iostream>

Account::Account(std::string name, double initialAmount) 
    : accountHolder(name), sold(initialAmount), nrTransactions(0)
{
    transactions = new double[100];
    std::cout<< "Cont creat pentru "<< accountHolder << " cu soldul de "<< sold << " lei.\n";
}

Account::~Account()
{
    std::cout << "Free memory for account holder: " << accountHolder << ".\n";
    delete[] transactions;
}

void Account::deposit(double sum) {
    if(sum > 0 && nrTransactions < 100){
        transactions[nrTransactions++] = sum;
        sold = sold + sum;
    }
    else{
        std::cout << "Deposit value must be a possitive number or you've reached the maximum number of transactions" <<std::endl;
    }
}

void Account::withdraw(double sum) {
    if(sum > 0 && nrTransactions <= 100){
        if(sum > sold){
            std::cout << "Insufficient funds!!!" << std::endl;
        }
        else {
            sold = sold - sum;
            transactions[nrTransactions++] = -sum;
            std::cout << "The sold remained is: "<< sold << " lei" << std::endl;
        }
    } else{
        std::cout << "Withdraw value must be a possitivie number!" <<std::endl;
    }
}

double Account::getSold() const {
    return sold;
}

std::string Account::getAccountHolder() const {
    return accountHolder;
}

void Account::showTransactions() const
{
    std::cout << "Transactions for user: "<< accountHolder << ":";
    for(int i = 0; i < nrTransactions; i++)
    {
        std::cout << transactions[i] << " ";
    }
    std::cout << "\n";
}