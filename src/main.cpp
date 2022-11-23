/*
 * A frogger implementation for Arduino
 */
// keep intellisense satisfied
#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

// Header file needed to enable interrupts
 #include <avr/io.h>
 #include <avr/eeprom.h>
 #include <util/delay.h>
 #include <avr/interrupt.h>
 #include <Wire.h>
 #include <HardwareSerial.h>
 #include <Nunchuk.h>

// Baudrate for Serial communication
#define BAUDRATE        9600

// The Wire address of the Nunchuk
#define NUNCHUK_ADDRESS 0x52

// The value of the Nunchuk joystick when it is not pointed
#define MIDDLE_Y        136
#define MIDDLE_X        125

// The offset used to make sure the joystick is not too sensitive
#define OFFSET          15

// An enum with the possible joystick states
enum nunchuk_joystick_state { UP, DOWN, MIDDLE, LEFT, RIGHT};

// An enum with the possible button states
enum nunchuk_button_state { RELEASED, PRESSED };

// Global variables containing the X and Y states of the joycon
volatile nunchuk_joystick_state X_AXIS = MIDDLE;
volatile nunchuk_joystick_state Y_AXIS = MIDDLE;

// Global variables containing the button states of the C and Z buttons
volatile nunchuk_button_state C_BUTTON = RELEASED;
volatile nunchuk_button_state Z_BUTTON = RELEASED;

// An enum for the different places to read or write to/from on the EEPROM
enum eeprom_location { NONE = EEAR0, HIGH_SCORE = EEAR1, OPPONENT_HIGH = EEAR2 };

// An enum for setting EEPROM mode
enum eeprom_read_or_write { READ, WRITE };

volatile struct {
	eeprom_read_or_write state;
	eeprom_location address;
	uint8_t value;
} EEPROM_PROG = { READ, NONE, 0 };

volatile uint8_t EEPROM_VALUE = 0;

ISR(EE_READY_vect)
{
	if (EEPROM_PROG.address == NONE) return;
	if (EEPROM_PROG.state == READ)
		EEPROM_VALUE = eeprom_read_byte((uint8_t *)EEPROM_PROG.address);
	eeprom_write_byte((uint8_t *)EEPROM_PROG.address, EEPROM_PROG.value);
}

// Update the X_AXIS, Y_AXIS, C_BUTTON and Z_BUTTON globals to reflect the state of the nunchuk
void update_nunchuk_state(uint8_t address)
{
    // If the Nunchuk is no longer connected, do not update the variables
    if (!Nunchuk.getState(address)) return;

    // Get the current values
    uint8_t y_val = Nunchuk.state.joy_y_axis;
    uint8_t x_val = Nunchuk.state.joy_x_axis;
    uint8_t c_val = Nunchuk.state.c_button;
    uint8_t z_val = Nunchuk.state.z_button;

    // Update the global variables
    Y_AXIS = y_val > (MIDDLE_Y + OFFSET) ? UP : y_val < (MIDDLE_Y - OFFSET) ? DOWN : MIDDLE;
    X_AXIS = x_val > (MIDDLE_X + OFFSET) ? RIGHT : x_val < (MIDDLE_X - OFFSET) ? LEFT : MIDDLE;
    C_BUTTON = c_val == 1 ? PRESSED : RELEASED;
    Z_BUTTON = z_val == 1 ? PRESSED : RELEASED;
}

// A method to initialize the nunchuk
bool initialize_nunchuk(uint8_t address)
{
    // Enable wire communication.
    Wire.begin();
    
    // Begin communication with the Nunchuk and return if that is successful
    return Nunchuk.begin(NUNCHUK_ADDRESS);
}

int main(void)
{
    // Enable interrupts
    sei();

    // Begin Serial communication
    Serial.begin(BAUDRATE);

    // Initialize the connection with the nunchuk and stop if it is not found
    if (!initialize_nunchuk(NUNCHUK_ADDRESS)) return 1;

    // Repeat forever
    while (1) 
    {
        // Update the Nunchuk global variables
        update_nunchuk_state(NUNCHUK_ADDRESS);
    }

    // This is never reached.
    return 0;
}