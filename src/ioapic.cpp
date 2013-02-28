#include "ioapic.h"

ioapic::ioapic(ioapic::register_t * base_addr):
    base_register_addr(base_addr)
{
}

ioapic::~ioapic()
{
}

uint64_t
ioapic::get_max_redirect_entry() const
{
    version_register value;
    value.raw = get(ioapic::version);
    return value.r.max_redirect_entry;
}

void
ioapic::set_default_cpu(cpu * cpu)
{
    default_cpu = cpu;
}

void
ioapic::setup()
{
    uint64_t i;
    uint64_t max = get_max_redirect_entry();

    /* mask all */
    for (i = 0; i < max; ++i)
    {
    }
}
