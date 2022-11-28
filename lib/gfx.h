
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

// Translate a pos with a size to a 1D array pointer
// @param base The pointer to the start of the array
// @param pos The position in the array (expressed in x/y)
// @param size The size of the array (expressed in width/height). THIS ASSUMES A POINTER.
#define VECTOR2_TO_PTR(base, pos, size) (base + (pos.x + pos.y * (size)->x))

// Same as VECTOR2_TO_PTR but it returns the color associated with the pointer.
// @see VECTOR2_TO_PTR
#define VECTOR2_TO_COLOR(base, pos, size) ((uint16_t)*VECTOR2_TO_PTR(base, pos, size))

// Set a tile of a tilemap to a specific image
// This define REQUIRES new_tile to be a pointer
#define SET_TILE(tilemap, vec, new_tile)    \
	tilemap[vec.y * 12 + vec.x] = new_tile; \
	draw_tile(tilemap, vec);

// An image construction macro
#define NEW_IMAGE(var_name, x, y, image_name) \
	BasicImage var_name = {                   \
		Vector2{x, y},                        \
		&image_name};

// A base struct for all drawable things
#define __IMAGE_BASE__ \
	Vector2 position;  \
	RawImage *raw;

// Image struct
typedef struct
{
	__IMAGE_BASE__
} BasicImage;

// We only use tilemaps covering the entire screen, so we know each tile contains 20x20 pixels
// We also know each tilemap has 12x16 tiles
typedef RawImage *TileMap[];

extern TileMap background;
// The background is index 0
// The foreground is index 1
// Possibly use union?
extern uint16_t text_color[2];

void init_gfx();

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
void draw_tilemap(TileMap map);
// Draw an entire tilemap, but the first color will be transparent
void draw_tilemap_mask(TileMap map);
// Draw a single tile of a tilemap
void draw_tile(TileMap map, Vector2 pos);
// Draw a single tile of a tilemap, but the first color will be transparent
void draw_tile_mask(TileMap map, Vector2 pos);

void draw_string(Vector2 position, char *string);
void draw_char(Vector2 *position, char c);

#endif
