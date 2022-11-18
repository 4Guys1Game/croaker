
#include "conversion.h"

char *uint64_to_string(char* buffer, uint16_t n)
{
	for (uint8_t idx = 21; idx > 0;)
	{
		idx--;
		buffer[idx] = (n % 10) + '0';
		n /= 10;
	}
	buffer[21] = '\0';
	return buffer;
}

char *uint32_to_string(char* buffer, uint32_t n)
{
	for (uint8_t idx = 11; idx > 0;)
	{
		idx--;
		buffer[idx] = (n % 10) + '0';
		n /= 10;
	}
	buffer[11] = '\0';
	return buffer;
}

char *uint16_to_string(char* buffer, uint16_t n)
{
	for (uint8_t idx = 6; idx > 0;)
	{
		idx--;
		buffer[idx] = (n % 10) + '0';
		n /= 10;
	}
	buffer[6] = '\0';
	return buffer;
}

char *uint8_to_string(char* buffer, uint8_t n)
{
	for (uint8_t idx = 4; idx > 0;)
	{
		idx--;
		buffer[idx] = (n % 10) + '0';
		n /= 10;
	}
	buffer[4] = '\0';
	return buffer;
}
