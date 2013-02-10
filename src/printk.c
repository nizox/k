#include <stdarg.h>
#include "string.h"
#include "screen.h"
#include "print.h"

void                vprintk(const char *fmt, va_list ap)
{
    char            buf[34];
    char            *str;

    for (; *fmt; ++fmt)
      {
        if (*fmt == '%')
          {
            switch (*(++fmt))
              {
                case 'c':
                    putchar((char)va_arg(ap, int));
                    break;
                case 's':
                    print((const char *)va_arg(ap, const char *));
                    break;
                case 'i':
                case 'd':
                    print(itoa((int)va_arg(ap, int), buf, 10));
                    break;
                case 'p':
                case 'x':
                    print(itoa((int)va_arg(ap, int), buf, 16));
                    break;
                case 'o':
                    print(itoa((int)va_arg(ap, int), buf, 8));
                    break;
                case 'b':
                    print(itoa((int)va_arg(ap, int), buf, 2));
                    break;
                case '%':
                    putchar(*fmt);
                    break;
                default:
                    putchar('%');
                    break;
              }
          }
        else
            putchar(*fmt);
      }
}

void                printk(const char *fmt, ...)
{
    va_list         ap;

    va_start(ap, fmt);
    vprintk(fmt, ap);
    va_end(ap);
}
