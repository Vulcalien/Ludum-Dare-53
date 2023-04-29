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

#define MENU_ITEMS (4)

static i32 menu_selected = 0;

static void start_init(u32 flags) {
    menu_selected = 0;
}

static void start_tick(void) {
    if(INPUT_PRESSED(KEY_LEFT | KEY_DOWN))
        menu_selected++;
    if(INPUT_PRESSED(KEY_RIGHT | KEY_UP))
        menu_selected--;

    if(menu_selected < 0)
        menu_selected = MENU_ITEMS - 1;
    else if(menu_selected >= MENU_ITEMS)
        menu_selected = 0;

    if(INPUT_RELEASED(KEY_A | KEY_B | KEY_START)) {
        switch(menu_selected) {
            case 0: // Start
                scene_set(&scene_game, 2);
                break;

            case 1: // How to play
                /*scene_set(&scene_howtoplay, 1);*/
                break;

            case 2: // Settings
                /*scene_set(&scene_settings, 1);*/
                break;

            case 3: // About
                /*scene_set(&scene_about, 1);*/
                break;
        }
    }
}

static void start_draw(void) {
    // TODO ...
}

const struct Scene scene_start = {
    .init = start_init,
    .tick = start_tick,
    .draw = start_draw
};
