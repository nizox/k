#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "ioapic.h"

char keymap[] = {0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0x0e, 0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0x1c, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 0, '`', 0, 0, 'z', 'x'    , 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 0, 0, ' ', 0};

class keyboard
{
  public:
    keyboard(ioapic & ioapic);
    ~keyboard();

    void setup();
    void interrupt();
    void handle_key();

  private:
    uint8_t read_data();
    bool is_buffer_ready();

    ioapic & _ioapic;
};

extern keyboard *_keyboard;

#endif
