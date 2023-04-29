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
#include "scene.h"

#include "input.h"
#include "level.h"
#include "screen.h"

static void game_init(u32 flags) {
    screen_clear_menu_bg();
    if(flags == 2)
        level_init();
}

static void game_tick(void) {
    level_tick();

    /*if(INPUT_PRESSED(KEY_START))*/
        /*scene_set(&scene_pause, 1);*/
}

static void game_draw(void) {
    level_draw();
}

const struct Scene scene_game = {
    .init = game_init,
    .tick = game_tick,
    .draw = game_draw
};
