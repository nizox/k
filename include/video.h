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

    enum    level
      {
        normal,
        warning,
        error,
        ok
      };

    enum    status
      {
        printok,
        printwarning,
        printerror
      };

    static const colors DEFAULT_FG = lightgray;
    static const colors DEFAULT_BG = blue;

    class attribute
      {
    public:

        attribute(colors fg=DEFAULT_FG, colors bg=DEFAULT_BG);
        attribute(const attribute& src);
        ~attribute();

        void            set(colors fg, colors bg);
        void            set_fg(colors fg);
        void            set_bg(colors bg);

        colors          get_fg() const;
        colors          get_bg() const;

    private:

        colors          fg_;
        colors          bg_;
      };

    video(colors fg = lightgray, colors bg = blue);
    video(const attribute& attr);
    ~video();

    void                set_fg(colors fg);
    void                set_bg(colors bg);
    void                set_attr(colors fg, colors bg);
    void                set_attr(const attribute& attr);

    attribute           save_attr() const;
    colors              get_fg() const;
    colors              get_bg() const;

    void                printf(const char* fmt, ...) const;

    virtual video&      operator<<(const char* string);
    virtual video&      operator<<(char c);
    virtual video&      operator<<(int number);
    virtual video&      operator<<(unsigned int number);
    virtual video&      operator<<(const void* ptr);
    virtual video&      operator<<(std::termination);
    video&              operator<<(level lvl);
    video&              operator<<(status st);

private:
    attribute           attr_;
    attribute           save_;

    static bool         initialized_;
};

#endif /* end of include guard: KERNEL_VIDEO_H */
