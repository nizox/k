#include "lock.h"

lock::lock()
{
}

lock::~lock()
{
}

bool
lock::is_locked()
{
    return _locked;
}

/* Returns 0 if lock is successful 1 otherwise */
bool
lock::take()
{
    bool r;

    __asm__ (
        "lock"             "\n"
        "cmpxchgl %2, %1"  "\n"
        : "=a"(r), "+m"(_locked)
        : "r"(1), "a"(0)
    );
    return r;
}

/* Returns 0 when the lock has been released 1 otherwise */
bool
lock::release()
{
    bool r;

    __asm__ (
        "lock"             "\n"
        "cmpxchgl %2, %1"  "\n"
        : "=a"(r), "+m"(_locked)
        : "r"(0), "a"(1)
    );
    return !r;
}
