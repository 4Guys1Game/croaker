
#ifndef __IMAGES__
#define __IMAGES__

#include <avr/pgmspace.h>
#include "prelude.h"

// Typecast const uint8_t[] into ImageBytes, which is a costless conversion
#define GET_IMAGE(img_name) ((ImageBytes)(__raw_ ## img_name ## _p))

// AUTO-GENERATED IMAGE CONVERTED FROM: frogge.bmp
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_frogge;
PROGMEM const uint8_t __raw_frogge_p[126] = {
	0xff, 0xff, 0x4f, 0xe0, 0x03, 0xe1, 0x00, 0x00, 0xf8, 0x0d, 0x23, 0xe0, 0x00, 0x00, 0x00, 0x00,
	0xb8, 0xa1, 0xf8, 0x91, 0x92, 0xa9, 0xc8, 0x99, 0xba, 0x91, 0xb8, 0x91, 0xd2, 0x91, 0xb0, 0x12, 0x20, 0x02, 0x9a, 0x90, 0x92, 0x10, 0xa8, 0x12, 0x20, 0x32, 0x9a, 0x30, 0x92, 0x10, 0xa8, 0x12, 0xda, 0x91, 0xa0, 0x91, 0xaa, 0x93, 0xb2, 0x10, 0x98, 0x12, 0xea, 0x10, 0x98, 0x12, 0x92, 0x32, 0x23, 0x32, 0x23, 0x9a, 0x10, 0x98, 0x12, 0x9a, 0x93, 0x94, 0x93, 0x9a, 0x91, 0xa0, 0x91, 0xaa, 0x94, 0xa2, 0x51, 0xb0, 0x12, 0xa2, 0x94, 0xa2, 0x10, 0xb0, 0x91, 0xc2, 0xa9, 0xa8, 0xd9, 0x9a, 0x91, 0x90, 0xa9, 0x90, 0xb1, 0xaa, 0x99, 0x9a, 0x91, 0xb0, 0x91, 0xa2, 0x91, 0xa2, 0x91, 0xb8, 0x12, 0x9a, 0x99, 0x9a, 0x10, 0xb8, 0x91, 0x21, 0x91, 0x01, 0xa1, 0xc8, 0x99, 0x90
};

