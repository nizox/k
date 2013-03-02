#ifndef APIC_H
#define APIC_H

#include "c/types.h"
#include "c/memory.h"

class local_apic
{
  public:
    /* The local APIC is mapped in a memory space dedicated to its processor.
     * Every access must be 32 bits aligned */
    typedef uint32_t register_t;
    enum register_index_t
    {
        id                          = 0x020,
        id_version                  = 0x030,
        task_priority               = 0x080,
        arbitration_priority        = 0x090,
        processor_priority          = 0x0A0,
        eoi                         = 0x0B0,
        logical_destination         = 0x0D0,
        destination_format          = 0x0E0,
        spurious_interrupt_vector   = 0x0F0,
        interrupt_status            = 0x100,
        trigger_mode                = 0x180,
        interrupt_request           = 0x200,
        error_status                = 0x280,
        interrupt_command0          = 0x300,
        interrupt_command1          = 0x310,
        lvt_timer                   = 0x320,
        perf_counter_lvt            = 0x340,
        lvt_lint0                   = 0x350,
        lvt_lint1                   = 0x360,
        lvt_error                   = 0x370,
        timer_initial_count         = 0x380,
        timer_current_count         = 0x390,
        timer_divide_configuration  = 0x3E0,
    };

    local_apic(register_t * base_addr = (register_t *) LOCAL_APIC_ADDR);
    ~local_apic();

    int get_id();
    void send_eoi(register_t value = 0x0);
    void setup();
    void enable();

  private:
    /* We must avoid pointer arythmetic here */
    inline register_t get(register_index_t index) const
    {
        return *(base_register_addr + index / sizeof(*base_register_addr));
    }

    inline void set(register_index_t index, register_t value)
    {
        *(base_register_addr + index / sizeof(*base_register_addr)) = value;
    }

    inline void set_bit(register_index_t index, uint32_t mask)
    {
        *(base_register_addr + index / sizeof(*base_register_addr)) |= mask;
    }

    inline void unset_bit(register_index_t index, uint32_t mask)
    {
        *(base_register_addr + index / sizeof(*base_register_addr)) &= ~mask;
    }


    register_t * base_register_addr;
};

#endif
