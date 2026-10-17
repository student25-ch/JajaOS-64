/*
 * JajaOS PS/2 Keyboard Driver
 * GPL-3.0-only
 */
#include "keyboard.h"
#include "kernel.h"
#include "vga.h"

static uint8_t kbd_buffer[256];
static size_t buf_head, buf_tail;

void keyboard_init(void)
{
	buf_head = 0;
	buf_tail = 0;
	vga_puts("[+] PS/2 Keyboard Driver loaded\n");
}

bool keyboard_has_data(void)
{
	return !(buf_head == buf_tail);
}

char keyboard_read_char(void)
{
	if(buf_head == buf_tail) return 0;
	char c = kbd_buffer[buf_tail];
	buf_tail = (buf_tail + 1) % 256;
	return c;
}

static void kbd_buffer_push(char c)
{
	size_t next = (buf_head + 1) % 256;
	if(next != buf_tail)
	{
		kbd_buffer[buf_head] = c;
		buf_head = next;
	}
}
