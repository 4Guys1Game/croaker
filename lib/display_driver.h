
#ifndef __ILI3941_DISPLAY_DRIVER__
#define __ILI3941_DISPLAY_DRIVER__

#include <avr/io.h>
#include <avr/delay.h>

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

void spi_write(uint8_t data);
void spi_write16(uint16_t data);
void spi_begin_write();
void spi_end_write();
void spi_send_command(uint8_t command);
void init_spi();

#endif
