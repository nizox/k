#include "screen.h"
#include "string.h"
#include "print.h"

void                putchar(char c)
{
    screen_write(&c, 1);
}

void                print(const char *string)
{
    screen_write(string, strlen(string));
}

void                puts(const char *string)
{
    print(string);
    putchar('\n');
}
