#include "string.h"

static const char   *base2 = "01";
static const char   *base3 = "012";
static const char   *base4 = "0123";
static const char   *base8 = "01234567";
static const char   *base10 = "0123456789";
static const char   *base16 = "0123456789abcdef";

static const char   *choose_table(int base)
{
    const char      *base_table;

    switch (base)
      {
        case 2:
            base_table = base2;
            break;
        case 3:
            base_table = base2;
            break;
        case 4:
            base_table = base2;
            break;
        case 8:
            base_table = base8;
            break;
        case 10:
            base_table = base10;
            break;
        case 16:
            base_table = base16;
            break;
        default:
            base_table = base10;
            break;
      }
    return base_table;
}

static int          in_base(char c, const char *base_table)
{
    int             pos;

    for (pos = 0; base_table[pos] != 0; ++pos)
      {
        if (base_table[pos] == c)
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

/*
 * Handles 2, 8, 16 and 32 radices
 *
 * Buffer sizes corresponding to radix:
 * 2 -> 33
 * 8 -> 13
 * 10 -> 12
 * 16 -> 10
 */
char                *itoa(int nbr, char *buf, int radix)
{
    int             i = 0;
    int             mult;
    int             power = max_power(nbr, radix);
    const char      *base_table = choose_table(radix);

    if (nbr == 0)
      {
        buf[0] = base_table[0];
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

        while (power != 0)
          {
            mult = nbr / power;
            buf[i] = base_table[-mult];
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
    const char      *base_table = choose_table(base);
    int             isneg = 1;
    long int        number = 0;
    int             val;

    for (; *ptr != 0; ++ptr)
      {
        switch (*ptr)
          {
            case '+':
                break;
            case '-':
                isneg = 0;
                break;
            default:
                val = in_base(*ptr, base_table);
                if (val == -1)
                  break;
                number = number * base - val;
          }
      }

    COND_NEGATE(isneg, number);

    if (endptr != 0)
        *endptr = (char *)ptr;
    return number;
}

unsigned int        strlen(const char *str)
{
    const char      *endptr;

    for (endptr = str; *endptr; ++endptr)
        ;
    return endptr - str;
}

void                *memset(void *s, int c, unsigned int n)
{
    char            *ptr = s;

    for (; ptr - (char *)s < n; ++ptr)
        *ptr = (char)c;

    return s;
}

void                *memcpy(void *dest, const void *src, unsigned int n)
{
    char            *cdest = dest;
    const char      *csrc = src;

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

char                *strncpy(char *dest, const char *src, unsigned int n)
{
    return memcpy(dest, src, n);
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

char                *strncat(char *dest, const char *src, unsigned int n)
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
