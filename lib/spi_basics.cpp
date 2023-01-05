
#include "spi_basics.h"

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


