#ifndef KERNEL_C_STRING_H_
#define KERNEL_C_STRING_H_

#include "c/kernel.h"
#include "c/types.h"

__C_BEGIN

#define SIGN        1
#define PREFIX      2
#define SMALL       32  /* Must be this valie, no other else */

#define LOWER(c) ((c) | SMALL)
#define UPPER(c) ((c) & (~SMALL))

#define XOR_SWAP(x, y)      \
do {                        \
      x ^= y;               \
      y ^= x;               \
      x ^= y;               \
} while (0)

char* number(uintptr_t num, char *buf, int base, uint8_t flags);
char* itoa(int num, char *buf, int radix);
long int strtol(const char *ptr, char **endptr, int base);
size_t strlen(const char *str);
void* memset(void *s, int c, size_t n);
void* memcpy(void *dest, const void *src, size_t n);
void* memmove(void *dest, const void *src, size_t n);
char* strcpy(char *dest, const char *src);
char* strncpy(char *dest, const char *src, size_t n);
char* strcat(char *dest, const char *src);
char* strncat(char *dest, const char *src, size_t n);
char* strrev(char *begin, char *end);
int memcmp(const void *m1, const void *m2, size_t n);
char *strchr(const char *s, int c);
int strcmp(const char *s1, const char *s2);
char *strpbrk(const char *s, const char *accept);
int floor(float x);
double pow(double x, double y);

__C_END

#endif /* end of include guard: KERNEL_C_STRING_H_ */
