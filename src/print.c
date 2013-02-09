#include "screen.h"
#include "print.h"

void                print(const char *string)
{
    for (; *string != 0; ++string)
        putchar(*string);
}

void                puts(const char *string)
{
    print(string);
    putchar('\n');
}

void                swrite(const char *str, unsigned int n)
{
    while (n--)
        putchar(*(str++));
}
