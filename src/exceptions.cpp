#include "exceptions.h"
#include "video.h"
#include "std.h"


/*
 * Exception and interrupt reference Intel Vol. 3A 6.15
 */
const char * exception_names[] = {
 /* 0 */  "Divide Error Exception",
 /* 1 */  "Debug Exception",
 /* 2 */  "NMI Interrupt",
 /* 3 */  "Breakpoint Exception",
 /* 4 */  "Overflow Exception",
 /* 5 */  "BOUND Range Exceeded Exception",
 /* 6 */  "Invalid Opcode Exception",
 /* 7 */  "Device Not Available Exception",
 /* 8 */  "Double Fault Exception",
 /* 9 */  "Coprocessor Segment Overrun",
 /* 10 */ "Invalid TSS Exception",
 /* 11 */ "Segment Not Present",
 /* 12 */ "Stack Fault Exception",
 /* 13 */ "General Protection Exception",
 /* 14 */ "Page Fault Exception",
 /* 15 */ 0,
 /* 16 */ "x87 FPU Floating-Point Error",
 /* 17 */ "Alignment Check Exception",
 /* 18 */ "Machine-Check Exception",
 /* 19 */ "SIMD Floating-Point Exception",
 /* 20 */ "Virtualization Exception",
};

void
print_exception(unsigned short i)
{
    char *ptr;

    if (i < sizeof(exception_names) / sizeof(*exception_names))
    {
        video() << exception_names[i] << std::endl;
    }
    else
    {
        video() << "Exception " << i << std::endl;
    }
}


EXC_ERRFUNC(exc_double_fault, 8)(struct exception_frame * frame)
{
    print_exception(frame->exc);
}

EXC_ERRFUNC(exc_invalid_tss, 10)(struct exception_frame * frame)
{
    print_exception(frame->exc);
}

EXC_ERRFUNC(exc_no_segment, 11)(struct exception_frame * frame)
{
    print_exception(frame->exc);
}

EXC_ERRFUNC(exc_stack_fault, 12)(struct exception_frame * frame)
{
    print_exception(frame->exc);
}

EXC_ERRFUNC(exc_general_protection, 13)(struct exception_frame * frame)
{
    print_exception(frame->exc);
}

EXC_ERRFUNC(exc_page_fault, 14)(struct exception_frame * frame)
{
    print_exception(frame->exc);
}

EXC_ERRFUNC(exc_alignment_check, 17)(struct exception_frame * frame)
{
    print_exception(frame->exc);
}

/*
 * Catch all special handler. we don't push the exception number here because
 * we don't know it. But as we can get the EAX that was pushed on the stack
 * instead of the error field, we are able to compute the exception number !
 */
extern "C" __attribute__((naked)) void
exc_catch_all(void)
{
    __asm__ (
        "pushq %rsi"                "\n"
        "pushq %rdi"                "\n"
        "pushq %rbp"                "\n"
        "pushq %r15"                "\n"
        "pushq %r14"                "\n"
        "pushq %r13"                "\n"
        "pushq %r12"                "\n"
        "pushq %r11"                "\n"
        "pushq %r10"                "\n"
        "pushq %r9"                 "\n"
        "pushq %r8"                 "\n"
        "pushq %rdx"                "\n"
        "pushq %rcx"                "\n"
        "pushq %rbx"                "\n"
        "pushq %rax"                "\n"
        "subq $8, %rsp"             "\n"
        "movq %rsp, %rdi"           "\n"
        "call exc_catch_all_handler""\n"
        "addq $8, %rsp"             "\n"
        "popq %rax"                 "\n"
        "popq %rbx"                 "\n"
        "popq %rcx"                 "\n"
        "popq %rdx"                 "\n"
        "popq %r8"                  "\n"
        "popq %r9"                  "\n"
        "popq %r10"                 "\n"
        "popq %r11"                 "\n"
        "popq %r12"                 "\n"
        "popq %r13"                 "\n"
        "popq %r14"                 "\n"
        "popq %r15"                 "\n"
        "popq %rbp"                 "\n"
        "popq %rdi"                 "\n"
        "popq %rsi"                 "\n"
        "addq $8, %rsp"             "\n"
        "iretq"                     "\n"
    );
}

call_instruction exc_default_handlers[IDT_SIZE];

extern "C" void
exc_catch_all_handler(struct exception_frame *frame)
{
    /* Compute the exception number */
    frame->exc = (frame->error - (uint64_t) exc_default_handlers - 5)
        / sizeof(*exc_default_handlers);
    print_exception(frame->exc);
}
