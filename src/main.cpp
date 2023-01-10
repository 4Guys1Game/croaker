/*
 * A frogger implementation for Arduino
 */
// keep intellisense satisfied
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#include "display_driver.h"
#endif

#include <avr/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "collision.h"
#include "conversion.h"
#include "global_time.h"
#include "ir.h"
#include "nunchuk_frogger.h"
#include "prelude.h"
#include "segment_display.h"
#include "game_states.h"
#include "touch_driver.h"
#include "brightness.h"

// Baudrate for Serial communication
#define BAUDRATE 9600

// The Wire address of the Nunchuk
#define NUNCHUK_ADDRESS 0x52

// The speed of all moving things on the map which aren't player controlled
#define MOVEABLE_MOVE_SPEED 350

// Functions for reading and writing values to the EEPROM.
#define load_value(address) eeprom_read_byte((uint8_t *)address)
#define save_value(address, value) eeprom_write_byte((uint8_t *)address, value)

// Value to determine who won, 0 if nobody, 1 if player 1, 2 if player 2
uint8_t winner = 0;
uint16_t current_score = 0;
uint8_t status_to_send = 0;

// An enum for the different addresses to read or write to/from on the EEPROM
enum eeprom_location
{
	HIGH_SCORE = EEAR0,
	OPPONENT_HIGH_SCORE = EEAR0
};

enum nunchuk_screen
{
	START_UP,
	START_SCREEN,
	GAME_SCREEN
};

Player players[] = {
	{
		{4 * 20, 15 * 20},
		{
			{4 * 20, 15 * 20},
			&image_frogge
		}
	},
	{
		{6 * 20, 15 * 20},
		{
			{6 * 20, 15 * 20},
			&image_frogge_2}
	}
};


uint8_t simulation_x = 0;

uint8_t inline get_simulation_x(int8_t tile_offset)
{
	return ((SCREEN_WIDTH_TILE - simulation_x + 1) + tile_offset) % SCREEN_WIDTH_TILE;
}

void inline simulate_single_car(Vector2 *tile_position, uint8_t offset)
{
	tile_position->x = get_simulation_x(offset + 2);
	set_tile(&current_level.foreground, *tile_position, 2);
	draw_tile(&current_level.foreground, *tile_position);
	tile_position->x = get_simulation_x(offset + 1);
	set_tile(&current_level.foreground, *tile_position, 1);
	draw_tile(&current_level.foreground, *tile_position);
	tile_position->x = get_simulation_x(offset + 3);
	set_tile(&current_level.foreground, *tile_position, 0);
	draw_tile(&current_level.background, *tile_position);
}

void inline simulate_single_log(Vector2 *tile_position, uint8_t middle_length, uint8_t offset)
{
	tile_position->x = get_simulation_x(offset + middle_length + 1);
	set_tile(&current_level.foreground, *tile_position, 5);
	draw_tile(&current_level.foreground, *tile_position);
	tile_position->x = get_simulation_x(offset);
	set_tile(&current_level.foreground, *tile_position, 3);
	draw_tile(&current_level.foreground, *tile_position);
	if (middle_length >= 1)
	{
		tile_position->x = get_simulation_x(offset + 1);
		set_tile(&current_level.foreground, *tile_position, 4);
		draw_tile(&current_level.foreground, *tile_position);
	}
	tile_position->x = get_simulation_x(offset + middle_length + 2);
	set_tile(&current_level.foreground, *tile_position, 0);
	draw_tile(&current_level.background, *tile_position);
}

void simulate_moveables()
{
	// Update the simulation
	simulation_x = (simulation_x + 1) % SCREEN_WIDTH_TILE;

	Vector2 vec = {0, current_level.cars.start_y};
	for (uint8_t car_idx = 0; car_idx < current_level.cars.position_len; car_idx++) {
		simulate_single_car(&vec, current_level.cars.positions[car_idx].x);
		vec.y += current_level.cars.positions[car_idx].increment_y;
	}

	vec.y = current_level.logs.start_y;
	for (uint8_t log_idx = 0; log_idx < current_level.logs.position_len; log_idx++) {
		simulate_single_log(&vec, current_level.logs.positions[log_idx].w, current_level.logs.positions[log_idx].x);
		vec.y += current_level.logs.positions[log_idx].increment_y;
	}
}

inline void black_screen()
{
	Vector2 screen_zero = {0, 0};
	Vector2 screen_max = {SCREEN_WIDTH, SCREEN_HEIGHT / 10};
	for (int i = 1; i <= 10; i++)
	{
		draw_rect(&screen_zero, &screen_max, text_color[0]);
		screen_zero.y = screen_max.y;
		screen_max.y = (SCREEN_HEIGHT / 10 * i);
	}
}

void draw_start_screen();
void nunchuk_disconnected(nunchuk_screen screen);

inline void draw_start_screen()
{
	BasicImage logo = { {34, 75}, &image_croaker_logo };
	black_screen();
	draw_image(&logo);
	draw_string({20, 220}, (char *) "Touch screen to start");
    // Done drawing, setup the touch
    touch_setup_registers();
    uint8_t is_pressed = is_screen_being_touched();
	while(!is_pressed)
	{
        update_brightness();
		nunchuk_state nunchuk = get_nunchuk_state(NUNCHUK_ADDRESS);
		if (!nunchuk.connected)
        {
            display_setup_registers();
            nunchuk_disconnected(START_SCREEN);
            touch_setup_registers();
        };
        is_pressed = is_screen_being_touched();
	}
    // Make sure we re-enable drawing again!
    display_setup_registers();
}

