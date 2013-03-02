#include "apic.h"
#include "exceptions.h"

local_apic::local_apic(local_apic::register_t * base_addr):
    base_register_addr(base_addr)
{
}

local_apic::~local_apic()
{
}

int
local_apic::get_id()
{
    return get(local_apic::id) >> 24;
}

void
local_apic::send_eoi(local_apic::register_t value)
{
    set(local_apic::eoi, value);
}

void
local_apic::setup()
{
    /* Set destination format to flat mode */
    set_bit(local_apic::destination_format, 0xF << 28);
    /* Set logical destination to 1 so all CPU are in the same group */
    //set_bit(local_apic::logical_destination, 0x1 << 24);
    /* Clear the task priority */
    set(local_apic::task_priority, 0x0);
}

void
local_apic::enable()
{
    /* Enable the Local APIC and set the spurious interrupt vector.
     * The 8th bit enables the local APIC, and the interrupt vector must
     * have bits 0 to 3 set to 1. 79 is 01001111
     */
    set_bit(local_apic::spurious_interrupt_vector, 1 << 8 | 79);
}
