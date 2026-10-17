/*
 * JajaOS Linker Script
 * GPL-3.0-only
 */
ENTRY(_start)
SECTIONS
{
    . = 1M; /* 内核加载到 0x100000 1MB位置 */
    .text ALIGN(4K) :
    {
        *(.boot)
        *(.text)
    }
    .rodata ALIGN(4K) : { *(.rodata) }
    .data ALIGN(4K) : { *(.data) }
    .bss ALIGN(4K) :
    {
        __bss_start = .;
        *(COMMON)
        *(.bss)
        __bss_end = .;
    }
}
