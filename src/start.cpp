#include "c/print.h"
#include "c/screen.h"
#include "c/interrupts.h"

/*
 * This is the entry point of the kernel
 * we must never return from this function
 */
extern "C"
void            _cppstart(void)
{
    screen_init_default();
    puts("Loading IDT ...");
    init_interrupts();
    puts("IDT loaded.");

    /* Put a fun message here */
    for(;;);
}
