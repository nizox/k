#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

/* Structures described in Intel Vol. 3A 6.14 */
#pragma pack(push, 1)
struct idt_register
{
    uint16_t limit;
    uint64_t base;
};

struct idt_descriptor
{
    uint16_t low_word;
    uint16_t cs_selector;
    uint8_t  reserved0;
    uint8_t  flags;
    uint16_t high_word;
    uint32_t high_dword;
    uint32_t reserved1;
};
#pragma pack(pop)

struct exception_frame
{
    /* Exception number */
    uint64_t reason;
    /* Saved registers */
    uint64_t rdi;

    /* Optional exception error code */
    uint64_t error;
    /* Default interruption args */
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
};

/*
 * Nice trick from Clang to make C function without stack manipulation
 */
#define EXC_ERRFUNC(name, num)                          \
__attribute__((naked)) void                             \
name (void)                                             \
{                                                       \
    __asm__ (                                           \
        "pushq %rdi"                "\n"                \
        "pushq $" # num             "\n"                \
        "movq %rsp, %rdi"           "\n"                \
        "call " # name "_handler"   "\n"                \
        "addq $8, %rsp"             "\n"                \
        "popq %rdi"                 "\n"                \
        "iretq"                     "\n"                \
    );                                                  \
}                                                       \
void name ## _handler

void init_interrupts(void);

#ifdef __cplusplus
}
#endif

#endif
