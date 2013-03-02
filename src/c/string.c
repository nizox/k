#include "c/string.h"

static const char       digits[16] = "0123456789ABCDEF";

char*
number(uintptr_t num, char *buf, int base, uint8_t flags)
{
    ssize_t             i = 0;
    char                locase = (flags & SMALL);
    uint8_t             isneg = (intptr_t)num < 0 && (flags & SIGN) != 0;

    if (num == 0)
        buf[i++] = '0';
    else
      {
        COND_SET_BIT(flags, isneg, SIGN);
        COND_NEGATE(isneg, num);
        while (num)
          {
            buf[i++] = digits[num % base] | locase;
            num /= base;
          }
        if (flags & PREFIX && (base & (8 | 16)))
          {
            if (base & 16)
                buf[i++] = 'X' | locase;
            buf[i++] = '0';
          }
        if (flags & SIGN)
            buf[i++] = '-';
      }

    buf[i] = 0;
    strrev(buf, buf + i - 1);

    return buf;
}

char*
itoa(int num, char *buf, int radix)
{
    return number(num, buf, radix, SIGN);
}

int
in_base(char c)
{
    size_t              i;

    for (i = 0; i < 16; ++i)
        if (c == digits[i])
            return i;
    return -1;
}

long int
strtol(const char *ptr, char **endptr, int base)
{
    int             isneg = 0;
    long int        number = 0;
    int             val;

    for (; *ptr != 0; ++ptr)
      {
        switch (*ptr)
          {
            case '+':
                break;
            case '-':
                isneg = 1;
                break;
            default:
                val = in_base(*ptr);
                if (val == -1)
                    goto end;
                number = number * base - val;
                break;
          }
      }

end:
    COND_NEGATE(!isneg, number);

    if (endptr != 0)
        *endptr = (char *)ptr;
    return number;
}

size_t
strlen(const char *str)
{
    const char      *endptr;

    for (endptr = str; *endptr; ++endptr)
        ;
    return endptr - str;
}

void*
memset(void *s, int c, size_t n)
{
    char            *ptr = (char *)s;

    for (; (size_t)(ptr - (char *)s) < n; ++ptr)
        *ptr = (char)c;

    return s;
}

void*
memcpy(void *dest, const void *src, size_t n)
{
    char            *cdest = (char *)dest;
    const char      *csrc = (char *)src;

    for (; n; --n, ++cdest, ++csrc)
        *cdest = *csrc;

    return dest;
}
void*
memmove(void *dest, const void *src, size_t n)
{
    return memcpy(dest, src, n);
}

char*
strcpy(char *dest, const char *src)
{
    char            *save = dest;

    while (*src)
      {
        *dest = *src;
        ++src;
        ++dest;
      }
    return save;
}

char*
strncpy(char *dest, const char *src, size_t n)
{
    char            *save = dest;

    while (*src && n)
      {
        *dest = *src;
        ++src;
        ++dest;
        --n;
      }
    return save;
}

char*
strcat(char *dest, const char *src)
{
    int             i = 0;
    int             j = 0;

    while (dest[i])
        ++i;
    while (src[j])
      {
        dest[i] = src[j];
        ++i;
        ++j;
      }
    dest[i] = 0;
    return dest;
}

char*
strncat(char *dest, const char *src, size_t n)
{
    int             i = 0;
    int             j = 0;

    while (dest[i])
        ++i;
    while (src[j] && n)
      {
        dest[i] = src[j];
        ++i;
        ++j;
        --n;
      }
    dest[i] = 0;
    return dest;
}

char*
strrev(char *begin, char *end)
{
    char    *save = begin;

    for (; begin < end; ++begin, --end)
        XOR_SWAP(*begin, *end);
    return save;
}
