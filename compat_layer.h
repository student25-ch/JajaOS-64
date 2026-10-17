/*
 * JajaOS Binary Compatibility Layer
 * GPL-3.0-only
 */
#ifndef COMPAT_LAYER_H
#define COMPAT_LAYER_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    BIN_TYPE_UNKNOWN,
    BIN_TYPE_ELF64,
    BIN_TYPE_PE_EXE,
    BIN_TYPE_DEB,
    BIN_TYPE_DMG
} BinaryType;

BinaryType compat_detect_binary(uint8_t* buffer, uint64_t size);
bool compat_load_binary(uint8_t* buffer, uint64_t size);
void compat_init(void);

#endif
