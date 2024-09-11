
word_A1CC:  dw 0                       ; A1CC
word_A1CE:  dw 0                       ; A1CE
word_A1D0:  dw 0                       ; A1D0
word_A1D2:  dw 0                       ; A1D2
word_A1D4:  dw 0                       ; A1D4


;
; A1D6: Draw small character
;
; in:
; (ax, bx) - x, y
; ch - unpacked texture index
; cl - ASCII char
;
draw_char_small:
    and     cl, 1111111b
    cmp     cl, 0
    jz      loc_A21C
    cmp     cl, '%'
    jz      loc_A220
    cmp     cl, '-'
    jz      loc_A214
    cmp     cl, '.'
    jz      loc_A218
    cmp     cl, 'z'
    ja      ret_A213
    cmp     cl, 'a'
    jb      loc_A1FC
    sub     cl, 'W'
    jmp     bmp_draw

loc_A1FC:
    cmp     cl, 'Z'
    ja      ret_A213
    cmp     cl, 'A'
    jb      loc_A20B
    sub     cl, '7'
    jmp     bmp_draw

loc_A20B:
    sub     cl, '0'
    cmp     cl, 10
    jb      bmp_draw

ret_A213:
    ret

loc_A214:
    mov     cl, 24h                    ; '$'
    jmp     bmp_draw

loc_A218:
    mov     cl, 25h                    ; '%'
    jmp     bmp_draw

loc_A21C:
    mov     cl, 26h                    ; '&'
    jmp     bmp_draw

