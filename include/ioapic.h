#ifndef IOAPIC_H
#define IOAPIC_H

#include "c/types.h"
#include "c/memory.h"
#include "cpu.h"

class ioapic
{
  public:
    typedef uint32_t register_t;
    enum register_index_t
    {
        id                  = 0x00,
        version             = 0x01,
        arbitration_id      = 0x02,
        redirect_table      = 0x10,
    };

    union redirect_entry
    {
        struct
        {
            uint64_t vector             : 8;
            uint64_t delivery_mode      : 3;
            uint64_t destination_mode   : 1;
            uint64_t delivery_status    : 1;
            uint64_t pin_polarity       : 1;
            uint64_t remote_irr         : 1;
            uint64_t trigger_mode       : 1;
            uint64_t mask               : 1;
            uint64_t reserved           : 39;
            uint64_t destination        : 8;
        } e;
        register_t raw[2];
    };

    union version_register
    {
        struct
        {
            uint64_t version            : 8;
            uint64_t reserved0          : 8;
            uint64_t max_redirect_entry : 8;
            uint64_t reserved1          : 8;
        } r;
        register_t raw;
    };

    ioapic(register_t * base_addr);
    ~ioapic();

    void set_default_cpu(cpu * cpu);
    uint64_t get_max_redirect_entry() const;
    void setup();

  private:
    inline register_t get(register_index_t index) const
    {
        *base_register_addr = index;
        return *(base_register_addr + 4);
    }

    inline void set(register_index_t index, register_t value)
    {
        *base_register_addr = index;
        *(base_register_addr + 4) = value;
    }

    register_t * base_register_addr;
    cpu * default_cpu;
};

#endif
