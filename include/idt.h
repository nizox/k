#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "c/types.h"

#define IDT_SIZE    256

class idt
{
 public:
    enum gate_type
    {
        trap = 0xE,
        interrupt = 0xF
    };

    void set_gate(short i, void (*ptr)(), gate_type type = interrupt,
            short dpl = 0);

    /* Make this IDT active */
    void setup();

 private:
    struct __attribute__((packed)) descriptor
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
    } descriptors[IDT_SIZE];

    struct __attribute__((packed))
    {
        uint64_t limit : 16;
        uint64_t base  : 64;
    } idtr;
};


#endif
