#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include "BankEntity.hpp"
#include "Account.hpp"

void threadJob(std::shared_ptr<BankEntity> acc, int id) {
    acc->deposit(10);
}

int main()
{
    std::unique_ptr<BankEntity> acc = std::make_unique<Account>("Unique", 1000);
    auto accShared = std::make_shared<Account>("Shared", 200);

    auto a = std::make_shared<Account>("Threaded", 500);

    std::thread t1(threadJob, a, 1);
    std::thread t2(threadJob, a, 2);

    t1.join();
    t2.join();

    /*
    auto bad = std::make_shared<Account>("Bad", 300);

    std::thread t1([&](){ bad->deposit(10); });
    std::thread t2([&](){ bad->deposit(10); });

    t1.join();
    t2.join();
    // unpredictable behavior — unprotected shared resource
    */

    /*
    std::unique_ptr<Account> a = std::make_unique<Account>("A", 100);
    std::unique_ptr<Account> b = a; // ERROR — copy forbidden
    */

    /*
    auto sp = std::make_shared<Account>("Dangling", 100);
    Account* raw = sp.get();
    sp.reset();
    // raw->deposit(10); // CRASH — use after free
    */



    return 0;
}