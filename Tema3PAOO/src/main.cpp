#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include "BankEntity.hpp"
#include "Account.hpp"

void threadJobShared(std::shared_ptr<Account> acc) {
    for (int i = 0; i < 10; i++)
        acc->deposit(1);
}

void threadJobUnsafe(Account* acc) {
    for (int i = 0; i < 10; i++)
        acc->unsafeDeposit(1);
}

void threadJobCustom(std::shared_ptr<Account> acc) {
    for (int i = 0; i < 10; i++)
        acc->customDeposit(1);
}

int main() {

    // 1) UNIQUE_PTR
    std::unique_ptr<BankEntity> u = std::make_unique<Account>("U", 1000);
    u->deposit(50);

    // 2) SHARED_PTR (folosit cu thread-uri)
    auto accShared = std::make_shared<Account>("Shared", 0);

    std::thread t1(threadJobShared, accShared);
    std::thread t2(threadJobShared, accShared);

    t1.join();
    t2.join();

    std::cout << "Shared (standard mutex) balance = "
              << accShared->getBalance() << "\n";

    // 3) EXEMPLU CARE NU FUNCȚIONEAZĂ — race condition
    /*
    Account bad("Bad", 0);

    std::thread t3(threadJobUnsafe, &bad);
    std::thread t4(threadJobUnsafe, &bad);

    t3.join();
    t4.join();

    std::cout << "Unsafe (no mutex) balance = "
              << bad.getBalance() << " (WRONG!)\n";
    */

    // 4) EXEMPLU CU MUTEX CUSTOM (LockGuardRAII)
    auto accCustom = std::make_shared<Account>("Custom", 0);

    std::thread t5(threadJobCustom, accCustom);
    std::thread t6(threadJobCustom, accCustom);

    t5.join();
    t6.join();

    std::cout << "Custom mutex RAII balance = "
              << accCustom->getBalance() << "\n";

    return 0;
}
