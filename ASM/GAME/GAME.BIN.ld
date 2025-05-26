SECTIONS
{
    __romPos = 0;
    _gp = 0x15B4F0;
    ovl_header_ROM_START = __romPos;
    ovl_header_VRAM = ADDR(.ovl_header);
    .ovl_header : AT(ovl_header_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        ovl_header_DATA_START = .;
        build/asm/game/data/ovl_header.s.o(.data);
        ovl_header_DATA_END = .;
        ovl_header_DATA_SIZE = ABSOLUTE(ovl_header_DATA_END - ovl_header_DATA_START);
    }
    __romPos += SIZEOF(.ovl_header);
    ovl_header_ROM_END = __romPos;
    ovl_header_VRAM_END = .;

    game_ROM_START = __romPos;
    game_VRAM = ADDR(.game);
    .game 0x62B380 : AT(game_ROM_START) SUBALIGN(16)
    {
        FILL(0x00000000);
        game_TEXT_START = .;
        build/asm/game/text.s.o(.text);
        build/asm/game/init.s.o(.text);
        . = ALIGN(., 16);
        game_TEXT_END = .;
        game_TEXT_SIZE = ABSOLUTE(game_TEXT_END - game_TEXT_START);
        game_DATA_START = .;
        build/asm/game/data/data.data.s.o(.data);
        build/asm/game/text.s.o(.data);
        build/asm/game/init.s.o(.data);
        . = ALIGN(., 16);
        game_DATA_END = .;
        game_DATA_SIZE = ABSOLUTE(game_DATA_END - game_DATA_START);
        game_RODATA_START = .;
        build/asm/game/data/rodata.rodata.s.o(.rodata);
        build/asm/game/text.s.o(.rodata);
        build/asm/game/init.s.o(.rodata);
        build/asm/game/data/ctors.rodata.s.o(.rodata);
        . = ALIGN(., 16);
        game_RODATA_END = .;
        game_RODATA_SIZE = ABSOLUTE(game_RODATA_END - game_RODATA_START);
    }
    game_bss_VRAM = ADDR(.game_bss);
    .game_bss (NOLOAD) : SUBALIGN(16)
    {
        FILL(0x00000000);
        game_BSS_START = .;
        build/asm/game/text.s.o(.bss);
        build/asm/game/init.s.o(.bss);
        build/asm/game/data/bss.bss.s.o(.bss);
        . = ALIGN(., 16);
        game_BSS_END = .;
        game_BSS_SIZE = ABSOLUTE(game_BSS_END - game_BSS_START);
    }
    __romPos += SIZEOF(.game);
    __romPos = ALIGN(__romPos, 16);
    . = ALIGN(., 16);
    game_ROM_END = __romPos;
    game_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
