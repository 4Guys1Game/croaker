
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "global_time.h"
#include "ir.h"
#include "conversion.h"
#include "gfx.h"

#define HALF_PULSE_WIDTH_MS 5
#define MASK_16_TO_11_BIT 0x7FF
#define MASK_16_TO_8_BIT 0xFF

// Buffer for receiving data in the 11 bits necessary
volatile uint16_t ir_receive_buffer = 0;
// The current fully recieved packet
volatile uint16_t received_ir_packet = 0;
volatile uint8_t previous_state = 0;
volatile uint8_t time_since_state_change = 0;
volatile uint32_t previous_time_value = 0;

// Package metadata
uint16_t packet = 0;
uint16_t packet_index = 0;
// Pulse metadata
uint32_t next_half_pulse = 0;
uint8_t second_half_of_pulse = 0;
uint8_t is_high = 0;

// A bool indicating whenever of not a package has been sent
uint8_t packet_sent = 0;

// Convert a data packet to only the data itself
IRData convert_packet_to_irdata(uint16_t packet)
{
	// Shift the bits 1 to the right to get rid of the parity bit
	packet >>= 1;
	// Use a mask to set the 2 message start bits (which are now moved to the right by 1) to 0, meaning only the data remains
	packet &= MASK_16_TO_8_BIT;
	return packet;
}

// Get the current data packet
// Returns an array of two IRData values, the first is for the x coordinate, the second one is for the y coordinate
void ir_get_latest_data_packet(Vector2 *coordinates)
{
	if (received_ir_packet != 0)
	{
		// Get the packet and turn it into only the data with the convert_packet_to_irdata function
		IRData packet_to_return = convert_packet_to_irdata(received_ir_packet);
		if (packet_to_return > 23 && packet_to_return < 208)
		{
			// Set the x coordinate in the array by bit shifting 4 to the right, only leaving the first 4 bits
			// Afterwards multiply the value by 20 to get the actual pixel value of the position
			coordinates->x = (packet_to_return % 12) * 20;
			// Set the y coordinate in the array by masking the value with 00001111, meaning only the last 4 bits remain
			// Afterwards multiply the value by 20 to get the actual pixel value of the position
			// Because of the bar at the top, we must do an offset on the y value
			coordinates->y = (packet_to_return / 12) * 20;
		}
		// Reset received_ir_packet so no duplicate packets can be sent
		received_ir_packet = 0;
	}
}

void ir_get_current_status(uint8_t *status){
	if (received_ir_packet != 0)
	{
		// Get the packet and turn it into only the data with the convert_packet_to_irdata function
		IRData packet_to_return = convert_packet_to_irdata(received_ir_packet);
		if (packet_to_return > 208)
		{
			*status = packet_to_return;
			// Reset received_ir_packet so no duplicate packets can be sent
			received_ir_packet = 0;
		}
		else
		{
			*status = 0;
		}
	}
}

// Convert the 16 bits of received data into an 8bit packet that gets used in the program
void ir_convert_received_data_to_packet(uint16_t buffer_data)
{
	// Create the packet
	uint16_t packet_to_return = 0;
	// Only get the relevant data by masking the buffer with 7FF (0000011111111111 in binary) and only keeping the last 11 bits
	packet_to_return = buffer_data & MASK_16_TO_11_BIT;
	received_ir_packet = packet_to_return;
}

// Checks if the given input is valid by checking the parity bit and the starting bits
void ir_check_input(uint16_t buffer)
{
	// Calculate what the parity bit should be based on the provided data
	uint16_t parity = 0x00;
	// Add the bits from the data to the parity value
	for (uint16_t idx = 1; idx < 9; idx++)
	{
		parity += (buffer & (1 << idx)) >> idx;
	}
	// Do a modulo 2 to determine of parity is even or uneven
	parity %= 2;

	// Check if the calculated parity equals the parity bit found in the received packet
	if (parity == (buffer & (parity << 1)) && (buffer & ((uint16_t)1 << 9)) == 512 && (buffer & ((uint16_t)1 << 10)) == 1024)
	{
		// Create the packet
		uint16_t packet_to_return = 0;
		// Only get the relevant data by masking the buffer with 7FF (0000011111111111 in binary) and only keeping the last 11 bits
		packet_to_return = (buffer & MASK_16_TO_11_BIT);
		received_ir_packet = packet_to_return;
	}
}

