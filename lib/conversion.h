
#ifndef __CONV_LIB__
#define __CONV_LIB__

#include <stdint.h>

// Create a string from a 64 bit number
char *uint64_to_string(char* buffer, uint64_t n);
// Create a string from a 32 bit number
char *uint32_to_string(char* buffer, uint32_t n);
// Create a string from a 16 bit number
char *uint16_to_string(char* buffer, uint16_t n);
// Create a string from a 8 bit number
char *uint8_to_string(char* buffer, uint8_t n);
// Create a string of the binary represenration of a 32 bit number
char* uint32_to_binary_str(char* buffer, uint32_t value);
// Create a string of the binary represenration of a 16 bit number
char* uint16_to_binary_str(char* buffer, uint16_t value);

#endif
