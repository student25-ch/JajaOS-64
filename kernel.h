/*
 * JajaOS Kernel Header
 * GPL-3.0-only
 */
#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define PANIC(msg) kernel_panic(msg, __FILE__, __LINE__)

void kmain(void);
void kernel_panic(const char* msg, const char* file, uint64_t line);

#endif
