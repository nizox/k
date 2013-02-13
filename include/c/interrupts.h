#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

#define IDT_SIZE  256

/* Structures and enum described in Intel Vol. 3A 6.14 */
#pragma pack(push, 1)
struct idt_register
{
    uint64_t limit : 16;
    uint64_t base  : 64;
};

struct idt_descriptor
{
    uint64_t low_word    : 16;
    uint64_t ss          : 16;
    uint64_t ist         : 3;
    uint64_t reserved0   : 5;
    uint64_t type        : 4;
    uint64_t reserved1   : 1;
    uint64_t dpl         : 2;
    uint64_t p           : 1;
    uint64_t high_word   : 16;
    uint64_t high_dword  : 32;
    uint64_t reserved2   : 32;
};
#pragma pack(pop)

enum idt_gate_type
{
    TRAP = 0xE,
    INTERRUPT = 0xF
};


struct exception_frame
{
    /* Exception number */
    uint64_t exc;

    /* Saved registers */
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;

    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;

    uint64_t rbp;
    uint64_t rdi;
    uint64_t rsi;

    /* Default interruption args on the stack
     * See Intel Vol. 3A Figure 6-8
     *
     * Optional exception error code
     */
    uint64_t error;
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
};


/*
 * Nice trick from Clang to make C function without stack manipulation.
 * EXC_ERRFUNC and EXC_FUNC create an exception handler which saves registers
 * in the exception_frame structure.
 *
 * EXC_ERRFUNC is made for interrupts that give an error code.
 */
#define EXC_ERRFUNC(name, num)                          \
__attribute__((naked)) void                             \
name (void)                                             \
{                                                       \
    __asm__ (                                           \
        "pushq %rsi"                "\n"                \
        "pushq %rdi"                "\n"                \
        "pushq %rbp"                "\n"                \
        "pushq %r15"                "\n"                \
        "pushq %r14"                "\n"                \
        "pushq %r13"                "\n"                \
        "pushq %r12"                "\n"                \
        "pushq %r11"                "\n"                \
        "pushq %r10"                "\n"                \
        "pushq %r9"                 "\n"                \
        "pushq %r8"                 "\n"                \
        "pushq %rdx"                "\n"                \
        "pushq %rcx"                "\n"                \
        "pushq %rbx"                "\n"                \
        "pushq %rax"                "\n"                \
        "pushq $" # num             "\n"                \
        "movq %rsp, %rdi"           "\n"                \
        "call " # name "_handler"   "\n"                \
        "addq $8, %rsp"             "\n"                \
        "popq %rax"                 "\n"                \
        "popq %rbx"                 "\n"                \
        "popq %rcx"                 "\n"                \
        "popq %rdx"                 "\n"                \
        "popq %r8"                  "\n"                \
        "popq %r9"                  "\n"                \
        "popq %r10"                 "\n"                \
        "popq %r11"                 "\n"                \
        "popq %r12"                 "\n"                \
        "popq %r13"                 "\n"                \
        "popq %r14"                 "\n"                \
        "popq %r15"                 "\n"                \
        "popq %rbp"                 "\n"                \
        "popq %rdi"                 "\n"                \
        "popq %rsi"                 "\n"                \
        "iretq"                     "\n"                \
    );                                                  \
}                                                       \
void name ## _handler

#define EXC_FUNC(name, num)                             \
__attribute__((naked)) void                             \
name (void)                                             \
{                                                       \
    __asm__ (                                           \
        "subq $8, %rsp"             "\n"                \
        "pushq %rsi"                "\n"                \
        "pushq %rdi"                "\n"                \
        "pushq %rbp"                "\n"                \
        "pushq %r15"                "\n"                \
        "pushq %r14"                "\n"                \
        "pushq %r13"                "\n"                \
        "pushq %r12"                "\n"                \
        "pushq %r11"                "\n"                \
        "pushq %r10"                "\n"                \
        "pushq %r9"                 "\n"                \
        "pushq %r8"                 "\n"                \
        "pushq %rdx"                "\n"                \
        "pushq %rcx"                "\n"                \
        "pushq %rbx"                "\n"                \
        "pushq %rax"                "\n"                \
        "pushq $" # num             "\n"                \
        "movq %rsp, %rdi"           "\n"                \
        "call " # name "_handler"   "\n"                \
        "addq $8, %rsp"             "\n"                \
        "popq %rax"                 "\n"                \
        "popq %rbx"                 "\n"                \
        "popq %rcx"                 "\n"                \
        "popq %rdx"                 "\n"                \
        "popq %r8"                  "\n"                \
        "popq %r9"                  "\n"                \
        "popq %r10"                 "\n"                \
        "popq %r11"                 "\n"                \
        "popq %r12"                 "\n"                \
        "popq %r13"                 "\n"                \
        "popq %r14"                 "\n"                \
        "popq %r15"                 "\n"                \
        "popq %rbp"                 "\n"                \
        "popq %rdi"                 "\n"                \
        "popq %rsi"                 "\n"                \
        "addq $8, %rsp"             "\n"                \
        "iretq"                     "\n"                \
    );                                                  \
}                                                       \
void name ## _handler

void init_interrupts(void);
void idt_gate_set(short index, void * ptr, enum idt_gate_type type, short dpl);

#ifdef __cplusplus
}
#endif

#endif
