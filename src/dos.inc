;
; DA94:
;
sub_DA94:
    push    ds
    pop     es
    mov     di, arr_172C
    mov     cx, 128
    mov     al, 0
    rep stosb
    mov     byte [arr_172C + 25], 0FFh
    mov     byte [arr_172C + 1], 0FFh
    mov     si, arr_1701
    mov     bh, 0

loc_DAAF:
    mov     bl, [si]
    inc     si
    mov     byte [bx + arr_172C], 0FFh
    cmp     si, byte_1707 - 1
    jb      loc_DAAF

    mov     si, arr_1718
    mov     bh, 0

loc_DAC2:
    mov     bl, [si]
    inc     si
    mov     byte [bx + arr_172C], 0FFh
    cmp     si, byte_171E - 1
    jb      loc_DAC2
    ret


;
; DAD1:
;
sub_DAD1:
    mov     al, 0
    cmp     byte [byte_3E2C], al
    jz      ret_DB27

    ; - MS MOUSE - RETURN POSITION AND BUTTON STATUS
    ; Return: BX = button status, CX = column, DX = row
    mov     ax, 3
    int     33h
    and     bx, 3
    mov     [word_3E2E], bx
    mov     al, bl
    add     al, 0FFh
    sbb     al, al
    mov     [byte_3E2D], al
    mov     [word_3E30], cx
    mov     [word_3E32], dx
    mov     al, [byte_3DD0]
    and     al, 1
    mov     ah, [byte_3DD8]
    and     ah, 1
    shl     ah, 1
    or      ah, al
    shl     ah, 2
    mov     al, bl
    cmp     word [word_16F2], 0
    jnz     loc_DB18

    shr     ah, 2
    shl     al, 2

loc_DB18:
    or      al, ah
    cmp     cx, 200h
    cmc
    rcl     al, 1
    cmp     cx, 80h
    rcl     al, 1

ret_DB27:
    ret


;
; DB28:
;
sub_DB28:
    call    sub_DA94
    mov     ax, [word_3E16]
    mov     di, rnd_3EEE
    push    ds
    pop     es
    mov     cx, 8 * 2                  ; fill rnd_3EEE and rnd_3EFE
    rep stosw
    mov     bp, 0C00h

loc_DB3B:
    mov     ax, bp
    mov     ah, 0
    mov     cx, 8

loc_DB42:
    shl     al, 1
    adc     ah, 0
    loop    loc_DB42

    mov     [bp], ah
    inc     bp
    cmp     bp, 0D00h
    jb      loc_DB3B

    push    cs                         ; fill cs:0000 with a code that draws bitmap
    pop     es
    mov     di, 0
    mov     dh, 0

loc_DB5A:
    mov     dl, dh
    push    di
    mov     cx, 8

loc_DB60:
    dec     cx
    shl     dl, 1
    jb      loc_DB7C

    mov     al, 47h
    jcxz    loc_DB9D
    js      loc_DB9D
    mov     ax, 0C783h                 ; 83 C7 XX - add di, XX
    stosw
    mov     al, 1

loc_DB71:
    inc     al
    dec     cx
    shl     dl, 1
    jcxz    loc_DB9D
    jns     loc_DB71
    jmp     loc_DB9D

loc_DB7C:
    mov     al, 0A4h
    jns     loc_DB9D
    mov     al, 0A5h
    dec     cx
    shl     dl, 1
    cmp     word [cs:word_D379], 0
    jz      loc_DB9D
    cmp     dl, 0C0h
    jb      loc_DB9D
    sub     cx, 2
    shl     dl, 2
    mov     al, 66h
    stosb
    mov     al, 0A5h

loc_DB9D:
    stosb
    and     cx, cx
    jg      loc_DB60

    mov     si, raw_DBB4
    mov     cx, raw_DBC2 - raw_DBB4    ; = 14
    rep movs byte [es:di], [cs:si]     ; fill the rest of the code
    pop     di
    add     di, 32                     ; each code snippet is 32 bytes long
    inc     dh
    jnz     loc_DB5A
    ret

raw_DBB4:
    dec     cl
    jz      loc_DBC0

    mov     ah, 0
    lodsb
    shl     ax, 5
    jmp     ax

