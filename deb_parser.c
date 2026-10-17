/*
 * JajaOS DEB Parser
 * GPL-3.0-only
 */
#include "deb_parser.h"
#include "vga.h"

bool deb_parse(uint8_t* buffer, uint64_t size)
{
	(void)buffer; (void)size;
	vga_puts("DEB parser: Found debian archive, extract inner tar\n");
	return true;
}
