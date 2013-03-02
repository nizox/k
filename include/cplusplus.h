#pragma once
#ifndef CPLUSPLUS_9QQXACFD
#define CPLUSPLUS_9QQXACFD

#include "c/types.h"

void    call_global_ctors();
void*   operator new(size_t);
void*   operator new[](size_t);
void    operator delete(void *);
void    operator delete[](void *);

#endif /* end of include guard: CPLUSPLUS_9QQXACFD */
