#ifndef KERNEL_C_PRINT_H
#define KERNEL_C_PRINT_H

#include "c/kernel.h"

__C_BEGIN

#include <stdarg.h>

void                putchar(char c);
void                print(const char *string);
void                puts(const char *string);
void                vprintk(const char *fmt, va_list ap);
void                printk(const char *fmt, ...);

__C_END

#endif /* end of include guard: KERNEL_C_PRINT_H */
