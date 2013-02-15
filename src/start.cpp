#include "c/print.h"
#include "c/screen.h"

#include "isr.h"
#include "video.h"
#include "std.h"

/*
 * This is the entry point of the kernel
 * we must never return from this function
 */
extern "C"
void            _cppstart(void)
{
    video       screen;

    screen << "Loading IDT ...";
    _isr.setup();
    screen << video::printok << std::endl;

    /* Put a fun message here */
    for(;;);
}
