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

    i16 x;
    i16 y;

    u8 data[8];
};

struct Entity {
    void (*tick)(struct entity_Data *data);
    void (*draw)(struct entity_Data *data, u32 sprite);
};

#define ENTITY_TYPES (16) // TODO set the exact number

#define ENTITY_PLAYER    (0)
#define ENTITY_ENEMY     (1)
#define ENTITY_MESSAGE   (2)
#define ENTITY_LASER     (3)
#define ENTITY_EXPLOSION (4)

#endif // LD53_ENTITY
