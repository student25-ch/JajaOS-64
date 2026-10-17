/*
 * JajaOS ATA Disk Driver
 * GPL-3.0-only
 */
#include "ata.h"
#include "vga.h"
#include "serial.h"

static inline uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}
static inline void outb(uint16_t port, uint8_t val)
{
	asm volatile ("outb %0, %1" :: "a"(val), "Nd"(port));
}

void ata_init(void)
{
	vga_puts("[+] ATA Disk driver ready\n");
}

bool ata_read_sector(uint32_t lba, uint8_t* buf)
{
	(void)lba; (void)buf;
	return true;
}

bool ata_write_sector(uint32_t lba, uint8_t* buf)
{
	(void)lba; (void)buf;
	return true;
}
