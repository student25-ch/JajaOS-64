/*
 * JajaOS ELF64 Loader
 * GPL-3.0-only
 */
#ifndef ELF_LOADER_H
#define ELF_LOADER_H

#include <stdint.h>
#include <stdbool.h>

bool elf_load(uint8_t* buffer, uint64_t size);

#endif
