/*
 * A frogger implementation for Arduino
 */
// keep intellisense satisfied
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

#include "prelude.h"
#include "global_time.h"
#include "collision.h"
#include "ir.h"
#include "conversion.h"
#include "nunchuk_frogger.h"

// Baudrate for Serial communication
#define BAUDRATE 9600

// The Wire address of the Nunchuk
#define NUNCHUK_ADDRESS 0x52

// The speed of all moving things on the map which aren't player controlled
#define MOVEABLE_MOVE_SPEED 350

// Functions for reading and writing values to the EEPROM.
#define load_value(address) eeprom_read_byte((uint8_t *)address)
#define save_value(address, value) eeprom_write_byte((uint8_t *)address, value)

// An enum for the different addresses to read or write to/from on the EEPROM
enum eeprom_location
{
	HIGH_SCORE = EEAR0,
	OPPONENT_HIGH_SCORE = EEAR0
};

Player players[] = {
	{
		{ 4 * 20, 15 * 20 },
		{
			{ 4 * 20, 15 * 20 },
			&image_frogge
		}
	},
	{
		{ 6 * 20, 15 * 20 },
		{
			{ 6 * 20, 15 * 20 },
			&image_frogge
		}
	}
};

uint8_t simulation_x = 0;

uint8_t inline get_simulation_x(int8_t tile_offset)
{
	return ((SCREEN_WIDTH_TILE - simulation_x + 1) + tile_offset) % SCREEN_WIDTH_TILE;
}

void simulate_moveables()
{
	// Update the simulation
	simulation_x = (simulation_x + 1) % SCREEN_WIDTH_TILE;

	Vector2 vec = Vector2 {
		get_simulation_x(2),
		9
	};
	set_tile(&foreground, vec, 2);
	draw_tile(&foreground, vec);
	vec.x = get_simulation_x(1);
	set_tile(&foreground, vec, 1);
	draw_tile(&foreground, vec);
	vec.x = get_simulation_x(3);
	set_tile(&foreground, vec, 0);
	draw_tile(&background, vec);

	vec.x = get_simulation_x(8 + 2);
	set_tile(&foreground, vec, 2);
	draw_tile(&foreground, vec);
	vec.x = get_simulation_x(8 + 1);
	set_tile(&foreground, vec, 1);
	draw_tile(&foreground, vec);
	vec.x = get_simulation_x(8 + 3);
	set_tile(&foreground, vec, 0);
	draw_tile(&background, vec);
}

int main(void)
{
	sei();

	// Initialize required functionalities
	setup_global_timer();
	init_gfx();
	init_ir(FREQ_VAL_38KHZ);
	init_nunchuk(NUNCHUK_ADDRESS);

	// Draw the background & foreground
	draw_tilemap(&background);
	draw_tilemap(&foreground);

	// Init the game timers
	uint32_t next_message = 0;
	uint32_t next_move_tick = 0;
	uint32_t next_moveables_tick = 0;

	uint8_t is_at_end = false;

	draw_image_mask(&players[0].image);

	draw_string({20, 20}, "Hello World");
	draw_string({20, 40}, "0123456789");
	draw_string({20, 60}, "abcdefghijklm");
	draw_string({20, 80}, "nopqrstuvwxyz");

	// Main game loop
	while (1)
	{
		nunchuk_state nunchuk = get_nunchuk_state(NUNCHUK_ADDRESS);
		nunchuk_joystick_state y_val = nunchuk.nunchuk_y;
		nunchuk_joystick_state x_val = nunchuk.nunchuk_x;

		if (global_time >= next_moveables_tick)
		{
			next_moveables_tick = global_time + MOVEABLE_MOVE_SPEED;
			simulate_moveables();
			// Force collision detection by moving the player 0 tiles
			move_player(&players[0], {0, 0});
		}

		if (global_time >= next_move_tick)
		{
			next_move_tick = global_time + MOVEMENT_INTERVAL;

			move_player(&players[0], {
				(x_val == LEFT) ? (int16_t)-1 : (x_val == RIGHT) ? (int16_t)1 : (int16_t)0,
				(y_val == UP) ? (int16_t)-1 : (y_val == DOWN) ? (int16_t)1 : (int16_t)0
			});
			// uint16_t prev_x = player_pos.x;
			// uint16_t prev_y = player_pos.y;
			// player_pos.x += (x_val == LEFT) ? (player_pos.x == 0 ? 0 : -MOVEMENT_SPEED) : (x_val == RIGHT) ? (player_pos.x == 220 ? 0 : MOVEMENT_SPEED) : 0;
			// player_pos.y += (y_val == UP) ? (player_pos.y == 40 ? 0 : -MOVEMENT_SPEED) : (y_val == DOWN) ? (player_pos.y == 300 ? 0 : MOVEMENT_SPEED) : 0;
			
			// if (prev_x != player_pos.x || prev_y != player_pos.y)
			// {
			// 	move_image(&main_character, &player_pos);
			// }
		}


		// Constantly send IR messages
		if (global_time >= next_message)
		{
			next_message = global_time + 500;
			ir_send_message(15);
		}

		// Update the IR
		ir_heartbeat();

		// Get the latest available data
		IRData received_data = ir_get_latest_data_packet();
		// Check if the data isn't invalid
		if(received_data != 0){
			// Continue here with the received data
		}
	}

	// This is never reached.
	return 0;
}
