
// This file just contains the background tilemap
// This used to be inside of the gfx.cpp file, but
// it was moved here for clearity reasons.

#ifndef __GFX_BACKGROUND__
#define __GFX_BACKGROUND__

#include "gfx.h"
#include <avr/pgmspace.h>

// clang-format off

#define __BG_TILE(a, b) ((uint8_t)(a << 4 | b))
#define __BG_ROW(a) __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(a, a),
#define __BG_GRASS_1(a, b) __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(b, a), __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(a, b),
#define __BG_GRASS_2(a, b)  __BG_TILE(b, a), __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(b, b), __BG_TILE(a, a), __BG_TILE(a, a),

Level current_level; // Make sure to initialize this in main using set_current_level(), otherwise bad things will happen.

void set_current_level(uint8_t level)
{
    memcpy_P(&current_level, &levels[level], sizeof(Level));
}

const PROGMEM Level levels[] = {
    {
        {
            {
                __BG_ROW(0)
				__BG_ROW(0)
				__BG_GRASS_2(7, 1)
				__BG_ROW(2)
                __BG_ROW(3)
				__BG_ROW(3)
				__BG_ROW(3)
				__BG_ROW(3)
                __BG_ROW(4)
				__BG_ROW(5)
				__BG_ROW(5)
				__BG_ROW(5)
                __BG_ROW(5)
				__BG_ROW(6)
				__BG_GRASS_1(1, 7)
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
                { 0, 0 },
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
    },

	{
        {
            {
                __BG_ROW(0)
				__BG_ROW(0)
				__BG_ROW(4)
				__BG_ROW(5)
                __BG_ROW(5)
				__BG_ROW(5)
				__BG_ROW(5)
				__BG_ROW(5)
                __BG_ROW(5)
				__BG_ROW(5)
				__BG_ROW(5)
				__BG_ROW(5)
                __BG_ROW(5)
				__BG_ROW(5)
				__BG_ROW(6)
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
            3,
            19,
            {
                { 0, 0 },
                { 1, 8 },
                
				{ 0, 1 },
                { 1, 5 },

                { 0, 2 },
                { 0, 5 },
                { 1, 8 },

                { 1, 1 },
                
				{ 0, 6 },
				{ 1, 9 },

				{ 1, 3 },

				{ 1, 6 },

				{ 1, 1 },

				{ 0, 8 },
				{ 0, 1 },
				{ 1, 5 },

				{ 0, 2 },
				{ 1, 8 },

				{ 1, 12 },
            }
        },
        {
            0,
            0,
			{}
        }
    },

	{
        {
            {
                __BG_ROW(0)
				__BG_ROW(0)
				__BG_ROW(4)
				__BG_ROW(5)
                __BG_ROW(5)
				__BG_ROW(5)
				__BG_ROW(6)
				__BG_ROW(2)
                __BG_ROW(3)
				__BG_ROW(3)
				__BG_ROW(3)
				__BG_ROW(3)
                __BG_ROW(3)
				__BG_ROW(3)
				__BG_ROW(5)
                __BG_ROW(6)
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
            3,
            7,
            {
                { 0, 0 },
                { 0, 6 },
                { 1, 12 },

                { 0, 2 },
                { 1, 8 },

                { 0, 4 },
                { 0, 10 },
            }
        },
        {
            8,
            7,
			{
                { 1, 5, 0 },
                { 1, 7, 4 },
                { 1, 2, 6 },
                { 0, 0, 5 },
                { 1, 4, 9 },
                { 1, 3, 2 },
                { 1, 6, 1 },
            }
        }
    },

    {
        {
            {
                __BG_ROW(0)
				__BG_ROW(0)
				__BG_ROW(6)
				__BG_ROW(2)
                __BG_ROW(3)
				__BG_ROW(3)
				__BG_ROW(3)
				__BG_ROW(3)
                __BG_ROW(3)
				__BG_ROW(3)
				__BG_ROW(3)
				__BG_ROW(3)
                __BG_ROW(3)
				__BG_ROW(3)
				__BG_ROW(6)
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
            0,
            0,
            {}
        },
        {
            4,
            14,
			{
                { 0, 1, 0 },
                { 1, 0, 5 },
                { 0, 0, 1 },
                { 1, 2, 6 },
                { 1, 6, 0 },
                { 1, 0, 4 },
                { 1, 1, 2 },
                { 0, 2, 11 },
                { 1, 2, 4 },
                { 1, 6, 10 },
                { 0, 4, 5 },
                { 1, 0, 0 },
                { 1, 7, 8 },
                { 1, 3, 11 },
            }
        }
    }
};

// clang-format on

#endif
