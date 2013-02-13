#ifndef C_EXCEPTIONS_H
#define C_EXCEPTIONS_H

#include "c/types.h"
#include "c/interrupts.h"

#ifdef __cplusplus
export "C" {
#endif

extern void exc_double_fault(void);
extern void exc_invalid_tss(void);
extern void exc_no_segment(void);
extern void exc_stack_fault(void);
extern void exc_general_protection(void);
extern void exc_page_fault(void);
extern void exc_alignment_check(void);

/*
 * This structure will contain the JMP instruction to the catch all
 * exception handler.
 */
typedef uint64_t call_instruction;

extern call_instruction exc_default_handlers[IDT_SIZE];

void init_catch_all_exceptions(void);

#ifdef __cplusplus
}
#endif

#endif
