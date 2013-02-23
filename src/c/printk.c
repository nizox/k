#include <stdarg.h>

#include "c/string.h"
#include "c/screen.h"
#include "c/print.h"

void                vprintk(const char *fmt, va_list ap)
{
    char            buf[66];
    char            *str;
    int             flags;

    for (; *fmt; ++fmt)
      {
        if (*fmt == '%')
          {
            flags = 0;
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
                    flags |= SIGN;
                case 'u':
                    print(number((int)va_arg(ap, uintptr_t), buf, 10, flags));
                    break;
                case 'x':
                    flags |= SIGN;
                case 'p':
                    print(number((int)va_arg(ap, uintptr_t), buf, 16, PREFIX | SMALL | flags));
                    break;
                case 'o':
                    print(number((int)va_arg(ap, uintptr_t), buf, 8, PREFIX | SMALL));
                    break;
                case 'b':
                    print(number((int)va_arg(ap, uintptr_t), buf, 2, 0));
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
