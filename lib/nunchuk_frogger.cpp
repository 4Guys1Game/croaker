/*
 * A stripped version of the Nunchuk.h library
 */
#include <util/delay.h>
#include <Wire.h>
#include "nunchuk_frogger.h"

// Memory addresses of the Nunchuk
#define NCSTATE 0x00 // State address (6 bytes)
#define NCID 0xFA    // ID address (4 bytes)

#define CHUNKLEN 32
#define STATELEN 6

// Ms to wait before reading the Wire
#define WAITFORREAD 1

// Deadzone for the Nunchuk
#define OFFSET 50

// Byte length of the ID
#define IDLEN 4

// Array used for converting a Nibble to Ascii/Hex
char btoa[] = {'0', '1', '2', '3', '4', '5', '6', '7',
               '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

// Buffer in which to store received data
uint8_t buffer[CHUNKLEN];

// Values used in calibration
uint8_t middle_x, middle_y;

// The state of the Nunchuk
nunchuk_state state = {MIDDLE, MIDDLE, RELEASED, RELEASED};

// A variable for containing the Nunchuk id
char id[2 * IDLEN + 3];

// Prototypes
bool _get_id(uint8_t address);
uint8_t _read(uint8_t address, uint8_t offset, uint8_t len);
bool _calibrate(uint8_t address);
bool _update_nunchuk_state(uint8_t address, bool calibrate = false);

// Initialize connection to Nunchuk
bool init_nunchuk(uint8_t address)
{
    Wire.begin();
    Wire.beginTransmission(address);
    Wire.write(0xF0);
    Wire.write(0x55);
    Wire.endTransmission(true);
    Wire.beginTransmission(address);
    Wire.write(0xFB);
    Wire.write(0x00);
    Wire.endTransmission(true);

    return _calibrate(address);
}

// Read the value of the Nunchuk
nunchuk_state get_nunchuk_state(uint8_t address)
{
    // Check first to see if the Nunchuk is still connected and reset state if not
    if (!_update_nunchuk_state(address))
        state = {MIDDLE, MIDDLE, RELEASED, RELEASED};

    // Return the state
    return state;
}

// Get the current state of the Nunchuk
// The byte is divided as such:
// Byte 0: SX[7:0]
// Byte 1: SY[7:0]
// Byte 5: BC, BZ
bool _update_nunchuk_state(uint8_t address, bool calibrate)
{
    // Get the state from the provided address
    if (_read(address, NCSTATE, STATELEN) != STATELEN)
        return (false);

    uint8_t x_val = buffer[0];
    uint8_t y_val = buffer[1];
    uint8_t z_val = !(buffer[5] & 0x01);
    uint8_t c_val = !((buffer[5] & 0x02) >> 1);

    // Calibrate the Nunchuk if needed
    if (calibrate)
    {
        middle_x = x_val;
        middle_y = y_val;
    }

    // Read the joystick values
    state.nunchuk_x = x_val > (middle_x + OFFSET) ? RIGHT : x_val < (middle_x - OFFSET) ? LEFT
                                                                                        : MIDDLE;
    state.nunchuk_y = y_val > (middle_y + OFFSET) ? UP : y_val < (middle_y - OFFSET) ? DOWN
                                                                                     : MIDDLE;

    // Read the button values
    state.nunchuk_z = z_val == 1 ? PRESSED : RELEASED;
    state.nunchuk_c = c_val == 1 ? PRESSED : RELEASED;

    return true;
}

// A function used for calibrating the Nunchuk
bool _calibrate(uint8_t address)
{
    if (!_get_id(address))
        return false;

    return _update_nunchuk_state(address, true);
}

// Get the id of a connected Nunchuk
bool _get_id(uint8_t address)
{
    // Try to read data from the Nunchuk
    if (_read(address, NCID, IDLEN) != IDLEN)
        return false;

    // Create the id
    id[0] = '0';
    id[1] = 'x';
    for (uint8_t i = 0; i < IDLEN; i++)
    {
        id[2 + 2 * i] = btoa[(buffer[i] >> 4)];
        id[2 + 2 * i + 1] = btoa[(buffer[i] & 0x0F)];
    }
    id[2 * IDLEN + 2] = '\0';

    return true;
}

// Read from the Nunchuk
uint8_t _read(uint8_t address, uint8_t offset, uint8_t len)
{
    uint8_t n = 0;

    // Send the offset
    Wire.beginTransmission(address);
    Wire.write(offset);
    Wire.endTransmission(true);

    // Wait for the offset to arrive
    _delay_ms(WAITFORREAD);

    // Request the amount of bytes that contain the Nunchuk data
    Wire.requestFrom(address, len);

    // Read through the bytes
    while (Wire.available() && n <= len)
        buffer[n++] = Wire.read();

    // Return the number of bytes read
    return n;
}