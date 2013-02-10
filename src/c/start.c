void    _cppstart();

/*
 * Trick made because for an unknown reason, the bootloader
 * is unable to jump to an unmangled C++ function.
 */
void _start()
{
    _cppstart();
}
