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
                      1 << 8  | // Enable BG 0
                      0 << 9  | // Enable BG 1
                      0 << 10 | // Enable BG 2
                      1 << 11 | // Enable BG 3
                      1 << 12;  // Enable OBJ

    // BG0: menus
    BG0_CONTROL = 0 << 0 | // Priority
                  0 << 2 | // Tileset Character Block
                  8 << 8 | // Tilemap Block
                  0 << 14; // Size (0 is 256x256, 2K)

    // BG3: sky background
    BG3_CONTROL = 3 << 0  | // Priority
                  0 << 2  | // Tileset Character Block
                  9 << 8 | // Tilemap Block
                  2 << 14; // Size (2 is 256x512, 4K)

    // draw sky background
    for(u32 i = 0; i < 32 * 64; i++) {
        u16 r = rand();
        if(r % 8 == 0)
            BG3_TILEMAP[i] = 64 + ((r >> 8) % 8);
        else
            BG3_TILEMAP[i] = 64;
    }
}

void screen_show_menu_bg(bool flag) {
    if(flag)
        DISPLAY_CONTROL |= (1 << 8);
    else
        DISPLAY_CONTROL &= ~(1 << 8);
}

IWRAM_SECTION
void screen_write(char *text, u32 x0, u32 y0) {
    i32 y = y0;
    for(i32 x = x0; *text != '\0'; x++, text++) {
        char c = *text;
        if(c == '\n') {
            x = x0 - 1;
            y++;
        } else {
            BG0_TILEMAP[x + y * 32] = (c - ' ');
        }
    }
}

void screen_draw_frame(u32 x0, u32 y0, u32 x1, u32 y1) {
    BG0_TILEMAP[x0 + y0 * 32] = 74;
    BG0_TILEMAP[x1 + y0 * 32] = 74 | 1 << 10;
    BG0_TILEMAP[x0 + y1 * 32] = 74 | 2 << 10;
    BG0_TILEMAP[x1 + y1 * 32] = 74 | 3 << 10;

    for(u32 x = x0 + 1; x < x1; x++) {
        BG0_TILEMAP[x + y0 * 32] = 73;
        BG0_TILEMAP[x + y1 * 32] = 73 | 2 << 10;

        for(u32 y = y0 + 1; y < y1; y++)
            BG0_TILEMAP[x + y * 32] = 0;
    }

    for(u32 y = y0 + 1; y < y1; y++) {
        BG0_TILEMAP[x0 + y * 32] = 72;
        BG0_TILEMAP[x1 + y * 32] = 72 | 1 << 10;
    }
}

IWRAM_SECTION
void vsync(void) {
    __asm__ volatile ("swi 0x05 << 16");
}
