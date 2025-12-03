#include "BankEntity.hpp"



void lock(Mutex* pm) {
    pm->mtx.lock();
}

void unlock(Mutex* pm) {
    pm->mtx.unlock();
}


LockGuardRAII::LockGuardRAII(Mutex* pm)
    : mutexPtr(pm)
{
    lock(mutexPtr);  
}

LockGuardRAII::~LockGuardRAII() {
    unlock(mutexPtr);  
}
