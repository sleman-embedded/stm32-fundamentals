SECTIONS
{
    .text 0x08000000 :
    {
        KEEP(*(.vectors))
        *(.text*)
        *(.rodata*)
        *(.data*)
    }
}