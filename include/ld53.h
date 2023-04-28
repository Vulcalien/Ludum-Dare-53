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
#ifndef LD53_CORE
#define LD53_CORE

#include "types.h"
#include "util.h"

#define THUMB __attribute__((target("thumb")))

#define NOINLINE __attribute__((noinline))
#define NOCLONE  __attribute__((noclone))

#define EWRAM_SECTION        __attribute__((section(".ewram")))
#define EWRAM_BSS_SECTION    __attribute__((section(".bss.ewram")))
#define IWRAM_SECTION        __attribute__((section(".iwram")))
#define IWRAM_RODATA_SECTION __attribute__((section(".rodata_iwram")))

#define static_assert _Static_assert

#ifndef NULL
    #define NULL ((void *) 0)
#endif

// The behavior of right shift for negative values is
// implementation-dependent, but Arithmetic Right Shift is required
static_assert((-1) >> 1 == -1, "Arithmetic Right Shift is required");

#endif // LD53_CORE
