
#ifndef __SPI_BASICS__
#define __SPI_BASICS__

#include <avr/io.h>

#define TFT_DC 9
#define TFT_CS 10
#define TFT_DC_PORT PB1
#define TFT_CS_PORT PB2

void output_dc_cs();
void input_dc_cs();
void set_dc_high();
void set_dc_low();
void set_cs_high();
void set_cs_low();
void spi_write(uint8_t data);
void spi_write16(uint16_t data);

#endif

