#include "c/memory.h"
 
void    _cppstart();

/*
 * Trick made because for an unknown reason, the bootloader
 * is unable to jump to an unmangled C++ function.
 * Used to commit stack relocation anyway.
 */
void _start()
{
    relocate_stack(STACKBASE);
    _cppstart();
}
