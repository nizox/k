#include "c/types.h"

// This function is used as a fallback on pure-virtual function call.
// If not provided, C++ compilers such as clang++ or g++ will use this
// symbol in their thunk function without providing it. Therefore
// linker will complain for an unresolved symbol.
extern "C" {

void *__dso_handle;

void __cxa_pure_virtual()
{}

int __cxa_atexit(void (*destructor) (void *), void *arg, void *dso)
{
    (void)destructor;
    (void)arg;
    (void)dso;
    return -1;
}

}

void*           operator new(size_t)
{
    return (void*)0;
}

void*           operator new[](size_t)
{
    return (void*)0;
}

void            operator delete(void *)
{
}

void            operator delete[](void *)
{
}
