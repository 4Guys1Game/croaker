
#ifndef __GFX_LIB__
#define __GFX_LIB__

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Images
#include <avr/pgmspace.h>
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

// An image construction macro
#define NEW_IMAGE(type, var_name, x, y, image_name) \
type var_name = { \
	Vector2 { x, y }, \
	&image_name \
}; \

// A base struct for all drawable things
#define __IMAGE_BASE__ \
	Vector2 position; \
	RawImage *raw; \

// Image struct
typedef struct {
	__IMAGE_BASE__
} BasicImage;

typedef struct {
	__IMAGE_BASE__
	Vector2 rect_position;
	Vector2 rect_size;
} ImageSegment;

// The screen, it's not adviced to modify the screen directly, but rather use the functions defined here
extern Adafruit_ILI9341 tft;

void init_gfx();

void draw_image(BasicImage *img);

#endif
