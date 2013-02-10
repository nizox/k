#include <stdarg.h>
 
#include "video.h"
#include "c/screen.h"
#include "c/print.h"

video::video(colors fg, colors bg)
    : fg_(fg), bg_(bg)
{
    ::screen_init(static_cast<EGA_COLORS>(bg_), static_cast<EGA_COLORS>(fg_));
}

video::~video()
{}

void                video::set_fg(colors fg)
{
    fg_ = fg;
    ::set_fg_color(static_cast<EGA_COLORS>(fg_));
}

void                video::set_bg(colors bg)
{
    bg_ = bg;
    ::set_bg_color(static_cast<EGA_COLORS>(bg_));
}

void                video::set_cursor(colors fg, colors bg)
{
    set_fg(fg);
    set_bg(bg);
}

video::colors      video::get_fg() const
{
    return fg_;
}

video::colors      video::get_bg() const
{
    return bg_;
}

void                video::printf(const char* fmt, ...) const
{
    va_list         ap;

    va_start(ap, fmt);
    ::vprintk(fmt, ap);
    va_end(ap);
}

video&             video::operator<<(const char* string)
{
    ::print(string);
    return *this;
}

video&              video::operator<<(char c)
{
    ::putchar(c);
    return *this;
}

video&              video::operator<<(int number)
{
    ::printk("%d", number);
    return *this;
}

video&              video::operator<<(unsigned int number)
{
    return this->operator<<(static_cast<int>(number));
}

video&              video::operator<<(const void* ptr)
{
    ::printk("%x", ptr);
    return *this;
}

video&             video::operator<<(std::termination)
{
    ::putchar('\n');
    return *this;
}