// AUTO-GENERATED IMAGE CONVERTED FROM: grass.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_grass;
PROGMEM const uint8_t __raw_grass_p[88] = {
	0x04, 0xe1, 0x04, 0x61, 0x03, 0xe1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xa8, 0xa9, 0xf0, 0x99, 0x92, 0x99, 0xd0, 0x99, 0xb2, 0x99, 0xc0, 0x91, 0xc2, 0x91, 0xb8, 0x99, 0xca, 0x10, 0xb0, 0x99, 0xca, 0x10, 0xb8, 0x91, 0xba, 0x99, 0xc0, 0x99, 0xaa, 0x91, 0xd8, 0xc1, 0xe8, 0xb1, 0xb8, 0xa9, 0xf0, 0x91, 0x9a, 0x91, 0xe0, 0x91, 0xaa, 0x10, 0xd0, 0x91, 0xb2, 0x91, 0xc0, 0x99, 0xba, 0x91, 0xc0, 0x99, 0xba, 0x99, 0xc0, 0x99, 0xb2, 0x99, 0xc8, 0x91, 0xaa, 0x99, 0xd8, 0xa1, 0x21, 0x91, 0xf0, 0x99, 0xf8, 0xa8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: grass_lake.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_grass_lake;
PROGMEM const uint8_t __raw_grass_lake_p[58] = {
	0x04, 0x9f, 0x03, 0xfa, 0x04, 0x61, 0x04, 0xe1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xa0, 0x99, 0xf8, 0xb9, 0xb0, 0xa1, 0x90, 0x91, 0x92, 0x32, 0xb1, 0x90, 0x92, 0xa9, 0x23, 0xab, 0x92, 0xa1, 0x9a, 0xf3, 0x9a, 0xfb, 0xab
};

// AUTO-GENERATED IMAGE CONVERTED FROM: lake.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_lake;
PROGMEM const uint8_t __raw_lake_p[43] = {
	0x04, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xd0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: lake_sand.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_lake_sand;
PROGMEM const uint8_t __raw_lake_sand_p[54] = {
	0xfe, 0x4d, 0x03, 0xfa, 0x04, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xf8, 0xf8, 0xe0, 0xa9, 0xf0, 0x99, 0x92, 0x91, 0xa0, 0xa9, 0x98, 0x91, 0xaa, 0xb9, 0xa2, 0x91, 0xca, 0x99, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0x9a
};

// AUTO-GENERATED IMAGE CONVERTED FROM: road_grass.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_road_grass;
PROGMEM const uint8_t __raw_road_grass_p[59] = {
	0x04, 0xe1, 0x03, 0xe1, 0x01, 0x60, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xf8, 0xf8, 0xf8, 0xd0, 0x99, 0x90, 0x91, 0xa0, 0xf9, 0xf9, 0x91, 0x9a, 0xc1, 0xaa, 0x91, 0xba, 0xa1, 0x9a, 0x93, 0xc2, 0x93, 0xb2, 0xbb, 0x92, 0xbb, 0x9a, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xc3, 0xd4, 0xab
};

// AUTO-GENERATED IMAGE CONVERTED FROM: road_middle.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_road_middle;
PROGMEM const uint8_t __raw_road_middle_p[45] = {
	0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xa8, 0xd1, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xd0, 0xd1, 0xa8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: sand_grass.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_sand_grass;
PROGMEM const uint8_t __raw_sand_grass_p[74] = {
	0x04, 0xe1, 0x04, 0x61, 0x03, 0xe1, 0xfe, 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xa0, 0x91, 0xf8, 0x01, 0xa1, 0xf0, 0x91, 0x9a, 0x10, 0xa8, 0xa1, 0xa0, 0x12, 0x9a, 0x10, 0x98, 0x99, 0x9a, 0x10, 0x90, 0x12, 0x92, 0x91, 0xa0, 0x12, 0xa2, 0x10, 0x98, 0xa1, 0xa8, 0x91, 0xa2, 0x10, 0xf0, 0x01, 0x91, 0xf8, 0xf8, 0xf8, 0xab, 0xb8, 0xa3, 0x90, 0xcb, 0xa0, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xbb
};

// AUTO-GENERATED IMAGE CONVERTED FROM: sidewalk_road.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_sidewalk_road;
PROGMEM const uint8_t __raw_sidewalk_road_p[70] = {
	0x00, 0x00, 0xff, 0xff, 0x01, 0x60, 0x75, 0x0e, 0xb5, 0xd6, 0x7b, 0xef, 0x4b, 0xea, 0x00, 0x00,
	0xa8, 0xd1, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x90, 0x92, 0xc0, 0xa2, 0xa8, 0xaa, 0x90, 0x92, 0x34, 0x43, 0x9b, 0xb4, 0x93, 0xa4, 0x35, 0x9d, 0x96, 0x9d, 0x45, 0x56, 0x65, 0xa5, 0x45, 0xc5, 0x45, 0xc5, 0x45, 0xc5, 0x45, 0xc5, 0x45, 0xc5, 0x45, 0xc5, 0x8c
};


// AUTO-GENERATED IMAGE CONVERTED FROM: font_0.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_0_p[] = {
	65 - 16,
	0xe8, 0xa1, 0xa8, 0x91, 0x90, 0x91, 0xa0, 0x10, 0x90, 0x91, 0xa0, 0x10, 0x90, 0x99, 0x90, 0x91, 0x90, 0x10, 0x91, 0x90, 0x91, 0x90, 0x10, 0x91, 0x90, 0x91, 0x01, 0x90, 0x91, 0x90, 0x91, 0x01, 0x90, 0x91, 0x90, 0x99, 0x98, 0x91, 0x98, 0x91, 0x98, 0x10, 0x98, 0x91, 0x90, 0x91, 0xa8, 0xa1, 0xe8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_1.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_1_p[] = {
	42 - 16,
	0xf8, 0x10, 0xb0, 0x99, 0xb0, 0x91, 0x01, 0xc8, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xa8, 0xb9, 0xd8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_2.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_2_p[] = {
	45 - 16,
	0xe8, 0x99, 0xa8, 0x91, 0x98, 0x91, 0x98, 0x10, 0x98, 0x91, 0xc8, 0x10, 0xb8, 0x91, 0xc0, 0x91, 0xb8, 0x91, 0xc0, 0x10, 0xb8, 0x10, 0xb8, 0x10, 0xb8, 0x10, 0xb8, 0xb9, 0xe0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_3.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_3_p[] = {
	45 - 16,
	0xe8, 0x99, 0xa8, 0x91, 0x98, 0x91, 0xc8, 0x10, 0xc0, 0x10, 0xb8, 0x91, 0xb0, 0x99, 0xc0, 0x99, 0xc8, 0x10, 0xc0, 0x91, 0xc0, 0x10, 0x90, 0x91, 0x98, 0x91, 0xa0, 0xa9, 0xe8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_4.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_4_p[] = {
	47 - 16,
	0xf0, 0x91, 0xc0, 0x10, 0xc0, 0x10, 0xb8, 0x91, 0xc0, 0x10, 0xb8, 0x91, 0x90, 0x10, 0xa0, 0x10, 0x90, 0x10, 0x98, 0x91, 0x98, 0x10, 0x98, 0xc1, 0xb8, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xe0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_5.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_5_p[] = {
	43 - 16,
	0xe0, 0xb1, 0xa0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0xb1, 0xc8, 0x10, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0x90, 0x91, 0x98, 0x91, 0xa0, 0xa9, 0xe8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_6.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_6_p[] = {
	55 - 16,
	0xf0, 0xa1, 0xa8, 0x91, 0x90, 0x10, 0x98, 0x91, 0xc0, 0x10, 0xb8, 0x91, 0x90, 0x91, 0xa0, 0xb9, 0x98, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x98, 0x10, 0x98, 0x91, 0x98, 0x10, 0x98, 0x91, 0x98, 0x91, 0x98, 0x10, 0xa0, 0xa1, 0xe8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_7.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_7_p[] = {
	42 - 16,
	0xe0, 0xb9, 0xc0, 0x91, 0xc0, 0x10, 0xb8, 0x91, 0xc0, 0x10, 0xb8, 0x91, 0xc0, 0x10, 0xb8, 0x91, 0xc0, 0x91, 0xc0, 0x10, 0xb8, 0x91, 0xc0, 0x10, 0xf0, 0x88
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_8.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_8_p[] = {
	59 - 16,
	0xe8, 0xa1, 0xa8, 0x91, 0x90, 0x91, 0xa0, 0x10, 0x98, 0x91, 0x98, 0x10, 0x98, 0x91, 0x98, 0x91, 0x98, 0x10, 0xa0, 0xa1, 0xa8, 0x91, 0x01, 0x91, 0x98, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa8, 0x10, 0x01, 0x10, 0x98, 0x91, 0x98, 0x10, 0x98, 0x91, 0xa0, 0xa9, 0xe0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_9.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_9_p[] = {
	54 - 16,
	0xe8, 0xa1, 0xa8, 0x91, 0x90, 0x91, 0x98, 0x91, 0xa0, 0x10, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x98, 0x91, 0x01, 0x99, 0xa0, 0x99, 0x01, 0xc8, 0x10, 0xb8, 0x91, 0xb0, 0x99, 0xa8, 0x99, 0xf8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_a.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_a_p[] = {
	53 - 16,
	0xf0, 0x91, 0xc0, 0x91, 0xb8, 0xa1, 0xb0, 0x10, 0x01, 0xb0, 0x10, 0x01, 0xa8, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x98, 0x10, 0x98, 0x10, 0x98, 0x10, 0x90, 0xc1, 0x90, 0x91, 0xa8, 0x10, 0x01, 0xb0, 0x10, 0x01, 0xb0, 0x10, 0xd0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_b.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_b_p[] = {
	59 - 16,
	0xe0, 0xa1, 0xb0, 0x10, 0x01, 0x91, 0xa0, 0x10, 0x98, 0x91, 0x98, 0x10, 0x98, 0x91, 0x98, 0x10, 0x98, 0x10, 0x98, 0xa9, 0xa8, 0x10, 0x01, 0x91, 0xa0, 0x10, 0x98, 0x91, 0x98, 0x10, 0xa0, 0x10, 0x90, 0x10, 0xa0, 0x10, 0x90, 0x10, 0x98, 0x91, 0x98, 0xa9, 0xe8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_c.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_c_p[] = {
	45 - 16,
	0xf0, 0xa1, 0xa8, 0x91, 0x90, 0x91, 0x98, 0x91, 0xb8, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc8, 0x10, 0xc0, 0x91, 0xa0, 0x91, 0xa0, 0xa9, 0xd8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_d.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_d_p[] = {
	59 - 16,
	0xd8, 0xa9, 0xa8, 0xb9, 0x98, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa8, 0x10, 0x01, 0x10, 0xa0, 0x10, 0x01, 0x10, 0xa0, 0x10, 0x01, 0x10, 0xa0, 0x10, 0x01, 0x10, 0xa0, 0x10, 0x01, 0x10, 0x98, 0x91, 0x90, 0x91, 0x98, 0x91, 0x98, 0xb1, 0xe8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_e.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_e_p[] = {
	41 - 16,
	0xe0, 0xb9, 0x98, 0xb9, 0x98, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0xb1, 0xa0, 0xb1, 0xa0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0xb9, 0xd8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_f.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_f_p[] = {
	42 - 16,
	0xe0, 0xb9, 0x98, 0xb9, 0x98, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0xb1, 0xa0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xf8, 0x88
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_g.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_g_p[] = {
	53 - 16,
	0xf0, 0xa1, 0xa0, 0x99, 0x90, 0x91, 0x98, 0x10, 0xb8, 0x91, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0x90, 0xa1, 0x90, 0x10, 0xa8, 0x10, 0x01, 0x10, 0xa0, 0x10, 0x01, 0x10, 0xa0, 0x10, 0x90, 0x91, 0x98, 0x91, 0xa0, 0xa9, 0xe0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_h.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_h_p[] = {
	63 - 16,
	0xd8, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0xc1, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0xd8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_i.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_i_p[] = {
	41 - 16,
	0xe0, 0xb1, 0xb0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xb0, 0xb1, 0xe0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_j.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_j_p[] = {
	43 - 16,
	0xe8, 0xa9, 0xa8, 0xa9, 0xc8, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0x98, 0x10, 0x90, 0x91, 0x98, 0xb1, 0xe8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_k.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_k_p[] = {
	60 - 16,
	0xe0, 0x10, 0xa0, 0x91, 0x90, 0x10, 0x98, 0x91, 0x98, 0x10, 0x90, 0x91, 0xa0, 0x10, 0x01, 0x10, 0xa0, 0x10, 0x91, 0xb0, 0x99, 0xb8, 0x10, 0x91, 0xb0, 0x10, 0x01, 0xb0, 0x10, 0x01, 0x10, 0xa0, 0x10, 0x90, 0x91, 0xa0, 0x10, 0x98, 0x91, 0x98, 0x10, 0xa0, 0x91, 0xd0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_l.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_l_p[] = {
	41 - 16,
	0xe0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0xb9, 0xd8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_m.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_m_p[] = {
	67 - 16,
	0xd8, 0x91, 0xa0, 0x91, 0x90, 0x99, 0x98, 0x91, 0x90, 0x99, 0x90, 0x99, 0x90, 0x10, 0x10, 0x09, 0x90, 0x10, 0x10, 0x09, 0x90, 0x10, 0x10, 0x09, 0x90, 0x10, 0x91, 0x09, 0x90, 0x10, 0x01, 0x10, 0x01, 0x90, 0x10, 0x01, 0x10, 0x01, 0x90, 0x10, 0x01, 0x10, 0x01, 0x10, 0x10, 0xa8, 0x91, 0x01, 0xb0, 0x91, 0xd0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_n.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_n_p[] = {
	70 - 16,
	0xd8, 0x99, 0x98, 0x91, 0x90, 0x99, 0x98, 0x91, 0x90, 0x99, 0x98, 0x91, 0x90, 0xa1, 0x90, 0x91, 0x90, 0x91, 0x01, 0x90, 0x91, 0x90, 0x91, 0x01, 0x10, 0x91, 0x90, 0x91, 0x90, 0x10, 0x91, 0x90, 0x91, 0x90, 0x10, 0x91, 0x90, 0x91, 0x90, 0xa1, 0x90, 0x91, 0x98, 0x10, 0x10, 0x01, 0x10, 0x90, 0x99, 0x90, 0x91, 0xa0, 0x91, 0xd8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_o.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_o_p[] = {
	57 - 16,
	0xe8, 0xa1, 0xa8, 0x91, 0x90, 0x91, 0x98, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa8, 0x10, 0x01, 0xb0, 0x10, 0x01, 0xb0, 0x10, 0x01, 0xb0, 0x10, 0x01, 0xb0, 0x10, 0x01, 0x10, 0xa0, 0x10, 0x01, 0x10, 0x98, 0x91, 0x98, 0x91, 0x98, 0x10, 0xa0, 0xa1, 0xe8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_p.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_p_p[] = {
	52 - 16,
	0xe0, 0xa9, 0xa8, 0x10, 0x90, 0x99, 0x98, 0x10, 0xa0, 0x10, 0x90, 0x10, 0xa0, 0x10, 0x90, 0x10, 0xa0, 0x10, 0x90, 0x10, 0x98, 0x91, 0x98, 0xb9, 0x98, 0xa9, 0xa8, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xf0, 0x90
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_q.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_q_p[] = {
	59 - 16,
	0xe8, 0xa1, 0xa8, 0x91, 0x90, 0x91, 0x98, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa8, 0x10, 0x01, 0xb0, 0x10, 0x01, 0xb0, 0x10, 0x01, 0xb0, 0x10, 0x01, 0xb0, 0x10, 0x01, 0x10, 0xa0, 0x10, 0x01, 0x10, 0x98, 0x91, 0x98, 0x91, 0x98, 0x10, 0xa0, 0xa1, 0xd0, 0x91, 0x88
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_r.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_r_p[] = {
	61 - 16,
	0xe0, 0xa9, 0xa8, 0x10, 0x90, 0x91, 0xa0, 0x10, 0x98, 0x91, 0x98, 0x10, 0xa0, 0x10, 0x90, 0x10, 0x98, 0x91, 0x98, 0x10, 0x98, 0x10, 0x98, 0xa9, 0xa8, 0x10, 0x01, 0x10, 0xa0, 0x10, 0x90, 0x10, 0xa0, 0x10, 0x90, 0x91, 0xa0, 0x10, 0x98, 0x91, 0x98, 0x10, 0xa0, 0x91, 0xd0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_s.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_s_p[] = {
	45 - 16,
	0xe8, 0xa1, 0xa8, 0x91, 0x90, 0x99, 0x90, 0x91, 0xc0, 0x91, 0xc8, 0x91, 0xc8, 0x99, 0xc8, 0x99, 0xc8, 0x91, 0xc8, 0x10, 0xb8, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x98, 0xb1, 0xe0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_t.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_t_p[] = {
	41 - 16,
	0xd8, 0xc9, 0x01, 0xb9, 0xa8, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xf0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_u.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_u_p[] = {
	63 - 16,
	0xd8, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x91, 0xa0, 0x91, 0x98, 0x91, 0x98, 0x10, 0xa0, 0xa1, 0xe8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_v.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_v_p[] = {
	56 - 16,
	0xd0, 0x91, 0xb0, 0x91, 0x01, 0xb0, 0x10, 0x01, 0x10, 0xa0, 0x10, 0x01, 0x10, 0x98, 0x91, 0x98, 0x10, 0x98, 0x10, 0x98, 0x91, 0x98, 0x10, 0x98, 0x91, 0x90, 0x91, 0xa8, 0x10, 0x01, 0xb0, 0x91, 0x01, 0xb0, 0xa1, 0xb8, 0x91, 0xc0, 0x91, 0xf0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_w.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_w_p[] = {
	66 - 16,
	0xd0, 0x91, 0xb8, 0x99, 0xb8, 0x99, 0x90, 0x91, 0x90, 0x91, 0x01, 0x90, 0x91, 0x90, 0x91, 0x01, 0x90, 0x91, 0x90, 0x10, 0x01, 0x90, 0x99, 0x01, 0x90, 0x10, 0x91, 0x09, 0x90, 0x10, 0x10, 0x09, 0x90, 0x99, 0x90, 0x10, 0x10, 0x01, 0x91, 0x90, 0x99, 0x98, 0x91, 0x90, 0x99, 0x98, 0x91, 0x90, 0x91, 0xe0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_x.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_x_p[] = {
	56 - 16,
	0xd8, 0x91, 0xa8, 0x10, 0x90, 0x10, 0x98, 0x91, 0x98, 0x91, 0x90, 0x91, 0xa8, 0x10, 0x01, 0xb0, 0xa1, 0xb8, 0x91, 0xc0, 0x91, 0xb8, 0xa1, 0xb0, 0x10, 0x01, 0x10, 0x98, 0x91, 0x98, 0x10, 0x90, 0x91, 0xa0, 0x91, 0x90, 0x10, 0xa8, 0x91, 0xd0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_y.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_y_p[] = {
	50 - 16,
	0xd0, 0x91, 0xb0, 0x91, 0x01, 0x10, 0xa0, 0x10, 0x90, 0x10, 0x98, 0x91, 0x98, 0x91, 0x98, 0x10, 0xa0, 0x10, 0x01, 0xb0, 0xa1, 0xb8, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xc0, 0x91, 0xf0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: font_z.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
PROGMEM const uint8_t __raw_font_z_p[] = {
	41 - 16,
	0xe0, 0xb9, 0x98, 0xb9, 0xc0, 0x10, 0xb8, 0x91, 0xb8, 0x91, 0xc0, 0x10, 0xb8, 0x91, 0xb8, 0x91, 0xc0, 0x10, 0xb8, 0x91, 0xb8, 0x91, 0xc0, 0xc1, 0xd8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: car-front.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_car_front;
PROGMEM const char __raw_car_front_p[135] = {
	0x00, 0x00, 0xe0, 0xc4, 0xff, 0x60, 0xb8, 0x04, 0x10, 0x82, 0x7b, 0xef, 0x9c, 0xf3, 0x00, 0x00,
	0x90, 0xf9, 0x99, 0x02, 0x9b, 0xb9, 0x94, 0x14, 0xa4, 0x02, 0x9b, 0xb1, 0x45, 0x94, 0x93, 0x91, 0x40, 0xc9, 0x45, 0x65, 0x64, 0x31, 0x94, 0xc9, 0x45, 0xa5, 0x43, 0x14, 0x41, 0xc1, 0x45, 0x6d, 0x43, 0x14, 0xc9, 0x45, 0xad, 0x43, 0x1c, 0xb9, 0x45, 0x6d, 0x43, 0x14, 0x41, 0x41, 0xa9, 0x45, 0xad, 0x43, 0x14, 0x41, 0x41, 0xa9, 0x45, 0x65, 0x65, 0x54, 0x31, 0xa4, 0xb1, 0x45, 0x65, 0x65, 0x54, 0x31, 0xa4, 0xb1, 0x45, 0xad, 0x43, 0x14, 0x41, 0x41, 0xb1, 0x45, 0x6d, 0x43, 0x14, 0x41, 0xc1, 0x45, 0xad, 0x43, 0x14, 0xd1, 0x45, 0x6d, 0x43, 0x14, 0xd1, 0x45, 0xa5, 0x43, 0x14, 0x40, 0xc9, 0x45, 0x65, 0x64, 0x31, 0x94, 0x02, 0x9b, 0xb1, 0x45, 0x94, 0x93, 0x91, 0x40, 0x23, 0x93, 0xb9, 0x41, 0x14, 0xa4, 0x90, 0xf9, 0x99
};

// AUTO-GENERATED IMAGE CONVERTED FROM: car-back.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_car_back;
PROGMEM const char __raw_car_back_p[154] = {
	0xe0, 0xc4, 0x00, 0x00, 0x10, 0xa2, 0xb8, 0x04, 0xff, 0x60, 0x7b, 0xef, 0x9c, 0xf3, 0x00, 0x00,
	0xf8, 0x01, 0x99, 0xa2, 0xc8, 0x9b, 0x41, 0x91, 0x20, 0x90, 0x20, 0x02, 0xa8, 0x9b, 0x41, 0x91, 0xaa, 0x02, 0x52, 0xc0, 0x99, 0x9a, 0x0a, 0x95, 0x20, 0x02, 0x20, 0x98, 0x91, 0x02, 0x28, 0x25, 0x65, 0x28, 0x20, 0x90, 0x91, 0x02, 0x28, 0x25, 0x95, 0x28, 0x20, 0x01, 0x91, 0x02, 0x20, 0x20, 0x02, 0x95, 0x28, 0x20, 0x01, 0x91, 0x02, 0x9a, 0x90, 0x25, 0x52, 0x0a, 0x90, 0x99, 0xaa, 0x90, 0x25, 0x52, 0x0a, 0x90, 0x99, 0xaa, 0x90, 0x25, 0x52, 0x0a, 0x90, 0x99, 0x02, 0x9a, 0x90, 0x25, 0x52, 0x0a, 0x90, 0x99, 0x02, 0x20, 0x20, 0x02, 0x95, 0x28, 0x20, 0x01, 0x91, 0x02, 0x28, 0x25, 0x95, 0x28, 0x20, 0x01, 0x91, 0x02, 0x28, 0x25, 0x65, 0x28, 0x20, 0x90, 0x91, 0x9a, 0x0a, 0x95, 0x20, 0x02, 0x20, 0x98, 0x91, 0xaa, 0x02, 0x52, 0xc0, 0x99, 0x20, 0x90, 0x20, 0x02, 0xa8, 0x9b, 0x41, 0x91, 0xa2, 0xc8, 0x9b, 0x41, 0x91, 0xf8, 0x01, 0x99
};

// AUTO-GENERATED IMAGE CONVERTED FROM: log_back.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_log_back;
PROGMEM const char __raw_log_back_p[112] = {
	0x54, 0x3f, 0x20, 0x80, 0x61, 0xc2, 0x49, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xf8, 0xa8, 0xf9, 0xa8, 0xf2, 0x91, 0xa0, 0x92, 0x32, 0xa2, 0x93, 0xaa, 0x10, 0x98, 0x93, 0x23, 0x32, 0x23, 0xc2, 0x91, 0x90, 0xaa, 0x93, 0xb2, 0x32, 0x9a, 0x10, 0x23, 0xc2, 0x9b, 0x23, 0x9a, 0x10, 0x3a, 0x9b, 0xba, 0x93, 0x9a, 0x12, 0x23, 0x32, 0xa2, 0x9b, 0xba, 0x12, 0xf2, 0x32, 0x92, 0x12, 0x93, 0xa2, 0x32, 0xa2, 0x93, 0xa2, 0x13, 0x92, 0x93, 0x92, 0x93, 0x92, 0x93, 0xb2, 0x12, 0xc2, 0x32, 0xc2, 0x12, 0xc2, 0x32, 0xba, 0x10, 0x92, 0x32, 0xb2, 0x93, 0xb2, 0x10, 0x93, 0x23, 0x92, 0x32, 0xc2, 0x91, 0x90, 0xa2, 0x93, 0xca, 0x10, 0x98, 0xf2, 0x91, 0xa0, 0xf9, 0xf8, 0xd0
};

// AUTO-GENERATED IMAGE CONVERTED FROM: grass_road.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_grass_road;
PROGMEM const char __raw_grass_road_p[80] = {
	0x00, 0x00, 0x9c, 0xf3, 0x7b, 0xef, 0x25, 0x69, 0x0b, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf9, 0xa9, 0x92, 0x12, 0x92, 0x12, 0x92, 0x12, 0x92, 0x12, 0x92, 0x12, 0x92, 0x12, 0x92, 0x12, 0x92, 0x12, 0x92, 0x12, 0x92, 0x12, 0xf9, 0xa9, 0xfb, 0xab, 0x43, 0xf3, 0x9b, 0x9c, 0xfb, 0x34, 0x94, 0xd3, 0x94, 0xb3, 0x43, 0xcb, 0xa4, 0xcb, 0x94, 0xb3, 0x94, 0xcb, 0xa4, 0xcb, 0x94, 0xb3, 0x94, 0xcb, 0xa4, 0xfb, 0x93, 0x94, 0xfb, 0xc3
};

// AUTO-GENERATED IMAGE CONVERTED FROM: log_middle.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_log_middle;
PROGMEM const char __raw_log_middle_p[122] = {
	0x54, 0x3f, 0x38, 0xe0, 0x20, 0x80, 0x49, 0x41, 0x61, 0xc2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xd0, 0x10, 0xc0, 0xca, 0x13, 0x12, 0xba, 0xcc, 0x13, 0x14, 0xbc, 0x34, 0x43, 0x34, 0x94, 0x13, 0x31, 0xa4, 0x93, 0x9c, 0x93, 0xac, 0x13, 0x14, 0x9c, 0x34, 0x94, 0x34, 0xa4, 0x93, 0xc4, 0x34, 0xb4, 0x93, 0x43, 0xac, 0x9b, 0xac, 0x93, 0xac, 0x34, 0xcc, 0x93, 0x94, 0x93, 0xa4, 0x34, 0xb4, 0x93, 0xb4, 0x34, 0xb4, 0x9b, 0xb4, 0x34, 0xc4, 0x34, 0x94, 0x34, 0x9c, 0x34, 0x99, 0x94, 0xab, 0x43, 0x43, 0x34, 0x9b, 0x13, 0x93, 0x14, 0xb4, 0x34, 0x94, 0x34, 0x94, 0x93, 0x91, 0xb4, 0x34, 0x43, 0xb4, 0x91, 0xbc, 0x34, 0x34, 0x43, 0xa4, 0x93, 0xac, 0x9b, 0x94, 0x93, 0xac, 0x34, 0x43, 0xd4, 0x34, 0x9c, 0x34, 0xf4, 0xb4, 0xfa, 0xaa, 0xf8, 0xa8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: log_front.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_log_front;
PROGMEM const char __raw_log_front_p[102] = {
	0x54, 0x3f, 0x20, 0x80, 0x61, 0xc2, 0x49, 0x41, 0x8a, 0xc5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xf8, 0xd0, 0xf9, 0xa0, 0x91, 0xf2, 0xa0, 0x12, 0xe2, 0x93, 0x90, 0x91, 0x92, 0x94, 0xa2, 0xb3, 0x92, 0x01, 0x9a, 0xa4, 0x92, 0x32, 0xba, 0x01, 0x9a, 0xa4, 0xda, 0x12, 0x24, 0xb4, 0x23, 0x93, 0xaa, 0x31, 0x24, 0xbc, 0xa2, 0xab, 0x21, 0x24, 0xc4, 0xca, 0x12, 0xcc, 0xa2, 0x32, 0x9a, 0x12, 0xc4, 0x92, 0x9b, 0x23, 0x9a, 0x12, 0x24, 0xb4, 0xb2, 0xa3, 0x01, 0x9a, 0xa4, 0xda, 0x01, 0x9a, 0xa4, 0xda, 0x90, 0x91, 0x92, 0x94, 0x9a, 0x9b, 0xaa, 0x30, 0x98, 0x12, 0xc2, 0xab, 0x20, 0x98, 0x91, 0xf2, 0xa8, 0xf9, 0xf8, 0xa8
};

// AUTO-GENERATED IMAGE CONVERTED FROM: croaker_logo.png
// AUTO GENERATED IMAGE, PUT ME IN images.h
extern RawImage image_croaker_logo;
PROGMEM const char __raw_croaker_logo_p[1048] = {
	0x00, 0x00, 0x0b, 0x24, 0x25, 0x69, 0x7b, 0xef, 0xf2, 0xcc, 0x1f, 0x0a, 0x00, 0x00, 0x00, 0x00,
	0xf8, 0xf8, 0xf8, 0xf8, 0xb0, 0xa1, 0x90, 0xa1, 0xf8, 0xf8, 0xc0, 0xa2, 0x90, 0xa2, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xc0, 0xa1, 0x90, 0xa1, 0xf8, 0xf8, 0xc0, 0xa2, 0x90, 0xa2, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xc0, 0x91, 0x30, 0xa1, 0x30, 0xf0, 0xf8, 0xd0, 0x32, 0x9a, 0x03, 0x92, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xc0, 0x91, 0x93, 0xa1, 0x93, 0xf8, 0xf8, 0xc0, 0x93, 0xa2, 0x93, 0x92, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xb0, 0xf1, 0xf8, 0xf8, 0xa0, 0xf2, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xa0, 0xf1, 0xf8, 0xf8, 0xa0, 0xf2, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xa0, 0xb1, 0xa4, 0xa1, 0xf8, 0xf8, 0xa0, 0xa2, 0xa4, 0xb2, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xa0, 0xb1, 0xa4, 0xa1, 0xf8, 0xf8, 0xa0, 0xa2, 0xa4, 0xb2, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xb0, 0x91, 0xb5, 0x91, 0xf8, 0xf8, 0xc0, 0x92, 0xb5, 0x92, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xc0, 0x91, 0xb5, 0x91, 0xf8, 0xf8, 0xc0, 0x92, 0xb5, 0x92, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xb0, 0x92, 0x91, 0xb5, 0x91, 0x92, 0xf8, 0xf8, 0xa0, 0x91, 0x92, 0xb5, 0x92, 0x91, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xa0, 0x92, 0x91, 0xb5, 0x91, 0x92, 0xf8, 0xf8, 0xa0, 0x91, 0x92, 0xb5, 0x92, 0x91, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x90, 0xa2, 0x91, 0xb2, 0x91, 0xa2, 0xf8, 0xf8, 0xa1, 0x92, 0xb1, 0x92, 0xa1, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xa2, 0x91, 0xb2, 0x91, 0xa2, 0xf8, 0xf8, 0xa1, 0x92, 0xb1, 0x92, 0xa1, 0xf8, 0xf8, 0xf8, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0x95, 0xa0, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0x95, 0x90, 0xa5, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xe8, 0xc5, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xe8, 0xb5, 0xc8, 0xcd, 0xc8, 0xe5, 0xf8, 0xcd, 0xf8, 0xcd, 0xe0, 0xb5, 0x98, 0xb5, 0xc8, 0xfd, 0xc8, 0xe5, 0xc0, 0xa5, 0xc8, 0xcd, 0xc8, 0xe5, 0xf8, 0xcd, 0xf8, 0xcd, 0xe0, 0xb5, 0x98, 0xb5, 0xc8, 0xfd, 0xc8, 0xe5, 0xc0, 0xa5, 0xc8, 0xcd, 0xc8, 0xe5, 0xf8, 0xcd, 0xf8, 0xcd, 0xe0, 0xb5, 0x98, 0xb5, 0xc8, 0xfd, 0xc8, 0xe5, 0xc0, 0xa5, 0xb0, 0xb5, 0xb0, 0x9d, 0x98, 0xb5, 0xc8, 0x9d, 0xc8, 0xb5, 0xb0, 0x9d, 0xc8, 0xb5, 0xb0, 0x9d, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0xe0, 0x9d, 0x98, 0xb5, 0xc8, 0x9d, 0xa8, 0xa5, 0xb0, 0xb5, 0xb0, 0x9d, 0x98, 0xb5, 0xc8, 0x9d, 0xc8, 0xb5, 0xb0, 0x9d, 0xc8, 0xb5, 0xb0, 0x9d, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0xe0, 0x9d, 0x98, 0xb5, 0xc8, 0x9d, 0xa8, 0xa5, 0xb0, 0xb5, 0xb0, 0x9d, 0x98, 0xb5, 0xc8, 0x9d, 0xc8, 0xb5, 0xb0, 0x9d, 0xc8, 0xb5, 0xb0, 0x9d, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0xe0, 0x9d, 0x98, 0xb5, 0xc8, 0x9d, 0xa8, 0xa5, 0x98, 0xb5, 0x98, 0xb5, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0x9d, 0xb0, 0xb5, 0x98, 0xcd, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x90, 0xa5, 0x98, 0xb5, 0x98, 0xb5, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0x9d, 0xb0, 0xb5, 0x98, 0xcd, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x90, 0xa5, 0x98, 0xb5, 0x98, 0xb5, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0x9d, 0xb0, 0xb5, 0x98, 0xcd, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x90, 0xa5, 0x98, 0xb5, 0x98, 0x9d, 0xc8, 0xb5, 0xc8, 0x9d, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0xe0, 0x9d, 0x98, 0xb5, 0xb0, 0x9d, 0xc8, 0xb5, 0xc8, 0x9d, 0xb0, 0xb5, 0xc8, 0x9d, 0xa8, 0xa5, 0x98, 0xb5, 0x98, 0x9d, 0xc8, 0xb5, 0xc8, 0x9d, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0xe0, 0x9d, 0x98, 0xb5, 0xb0, 0x9d, 0xc8, 0xb5, 0xc8, 0x9d, 0xb0, 0xb5, 0xc8, 0x9d, 0xa8, 0xa5, 0x98, 0xb5, 0x98, 0x9d, 0xc8, 0xb5, 0xc8, 0x9d, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0xe0, 0x9d, 0x98, 0xb5, 0xb0, 0x9d, 0xc8, 0xb5, 0xc8, 0x9d, 0xb0, 0xb5, 0xc8, 0x9d, 0xa8, 0xa5, 0x98, 0xb5, 0x98, 0xb5, 0xb0, 0xb5, 0x98, 0x9d, 0x98, 0x9d, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0x9d, 0xb0, 0xb5, 0x98, 0xcd, 0xb0, 0xb5, 0x98, 0x9d, 0x98, 0x9d, 0xa8, 0xa5, 0x98, 0xb5, 0x98, 0xb5, 0xb0, 0xb5, 0x98, 0x9d, 0x98, 0x9d, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0x9d, 0xb0, 0xb5, 0x98, 0xcd, 0xb0, 0xb5, 0x98, 0x9d, 0x98, 0x9d, 0xa8, 0xa5, 0x98, 0xb5, 0x98, 0xb5, 0xb0, 0xb5, 0x98, 0x9d, 0x98, 0x9d, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0x9d, 0xb0, 0xb5, 0x98, 0xcd, 0xb0, 0xb5, 0x98, 0x9d, 0x98, 0x9d, 0xa8, 0xa5, 0xb0, 0xb5, 0xb0, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0xb0, 0xb5, 0xb0, 0x9d, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0xe0, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x90, 0xa5, 0xb0, 0xb5, 0xb0, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0xb0, 0xb5, 0xb0, 0x9d, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0xe0, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x90, 0xa5, 0xb0, 0xb5, 0xb0, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0xb0, 0xb5, 0xb0, 0x9d, 0xb0, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x98, 0xb5, 0xe0, 0x9d, 0x98, 0xb5, 0x98, 0xb5, 0x98, 0x9d, 0x90, 0xa5, 0xc8, 0xcd, 0xc8, 0xb5, 0x98, 0xb5, 0xe0, 0xcd, 0xe0, 0xb5, 0x98, 0xb5, 0xc8, 0xb5, 0x98, 0xb5, 0xc8, 0xfd, 0xc8, 0xb5, 0x98, 0xb5, 0xa8, 0xa5, 0xc8, 0xcd, 0xc8, 0xb5, 0x98, 0xb5, 0xe0, 0xcd, 0xe0, 0xb5, 0x98, 0xb5, 0xc8, 0xb5, 0x98, 0xb5, 0xc8, 0xfd, 0xc8, 0xb5, 0x98, 0xb5, 0xa8, 0xa5, 0xc8, 0xcd, 0xc8, 0xb5, 0x98, 0xb5, 0xe0, 0xcd, 0xe0, 0xb5, 0x98, 0xb5, 0xc8, 0xb5, 0x98, 0xb5, 0xc8, 0xfd, 0xc8, 0xb5, 0x98, 0xb5, 0xa8, 0xb5, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xe8, 0xc5, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xe8, 0xa5, 0x90, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0x95, 0xa0, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0x95, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xc0
};

PROGMEM const uint8_t image[] = {
	// First 16 bytes are colors
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
