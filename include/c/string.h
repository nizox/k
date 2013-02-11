#ifndef KERNEL_STRING_H_
#define KERNEL_STRING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

/* Branchless conditional negate. */
#define COND_NEGATE(cond, number) (number) = ((number) ^ -(!cond)) + (!cond)

typedef struct
{
    const char      *base_table;
    const char      *prefix;
    size_t    prefix_len;
}                   base_data;

#define MAKE_BASE_TABLE(name, radix, prefix)   \
static const base_data  base##name = {(radix), (prefix), sizeof(prefix) - 1}

char                *itoa(int nbr, char *buf, int base);
long int            strtol(const char *ptr, char **endptr, int base);
size_t              strlen(const char *str);
void                *memset(void *s, int c, size_t n);
void                *memcpy(void *dest, const void *src, size_t n);
char                *strcpy(char *dest, const char *src);
char                *strncpy(char *dest, const char *src, size_t n);
char                *strcat(char *dest, const char *src);
char                *strncat(char *dest, const char *src, size_t n);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: KERNEL_STRING_H_ */
