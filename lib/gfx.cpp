
#include "gfx.h"

#define BYTE_TYPE_OFFSET 7
#define COLOR_FIRST_COL_OFFSET 4
#define COLOR_SECOND_COL_OFFSET 0
#define COLOR_COPY_OFFSET 3
#define RANGE_COL_OFFSET 0
#define RANGE_RANGE_OFFSET 3

void set_address_window(Vector2 *position, Vector2 *size)
{
	spi_send_command(CMD_COLUMN_ADDRESS_SET);
	spi_write16(position->x);
	spi_write16(position->x + size->x - 1);

	spi_send_command(CMD_PAGE_ADDRESS_SET);
	spi_write16(position->y);
	spi_write16(position->y + size->y - 1);

	spi_send_command(CMD_MEMORY_WRITE);
}

void draw_bitmap_P(ImageBytes image, ImageLength image_len, Vector2 *position, Vector2 *size)
{
	// Retrieve the color palette
	uint16_t color_palette[] = {
		(pgm_read_byte(image + 0) << 8) + pgm_read_byte(image + 1),
		(pgm_read_byte(image + 2) << 8) + pgm_read_byte(image + 3),
		(pgm_read_byte(image + 4) << 8) + pgm_read_byte(image + 5),
		(pgm_read_byte(image + 6) << 8) + pgm_read_byte(image + 7),
		(pgm_read_byte(image + 8) << 8) + pgm_read_byte(image + 9),
		(pgm_read_byte(image + 10) << 8) + pgm_read_byte(image + 11),
		(pgm_read_byte(image + 12) << 8) + pgm_read_byte(image + 13),
		(pgm_read_byte(image + 14) << 8) + pgm_read_byte(image + 15),
	};

	// Start a write message
	spi_begin_write();
	set_address_window(position, size);

	for (uint16_t idx = 16; idx < image_len; idx++)
	{
		register uint8_t byte = pgm_read_byte(image + idx);
		// Case 1: RANGE_BYTE
		if (byte & (1 << BYTE_TYPE_OFFSET))
		{
			uint8_t range = (byte & (0b1111 << RANGE_RANGE_OFFSET)) >> RANGE_RANGE_OFFSET;
			uint8_t col_idx = (byte & (0b111 << RANGE_COL_OFFSET)) >> RANGE_COL_OFFSET;
			// Save on creating an extra variable by reusing the range var
			for (range + 1; range > 0; range--)
			{
				spi_write16(color_palette[col_idx]);
			}
		}
		// Case 2: COLOR_BYTE
		else
		{
			// Retrieve the colors & write to screen
			uint8_t col_idx_1 = (byte & (0b111 << COLOR_FIRST_COL_OFFSET)) >> COLOR_FIRST_COL_OFFSET;
			uint8_t col_idx_2 = (byte & (0b111 << COLOR_SECOND_COL_OFFSET)) >> COLOR_SECOND_COL_OFFSET;
			spi_write16(color_palette[col_idx_1]);
			spi_write16(color_palette[col_idx_2]);
			// If the copy bit is set, write again
			if (byte & (1 << COLOR_COPY_OFFSET))
			{
				spi_write16(color_palette[col_idx_1]);
				spi_write16(color_palette[col_idx_2]);
			}
		}
	}

	// Send the transmittion
	spi_end_write();
}

void draw_bitmap_mask_P(ImageBytes image, ImageLength image_len, Vector2 *position, Vector2 *size)
{
#define incr_cursor                            \
	cursor.x++;                                \
	if (cursor.x == position->x + size->x)     \
	{                                          \
		cursor.x = position->x;                \
		cursor.y++;                            \
		if (cursor.y == position->y + size->y) \
		{                                      \
			break;                             \
		}                                      \
	}
	// Retrieve the color palette
	uint16_t color_palette[] = {
		(pgm_read_byte(image + 0) << 8) + pgm_read_byte(image + 1),
		(pgm_read_byte(image + 2) << 8) + pgm_read_byte(image + 3),
		(pgm_read_byte(image + 4) << 8) + pgm_read_byte(image + 5),
		(pgm_read_byte(image + 6) << 8) + pgm_read_byte(image + 7),
		(pgm_read_byte(image + 8) << 8) + pgm_read_byte(image + 9),
		(pgm_read_byte(image + 10) << 8) + pgm_read_byte(image + 11),
		(pgm_read_byte(image + 12) << 8) + pgm_read_byte(image + 13),
		(pgm_read_byte(image + 14) << 8) + pgm_read_byte(image + 15),
	};

	// Start a write message
	spi_begin_write();
	set_address_window(position, size);

	Vector2 cursor = Vector2{position->x, position->y};
	Vector2 addr_size = Vector2{1, 1};

	for (uint16_t idx = 16; idx < image_len; idx++)
	{
		register uint8_t byte = pgm_read_byte(image + idx);
		// Case 1: RANGE_BYTE
		if (byte & (1 << BYTE_TYPE_OFFSET))
		{
			uint8_t range = (byte & (0b1111 << RANGE_RANGE_OFFSET)) >> RANGE_RANGE_OFFSET;
			uint8_t col_idx = (byte & (0b111 << RANGE_COL_OFFSET)) >> RANGE_COL_OFFSET;
			// Save on creating an extra variable by reusing the range var
			// Having the if outside is more efficient than having it inside the loop
			if (col_idx != 0)
			{
				for (range + 1; range > 0; range--)
				{

					set_address_window(&cursor, &addr_size);
					spi_write16(color_palette[col_idx]);
					incr_cursor;
				}
			}
			else
			{
				for (range + 1; range > 0; range--)
				{
					incr_cursor;
				}
			}
		}
		// Case 2: COLOR_BYTE
		else
		{
			// Retrieve the colors & write to screen
			uint8_t col_idx_1 = (byte & (0b111 << COLOR_FIRST_COL_OFFSET)) >> COLOR_FIRST_COL_OFFSET;
			uint8_t col_idx_2 = (byte & (0b111 << COLOR_SECOND_COL_OFFSET)) >> COLOR_SECOND_COL_OFFSET;
			if (col_idx_1 != 0)
			{
				set_address_window(&cursor, &addr_size);
				spi_write16(color_palette[col_idx_1]);
			}
			incr_cursor;
			if (col_idx_2 != 0)
			{
				set_address_window(&cursor, &addr_size);
				spi_write16(color_palette[col_idx_2]);
			}
			incr_cursor;
			// If the copy bit is set, write again
			if (byte & (1 << COLOR_COPY_OFFSET))
			{
				if (col_idx_1 != 0)
				{
					set_address_window(&cursor, &addr_size);
					spi_write16(color_palette[col_idx_1]);
				}
				incr_cursor;
				if (col_idx_2 != 0)
				{
					set_address_window(&cursor, &addr_size);
					spi_write16(color_palette[col_idx_2]);
				}
				incr_cursor;
			}
		}
	}

	// Send the transmittion
	spi_end_write();
}

