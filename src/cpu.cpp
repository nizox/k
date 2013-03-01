#include "cpu.h"

cpu::cpu()
{
}

cpu::~cpu()
{
}

bool
cpu_features::has_msr(void)
{
    return value.reg.edx & (1 << 5);
}

bool
cpu_features::has_apic(void)
{
    return value.reg.edx & (1 << 9);
}

/* We should probably return a copy of the string here instead of a pointer
* to the buffer which is not ended by '\0'.
*/
char const *
cpu::get_vendor_id(void)
{
    cpuid_request(tmp, cpu::vendor_string);
    return tmp.value.vendor_string;
}

cpu_features &
cpu::get_features(void)
{
    cpuid_request(tmp, cpu::features);
    return static_cast<cpu_features &>(tmp);
}

uint64_t
cpu::get_rflags(void)
{
    uint64_t rflags;

    __asm__ (
        "pushfq"  "\n"
        "popq %0" "\n"
    : "=m"(rflags) : );

    return rflags;
}

cpuid_response &
cpu::cpuid_request(cpuid_response & r, cpu::cpuid_request_type req)
{
    __asm__ (
        "cpuid" : "=a"(r.value.reg.eax), "=b"(r.value.reg.ebx),
        "=c"(r.value.reg.ecx), "=d"(r.value.reg.edx) : "a"(req)
    );
    return r;
}

local_apic &
cpu::get_local_apic()
{
    return lapic;
}

void
cpu::setup()
{
    disable_interrupts();
    lapic.setup();
    lapic.enable();
    enable_interrupts();
}

void
cpu::enable_interrupts()
{
    __asm__ ("sti");
}

void
cpu::disable_interrupts()
{
    __asm__ ("cli");
}