loc_A220:
    mov     cl, 27h                    ; '''
    jmp     bmp_draw


;
; A224: Draw a bitmap
;
; in:
; (ax, bx) - x, y
; ch - unpacked data index
; cl - char
;
bmp_draw:
    pusha
    push    ds
    push    es
    mov     di, 1360
    add     di, ax
    mov     ax, 336
    mul     bx
    add     di, ax
    mov     es, [word_63BC]            ; video memory for A000
    mov     bl, ch
    mov     bh, 0
    shl     bx, 1
    mov     ax, [chr_bmp_ptr + bx]
    mov     ds, ax                     ; ds = unpacked data after sub_c505
    mov     bl, cl
    shl     bx, 3
    add     ax, [bx]                   ; let op_pos = ax;
    mov     cx, [bx + 2]
    mov     dx, [bx + 4]               ; let height = dx;
    mov     ds, ax
    mov     si, 0
    add     cx, 7
    shr     cx, 3                      ; let repeat = cx;
    mov     [cs:word_A1CC], cx
    mov     bx, loc_A265
    jmp     loc_A26D

loc_A265:
    pop     di
    add     di, 336
    dec     dx
    jz      loc_A27B

loc_A26D:
    push    di
    mov     cl, [cs:word_A1CC]
    mov     ah, 0
    lodsb
    shl     ax, 5
    jmp     ax

loc_A27B:
    pop     es
    pop     ds
    popa
    ret


loc_A27F:
    cmp     word [word_2114], 0FAh
    jnz     loc_A28D
    mov     word [word_6348], 0Ah

loc_A28D:
    mov     si, arr34_2378
    cmp     word [word_63A0], 0
    jnz     loc_A2A1
    mov     si, arr34_2356
    cmp     word [word_639E], 0
    jz      loc_A2B5

loc_A2A1:
    add     si, word [word_636E]
    mov     ah, 0
    mov     al, [si]
    mov     [word_6348], ax
    mov     al, [si + 17]
    mov     [word_634A], ax
    mov     [word_634C], ax

loc_A2B5:
    cmp     word [word_2114], 0F0h
    jns     loc_A2C0
    jmp     loc_A43E

loc_A2C0:
    mov     word [word_2206], 0
    cmp     word [word_2114], 0FAh
    je      loc_A2D6
    cmp     word [word_2114], 0FCh
    jne     loc_A2DE

loc_A2D6:
    mov     bp, [word_6348]
    mov     [word_2206], bp

loc_A2DE:
    add     bx, 0A0h
    mov     [word_239A], bx
    mov     [word_239C], cx
    mov     ax, [word_2216]
    shr     ax, 4
    mov     [word_239E], ax
    shr     word [word_239E], 1
    shl     ax, 1
    mov     si, arr_6BC2
    add     si, ax
    mov     ax, [si]
    mov     [word_2216], ax
    cmp     word [word_23A0], 0
    jz      loc_A32B
    mov     word [word_23A0], 0
    mov     word [word_6362], 140h
    mov     cx, 0
    mov     ax, [word_2112]
    mov     ah, 0
    mov     bp, [word_239C]
    mov     [word_6366], bp
    mov     dx, ax
    jmp     sub_A51E

loc_A32B:
    mov     bp, [word_239A]
    sub     bp, [word_2216]
    mov     [word_6362], bp
    mov     bp, [word_239C]
    mov     [word_6366], bp
    mov     ax, [word_239E]
    mov     dx, bp
    sub     dx, ax
    cmp     word [word_2114], 0FCh
    jnz     loc_A3AD
    cmp     word [word_1FD4], 0
    js      loc_A3AD
    cmp     dx, [word_1FD4]
    jle     loc_A3AD
    push    ax
    push    bx
    push    cx
    push    dx
    push    word [word_6362]
    push    word [word_6366]
    push    word [word_636A]
    push    word [word_636E]
    push    word [word_2206]
    mov     [word_6366], dx
    mov     dx, [word_1FD4]
    sub     dx, 2
    jns     loc_A383
    mov     dx, 0

loc_A383:
    mov     cx, 0
    mov     word [word_6362], 140h
    mov     word [word_2206], 0
    call    sub_A51E
    pop     word [word_2206]
    pop     word [word_636E]
    pop     word [word_636A]
    pop     word [word_6366]
    pop     word [word_6362]
    pop     dx
    pop     cx
    pop     bx
    pop     ax

loc_A3AD:
    cmp     word [word_2114], 0FCh
    jns     loc_A3C6
    mov     cx, [word_2216]
    sar     cx, 1
    sub     cx, [word_6362]
    neg     cx
    call    sub_A51E
    jmp     loc_A3D8

loc_A3C6:
    mov     bp, [word_239A]
    sub     bp, [word_2216]
    mov     [word_6362], bp
    mov     cx, 0
    call    sub_A51E

loc_A3D8:
    mov     cx, [word_239A]
    add     cx, [word_2216]
    mov     bp, [word_239C]
    mov     [word_6366], bp
    mov     ax, [word_239E]
    mov     dx, bp
    sub     dx, ax
    cmp     word [word_2114], 0FCh
    jns     loc_A408
    mov     bp, [word_2216]
    sar     bp, 1
    add     bp, cx
    mov     [word_6362], bp
    call    sub_A51E
    jmp     loc_A411

loc_A408:
    mov     word [word_6362], 140h
    call    sub_A51E

loc_A411:
    mov     cx, 0
    mov     word [word_6362], 140h
    mov     bp, [word_239C]

loc_A41E:
    mov     ax, [word_239E]
    sub     bp, ax
    mov     [word_6366], bp
    mov     dx, bp
    shr     ax, 1
    sub     dx, ax
    cmp     word [word_2114], 0FDh
    jne     loc_A43B
    mov     dx, word [word_2112]
    mov     dh, 0

loc_A43B:
    jmp     sub_A51E

loc_A43E:
    add     bx, 0A0h
    mov     [word_239A], bx
    mov     [word_239C], cx
    mov     ax, [word_2216]
    shr     ax, 4
    mov     [word_239E], ax
    shr     word [word_239E], 1
    shl     ax, 1
    mov     si, arr_6BC2
    add     si, ax
    mov     ax, [si]
    mov     [word_2216], ax
    mov     bp, [word_6348]
    mov     [word_2206], bp
    mov     bp, [word_239A]
    sub     bp, [word_2216]
    mov     [word_6362], bp
    mov     bp, [word_239C]
    mov     [word_6366], bp
    mov     ax, [word_239E]
    mov     dx, bp
    sub     dx, ax
    mov     cx, [word_6362]
    shr     ax, 3
    sub     cx, ax
    call    sub_A51E
    mov     bp, [word_6348]
    mov     [word_2206], bp
    mov     cx, [word_239A]
    add     cx, [word_2216]
    mov     bp, [word_239C]
    mov     [word_6366], bp
    mov     ax, [word_239E]
    mov     dx, bp
    sub     dx, ax
    mov     [word_6362], cx
    shr     ax, 3
    add     [word_6362], ax
    call    sub_A51E
    mov     bp, [word_634A]
    cmp     word [word_2114], 7Ah
    je      loc_A4CE
    mov     bp, [word_634C]

loc_A4CE:
    mov     [word_2206], bp
    mov     ax, [word_239E]
    shr     ax, 3
    mov     cx, [word_239A]
    sub     cx, [word_2216]
    sub     cx, ax
    mov     bp, [word_239A]
    add     bp, [word_2216]
    add     bp, ax
    mov     [word_6362], bp
    mov     bp, [word_239C]
    mov     ax, [word_239E]
    sub     bp, ax
    mov     [word_6366], bp
    mov     dx, bp
    shr     ax, 1
    sub     dx, ax
    mov     ax, dx
    add     ax, [word_6366]
    shr     ax, 1
    mov     [word_2350], ax
    cmp     word [word_2114], 0FDh
    jnz     loc_A51C
    mov     dx, [word_1FF0]
    mov     dh, 0

loc_A51C:
    jmp     sub_A51E


;
; A51E:
;
sub_A51E:
    and     cx, cx
    jge     loc_A525
    mov     cx, 0

loc_A525:
    cmp     word [word_6362], 140h
    jl      loc_A533
    mov     word [word_6362], 140h

loc_A533:
    and     dx, dx
    jge     loc_A53A
    mov     dx, 0

loc_A53A:
    mov     bp, [word_2218]
    cmp     [word_6366], bp
    jle     loc_A548
    mov     [word_6366], bp

loc_A548:
    sub     [word_6362], cx
    jle     ret_A58A
    sub     [word_6366], dx
    jl      ret_A58A
    inc     word [word_6366]
    mov     ax, 336
    mul     dx
    add     ax, cx
    add     ax, 550h
    mov     di, ax
    and     di, 0Fh
    shr     ax, 4
    add     ax, [word_63BC]
    mov     es, ax
    mov     ax, [word_2206]
    add     al, 0F0h
    mov     bp, 336
    sub     bp, [word_6362]

loc_A57C:
    mov     cx, [word_6362]
    rep stosb
    add     di, bp
    dec     word [word_6366]
    jnz     loc_A57C

ret_A58A:
    ret


;
; A58B:
;
sub_A58B:
    test    word [word_2064], 1Fh
    jne     ret_A5CD
    push    ax
    push    bx
    push    cx
    push    si
    push    di
    push    ds
    mov     bx, [word_2064]
    shl     bx, 3
    mov     ax, 336
    mul     word [bx - 3A94h]
    add     ax, 550h
    adc     dx, 0
    mov     bp, ax
    mov     di, dx
    shr     bx, 7
    cmp     word [word_63AA], 0
    jz      loc_A5BE
    add     bx, 8

loc_A5BE:
    call    word [arr_23A2 + bx]
    pop     ds
    pop     di
    pop     si
    pop     cx
    pop     bx
    pop     ax
    sub     word [word_2064], 20h

ret_A5CD:
    ret


;
; A5CE:
;
sub_A5CE:
    mul     word [word_3EE6]
    shl     ax, 1
    rcl     dx, 1
    shl     ax, 1
    rcl     dx, 1
    shl     ax, 1
    rcl     dx, 1
    shl     ax, 1
    rcl     dx, 1
    shl     ax, 1
    rcl     dx, 1
    shl     ax, 1
    rcl     dx, 1
    shl     ax, 1
    rcl     dx, 1
    shl     ax, 1
    rcl     dx, 1
    ret


;
; A5F3:
;
sub_A5F3:
    mov     ax, 512
    call    sub_A5CE
    shr     dx, 1
    jae     loc_A604
    add     bp, 336
    adc     di, 0

loc_A604:
    mov     si, dx
    shl     si, 2
    mov     es, [word_2C76]
    mov     ax, bp
    and     bp, 7FFFh
    shl     ax, 1
    rcl     di, 1
    shl     di, 11
    mov     dx, [word_63BC]
    add     di, dx
    mov     ds, di
    mov     ax, 505h

loc_A625:
    and     si, 1FCh
    mov     di, bp
    add     di, word [es:si]
    call    word [es:si + 2]
    add     si, 4
    sub     bp, 336 * 2
    jae     loc_A625
    add     bp, 8000h
    mov     bx, ds
    sub     bx, 800h
    mov     ds, bx
    cmp     bx, dx
    jae     loc_A625
    ret


;
; A64C:
;
sub_A64C:
    mov     ax, 384
    call    sub_A5CE
    mov     si, dx
    shl     si, 2
    mov     es, [word_2C78]
    mov     ax, bp
    and     bp, 7FFFh
    shl     ax, 1
    rcl     di, 1
    shl     di, 11
    mov     dx, [word_63BC]
    add     di, dx
    mov     ds, di
    mov     ax, 505h

loc_A673:
    and     si, 3FCh
    mov     di, bp
    add     di, [es:si]
    call    word [es:si + 2]
    add     si, 4
    sub     bp, 336
    jae     loc_A673
    add     bp, 8000h
    mov     bx, ds
    sub     bx, 800h
    mov     ds, bx
    cmp     bx, dx
    jae     loc_A673
    ret


;
; A69A:
;
sub_A69A:
    mov     ax, 256
    call    sub_A5CE
    mov     si, dx
    shl     si, 3
    mov     es, [word_2C7A]
    mov     ax, bp
    and     bp, 7FFFh
    shl     ax, 1
    rcl     di, 1
    shl     di, 11
    mov     dx, [word_63BC]
    add     di, dx
    mov     ds, di
    mov     ax, 505h

loc_A6C1:
    and     si, 7F8h
    mov     di, bp
    add     di, [es:si]
    call    word [es:si + 2]
    mov     di, bp
    add     di, [es:si + 4]
    call    word [es:si + 6]
    add     si, 8
    sub     bp, 336
    jae     loc_A6C1
    add     bp, 8000h
    mov     bx, ds
    sub     bx, 800h
    mov     ds, bx
    cmp     bx, dx
    jae     loc_A6C1
    ret


;
; A6F2:
;
sub_A6F2:
    mov     ax, 128
    call    sub_A5CE
    mov     si, dx
    shl     si, 3
    mov     ax, bp
    and     bp, 7FFFh
    shl     ax, 1
    rcl     di, 1
    shl     di, 11
    mov     dx, [word_63BC]
    add     di, dx
    mov     es, di
    mov     ds, [word_2C7C]
    mov     ax, 505h

loc_A719:
    and     si, 7F8h
    mov     di, bp
    add     di, [si]
    stosb
    mov     di, bp
    add     di, [si + 2]
    stosb
    mov     di, bp
    add     di, [si + 4]
    stosb
    mov     di, bp
    add     di, [si + 6]
    stosb
    add     si, 8
    sub     bp, 336
    jae     loc_A719
    add     bp, 8000h
    mov     bx, es
    sub     bx, 800h
    mov     es, bx
    cmp     bx, dx
    jae     loc_A719
    ret


;
; A74E:
;
sub_A74E:
    mov     ax, 600h
    call    sub_A5CE
    shr     dx, 1
    jae     loc_A75F
    add     bp, 336
    adc     di, 0

loc_A75F:
    mov     si, dx
    shl     si, 1
    mov     es, [word_2C76]
    mov     ax, bp
    and     bp, 7FFFh
    shl     ax, 1
    rcl     di, 1
    shl     di, 11
    mov     dx, [word_63BC]
    add     di, dx
    mov     ds, di
    mov     ax, 1B0Fh

loc_A77F:
    and     si, 0FEh
    mov     di, bp
    add     di, [es:si]
    mov     [di], al
    mov     [di + 336 * 1], al
    mov     [di + 336 * 2], al
    mov     [di + 336 * 3], ah
    add     si, 2
    sub     bp, 336 * 2
    jae     loc_A77F
    add     bp, 8000h
    mov     bx, ds
    sub     bx, 800h
    mov     ds, bx
    cmp     bx, dx
    jae     loc_A77F
    ret


;
; A7B0:
;
sub_A7B0:
    mov     ax, 500h
    call    sub_A5CE
    mov     si, dx
    shl     si, 1
    mov     es, [word_2C78]
    mov     ax, bp
    and     bp, 7FFFh
    shl     ax, 1
    rcl     di, 1
    shl     di, 11
    mov     dx, [word_63BC]
    add     di, dx
    mov     ds, di
    mov     ax, 1B0Fh

loc_A7D6:
    and     si, 1FEh
    mov     di, bp
    add     di, [es:si]
    mov     [di], al
    mov     [di + 336], al
    mov     [di + 336 * 2], ah
    add     si, 2
    sub     bp, 336
    jae     loc_A7D6
    add     bp, 8000h
    mov     bx, ds
    sub     bx, 800h
    mov     ds, bx
    cmp     bx, dx
    jae     loc_A7D6
    ret


;
; A803:
;
sub_A803:
    mov     ax, 400h
    call    sub_A5CE
    mov     si, dx
    shl     si, 2
    mov     es, [word_2C7A]
    mov     ax, bp
    and     bp, 7FFFh
    shl     ax, 1
    rcl     di, 1
    shl     di, 11
    mov     dx, [word_63BC]
    add     di, dx
    mov     ds, di
    mov     ax, 1B0Fh

loc_A82A:
    and     si, 1FCh
    mov     di, bp
    add     di, [es:si]
    mov     [di], al
    mov     [di + 336], ah
    mov     di, bp
    add     di, [es:si + 2]
    mov     [di], al
    mov     [di + 336], ah
    add     si, 4
    sub     bp, 336
    jae     loc_A82A
    add     bp, 8000h
    mov     bx, ds
    sub     bx, 800h
    mov     ds, bx
    cmp     bx, dx
    jae     loc_A82A
    ret


sub_A85F:
    ret


sub_A860:
    mov     [di], ax
    mov     [di + 336], ax
    ret


sub_A867:
    mov     [di], ax
    mov     [di + 336], al
    ret


sub_A86E:
    mov     [di], ax
    mov     [di + 336 + 1], al
    ret


sub_A875:
    mov     [di], al
    mov     [di + 336], ax
    ret


sub_A87C:
    mov     [di + 1], al
    mov     [di + 336], ax
    ret


sub_A884:
    mov     [di], ax
    mov     [di + 2], al
    mov     [di + 336], ax
    mov     [di + 336 + 2], al
    mov     [di + 336 * 2 + 1], al
    ret


sub_A896:
    mov     [di + 1], al
    mov     [di + 336], ax
    mov     [di + 336 + 2], al
    mov     [di + 336 * 2], ax
    mov     [di + 336 * 2 + 2], al
    ret


sub_A8AA:
    mov     [di], ax
    mov     [di + 336], ax
    mov     [di + 336 + 2], al
    mov     [di + 336 * 2 + 1], ax
    ret


sub_A8B9:
    mov     [di + 1], ax
    mov     [di + 336], ax
    mov     [di + 336 + 2], al
    mov     [di + 336 * 2], ax
    ret


sub_A8C9:
    mov     [di], ax
    mov     [di + 2], al
    mov     [di + 336], ax
    mov     [di + 336 + 2], al
    mov     [di + 336 * 2], ax
    ret


sub_A8DB:
    mov     [di], ax
    mov     [di + 2], al
    mov     [di + 336], ax
    mov     [di + 336 + 2], al
    mov     [di + 336 * 2 + 1], ax
    ret


sub_A8ED:
    mov     [di], ax
    mov     [di + 336], ax
    mov     [di + 336 + 2], al
    mov     [di + 336 * 2], ax
    mov     [di + 336 * 2 + 2], al
    ret


sub_A900:
    mov     [di + 1], ax
    mov     [di + 336], ax
    mov     [di + 336 + 2], al
    mov     [di + 336 * 2], ax
    mov     [di + 336 * 2 + 2], al
    ret


sub_A914:
    mov     [di + 1], ax
    mov     [di + 336], ax
    mov     [di + 336 + 2], ax
    mov     [di + 336 * 2], ax
    mov     [di + 336 * 2 + 2], ax
    mov     [di + 336 * 3 + 1], ax
    ret


sub_A92C:
    mov     [di + 2], al
    mov     [di + 336 + 1], al
    mov     [di + 336 + 2], ax
    mov     [di + 336 * 2], ax
    mov     [di + 336 * 2 + 2], ax
    mov     [di + 336 * 3 + 1], ax
    ret


sub_A944:
    mov     [di + 1], al
    mov     [di + 336], ax
    mov     [di + 336 + 2], al
    mov     [di + 336 * 2], ax
    mov     [di + 336 * 2 + 2], ax
    mov     [di + 336 * 3 + 1], ax
    ret


sub_A95C:
    mov     [di + 1], ax
    mov     [di + 336], ax
    mov     [di + 336 + 2], ax
    mov     [di + 336 * 2 + 1], al
    mov     [di + 336 * 2 + 2], ax
    mov     [di + 336 * 3 + 2], al
    ret


sub_A974:
    mov     [di + 1], ax
    mov     [di + 336], ax
    mov     [di + 336 + 2], ax
    mov     [di + 336 * 2], ax
    mov     [di + 336 * 2 + 1], al
    mov     [di + 336 * 3 + 1], al
    ret


sub_A98C:
    mov     [di + 1], ax
    mov     [di + 336], ax
    mov     [di + 336 + 2], ax
    mov     [di + 336 * 2], ax
    mov     [di + 336 * 2 + 2], ax
    mov     [di + 336 * 3 + 1], ax
    ret


sub_A9A4:
    mov     [di], ax
    mov     [di + 336], ax
    mov     [di + 336 + 2], al
    mov     [di + 336 * 2 + 1], al
    mov     [di + 336 * 2 + 2], ax
    mov     [di + 336 * 3 + 2], ax
    ret


sub_A9BB:
    mov     [di + 2], ax
    mov     [di + 336 + 1], al
    mov     [di + 336 + 2], ax
    mov     [di + 336 * 2], ax
    mov     [di + 336 * 2 + 2], al
    mov     [di + 336 * 3], ax
    ret
