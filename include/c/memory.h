#ifndef KERNEL_MEMORY_H_
#define KERNEL_MEMORY_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Kernel Memory Mapping
 *
 * +-----------------------+    0x0
 * | IDT                   |
 * +-----------------------+    0xFFF
 * +-----------------------+    0x1000
 * | GDT                   |
 * +-----------------------+    0x1FFF
 * +-----------------------+    0x2000
 * | PML4                  |
 * +-----------------------+    0x2FFF
 * +-----------------------+    0x3000
 * | PDP                   |
 * +-----------------------+    0x3FFF
 *        ........
 * +-----------------------+    0x10000
 * | Page Directory room   |
 * +-----------------------+    0x4FFFF
 *        ........
 * +-----------------------+    0x100000
 * | Kernel Code           |
 * +-----------------------+    0x1FFFFF
 *
 * ======= Next Page =======
 *
 * +-----------------------+    0x200000
 * | Heap                  |
 * +-----------------------+    0x2FFFFF
 * +-----------------------+    0x300000
 * | Stack                 |
 * +-----------------------+    0x3FFFF
 */

#define PML4            0x2000

#define KILOBYTE        1024
#define MEGABYTE        (1024 * KILOBYTE)
#define GIGABYTE        (1024 * MEGABYTE)

#define STACKBASE       0x400000              /* Stack is at the end of the first page */
#define STACKSIZE       (MEGABYTE)        /* 512KiB stack */
#define STACKLIMIT      STACKBASE - STACKSIZE

#define relocate_stack(base)        \
do {                                \
      asm(                          \
          "mov %0, %%rax \n"        \
          "mov %%rax, %%rsp \n"     \
          :: "i"(base)              \
          );                        \
} while (0)

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: KERNEL_MEMORY_H_ */
