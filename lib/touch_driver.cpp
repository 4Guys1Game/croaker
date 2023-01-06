
// TODO: Remove these two
#include <HardwareSerial.h>
#include <avr/delay.h>
#include <util/delay.h>

#include "Arduino.h"
#include "touch_driver.h"

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

static inline void touch_write8(uint8_t reg, uint8_t data)
{
    set_cs_low();
    touch_transfer(TS_WRITE_BIT | reg);
    touch_transfer(data);
    set_cs_high();
}

static inline uint8_t touch_read8(uint8_t reg)
{
    set_cs_low();
    touch_transfer(TS_READ_BIT | reg);
    touch_transfer(0);
    uint8_t data = touch_transfer(0);
    set_cs_high();
    return data;
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
    // Force SS to be high
	PORTB |= (1 << PB2);
	// Make sure the correct pins are set to output (CLK, MOSI, SS)
	DDRB |= (1 << PB2) | (1 << PB3) | (1 << PB5);
    // Set MISO to input
	DDRB &= ~(1 << PB4);
    // Set the touchscreen SPI pin to output
    DDRB |= 1 << TS_CS_PORT; 

    Serial.begin(9600);

    // Print screen version, comment this out during production
    // uint16_t screen_version = (touch_read8(0) << 8) + touch_read8(1);
    // Serial.println(screen_version);

    // Reset
    touch_write8(0x03, 0x02); // Reset 1
    _delay_ms(10);
    touch_write8(0x04, 0x00); // Reset 2

    // Enable touch
    touch_write8(0x40, 0x00 | 0x01);
    // ADC
    touch_write8(0x20, 0x00 | (0x06 << 4));
    touch_write8(0x21, 0x02);
    // Touchscreen config
    touch_write8(0x41, 0x80 | 0x20 | 0x04);
    touch_write8(0x56, 0x06);
    touch_write8(0x58, 0x01);

    while (true) {
        uint8_t val = touch_read8(0x40);
        Serial.print("returned: ");
        Serial.println(val);

        _delay_ms(500);
    }
}


