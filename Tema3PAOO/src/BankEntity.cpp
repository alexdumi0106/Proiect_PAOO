#include "BankEntity.hpp"

// ---------------------------
// DEFINIȚII lock/unlock
// ---------------------------
void lock(Mutex* pm) {
    pm->mtx.lock();
}

void unlock(Mutex* pm) {
    pm->mtx.unlock();
}

// ---------------------------
// DEFINIȚII LockGuardRAII
// ---------------------------
LockGuardRAII::LockGuardRAII(Mutex* pm)
    : mutexPtr(pm)
{
    lock(mutexPtr);  // RAII acquire
}

LockGuardRAII::~LockGuardRAII() {
    unlock(mutexPtr);  // RAII release
}
