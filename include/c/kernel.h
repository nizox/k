#ifndef KERNEL_C_H_
#define KERNEL_C_H_

#ifdef __cplusplus
# define __C_BEGIN extern "C" {
# define __C_END }
#else
# define __C_BEGIN
# define __C_END
#endif

/* Branchless conditional negate. */
#define COND_NEGATE(cond, number) (number) = ((number) ^ -(cond)) + (cond)

/* Branchless conditional bit set/clear */
#define COND_SET_BIT(value, flag, mask)         \
do {                                            \
      (value) ^= (-(flag) ^ (value)) & (mask);    \
} while (0)

/* Check if a number is a power of two */
#define TWO_POWER(x) ((x) == 1 || !((x) & (x - 1)))

#endif /* end of include guard: KERNEL_C_H_ */
