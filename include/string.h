#ifndef KERNEL_STRING_H_
#define KERNEL_STRING_H_

/* Branchless conditional negate. */
#define COND_NEGATE(cond, number) (number) = ((number) ^ -(!cond)) + (!cond)

typedef struct
{
    const char      *base_table;
    const char      *prefix;
    unsigned int    prefix_len;
}                   base_data;

#define MAKE_BASE_TABLE(name, radix, prefix)   \
static const base_data  base##name = {(radix), (prefix), sizeof(prefix) - 1}

char                *itoa(int nbr, char *buf, int base);
long int            strtol(const char *ptr, char **endptr, int base);
unsigned int        strlen(const char *str);
void                *memset(void *s, int c, unsigned int n);
void                *memcpy(void *dest, const void *src, unsigned int n);
char                *strcpy(char *dest, const char *src);
char                *strncpy(char *dest, const char *src, unsigned int n);
char                *strcat(char *dest, const char *src);
char                *strncat(char *dest, const char *src, unsigned int n);

#endif /* end of include guard: KERNEL_STRING_H_ */
