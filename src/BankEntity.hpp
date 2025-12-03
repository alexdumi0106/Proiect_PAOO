#pragma once
#include <string>

class BankEntity {
    protected:
        std::string accountHolder;
        double sold;

    public:
        BankEntity(std::string name, double initial)
            : accountHolder(name), sold(initial) {}

        virtual ~BankEntity() = default; // OBLIGATORIU pentru polimorfism

        virtual void deposit(double sum) = 0;
        virtual void withdraw(double sum) = 0;

        std::string getHolder() const { return accountHolder; }
        double getSold() const { return sold; }
};
