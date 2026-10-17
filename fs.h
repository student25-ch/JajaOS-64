/*
 * JajaOS Simple Filesystem
 * GPL-3.0-only
 */
#ifndef FS_H
#define FS_H

#include <stdint.h>
#include <stdbool.h>

#define FS_MAX_FILES 64
#define FS_FILENAME_LEN 32

struct fs_file {
	char name[FS_FILENAME_LEN];
	uint32_t size;
	uint32_t start_sector;
	bool exists;
};

void fs_init(void);
bool fs_create(const char* name, uint32_t size);
bool fs_read(const char* name, uint8_t* out_buf, uint32_t offset, uint32_t len);
bool fs_write(const char* name, uint8_t* in_buf, uint32_t offset, uint32_t len);

#endif
