// /*
//  * A frogger implementation for Arduino
//  */
// // keep intellisense satisfied
// #ifndef __AVR_ATmega328P__
// #define __AVR_ATmega328P__
// #endif

// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <avr/delay.h>

// #include "prelude.h"
// #include "global_time.h"
// #include "collision.h"
// #include "ir.h"
// #include "conversion.h"
// #include "nunchuk_frogger.h"
// #include "segment_display.h"
// #include "brightness.h"

// // Baudrate for Serial communication
// #define BAUDRATE 9600

// // The Wire address of the Nunchuk
// #define NUNCHUK_ADDRESS 0x52

// // The speed of all moving things on the map which aren't player controlled
// #define MOVEABLE_MOVE_SPEED 350

// // Functions for reading and writing values to the EEPROM.
// #define load_value(address) eeprom_read_byte((uint8_t *)address)
// #define save_value(address, value) eeprom_write_byte((uint8_t *)address, value)

// // An enum for the different addresses to read or write to/from on the EEPROM
// enum eeprom_location
// {
// 	HIGH_SCORE = EEAR0,
// 	OPPONENT_HIGH_SCORE = EEAR0
// };

// enum nunchuk_screen
// {
// 	START_UP,
// 	START_SCREEN,
// 	GAME_SCREEN
// };

// Player players[] = {
// 	{{4 * 20, 15 * 20},
// 	 {{4 * 20, 15 * 20},
// 	  &image_frogge}},
// 	{{6 * 20, 15 * 20},
// 	 {{6 * 20, 15 * 20},
// 	  &image_frogge}}};

// uint8_t simulation_x = 0;

// uint8_t inline get_simulation_x(int8_t tile_offset)
// {
// 	return ((SCREEN_WIDTH_TILE - simulation_x + 1) + tile_offset) % SCREEN_WIDTH_TILE;
// }

// void inline simulate_single_car(Vector2 *tile_position, uint8_t offset)
// {
// 	tile_position->x = get_simulation_x(offset + 2);
// 	set_tile(&foreground, *tile_position, 2);
// 	draw_tile(&foreground, *tile_position);
// 	tile_position->x = get_simulation_x(offset + 1);
// 	set_tile(&foreground, *tile_position, 1);
// 	draw_tile(&foreground, *tile_position);
// 	tile_position->x = get_simulation_x(offset + 3);
// 	set_tile(&foreground, *tile_position, 0);
// 	draw_tile(&background, *tile_position);
// }

// void inline simulate_single_log(Vector2 *tile_position, uint8_t middle_length, uint8_t offset)
// {
// 	tile_position->x = get_simulation_x(offset + middle_length + 1);
// 	set_tile(&foreground, *tile_position, 5);
// 	draw_tile(&foreground, *tile_position);
// 	tile_position->x = get_simulation_x(offset);
// 	set_tile(&foreground, *tile_position, 3);
// 	draw_tile(&foreground, *tile_position);
// 	if (middle_length >= 1)
// 	{
// 		tile_position->x = get_simulation_x(offset + 1);
// 		set_tile(&foreground, *tile_position, 4);
// 		draw_tile(&foreground, *tile_position);
// 	}
// 	tile_position->x = get_simulation_x(offset + middle_length + 2);
// 	set_tile(&foreground, *tile_position, 0);
// 	draw_tile(&background, *tile_position);
// }

// void simulate_moveables()
// {
// 	// Update the simulation
// 	simulation_x = (simulation_x + 1) % SCREEN_WIDTH_TILE;

// 	Vector2 vec = {0, 9};
// 	simulate_single_car(&vec, 0);
// 	simulate_single_car(&vec, 8);
// 	vec.y++;
// 	simulate_single_car(&vec, 4);
// 	vec.y++;
// 	simulate_single_car(&vec, 5);
// 	vec.y++;
// 	simulate_single_car(&vec, 1);
// 	simulate_single_car(&vec, 10);

// 	vec.y = 7;
// 	simulate_single_log(&vec, 3, 0);
// 	simulate_single_log(&vec, 2, 7);
// 	vec.y--;
// 	simulate_single_log(&vec, 8, 2);
// 	vec.y--;
// 	simulate_single_log(&vec, 2, 5);
// 	simulate_single_log(&vec, 4, 10);
// 	vec.y--;
// 	simulate_single_log(&vec, 0, 2);
// 	simulate_single_log(&vec, 0, 6);
// 	simulate_single_log(&vec, 0, 10);
// }

// inline void black_screen()
// {
// 	Vector2 screen_zero = {0, 0};
// 	Vector2 screen_max = {SCREEN_WIDTH, SCREEN_HEIGHT / 10};
// 	for (int i = 1; i <= 10; i++)
// 	{
// 		draw_rect(&screen_zero, &screen_max, text_color[0]);
// 		screen_zero.y = screen_max.y;
// 		screen_max.y = (SCREEN_HEIGHT / 10 * i);
// 	}
// }

// void draw_start_screen();
// void nunchuk_disconnected(nunchuk_screen screen);

