/*
 * JajaOS PE(EXE) Header Parser
 * GPL-3.0-only
 */
#ifndef PE_LOADER_H
#define PE_LOADER_H

#include <stdint.h>
#include <stdbool.h>

bool pe_parse(uint8_t* buffer, uint64_t size);

#endif
