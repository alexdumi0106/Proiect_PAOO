#ifndef BANKENTITY_HPP
#define BANKENTITY_HPP
#include <string>
#include <mutex>
#include <utility>


// C-style Mutex struct
struct Mutex {
    std::mutex mtx;
};


void lock(Mutex* pm);
void unlock(Mutex* pm);

// RAII LockGuard (Item 14)
class LockGuardRAII {
    private:
        Mutex* mutexPtr;

        // Interzicem copierea — conform Item 14
        LockGuardRAII(const LockGuardRAII&) = delete;
        LockGuardRAII& operator=(const LockGuardRAII&) = delete;

    public:
        explicit LockGuardRAII(Mutex* pm);
        ~LockGuardRAII();
};


// Clasa abstracta BankEntity
class BankEntity {
    protected:
        std::string owner;

    public:
        explicit BankEntity(std::string name)
            : owner(std::move(name)) {}

        virtual ~BankEntity() = default;

        virtual void deposit(double amount) = 0;
        virtual void withdraw(double amount) = 0;

        std::string getOwner() const { 
            return owner; 
        }
};

#endif
