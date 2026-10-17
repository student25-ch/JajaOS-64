/*
 * JajaOS ATA PATA Disk Driver
 * GPL-3.0-only
 */
#ifndef ATA_H
#define ATA_H

#include <stdint.h>
#include <stdbool.h>

#define ATA_PRIMARY_IO 0x1F0
#define ATA_PRIMARY_CTRL 0x3F6

bool ata_read_sector(uint32_t lba, uint8_t* buf);
bool ata_write_sector(uint32_t lba, uint8_t* buf);
void ata_init(void);

#endif
