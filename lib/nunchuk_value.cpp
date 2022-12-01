#include "nunchuk_value.h"
#include <Nunchuk.h>
#include <Wire.h>

// The value of the Nunchuk joystick when it is not pointed anywhere
#define MIDDLE_Y 		    136
#define MIDDLE_X 		    125

// The offset used to make sure the joystick is not too sensitive
#define OFFSET 	 		    15

// A variable used for storing the Nunchuk address in
volatile uint8_t nunchuk_address = 0;

bool init_nunchuk(uint8_t address)
{
    // Enable wire communication
    Wire.begin();

    // Set the used address
    nunchuk_address = address;

    // Begin communication with the Nunchuk and return if that is successful
    return Nunchuk.begin(address);
}

// Check if a Nunchuk is connected
bool is_connected()
{
    return Nunchuk.getState(nunchuk_address);
}

// Read the value of the Nunchuk's joystick X- or Y-axis
nunchuk_joystick_state get_joystick_state(nunchuk_read_joystick x_or_y)
{
    // Check first to see if the Nunchuk is still connected
    if (!is_connected())
        return MIDDLE;

    // Read the value
    uint8_t value = x_or_y == X ? Nunchuk.state.joy_x_axis : Nunchuk.state.joy_y_axis;

    // Return the correct enum value
    if (x_or_y == X)
        return value > (MIDDLE_X + OFFSET) ? RIGHT : value < (MIDDLE_X - OFFSET) ? LEFT : MIDDLE;
    else
        return value > (MIDDLE_Y + OFFSET) ? UP : value < (MIDDLE_Y - OFFSET) ? DOWN : MIDDLE;
}

// Read the value of the Nunchuk's C- or Z-button
nunchuk_button_state get_button_state(nunchuk_read_button c_or_z)
{
    // Check first to see if the Nunchuk is still connected
    if (!is_connected())
        return RELEASED;

    // Read the value
    uint8_t value = c_or_z == C ? Nunchuk.state.c_button : Nunchuk.state.z_button;

    // Return the correct enum value
    return value == 1 ? PRESSED : RELEASED;
}