
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>

#include <HardwareSerial.h> // REMOVE ME

#include "global_time.h"
#include "ir.h"

#define HALF_PULSE_WIDTH_MS 10

volatile uint16_t ir_receive_buffer = 0000000000000000;

// Package metadata
IRPacket packet = 0;
uint8_t packet_index = 0;
// Pulse metadata
uint32_t next_half_pulse = 0;
uint8_t second_half_of_pulse = 0;
uint8_t is_high = 0;

// A bool indicating whenever of not a package has been sent
uint8_t packet_sent = 0;

#define GET_IR_BIT                            \
    uint8_t ir_status = (PIND & (1 << DDD2)) >> DDD2; \
    uint8_t ir_bit = ir_status == 4 ? 0 : 1;

void ir_convert_received_data_to_8bit(){
	uint8_t byte = 0;
	for (uint8_t idx = 13, count = 4; idx > 4 && count >= 0; idx -= 2, count--)
	{
		byte |= (ir_receive_buffer & (1 << idx)) << count;
	}
	Serial.println(ir_receive_buffer, BIN);
	Serial.println(byte);
	ir_receive_buffer = 0;
}

// Checks if the given input is valid by checking the parity bit
void ir_check_input(){
	// Calculate what the parity bit should be based on the provided data
	uint8_t parity = 0x00;
	// Add the bits from the data to the parity value
	for (uint8_t idx = 5; idx < 14; idx+= 2)
	{
		parity += (ir_receive_buffer & (1 << idx)) >> idx;
	}
	// Do a modulo 2 to determine of parity is even or uneven
	parity %= 2;

	// Check if the calculated parity equals the parity bit found in the received packet
	if(parity == (ir_receive_buffer & (parity << 1))){
		ir_convert_received_data_to_8bit();
	}
}

void ir_receive_pulse(){
    GET_IR_BIT;

	// shift the existing bits in the buffer by 1 to the left. This sets the newest least signisficant bit to 0
	ir_receive_buffer <<= 1;

	// set the new least significant bit to the new value
	ir_receive_buffer |= !(ir_status) << 0; 

	// check if the buffer & 1111010101010101 (F555 in hexadecimal) is equal to 1010000000000000 (A000 in hexadecimal)
	// with this we know if the start bit was set correctly and that every pulse (which is 2 bits) ends with a 0
	if((ir_receive_buffer & 0xF555) == 0xA000){
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

void ir_send_message(IRPacket data)
{
	// Calculate the parity
	// 0x01 if uneven
	// 0x00 if even
	uint8_t parity = 0x00;
	// Add the bits from the data to the parity value
	for (uint8_t idx = 0; idx < 5; idx++)
	{
		parity += (data & (1 << idx)) >> idx;
	}
	// Do a modulo 2 to determine of parity is even or uneven
	parity %= 2;

	// Config data
	packet = 0xc0 | ((data & 0x1f) << 1) | parity;
	packet_index = 8;
	packet_sent = 0;
	next_half_pulse = global_time;
}

void ir_heartbeat()
{
	if ((global_time + 1) >= next_half_pulse)
	{
		//Go do the receiving part of IR
		ir_receive_pulse();
		next_half_pulse = global_time + HALF_PULSE_WIDTH_MS;
		// Go through every bit of the packet
		/*if (packet_index > 0)
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

			next_half_pulse = global_time + HALF_PULSE_WIDTH_MS;
		}
		else
		{
			ir_set_low();
			PORTD &= ~(1 << PD6);
			// If packet index == 0, then we finished sending
			// Meaning this should be 1
			packet_sent = 1;
		}*/
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

/*void ir_receiver()
{
    int8_t ir_buffer;
    GET_IR_BIT;

    if (ir_bit == 1)
    { // checks if a start pulse is detected for 10ms
        GET_IR_BIT;
        if (ir_bit == 0)
        { // check for 10ms pause between the 2 start pulses
            GET_IR_BIT;
            if (ir_bit == 1)
            { // checks for the second start pulse
                GET_IR_BIT;
                if (ir_bit != 0)
                {
                    return;
                }

                // Read data
                for (uint8_t idx = 0; idx < 6; idx++)
                {
                    GET_IR_BIT;
                    ir_buffer |= ir_bit * (1 << idx);
                    GET_IR_BIT_DELAY;
                    if (ir_bit != 0)
                    {
                        return;
                    }
                }
            }
        }
    }
    Serial.println(ir_buffer, DEC);
}*/