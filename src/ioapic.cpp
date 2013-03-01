#include "ioapic.h"

ioapic_redirect_entry::ioapic_redirect_entry(ioapic & io, int index):
    _ioapic(io), _index(index)
{
}

ioapic_redirect_entry::~ioapic_redirect_entry()
{
}

void
ioapic_redirect_entry::commit()
{
    _ioapic.set(ioapic::redirect_table + _index * 2, value.raw[0]);
    _ioapic.set(ioapic::redirect_table + _index * 2 + 1, value.raw[1]);
}

ioapic::ioapic(cpu & default_cpu, ioapic::register_t * base_addr):
    main_cpu(default_cpu), base_register_addr(base_addr)
{
}

ioapic::~ioapic()
{
}

ioapic_redirect_entry
ioapic::get_redirect_entry(int index)
{
    ioapic_redirect_entry buf(*this, index);

    buf.value.raw[0] = get(ioapic::redirect_table + index * 2);
    buf.value.raw[1] = get(ioapic::redirect_table + index * 2 + 1);
    return buf;
}

uint64_t
ioapic::get_max_redirect_entry() const
{
    version_register value;
    value.raw = get(ioapic::version);
    return value.r.max_redirect_entry;
}

void
ioapic::setup()
{
    uint64_t i;
    uint64_t max = get_max_redirect_entry();

    for (i = 0; i < max; ++i)
    {
        ioapic_redirect_entry entry = get_redirect_entry(i);
        entry.mask();
        entry.commit();
    }
}
