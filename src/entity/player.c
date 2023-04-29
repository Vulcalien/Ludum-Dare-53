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
#include "player.h"
#include "entity.h"

#include "screen.h"
#include "level.h"
#include "input.h"

struct player_Data {
    u16 juice;

    u8 unused[6];
};

static_assert(sizeof(struct player_Data) == 8, "player_Data: wrong size");

static void player_tick(struct entity_Data *data) {
    struct player_Data *player_data = (struct player_Data *) &data->data;

    i32 xm = 0, ym = 0;
    if(INPUT_DOWN(KEY_LEFT)) xm--;
    if(INPUT_DOWN(KEY_RIGHT)) xm++;
    if(INPUT_DOWN(KEY_UP)) ym--;
    if(INPUT_DOWN(KEY_DOWN)) ym++;
}

static u32 player_draw(struct entity_Data *data, u32 entities_drawn) {
    struct player_Data *player_data = (struct player_Data *) &data->data;

    SPRITE(
        &OAM[entities_drawn * 4], data->x, data->y,
        1, 2, 0, 0
    );

    SPRITE(
        &OAM[(entities_drawn + 1) * 4], data->x, data->y,
        2, 0, 0, 64 + (tick_count / 8) % 4
    );

    return 2;
}

const struct Entity entity_player = {
    .tick = player_tick,
    .draw = player_draw
};

void level_add_player(void) {
    struct entity_Data *data = &level.entities[0];
    struct player_Data *player_data = (struct player_Data *) &data->data;

    data->type = ENTITY_PLAYER;
    data->x = 0;
    data->y = 0;

    player_data->juice = 0;
}