// /*
//  * A frogger implementation for Arduino.
//  */

// keep intellisense satisfied
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

// // Header file needed to enable interrupts.
#include <avr/interrupt.h>
#include <util/delay.h>

// Local libs
#include "global_time.h"
#include "gfx.h"
#include "convertion.h"

int main(void)
{
	sei(); // Enable global interrupts
	setup_global_timer(); // Enable global timer
	init_gfx(); // Enable the gfx library

	tft.fillScreen(ILI9341_BLACK);
	while (1) {
		tft.fillScreen(ILI9341_CYAN);
		tft.fillScreen(ILI9341_RED);
	}
	return (0);
}
