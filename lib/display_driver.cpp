
#include "display_driver.h"

inline void output_dc_cs()
{
	DDRB |= (1 << TFT_CS_PORT);
	DDRB |= (1 << TFT_DC_PORT);
}

inline void input_dc_cs()
{
	DDRB &= ~(1 << TFT_CS_PORT);
	DDRB &= ~(1 << TFT_DC_PORT);
}

inline void set_dc_high()
{
	PORTB |= (1 << TFT_DC_PORT);
}

inline void set_dc_low()
{
	PORTB &= ~(1 << TFT_DC_PORT);
}

inline void set_cs_high()
{
	PORTB |= (1 << TFT_CS_PORT);
}

inline void set_cs_low()
{
	PORTB &= ~(1 << TFT_CS_PORT);
}

static inline void display_write(uint8_t data)
{
	SPDR = data;
	// Wait until write is finished
	asm volatile("nop");
	while (!(SPSR & _BV(SPIF)))
		;
}

static inline void display_write16(uint16_t data)
{
	display_write(data >> 8);
	display_write(data);
}

static inline void display_begin_write()
{
	set_cs_low();
}

static inline void display_end_write()
{
	set_cs_high();
}

static inline void display_send_command(uint8_t cmd)
{
	set_dc_low();
	display_write(cmd);
	set_dc_high();
}

// Private function; only used to send the initial commands to the screen
void spi_send_command_args(uint8_t cmd, uint8_t *args, uint8_t len)
{
	display_begin_write();

	set_dc_low();
	display_write(cmd);
	set_dc_high();

	for (uint8_t idx = 0; idx < len; idx++)
	{
		display_write(*args);
		args++;
	}

	display_end_write();
}

void init_display()
{
	output_dc_cs();

	// Enable SPI and set to master mode
	SPCR |= (1 << SPE) | (1 << MSTR);
	// Set clock divider to 2
	SPSR |= (1 << SPI2X);
	// Set bit order (MSBFirst)
	SPCR &= ~(1 << DORD);
	// Set data mode (mode 0)
	SPCR &= ~((1 << CPOL) | (1 << CPHA));
	// Enable the internal pull-ups of SS
	PORTB |= (1 << PB1) | (1 << PB2);
	// Make sure the correct pins are set to output (CLK, MOSI, SS)
	DDRB |= (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB5);

	// Force a software reset
	display_send_command(0x01);
	_delay_ms(150);

	// Copied from Adafruit ILI9341
	uint8_t init_cmd[] = {
		// Exclusive to the Adafruit ILI
		CMD_UNDOCUMENTED_PREBOOT1, 3, 0x03, 0x80, 0x02, // I wasn't able to find documentation on what these do
		CMD_UNDOCUMENTED_PREBOOT2, 3, 0x00, 0xC1, 0x30,
		CMD_POWER_ON_SEQUENCE, 4, 0x64, 0x03, 0x12, 0x81,
		CMD_DRIVER_TIMING_CONTROL_A, 3, 0x85, 0x00, 0x78,
		CMD_POWER_CONTROL_A, 5, 0x39, 0x2C, 0x00, 0x34, 0x02,
		CMD_PUMP_RATIO_CONTROL, 1, 0x20,
		CMD_DRIVER_TIMING_CONTROL_B, 2, 0x00, 0x00,

		CMD_POWER_CONTROL1, 1, 0x23,				   // Power control VRH[5:0]
		CMD_POWER_CONTROL2, 1, 0x10,				   // Power control SAP[2:0];BT[3:0]
		CMD_VCOM_CONTROL1, 2, 0x3e, 0x28,			   // VCM control
		CMD_VCOM_CONTROL2, 1, 0x86,					   // VCM control2
		CMD_MEMORY_ACCESS_CONTROL, 1, 0x48,			   // Memory Access Control
		CMD_VERTICAL_SCROLLING_START_ADDRESS, 1, 0x00, // Vertical scroll zero
		CMD_PIXEL_FORMAT, 1, 0x55,
		CMD_FRAME_RATE_CONTROL, 2, 0x00, 0x18,
		CMD_DISPLAY_FUNCTION_CONTROL, 3, 0x08, 0x82, 0x27,																			 // Display Function Control
		CMD_ENABLE_3G, 1, 0x00,																										 // 3Gamma Function Disable
		CMD_GAMMA_SET, 1, 0x01,																										 // Gamma curve selected
		CMD_POSITIVE_GAMMA_CORRECTION, 15, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00, // Set Gamma
		CMD_NEGATIVE_GAMMA_CORRECTION, 15, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F, // Set Gamma
		CMD_SLEEP_OUT, 0x80,																										 // Exit Sleep
		CMD_DISPLAY_ON, 0x80,																										 // Display on
		CMD_NOP																														 // End of list
	};

	// Send a bunch of initial data
	uint8_t cmd, x, numArgs;
	uint8_t *addr = init_cmd;
	while ((cmd = *(addr++)) > 0)
	{
		x = *(addr++);
		numArgs = x & 0x7F;
		spi_send_command_args(cmd, addr, numArgs);
		addr += numArgs;
		if (x & 0x80)
		{
			_delay_ms(150);
		}
	}
}
