#include "c/interrupts.h"

struct idt_descriptor   idt_gates[256];
struct idt_register     idtr;

void
idt_gate_set(short index, uint64_t ptr, uint8_t flags)
{
    idt_gates[index] = (struct idt_descriptor) {
        .low_word = ptr & 0xFFFF, /* First 16 bits */
        .cs_selector = 0x8, /* Code segment is the second element of the GDT */
        .reserved0 = 0, /* Do not use */
        .flags = flags,
        .high_word = (ptr >> 16) & 0xFFFF, /* Next 16 bits */
        .high_dword = ptr >> 32, /* Last 32 bits */
        .reserved1 = 0 /* Do not use */
    };
}

void
exception_handler(void)
{
    for(;;);
}

void
init_idt(void)
{
    short i;

    /* Initialize exception gates */
    for (i = 0; i < 32; ++i)
    {
        /* 0x8E is the 64 bits interrupt gate flag */
        idt_gate_set(i, (uint64_t) &exception_handler, 0x8E);
    }

    idtr.base = (uint64_t) &idt_gates;
    idtr.limit = sizeof(idt_gates) * sizeof(*idt_gates) - 1;

    /* Load the Interrupt Descriptor Table */
    asm ("lidt (idtr)");
}

void
init_interrupts(void)
{
    init_idt();
}
