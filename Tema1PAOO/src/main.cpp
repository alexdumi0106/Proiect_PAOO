#include <iostream>
#include <Account.hpp>
#include <utility>

Account createTemporaryAccount()
{
    Account temporaryAccount("Cont temporar", 400);
    temporaryAccount.deposit(200);
    return temporaryAccount;
}

int main()
{
    Account myAccount("Alex Dumitrescu", 1000.0);

    std::cout << "Titular: " << myAccount.getAccountHolder() << ".\n";
    std::cout << "Sold: " << myAccount.getSold() << "\n";

    myAccount.deposit(250);
    myAccount.withdraw(150);

    /*Account mySecondAccount = myAccount;
    std::cout << "Cont nou deschis pe numele: " << mySecondAccount.getAccountHolder() << ".\n";
    std::cout << "Sold: " << mySecondAccount.getSold() << "\n";

    myAccount.deposit(250);
    myAccount.withdraw(150);

    myAccount.showTransactions();

    mySecondAccount.deposit(100);
    mySecondAccount.withdraw(250);

    mySecondAccount.showTransactions();*/

    Account mySecondAccount = std::move(myAccount);
    mySecondAccount.showTransactions();

    Account myThirdAccount = createTemporaryAccount();
    myThirdAccount.showTransactions();

    return 0;
}