#ifndef KERNEL_VIDEO_H
#define KERNEL_VIDEO_H

#include "std.h"
#include "ostream.h"

class video: public std::ostream
{
public:
    enum    colors
      {
        black = 0,
        blue,
        green,
        cyan,
        red,
        magenta,
        brown,
        lightgray,
        darkgray,
        brightblue,
        brightgreen,
        brightcyan,
        brightred,
        brightmagenta,
        brightyellow,
        white
      };

    video(colors fg = lightgray, colors bg = blue);
    ~video();

    void                set_fg(colors fg);
    void                set_bg(colors bg);
    void                set_cursor(colors fg, colors bg);

    colors              get_bg() const;
    colors              get_fg() const;

    void                printf(const char* fmt, ...) const;

    virtual video&      operator<<(const char* string);
    virtual video&      operator<<(char c);
    virtual video&      operator<<(int number);
    virtual video&      operator<<(unsigned int number);
    virtual video&      operator<<(const void* ptr);
    virtual video&      operator<<(std::termination);

private:
    colors              fg_;
    colors              bg_;

    static bool         initialized_;
};

#endif /* end of include guard: KERNEL_VIDEO_H */