inline void nunchuk_disconnected(nunchuk_screen screen)
{
	black_screen();
	switch (screen)
	{
		case START_UP:
			draw_string({35, 150}, (char *) "ATTACH A NUNCHUK");
			while (!init_nunchuk(NUNCHUK_ADDRESS)) { _delay_ms(100); update_brightness(); }
			break;
		case START_SCREEN:
			draw_string({35, 150}, (char *) "ATTACH A NUNCHUK");
			while (!init_nunchuk(NUNCHUK_ADDRESS)) { _delay_ms(100); update_brightness(); }
			draw_start_screen();
			break;
		case GAME_SCREEN:
			draw_string({55, 140}, (char *) "PLEASE RESET");
			draw_string({15, 160}, (char *) "NUNCHUK DISCONNECTED");
			while(true) { update_brightness(); }
			break;
		default:
			break;
	}
}

int main(void)
{
	sei();
  
    init_adc();
    init_pwm();

	// Initialize required functionalities
    init_touch(); // Important we do this before gfx!
	init_gfx(); // Do this after the touch! If you don't, then call display_setup_registers() afterwards!

    set_current_level(3);

	if (!init_nunchuk(NUNCHUK_ADDRESS))
		nunchuk_disconnected(START_SCREEN);

	draw_start_screen();

	setup_global_timer();
	init_ir(FREQ_VAL_56KHZ);
	
	// Draw the background & foreground
	draw_tilemap(&current_level.background);
	draw_tilemap(&current_level.foreground);

	uint8_t is_at_end = false;

	draw_image_mask(&players[0].image);

	Vector2 topbar_begin = {0, 0};
	Vector2 topbar_end = {240, 40};

	draw_rect(&topbar_begin, &topbar_end, text_color[0]);
	draw_string({10, 2}, (char*)"Highscore");
	{
		uint8_t highscore = load_value(eeprom_location::HIGH_SCORE);
		char score_buffer[4];
		uint8_to_string(score_buffer, highscore);
		draw_string({20 + 10 * 10, 2}, score_buffer);
	}
	draw_string({10, 22}, (char*)"Current Time");
	draw_string({20 + 12 * 10, 22}, (char*)"00000");

	// Array for positions of the other player
	Vector2 second_player_coords;
	second_player_coords.x = players[1].spawn.x;
	second_player_coords.y = players[1].spawn.y;

	// Value for received status
	uint8_t status = 0;

	uint8_t player_1_end = 0;
	uint8_t player_2_end = 0;

	uint16_t player_time_faster_than_enemy = 0;

	uint8_t times_status_set = 0;

	uint8_t current_level = 0;
	uint8_t level_changed = 0;

	// Init the game timers
	uint32_t next_message = global_time;
	uint32_t next_move_tick = global_time;
	uint32_t next_moveable_tick = global_time + 150;
	uint32_t next_second = global_time;

	// Main game loop
	while (1)
	{
		nunchuk_state nunchuk = get_nunchuk_state(NUNCHUK_ADDRESS);
		if(!nunchuk.connected) nunchuk_disconnected(GAME_SCREEN);
		nunchuk_joystick_state y_val = nunchuk.nunchuk_y;
		nunchuk_joystick_state x_val = nunchuk.nunchuk_x;

		if (global_time >= next_second)
		{
			next_second = global_time + SECOND;
			char time_buffer[6];
			uint16_to_string(time_buffer, (uint16_t)(global_time / 1000));
			draw_string({20 + 12 * 10, 22}, time_buffer);

			show_on_segment_display((global_time / 1000) % 10);
		}

		if (global_time >= next_moveable_tick)
		{
			next_moveable_tick = global_time + MOVEABLE_MOVE_SPEED;
			simulate_moveables();
			// Send the player position after we simulated the cars, this is to prevent it from interferring with the timings
			if(status_to_send == 0)
			{
				ir_send_message_position(&players[0].image.position);
			}
			else
			{
				ir_send_message_status(&status_to_send);
			}
		}

		if (global_time >= next_move_tick && (x_val != MIDDLE || y_val != MIDDLE))
		{
			next_move_tick = global_time + MOVEMENT_INTERVAL;

			move_player(&players[0], {(x_val == LEFT)	 ? (int16_t)-1
									  : (x_val == RIGHT) ? (int16_t)1
														 : (int16_t)0,
									  (y_val == UP)		? (int16_t)-1
									  : (y_val == DOWN) ? (int16_t)1
														: (int16_t)0});

			// Move the position of the enemy frog by using the received coordinates
			move_image(&players[1].image, &second_player_coords);
		}

		// Update the IR
		ir_heartbeat();

		// Get the current status
		gamestate_get_status(&status);

		// Get player 2 movement info if the status isn't a valid one
		if(status == 0)
		{
			// Get the latest available data using a vector2 to write to
			ir_get_latest_data_packet(&second_player_coords);
		}
		if((player_1_end == 1 && player_2_end == 1 && winner == 1 && status == ACKNOWLEDGEMENT_STATUS && level_changed == 0)||(player_1_end == 1 && player_2_end == 1 && winner == 2 && status == NEXT_LEVEL_STATUS && level_changed == 0 && times_status_set > 66))
		{
			current_level++;
			level_changed = 1;
			status_to_send = 0;
		}
		else
		{
			// Check if the game has ended, and determine the winner and the time by which they won
			uint8_t winner_copy = winner;
			check_for_end(&players[0].image.position, &player_1_end, &status, &player_2_end, &winner, &player_time_faster_than_enemy);
			if(winner != winner_copy)
			{
				level_changed = 0;
			}

			gamestate_set_new_send_status(&winner, &player_1_end, &player_2_end, &status_to_send, &status);
			if(status_to_send == ACKNOWLEDGEMENT_STATUS)
			{
				times_status_set++;
			}
		}
	}

        update_brightness();
	}
}
