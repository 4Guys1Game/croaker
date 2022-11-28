/*
 * A frogger implementation for Arduino
 */
// keep intellisense satisfied
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

 #include <avr/io.h>
 #include <avr/eeprom.h>
 #include <avr/interrupt.h>
 #include <HardwareSerial.h>
 #include <nunchuck_value.h>

// Baudrate for Serial communication
#define BAUDRATE 9600

// The Wire address of the Nunchuk
#define NUNCHUK_ADDRESS 0x52

// Functions for reading and writing values to the EEPROM.
#define load_value(address) 	   eeprom_read_byte((uint8_t *)address)
#define save_value(address, value) eeprom_write_byte((uint8_t *)address, value)

// An enum for the different addresses to read or write to/from on the EEPROM
enum eeprom_location { HIGH_SCORE = EEAR0, OPPONENT_HIGH_SCORE = EEAR0 };

int main(void)
{
    // Enable interrupts
    sei();

    // Begin Serial communication
    Serial.begin(BAUDRATE);

    // Initialize the connection with the nunchuk and stop if it is not found
    if (!init_nunchuk(NUNCHUK_ADDRESS)) return 1;
    
    // Repeat forever
    while (1) {}

    // This is never reached.
    return 0;
}
