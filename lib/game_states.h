#include "prelude.h"

extern uint8_t amount_of_wins;

void gamestate_get_wins(uint8_t *wins);

void gamestate_calculate_score(uint32_t *score_in_ms, uint32_t *score_to_return);

void gamestate_get_status(uint8_t *status);

// Check if the game has ended, who won and by how much
void check_for_end(Vector2 *player_1_pos, uint8_t *player_1_win, uint8_t *status, uint8_t *player_2_win, uint8_t *winner, uint32_t *player_time_faster);

void check_for_time_difference(uint32_t *time);

void get_win_time_if_applicable(uint8_t *winner, uint32_t *current_score);

void gamestate_set_new_send_status(uint8_t *winner, uint8_t *player_1_end, uint8_t *player_2_end, uint8_t *status_to_send, uint8_t *received_status);