// Init the background
TileMap background = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	&image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, 
	&image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, 

	&image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, 
	&image_sand_grass, &image_sand_grass, &image_sand_grass, &image_sand_grass, &image_sand_grass, &image_sand_grass, &image_sand_grass, &image_sand_grass, &image_sand_grass, &image_sand_grass, &image_sand_grass, &image_sand_grass, 		
	&image_lake_sand, &image_lake_sand, &image_lake_sand, &image_lake_sand, &image_lake_sand, &image_lake_sand, &image_lake_sand, &image_lake_sand, &image_lake_sand, &image_lake_sand, &image_lake_sand, &image_lake_sand, 
	&image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, 

	&image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, 
	&image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, &image_lake, 
	&image_grass_lake, &image_grass_lake, &image_grass_lake, &image_grass_lake, &image_grass_lake, &image_grass_lake, &image_grass_lake, &image_grass_lake, &image_grass_lake, &image_grass_lake, &image_grass_lake, &image_grass_lake, 
	&image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, &image_grass, 

	&image_road_grass, &image_road_grass, &image_road_grass, &image_road_grass, &image_road_grass, &image_road_grass, &image_road_grass, &image_road_grass, &image_road_grass, &image_road_grass, &image_road_grass, &image_road_grass,
	&image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, 
	&image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, &image_road_middle, 
	&image_sidewalk_road, &image_sidewalk_road, &image_sidewalk_road, &image_sidewalk_road, &image_sidewalk_road, &image_sidewalk_road, &image_sidewalk_road, &image_sidewalk_road, &image_sidewalk_road, &image_sidewalk_road, &image_sidewalk_road, &image_sidewalk_road, 
};

void init_gfx()
{
	init_spi(); // Initialize the tft
}

void draw_image(BasicImage *img)
{
	draw_bitmap_P(
		img->raw->data,
		img->raw->len,
		&img->position,
		&img->raw->size);
}

void draw_image_mask(BasicImage *img)
{
	draw_bitmap_mask_P(
		img->raw->data,
		img->raw->len,
		&img->position,
		&img->raw->size);
}

void draw_behind(BasicImage *img)
{
	uint8_t begin_x = img->position.x / 20;
	uint8_t begin_y = img->position.y / 20;
	uint8_t end_x = begin_x + img->raw->size.x / 20;
	uint8_t end_y = begin_y + img->raw->size.y / 20;
	Vector2 size = {20, 20};
	
	for (uint8_t x = begin_x; x < end_x; x++)
	{
		for (uint8_t y = begin_y; y < end_y; y++)
		{
			Vector2 position = {x * 20, y * 20};
			RawImage* image = background[ y * 12 + x ];
			draw_bitmap_P(
				image->data,
				image->len,
				&position,
				&size
			);
		}
	}
}

void move_image(BasicImage *img, Vector2 *new_pos)
{
	draw_behind(img);
	img->position.x = new_pos->x;
	img->position.y = new_pos->y;
	draw_image_mask(img);
}

#define DRAW_TILEMAP(func)                      \
	Vector2 position = {0, 0};                  \
	Vector2 size = {20, 20};                    \
	for (uint8_t idx = 0; idx < 12 * 16; idx++) \
	{                                           \
		if (map[idx])                           \
		{                                       \
			position.x = (idx % 12) * 20;       \
			position.y = (idx / 12) * 20;       \
			func(                               \
				map[idx]->data,                 \
				map[idx]->len,                  \
				&position,                      \
				&size);                         \
		}                                       \
	}

void draw_tilemap(TileMap map)
{
	DRAW_TILEMAP(draw_bitmap_P)
}

void draw_tilemap_mask(TileMap map)
{
	DRAW_TILEMAP(draw_bitmap_mask_P)
}

// This takes a uint8_t and not a Vector2 to reduce memory usage
void draw_tile(TileMap map, Vector2 pos)
{
	Vector2 size = {20, 20};
	RawImage* raw = map[ pos.y * 12 + pos.x ];
	pos.x *= 20;
	pos.y *= 20;
	draw_bitmap_P(
		raw->data,
		raw->len,
		&pos,
		&size);
}

void draw_tile_mask(TileMap map, Vector2 pos)
{
	Vector2 size = {20, 20};
	RawImage* raw = map[ pos.y * 12 + pos.x ];
	pos.x *= 20;
	pos.y *= 20;
	draw_bitmap_mask_P(
		raw->data,
		raw->len,
		&pos,
		&size);
}
