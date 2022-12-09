
#ifndef __COLLISION__
#define __COLLISION__

#include "gfx.h"

#define MOVEMENT_SPEED 20
#define MOVEMENT_INTERVAL 150

// Is a tile standable for the player?
uint8_t is_position_standable(Vector2 *position);

// This does bounce checking and checks if the player can even stand on a tile
// This function also resets the player position if collision is detected
uint8_t move_player(Player *plr, Vector2 delta);

#endif
