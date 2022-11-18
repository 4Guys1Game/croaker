
#include "gfx.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void init_gfx() {
	tft.begin(); // Initialize the tft
}

Adafruit_ILI9341 get_tft() {
	return tft;
}
