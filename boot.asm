org 0x7c00
call readProgram
call setVESAMode
cli
mov sp, 0xfffc
mov ax, 0
call segnull
lgdt[gdt]
mov eax, cr0
or eax, 1
mov cr0, eax
mov eax, [buf+0x28]
mov dword[0x8000], eax
jmp MyCode : 0xc004
ret

readProgram:
    mov ax, 0x0210
    mov dx, 0x0080
    mov cx, 0x0010
    mov bx, 0x8004
    int 0x13
    mov ax, 0x0220
    mov dx, 0x0080
    mov cx, 0x0002
    mov bx, 0xc004
    int 0x13
ret

segnull:
    mov ss, ax
    mov ds, ax
    mov fs, ax
    mov es, ax
    mov gs, ax
    ret

setVESAMode:
    mov ax, 0x4f01
    mov cx, 0x118
    mov di, buf
    int 0x10
    mov ax, 0x4f02
    mov bx, 0x4118
    int 0x10
    ret

gd_table:
    Null_d:
        Dd 0
        Dd 0
    Code_d:
        Dw 0xffff
        Dw 0
        Db 0
        Db 0b10011010
         
        Db 0b11001111
        Db 0
    Data_d:
        Dw 0xffff
        Dw 0
        Db 0
        Db 0b10010010
        Db 0b11001111
    gd_table_end:
    gdt:
        Dw gd_table_end-gd_table
        Dd gd_table
MyCode equ Code_d-gd_table
buf dd 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
