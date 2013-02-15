#include "video.h"

video::attribute::attribute(colors fg, colors bg)
    : fg_(fg), bg_(bg)
{}

video::attribute::attribute(const attribute& src)
{
    if (&src != this)
      {
        this->fg_ = src.fg_;
        this->bg_ = src.bg_;
      }
}

video::attribute::~attribute()
{}

void                video::attribute::set(colors fg, colors bg)
{
    this->set_fg(fg);
    this->set_bg(bg);
}

void                video::attribute::set_fg(colors fg)
{
    fg_ = fg;
}

void                video::attribute::set_bg(colors bg)
{
    bg_ = bg;
}

video::colors       video::attribute::get_fg() const
{
    return fg_;
}

video::colors       video::attribute::get_bg() const
{
    return bg_;
}
