
#include <avr/delay.h>

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

static inline void touch_write(uint8_t reg, uint8_t data)
{
    set_cs_low();
    touch_transfer(TS_WRITE_BIT | reg);
    touch_transfer(data);
    set_cs_high();
}

static inline uint8_t touch_read(uint8_t reg)
{
    set_cs_low();
    touch_transfer(TS_READ_BIT | reg);
    // I'm not sure why we send two zeroes when trying to read a register when the documentation says we only need one
    // But the official driver does this as well? So it's fine I suppose?
    // But it doesn't seem to work otherwise
    touch_transfer(0);
    uint8_t data = touch_transfer(0);
    set_cs_high();
    return data;
}

inline static uint8_t is_screen_being_touched()
{
    uint8_t touch_register = touch_read(TS_CMD_TSC_CTRL);
    return touch_register & TS_TSC_CTRL_TOUCHED;
}

void touch_setup_registers()
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
}

void init_touch()
{
    touch_setup_registers();

    // Print screen version, comment this out during production
    // uint16_t screen_version = (touch_read8(0) << 8) + touch_read8(1);
    // Serial.println(screen_version);

    // Reset
    touch_write(TS_CMD_RESET1, TS_RESET1_SOFTRESET); // Reset 1
    _delay_ms(10); // Give it time to reset
    touch_write(TS_CMD_RESET2, 0x00); // Reset 2

    // Enable touch
    touch_write(TS_CMD_TSC_CTRL, TS_TSC_CTRL_EN);
    // ADC
    touch_write(TS_CMD_ADC_CTRL1, TS_ADC_CTRL1_SAMPLE0 | TS_ADC_CTRL1_SAMPLE2);
    touch_write(TS_CMD_ADC_CTRL2, TS_ADC_CTRL2_FREQ1);
    // Touchscreen config
    touch_write(TS_CMD_TSC_CFG, TS_TSC_CFG_AVG_CTRL1 | TS_TSC_CFG_TOUCH_DELAY2 | TS_TSC_CFG_SETTLING2);
    touch_write(TS_CMD_TSC_FRACT, TS_TSC_FRACT0 | TS_TSC_FRACT2);
    touch_write(TS_CMD_I_DRIVE, TS_I_DRIVE1);
}


