ENTRY(_start)
SECTIONS {
    . = 1M;
    .multiboot : { KEEP(*(.multiboot)) }
    .text : { *(.text*) }
    .rodata : { *(.rodata*) }
    . = ALIGN(4096);
    .data : { *(.data*) }
    .bss : { *(COMMON) *(.bss*) }
}
