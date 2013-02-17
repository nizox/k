#ifndef KERNEL_HEAP_H_
#define KERNEL_HEAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "c/memory.h"

void *shlimit(int inc);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: KERNEL_HEAP_H_ */
