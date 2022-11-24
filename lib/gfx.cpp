
#include "gfx.h"

#define BYTE_TYPE_OFFSET 7
#define COLOR_FIRST_COL_OFFSET 4
#define COLOR_SECOND_COL_OFFSET 0
#define COLOR_COPY_OFFSET 3
#define RANGE_COL_OFFSET 0
#define RANGE_RANGE_OFFSET 3

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// // Same as draw_bitmap, but handles bitmaps stored in PROGMEM
// void draw_bitmap_P(uint16_t *bitmap, Vector2 *position, Vector2 *size)
// {
// 	for (uint16_t h = 0; h < size->y; h++)
// 	{
// 		for (uint16_t w = 0; w < size->x; w++)
// 		{
// 			Vector2 img_pos = {w, h};
// 			uint16_t color = pgm_read_dword(VECTOR2_TO_PTR(bitmap, img_pos, size));
// 			tft.drawPixel(position->x + w, position->y + h, color);
// 		}
// 	}
// }

// // Same as draw_bitmap_rect, but handles bitmaps stored in PROGMEM
// void draw_bitmap_rect_P(uint16_t *bitmap, Vector2 position, Vector2 *size, Vector2 *rect_pos, Vector2 *rect_size)
// {
// 	for (uint16_t h = 0; h < rect_size->y; h++)
// 	{
// 		for (uint16_t w = 0; w < rect_size->x; w++)
// 		{
// 			Vector2 img_pos = {rect_pos->x + w, rect_pos->y + h};
// 			uint16_t color = pgm_read_dword(VECTOR2_TO_PTR(bitmap, img_pos, size));
// 			tft.drawPixel(position.x + w, position.y + h, color);
// 		}
// 	}
// }

void draw_bitmap_opt_P(ImageBytes opt_bitmap, ImageLength opt_bitmap_size, Vector2 *position, Vector2 *size)
{
	// Retrieve the color palette
	uint16_t color_palette[] = {
		(pgm_read_byte(opt_bitmap + 0) << 8) + pgm_read_byte(opt_bitmap + 1),
		(pgm_read_byte(opt_bitmap + 2) << 8) + pgm_read_byte(opt_bitmap + 3),
		(pgm_read_byte(opt_bitmap + 4) << 8) + pgm_read_byte(opt_bitmap + 5),
		(pgm_read_byte(opt_bitmap + 6) << 8) + pgm_read_byte(opt_bitmap + 7),
		(pgm_read_byte(opt_bitmap + 8) << 8) + pgm_read_byte(opt_bitmap + 9),
		(pgm_read_byte(opt_bitmap + 10) << 8) + pgm_read_byte(opt_bitmap + 11),
		(pgm_read_byte(opt_bitmap + 12) << 8) + pgm_read_byte(opt_bitmap + 13),
		(pgm_read_byte(opt_bitmap + 14) << 8) + pgm_read_byte(opt_bitmap + 15),
	};

	// Start a write message
	tft.startWrite();
    tft.setAddrWindow(position->x, position->y, size->x, size->y);

	for (uint16_t idx = 16; idx < opt_bitmap_size; idx++)
	{
		register uint8_t byte = pgm_read_byte(opt_bitmap + idx);
		// Case 1: RANGE_BYTE
		if (byte & (1 << BYTE_TYPE_OFFSET))
		{
			uint8_t range = (byte & (0b1111 << RANGE_RANGE_OFFSET)) >> RANGE_RANGE_OFFSET;
			uint8_t col_idx = (byte & (0b111 << RANGE_COL_OFFSET)) >> RANGE_COL_OFFSET;
			// Save on creating an extra variable by reusing the range var
			for (range + 1; range > 0; range--)
			{
				tft.SPI_WRITE16(color_palette[col_idx]);
			}
		}
		// Case 2: COLOR_BYTE
		else
		{
			// Retrieve the colors & write to screen
			uint8_t col_idx_1 = (byte & (0b111 << COLOR_FIRST_COL_OFFSET)) >> COLOR_FIRST_COL_OFFSET;
			uint8_t col_idx_2 = (byte & (0b111 << COLOR_SECOND_COL_OFFSET)) >> COLOR_SECOND_COL_OFFSET;
			tft.SPI_WRITE16(color_palette[col_idx_1]);
			tft.SPI_WRITE16(color_palette[col_idx_2]);
			// If the copy bit is set, write again
			if (byte & (1 << COLOR_COPY_OFFSET))
			{
				tft.SPI_WRITE16(color_palette[col_idx_1]);
				tft.SPI_WRITE16(color_palette[col_idx_2]);
			}
		}
	}

	// Send the transmittion
	tft.endWrite();
}


void init_gfx()
{
	tft.begin(); // Initialize the tft
}

void draw_image(BasicImage *img)
{
	draw_bitmap_opt_P(
		img->raw->data,
		img->raw->len,
		&img->position,
		&img->raw->size
	);
}
