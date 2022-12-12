
#include "collision.h"

RawImage* blacklist[] = {
	&image_car_front,
	&image_car_back,
	0
};

// Compare a tilemap to a raw image, intended only to be used in this file
uint8_t compare_tile(TileMap *map, Vector2 *tile_pos, RawImage *compare_to)
{
	uint16_t index = tile_pos->y * 6 + tile_pos->x / 2;
	uint8_t tile_id = (tile_pos->x % 2) ? (map->tiles[index] & 0x0f) : ((map->tiles[index] & 0xf0) >> 4);
	RawImage *raw_img = map->sprites[tile_id - 1];
	ImageBytes raw = raw_img->data;

	return raw == compare_to->data;
}

uint8_t is_position_standable(Vector2 position)
{
	position.x /= 20;
	position.y /= 20;
	RawImage **ptr = blacklist;
	while (*ptr != 0)
	{
		if (compare_tile(&foreground, &position, *ptr))
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
	delta.x = CLAMP_SCREEN_X(plr->image.position.x + delta.x * MOVEMENT_SPEED);
	delta.y = CLAMP_SCREEN_Y(plr->image.position.y + delta.y * MOVEMENT_SPEED);

	compare_val = is_position_standable(delta) ? delta : plr->spawn;

	if (compare_val.x != plr->image.position.x || compare_val.y != plr->image.position.y)
	{
		move_image(&plr->image, &compare_val);
	}
}
