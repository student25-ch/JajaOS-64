/*
 * JajaOS PS/2 Keyboard Driver
 * GPL-3.0-only
 */
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#define KBD_DATA_PORT 0x60
#define KBD_STATUS_PORT 0x64

void keyboard_init(void);
char keyboard_read_char(void);
bool keyboard_has_data(void);

#endif
