/*
 * JajaOS PCI Bus Scan
 * GPL-3.0-only
 */
#include "pci.h"
#include "vga.h"

static inline uint32_t pci_make_addr(uint8_t bus, uint8_t dev, uint8_t func, uint8_t offset)
{
	return (1U <<31) | ((uint32_t)bus <<16) | ((uint32_t)dev <<11) | ((uint32_t)func <<8) | (offset & 0xFC);
}

static inline uint32_t inl(uint16_t port)
{
	uint32_t ret;
	asm volatile("inl %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}
static inline void outl(uint16_t port, uint32_t val)
{
	asm volatile("outl %0, %1"::"a"(val), "Nd"(port));
}

uint32_t pci_read(uint8_t bus, uint8_t dev, uint8_t func, uint8_t offset)
{
	uint32_t addr = pci_make_addr(bus,dev,func,offset);
	outl(PCI_CONFIG_PORT, addr);
	return inl(PCI_DATA_PORT);
}

void pci_init(void)
{
	vga_puts("[+] Scanning PCI devices...\n");
	for(uint8_t bus = 0; bus < 1; bus++)
	{
		for(uint8_t dev = 0; dev <32; dev++)
		{
			uint32_t val = pci_read(bus, dev,0,0);
			uint16_t vid = val & 0xFFFF;
			uint16_t did = (val >>16) & 0xFFFF;
			if(vid != 0xFFFF)
			{
				vga_puts("PCI found dev, vendor:");
				vga_print_num(vid);
				vga_puts("\n");
			}
		}
	}
	vga_puts("[+] PCI scan complete\n");
}
