#include "c/string.h"

MAKE_BASE_TABLE(2, "01", "b");
MAKE_BASE_TABLE(3, "012", "");
MAKE_BASE_TABLE(4, "0123", "");
MAKE_BASE_TABLE(8, "01234567", "0");
MAKE_BASE_TABLE(10, "0123456789", "");
MAKE_BASE_TABLE(16, "0123456789abcdef", "0x");

static const base_data   *choose_table(int base)
{
    switch (base)
      {
        case 2:
            return &base2;
        case 3:
            return &base3;
        case 4:
            return &base4;
        case 8:
            return &base8;
        case 16:
            return &base16;
        case 10:
        default:
            return &base10;
      }
}

static int          in_base(char c, const base_data *bd)
{
    int             pos;

    for (pos = 0; bd->base_table[pos] != 0; ++pos)
      {
        if (bd->base_table[pos] == c)
            return pos;
      }
    return -1;
}

static int          max_power(int nbr, int base)
{
    int             power = 1;

    for (power = 1; (nbr /= base); power *= base)
        ;
    return power;
}

char                *itoa(int nbr, char *buf, int radix)
{
    int             i = 0;
    int             mult;
    int             power = max_power(nbr, radix);
    const base_data *bd = choose_table(radix);

    if (nbr == 0)
      {
        strncpy(buf, bd->prefix, bd->prefix_len);
        i += bd->prefix_len;
        buf[i] = bd->base_table[0];
        ++i;
      }
    else
      {
        if (nbr < 0)
          {
            buf[i] = '-';
            ++i;
          }
        else
            nbr = -nbr;

        strncpy(buf + i, bd->prefix, bd->prefix_len);
        i += bd->prefix_len;
        while (power != 0)
          {
            mult = nbr / power;
            buf[i] = bd->base_table[-mult];
            nbr %= power;
            power /= radix;
            ++i;
          }
      }

    buf[i] = 0;
    return buf;
}

long int            strtol(const char *ptr, char **endptr, int base)
{
    const base_data *bd = choose_table(base);
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
                val = in_base(*ptr, bd);
                if (val == -1)
                    goto end;
                number = number * base - val;
                break;
          }
      }

end:
    COND_NEGATE(isneg, number);

    if (endptr != 0)
        *endptr = (char *)ptr;
    return number;
}

size_t              strlen(const char *str)
{
    const char      *endptr;

    for (endptr = str; *endptr; ++endptr)
        ;
    return endptr - str;
}

void                *memset(void *s, int c, size_t n)
{
    char            *ptr = (char *)s;

    for (; (size_t)(ptr - (char *)s) < n; ++ptr)
        *ptr = (char)c;

    return s;
}

void                *memcpy(void *dest, const void *src, size_t n)
{
    char            *cdest = (char *)dest;
    const char      *csrc = (char *)src;

    for (; n; --n, ++cdest, ++csrc)
        *cdest = *csrc;

    return dest;
}

char                *strcpy(char *dest, const char *src)
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

char                *strncpy(char *dest, const char *src, size_t n)
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

char                *strcat(char *dest, const char *src)
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

char                *strncat(char *dest, const char *src, size_t n)
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
