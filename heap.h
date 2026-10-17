/*
 * JajaOS Kernel Heap Allocator
 * GPL-3.0-only
 */
#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

void heap_init(void);
void* kmalloc(size_t sz);
void kfree(void* ptr);

#endif
