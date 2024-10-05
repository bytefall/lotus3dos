;
; A9D3: Process game code number (i.e. difficulty)
;
sub_A9D3:
    mov     si, arr_1F3E
    lodsw
    cmp     ax, 13
    js      loc_A9DD
    dec     ax

loc_A9DD:
    mov     bx, ax
    and     ax, 1
    mov     [is_circular_track], ax
    shr     bx, 1
    mov     al, [arr_23E2 + bx]
    mov     [track_num], ax
    lodsw
    call    sub_D097
    mov     [word_2442], ax
    lodsw
    call    sub_D097
    mov     [word_2444], ax
    lodsw
    call    sub_D097
    mov     [word_2446], ax            ; when commented out - horizontal position of a car in a demo is messed up
    lodsw
    call    sub_D097
    mov     [word_2448], ax
    lodsw
    call    sub_D097
    mov     [word_244A], ax
    lodsw
    call    sub_D097
    mov     [word_244E], ax            ; for D00 = 0x64 = 100
    lodsw
    call    sub_D097
    mov     [word_2450], ax            ; for D00 = 0x50 = 80
    lodsw
    call    sub_D097
    mov     [word_2452], ax            ; for D00 = 0x14 = 20
    lodsw
    mov     [word_244C], ax            ; for D00 = 0x20 = 32
    mov     si, arr_1F3E
    mov     ax, 0
    mov     dx, 0
    mov     cx, 0
    mov     di, 7

loc_AA39:
    mov     cx, [si]
    add     cx, di

loc_AA3D:
    add     ax, cx
    adc     dx, 0
    mov     bp, dx
    shl     bp, 1
    rcl     ax, 1
    rcl     dx, 1
    shl     bp, 1
    rcl     ax, 1
    rcl     dx, 1
    shl     bp, 1
    rcl     ax, 1
    rcl     dx, 1
    loop    loc_AA3D
    add     di, 11
    add     si, 2
    cmp     si, arr_1F40 + 7 * 2
    jb      loc_AA39
    mov     [word_2454], ax
    mov     [word_2456], dx
    push    ds
    pop     es
    mov     di, rnd_248E
    mov     cx, 8

loc_AA73:
    stosw
    xchg    ax, dx
    loop    loc_AA73
    mov     word [word_23FC], tmp_file_buf
    mov     word [word_23FE], 0
    cmp     word [is_circular_track], 0
    jnz     loc_AA95
    add     word [word_23FC], 128
    add     word [word_23FE], 8

loc_AA95:
    mov     ax, [word_2456]
    and     ax, 1FFh
    add     ah, [word_2446]
    mov     [word_2446], ax
    mov     ax, 2048
    mov     bx, 512
    cmp     word [is_circular_track], 0
    jnz     loc_AAB5
    mov     ax, 992
    mov     bx, 256

loc_AAB5:
    sub     ax, bx
    mul     word [word_2446]
    mov     bp, 26111
    div     bp
    add     ax, bx
    mov     [word_635E], ax
    cwd
    mov     bp, 240
    div     bp
    inc     ax
    cmp     ax, 3
    jns     loc_AAD4
    mov     ax, 3

loc_AAD4:
    mov     [word_635A], ax
    mov     ax, [word_635E]
    cwd
    mov     bp, 128
    div     bp
    cmp     ax, 15
    js      loc_AAE8
    mov     ax, 15

loc_AAE8:
    sub     ax, [word_635A]
    inc     ax
    mul     word [word_2456]
    mov     cx, dx
    add     cx, [word_635A]
    mov     [num_of_tracks], cx
    mov     ax, [word_635E]
    cwd
    div     cx
    mov     [word_23F2], ax
    cmp     word [is_circular_track], 0
    jnz     ret_AB43
    mov     si, arr_2400
    mov     cx, 8
    mov     [si], cx
    add     si, 2
    mov     bp, [num_of_tracks]

loc_AB1A:
    add     cx, [word_23F2]
    call    smart_crc
    mov     dx, 96
    mul     dx
    sub     dx, 48
    add     dx, cx
    ; most likely here should be:
    ; mov [si], dx
    ; but with dx demo controls do not work properly
    mov     [si], cx
    add     si, 2
    dec     bp
    jnz     loc_AB1A
    mov     word [si], -1
    mov     ax, [word_635E]
    mov     [word_23F2], ax
    add     ax, 8
    mov     [si - 2], ax

ret_AB43:
    ret


;
; AB44:
;
smart_crc:
    push    bx
    push    dx
    mov     bx, rnd_248E
    mov     ax, [bx]
    mov     dx, [bx + 2]
    add     ax, 0A41Fh
    adc     dx, 736Fh
    mov     [bx], ax
    mov     [bx + 2], dx
    adc     ax, [bx + 4]
    adc     dx, [bx + 6]
    adc     ax, 3959h
    adc     dx, 1324h
    mov     [bx + 4], ax
    mov     [bx + 6], dx
    adc     ax, [bx + 8]
    adc     dx, [bx + 10]
    adc     ax, 1142h
    adc     dx, 8686h
    mov     [bx + 8], ax
    mov     [bx + 10], dx
    adc     ax, [bx + 12]
    adc     dx, [bx + 14]
    adc     ax, 2127h
    adc     dx, 44F0h
    mov     [bx + 12], ax
    mov     [bx + 14], dx
    mov     word [word_6354], dx
    pop     dx
    pop     bx
    ret


;
; AB9A:
;
sub_AB9A:
    push    bx
    push    dx
    mov     bx, rnd_3EEE
    mov     ax, [bx]
    mov     dx, [bx + 2]
    add     ax, 541Fh
    adc     dx, 7362h
    mov     [bx], ax
    mov     [bx + 2], dx
    adc     ax, [bx + 4]
    adc     dx, [bx + 6]
    adc     ax, 6475h
    adc     dx, 7FBEh
    mov     [bx + 4], ax
    mov     [bx + 6], dx
    adc     ax, [bx + 8]
    adc     dx, [bx + 10]
    adc     ax, 5984h
    adc     dx, 8326h
    mov     [bx + 8], ax
    mov     [bx + 10], dx
    adc     ax, [bx + 12]
    adc     dx, [bx + 14]
    adc     ax, 3747h
    adc     dx, 0F029h
    mov     [bx + 12], ax
    mov     [bx + 14], dx
    mov     word [word_6354], dx
    pop     dx
    pop     bx
    ret


;
; ABF0:
;
sub_ABF0:
    push    bx
    push    dx
    mov     bx, rnd_3EFE
    mov     ax, [bx]
    mov     dx, [bx + 2]
    add     ax, 541Fh
    adc     dx, 7362h
    mov     [bx], ax
    mov     [bx + 2], dx
    adc     ax, [bx + 4]
    adc     dx, [bx + 6]
    adc     ax, 6475h
    adc     dx, 7FBEh
    mov     [bx + 4], ax
    mov     [bx + 6], dx
    adc     ax, [bx + 8]
    adc     dx, [bx + 10]
    adc     ax, 5984h
    adc     dx, 8326h
    mov     [bx + 8], ax
    mov     [bx + 10], dx
    adc     ax, [bx + 12]
    adc     dx, [bx + 14]
    adc     ax, 3747h
    adc     dx, 0F029h
    mov     [bx + 12], ax
    mov     [bx + 14], dx
    mov     word [word_6354], dx
    pop     dx
    pop     bx
    ret
