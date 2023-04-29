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
#ifndef LD53_ENTITY
#define LD53_ENTITY

#include "ld53.h"

struct entity_Data {
    i8 type;

    i32 x;
    i32 y;

    u8 data[8];
};

struct Entity {
    void (*tick)(struct entity_Data *data);
    u32 (*draw)(struct entity_Data *data, u32 entities_drawn);

    void (*hurt)(struct entity_Data *data, struct entity_Data *attacker,
                 u32 damage);
};

#define ENTITY_TYPES (16) // TODO set the exact number
extern const struct Entity *entity_list[ENTITY_TYPES];

extern const struct Entity entity_player;
extern const struct Entity entity_enemy;
extern const struct Entity entity_laser;

#define ENTITY_PLAYER    (0)
#define ENTITY_ENEMY     (1)
#define ENTITY_LASER     (2)
#define ENTITY_MESSAGE   (3)
#define ENTITY_EXPLOSION (4)

#define SPRITE(attr, xs, ys, shape, size, flip, tile)\
    do {\
        (attr)[0] = ((ys - level.offset.y) & 0xff)    << 0 |\
                    ((shape) & 0x3)                   << 14;\
        (attr)[1] = ((xs - level.offset.x) & 0x1ff)  << 0  |\
                    ((flip) & 0x3)                   << 12 |\
                    ((size) & 0x3)                   << 14;\
        (attr)[2] = ((tile) & 0x3ff) << 0 |\
                    0                << 10;\
    } while(0)

#endif // LD53_ENTITY
