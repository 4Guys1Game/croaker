
#include "gfx.h"

#define BYTE_TYPE_OFFSET 7
#define COLOR_FIRST_COL_OFFSET 4
#define COLOR_SECOND_COL_OFFSET 0
#define COLOR_COPY_OFFSET 3
#define RANGE_COL_OFFSET 0
#define RANGE_RANGE_OFFSET 3

uint16_t text_color[] = {
	RGB_TO_COLOR(0, 0, 0),
	RGB_TO_COLOR(31, 63, 31)};

void set_address_window(Vector2 *position, Vector2 *size)
{
	display_send_command(CMD_COLUMN_ADDRESS_SET);
	spi_write16(position->x);
	spi_write16(position->x + size->x - 1);

	display_send_command(CMD_PAGE_ADDRESS_SET);
	spi_write16(position->y);
	spi_write16(position->y + size->y - 1);

	display_send_command(CMD_MEMORY_WRITE);
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
	display_begin_write();
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
	display_end_write();
}

void draw_bitmap_mask_P(ImageBytes image, ImageLength image_len, Vector2 *position, Vector2 *size)
{
#define INCR_CURSOR                            \
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
	display_begin_write();
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
					INCR_CURSOR;
				}
			}
			else
			{
				for (range + 1; range > 0; range--)
				{
					INCR_CURSOR;
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
			INCR_CURSOR;
			if (col_idx_2 != 0)
			{
				set_address_window(&cursor, &addr_size);
				spi_write16(color_palette[col_idx_2]);
			}
			INCR_CURSOR;
			// If the copy bit is set, write again
			if (byte & (1 << COLOR_COPY_OFFSET))
			{
				if (col_idx_1 != 0)
				{
					set_address_window(&cursor, &addr_size);
					spi_write16(color_palette[col_idx_1]);
				}
				INCR_CURSOR;
				if (col_idx_2 != 0)
				{
					set_address_window(&cursor, &addr_size);
					spi_write16(color_palette[col_idx_2]);
				}
				INCR_CURSOR;
			}
		}
	}

	// Send the transmittion
	display_end_write();
}

void init_gfx()
{
	init_display(); // Initialize the tft
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
	uint8_t end_x = (img->position.x + img->raw->size.x - 1) / 20;
	uint8_t end_y = (img->position.y + img->raw->size.y - 1) / 20;
	Vector2 size = {20, 20};

	for (uint8_t x = begin_x; x <= end_x; x++)
	{
		for (uint8_t y = begin_y; y <= end_y; y++)
		{
			draw_tile(&background, {x, y});
			draw_tile_checked(&foreground, {x, y});
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

void move_image_check(BasicImage *img, Vector2 *new_pos)
{
	if (new_pos->x != img->position.x || new_pos->y != img->position.y)
	{
		draw_behind(img);
		img->position.x = new_pos->x;
		img->position.y = new_pos->y;
		draw_image_mask(img);
	}
}

void draw_tilemap(TileMap *map)
{
	Vector2 position = {0, 0};
	Vector2 size = {20, 20};
	for (uint8_t idx = 0; idx < 12 * 16 / 2; idx++)
	{
		uint8_t tile1_id = (map->tiles[idx] & 0xf0) >> 4;

		if (tile1_id)
		{
			position.x = ((idx * 2) % 12) * 20;
			position.y = ((idx * 2) / 12) * 20;
			RawImage *texture = map->sprites[tile1_id - 1];
			draw_bitmap_P(
				texture->data,
				texture->len,
				&position,
				&size);
		}
		uint8_t tile2_id = map->tiles[idx] & 0x0f;
		if (tile2_id)
		{
			position.x = ((idx * 2 + 1) % 12) * 20;
			position.y = ((idx * 2 + 1) / 12) * 20;
			RawImage *texture = map->sprites[tile2_id - 1];
			draw_bitmap_P(
				texture->data,
				texture->len,
				&position,
				&size);
		}
	}
}

void set_tile(TileMap *map, Vector2 pos, uint8_t new_id)
{
	Vector2 size = {20, 20};
	uint16_t index = pos.y * 6 + pos.x / 2;
	if(pos.x % 2)
	{
		map->tiles[index] &= ~0x0f;
		map->tiles[index] |= new_id & 0x0f;
	}
	else
	{
		map->tiles[index] &= ~0xf0;
		map->tiles[index] |= new_id << 4;
	}
}

void draw_tile(TileMap *map, Vector2 pos)
{
	Vector2 size = {20, 20};
	uint16_t index = pos.y * 6 + pos.x / 2;
	uint8_t tile_id = (pos.x % 2) ? (map->tiles[index] & 0x0f) : ((map->tiles[index] & 0xf0) >> 4);
	RawImage *raw = map->sprites[tile_id - 1];
	pos.x *= 20;
	pos.y *= 20;
	draw_bitmap_P(
		raw->data,
		raw->len,
		&pos,
		&size);
}

void draw_tile_checked(TileMap *map, Vector2 pos)
{
	Vector2 size = {20, 20};
	uint16_t index = pos.y * 6 + pos.x / 2;
	uint8_t tile_id = (pos.x % 2) ? (map->tiles[index] & 0x0f) : ((map->tiles[index] & 0xf0) >> 4);
	if (tile_id == 0)
	{
		return;
	}
	RawImage *raw = map->sprites[tile_id - 1];
	pos.x *= 20;
	pos.y *= 20;
	draw_bitmap_P(
		raw->data,
		raw->len,
		&pos,
		&size);
}

void draw_font_image_P(ImageBytes image, Vector2 *position, Vector2 *size)
{
	uint8_t image_len = pgm_read_byte(image) + 1;

	// Start a write message
	display_begin_write();
	set_address_window(position, size);

	for (uint16_t idx = 1; idx < image_len; idx++)
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
				spi_write16(text_color[col_idx]);
			}
		}
		// Case 2: COLOR_BYTE
		else
		{
			// Retrieve the colors & write to screen
			uint8_t col_idx_1 = (byte & (0b111 << COLOR_FIRST_COL_OFFSET)) >> COLOR_FIRST_COL_OFFSET;
			uint8_t col_idx_2 = (byte & (0b111 << COLOR_SECOND_COL_OFFSET)) >> COLOR_SECOND_COL_OFFSET;
			spi_write16(text_color[col_idx_1]);
			spi_write16(text_color[col_idx_2]);
			// If the copy bit is set, write again
			if (byte & (1 << COLOR_COPY_OFFSET))
			{
				spi_write16(text_color[col_idx_1]);
				spi_write16(text_color[col_idx_2]);
			}
		}
	}

	// Send the transmittion
	display_end_write();
}

