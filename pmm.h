/*
 * JajaOS PMM Physical Memory Manager
 * GPL-3.0-only
 */
#ifndef PMM_H
#define PMM_H

#include <stdint.h>

#define PAGE_SIZE 4096

void pmm_init(void);
void* pmm_alloc_page(void);
void pmm_free_page(void* addr);

#endif
