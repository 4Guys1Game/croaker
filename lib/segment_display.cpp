
#include <Wire.h>

// The IO expander address
#define IO_EXPANDER_ADDR 0x39
#define MAX_DISPLAY_RANGE 16

volatile uint8_t numbers[MAX_DISPLAY_RANGE] = {
        0b01000000, // 0
        0b01111001, // 1
        0b00100100, // 2
        0b00110000, // 3
        0b00011001, // 4
        0b00010010, // 5
        0b00000010, // 6
        0b01111000, // 7
        0b00000000, // 8
        0b00010000, // 9
        0b00001000, // a
        0b00000011, // b
        0b00100111, // c
        0b00100001, // d
        0b00000110, // e
        0b00001110  // f
};

// Writes a byte to the IO expander using I2C
void io_expander_write(uint8_t byte)
{
	Wire.beginTransmission(IO_EXPANDER_ADDR);
	Wire.write(byte);
	Wire.endTransmission();
}

void show_on_segment_display(uint8_t value) {
	io_expander_write(numbers[value % MAX_DISPLAY_RANGE]);
}
