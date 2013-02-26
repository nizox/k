#include "isr.h"
#include "video.h"
#include "kheap.h"

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

    screen << "Initializing kernel heap ..." << std::endl;
    kheap::brk          brk(info);
    if (brk.ok())
      {
        screen << "Heap start address: " << brk.get() << "" << std::endl;
        screen << "Heap limit: " << (int)TO_MEGABYTES(brk.limit()) << " Mib" << std::endl;
      }
    else
        goto loop;

    screen << "Loading IDT ..." << std::endl;
    _isr.setup();
    screen << "IDT Loaded." << std::endl;

loop:
    for(;;);
}