void ir_receive_pulse()
{
	// Get the current status by checking the D2 bit of PIND
	// Starting from 0 that is the second bit, so we need to shift that bit to the right to get the correct value
	// Lastly because of the way the receiver works we need to invert the bit to get the correct data
	uint8_t ir_status = !((PIND & (1 << DDD2)) >> DDD2);

	// With this we know enough time has passed for there to be a new message
	if (global_time - previous_time_value >= 100)
	{
		// Go do the checking of the input to see if it is a valid message
		uint16_t input = ir_receive_buffer;
		ir_check_input(input);

		// Reset the buffer to have room te receive a new message
		ir_receive_buffer = 0;
		previous_time_value = global_time;
	}

	// Check if the current status is different form the previous state, so going form 1 to 0 and vice versa
	if (ir_status != previous_state)
	{
		
		// Check if enough time has passed that this is a pulse different that matters, and not just a set to high or low to start the next bit
		if (global_time - previous_time_value >= 7) 
		{
			// Shift the bits to the left by one
			ir_receive_buffer <<= 1;
			// Set the new least significant bit
			ir_receive_buffer |= ir_status;
			previous_time_value = global_time;
		}

		// Set the previous state to the current state, so the new comparison will be correct
		previous_state = ir_status;
	}
}
void ir_set_high()
{
	is_high = 1;
	// Set prescalar to 1
	TCCR0B |= (1 << CS00);
	// Allow the LED to be set to high
	TCCR0A |= (1 << COM0A0);
	// Empty any remaining count
	TCNT0 = 0;
}

void ir_set_low()
{
	is_high = 0;
	// Turn prescalar off
	TCCR0B &= ~(1 << CS00);
	// Don't allow the LED to be set to high
	TCCR0A &= ~(1 << COM0A0);
	// Make sure we empty PORTD
	PORTD &= ~(1 << PD6);
	// Empty any remaining count
	TCNT0 = 0;
}

uint16_t ir_create_packet(Vector2 *position)
{

	uint8_t data = (position->x / 20) + (position->y / 20) * 12;
	// Calculate the parity
	// 0x01 if uneven
	// 0x00 if even
	uint8_t parity = 0x00;
	// Add the bits from the data to the parity value
	for (uint8_t idx = 0; idx < 8; idx++)
	{
		parity += (data & (1 << idx)) >> idx;
	}
	// Do a modulo 2 to determine of parity is even or uneven
	parity %= 2;

	// Config data
	packet = 0x600 | ((data & 0xFF) << 1) | parity;
	return packet;
}

uint16_t ir_create_packet_status(volatile uint8_t *data)
{
	// Calculate the parity
	// 0x01 if uneven
	// 0x00 if even
	uint8_t parity = 0x00;
	// Add the bits from the data to the parity value
	for (uint8_t idx = 0; idx < 8; idx++)
	{
		parity += (*data & (1 << idx)) >> idx;
	}
	// Do a modulo 2 to determine of parity is even or uneven
	parity %= 2;

	// Config data
	packet = 0x600 | ((*data & 0xFF) << 1) | parity;
	return packet;
}

void ir_send_message_position(Vector2 *position)
{
	// Create the packet
	packet = ir_create_packet(position);
	packet_index = 11;
	packet_sent = 0;
}

void ir_send_message_status(volatile uint8_t *position)
{
	// Create the packet
	packet = ir_create_packet_status(position);
	packet_index = 11;
	packet_sent = 0;
}

void ir_heartbeat()
{
	ir_receive_pulse();
	if (global_time >= next_half_pulse)
	{
		// Go through every bit of the packet
		if (packet_index > 0)
		{
			// If we're in the second part of the pulse, where it always has to be low
			if (second_half_of_pulse)
			{
				// Manchester encoding, if 1, go from low to high, if 0, go high to low
				// Inverse of the next if statement
				if (packet & (1 << (packet_index - 1)))
				{
					ir_set_high();
				}
				else
				{
					ir_set_low();
				}
				second_half_of_pulse = 0;
				packet_index--;
			}
			else
			{
				// Manchester encoding, if 1, go from low to high, if 0, go high to low
				if (packet & (1 << (packet_index - 1)))
				{
					ir_set_low();
				}
				else
				{
					ir_set_high();
				}
				second_half_of_pulse = 1;
			}
		}
		else
		{
			ir_set_low();
			PORTD &= ~(1 << PD6);
			// If packet index == 0, then we finished sending
			// Meaning this should be 1
			packet_sent = 1;
		}
		next_half_pulse = global_time + HALF_PULSE_WIDTH_MS;
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