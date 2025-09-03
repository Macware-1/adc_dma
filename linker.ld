MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
    SRAM  (xrw) : ORIGIN = 0x20000000, LENGTH = 32K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
    /* Vector table and .text into FLASH */
    .vector_table :
    {
        KEEP(*(.vector_table))
    } > FLASH

    .text :
    {
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        _etext = .;
    } > FLASH

    /* .data section: load from FLASH to RAM */
    .data : AT(_etext)
    {
        _sdata = .;
        *(.data)
        *(.data*)
        _edata = .;
    } > SRAM

    /* .bss section: zero-initialized in RAM */
    .bss :
    {
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM

}
