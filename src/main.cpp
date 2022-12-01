/*
 * A frogger implementation for Arduino
 */
// keep intellisense satisfied
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>
#include <avr/delay.h>

#include "prelude.h"
#include "global_time.h"
#include "gfx.h"
#include "ir.h"
#include "conversion.h"
#include "nunchuk_value.h"

#define MOVEMENT_SPEED 20
#define MOVEMENT_INTERVAL 150

// Baudrate for Serial communication
#define BAUDRATE 9600

// The Wire address of the Nunchuk
#define NUNCHUK_ADDRESS 0x52

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
	draw_tilemap(&background);
	uint32_t next_message = 0;
	uint32_t next_move_tick = 0;

	Vector2 start_pos = {4 * 20, 15 * 20};
	// Vector2 end_pos = {6 * 20, 10 * 20};
	NEW_IMAGE(main_character, start_pos.x, start_pos.y, image_frogge);

	uint8_t is_at_end = false;

	draw_image_mask(&main_character);

	draw_string({20, 20}, "Hello World");
	draw_string({20, 40}, "0123456789");
	draw_string({20, 60}, "abcdefghijklm");
	draw_string({20, 80}, "nopqrstuvwxyz");

	// Main game loop
	while (1)
	{
		nunchuk_joystick_state y_val = get_joystick_state(Y);
		nunchuk_joystick_state x_val = get_joystick_state(X);

		if (global_time >= next_move_tick)
		{
			next_move_tick = global_time + MOVEMENT_INTERVAL;

			uint16_t prev_x = start_pos.x;
			uint16_t prev_y = start_pos.y;
			start_pos.x += (x_val == LEFT) ? (start_pos.x == 0 ? 0 : -MOVEMENT_SPEED) : (x_val == RIGHT) ? (start_pos.x == 220 ? 0 : MOVEMENT_SPEED) : 0;
			start_pos.y += (y_val == UP) ? (start_pos.y == 40 ? 0 : -MOVEMENT_SPEED) : (y_val == DOWN) ? (start_pos.y == 300 ? 0 : MOVEMENT_SPEED) : 0;
			
			if (prev_x != start_pos.x || prev_y != start_pos.y)
			{
				move_image(&main_character, &start_pos);
			}
		}


		// Constantly send IR messages
		if (global_time >= next_message)
		{
			next_message = global_time + 500;
			ir_send_message(2);
		}

		// Update the IR
		ir_heartbeat();
	}

	// This is never reached.
	return 0;
}
