
#ifndef __GFX_LIB__
#define __GFX_LIB__

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// The screen, it's not adviced to modify the screen directly, but rather use the functions defined here
extern Adafruit_ILI9341 tft;

// Start the gfx library
void init_gfx();

#endif
