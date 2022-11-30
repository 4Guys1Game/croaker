/*
 * A frogger implementation for Arduino
 */
// keep intellisense satisfied
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>
#include <nunchuck_value.h>
#include <avr/delay.h>

#include "global_time.h"
#include "gfx.h"
#include "ir.h"

// Baudrate for Serial communication
#define BAUDRATE 9600

// The Wire address of the Nunchuk
#define NUNCHUK_ADDRESS 0x52

// Functions for reading and writing values to the EEPROM.
#define load_value(address) eeprom_read_byte((uint8_t *)address)
#define save_value(address, value) eeprom_write_byte((uint8_t *)address, value)

// An enum for the different addresses to read or write to/from on the EEPROM
enum eeprom_location
{
	HIGH_SCORE = EEAR0,
	OPPONENT_HIGH_SCORE = EEAR0
};

int main(void)
{
	// Init
	setup_global_timer();
	init_gfx();
	init_ir(FREQ_VAL_38KHZ);

	sei();

	// Begin Serial communication
	Serial.begin(BAUDRATE);


	// Initialize the connection with the nunchuk and stop if it is not found
	if (!init_nunchuk(NUNCHUK_ADDRESS)) return 1;

	// Draw the background
	draw_tilemap(background);
	uint32_t next_message = 0;
	uint32_t next_move = 0;

	Vector2 start_pos = {4 * 20, 15 * 20};
	Vector2 end_pos = {6 * 20, 10 * 20};
	NEW_IMAGE(main_character, start_pos.x, start_pos.y, image_frogge);

	uint8_t is_at_end = false;

	// Main game loop
	while (1)
	{

		if (global_time >= next_move)
		{
			if (is_at_end)
			{
				is_at_end = false;
				move_image(&main_character, &start_pos);
			}
			else
			{
				is_at_end = true;
				move_image(&main_character, &end_pos);
			}
			next_move = global_time + 250;
		}

		// Constantly send IR messages
		if (global_time >= next_message)
		{
			next_message = global_time + 500;
			ir_send_message(2);
            Serial.print("Nunchuk: Y:");
            nunchuk_joystick_state yval = get_joystick_state(Y);
            nunchuk_joystick_state xval = get_joystick_state(X);
            Serial.print(yval == UP ? "Up" : yval == DOWN ? "Down" : "Middle");
            Serial.print(" X:");
            Serial.print(xval == LEFT ? "Left" : xval == RIGHT ? "Right" : "Middle");
            Serial.print(" C:");
            Serial.print(get_button_state(C) == PRESSED ? "Pressed" : "Released");
            Serial.print(" Z:");
            Serial.println(get_button_state(Z) == PRESSED ? "Pressed" : "Released");
		}

		// Update the IR
		ir_heartbeat();
	}

	// This is never reached.
	return 0;
}
