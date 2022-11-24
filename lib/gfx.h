
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

// Typecast const uint8_t[] into ImageBytes, which is a costless convertion
#define GET_IMAGE(img_name) ((ImageBytes)(&img_name))

// Simplistic image re-definitions
typedef uint8_t* ImageBytes;
typedef uint16_t ImageLength;

// A simple vector2 struct
typedef struct Vector2 {
	uint16_t x;
	uint16_t y;
} Vector2;

// A base struct for all drawable things
#define DRAWABLE_BASE(inherit) \
	Vector2 position; \
	Vector2 size; \

// Image struct
typedef struct DrawableImage {
	DRAWABLE_BASE(DrawableImage)
	ImageBytes img;
} DrawableImage;

typedef struct DrawableImageRect {
	DRAWABLE_BASE(DrawableImageRect)
	ImageBytes img;
	Vector2 rect_position;
	Vector2 rect_size;
} DrawableImageRect;

// The screen, it's not adviced to modify the screen directly, but rather use the functions defined here
extern Adafruit_ILI9341 tft;

void init_gfx();

void draw_image(DrawableImage *img, ImageLength len);

#endif
