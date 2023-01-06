
#include "touch_driver.h"
#include <cstdint>

inline void set_cs_high()
{
	PORTB |= (1 << TS_CS_PORT);
}

inline void set_cs_low()
{
	PORTB &= ~(1 << TS_CS_PORT);
}

static inline uint8_t touch_transfer(uint8_t data)
{
	SPDR = data;
	// Wait until write is finished
	asm volatile("nop");
	while (!(SPSR & _BV(SPIF))) {};
    return SPDR;
}

static inline uint16_t touch_transfer16(uint16_t data)
{
    uint16_t retrieved_data = touch_transfer(data >> 8) << 8;
	retrieved_data |= touch_transfer(data);
    return retrieved_data;
}

void init_touch()
{
	// Enable SPI and set to master mode
	SPCR |= (1 << SPE) | (1 << MSTR);
	// Set clock divider to 16
    SPCR |= 1 << SPR0;
    SPCR &= ~(1 << SPR1);
    SPSR &= ~(1 << SPI2X);
	// Set bit order (MSBFirst)
	SPCR &= ~(1 << DORD);
	// Set data mode (mode 0)
	SPCR &= ~((1 << CPOL) | (1 << CPHA));
	// Make sure the correct pins are set to output (CLK, MOSI, SS)
	DDRB |= (1 << PB2) | (1 << PB3) | (1 << PB5);
    // Set MISO to input
	DDRB &= ~(1 << PB4);
    // Set the touchscreen SPI pin to output
    DDRB |= 1 << TS_CS_PORT; 

    // while (true) {}
}


