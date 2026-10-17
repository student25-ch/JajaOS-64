/*
 * JajaOS IDT Implementation
 * GPL-3.0-only
 */
#include "idt.h"
#include "kernel.h"

static struct idt_entry idt[256];
static struct idt_ptr ip;

void idt_set_gate(uint8_t num, void* handler, uint16_t sel, uint8_t flags)
{
    uint64_t off = (uint64_t)handler;
    idt[num].offset_low  = off & 0xFFFF;
    idt[num].selector    = sel;
    idt[num].ist         = 0;
    idt[num].flags       = flags;
    idt[num].offset_mid  = (off >> 16) & 0xFFFF;
    idt[num].offset_high = (off >> 32);
    idt[num].reserved    = 0;
}

void idt_init(void)
{
    ip.limit = sizeof(idt)-1;
    ip.base  = (uint64_t)&idt;
    asm volatile ("lidt %0" : : "m"(ip));
    vga_puts("[+] IDT Initialized\n");
}
