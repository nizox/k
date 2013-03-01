#ifndef ISR_H
#define ISR_H

#include "idt.h"

class isr
{
 public:
    void setup();

 private:
    idt _idt;
};

extern isr _isr;

#endif
