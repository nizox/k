#ifndef KERNEL_C_TYPES_H_
#define KERNEL_C_TYPES_H_

#include "c/kernel.h"

__C_BEGIN

/* This is for LLP64 systems.
 * See http://wiki.osdev.org/X86-64#Data_Types
 */

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;
typedef uint64_t            intptr_t;

typedef long long           intmax_t;
typedef unsigned long long  uintmax_t;

typedef long long           intptr_t;
typedef unsigned long long  uintptr_t;

typedef unsigned long       size_t;
typedef long                ssize_t;

__C_END


#endif /* end of include guard: KERNEL_C_TYPES_H_ */
