#ifndef CPU_H
#define CPU_H

#include "c/types.h"

class cpuid_response
{
  protected:
    union
    {
        struct
        {
            uint32_t ebx;
            uint32_t edx;
            uint32_t ecx;
            uint32_t eax;
        } reg;
        char vendor_string[12];
    } value;

    friend class cpu;
};


class cpu_features: public cpuid_response
{
  public:
    bool has_apic(void);
    bool has_msr(void);
};


class cpu
{
  public:
    uint64_t get_rflags(void);
    /*
     * As we have no dynamic memory allocation yet, these functions cannot be
     * used in the same time as they share the same response buffer.
     */
    char const * get_vendor_id(void);
    cpu_features & get_features(void);

  protected:
    enum cpuid_request_type
    {
        vendor_string,
        features,
        tlb,
        serial
    };

    cpuid_response & cpuid_request(cpuid_response &, cpuid_request_type);

  private:
    cpuid_response tmp;
};

#endif
