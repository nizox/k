#ifndef KERNEL_PRINT_H
#define KERNEL_PRINT_H

#include <stdarg.h>

void                putchar(char c);
void                print(const char *string);
void                puts(const char *string);
void                vprintk(const char *fmt, va_list ap);
void                printk(const char *fmt, ...);

#endif /* end of include guard: KERNEL_PRINT_H */
