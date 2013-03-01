#include "c/screen.h"
#include "c/memory.h"

static cursor point;
static char vga_attr;

static void         scroll(unsigned int n)
{
    unsigned char   *video;
    unsigned char   *tmp;

    for (video = (unsigned char*) SCREEN_START;
         video < (unsigned char*) SCREEN_END;
         video += 2)
      {
        tmp = (unsigned char*) (video + n * SCREEN_COLUMNS);

        if (tmp < (unsigned char*) SCREEN_END)
          {
            *video = *tmp;
            *(video + 1) = *(tmp + 1);
          }
        else
          {
            *video = 0;
            *(video + 1) = 0;
          }
      }

    point.y -= n;
    if (point.y < 0)
        point.y = 0;
}

void                screen_clear(void)
{
    unsigned char   *video;

    for (video = (unsigned char*) SCREEN_START;
         video < (unsigned char*) SCREEN_END;
         ++video)
      {
        *video = 0;
      }

    point.x = 0;
    point.y = 0;
}

static void         screen_write_char(char c)
{
    unsigned char   *video;

    switch (c)
      {
        case '\n':
            point.x = 0;
            ++point.y;
            break;
        case '\t':
            point.x = point.x + 8 - (point.x % 8);
            break;
        case '\r':
            point.x = 0;
        default:
            video = (unsigned char*) ((unsigned char*)SCREEN_START + 1 * point.x + SCREEN_COLUMNS * point.y);
            *video = c;
            *(video + 1) = vga_attr;
            point.x += 2;
            if (point.x > 79)
              {
                point.x = 0;
                point.y++;
              }
            break;
      }
    if (point.y > SCREEN_LINES)
        scroll(point.y - SCREEN_LINES);
}

void                 screen_write(const char *ptr, unsigned int size)
{
    for (; size > 0; --size, ++ptr)
        screen_write_char(*ptr);
}

void                set_bg_color(EGA_COLORS color)
{
    vga_attr = (color << 4) | (vga_attr & 15);
}

void                set_fg_color(EGA_COLORS color)
{
    /* Taking account of black (0x0) */
    vga_attr = (vga_attr >> 4) << 4 | color;
}

void                screen_init(EGA_COLORS bg, EGA_COLORS fg)
{
    screen_clear();
    set_bg_color(bg);
    set_fg_color(fg);
}

void                screen_init_default(void)
{
    screen_init(BLUE, LIGHTGRAY);
}
