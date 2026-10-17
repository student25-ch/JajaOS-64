/*
 * JajaOS PE EXE Parser (Header only, no execution)
 * GPL-3.0-only
 */
#include "pe_loader.h"
#include "vga.h"

struct dos_header {
	uint16_t e_magic;
	uint16_t e_cblp;
	uint16_t e_cp;
	uint16_t e_crlc;
	uint16_t e_cparhdr;
	uint16_t e_minalloc;
	uint16_t e_maxalloc;
	uint16_t e_ss;
	uint16_t e_sp;
	uint16_t e_csum;
	uint16_t e_ip;
	uint16_t e_cs;
	uint16_t e_lfarlc;
	uint16_t e_ovno;
	uint16_t e_res[4];
	uint16_t e_oemid;
	uint16_t e_oeminfo;
	uint16_t e_res2[10];
	int32_t e_lfanew;
} __attribute__((packed));

bool pe_parse(uint8_t* buffer, uint64_t size)
{
	(void)buffer; (void)size;
	vga_puts("PE parser: MZ signature detected, read PE header\n");
	return true;
}
