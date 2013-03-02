#include "keyboard.h"
#include "isr.h"
#include "exceptions.h"
#include "video.h"
#include "std.h"


EXC_FUNC(exc_keyboard, 33)(struct exception_frame *frame)
{
    video() << "KEY" << std::endl;
}

keyboard::keyboard(ioapic & ioapic): _ioapic(ioapic)
{
}

keyboard::~keyboard()
{
}

void keyboard::setup()
{
    _isr.set_interrupt_gate(33, &exc_keyboard);
    _ioapic.default_redirect_irq(0, 33);
}
