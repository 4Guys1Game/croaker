
#include "gfx.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// Draw a bitmap on the screen
void draw_bitmap(uint16_t *bitmap, Vector2 *position, Vector2 *size)
{
	tft.drawRGBBitmap(position->x, position->y, bitmap, size->x, size->y);
}

// Draw a specified rectangle of a bitmap on the screen
void draw_bitmap_rect(uint16_t *bitmap, Vector2 position, Vector2 *size, Vector2 *rect_pos, Vector2 *rect_size)
{
	for (uint16_t h = 0; h < rect_size->y; h++)
	{
		for (uint16_t w = 0; w < rect_size->x; w++)
		{
			Vector2 img_pos = {rect_pos->x + w, rect_pos->y + h};
			tft.drawPixel(position.x + w, position.y + h, VECTOR2_TO_COLOR(bitmap, img_pos, size));
		}
	}
}

// Same as draw_bitmap, but handles bitmaps stored in PROGMEM
void draw_bitmap_P(uint16_t *bitmap, Vector2 *position, Vector2 *size)
{
	for (uint16_t h = 0; h < size->y; h++)
	{
		for (uint16_t w = 0; w < size->x; w++)
		{
			Vector2 img_pos = {w, h};
			uint16_t color = pgm_read_dword(VECTOR2_TO_PTR(bitmap, img_pos, size));
			tft.drawPixel(position->x + w, position->y + h, color);
		}
	}
}

// Same as draw_bitmap_rect, but handles bitmaps stored in PROGMEM
void draw_bitmap_rect_P(uint16_t *bitmap, Vector2 position, Vector2 *size, Vector2 *rect_pos, Vector2 *rect_size)
{
	for (uint16_t h = 0; h < rect_size->y; h++)
	{
		for (uint16_t w = 0; w < rect_size->x; w++)
		{
			Vector2 img_pos = {rect_pos->x + w, rect_pos->y + h};
			uint16_t color = pgm_read_dword(VECTOR2_TO_PTR(bitmap, img_pos, size));
			tft.drawPixel(position.x + w, position.y + h, color);
		}
	}
}

void draw_image(DrawableImage *img)
{
	Vector2 positions[] = {
		{10, 10},
		{40, 10},
		{70, 10},
		{110, 10},
	};
	Vector2 zero_pos = {0, 0};
	Vector2 off_5_pos = {5, 5};
	Vector2 full_img = {20, 20};
	Vector2 half_w_img = {10, 20};
	Vector2 half_h_img = {20, 10};
	Vector2 half_wh_img = {10, 10};

	draw_bitmap_P((uint16_t *)frogge, positions, &full_img);
	draw_bitmap_rect_P((uint16_t *)frogge, positions[1], &full_img, &zero_pos, &half_w_img);
	draw_bitmap_rect_P((uint16_t *)frogge, positions[2], &full_img, &zero_pos, &half_h_img);
	draw_bitmap_rect_P((uint16_t *)frogge, positions[3], &full_img, &off_5_pos, &half_wh_img);
}

void undraw_image(DrawableImage *img)
{
	draw_bitmap(img->img, &img->position, &img->size);
}

DrawableImage background{
	Vector2{0, 0},
	Vector2{10, 5},
	&draw_image,
	nullptr
	// (uint16_t[50]) {
	// 	RGB_TO_COLOR(12, 0, 11), RGB_TO_COLOR(12, 0, 12), RGB_TO_COLOR(12, 0, 13), RGB_TO_COLOR(12, 0, 14), RGB_TO_COLOR(12, 0, 15), RGB_TO_COLOR(12, 63, 16), RGB_TO_COLOR(12, 63, 17), RGB_TO_COLOR(12, 63, 18), RGB_TO_COLOR(12, 63, 19), RGB_TO_COLOR(12, 63, 20),
	// 	RGB_TO_COLOR(14, 0, 11), RGB_TO_COLOR(14, 0, 12), RGB_TO_COLOR(14, 0, 13), RGB_TO_COLOR(14, 0, 14), RGB_TO_COLOR(14, 0, 15), RGB_TO_COLOR(14, 63, 16), RGB_TO_COLOR(14, 63, 17), RGB_TO_COLOR(14, 63, 18), RGB_TO_COLOR(14, 63, 19), RGB_TO_COLOR(14, 63, 20),
	// 	RGB_TO_COLOR(16, 0, 11), RGB_TO_COLOR(16, 0, 12), RGB_TO_COLOR(16, 0, 13), RGB_TO_COLOR(16, 0, 14), RGB_TO_COLOR(16, 0, 15), RGB_TO_COLOR(16, 63, 16), RGB_TO_COLOR(16, 63, 17), RGB_TO_COLOR(16, 63, 18), RGB_TO_COLOR(16, 63, 19), RGB_TO_COLOR(16, 63, 20),
	// 	RGB_TO_COLOR(18, 0, 11), RGB_TO_COLOR(18, 0, 12), RGB_TO_COLOR(18, 0, 13), RGB_TO_COLOR(18, 0, 14), RGB_TO_COLOR(18, 0, 15), RGB_TO_COLOR(18, 63, 16), RGB_TO_COLOR(18, 63, 17), RGB_TO_COLOR(18, 63, 18), RGB_TO_COLOR(18, 63, 19), RGB_TO_COLOR(18, 63, 20),
	// 	RGB_TO_COLOR(20, 0, 11), RGB_TO_COLOR(20, 0, 12), RGB_TO_COLOR(20, 0, 13), RGB_TO_COLOR(20, 0, 14), RGB_TO_COLOR(20, 0, 15), RGB_TO_COLOR(20, 63, 16), RGB_TO_COLOR(20, 63, 17), RGB_TO_COLOR(20, 63, 18), RGB_TO_COLOR(20, 63, 19), RGB_TO_COLOR(20, 63, 20),
	// }
};

void init_gfx()
{
	tft.begin(); // Initialize the tft
}
