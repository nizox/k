#ifndef KERNEL_STRING_H_
#define KERNEL_STRING_H_

/* Branchless conditional negate. */
#define COND_NEGATE(cond, number) (number) = ((number) ^ -(!cond)) + (!cond)

char                *itoa(int nbr, char *buf, int base);
long int            strtol(const char *ptr, char **endptr, int base);
unsigned int        strlen(const char *str);
void                *memset(void *s, int c, unsigned int n);
void                *memcpy(void *dest, const void *src, unsigned int n);
char                *strcpy(char *dest, const char *src);
char                *strncpy(char *dest, const char *src, unsigned int n);
char                *strcat(char *dest, const char *src);

#endif /* end of include guard: KERNEL_STRING_H_ */
