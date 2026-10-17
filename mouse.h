/*
 * JajaOS PS/2 Mouse Driver
 * GPL-3.0-only
 */
#ifndef MOUSE_H
#define MOUSE_H

#include <stdint.h>

void mouse_init(void);
void mouse_get_pos(int16_t* x, int16_t* y);

#endif
