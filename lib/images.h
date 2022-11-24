
#ifndef __IMAGES__
#define __IMAGES__

#include <avr/pgmspace.h>
#include "prelude.h"

// Typecast const uint8_t[] into ImageBytes, which is a costless convertion
#define GET_IMAGE(img_name) ((ImageBytes)(__raw_ ## img_name ## _p))

// A raw image data struct
typedef struct
{
	ImageBytes data;
	ImageLength len;
	Vector2 size;
} RawImage;

// AUTO-GENERATED IMAGE CONVERTED FROM: frogge.bmp
PROGMEM const uint8_t __raw_frogge_p[134] = {
	0xff, 0xff, 0x4f, 0xe0, 0x03, 0xe1, 0x00, 0x00, 0xf8, 0x0d, 0x23, 0xe0, 0x00, 0x00, 0x00, 0x00,
	0xb8, 0x19, 0xf8, 0x11, 0x22, 0xa9, 0xc8, 0x11, 0x12, 0xb2, 0x11, 0xb8, 0x11, 0xd2, 0x11, 0xb0, 0x12, 0x20, 0x02, 0x22, 0x20, 0x02, 0x21, 0xb0, 0x12, 0x20, 0x32, 0x22, 0x23, 0x02, 0x21, 0xb0, 0x12, 0xda, 0x11, 0x08, 0x11, 0xaa, 0x33, 0xb2, 0x10, 0x00, 0x01, 0xf2, 0x10, 0x00, 0x01, 0x22, 0x23, 0x22, 0x33, 0x22, 0x32, 0x22, 0x10, 0x00, 0x01, 0x2a, 0x33, 0x44, 0x33, 0x22, 0x21, 0x10, 0x00, 0x01, 0x12, 0x2a, 0x44, 0x2a, 0x51, 0xb0, 0x12, 0x2a, 0x44, 0x2a, 0x10, 0xb0, 0x11, 0xc2, 0xa9, 0xa8, 0xd9, 0x22, 0x21, 0x10, 0x01, 0x19, 0x00, 0xb1, 0xaa, 0x11, 0x12, 0x22, 0x11, 0xb0, 0x11, 0x2a, 0x11, 0x2a, 0x11, 0xb8, 0x12, 0x22, 0x21, 0x11, 0x22, 0x21, 0xc0, 0x11, 0x21, 0x11, 0x01, 0x19, 0xc8, 0x11, 0x10, 0x08
};
extern RawImage frogge;

PROGMEM const uint8_t image[] = {
	// First 8 bytes are colors
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
	// Colormap
	// The colormap uses the following format;

	// COLOR BYTE
	// [ RESV | COL1 | COL2 | COL3 | COPY | COL1 | COL2 | COL3 ]
	//
	// The first bit is always 0, the following 3 bits are
	// are the palette index. Then the following bit indicates if
	// the 4 pixels (the two defined in this byte, and the two
	// pixels after) match a xoxo pattern. Otherwise this is set
	// to zero. After this bit, another 3 bits are used for
	// the next pixel color.

	// RANGE BYTE
	// [ RESV | RAN1 | RAN2 | RAN3 | RAN4 | COL1 | COL2 | COL3 ]
	//
	// The first bit is always 1, the 4 bits after are used to
	// indicate how many following pixels should use the same color.
	// The remaining 3 bits are the color palette index to repeat.
};

#endif
