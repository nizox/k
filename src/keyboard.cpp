#include "ioapic.h"
#include "keyboard.h"
#include "isr.h"
#include "exceptions.h"
#include "video.h"

keyboard *_keyboard;
char keymap[] = {0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0x0e, 0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0x1c, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 0, '`', 0, 0, 'z', 'x'    , 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 0, 0, ' ', 0};

EXC_FUNC(exc_keyboard, 33)(struct exception_frame *frame)
{
    _keyboard->interrupt();
}

keyboard::keyboard(ioapic & ioapic, task::scheduler & sched):
    _ioapic(ioapic), _sched(sched)
{
}

keyboard::~keyboard()
{
}

void
keyboard::interrupt()
{
    _sched.post([&] () -> int {
        this->handle_key();
        return 0;
    });
    _ioapic.get_cpu_for_irq(0).get_local_apic().send_eoi();
}

void
keyboard::handle_key()
{
    uint8_t data;
    char key;
    video screen;

    while (is_buffer_ready())
    {
        data = read_data();
        if (data < 0x80) /* Keypress */
        {
            key = keymap[data];
            if (key)
                screen << key;
            else
                screen << std::endl << (int)data;
        }
    }
}

uint8_t
keyboard::read_data()
{
    char data;

    __asm__ ("inb $0x60, %0" : "=a"(data));
    return data;
}

bool
keyboard::is_buffer_ready()
{
    char status;

    __asm__ ("inb $0x64, %0" : "=a"(status));
    return status & 0x1;
}

void
keyboard::setup()
{
    _isr.set_interrupt_gate(33, &exc_keyboard);
    _ioapic.default_redirect_irq(0, 33);
}
