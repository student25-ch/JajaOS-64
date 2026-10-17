/*
 * JajaOS Shell Command Line
 * GPL-3.0-only
 */
#include "shell.h"
#include "vga.h"
#include "keyboard.h"
#include "compat_layer.h"
#include "fs.h"
#include "serial.h"

#define SHELL_BUF_SIZE 256
static char cmd_buf[SHELL_BUF_SIZE];
static int cmd_pos = 0;

static void shell_reset_buf(void)
{
	cmd_pos = 0;
	for(int i=0;i<SHELL_BUF_SIZE;i++) cmd_buf[i]=0;
}

static void shell_prompt(void)
{
	vga_puts("jajaos> ");
}

static void shell_run_cmd(char* cmd)
{
	if(!cmd || cmd[0]==0) return;
	if(strcmp(cmd,"help") == 0)
	{
		vga_puts("=== JajaOS Shell Help ===\n");
		vga_puts("help       - show help\n");
		vga_puts("reboot     - soft reboot\n");
		vga_puts("serial     - toggle serial\n");
		vga_puts("loadbin    - load binary via compat layer\n");
		vga_puts("ls         - list files\n");
		vga_puts("clear      - clear screen\n");
		return;
	}
	if(strcmp(cmd,"clear") == 0)
	{
		vga_clear();
		return;
	}
	if(strcmp(cmd,"ls") ==0)
	{
		vga_puts("JajaOS root directory:\n");
		vga_puts("kernel.elf\n");
		vga_puts("test.elf64\n");
		vga_puts("app.pe\n");
		return;
	}
	if(strcmp(cmd,"loadbin") ==0)
	{
		vga_puts("Compat layer binary loader ready\n");
		return;
	}
	vga_puts("Unknown command > ");
	vga_puts(cmd);
	vga_puts("\n");
}

void shell_start(void)
{
	vga_puts("\n[+] JajaOS Interactive Shell Started\n");
	shell_reset_buf();
	shell_prompt();
	for(;;)
	{
		if(keyboard_has_data())
		{
			char c = keyboard_read_char();
			if(c == '\r')
			{
				vga_puts("\n");
				shell_run_cmd(cmd_buf);
				shell_reset_buf();
				shell_prompt();
			}else if(c == '\b')
			{
				if(cmd_pos >0)
				{
					cmd_pos--;
					cmd_buf[cmd_pos] = 0;
					vga_putc('\b');
					vga_putc(' ');
					vga_putc('\b');
				}
			}else if(cmd_pos < SHELL_BUF_SIZE-1)
			{
				cmd_buf[cmd_pos++] = c;
				vga_putc(c);
			}
		}
		asm("hlt");
	}
}
