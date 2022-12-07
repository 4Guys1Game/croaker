/*
 * A stripped version of the Nunchuk.h library
 */
#ifndef NUNCHUK_H_
#define NUNCHUK_H_

#include <stdint.h>

// An enum with the possible joystick states
enum nunchuk_joystick_state
{
    UP,
    DOWN,
    MIDDLE,
    LEFT,
    RIGHT
};

// An enum with the possible button states
enum nunchuk_button_state
{
    RELEASED,
    PRESSED
};

// A struct for containing the state of the Nunchuk
struct nunchuk_state
{
    nunchuk_joystick_state nunchuk_x;
    nunchuk_joystick_state nunchuk_y;
    nunchuk_button_state nunchuk_z;
    nunchuk_button_state nunchuk_c;
};

// A function for initializing contact with the Nunchuk
bool init_nunchuk(uint8_t address);
// A function for getting the state of the Nunchuk
nunchuk_state get_nunchuk_state(uint8_t address);

#endif