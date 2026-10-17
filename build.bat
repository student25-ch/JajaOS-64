@echo off
chcp 65001>nul
setlocal enabledelayedexpansion
echo ==============================================
echo JajaOS Step2: Build & Run (x86_64 GPLv3)
echo Toolchain: F:\x86_64-elf-tools-windows\bin
echo ==============================================
:: 固定工具绝对路径
set "TOOL_BIN=F:\x86_64-elf-tools-windows\bin"
set NASM=%TOOL_BIN%\nasm.exe
set GCC=%TOOL_BIN%\x86_64-elf-gcc.exe
set LD=%TOOL_BIN%\x86_64-elf-ld.exe
set OBJCOPY=%TOOL_BIN%\x86_64-elf-objcopy.exe
set OBJDUMP=%TOOL_BIN%\x86_64-elf-objdump.exe

:: 全部目标文件
set OBJS=boot.o
set OBJS=%OBJS% kernel.o gdt.o idt.o pmm.o vmm.o heap.o
set OBJS=%OBJS% vga.o keyboard.o serial.o mouse.o pci.o ata.o
set OBJS=%OBJS% fs.o shell.o compat_layer.o elf_loader.o pe_loader.o deb_parser.o

echo.
echo [1/3] Assemble ASM
%NASM% -f elf64 boot.asm -o boot.o
if errorlevel 1 goto build_fail

echo.
echo [2/3] Compile C source (freestanding x86_64)
%GCC% -ffreestanding -mno-red-zone -m64 -g -c kernel.c -o kernel.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c gdt.c -o gdt.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c idt.c -o idt.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c pmm.c -o pmm.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c vmm.c -o vmm.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c heap.c -o heap.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c vga.c -o vga.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c keyboard.c -o keyboard.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c serial.c -o serial.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c mouse.c -o mouse.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c pci.c -o pci.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c ata.c -o ata.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c fs.c -o fs.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c shell.c -o shell.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c compat_layer.c -o compat_layer.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c elf_loader.c -o elf_loader.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c pe_loader.c -o pe_loader.o
%GCC% -ffreestanding -mno-red-zone -m64 -g -c deb_parser.c -o deb_parser.o
if errorlevel 1 goto build_fail

echo.
echo [3/3] Link kernel with linker script
%LD% -m elf_x86_64 -T linker.ld %OBJS% -o jajaos.elf
if errorlevel 1 goto build_fail

echo.
echo Generate raw binary image
%OBJCOPY% -O binary jajaos.elf jajaos.bin

echo.
echo ===== JAJAOS BUILD SUCCESS! =====
echo Start QEMU x86_64
qemu-system-x86_64 -drive format=raw,file=jajaos.bin
goto end

:build_fail
echo.
echo !!!!!!!!! JAJAOS BUILD FAILED !!!!!!!!!
pause
:end
pause
