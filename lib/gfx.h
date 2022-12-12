
#ifndef __GFX_LIB__
#define __GFX_LIB__

#include <avr/pgmspace.h>

#include "display_driver.h"
// Images
#include "images.h"

// ILI screen resolution
// 240x320

// A macro converting any rgb pair into a valid color code
// One must provid one of the following valid ranges, the resulting color is undefined if these ranges are not followed
// @param r Red color, valid range: [0..31]
// @param g Green color, valid range: [0..63]
// @param b Blue color, valid range: [0..31]
#define RGB_TO_COLOR(r, g, b) ((uint16_t)(r * 2048 + g * 32 + b))

// An image construction macro
#define NEW_IMAGE(var_name, x, y, image_name) \
	BasicImage var_name = {                   \
		Vector2{x, y},                        \
		&image_name};

// We only use tilemaps covering the entire screen, so we know each tile contains 20x20 pixels
// We also know each tilemap has 12x16 tiles
typedef struct {
	uint8_t tiles[12 * 16 / 2];
	RawImage *sprites[15];
} TileMap;

extern TileMap background;
// The background is index 0
// The foreground is index 1
// Possibly use union?
extern uint16_t text_color[2];

extern TileMap foreground;
extern uint16_t text_color[2];

void init_gfx();

void set_tile(TileMap *map, Vector2 pos, uint8_t new_id);

// This function must be wrapped with spi_begin_write() and spi_end_write()
void set_address_window(Vector2 *position, Vector2 *size);

// Draws the tiles behind this image
void draw_behind(BasicImage *img);
void move_image(BasicImage *img, Vector2 *new_position);

// Draw a single image
void draw_image(BasicImage *img);
// Draw a single image, but the first color will be transparent
void draw_image_mask(BasicImage *img);

// Draw an entire tilemap
void draw_tilemap(TileMap *map);
// Draw an entire moving tilemap
void draw_movingtilemap(TileMap *map);
// Draw a single tile of a tilemap
void draw_tile(TileMap *map, Vector2 pos);
// The same as draw_tile, but it doesn't draw tiles with id 0 (=no texture)
void draw_tile_checked(TileMap *map, Vector2 pos);

void draw_string(Vector2 position, char *string);
void draw_char(Vector2 *position, char c);

#endif
