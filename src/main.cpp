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
uint32_t current_score = 0;
uint8_t status_to_send = 0;

// An enum for the different addresses to read or write to/from on the EEPROM
enum eeprom_location
{
	HIGH_SCORE_0 = EEAR0,
	HIGH_SCORE_1 = EEAR1,
	HIGH_SCORE_2 = EEAR2,
	HIGH_SCORE_3 = EEAR3
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

    set_current_level(0);

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
		uint8_t highscore_0 = load_value(eeprom_location::HIGH_SCORE_0);
		uint8_t highscore_1 = load_value(eeprom_location::HIGH_SCORE_1);
		uint8_t highscore_2 = load_value(eeprom_location::HIGH_SCORE_2);
		uint8_t highscore_3 = load_value(eeprom_location::HIGH_SCORE_3);
		uint32_t highscore = highscore_0;
		highscore <<= 8;
		highscore |= highscore_1;
		highscore <<= 8;
		highscore |= highscore_2;
		highscore <<= 8;
		highscore |= highscore_3;
		char score_buffer[11];
		uint32_to_string(score_buffer, highscore);
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

	uint8_t level_changed = 0;
    uint8_t current_level_index = 3;

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

			uint8_t wins;
			gamestate_get_wins(&wins);
			show_on_segment_display(wins);
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
		if (status == 0)
		{
			// Get the latest available data using a vector2 to write to
			ir_get_latest_data_packet(&second_player_coords);
		}
		if ((player_1_end == 1 && player_2_end == 1 && winner == 1 && status == ACKNOWLEDGEMENT_STATUS && level_changed == 0) || (player_1_end == 1 && player_2_end == 1 && winner == 2 && status == NEXT_LEVEL_STATUS && level_changed == 0 && times_status_set > 66))
		{
            current_level_index++;
            if (current_level_index == 4)
            {
                set_current_level(current_level_index);
                move_image(&players[0].image, &players[0].spawn);
            }
			level_changed = 1;
			status_to_send = 0;
            times_status_set = 0;

            player_1_end = 0;
            player_2_end = 0;
			winner = 0;
		}
		else
		{
			// Check if the game has ended, and determine the winner and the time by which they won
			check_for_end(&players[0].image.position, &player_1_end, &status, &player_2_end, &winner, &player_time_faster_than_enemy);
			if (winner == 0)
			{
				level_changed = 0;
			}

			gamestate_set_new_send_status(&winner, &player_1_end, &player_2_end, &status_to_send, &status);
			if (status_to_send == ACKNOWLEDGEMENT_STATUS)
			{
				times_status_set++;
			}
		}

		if(current_level_index == 4)
		{
			uint32_t calculated_score = 0;
			gamestate_calculate_score(&current_score, &calculated_score);
			uint8_t highscore_0 = load_value(eeprom_location::HIGH_SCORE_0);
			uint8_t highscore_1 = load_value(eeprom_location::HIGH_SCORE_1);
			uint8_t highscore_2 = load_value(eeprom_location::HIGH_SCORE_2);
			uint8_t highscore_3 = load_value(eeprom_location::HIGH_SCORE_3);
			uint32_t previous_highscore = highscore_0;
			previous_highscore <<= 8;
			previous_highscore |= highscore_1;
			previous_highscore <<= 8;
			previous_highscore |= highscore_2;
			previous_highscore <<= 8;
			previous_highscore |= highscore_3;
			if(calculated_score > previous_highscore)
			{
				uint8_t highscore_save_0 = calculated_score >> 24;
				uint8_t highscore_save_1 = calculated_score >> 16;
				uint8_t highscore_save_2 = calculated_score >> 8;
				uint8_t highscore_save_3 = calculated_score;
				save_value(eeprom_location::HIGH_SCORE_0, highscore_save_0);
				save_value(eeprom_location::HIGH_SCORE_1, highscore_save_1);
				save_value(eeprom_location::HIGH_SCORE_2, highscore_save_2);
				save_value(eeprom_location::HIGH_SCORE_3, highscore_save_3);
			}
		}

        update_brightness();
	}

    // The end screen, this should idealy be put in it's own function, however, since it's the end of the file
    // I don't really think it's needed
    black_screen();
    draw_string({30, 55}, (char*)"thanks for playing");
	BasicImage logo = { {34, 75}, &image_croaker_logo };
    draw_image(&logo);
    if (amount_of_wins >= 2)
    {
        draw_string({85, 160}, (char*)"victory");
    }
    else
    {
        draw_string({80, 160}, (char*)"defeated");
    }
    draw_string({65, 200}, (char*)"final score");
    char score_text_buffer[11];
    uint32_to_string(score_text_buffer, current_score);
    draw_string({65, 220}, score_text_buffer);
}
