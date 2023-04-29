/* Copyright 2023 Vulcalien
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "screen.h"

#include "atlas.h"

#define DISPLAY_CONTROL *((vu16 *) 0x04000000)
#define DISPLAY_STATUS  *((vu16 *) 0x04000004)

#define WINDOW_IN  *((vu16 *) 0x04000048)
#define WINDOW_OUT *((vu16 *) 0x0400004a)

#define CHAR_BLOCK_0 ((vu16 *) 0x06000000)
#define CHAR_BLOCK_1 ((vu16 *) 0x06004000)
#define CHAR_BLOCK_2 ((vu16 *) 0x06008000)
#define CHAR_BLOCK_3 ((vu16 *) 0x0600c000)

#define SPR_TILESET ((vu16 *) 0x06010000)

#define BG0_CONTROL *((vu16 *) 0x04000008)
#define BG1_CONTROL *((vu16 *) 0x0400000a)
#define BG2_CONTROL *((vu16 *) 0x0400000c)
#define BG3_CONTROL *((vu16 *) 0x0400000e)

#define BG_PALETTE  ((vu16 *) 0x05000000)
#define SPR_PALETTE ((vu16 *) 0x05000200)

static inline void copy_palettes(void) {
    u16 palette[16] = {
        0,
        0x7fff, 0x0000, 0x001d, 0x02bd, 0x03bd,
        0x6f7b, 0x3398, 0x295f, 0x294a, 0x7400
    };

    memcpy16(BG_PALETTE, palette, sizeof(palette) / sizeof(u16));
    memcpy16(SPR_PALETTE, palette, sizeof(palette) / sizeof(u16));
}

static inline void copy_tileset(vu16 *dest, u8 *tileset, u32 size) {
    size /= 2;

    for(u32 i = 0; i < size; i++) {
        u8 byte0 = tileset[i * 2];
        byte0 = (byte0 & 0x0f) << 4 | (byte0 & 0xf0) >> 4;

        u8 byte1 = tileset[i * 2 + 1];
        byte1 = (byte1 & 0x0f) << 4 | (byte1 & 0xf0) >> 4;

        dest[i] = byte0 | byte1 << 8;
    }
}

static inline void copy_tilesets(void) {
    copy_tileset(
        SPR_TILESET, sprite_atlas,
        sizeof(sprite_atlas) / sizeof(u8)
    );

    copy_tileset(
        CHAR_BLOCK_0, tile_atlas,
        sizeof(tile_atlas) / sizeof(u8)
    );
}

void screen_init(void) {
    // hide all sprites
    for(u32 i = 0; i < 128; i++)
        OAM[i * 4] = 1 << 9;

    // enable V-Blank IRQ
    DISPLAY_STATUS = (1 << 3);

    copy_palettes();
    copy_tilesets();

    DISPLAY_CONTROL = 0       | // Video Mode
                      0 << 8  | // Enable BG 0
                      0 << 9  | // Enable BG 1
                      0 << 10 | // Enable BG 2
                      0 << 11 | // Enable BG 3
                      1 << 12;  // Enable OBJ
}

IWRAM_SECTION
void vsync(void) {
    __asm__ volatile ("swi 0x05 << 16");
}
