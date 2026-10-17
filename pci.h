/*
 * JajaOS PCI Bus Scanner
 * GPL-3.0-only
 */
#ifndef PCI_H
#define PCI_H

#include <stdint.h>

#define PCI_CONFIG_PORT 0xCF8
#define PCI_DATA_PORT 0xCFC

struct pci_device {
	uint16_t vendor_id;
	uint16_t dev_id;
	uint8_t bus;
	uint8_t dev;
	uint8_t func;
};

void pci_init(void);
uint32_t pci_read(uint8_t bus, uint8_t dev, uint8_t func, uint8_t offset);

#endif
