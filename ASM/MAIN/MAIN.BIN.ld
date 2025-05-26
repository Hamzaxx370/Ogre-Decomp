SECTIONS
{
    __romPos = 0;
    ovl_header_ROM_START = __romPos;
    ovl_header_VRAM = ADDR(.ovl_header);
    .ovl_header : AT(ovl_header_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        ovl_header_DATA_START = .;
        build/asm/main/data/ovl_header.s.o(.data);
        ovl_header_DATA_END = .;
        ovl_header_DATA_SIZE = ABSOLUTE(ovl_header_DATA_END - ovl_header_DATA_START);
    }
    __romPos += SIZEOF(.ovl_header);
    ovl_header_ROM_END = __romPos;
    ovl_header_VRAM_END = .;

    main_ROM_START = __romPos;
    main_VRAM = ADDR(.main);
    .main 0x167D00 : AT(main_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        main_TEXT_START = .;
        build/asm/main/text.s.o(.text);
        build/asm/main/data/vutext.s.o(.text);
        build/asm/main/init.s.o(.text);
        . = ALIGN(., 16);
        main_TEXT_END = .;
        main_TEXT_SIZE = ABSOLUTE(main_TEXT_END - main_TEXT_START);
        main_DATA_START = .;
        build/asm/main/data/data.data.s.o(.data);
        build/asm/main/text.s.o(.data);
        build/asm/main/data/vutext.s.o(.data);
        build/asm/main/init.s.o(.data);
        . = ALIGN(., 16);
        main_DATA_END = .;
        main_DATA_SIZE = ABSOLUTE(main_DATA_END - main_DATA_START);
        main_RODATA_START = .;
        build/asm/main/data/rodata.rodata.s.o(.rodata);
        build/asm/main/text.s.o(.rodata);
        build/asm/main/data/vutext.s.o(.rodata);
        build/asm/main/init.s.o(.rodata);
        build/asm/main/data/ctors.rodata.s.o(.rodata);
        . = ALIGN(., 16);
        main_RODATA_END = .;
        main_RODATA_SIZE = ABSOLUTE(main_RODATA_END - main_RODATA_START);
    }
    main_bss_VRAM = ADDR(.main_bss);
    .main_bss (NOLOAD) : SUBALIGN(16)
    {
        FILL(0x00000000);
        main_BSS_START = .;
        build/asm/main/text.s.o(.bss);
        build/asm/main/data/vutext.s.o(.bss);
        build/asm/main/init.s.o(.bss);
        build/asm/main/data/bss.bss.s.o(.bss);
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
