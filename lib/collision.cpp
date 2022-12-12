
#include "collision.h"

// All the tiles which make the player respawn in the foreground
RawImage* foreground_blacklist[] = {
	&image_car_front,
	&image_car_back,
	0
};

// All the tiles which make the player respawn in the background
RawImage* background_blacklist[] = {
	&image_lake,
	0
};

// Compare a tilemap to a raw image, intended only to be used in this file
uint8_t compare_tile(TileMap *map, Vector2 *tile_pos, RawImage *compare_to)
{
	// Get the index in the array
	uint16_t index = tile_pos->y * 6 + tile_pos->x / 2;
	// Get the id
	uint8_t tile_id = (tile_pos->x % 2) ? (map->tiles[index] & 0x0f) : ((map->tiles[index] & 0xf0) >> 4);
	RawImage *raw_img = map->sprites[tile_id - 1];
	ImageBytes raw = raw_img->data;

	// Compare the raw image pointers
	return raw == compare_to->data;
}

uint8_t is_position_standable(Vector2 position)
{
	// Convert pixel space into tile space 
	position.x /= 20;
	position.y /= 20;
	// Check the foreground for illegal tiles
	RawImage **ptr = foreground_blacklist;
	while (*ptr != 0)
	{
		if (compare_tile(&foreground, &position, *ptr))
		{
			return 0;
		};
		ptr++;
	}
	// Check the background for illegal tiles
	ptr = background_blacklist;
	while (*ptr != 0)
	{
		if (compare_tile(&background, &position, *ptr))
		{
			return 0;
		};
		ptr++;
	}
	return 1;
}

uint8_t move_player(Player *plr, Vector2 delta)
{
	Vector2 compare_val = plr->image.position;
	// Make sure we're in bounds
	delta.x = CLAMP_SCREEN_X(plr->image.position.x + delta.x * MOVEMENT_SPEED);
	delta.y = CLAMP_SCREEN_Y(plr->image.position.y + delta.y * MOVEMENT_SPEED);

	// Can we stand here? If not, respawn
	compare_val = is_position_standable(delta) ? delta : plr->spawn;

	// If we didn't move, then don't bother drawing
	if (compare_val.x != plr->image.position.x || compare_val.y != plr->image.position.y)
	{
		move_image(&plr->image, &compare_val);
	}
}
