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
#include "entity.h"

#include "screen.h"
#include "level.h"

struct enemy_Data {
    u8 unused[8];
};

static_assert(sizeof(struct enemy_Data) == 8, "enemy_Data: wrong size");

static void enemy_tick(struct entity_Data *data) {
    struct enemy_Data *enemy_data = (struct enemy_Data *) &data->data;


}

/*static*/
u32 enemy_draw(struct entity_Data *data, u32 entities_drawn) {
    struct enemy_Data *enemy_data = (struct enemy_Data *) &data->data;

    SPRITE(
        &OAM[entities_drawn * 4], data->x, data->y,
        1, 2, 1, 4
    );

    SPRITE(
        &OAM[(entities_drawn + 1) * 4], data->x + 24, data->y,
        2, 0, 1, 64 + (tick_count / 8) % 4
    );

    return 2;
}

const struct Entity entity_enemy = {
    .tick = enemy_tick,
    .draw = enemy_draw
};

void level_add_enemy(void) {
    struct entity_Data *data = level_new_entity(ENTITY_ENEMY);
    struct enemy_Data *enemy_data = (struct enemy_Data *) &data->data;

    // ...
}
