/*
 * JajaOS DMG / HFS+ Parser
 * GPL-3.0-only
 */
#ifndef DMG_PARSER_H
#define DMG_PARSER_H

#include <stdint.h>
#include <stdbool.h>

bool dmg_parse(uint8_t* buffer, uint64_t size);

#endif
