#ifndef __NUNCHUCK_VALUE__
#define __NUNCHUK_VALUE__
#include <stdint.h>

// An enum with the different nunchuk joystick values.
enum nunchuk_read_joystick  { Y, X };

// An enum with the different nunchuk button values.
enum nunchuk_read_button    { C, Z };

// An enum with the possible joystick states
enum nunchuk_joystick_state { UP, DOWN, MIDDLE, LEFT, RIGHT};

// An enum with the possible button states
enum nunchuk_button_state   { RELEASED, PRESSED };

bool init_nunchuk(uint8_t address);
bool is_connected();
nunchuk_joystick_state get_joystick_state(nunchuk_read_joystick x_or_y);
nunchuk_button_state get_button_state(nunchuk_read_button x_or_y);
#endif