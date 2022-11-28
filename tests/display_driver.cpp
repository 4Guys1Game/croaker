
#include "display_driver.h"

void flash_screen()
{
	init_spi();

	spi_begin_write();
	spi_send_command(CMD_COLUMN_ADDRESS_SET);
	spi_write16(0);
	spi_write16(240);

	spi_send_command(CMD_PAGE_ADDRESS_SET);
	spi_write16(0);
	spi_write16(200);
	spi_send_command(CMD_MEMORY_WRITE);

	for (uint8_t x = 0; x < 240; x++)
	{
		for (uint8_t y = 0; y < 200; y++)
		{
			spi_write(0x00);
			spi_write(0x8f);
		}
		for (uint8_t y = 0; y < 120; y++)
		{
			spi_write(0x00);
			spi_write(0x8f);
		}
	}
	spi_end_write();

	while (1)
	{
		spi_begin_write();
		spi_send_command(CMD_MEMORY_WRITE);
		for (uint8_t x = 0; x < 240; x++)
		{
			for (uint8_t y = 0; y < 200; y++)
			{
				spi_write16(0x008f);
			}
			for (uint8_t y = 0; y < 120; y++)
			{
				spi_write16(0x008f);
			}
		}
		spi_end_write();

		spi_begin_write();
		spi_send_command(CMD_MEMORY_WRITE);
		for (uint8_t x = 0; x < 240; x++)
		{
			for (uint8_t y = 0; y < 200; y++)
			{
				spi_write16(0xf800);
			}
			for (uint8_t y = 0; y < 120; y++)
			{
				spi_write16(0xf800);
			}
		}
		spi_end_write();
	}
}
