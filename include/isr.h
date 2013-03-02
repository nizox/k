#ifndef ISR_H
#define ISR_H

#include "idt.h"

class isr
{
 public:
    void set_interrupt_gate(short i, void (*ptr)());
    void setup();

 private:
    idt _idt;
};

extern isr _isr;

#endif
