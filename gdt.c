/*
 * JajaOS GDT Implementation
 * GPL-3.0-only
 */
#include "gdt.h"
#include "kernel.h"

static struct gdt_entry gdt[5];
static struct gdt_ptr gp;

static void gdt_set_entry(int idx, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran)
{
    gdt[idx].base_low    = (base & 0xFFFF);
    gdt[idx].base_mid    = (base >> 16) & 0xFF;
    gdt[idx].base_high   = (base >> 24) & 0xFF;

    gdt[idx].limit_low   = (limit & 0xFFFF);
    gdt[idx].granularity = (limit >> 16) & 0x0F;
    gdt[idx].granularity |= gran & 0xF0;
    gdt[idx].access      = access;
}

void gdt_init(void)
{
    gp.limit = sizeof(gdt) - 1;
    gp.base = (uint64_t)&gdt;

    gdt_set_entry(0, 0, 0, 0, 0);
    gdt_set_entry(1, 0, 0xFFFF, 0x9A, 0xCF);
    gdt_set_entry(2, 0, 0xFFFF, 0x92, 0xCF);
    gdt_set_entry(3, 0, 0, 0x9A, 0x20);
    gdt_set_entry(4, 0, 0, 0x92, 0x00);

    asm volatile ("lgdt %0" : : "m"(gp));
    vga_puts("[+] GDT Initialized\n");
}
