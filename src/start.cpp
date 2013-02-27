#include "isr.h"
#include "video.h"
#include "kheap.h"
#include "allocator.h"

#include "c/string.h"

/*
 * This is the entry point of the kernel
 * we must never return from this function
 */
extern "C"
void
_cppstart(void)
{
    video               screen;
    memory::info        info(AVAILABLE_MEMORY MEGABYTES, 2 MEGABYTES, memory::pml4, memory::pdp, memory::pd);
    kheap::brk          brk(info);
    allocator           kmemalloc(brk);

    screen << "Initializing kernel heap ..." << std::endl;
    screen << "Loading IDT ..." << std::endl;
    _isr.setup();
    screen << "IDT Loaded." << std::endl;

    for(;;);
}
