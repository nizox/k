#ifndef KERNEL_PRINT_H
#define KERNEL_PRINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

void                putchar(char c);
void                print(const char *string);
void                puts(const char *string);
void                vprintk(const char *fmt, va_list ap);
void                printk(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: KERNEL_PRINT_H */
