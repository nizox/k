#ifndef C_EXCEPTIONS_H
#define C_EXCEPTIONS_H

#include "c/types.h"
#include "idt.h"

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
extern "C" __attribute__((naked)) void                  \
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
extern "C" void name ## _handler

#define EXC_FUNC(name, num)                             \
extern "C" __attribute__((naked)) void                  \
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
extern "C" void name ## _handler

/*
 * This structure will contain the JMP instruction to the catch all
 * exception handler.
 */
typedef uint64_t call_instruction;

extern call_instruction exc_default_handlers[IDT_SIZE];

extern "C" void exc_catch_all(void);

extern "C" void exc_double_fault(void);
extern "C" void exc_invalid_tss(void);
extern "C" void exc_no_segment(void);
extern "C" void exc_stack_fault(void);
extern "C" void exc_general_protection(void);
extern "C" void exc_page_fault(void);
extern "C" void exc_alignment_check(void);

#endif
