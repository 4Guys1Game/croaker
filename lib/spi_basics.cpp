
#include "spi_basics.h"

static inline void output_dc_cs()
{
	DDRB |= (1 << TFT_CS_PORT);
	DDRB |= (1 << TFT_DC_PORT);
}

static inline void input_dc_cs()
{
	DDRB &= ~(1 << TFT_CS_PORT);
	DDRB &= ~(1 << TFT_DC_PORT);
}

static inline void set_dc_high()
{
	PORTB |= (1 << TFT_DC_PORT);
}

static inline void set_dc_low()
{
	PORTB &= ~(1 << TFT_DC_PORT);
}

static inline void set_cs_high()
{
	PORTB |= (1 << TFT_CS_PORT);
}

static inline void set_cs_low()
{
	PORTB &= ~(1 << TFT_CS_PORT);
}

static inline void spi_write(uint8_t data)
{
	SPDR = data;
	// Wait until write is finished
	asm volatile("nop");
	while (!(SPSR & _BV(SPIF)))
		;
}

static inline void spi_write16(uint16_t data)
{
	spi_write(data >> 8);
	spi_write(data);
}


