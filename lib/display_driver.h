
#ifndef __ILI3941_DISPLAY_DRIVER__
#define __ILI3941_DISPLAY_DRIVER__

#include <avr/delay.h>
#include <avr/io.h>

// Ports
#define TFT_DC 9
#define TFT_CS 10
#define TFT_DC_PORT PB1
#define TFT_CS_PORT PB2

// Doesn't do anything until CMD_MEMORY_WRITE gets sent
#define CMD_COLUMN_ADDRESS_SET 0x2a
// Doesn't do anything until CMD_MEMORY_WRITE gets sent
#define CMD_PAGE_ADDRESS_SET 0x2b
// Pushes CMD_COLUMN_ADDRESS_SET and CMD_PAGE_ADDRESS_SET
// This command is followed by as many pixels as the user wants to send
#define CMD_MEMORY_WRITE 0x2c

// Other display screen registers
// There are taken from the default driver
#define CMD_POWER_ON_SEQUENCE 0xed
#define CMD_UNDOCUMENTED_PREBOOT1 0xef
#define CMD_UNDOCUMENTED_PREBOOT2 0xcf
#define CMD_DRIVER_TIMING_CONTROL_A 0xe8
#define CMD_DRIVER_TIMING_CONTROL_A2 0xe9
#define CMD_DRIVER_TIMING_CONTROL_B 0xea
#define CMD_POWER_CONTROL_A 0xcb
#define CMD_POWER_CONTROL_B 0xcf
#define CMD_PUMP_RATIO_CONTROL 0xf7
#define CMD_ENABLE_3G 0xf2
#define CMD_POWER_CONTROL1 0xc0
#define CMD_POWER_CONTROL2 0xc1
#define CMD_VCOM_CONTROL1 0xc5
#define CMD_VCOM_CONTROL2 0xc7
#define CMD_MEMORY_ACCESS_CONTROL 0x36
#define CMD_VERTICAL_SCROLLING_START_ADDRESS 0x37
#define CMD_PIXEL_FORMAT 0x3a
#define CMD_FRAME_RATE_CONTROL 0xb1
#define CMD_DISPLAY_FUNCTION_CONTROL 0xb6
#define CMD_GAMMA_SET 0x26
#define CMD_POSITIVE_GAMMA_CORRECTION 0xe0
#define CMD_NEGATIVE_GAMMA_CORRECTION 0xe1
#define CMD_SLEEP_OUT 0x11
#define CMD_DISPLAY_ON 0x29
#define CMD_NOP 0x00

// End a display transmittion
void display_begin_write();
// Begin a display transmittion
void display_end_write();
// Send a command to the screen
void display_send_command(uint8_t command);
// Setup the display
void init_display();
// Setup the registers, this is done by init_display as well, but if the SPI registers change, this must be called again
void display_setup_registers();
// Write a 8 bit value to the display
void display_write(uint8_t data);
// Write a 16 bit value to the display
void display_write16(uint16_t data);

#endif
