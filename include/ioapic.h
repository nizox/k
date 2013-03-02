#ifndef IOAPIC_H
#define IOAPIC_H

#include "c/types.h"
#include "c/memory.h"
#include "cpu.h"

class ioapic;

class ioapic_redirect_entry
{
  public:
    typedef uint32_t register_t;
    enum destination_mode
    {
        physical = 0,
        logical  = 1
    };

    void mask()
    {
        value.e.mask = 1;
    }
    void unmask()
    {
        value.e.mask = 0;
    }

    void set_vector(int vector)
    {
        value.e.vector = vector;
    }

    void set_physical_destination(int apic_id)
    {
        value.e.destination_mode = physical;
        value.e.destination = apic_id;
    }

    void commit();

  private:
    ioapic_redirect_entry(ioapic &, int);
    ~ioapic_redirect_entry();

    int _index;
    ioapic & _ioapic;
    union
    {
        struct __attribute__((packed))
        {
            uint64_t vector             : 8; /* ranges from 0x10 to 0xFE */
            uint64_t delivery_mode      : 3; /* Set to 0 for fixed mode now */
            uint64_t destination_mode   : 1; /* 0 physical mode, 1 logical */
            uint64_t delivery_status    : 1; /* 0 idle, 1 send pending */
            uint64_t pin_polarity       : 1; /* 0 high active, 1 low active */
            uint64_t remote_irr         : 1; /* for level triggering */
            uint64_t trigger_mode       : 1; /* 1 level sensitive, 0 edge */
            uint64_t mask               : 1; /* 1 masked, 0 non masked */
            uint64_t reserved           : 39;
            uint64_t destination        : 8; /* APIC ID if physical mode */
        } e;
        register_t raw[2];
    } value;

    friend class ioapic;
};


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
    union version_register
    {
        struct __attribute__((packed))
        {
            uint64_t version            : 8;
            uint64_t reserved0          : 8;
            uint64_t max_redirect_entry : 8;
            uint64_t reserved1          : 8;
        } r;
        register_t raw;
    };

    ioapic(cpu & default_cpu, register_t * base_addr = (register_t *) IOAPIC_ADDR);
    ~ioapic();

    cpu & get_cpu_for_irq(uint32_t irq);
    void default_redirect_irq(uint32_t irq, uint32_t int_vector);

    void setup();

  private:
    uint64_t get_max_redirect_entry() const;
    ioapic_redirect_entry get_redirect_entry(int index);

    inline register_t get(uint32_t index) const
    {
        *base_register_addr = index;
        return *(base_register_addr + 4);
    }

    inline void set(uint32_t index, register_t value)
    {
        *base_register_addr = index;
        *(base_register_addr + 4) = value;
    }

    register_t * base_register_addr;
    cpu & main_cpu;

    friend class ioapic_redirect_entry;
};

#endif
