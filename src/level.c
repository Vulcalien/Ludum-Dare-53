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
#include "level.h"

#include "entity.h"

EWRAM_BSS_SECTION
struct Level level;

void level_init(void) {
    for(u32 i = 0; i < LEVEL_ENTITY_COUNT; i++)
        level.entities[i].type = -1;

    level.offset.x = 0;
    level.offset.y = 0;
}

IWRAM_SECTION
void level_tick(void) {
    for(u32 i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        struct entity_Data *data = &level.entities[i];

        if(data->type < 0)
            continue;

        const struct Entity *e = &entity_list[data->type];
        e->tick(data);
    }
}

IWRAM_SECTION
void level_draw(void) {
    u32 sprites_drawn = 0;
    for(u32 i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        struct entity_Data *data = &level.entities[i];

        if(data->type < 0)
            continue;

        const struct Entity *e = &entity_list[data->type];
        sprites_drawn += e->draw(data, sprites_drawn);
    }
}
