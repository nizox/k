#include "c/memory.h"
#include "c/types.h"

void    _cppstart();

/*
 * Trick made because for an unknown reason, the bootloader
 * is unable to jump to an unmangled C++ function.
 * Used to commit stack relocation anyway.
 */
void _start()
{
    /*
     * Relocate the stack at the end of the last page inside the available memory.
     */
    relocate_stack(AVAILABLE_MEMORY * MEGABYTE);
    _cppstart();
}
