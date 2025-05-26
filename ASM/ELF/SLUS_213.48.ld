SECTIONS
{
    __romPos = 0;
    _gp = 0x15B4F0;
    elf_header_ROM_START = __romPos;
    elf_header_VRAM = ADDR(.elf_header);
    .elf_header : AT(elf_header_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        elf_header_DATA_START = .;
        build/asm/data/elf_header.s.o(.data);
        elf_header_DATA_END = .;
        elf_header_DATA_SIZE = ABSOLUTE(elf_header_DATA_END - elf_header_DATA_START);
    }
    __romPos += SIZEOF(.elf_header);
    elf_header_ROM_END = __romPos;
    elf_header_VRAM_END = .;

    main_ROM_START = __romPos;
    main_VRAM = ADDR(.main);
    .main 0x100000 : AT(main_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        main_TEXT_START = .;
        build/asm/sdk.s.o(.text);
        build/asm/text.s.o(.text);
        build/asm/init.s.o(.text);
        . = ALIGN(., 16);
        main_TEXT_END = .;
        main_TEXT_SIZE = ABSOLUTE(main_TEXT_END - main_TEXT_START);
        main_DATA_START = .;
        build/asm/data/data.data.s.o(.data);
        build/asm/sdk.s.o(.data);
        build/asm/text.s.o(.data);
        build/asm/init.s.o(.data);
        build/asm/data/sdata.data.s.o(.data);
        . = ALIGN(., 16);
        main_DATA_END = .;
        main_DATA_SIZE = ABSOLUTE(main_DATA_END - main_DATA_START);
        main_RODATA_START = .;
        build/asm/data/rodata.rodata.s.o(.rodata);
        build/asm/sdk.s.o(.rodata);
        build/asm/text.s.o(.rodata);
        build/asm/init.s.o(.rodata);
        build/asm/data/ctors.rodata.s.o(.rodata);
        build/asm/data/vtables.rodata.s.o(.rodata);
        build/asm/data/ovl_groups.rodata.s.o(.rodata);
        . = ALIGN(., 16);
        main_RODATA_END = .;
        main_RODATA_SIZE = ABSOLUTE(main_RODATA_END - main_RODATA_START);
    }
    main_bss_VRAM = ADDR(.main_bss);
    .main_bss (NOLOAD) : SUBALIGN(16)
    {
        FILL(0x00000000);
        main_BSS_START = .;
        build/asm/sdk.s.o(.bss);
        build/asm/text.s.o(.bss);
        build/asm/init.s.o(.bss);
        build/asm/data/sbss.bss.s.o(.bss);
        build/asm/data/bss.bss.s.o(.bss);
        . = ALIGN(., 16);
        main_BSS_END = .;
        main_BSS_SIZE = ABSOLUTE(main_BSS_END - main_BSS_START);
    }
    __romPos += SIZEOF(.main);
    __romPos = ALIGN(__romPos, 16);
    . = ALIGN(., 16);
    main_ROM_END = __romPos;
    main_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
