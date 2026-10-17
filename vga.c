/*
 * JajaOS VGA Text + GUI
 * GPL-3.0-only
 */
#include "vga.h"
#include "kernel.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void vga_init(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) VGA_BUFFER;
	vga_clear();
}

void vga_set_color(enum vga_color fg, enum vga_color bg) {
	terminal_color = vga_entry_color(fg, bg);
}

void vga_clear(void) {
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	terminal_row = 0;
	terminal_column = 0;
}

static void vga_scroll(void)
{
	for(size_t y = 1; y < VGA_HEIGHT; y++)
	{
		for(size_t x = 0; x < VGA_WIDTH; x++)
		{
			size_t dst = (y-1)*VGA_WIDTH + x;
			size_t src = y*VGA_WIDTH + x;
			terminal_buffer[dst] = terminal_buffer[src];
		}
	}
	for(size_t x = 0; x < VGA_WIDTH; x++)
	{
		size_t idx = (VGA_HEIGHT-1)*VGA_WIDTH + x;
		terminal_buffer[idx] = vga_entry(' ', terminal_color);
	}
	terminal_row = VGA_HEIGHT - 1;
	terminal_column = 0;
}

void vga_putc(char c) {
	unsigned char uc = c;
	if(c == '\n')
	{
		terminal_column = 0;
		terminal_row++;
		if(terminal_row >= VGA_HEIGHT)
			vga_scroll();
		return;
	}
	const size_t index = terminal_row * VGA_WIDTH + terminal_column;
	terminal_buffer[index] = vga_entry(uc, terminal_color);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			vga_scroll();
	}
}

void vga_puts(const char* s) {
	while (*s)
		vga_putc(*s++);
}

void vga_print_num(uint64_t num)
{
	if(num == 0)
	{
		vga_putc('0');
		return;
	}
	char buf[32];
	int pos = 0;
	while(num > 0)
	{
		buf[pos++] = (num%10)+'0';
		num /= 10;
	}
	for(int i = pos-1; i >=0; i--)
		vga_putc(buf[i]);
}

void vga_gui_pixel(uint16_t x, uint16_t y, uint8_t color)
{
	// VGA 图形模式预留入口，GUI绘图
	(void)x;(void)y;(void)color;
}
