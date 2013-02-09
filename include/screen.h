#ifndef KERNEL_SCREEN_H_
#define KERNEL_SCREEN_H_

typedef enum
{
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    BRIGHTBLUE,
    BRIGHTGREEN,
    BRIGHTCYAN,
    BRIGHTRED,
    BRIGHTMAGENTA,
    BRIGHTYELLOW,
    WHITE
}   EGA_COLORS;

typedef struct
{
    unsigned short  x;
    unsigned short  y;
}                   cursor;

void                screen_clear(void);
void                putchar(char c);
void                set_bg_color(EGA_COLORS color);
void                set_fg_color(EGA_COLORS color);
void                screen_init(EGA_COLORS bg, EGA_COLORS fg);
void                screen_init_default(void);

#endif /* end of include guard: KERNEL_SCREEN_H_ */
