/*
 * JajaOS VMM Implementation
 * GPL-3.0-only
 */
#include "vmm.h"
#include "pmm.h"
#include "kernel.h"

static pml4e_t* pml4;

void vmm_init(void)
{
    pml4 = pmm_alloc_page();
    asm volatile("mov %0, %%cr3" :: "r"(pml4));
    vga_puts("[+] VMM 4-level page table setup\n");
}

void* vmm_map_page(uint64_t va, uint64_t pa, uint64_t flags)
{
    uint64_t pml4_idx = (va >> 39) & 0x1FF;
    uint64_t pdpe_idx = (va >> 30) & 0x1FF;
    uint64_t pde_idx  = (va >> 21) & 0x1FF;
    uint64_t pte_idx  = (va >> 12) & 0x1FF;

    pdpe_t* pdpe;
    if(!(pml4[pml4_idx] & PTE_P))
    {
        pdpe = pmm_alloc_page();
        pml4[pml4_idx] = (uint64_t)pdpe | PTE_P | PTE_W;
    }else{
        pdpe = (pdpe_t*)(pml4[pml4_idx] & ~0xFFF);
    }

    pde_t* pd;
    if(!(pdpe[pdpe_idx] & PTE_P))
    {
        pd = pmm_alloc_page();
        pdpe[pdpe_idx] = (uint64_t)pd | PTE_P | PTE_W;
    }else{
        pd = (pde_t*)(pdpe[pdpe_idx] & ~0xFFF);
    }

    pte_t* pt;
    if(!(pd[pde_idx] & PTE_P))
    {
        pt = pmm_alloc_page();
        pd[pde_idx] = (uint64_t)pt | PTE_P | PTE_W;
    }else{
        pt = (pte_t*)(pd[pde_idx] & ~0xFFF);
    }
    pt[pte_idx] = pa | flags;
    return (void*)va;
}
