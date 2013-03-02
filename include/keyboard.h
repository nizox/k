#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "ioapic.h"
#include "scheduler.h"

class keyboard
{
  public:
    keyboard(ioapic & ioapic, task::scheduler & sched);
    ~keyboard();

    void setup();
    void interrupt();
    void handle_key();

  private:
    uint8_t read_data();
    bool is_buffer_ready();

    ioapic & _ioapic;
    task::scheduler & _sched;
};

extern keyboard *_keyboard;

#endif
