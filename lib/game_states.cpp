
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "global_time.h"
#include "conversion.h"
#include "ir.h"
#include "gfx.h"

#define WIN_STATUS 222
#define ACKNOWLEDGEMENT_STATUS 233
#define NEXT_LEVEL_STATUS 244

volatile uint8_t player_1_win = 0;
volatile uint8_t player_2_win = 0;
volatile uint8_t next_level = 0;

void *check_for_win(Vector2 *player_1_pos, uint8_t *player_1_win_main)
{
    if(player_1_pos->y < 50)
    {
        player_1_win = 1;
    }
    else
    {
        player_1_win = 0;
    }
    *player_1_win_main = player_1_win;
}

void *set_status_to_send(uint8_t *status)
{
    uint8_t current_status = 0;
    ir_get_current_status(&current_status);
    if(player_1_win == 1 && current_status != ACKNOWLEDGEMENT_STATUS)
    {
        *status = WIN_STATUS;
    }
    else if(player_1_win == 1 && current_status == ACKNOWLEDGEMENT_STATUS)
    {
        *status = NEXT_LEVEL_STATUS;
    }
    else if(player_2_win == 1 && current_status != NEXT_LEVEL_STATUS)
    {
        *status = ACKNOWLEDGEMENT_STATUS;
    }
    else if(player_2_win == 1 && current_status == NEXT_LEVEL_STATUS)
    {
        *status = 0;
    }
}

void *check_for_next_level(uint8_t *status)
{
    uint8_t current_status = 0;
    ir_get_current_status(&current_status);
    if(current_status == 244 || (player_1_win == 1 && current_status == 233))
    {
        *status = 1;
    }
    else
    {
        *status = 0;
    }
}

void *check_for_received_win(uint8_t *player_1_win)
{
    uint8_t status = 0;
    ir_get_current_status(&status);
    if(status == WIN_STATUS)
    {
        *player_1_win = 1;
    }
    else
    {
        *player_1_win = 0;
    }
}

void *check_for_acknowledgement_status(uint8_t *acknowledged){
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

void *get_status_to_send(uint8_t *player_1_win, uint8_t *player_2_win, uint8_t *status){
    if(*player_1_win == 1)
    {
        *status = WIN_STATUS;
    }
    else if(*player_2_win == 1)
    {
        *status = ACKNOWLEDGEMENT_STATUS;
    }
}