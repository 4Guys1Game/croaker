
// This file just contains the background tilemap
// This used to be inside of the gfx.cpp file, but
// it was moved here for clearity reasons.

#ifndef __GFX_BACKGROUND__
#define __GFX_BACKGROUND__

#include "gfx.h"

// clang-format off

#define __BG_TILE(a, b) ((uint8_t)(a << 4 | b))
#define __BG_ROW(a) __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(a, a),
#define __BG_GRASS_1(a, b) __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(b, a), __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(a, b),
#define __BG_GRASS_2(a, b)  __BG_TILE(b, a), __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(b, b), __BG_TILE(a, a), __BG_TILE(a, a),

uint8_t current_level = 0;

Level levels[] = {
    {
        {
            {
                __BG_ROW(0) __BG_ROW(0) __BG_GRASS_2(7, 1) __BG_ROW(2)
                __BG_ROW(3) __BG_ROW(3) __BG_ROW(3) __BG_ROW(3)
                __BG_ROW(4) __BG_ROW(5) __BG_ROW(5) __BG_ROW(5)
                __BG_ROW(5) __BG_ROW(6) __BG_GRASS_1(1, 7)
                __BG_GRASS_2(1, 7)
            },
            {
                &image_grass_bland,
                &image_water_sand_grass,
                &image_lake,
                &image_road_sand_water,
                &image_road,
                &image_grass_road,
                &image_grass_flower
            }
        },
        {
            {
                __BG_ROW(0) __BG_ROW(0) __BG_ROW(0) __BG_ROW(0)
                __BG_ROW(0) __BG_ROW(0) __BG_ROW(0) __BG_ROW(0)
                __BG_ROW(0) __BG_ROW(0) __BG_ROW(0) __BG_ROW(0)
            },
            {
                &image_car_front, &image_car_back, &image_log_front,
                &image_log_middle, &image_log_back
            }
        },
        {
            9,
            6,
            {
                { 0, 1 },
                { 1, 5 },
                { 1, 8 },
                { 1, 4 },
                { 1, 5 },
                { 0, 1 },
                { 0, 10 }
            }
        },
        {
            4,
            8,
            {
                { 0, 0, 10 },
                { 0, 0, 6 },
                { 1, 0, 2 },
                { 0, 4, 10 },
                { 1, 2, 5 },
                { 1, 7, 2 },
                { 0, 2, 8 },
                { 0, 1, 2 }
            }
        }
    }
};

// clang-format on

#endif
