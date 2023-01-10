
#ifndef __PRELUDE__
#define __PRELUDE__

#include <stdint.h>
#include <avr/eeprom.h>

// Simplistic image definitions
typedef uint8_t *ImageBytes;
typedef uint16_t ImageLength;

// A simple vector2 struct
typedef struct
{
	int16_t x;
	int16_t y;
} Vector2;

// A raw image data struct
typedef struct
{
	ImageBytes data;
	ImageLength len;
	Vector2 size;
} RawImage;

// Image struct
typedef struct
{
	Vector2 position;
	RawImage *raw;
} BasicImage;

typedef struct {
	Vector2 spawn;
	BasicImage image;
} Player;

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define SCREEN_WIDTH_TILE 12
#define SCREEN_HEIGHT_TILE 16

#define SCREEN_MAX_TILE_X (SCREEN_WIDTH - 20)
#define SCREEN_MAX_TILE_Y (SCREEN_HEIGHT - 20)
#define SCREEN_MIN_TILE_X 0
#define SCREEN_MIN_TILE_Y 40

#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))
#define CLAMP_SCREEN_X(x) CLAMP(x, SCREEN_MIN_TILE_X, SCREEN_MAX_TILE_X)
#define CLAMP_SCREEN_Y(y) CLAMP(y, SCREEN_MIN_TILE_Y, SCREEN_MAX_TILE_Y)
#define CLAMP_SCREEN(vec)              \
	{                                  \
		vec.x = CLAMP_SCREEN_X(vec.x); \
		vec.y = CLAMP_SCREEN_X(vec.y); \
	}

#define END_STATUS 222
#define ACKNOWLEDGEMENT_STATUS 233
#define NEXT_LEVEL_STATUS 244
#define DISCONNECT_STATUS 250

#endif
