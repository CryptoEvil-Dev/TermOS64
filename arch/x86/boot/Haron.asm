[BITS 16]
[ORG 0x7c00]

xor ax, ax
mov ds, ax
mov es, ax
mov ss, ax
mov sp, 0x7c00  ; Установим стек

mov [device_num], dl

; Проверка EBIOS
mov ah, 0x41
mov bx, 0x55aa
int 0x13
jc EBIOS_Error
cmp bx, 0xaa55
jne EBIOS_Error
jmp EBIOS_Succes


EBIOS_Error:
    mov si, EBIOS_ERR
    call write
    jmp $

EBIOS_Succes:
    mov si, EBIOS_OK
    call write
    mov ah, 0x0e
    mov al, 0x0a
    int 0x10
    mov al, 0x0d
    int 0x10



DAP_Settings:
; Настройка DAP для чтения
mov si, dap     ;   Загрузка адреса dap
mov ah, 0x42    ;   Функция Расширенного чтения
;mov dl, 0x80    ;   Номер диска 0x80 - первый.   По умолчанию, при загрузке с устройства, BIOS сам выставляет в регистр dl номер устройства.
mov [device_num], dl
int 0x13
jc rerr

; Успех


ReadELF:
    cmp dword [0x1000], 0x464c457f
    jne NO_ELF_ERR
    cmp byte [0x1004], 0x01
    jne NO_ELF_ERR


    mov ax, 0x0003
    int 0x10

cli
lgdt [gdt_descriptor]

mov eax, cr0
or eax, 1
mov cr0, eax

in al, 0x92
or al, 0x02
out 0x92, al    ; Открытие шлюза A20

jmp 0x08:0x1000


NO_ELF_ERR:
    mov si, ELF32_ERR
    call write
    jmp $


rerr:
    mov cx, [LBA_sectors]
    cmp cx, 0x00
    je ReadError
    dec cx
    mov [LBA_sectors], cx
    jmp DAP_Settings

ReadError:
    mov si, LBA_readerr
    call write
    jmp $



; Функция для вывода строки на экран
write: ; si - Адрес строки
    push ax
    push si
    mov ah, 0x0E
.wrieloop:
    cmp byte [si], 0x00
    je .writeend
    mov al, [si]
    int 0x10
    inc si
    jmp .wrieloop
.writeend:
    pop si
    pop ax
    ret

dap:
                db 0x10         ; Размер DAP 16 байт
                db 0x00         ; Зарезервировано
LBA_sectors:    dw 127          ; Количество секторов на чтение 127
                dw 0x1000       ; Смещение буфера
                dw 0x0000       ; Сегмент буфера
                dq 1            ; LBA=1 (Второй сектор): 1 сектор - Загрузочный, 2 сектор - нужно прочитать


gdt_start:
    ; Нулевой дескриптор
    dw 0                   ; Лимит (0)
    dw 0                   ; Базовый адрес (0)
    db 0                   ; Базовый адрес (0)
    db 0x00                ; Привилегии и тип (неиспользуемый)
    db 0x00                ; Флаги и лимит (0)
    db 0                   ; Базовый адрес (0)

    ; Сегмент кода (Ring 0)
    dw 0xFFFF              ; Лимит (64 КБ)
    dw 0x1000              ; Базовый адрес (0x0000)
    db 0x00                ; Базовый адрес (0x0000) (бит 16-23)
    db 0x9A                ; Привилегии и тип (исполняемый, доступный, уровень 0)
    db 0xCF                ; Флаги (размер 32 бита, лимит 4 КБ)
    db 0x00                ; Базовый адрес (0x0000) (бит 24-31)

    ; Сегмент данных (Ring 0)
    dw 0xFFFF              ; Лимит (64 КБ)
    dw 0x1000              ; Базовый адрес (0x0000)
    db 0x00                ; Базовый адрес (0x0000) (бит 16-23)
    db 0x92                ; Привилегии и тип (доступный, уровень 0)
    db 0xCF                ; Флаги (размер 32 бита, лимит 4 КБ)
    db 0x00                ; Базовый адрес (0x0000) (бит 24-31)

gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start




LBA_readerr: db "[panic] Read Error!",0
ELF32_ERR: db "[ELF32] Kernel Not found!",0
EBIOS_OK: db "[OK] LBA Supported!",0
EBIOS_ERR: db "[panic] LBA Not Supported!",0
device_num: db 0x00

times 510 - ($ - $$) db 0
dw 0xaa55
