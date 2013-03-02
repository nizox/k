#include "isr.h"
#include "exceptions.h"
#include "video.h"

isr _isr;

void
isr::setup()
{
    short i;
    uint64_t r;

    /*
     * Set the default handler for all interrupts.
     *
     * There is no way to get the exception number from a common handler.
     * But there is this trick that we came up to: we will fill an array of
     * 8 bytes fields with relative call to the common handler.
     *
     * We must use 8 bytes fields because the relative call instruction use a 4
     * bytes (32 bits) argument. So we will only use 5 bytes.
     *
     * By doing a call to our handler, the next instruction address will be
     * pushed to the stack and by positioning wisely the array in memory we
     * will be able to compute the exception number from the common handler.
     *
     * So basically the memory will be like:
     * 0000000000101720 <exc_catch_all>
     * ...
     * 0000000000102d50 0xffe9cbe8  0xffffffff
     * 0000000000102d58 0xffe9c3e8  0xffffffff
     * 0000000000102d60 0xffe9bbe8  0xffffffff
     * 0000000000102d68 0xffe9b3e8  0xffffffff
     *
     */
    for (i = 0; i < IDT_SIZE; ++i)
    {
        r = (uint64_t) (exc_default_handlers + i) - (uint64_t) exc_catch_all;
        ::exc_default_handlers[i] = (- r - 5) << 8 | 0xE8 /* E8 is CALL */;
        _idt.set_gate(i, (void (*)()) &exc_default_handlers[i]);
    }

    /*
     * And set specific handlers for interrupts giving an error
     */
    _idt.set_gate(8, &exc_double_fault);
    _idt.set_gate(10, &exc_invalid_tss);
    _idt.set_gate(11, &exc_no_segment);
    _idt.set_gate(12, &exc_stack_fault);
    _idt.set_gate(13, &exc_general_protection);
    _idt.set_gate(14, &exc_page_fault);
    _idt.set_gate(17, &exc_alignment_check);

    _idt.setup();
}

void
isr::set_interrupt_gate(short i, void (*ptr)())
{
    _idt.set_gate(i, ptr);
}
