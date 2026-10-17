/* GPLv3 JajaOS Kernel Entry */
#include "kernel.h"
#include "vga.h"
#include "pmm.h"
#include "vmm.h"
#include "compat_layer.h"
#include "shell.h"

// BSS段符号，由linker.ld提供
extern uint8_t __bss_start;
extern uint8_t __bss_end;

void kernel_panic(const char* msg, const char* file, uint64_t line)
{
    vga_puts("\n!!! JajaOS KERNEL PANIC !!!\n");
    vga_puts(msg);
    vga_puts("\nFile: ");
    vga_puts(file);
    vga_puts(" Line: ");
    vga_print_num(line);
    for(;;) asm("hlt");
}

void kmain(void)
{
    // 清零BSS
    uint64_t bss_size = (uint64_t)&__bss_end - (uint64_t)&__bss_start;
    for(uint64_t i = 0; i < bss_size; i++){
        (&__bss_start)[i] = 0;
    }

    vga_init();
    vga_puts("====================================\n");
    vga_puts("        JajaOS x86_64 Kernel        \n");
    vga_puts("           GPLv3 License            \n");
    vga_puts("====================================\n");

    gdt_init();
    idt_init();
    pmm_init();
    vmm_init();
    heap_init();
    compat_init();
    shell_start();

    for(;;) asm("hlt");
}
