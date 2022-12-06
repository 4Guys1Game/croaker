
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>

#include <HardwareSerial.h> // REMOVE ME

#include "global_time.h"
#include "ir.h"

#define HALF_PULSE_WIDTH_MS 10

// Package metadata
IRPacket packet = 0;
uint8_t packet_index = 0;
// Pulse metadata
uint32_t next_half_pulse = 0;
uint8_t second_half_of_pulse = 0;
uint8_t is_high = 0;

// A bool indicating whenever of not a package has been sent
uint8_t packet_sent = 0;

void ir_set_high()
{
	is_high = 1;
	// Set prescalar to 1
	TCCR0B |= (1 << CS00);
	// Empty any remaining count
	TCNT0 = 0;
}

void ir_set_low()
{
	is_high = 0;
	// Turn prescalar off
	TCCR0B &= ~(1 << CS00);
	// Make sure we empty PORTD
	PORTD &= ~(1 << PD6);
	// Empty any remaining count
	TCNT0 = 0;
}

void ir_send_message(IRPacket data)
{
	// Calculate the parity
	// 0x01 if uneven
	// 0x00 if even
	uint8_t parity = 0x00;
	for (uint8_t idx = 0; idx < 5; idx++)
	{
		parity += (data & (1 << idx));
	}
	parity %= 2;

	// Config data
	packet = 0xc0 | ((data & 0x1f) << 1) | parity;
	packet_index = 8;
	packet_sent = 0;
	next_half_pulse = global_time;
}

void ir_heartbeat()
{
	if (global_time >= next_half_pulse)
	{
		if (packet_index > 0)
		{
			// If we're in the low part of the pulse
			if (second_half_of_pulse)
			{
				// Set to low if it wasn't already
				if (is_high)
				{
					ir_set_low();
				}
				second_half_of_pulse = 0;
				packet_index--;
			}
			else
			{
				// Set high if we're a one, else low
				if (packet & (1 << (packet_index - 1)))
				{
					ir_set_high();
				}
				else
				{
					ir_set_low();
				}
				second_half_of_pulse = 1;
			}

			next_half_pulse = global_time + HALF_PULSE_WIDTH_MS;
		}
		else
		{
			// If packet index == 0, then we finished sending
			// Meaning this should be 1
			packet_sent = 1;
		}
	}
}

void init_ir(uint8_t frequency)
{
	// Initialize pin as pin for the port expander
	// initializing pin 6 (PD6) as the output pin for the switch
	DDRD |= (1 << PD6);

	// Output A Frequency when PhaseCorrectedPWM
	// Freq = 16MHz / (PRESCALAR * OCRA0 * 4)
	// f = 16MHz / (p * o * 4)
	// Reverse (to calculate the OCR0A)
	// o = 16MHz / (f * p * 4)

	// Set the prescalar to off
	TCCR0B &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));
	// Toggle OC0A on match
	TCCR0A |= (1 << COM0A0);
	// Set Phase Corrected PWM
	TCCR0A |= (1 << WGM00);
	TCCR0B |= (1 << WGM02);
	// Value determines the frequency on a scale of 0-255
	OCR0A = frequency;
}
