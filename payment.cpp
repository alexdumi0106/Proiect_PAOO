#include <iostream>
#include <string>
using namespace std;

class Payment
{
    protected:
        double amount;

    public:
        Payment(double amt) : amount(amt) {};

        virtual void processPayment() const = 0;

        double getAmount() const
        {
            return amount;
        };

        virtual ~Payment() {};
};

class CardPayment : public Payment
{
    protected:
        string cardNumber;

    public:
        CardPayment(double amt, string cardNr) : Payment(amt), cardNumber(cardNr) {};

        void processPayment() const override {
            cout<<"Processing card payment of "<< amount << "using card "<< cardNumber<< endl;
        }
};

class CashPayment : public Payment 
{
    public:
        CashPayment(double amt) : Payment(amt) {};

        void processPayment() const override {
            cout<<"Processing cash payment of "<< amount << " ron. "<<endl;
        }

        ~CashPayment() {};
};

class CryptoPayment : public Payment 
{
    protected:
        string walletAddress;
    public:
        CryptoPayment(double amt, string walletAddr): Payment(amt), walletAddress(walletAddr) {};

        void processPayment() const override {
            cout<<" Processing crypto payment of "<< amount << " using wallet: "<< walletAddress<< endl;
        };
        ~CryptoPayment() {};
};

int main()
{
    Payment* card = new CardPayment( 200.0, "1234-8876-3378-0009");
    Payment* cash = new CashPayment(900.0);
    Payment* crypto = new CryptoPayment(1500.0, "1A2B");

    card->processPayment();
    cash->processPayment();
    crypto->processPayment();

    delete crypto;
    delete cash;
    delete card;
};