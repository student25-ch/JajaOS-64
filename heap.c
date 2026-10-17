/*
 * JajaOS Kernel Heap Implementation (simple linked list heap)
 * GPL-3.0-only
 */
#include "heap.h"
#include "pmm.h"
#include "kernel.h"

typedef struct heap_block {
    size_t size;
    bool free;
    struct heap_block* next;
} heap_block_t;

static heap_block_t* heap_start;

void heap_init(void)
{
    heap_start = pmm_alloc_page();
    heap_start->size = PAGE_SIZE - sizeof(heap_block_t);
    heap_start->free = true;
    heap_start->next = NULL;
    vga_puts("[+] Kernel heap initialized\n");
}

void* kmalloc(size_t sz)
{
    heap_block_t* curr = heap_start;
    while(curr)
    {
        if(curr->free && curr->size >= sz)
        {
            curr->free = false;
            return (void*)((uint8_t*)curr + sizeof(heap_block_t));
        }
        curr = curr->next;
    }
    PANIC("JajaOS kmalloc: out of heap memory");
    return NULL;
}

void kfree(void* ptr)
{
    if(!ptr) return;
    heap_block_t* blk = (heap_block_t*)((uint8_t*)ptr - sizeof(heap_block_t));
    blk->free = true;
}
