#include "idt.h"

void
idt::set_gate(short i, void (*ptr)(), idt::gate_type type, short dpl)
{
    idt::descriptor desc = {
        .low_word = (uint64_t) ptr & 0xFFFF, /* First 16 bits */
        .ss = 0x8, /* Code segment is the second element of the GDT */
        .ist = 0, /* Interrupt stack table is unset */
        .reserved0 = 0, /* Do not use */
        .type = type,
        .reserved1 = 0, /* Do not use */
        .dpl = static_cast<uint64_t>(dpl),
        .p = 1, /* Set it active */
        .high_word = ((uint64_t) ptr >> 16) & 0xFFFF, /* Next 16 bits */
        .high_dword = (uint64_t) ptr >> 32, /* Last 32 bits */
        .reserved2 = 0 /* Do not use */
    };
    descriptors[i] = desc;
}


void
idt::setup()
{
    idtr.base = (uint64_t) &descriptors;
    idtr.limit = sizeof(descriptors) * sizeof(*descriptors) - 1;

    /* Load the Interrupt Descriptor Table */
    __asm__ ("lidt %0\n" : : "m"(idtr));
}
