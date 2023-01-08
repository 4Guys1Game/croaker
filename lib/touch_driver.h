
#ifndef __TOUCH_LIB__
#define __TOUCH_LIB__

#include <avr/io.h>

// Ports
#define TS_CS 8
#define TS_CS_PORT PB0

// The bit determining if a SPI transfer is a read or write operation
#define TS_WRITE_BIT 0x00
#define TS_READ_BIT (1 << 7)

// Registers
#define TS_CMD_TSC_CTRL 0x40
#define TS_CMD_TSC_CFG 0x41
#define TS_CMD_RESET1 0x03 // SYS_CTRL1
#define TS_CMD_RESET2 0x04 // SYS_CTRL2
#define TS_CMD_ADC_CTRL1 0x20
#define TS_CMD_ADC_CTRL2 0x21
#define TS_CMD_TSC_FRACT 0x56
#define TS_CMD_I_DRIVE 0x58

// Specific register locations
#define TS_RESET1_HIBERNATE (1 << 0)
#define TS_RESET1_SOFTRESET (1 << 1)
#define TS_RESET2_ADC_OFF (1 << 0)
#define TS_RESET2_TSC_OFF (1 << 1)
#define TS_RESET2_GPIO_OFF (1 << 2)
#define TS_TSC_CTRL_EN (1 << 0)
#define TS_TSC_CTRL_TOUCHED (1 << 7)
#define TS_ADC_CTRL1_SAMPLE0 (1 << 4)
#define TS_ADC_CTRL1_SAMPLE1 (1 << 5)
#define TS_ADC_CTRL1_SAMPLE2 (1 << 6)
#define TS_ADC_CTRL2_FREQ0 (1 << 0)
#define TS_ADC_CTRL2_FREQ1 (1 << 1)
#define TS_TSC_CFG_SETTLING0 (1 << 0)
#define TS_TSC_CFG_SETTLING1 (1 << 1)
#define TS_TSC_CFG_SETTLING2 (1 << 2)
#define TS_TSC_CFG_TOUCH_DELAY0 (1 << 3)
#define TS_TSC_CFG_TOUCH_DELAY1 (1 << 4)
#define TS_TSC_CFG_TOUCH_DELAY2 (1 << 5)
#define TS_TSC_CFG_AVG_CTRL0 (1 << 6)
#define TS_TSC_CFG_AVG_CTRL1 (1 << 7)
#define TS_TSC_FRACT0 (1 << 0)
#define TS_TSC_FRACT1 (1 << 1)
#define TS_TSC_FRACT2 (1 << 2)
#define TS_I_DRIVE0 (1 << 0)
#define TS_I_DRIVE1 (1 << 1)

// A pure write-read operation via SPI to the touch display
// This function is 'raw', it is better to use touch_write or touch_read instead
uint8_t touch_transfer(uint8_t data);
// Write a byte to the touchscreen register
void touch_write(uint8_t reg, uint8_t data);
// Read a byte from a touchscreen register
uint8_t touch_read(uint8_t reg);

// Init the touchscreen
void init_touch();
// Setup the registers, this is done during init_touch as well
// However, if the SPI registers have changed, you need to call this function again
// Just to be sure the commands send correctly
void touch_setup_registers();
// Checks if the screen is being touched
// Returns a zero if the screen is not being touched.
// Returns a non-zero if it is being touched
uint8_t is_screen_being_touched();

#endif
