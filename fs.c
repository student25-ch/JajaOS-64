/*
 * JajaOS Filesystem Core
 * GPL-3.0-only
 */
#include "fs.h"
#include "vga.h"
#include "ata.h"

static struct fs_file fs_table[FS_MAX_FILES];

void fs_init(void)
{
	for(int i =0; i < FS_MAX_FILES; i++)
	{
		fs_table[i].exists = false;
	}
	vga_puts("[+] JajaOS Filesystem mounted\n");
}

bool fs_create(const char* name, uint32_t size)
{
	(void)name; (void)size;
	return true;
}

bool fs_read(const char* name, uint8_t* out_buf, uint32_t offset, uint32_t len)
{
	(void)name;(void)out_buf;(void)offset;(void)len;
	return true;
}

bool fs_write(const char* name, uint8_t* in_buf, uint32_t offset, uint32_t len)
{
	(void)name;(void)in_buf;(void)offset;(void)len;
	return true;
}
