
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/interrupt.h>
#include "global_time.h"

// How many events need to take place before 1 ms passed
#define ONE_MS_COMP_VAL 250

uint32_t global_time = 0;

// This invokes every MS, so we increment the global_time by one
ISR(TIMER1_COMPA_vect)
{
	global_time += 1;
}

void setup_global_timer()
{
	// Set CTC mode (CTC|OCRA|Immediate|MAX)
	TCCR1A &= ~(1 << WGM10);
	TCCR1A &= ~(1 << WGM11);
	TCCR1B |= (1 << WGM12);
	TCCR1B &= ~(1 << WGM13);
	// Set prescalar to 64
	TCCR1B &= ~(1 << CS12);
	TCCR1B |= (1 << CS11) | (1 << CS10);
	// Set compare value
	OCR1A = ONE_MS_COMP_VAL;
	// Trigger interrupts
	TIMSK1 |= (1 << OCIE1A);
}
