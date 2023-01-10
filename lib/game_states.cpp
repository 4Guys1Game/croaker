
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "global_time.h"
#include "conversion.h"
#include "ir.h"
#include "gfx.h"
#include "game_states.h"
#include "prelude.h"

uint8_t current_status = 0;
uint8_t next_level = 0;
uint32_t time_when_won = 0;
uint32_t time_difference_in_ms = 0;

void gamestate_get_status(uint8_t *status)
{
    ir_get_current_status(status);
    current_status = *status;
}

void check_if_player_1_end(Vector2 *player_1_pos, uint8_t *player_1_end_main)
{
    // Check if player 1 has reached the top of the screen
    if(player_1_pos->y < 50)
    {
        *player_1_end_main = 1;
        time_when_won = global_time;
    }
    else
    {
        *player_1_end_main = 0;
    }
}

void check_for_time_difference(uint16_t *time)
{
    // Get the difference between the time when player 1 won and now
    time_difference_in_ms = global_time - time_when_won;
    // Check if the difference isn't 0
    if(time_difference_in_ms != 0)
    {
        *time = time_difference_in_ms;
        time_difference_in_ms = 0;
    }
    time_when_won = 0;
}

void get_win_time_if_applicable(uint8_t *winner, uint16_t *current_score)
{
    // If player 1 won
    if(*winner == 1)
    {
        uint16_t win_time = 0;
        check_for_time_difference(&win_time);
        current_score += win_time;
    }
}

void gamestate_set_new_send_status(uint8_t *winner, uint8_t *player_1_end_main, uint8_t *player_2_end_main, uint8_t *status_to_send, uint8_t *received_status)
{
    // Send acknowledgement that we're going to the next level
    if(*received_status == NEXT_LEVEL_STATUS)
    {
        *status_to_send = ACKNOWLEDGEMENT_STATUS;
    }
    // Send end status if player 1 has reached the end
    else if(*player_1_end_main == 1 && *player_2_end_main == 0)
    {
        *status_to_send = END_STATUS;
    }
    // Send end status if player 1 has reached the end while player 2 won
    else if(*player_1_end_main == 1 && *player_2_end_main == 1 && *winner == 2)
    {
        *status_to_send = END_STATUS;
    }
    // Send next level status if both players have reached the end, but player 1 won
    else if(*player_1_end_main == 1 && *player_2_end_main == 1 && *winner == 1)
    {
        *status_to_send = NEXT_LEVEL_STATUS;
    }
    // Set the status to 0 if none of these apply to assure no double statuses are sent
    else
    {
        *status_to_send = 0;
    }
}

void check_for_end(Vector2 *player_1_pos, uint8_t *player_1_end_main, uint8_t *status, uint8_t *player_2_end_main, uint8_t *winner, uint16_t *time_faster_than_enemy)
{
    // Check if the game has ended by way of player 1 reaching the end
    check_if_player_1_end(player_1_pos, player_1_end_main);
    // Check if the game has ended by way of player 2 reaching the end
    if(current_status == END_STATUS)
    {
        *player_2_end_main = 1;
    }
    // Check to see if a winner has been decided
    if(*player_1_end_main == 1 && *player_2_end_main == 0)
    {
        *winner = 1;
    }
    else if(*player_1_end_main == 0 && *player_2_end_main == 1)
    {
        *winner = 2;
    }

    // Get the time difference between when the current player ended and when the other player did
    get_win_time_if_applicable(winner, time_faster_than_enemy);
}
