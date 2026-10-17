/*
 * JajaOS PMM Implementation
 * GPL-3.0-only
 */
#include "pmm.h"
#include "kernel.h"

#define PMM_MAX_PAGES 1024
static uint64_t free_bitmap[PMM_MAX_PAGES/64];

void pmm_init(void)
{
    for(int i=0;i<PMM_MAX_PAGES/64;i++) free_bitmap[i]=0;
    vga_puts("[+] PMM Physical Memory Manager ready\n");
}

void* pmm_alloc_page(void)
{
    for(int i=0;i<PMM_MAX_PAGES;i++)
    {
        int idx = i/64;
        int bit = i%64;
        if( !(free_bitmap[idx] & (1ULL << bit)) )
        {
            free_bitmap[idx] |= (1ULL << bit);
            return (void*)(0x100000 + i*PAGE_SIZE);
        }
    }
    PANIC("JajaOS PMM out of physical memory");
    return NULL;
}

void pmm_free_page(void* addr)
{
    uint64_t pa = (uint64_t)addr;
    uint64_t page_idx = (pa - 0x100000)/PAGE_SIZE;
    int idx = page_idx/64;
    int bit = page_idx%64;
    free_bitmap[idx] &= ~(1ULL << bit);
}