// inline void draw_start_screen()
// {
// 	BasicImage logo = { {34, 75}, &image_croaker_logo };
// 	black_screen();
// 	draw_image(&logo);
// 	draw_string({40, 220}, (char *) "Press C to start");
// 	bool is_pressed = get_nunchuk_state(NUNCHUK_ADDRESS).nunchuk_c == PRESSED;
// 	while(!is_pressed)
// 	{
// 		nunchuk_state nunchuk = get_nunchuk_state(NUNCHUK_ADDRESS);
// 		if (!nunchuk.connected) nunchuk_disconnected(START_SCREEN);
// 		is_pressed = nunchuk.nunchuk_c == PRESSED;
// 	}
// }

// inline void nunchuk_disconnected(nunchuk_screen screen)
// {
// 	black_screen();
// 	switch (screen)
// 	{
// 		case START_UP:
// 			draw_string({35, 150}, (char *) "ATTACH A NUNCHUK");
// 			while (!init_nunchuk(NUNCHUK_ADDRESS)) { _delay_ms(100); }
// 			break;
// 		case START_SCREEN:
// 			draw_string({35, 150}, (char *) "ATTACH A NUNCHUK");
// 			while (!init_nunchuk(NUNCHUK_ADDRESS)) { _delay_ms(100); }
// 			draw_start_screen();
// 			break;
// 		case GAME_SCREEN:
// 			draw_string({55, 140}, (char *) "PLEASE RESET");
// 			draw_string({15, 160}, (char *) "NUNCHUK DISCONNECTED");
// 			while(true) {}
// 			break;
// 		default:
// 			break;
// 	}
// }

// int main(void)
// {
// 	sei();

// 	// Initialize required functionalities
// 	init_gfx();

// 	if (!init_nunchuk(NUNCHUK_ADDRESS))
// 		nunchuk_disconnected(START_SCREEN);

// 	draw_start_screen();

// 	setup_global_timer();
// 	init_ir(FREQ_VAL_56KHZ);
	
// 	// Draw the background & foreground
// 	draw_tilemap(&background);
// 	draw_tilemap(&foreground);

// 	uint8_t is_at_end = false;

// 	draw_image_mask(&players[0].image);

// 	Vector2 topbar_begin = {0, 0};
// 	Vector2 topbar_end = {240, 40};

// 	draw_rect(&topbar_begin, &topbar_end, text_color[0]);
// 	draw_string({10, 2}, "Highscore");
// 	{
// 		uint8_t highscore = load_value(eeprom_location::HIGH_SCORE);
// 		char score_buffer[4];
// 		uint8_to_string(score_buffer, highscore);
// 		draw_string({20 + 10 * 10, 2}, score_buffer);
// 	}
// 	draw_string({10, 22}, "Current Time");
// 	draw_string({20 + 12 * 10, 22}, "00000");

// 	// Array for positions of the other player
// 	Vector2 second_player_coords;
// 	second_player_coords.x = players[1].spawn.x;
// 	second_player_coords.y = players[1].spawn.y;

// 	// Init the game timers
// 	uint32_t next_message = global_time;
// 	uint32_t next_move_tick = global_time;
// 	uint32_t next_moveable_tick = global_time + 150;
// 	uint32_t next_second = global_time;

// 	// Main game loop
// 	while (1)
// 	{
// 		nunchuk_state nunchuk = get_nunchuk_state(NUNCHUK_ADDRESS);
// 		if(!nunchuk.connected) nunchuk_disconnected(GAME_SCREEN);
// 		nunchuk_joystick_state y_val = nunchuk.nunchuk_y;
// 		nunchuk_joystick_state x_val = nunchuk.nunchuk_x;

// 		if (global_time >= next_second)
// 		{
// 			next_second = global_time + SECOND;
// 			char time_buffer[6];
// 			uint16_to_string(time_buffer, (uint16_t)(global_time / 1000));
// 			draw_string({20 + 12 * 10, 22}, time_buffer);

// 			show_on_segment_display((global_time / 1000) % 10);
// 		}

// 		if (global_time >= next_moveable_tick)
// 		{
// 			next_moveable_tick = global_time + MOVEABLE_MOVE_SPEED;
// 			simulate_moveables();
// 			// Send the player position after we simulated the cars, this is to prevent it from interferring with the timings
// 			ir_send_message(&players[0].image.position);
// 		}

// 		if (global_time >= next_move_tick)
// 		{
// 			next_move_tick = global_time + MOVEMENT_INTERVAL;

// 			move_player(&players[0], {
// 				(x_val == LEFT) ? (int16_t)-1 : (x_val == RIGHT) ? (int16_t)1 : (int16_t)0,
// 				(y_val == UP) ? (int16_t)-1 : (y_val == DOWN) ? (int16_t)1 : (int16_t)0
// 			});

// 			// Move the position of the enemy frog by using the received coordinates
// 			move_image(&players[1].image, &second_player_coords);
// 		}

// 		// Update the IR
// 		// ir_heartbeat();

// 		// Get the latest available data using a vector2 to write to
// 		ir_get_latest_data_packet(&second_player_coords);
// 	}
// }


#include <avr/io.h>

int main(void)
{
    Serial.begin(9600);
    DDRB |= (1 << PB1); // Init pin 9 as output

    // prescaler 8
    TCCR1A |= (1 << WGM10) | (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11);

    OCR1A = 255; // Compare value

    TCCR1A |= (1 << COM1A1); // Enable the output on pin 9

	while (1)
    {
        serial.println("test")
    }
}