loc_DBC0:
    jmp     bx

raw_DBC2:
    mov     [err_str_ptr], dx
    ; DOS - 2+ - CREATE A FILE WITH HANDLE (CREAT)
    ; CX = attributes for file
    ; DS:DX -> ASCIZ filename (may include drive and path)
    mov     ax, 3C00h
    mov     cx, 0
    int     21h
    jb      loc_DBD3
    mov     bx, ax
    ret

loc_DBD3:
    mov     si, create_error
    jmp     loc_DC60


;
; DBD9: Opens a file.
;
file_open:
    mov     [err_str_ptr], dx
    ; DOS - 2+ - OPEN DISK FILE WITH HANDLE
    ; DS:DX -> ASCIZ filename
    ; AL = access mode
    ; 2 - read & write
    mov     ax, 3D02h
    int     21h
    jb      file_open_err
    mov     bx, ax
    ret

file_open_err:
    ; DOS - 2+ - CLOSE A FILE WITH HANDLE
    ; BX = file handle
    mov     ax, 3E00h
    int     21h
    mov     si, open_error
    jmp     loc_DC60


;
; DBF1: Reads a file.
;
; ax:dx - buffer,
; bx - file handler,
; cx - num of bytes to read
;
file_read:
    push    bx
    push    ds
    ; DOS - 2+ - READ FROM FILE WITH HANDLE
    ; BX = file handle, CX = number of bytes to read
    ; DS:DX -> buffer
    mov     ds, ax
    mov     ax, 3F00h
    int     21h
    pop     ds
    pop     bx
    mov     cx, ax
    jb      file_read_err
    ret

file_read_err:
    ; DOS - 2+ - CLOSE A FILE WITH HANDLE
    ; BX = file handle
    mov     ax, 3E00h
    int     21h
    mov     si, read_error
    jmp     loc_DC60


;
; DC0B: Is not known where it is called from
;
unk_DC0B:
    push    bx
    push    ds
    ; DOS - 2+ - WRITE TO FILE WITH HANDLE
    ; BX = file handle, CX = number of bytes to write, DS:DX -> buffer
    mov     ds, ax
    mov     ax, 4000h
    int     21h
    pop     ds
    pop     bx
    jb      loc_DC19
    ret

loc_DC19:
    ; DOS - 2+ - CLOSE A FILE WITH HANDLE
    ; BX = file handle
    mov     ax, 3E00h
    int     21h
    mov     si, write_error
    jmp     loc_DC60

    ; DOS - 2+ - CLOSE A FILE WITH HANDLE
    ; BX = file handle
    mov     ax, 3E00h
    int     21h
    jb      loc_DC2B
    ret

loc_DC2B:
    mov     si, close_error
    jmp     loc_DC60


;
; DC30: printf
;
; (si* string)
;
printf:
    lodsb
    cmp     al, 0
    jz      ret_DC4E

    cmp     al, '$'
    jz      loc_DC43

    push    si
    ; DOS - DISPLAY OUTPUT
    ; DL = character to send to standard output
    mov     dl, al
    mov     ah, 2
    int     21h
    pop     si
    jmp     printf

loc_DC43:
    push    si
    mov     si, [err_str_ptr]
    call    printf
    pop     si
    jmp     printf

ret_DC4E:
    ret


;
; DC4F:
;
sub_DC4F:
    push    ax
    mov     ax, [word_63BA]
    cmp     ax, [word_63BE]
    jae     loc_DC5B
    pop     ax
    ret

loc_DC5B:
    mov     si, memory_error
    jmp     loc_DC60

loc_DC60:
    mov     ds, [cs:word_5162]
    mov     [word_3EB9], si
    mov     byte [byte_3EBB], 1
    jmp     loc_DC70

loc_DC70:
    mov     ds, [cs:word_5162]
    cld
    call    sub_D396
    call    sub_209C
    call    sub_D3B6
    call    sub_5080
    call    sub_D3C7

    mov     si, [word_3EB9]
    call    printf

    ; DOS - 2+ - QUIT WITH EXIT CODE (EXIT)
    mov     al, [byte_3EBB]
    mov     ah, 4Ch
    int     21h
    ; DC93
