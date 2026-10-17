/*
 * JajaOS PS/2 Mouse
 * GPL-3.0-only
 */
#include "mouse.h"
#include "vga.h"

static int16_t mouse_x = 0;
static int16_t mouse_y = 0;

void mouse_init(void)
{
	mouse_x = 40;
	mouse_y = 12;
	vga_puts("[+] PS/2 Mouse driver initialized\n");
}

void mouse_get_pos(int16_t* x, int16_t* y)
{
	*x = mouse_x;
	*y = mouse_y;
}
