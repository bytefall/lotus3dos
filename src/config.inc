CFG_SIZE = 2087

;
; 503D: Opens an reads to cfg_data complete LOTUS.CFG
;
cfg_open_and_read:
    mov     dx, cfg_file_name          ; "LOTUS.CFG"
    mov     ax, 3D00h
    ; DOS - 2+ - OPEN DISK FILE WITH HANDLE
    ; DS:DX -> ASCIZ filename
    ; AL = access mode
    ; 0 - read
    int     21h
    jc      ret_5072
    mov     bx, ax
    mov     ah, 3Fh
    mov     dx, tmp_file_buf
    mov     cx, CFG_SIZE
    push    bx
    ; DOS - 2+ - READ FROM FILE WITH HANDLE
    ; BX = file handle, CX = number of bytes to read
    ; DS:DX -> buffer
    int     21h
    pop     bx
    jc      ret_5072
    mov     ah, 3Eh
    ; DOS - 2+ - CLOSE A FILE WITH HANDLE
    ; BX = file handle
    int     21h
    jc      ret_5072
    mov     si, tmp_file_buf
    call    cfg_check_crc
    jnz     ret_5072
    push    ds
    pop     es
    mov     si, tmp_file_buf
    mov     di, cfg_data
    mov     cx, CFG_SIZE
    rep movsb

ret_5072:
    ret


;
; 5073: Check config's CRC
;
cfg_check_crc:
    mov     cx, CFG_SIZE - 1
    mov     al, 85

loc_5078:
    add     al, [si]
    inc     si
    loop    loc_5078
    xor     [si], al
    ret


;
; 5080:
;
sub_5080:
    mov     byte [byte_1F08], 0
    mov     si, cfg_data
    call    cfg_check_crc
    mov     ah, 3Ch
    mov     cx, 0
    mov     dx, cfg_file_name
    ; DOS - 2+ - CREATE A FILE WITH HANDLE (CREAT)
    ; CX = attributes for file
    ; DS:DX -> ASCIZ filename (may include drive and path)
    int     21h
    jb      ret_50AB
    mov     bx, ax
    mov     ah, 40h
    mov     dx, cfg_data
    mov     cx, 2087
    push    bx
    ; DOS - 2+ - WRITE TO FILE WITH HANDLE
    ; BX = file handle, CX = number of bytes to write, DS:DX -> buffer
    int     21h
    pop     bx
    jb      ret_50AB
    mov     ah, 3Eh
    ; DOS - 2+ - CLOSE A FILE WITH HANDLE
    ; BX = file handle
    int     21h
ret_50AB:
    ret


;
; 50AC:
;
sub_50AC:
    push    bx
    mov     bl, 40h
    call    sub_50B4
    pop     bx
    ret


;
; 50B4:
;
sub_50B4:
    cmp     byte [song_num], 0
    jne     ret_50F7

    ; when sound of engines
    push    bx
    push    cx
    push    dx
    push    si
    push    di
    push    bp
    push    es
    mov     dx, ax
    sub     al, 96
    cmp     al, 22
    ja      loc_50F0
    mov     cl, ah
    xchg    ax, bx
    dec     cl
    jns     loc_50E1
    mov     cl, [byte_1F09]
    inc     cx
    cmp     cl, 8
    jb      loc_50DD
    mov     cl, 5

loc_50DD:
    mov     [byte_1F09], cl

loc_50E1:
    mov     dh, cl
    push    dx
    call    sub_20DB
    pop     ax
    mov     bl, ah
    mov     bh, 0
    mov     [bx + byte_1F0A], al

loc_50F0:
    pop     es
    pop     bp
    pop     di
    pop     si
    pop     dx
    pop     cx
    pop     bx

ret_50F7:
    ret


;
; 50F8:
;
sub_50F8:
    cmp     byte [song_num], 0
    jne     ret_5120

    ; when sound of engines
    push    bx
    push    cx
    push    dx
    push    si
    push    di
    push    bp
    push    es
    mov     dx, bx
    mov     bl, ah
    mov     bh, 0
    cmp     al, [bx + byte_1F0A]
    jne     loc_5119
    mov     cl, ah
    mov     al, dl
    call    sub_207C

loc_5119:
    pop     es
    pop     bp
    pop     di
    pop     si
    pop     dx
    pop     cx
    pop     bx

ret_5120:
    ret


;
; 5121:
;
sub_5121:
    cmp     byte [song_num], 0
    jne     ret_5149

    ; when sound of engines
    push    bx
    push    cx
    push    dx
    push    si
    push    di
    push    bp
    push    es
    mov     dx, bx
    mov     bl, ah
    mov     bh, 0
    cmp     al, [bx + byte_1F0A]
    jnz     loc_5142
    mov     cl, ah
    mov     ax, dx
    call    sub_208C

loc_5142:
    pop     es
    pop     bp
    pop     di
    pop     si
    pop     dx
    pop     cx
    pop     bx

ret_5149:
    ret


;
; 514A:
;
sub_514A:
    push    ax
    push    bx
    mov     bl, 0
    call    sub_50F8
    pop     bx
    pop     ax
    ret
