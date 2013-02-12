ENTRY(_start)
SECTIONS
{
    /* The kernel code is mapped at 0x100000
     * Static data is appended */
    .text 0x100000:
    {
        code = .;
        *(.text)
    }
    .data :
    {
        data = .;
        *(.data)
        *(.rodata)
    }
    .bss :
    {
        bss = .;
        *(.bss)
    }
}
