#ifndef INTERRUPTS_H
#define INTERRUPTS_H

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

void init_interrupts(void);

#endif
