/*
 * JajaOS DEB Package Parser
 * GPL-3.0-only
 */
#ifndef DEB_PARSER_H
#define DEB_PARSER_H

#include <stdint.h>
#include <stdbool.h>

bool deb_parse(uint8_t* buffer, uint64_t size);

#endif
