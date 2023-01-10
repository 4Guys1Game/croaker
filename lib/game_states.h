#include "prelude.h"

void gamestate_get_status(uint8_t *status);

// Check if the game has ended, who won and by how much
void check_for_end(Vector2 *player_1_pos, uint8_t *player_1_win, uint8_t *status, uint8_t *player_2_win, volatile uint8_t *winner, uint16_t *player_time_faster);

void check_for_time_difference(uint16_t *time);

void get_win_time_if_applicable(uint8_t *winner, uint16_t *current_score);

void gamestate_set_new_send_status(volatile uint8_t *winner, uint8_t *player_1_end, uint8_t *player_2_end, volatile uint8_t *status_to_send, uint8_t *received_status);
