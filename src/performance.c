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
#include "performance.h"

#include "input.h"
#include "screen.h"

static bool show_performance = false;
static u16 tick_vcount;
static u16 draw_vcount;

static u16 ticks = 0, frames = 0;
static u16 tps   = 0, fps    = 0;

IWRAM_SECTION
void performance_tick(void) {
    tick_vcount = VCOUNT;
    ticks++;

    if(INPUT_DOWN(KEY_L) && INPUT_DOWN(KEY_R) && INPUT_PRESSED(KEY_SELECT))
        show_performance = !show_performance;
}

IWRAM_SECTION
void performance_draw(void) {
    draw_vcount = VCOUNT;
    frames++;

    if(!show_performance)
        return;

    char text[8] = { 0 };

    itoa(tick_vcount, 16, text, 2, true);
    screen_write(text, 0, 0);
    itoa(draw_vcount, 16, text, 2, true);
    screen_write(text, 0, 1);
}

IWRAM_SECTION
void performance_vblank(void) {
    static u32 vblanks = 0;
    vblanks++;

    if(vblanks == 60) {
        vblanks = 0;

        tps = ticks;
        fps = frames;

        ticks = 0;
        frames = 0;
    }
}
