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

#include "level.h"
#include "screen.h"

struct laser_Data {
    i8 owner_type;

    u8 unused[7];
};

static_assert(sizeof(struct laser_Data) == 8, "laser_Data: wrong size");

IWRAM_SECTION
static void laser_tick(struct entity_Data *data) {
    struct laser_Data *laser_data = (struct laser_Data *) &data->data;

    if(laser_data->owner_type == ENTITY_PLAYER)
        data->x += 5;
    else
        data->x -= 3;

    i32 rel_x = data->x - level.offset.x;
    if(rel_x < -10 || rel_x >= 250) {
        data->type = -1;
        return;
    }

    for(u32 i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        struct entity_Data *e = &level.entities[i];
        if(e->type < 0)
            continue;

        const struct Entity *entity = entity_list[e->type];

        if(entity->hurt && e != data) {
            entity->hurt(e, data, 1);
            data->type = -1;
        }
    }
}

IWRAM_SECTION
static u32 laser_draw(struct entity_Data* data, u32 entities_draw) {
    SPRITE(
        &OAM[entities_draw * 4], data->x - 4, data->y - 4,
        0, 0, 0, 12
    );

    return 1;
}

const struct Entity entity_laser = {
    .tick = laser_tick,
    .draw = laser_draw
};

void level_add_laser(i8 owner_type, i32 x, i32 y) {
    struct entity_Data *data = level_new_entity(ENTITY_LASER);
    if(!data)
        return;

    struct laser_Data *laser_data = (struct laser_Data *) &data->data;

    data->x = x;
    data->y = y;
    laser_data->owner_type = owner_type;
}
