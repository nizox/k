#include "c/memory.h"
#include "c/types.h"

void    _cppstart();

void
_start()
{
    /*
     * Relocate the stack at the end of the last page inside the available memory
     * and jump to the main function to clear stack context.
     */
    relocate_stack(AVAILABLE_MEMORY  MEGABYTES);
    _cppstart();
}
