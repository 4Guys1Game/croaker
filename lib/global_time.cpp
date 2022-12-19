
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/interrupt.h>
#include "global_time.h"

// How many events need to take place before 1 ms passed
#define ONE_MS_COMP_VAL 125

uint32_t global_time = 0;
uint32_t global_time_tiny = 0;

// This invokes every MS, so we increment the global_time by one
ISR(TIMER2_COMPA_vect)
{
	global_time_tiny += 1;
	if (global_time_tiny % 125 == 0)
	{
		global_time += 1;
	}
}

void setup_global_timer()
{
	// Set CTC mode
	TCCR2A &= ~(1 << WGM20);
	TCCR2A |= (1 << WGM21);
	TCCR2B &= ~(1 << WGM22);
	// Set prescalar to 128
	TCCR2B &= ~(1 << CS21);
	TCCR2B |= (1 << CS22) | (1 << CS20);
	// Set compare value
	OCR2A = ONE_MS_COMP_VAL;
	// Trigger interrupts
	TIMSK2 |= (1 << OCIE2A);
}
