
#ifndef __TOUCH_LIB__
#define __TOUCH_LIB__

#include <avr/io.h>

#define TS_CS 8
#define TS_CS_PORT PB0

#define TS_WRITE_BIT 0x00
#define TS_READ_BIT 0x80

void init_touch();

#endif

