
// This file just contains the background tilemap
// This used to be inside of the gfx.cpp file, but
// it was moved here for clearity reasons.

#ifndef __GFX_BACKGROUND__
#define __GFX_BACKGROUND__

#include "gfx.h"

#define __BG_TILE(a, b) ((uint8_t)(a << 4 | b))
#define __BG_ROW(a) __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(a, a), __BG_TILE(a, a),

TileMap background = {
	{
		__BG_ROW(0)
		__BG_ROW(0)
		__BG_ROW(1)
		__BG_ROW(2)

		__BG_ROW(3)
		__BG_ROW(4)
		__BG_ROW(4)
		__BG_ROW(5)

		__BG_ROW(1)
		__BG_ROW(6)
		__BG_ROW(7)
		__BG_ROW(7)

		__BG_ROW(7)
		__BG_ROW(8)
		__BG_ROW(1)
		__BG_ROW(1)
	},
	{
		&image_grass,
		&image_sand_grass,
		&image_lake_sand,
		&image_lake,
		&image_grass_lake,
		&image_road_grass,
		&image_road_middle,
		&image_sidewalk_road,
	}
};

TileMap foreground = {
	{
		__BG_ROW(0)
		__BG_ROW(0)
		__BG_ROW(0)
		__BG_ROW(0)

		__BG_ROW(0)
		__BG_ROW(0)
		__BG_ROW(0)
		__BG_ROW(0)

		__BG_ROW(0)
		__BG_ROW(0)
		__BG_ROW(0)
		__BG_ROW(0)
	},
	{
		&image_road_middle,
	}
};

#endif
