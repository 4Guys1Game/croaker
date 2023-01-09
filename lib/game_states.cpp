
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

#define END_STATUS 222
#define ACKNOWLEDGEMENT_STATUS 233
#define NEXT_LEVEL_STATUS 244
#define DISCONNECT_STATUS 250

volatile uint8_t current_status = 0;
volatile uint8_t player_1_end = 0;
volatile uint8_t player_2_end = 0;
volatile uint8_t next_level = 0;
volatile uint32_t time_when_won = 0;
volatile uint32_t time_difference_in_ms = 0;

void gamestate_get_status(uint8_t *status){
    ir_get_current_status(status);
    current_status = *status;
}

void check_if_player_1_end(Vector2 *player_1_pos, uint8_t *player_1_end_main){
    if(player_1_pos->y < 50)
    {
        player_1_end = 1;
        time_when_won = global_time;
    }
    else
    {
        player_1_end = 0;
    }
    *player_1_end_main = player_1_end;
}

void check_for_time_difference(uint16_t *time)
{
    if(time_difference_in_ms != 0)
    {
        *time = time_difference_in_ms;
        time_difference_in_ms = 0;
    }
}

void get_win_time_if_applicable(uint8_t *winner, uint16_t *current_score)
{
    if(*winner == 1)
    {
        uint16_t win_time = 0;
        check_for_time_difference(&win_time);
        current_score += win_time;
    }

}

void gamestate_set_new_send_status(uint8_t *winner, uint8_t *player_1_end_main, uint8_t *player_2_end_main, uint8_t *status_to_send)
{
    if(*player_1_end_main == 1 && *player_2_end_main == 0){
        *status_to_send = END_STATUS;
    }else if(*player_1_end_main == 0 && *player_2_end_main == 1)
    {
        // Do nothing because of the fact player 1 hasn't finished yet
    }
}

void check_for_end(Vector2 *player_1_pos, uint8_t *player_1_end_main, uint8_t *status, uint8_t *player_2_end_main, uint8_t *winner, uint16_t *time_faster_than_enemy)
{
    // Check if the game has ended by way of player 1 reaching the end
    check_if_player_1_end(player_1_pos, player_1_end_main);
    player_1_end = *player_1_end_main;
    // Check if the game has ended by way of player 2 reaching the end
    if(current_status == END_STATUS)
    {
        player_2_end = 1;
        *player_2_end_main = 1;
    }
    // Check to see if a winner has been decided
    if(player_1_end == 1 && player_2_end == 0)
    {
        *winner = 1;
    }
    else if(player_1_end == 0 && player_2_end == 1)
    {
        *winner = 2;
    }

    // Get the time difference between when the current player ended and when the other player did
    get_win_time_if_applicable(winner, time_faster_than_enemy);

}

void set_status_to_send(uint8_t *status)
{
    uint8_t current_status = 0;
    ir_get_current_status(&current_status);
    if(player_1_end == 1 && current_status != END_STATUS)
    {
        *status = END_STATUS;
    }
    else if(player_1_end == 1 && current_status == END_STATUS)
    {
        *status = NEXT_LEVEL_STATUS;
    }
    else if(player_2_end == 1 && current_status != NEXT_LEVEL_STATUS)
    {
        *status = ACKNOWLEDGEMENT_STATUS;
    }
    else if(player_2_end == 1 && current_status == NEXT_LEVEL_STATUS)
    {
        *status = 0;
    }
}

void check_for_next_level(uint8_t *status)
{
    uint8_t current_status = 0;
    ir_get_current_status(&current_status);
    if(current_status == 244 || (player_1_end == 1 && current_status == 233))
    {
        *status = 1;
    }
    else
    {
        *status = 0;
    }
}

void check_for_received_win(uint8_t *player_1_win)
{
    uint8_t status = 0;
    ir_get_current_status(&status);
    if(status == END_STATUS)
    {
        *player_1_win = 1;
    }
    else
    {
        *player_1_win = 0;
    }
}

void check_for_acknowledgement_status(uint8_t *acknowledged){
    uint8_t status = 0;
    ir_get_current_status(&status);
    if(status == ACKNOWLEDGEMENT_STATUS)
    {
        *acknowledged = 1;
    }
    else
    {
        *acknowledged = 0;
    }
}

void get_status_to_send(uint8_t *player_1_win, uint8_t *player_2_win, uint8_t *status){
    if(*player_1_win == 1)
    {
        *status = END_STATUS;
    }
    else if(*player_2_win == 1)
    {
        *status = ACKNOWLEDGEMENT_STATUS;
    }
}