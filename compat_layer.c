/*
 * JajaOS Compatibility Layer Core
 * GPL-3.0-only
 */
#include "compat_layer.h"
#include "elf_loader.h"
#include "pe_loader.h"
#include "deb_parser.h"
#include "vga.h"

void compat_init(void)
{
    vga_puts("[+] JajaOS Compatibility Layer loaded\n");
    vga_puts("Supported formats: ELF64(run), PE/DEB/DMG(parse only)\n");
}

BinaryType compat_detect_binary(uint8_t* buffer, uint64_t size)
{
    if(size < 4) return BIN_TYPE_UNKNOWN;
    if(buffer[0]==0x7f && buffer[1]=='E' && buffer[2]=='L' && buffer[3]=='F')
    {
        return BIN_TYPE_ELF64;
    }
    if(buffer[0]=='M' && buffer[1]=='Z')
    {
        return BIN_TYPE_PE_EXE;
    }
    if(buffer[0]=='!' && buffer[1]=='<' && buffer[2]=='a')
    {
        return BIN_TYPE_DEB;
    }
    // DMG HFS+ signature
    if(buffer[0]=='H' && buffer[1]=='F' && buffer[2]=='S')
    {
    	return BIN_TYPE_DMG;
    }
    return BIN_TYPE_UNKNOWN;
}

bool compat_load_binary(uint8_t* buffer, uint64_t size)
{
    BinaryType type = compat_detect_binary(buffer,size);
    switch(type)
    {
        case BIN_TYPE_ELF64:
            vga_puts("[COMPAT] Loading ELF64 program...\n");
            return elf_load(buffer,size);
        case BIN_TYPE_PE_EXE:
            vga_puts("[COMPAT] Parse PE EXE header (no execute)\n");
            return pe_parse(buffer,size);
        case BIN_TYPE_DEB:
            vga_puts("[COMPAT] Parse DEB package\n");
            return deb_parse(buffer,size);
        case BIN_TYPE_DMG:
        	vga_puts("[COMPAT] Parse DMG HFS+ image\n");
        	return dmg_parse(buffer,size);
        default:
            vga_puts("[COMPAT] Unknown binary format!\n");
            return false;
    }
}
