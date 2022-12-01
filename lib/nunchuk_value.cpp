#include "nunchuk_value.h"
#include <Nunchuk.h>
#include <Wire.h>

// The offset used to make sure the joystick is not too sensitive
#define OFFSET 50

// Variables used for setting the middle values of the x and y axis
volatile uint8_t middle_y, middle_x;

// A variable used for storing the Nunchuk address in
volatile uint8_t nunchuk_address;

#define IS_CONNECTED() Nunchuk.getState(nunchuk_address)

bool init_nunchuk(uint8_t address)
{
    // Enable wire communication
    Wire.begin();

    // Set the used address
    nunchuk_address = address;

    // Begin communication with the Nunchuk and return if that is successful
    return Nunchuk.begin(address) ? calibrate_nunchuk() : false;
}

// Calibrate the middle values of the nunchuk
bool calibrate_nunchuk()
{
    // Check if the nunchuk is connected
    if (!IS_CONNECTED())
        return false;
    
    // Set the middle values
    middle_y = Nunchuk.state.joy_y_axis;
    middle_x = Nunchuk.state.joy_x_axis;
    
    return true;
}

// Read the value of the Nunchuk's joystick X- or Y-axis
nunchuk_joystick_state get_joystick_state(nunchuk_read_joystick x_or_y)
{
    // Check first to see if the Nunchuk is still connected
    if (!IS_CONNECTED())
        return MIDDLE;

    // Read the value
    uint8_t value = x_or_y == X ? Nunchuk.state.joy_x_axis : Nunchuk.state.joy_y_axis;

    // Return the correct enum value
    if (x_or_y == X)
        return value > (middle_x + OFFSET) ? RIGHT : value < (middle_x - OFFSET) ? LEFT
                                                                                 : MIDDLE;
    else
        return value > (middle_y + OFFSET) ? UP : value < (middle_y - OFFSET) ? DOWN
                                                                              : MIDDLE;
}

// Read the value of the Nunchuk's C- or Z-button
nunchuk_button_state get_button_state(nunchuk_read_button c_or_z)
{
    // Check first to see if the Nunchuk is still connected
    if (!IS_CONNECTED())
        return RELEASED;

    // Read the value
    uint8_t value = c_or_z == C ? Nunchuk.state.c_button : Nunchuk.state.z_button;

    // Return the correct enum value
    return value == 1 ? PRESSED : RELEASED;
}