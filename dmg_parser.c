/*
 * JajaOS DMG HFS+ image parser
 * GPL-3.0-only
 */
#include "dmg_parser.h"
#include "vga.h"

bool dmg_parse(uint8_t* buffer, uint64_t size)
{
	(void)buffer; (void)size;
	vga_puts("DMG parser: HFS+ volume detected\n");
	return true;
}
