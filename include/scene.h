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
#ifndef LD53_SCENE
#define LD53_SCENE

#include "ld53.h"

struct Scene {
    void (*init)(u32 flags);
    void (*tick)(void);
    void (*draw)(void);
};

extern const struct Scene *scene;

extern const struct Scene scene_start;
extern const struct Scene scene_game;
extern const struct Scene scene_howtoplay;
extern const struct Scene scene_settings;
extern const struct Scene scene_about;
extern const struct Scene scene_pause;

inline void scene_set(const struct Scene *new_scene, u32 flags) {
    scene = new_scene;

    if(flags && scene->init)
        scene->init(flags);
}

#endif // LD53_SCENE
