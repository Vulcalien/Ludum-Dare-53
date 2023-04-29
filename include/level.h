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
#ifndef LD53_LEVEL
#define LD53_LEVEL

#include "ld53.h"

#include "entity.h"

#define LEVEL_ENTITY_COUNT (128)

struct Level {
    struct entity_Data entities[LEVEL_ENTITY_COUNT];

    struct {
        i32 x;
        i32 y;
    } offset;
};

extern struct Level level;

extern void level_init(void);

#endif // LD53_LEVEL
