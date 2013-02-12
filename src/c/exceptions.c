#include "c/interrupts.h"
#include "c/exceptions.h"
#include "c/screen.h"

EXC_ERRFUNC(exc_gp, 13)(struct exception_frame * regs)
{
    print ("Exception GP");
}
