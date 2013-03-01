#include "isr.h"
#include "video.h"
#include "kheap.h"
#include "allocator.h"
#include "cpu.h"
#include "ioapic.h"

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
    cpu                 cpu;
    ioapic              ioapic(cpu);

    /* Interrupts are disabled by the bootloader but we want it to be clear */
    cpu.disable_interrupts();

    screen << "Initializing IDT ...";
    _isr.setup();
    screen << " ok" << std::endl;

    screen << "Initializing CPU ...";
    cpu.setup();
    screen << " ok" << std::endl;

    screen << "Initializing IOAPIC ...";
    ioapic.setup();
    screen << " ok" << std::endl;

    cpu.enable_interrupts();

    //screen << cpu.get_local_apic().get_id() << std::endl;

    memory::info        info(AVAILABLE_MEMORY MEGABYTES, 2 MEGABYTES, memory::pml4, memory::pdp, memory::pd);

    screen << "Initializing kernel heap ...";
    kheap::brk          brk(info);
    screen << " ok" << std::endl;

    screen << "Initializing allocator ...";
    allocator           kmemalloc(brk);
    global_allocator::set_allocator(&kmemalloc);
    screen << " ok" << std::endl;

    for(;;);
}
