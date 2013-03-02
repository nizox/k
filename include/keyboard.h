#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "ioapic.h"

class keyboard
{
  public:
    keyboard(ioapic & ioapic);
    ~keyboard();

    void setup();

  private:
    ioapic & _ioapic;
};

#endif
