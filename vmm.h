/*
 * JajaOS VMM Virtual Memory Manager (x86_64 4-level page table)
 * GPL-3.0-only
 */
#ifndef VMM_H
#define VMM_H

#include <stdint.h>

#define PTE_P (1<<0)
#define PTE_W (1<<1)
#define PTE_U (1<<2)

typedef uint64_t pte_t;
typedef uint64_t pde_t;
typedef uint64_t pdpe_t;
typedef uint64_t pml4e_t;

void vmm_init(void);
void* vmm_map_page(uint64_t va, uint64_t pa, uint64_t flags);

#endif
