; JajaOS Bootloader, GPLv3
[BITS 16]
[ORG 0x7C00]

%define KERNEL_OFFSET 0x1000
%define KERNEL_SEG 0x100

_start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    ; A20 Gate enable
    in al, 0x92
    or al, 2
    out 0x92, al

    ; 读取内核到 0x1000:0x0000
    mov bx, KERNEL_OFFSET
    mov ah, 0x02
    mov al, 32    ; 读取32扇区，足够放内核，按需调大
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0x80
    int 0x13
    jc disk_error

    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE32:init_pm

disk_error:
    mov si, err_msg
print_loop:
    lodsb
    or al,al
    jmp $
    mov ah,0x0E
    int 0x10
    jmp print_loop
err_msg db "JajaOS: Disk read fail!",0

[BITS 32]
init_pm:
    mov ax, DATA32
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax

    ; 构建四级页表，放在0x100000
    mov edi, 0x100000
    mov cr3, edi
    xor eax,eax
    mov ecx, 4096
    rep stosd
    mov edi, cr3

    ; PML4
    mov dword [edi], 0x101003
    add edi,0x1000
    ; PDP
    mov dword [edi], 0x102003
    add edi,0x1000
    ; PD
    mov dword [edi], 0x103003
    add edi,0x1000
    ; PT 映射0~2MB
    mov ebx,0x00000003
    mov ecx,512
pt_loop:
    mov [edi],ebx
    add ebx,0x1000
    add edi,8
    dec ecx
    jnz pt_loop

    mov eax,cr4
    or eax,1<<5
    mov cr4,eax

    mov ecx,0xC0000080
    rdmsr
    or eax,1<<8
    wrmsr

    mov eax,cr0
    or eax,1<<31
    mov cr0,eax

    jmp CODE64:long_mode_entry

[BITS 64]
long_mode_entry:
    mov rsp, 0xFFFF800000009000
    mov rbp, rsp
    extern kmain
    call kmain
.hang:
    hlt
    jmp .hang

; GDT
gdt_start:
gdt_null: dq 0
gdt_code32:
    dw 0xFFFF
    dw 0
    db 0
    db 0b10011010
    db 0b11001111
    db 0
gdt_data32:
    dw 0xFFFF
    dw 0
    db 0
    db 0b10010010
    db 0b11001111
    db 0
gdt_code64:
    dw 0
    dw 0
    db 0
    db 0b10011010
    db 0b00100000
    db 0
gdt_data64:
    dw 0
    dw 0
    db 0
    db 0b10010010
    db 0b00000000
    db 0
gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dq gdt_start

CODE32 equ gdt_code32 - gdt_start
DATA32 equ gdt_data32 - gdt_start
CODE64 equ gdt_code64 - gdt_start
DATA64 equ gdt_data64 - gdt_start

times 510 - ($-$$) db 0
dw 0xAA55
