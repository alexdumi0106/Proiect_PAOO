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
    Account myAccount("Alex Dumitrescu", 1000.0);

    std::cout << "Account name: " << myAccount.getAccountHolder() << ".\n";
    std::cout << "Sold: " << myAccount.getSold() << "\n";

    myAccount.deposit(250);
    myAccount.withdraw(150);

    Account copiedAccount = myAccount;
    copiedAccount.showTransactions();

    Account mySecondAccount = std::move(myAccount);
    mySecondAccount.showTransactions();

    Account myThirdAccount = createTemporaryAccount();
    myThirdAccount.showTransactions();

    return 0;
}