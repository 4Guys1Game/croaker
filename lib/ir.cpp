
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "global_time.h"
#include "ir.h"

#define HALF_PULSE_WIDTH_MS 5

// Buffer for receiving data in the 24 bits necessary
volatile uint32_t ir_receive_buffer = 0;
// The current fully recieved packet
volatile uint16_t received_ir_packet = 0;

// Package metadata
uint16_t packet = 0;
uint16_t packet_index = 0;
// Pulse metadata
uint32_t next_half_pulse = 0;
uint8_t second_half_of_pulse = 0;
uint8_t is_high = 0;

// A bool indicating whenever of not a package has been sent
uint8_t packet_sent = 0;

#define GET_IR_BIT                            \
    uint8_t ir_status = (PIND & (1 << DDD2)) >> DDD2; \
    uint8_t ir_bit = ir_status == 4 ? 0 : 1;

// Convert a data packet to only the data itself
IRData convert_packet_to_irdata(uint16_t packet){
	// Shift the bits 1 to the right to get rid of the parity bit
	packet >>= 1;
	// Use a mask to set the 2 message start bits (which are now moved to the right by 1) to 0, meaning only the data remains
	packet &= 0b0000000011111111;
	return packet;
} 

// Get the current data packet
// Returns an array of two IRData values, the first is for the x coordinate, the second one is for the y coordinate
void *ir_get_latest_data_packet(Vector2 *coordinates){
	if(received_ir_packet != 0){
	// Get the packet and turn it into only the data with the convert_packet_to_irdata function
	IRData packet_to_return = convert_packet_to_irdata(received_ir_packet);
	// Set the x coordinate in the array by bit shifting 4 to the right, only leaving the first 4 bits
	// Afterwards multiply the value by 20 to get the actual pixel value of the position
	coordinates->x = (packet_to_return >> 4) * 20;
	// Set the y coordinate in the array by masking the value with 00001111, meaning only the last 4 bits remain
	// Afterwards multiply the value by 20 to get the actual pixel value of the position
	// Because of the bar at the top, we must do an offset on the y value
	coordinates->y = ((packet_to_return & 0b00001111) * 20) + SCREEN_MIN_TILE_Y;

	// Reset received_ir_packet so no duplicate packets can be sent 
	received_ir_packet = 0;
	}
}

// Convert the 16 bits of received data into an 8bit packet that gets used in the program
void ir_convert_received_data_to_packet(){
	// Create the packet
	uint16_t packet_to_return = 0;
	// Loop through the 22 bits of data, starting from position 1 and incrementing by 2 because those positions hold the actual data
	for (uint32_t idx = 1; idx < 22; idx += 2)
	{
		// Check if the data on that bit isn't 0
		if((ir_receive_buffer & ((uint32_t)1 << idx)) != 0){
			// Add the bit to the packet in the correct place by dividing the index in 2
			packet_to_return |= 1 << (idx / 2);
		}
	}
	received_ir_packet = packet_to_return;
	// Reset the buffer for receiving data
	ir_receive_buffer = 0;
}

// Checks if the given input is valid by checking the parity bit
void ir_check_input(){
	// Calculate what the parity bit should be based on the provided data
	uint8_t parity = 0x00;
	// Add the bits from the data to the parity value
	for (uint16_t idx = 3; idx < 19; idx+= 2)
	{
		parity += (ir_receive_buffer & (1 << idx)) >> idx;
	}
	// Do a modulo 2 to determine of parity is even or uneven
	parity %= 2;

	// Check if the calculated parity equals the parity bit found in the received packet
	if(parity == (ir_receive_buffer & (parity << 1))){
		ir_convert_received_data_to_packet();
	}
}

void ir_receive_pulse(){
    GET_IR_BIT;

	// Shift the existing bits in the buffer by 1 to the left. This sets the newest least significant bit to 0
	ir_receive_buffer <<= 1;

	// Set the new least significant bit to the new value
	ir_receive_buffer |= !(ir_status) << 0;

	//Serial.println(ir_receive_buffer, BIN);
	// Check if the buffer & 00000000001111010101010101010101 (3D5555 in hexadecimal) is equal to 00000000001010000000000000000000 (280000 in hexadecimal)
	// With this we know if the start bit was set correctly and that every pulse (which is 2 bits) ends with a 0
	if((ir_receive_buffer & 0x3D5555) == 0x280000){
		ir_check_input();
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

uint16_t ir_create_packet(IRData data){
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

void ir_send_message(IRData data)
{
	// Create the packet
	packet = ir_create_packet(data);
	packet_index = 11;
	packet_sent = 0;
}

void ir_heartbeat()
{
	if ((global_time + 1) >= next_half_pulse)
	{
		// Go through every bit of the packet
		if (packet_index > 0)
		{
			// If we're in the second part of the pulse, where it always has to be low
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
				// Set to high if the bit is a 1, set to low if the bit is a 0
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
		// Go receive the pulse from the other game console
		ir_receive_pulse();
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