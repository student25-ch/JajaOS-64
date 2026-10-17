/*
 * JajaOS Serial Port COM1
 * GPL-3.0-only
 */
#include "serial.h"
#include "vga.h"
#include <stddef.h>

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

void serial_init(void)
{
	outb(COM1_PORT + 1, 0x00); // Disable interrupt
	outb(COM1_PORT + 3, 0x80); // DLAB
	outb(COM1_PORT + 0, 0x03); // Baud low
	outb(COM1_PORT + 1, 0x00); // Baud high
	outb(COM1_PORT + 3, 0x03); // 8 bits
	outb(COM1_PORT + 2, 0xC7); // FIFO
	outb(COM1_PORT + 4, 0x0B);
	vga_puts("[+] Serial COM1 debug port ready\n");
}

static int serial_transmit_empty(void)
{
	return inb(COM1_PORT +5) & 0x20;
}

void serial_putc(char c)
{
	while(serial_transmit_empty() == 0);
	outb(COM1_PORT, c);
}

void serial_puts(const char* s)
{
	while(*s)
	{
		serial_putc(*s++);
	}
}