void draw_string(Vector2 position, char *string)
{
	while (*string)
	{
		draw_char(&position, *string);
		position.x += 10;
		string++;
	}
}

void draw_char(Vector2 *position, char chr)
{
#define FONT_SWITCH_CASE(idx, letter)                                            \
	case idx:                                                                    \
		draw_font_image_P((ImageBytes)__raw_font_##letter##_p, position, &size); \
		break;

	if (chr >= '0' && chr <= '9')
	{
		chr -= '0';
	}
	else if (chr >= 'a' && chr <= 'z')
	{
		chr = chr - 'a' + 10;
	}
	else if (chr >= 'A' && chr <= 'Z')
	{
		chr = chr - 'A' + 10;
	}
	else
	{
		// Don't draw anything if it's not a character we can draw
		return;
	}
	Vector2 size = {10, 14};

	switch (chr)
	{
		FONT_SWITCH_CASE(0, 0)
		FONT_SWITCH_CASE(1, 1)
		FONT_SWITCH_CASE(2, 2)
		FONT_SWITCH_CASE(3, 3)
		FONT_SWITCH_CASE(4, 4)
		FONT_SWITCH_CASE(5, 5)
		FONT_SWITCH_CASE(6, 6)
		FONT_SWITCH_CASE(7, 7)
		FONT_SWITCH_CASE(8, 8)
		FONT_SWITCH_CASE(9, 9)
		FONT_SWITCH_CASE(10, a)
		FONT_SWITCH_CASE(11, b)
		FONT_SWITCH_CASE(12, c)
		FONT_SWITCH_CASE(13, d)
		FONT_SWITCH_CASE(14, e)
		FONT_SWITCH_CASE(15, f)
		FONT_SWITCH_CASE(16, g)
		FONT_SWITCH_CASE(17, h)
		FONT_SWITCH_CASE(18, i)
		FONT_SWITCH_CASE(19, j)
		FONT_SWITCH_CASE(20, k)
		FONT_SWITCH_CASE(21, l)
		FONT_SWITCH_CASE(22, m)
		FONT_SWITCH_CASE(23, n)
		FONT_SWITCH_CASE(24, o)
		FONT_SWITCH_CASE(25, p)
		FONT_SWITCH_CASE(26, q)
		FONT_SWITCH_CASE(27, r)
		FONT_SWITCH_CASE(28, s)
		FONT_SWITCH_CASE(29, t)
		FONT_SWITCH_CASE(30, u)
		FONT_SWITCH_CASE(31, v)
		FONT_SWITCH_CASE(32, w)
		FONT_SWITCH_CASE(33, x)
		FONT_SWITCH_CASE(34, y)
		FONT_SWITCH_CASE(35, z)
	default:
		break;
	}
}

void draw_rect(Vector2 *position, Vector2 *width, register uint16_t color)
{
	display_begin_write();
	set_address_window(position, width);

	uint16_t count_to = width->x * width->y;
	for (uint16_t count = 0; count < count_to; count++)
	{
		spi_write16(color);
	}

	display_end_write();
}
