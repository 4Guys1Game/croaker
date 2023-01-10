
#include <avr/io.h>

// Show a digit on the screen, any 8 bit number is valid but it will be modulo'd by 16
void show_on_segment_display(uint8_t value);
