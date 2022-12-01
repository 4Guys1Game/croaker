
#ifndef __PRELUDE__
#define __PRELUDE__

#include <stdint.h>
#include <avr/eeprom.h>

// Simplistic image definitions
typedef uint8_t* ImageBytes;
typedef uint16_t ImageLength;

// A simple vector2 struct
typedef struct
{
	uint16_t x;
	uint16_t y;
} Vector2;

// Functions for reading and writing values to the EEPROM.
#define LOAD_VALUE_FROM_EEPROM(address) 	   eeprom_read_byte((uint8_t *)address)
#define SAVE_VALUE_TO_EEPROM(address, value)   eeprom_write_byte((uint8_t *)address, value)

// An enum for the different addresses to read or write to/from on the EEPROM
enum eeprom_location
{
	HIGH_SCORE = EEAR0,
	OPPONENT_HIGH_SCORE = EEAR0
};

#endif
