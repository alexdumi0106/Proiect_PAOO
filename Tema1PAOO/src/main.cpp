#include <iostream>
#include <Account.hpp>
#include <utility>

Account createTemporaryAccount()
{
    Account temporaryAccount("Temporary account", 400);
    temporaryAccount.deposit(200);
    return temporaryAccount;
}

int main()
{
    /*Account myAccount("Alex Dumitrescu", 1000.0);

    std::cout << "Account name: " << myAccount.getAccountHolder() << ".\n";
    std::cout << "Sold: " << myAccount.getSold() << "\n";

    myAccount.deposit(250);
    myAccount.withdraw(150);

    Account copiedAccount = myAccount;
    copiedAccount.showTransactions();

    Account mySecondAccount = std::move(myAccount);
    mySecondAccount.showTransactions();

    Account myThirdAccount = createTemporaryAccount();
    myThirdAccount.showTransactions();*/

    /*Account a("A", 1000);
    Account b("B", 500);
    Account c("C", 200);

    a = b = c;
    a = std::move(b);

    a.showTransactions();
    b.showTransactions();
    c.showTransactions();

    a = a;*/

    std::cout<<"Exemplu cu copy-assignment. Cont secundar in cazul unei probleme cu principalul cont.\n";
    Account masterCard("Alex Dumitrescu", 1500.0);
    masterCard.deposit(500);
    masterCard.withdraw(700);

    Account temporaryMasterCard("Temporary account for Alex D", 0.0);
    temporaryMasterCard = masterCard; //Copy-assignment
    temporaryMasterCard.withdraw(200);

    std::cout<<"Master Card:\n";
    masterCard.showTransactions();

    std::cout<<"Temporary master card:\n";
    temporaryMasterCard.showTransactions();

    masterCard.deposit(400); //Demonstratie deep-copy, modificand originalul

    std::cout<<"Master Card:\n";
    masterCard.showTransactions();

    std::cout<<"Temporary master card:\n";
    temporaryMasterCard.showTransactions();

    std::cout<<"\n";
    std::cout<<"Exemplu cu move assignment. Mutarea contului de pe serverul vechi pe unul nou.\n";
    Account oldServerMasterCard("Alex Dumitrescu", 2000.0);
    oldServerMasterCard.deposit(500);
    oldServerMasterCard.withdraw(300);

    std::cout<<"Account from old server, before moving:\n";
    oldServerMasterCard.showTransactions();

    Account newServerMasterCard("New server account for Alex D", 0.0);

    newServerMasterCard = std::move(oldServerMasterCard);

    std::cout<<"Account from new server, after moving:\n";
    newServerMasterCard.showTransactions();

    std::cout<<"Account from old server, after moving:\n";
    oldServerMasterCard.showTransactions();

    return 0;
}