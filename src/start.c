#include "interrupts.h"
#include "screen.h"
#include "print.h"
#include "string.h"

extern char kX;
extern char kY;

/*
 * This is the entry point of the kernel
 * we must never return from this function
 */
void
_start(void)
{
    screen_init_default();
    puts("Loading IDT ...");
    init_interrupts();
    puts("IDT loaded.");

    /* Put a fun message here */
    for(;;);
}
