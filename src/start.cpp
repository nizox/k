#include "c/print.h"
#include "c/screen.h"
#include "c/heap.h"
#include "c/types.h"
#include "c/memory.h"

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

    screen << "Loading IDT ..." << std::endl;
    _isr.setup();
    screen << "IDT Loaded." << std::endl;

    for(;;);
}
