#include <iostream>
#include <Account.hpp>

int main()
{
    Account myAccount("Alex Dumitrescu", 1000.0);

    std::cout << "Titular: " << myAccount.getAccountHolder() << "\n";
    std::cout << "Sold: " << myAccount.getSold() << "\n";

    myAccount.deposit(250);
    std::cout << "A transaction was made in your account. New sold: " << myAccount.getSold() << "\n";

    myAccount.withdraw(150);
    std::cout << "A transaction was made in your account. New sold: " << myAccount.getSold() << "\n";

    myAccount.showTransactions();

    return 0;
}