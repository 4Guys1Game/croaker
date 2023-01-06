
#ifndef __TOUCH_LIB__
#define __TOUCH_LIB__

#include <avr/io.h>

#define TS_CS 8
#define TS_CS_PORT PB0

#define TS_WRITE_BIT 0x00
#define TS_READ_BIT 0x80

// A pure write-read operation via SPI to the touch display
// This function is 'raw', it is better to use touch_write or touch_read instead
uint8_t touch_transfer(uint8_t data);
// Write a byte to the touchscreen register
void touch_write(uint8_t reg, uint8_t data);
// Read a byte from a touchscreen register
uint8_t touch_read(uint8_t reg);

// Init the touchscreen
void init_touch();

#endif

