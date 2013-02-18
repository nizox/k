#ifndef KERNEL_MEMORY_H_
#define KERNEL_MEMORY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "c/types.h"

/*
 * Units
 */

#define KILOBYTE        1024
#define MEGABYTE        (1024 * KILOBYTE)
#define GIGABYTE        (1024 * MEGABYTE)

/*
 * Setup
 */

#define PURE64_PAGE_SIZE    (2 * MEGABYTE)

/*
 * Tables
 */

#define PURE64_IDT          0x1000
#define PURE64_IDT_SIZE     256
#define PURE64_GDT          0x1000
#define PURE64_GDT_SIZE     256
#define PURE64_PML4         0x2000
#define PURE64_PML4_SIZE    512
#define PURE64_PDP          0x3000
#define PURE64_PDP_SIZE     512
#define PURE64_PD           0x10000
#define PURE64_PD_SIZE      ((256 * KILOBYTE) / 8)

/*
 * Constant addresses
 */

#define VGA_MEM         0xa0000
#define VGA_TEXT        0xb8000
#define VGA_TEXT_SIZE   0xfa0
#define VGA_TEXT_END    VGA_TEXT+VGA_TEXT_SIZE

/*
 * Hardware informations
 */
#define PURE64_SYSTEM_VARIABLES 0x5000

#define SYSTEM_VALUE(type, padd) (*((type*)(PURE64_SYSTEM_VARIABLES + (padd))))

#define CPU_SPEED               SYSTEM_VALUE(uint16_t, 0x10)
#define ACTIVE_CPU_CORES        SYSTEM_VALUE(uint16_t, 0x12)
#define DETECTED_CPU_CORES      SYSTEM_VALUE(uint16_t, 0x14)
#define AVAILABLE_MEMORY        SYSTEM_VALUE(uint32_t, 0x20)

#define STACKBASE       0x400000                /* Stack is at the end of the first page */
#define STACKSIZE       (MEGABYTE)              /* 512KiB stack */
#define STACKLIMIT      STACKBASE - STACKSIZE

#define HEAPBASE        0x200000
#define HEAPSIZE        (MEGABYTE)
#define HEAPLIMIT       HEAPBASE + HEAPSIZE

#define relocate_stack(base)        \
do {                                \
      asm(                          \
          "mov %0, %%rax \n"        \
          "mov %%rax, %%rsp \n"     \
          :: "g"(base)              \
          );                        \
} while (0)

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: KERNEL_MEMORY_H_ */
