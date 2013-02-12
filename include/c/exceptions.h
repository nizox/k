#ifndef C_EXCEPTIONS_H
#define C_EXCEPTIONS_H

#include "c/interrupts.h"

#ifdef __cplusplus
export "C" {
#endif

extern void exc_gp(void);

#ifdef __cplusplus
}
#endif

#endif
