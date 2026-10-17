/*
 * JajaOS Serial COM1 Port Debug
 * GPL-3.0-only
 */
#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

#define COM1_PORT 0x3F8

void serial_init(void);
void serial_putc(char c);
void serial_puts(const char* s);

#endif
