#include "c/interrupts.h"
#include "c/exceptions.h"

struct idt_descriptor   idt_gates[IDT_SIZE];
struct idt_register     idtr;

void
idt_gate_set(short index, void * ptr, enum idt_gate_type type, short dpl)
{
    idt_gates[index] = (struct idt_descriptor) {
        .low_word = (uint64_t) ptr & 0xFFFF, /* First 16 bits */
        .ss = 0x8, /* Code segment is the second element of the GDT */
        .ist = 0, /* Interrupt stack table is unset */
        .reserved0 = 0, /* Do not use */
        .type = type,
        .reserved1 = 0, /* Do not use */
        .dpl = dpl,
        .p = 1, /* Set it active */
        .high_word = ((uint64_t) ptr >> 16) & 0xFFFF, /* Next 16 bits */
        .high_dword = (uint64_t) ptr >> 32, /* Last 32 bits */
        .reserved2 = 0 /* Do not use */
    };
}

void
init_idt(void)
{
    short i;

    /*
     * Set the default handler for all interrupts
     */
    for (i = 0; i < IDT_SIZE; ++i)
    {
        idt_gate_set(i, (void *) (exc_default_handlers + i), INTERRUPT, 0);
    }

    /*
     * And set specific handlers for interrupts giving an error
     */
    idt_gate_set(8, &exc_double_fault, INTERRUPT, 0);
    idt_gate_set(10, &exc_invalid_tss, INTERRUPT, 0);
    idt_gate_set(11, &exc_no_segment, INTERRUPT, 0);
    idt_gate_set(12, &exc_stack_fault, INTERRUPT, 0);
    idt_gate_set(13, &exc_general_protection, INTERRUPT, 0);
    idt_gate_set(14, &exc_page_fault, INTERRUPT, 0);
    idt_gate_set(17, &exc_alignment_check, INTERRUPT, 0);

    /* Load the Interrupt Descriptor Table */
    idtr.base = (uint64_t) &idt_gates;
    idtr.limit = sizeof(idt_gates) * sizeof(*idt_gates) - 1;

    __asm__ ("lidt %0\n" : : "m"(idtr));
}

void
init_interrupts(void)
{
    init_catch_all_exceptions();
    init_idt();
}
