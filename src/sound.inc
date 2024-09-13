;
; 2000:
;
sub_2000:
    pusha
    shl     ax, 1
    nop
    and     ax, 3FFh
    mov     bx, ax
    shr     bx, 7
    or      al, 80h
    mov     bp, ax
    mov     al, [word_2C]
    cmp     al, 40h
    jb      loc_2019
    mov     al, 3Fh

loc_2019:
    shl     al, 2
    mov     dl, al
    call    sub_202F
    neg     bp
    dec     bx
    call    sub_202F
    add     bx, 2
    call    sub_202F
    popa
    ret


;
; 202F:
;
sub_202F:
    cmp     bx, 8
    jae     ret_202F
    mov     ax, bp
    mul     dl
    mov     al, ah
    add     al, [bx]
    nop
    nop
    jae     loc_2042
    mov     al, 0FFh

loc_2042:
    mov     [bx], al
    nop
    nop
    cmp     [bx + 8], al
    nop
    jae     ret_202F
    mov     [bx + 8], al
    nop
    mov     byte [bx + 16], 100
    nop

ret_202F:
    ret


;
; 2056:
;
sub_2056:
    mov     si, 0
    mov     cx, 8

loc_205C:
    cmp     byte [si], 0
    je      loc_2064
    sub     byte [si], 3

loc_2064:
    cmp     byte [si + 16], 0
    je      loc_206F
    dec     byte [si + 16]
    jne     sub_2078

loc_206F:
    mov     al, [si]
    mov     [si + 8], al
    mov     byte [si + 16], 100

sub_2078:
    inc     si
    loop    loc_205C
    ret


;
; 207C: Called from cs:5116
;
sub_207C:
    push    ax
    mov     al, 6
    mul     cl
    mov     bx, ax
    pop     ax
    mov     di, [bx + arr_3A]
    nop
    jmp     word [word_36]             ; = 2557h


;
; 208C:
;
sub_208C:
    push    ax
    mov     al, 6
    mul     cl
    mov     bx, ax
    pop     ax
    mov     di, [bx + arr_3A]
    nop
    jmp     word [word_38]


;
; 209C:
;
sub_209C:
    mov     ax, sub_2141
    mov     [word_30], ax
    mov     [word_32], ax
    mov     [word_34], ax
    mov     byte [byte_22], 0
    mov     bx, [word_16F6]
    cmp     bl, 3
    ja      loc_20D9
    shl     bx, 1
    ; arr6_80 - for Adlib and Sound Blaster
    ; arr6_2DE - for Roland
    mov     si, [bx + word_18]
    nop
    mov     [word_20], si
    lodsw
    mov     cx, ds
    mov     es, cx
    mov     di, word_30                ; mov to word_30..=word_38
    mov     cx, 5
    ;           Roland
    ; word_30 = sub_27DF
    ; word_32 = sub_26EB
    ; word_34 = sub_2661
    ; word_36 = sub_281D
    ; word_38 = sub_283C
    rep movsw
    mov     cx, 8

loc_20D0:
    movsw                              ; arr_3A = arr8_8C
    add     di, 4
    loop    loc_20D0
    ; ax is loaded with lodsw above:
    ; sub_221F - for Sound Blaster and Adlib
    ; sub_25AD - for Roland
    ; sub_28FF - for PC speaker
    call    ax
    ret

loc_20D9:
    stc
    ret


;
; 20DB:
;
sub_20DB:
    cmp     byte [song_num], 0
    jnz     ret_20EC
    pusha
    push    ds
    push    es

loc_20E5:
    call    word [word_34]
    pop     es
    pop     ds
    popa

ret_20EC:
    ret


;
; 20ED: Init player
;
sub_20ED:
    call    sub_209C
    jb      ret_211D
    cmp     byte [song_num], 0
    je      loc_2113
    cmp     word [word_26], 0
    jz      ret_211D
    mov     al, 6
    call    sub_2207
    mov     byte [byte_23], 0
    call    sub_216D

loc_210D:
    mov     byte [byte_22], -1
    ret

loc_2113:
    cmp     word [word_16F6], 2
    jne     short ret_211D
    call    sub_2899

ret_211D:
    ret


;
; 211E:
;
sub_211E:
    call    word [word_30]
    cmp     byte [byte_22], 0
    jz      loc_213E
    mov     al, [byte_24]
    inc     byte [byte_23]
    cmp     [byte_23], al
    jb      loc_213E
    mov     byte [byte_23], 0
    call    sub_2142

loc_213E:
    call    sub_2056


;
; 2141:
;
sub_2141:
    ret


;
; 2142:
;
sub_2142:
    mov     es, [word_26]
    mov     di, [word_2A]
    mov     si, arr_3A
    call    sub_219F
    mov     si, arr_40
    call    sub_219F
    mov     si, arr_46
    call    sub_219F
    mov     si, arr_4C
    call    sub_219F
    cmp     word [es:di], 0FFFFh
    jz      short loc_2185
    xchg    di, [word_2A]
    ret


;
; 216D:
;
sub_216D:
    mov     word [word_28], 0
    cmp     byte [song_num], 3
    jne     loc_2185
    cmp     word [word_16F6], 3
    jne     loc_2185
    inc     word [word_28]

loc_2185:
    mov     es, [word_26]
    mov     di, [word_28]
    inc     word [word_28]
    shl     di, 1
    mov     di, [es:di]                ; di = 003C
    and     di, di
    jz      sub_216D
    mov     [word_2A], di              ; clock
    ret


;
; 219F:
;
sub_219F:
    mov     byte [word_2C], 0FFh
    mov     ax, [es:di]
    inc     di
    cmp     al, 0
    jz      ret_21FC
    inc     di
    test    al, 0C0h
    jz      loc_21BE
    test    al, 80h
    jnz     loc_21DF
    push    ax
    mov     al, [es:di]
    inc     di
    call    sub_21FD
    pop     ax

loc_21BE:
    mov     bl, al
    shr     bl, 2
    and     bx, 0Fh
    xchg    al, ah
    and     ax, 3FFh
    call    sub_2000
    mov     [si + 2], ax
    push    es
    push    di
    push    si
    mov     si, [si]
    call    word [word_32]             ; sub_232B (for Adlib and SB)
    pop     si
    pop     di
    pop     es
    jmp     loc_21F2

loc_21DF:
    dec     di

loc_21E0:
    call    sub_21FD
    mov     ax, [word_2C]
    cmp     al, 0FFh
    je      ret_21FC
    push    di
    mov     di, [si]
    call    word [word_36]             ; sub_2557 (for Adlib and SB)
    pop     di

loc_21F2:
    mov     ax, [word_2C]
    cmp     al, 0FFh
    je      ret_21FC
    mov     [si + 4], ax

ret_21FC:
    ret


;
; 21FD:
;
sub_21FD:
    test    al, 40h
    jne     sub_2207
    and     al, 3Fh
    mov     [word_2C], al
    ret


;
; 2207:
;
sub_2207:
    and     ax, 0Fh
    push    bx
    mov     bl, [song_num]
    mov     bh, 0
    shl     bx, 1
    mov     dx, [bx + tune_bpms]
    nop
    pop     bx
    mul     dx
    mov     [byte_24], ah
    ret


;
; 221F: called from cs:20D6 (call near ax) from sub_209C
;
sub_221F:
    mov     ax, [word_3D76]
    mov     dx, 0
    mov     bx, 303
    div     bx
    mov     [word_7C], ax
    mov     ax, [word_3D76]
    mov     dx, 0
    mov     bx, 43
    div     bx
    mov     [word_7E], ax
    mov     di, arr9_CC

loc_223E:
    mov     bx, [di]
    call    sub_2586
    mov     byte [di + 2], 0
    mov     word [di + 6], 0
    add     di, 18
    cmp     di, arr9_126
    jbe     loc_223E
    mov     ah, 1
    mov     al, 0
    call    sub_258F
    mov     ah, 4
    mov     al, 0E0h
    call    sub_258F
    mov     ah, 8
    mov     al, 0
    call    sub_258F
    mov     ah, 176
    mov     al, 0

loc_226E:
    call    sub_258F
    inc     ah
    cmp     ah, 185
    jb      loc_226E
    mov     ah, 0A0h
    mov     al, 0

loc_227C:
    call    sub_258F
    inc     ah
    cmp     ah, 0A9h
    jb      loc_227C
    mov     ah, 0C0h
    mov     al, 0

loc_228A:
    call    sub_258F
    inc     ah
    cmp     ah, 0C9h
    jb      loc_228A
    mov     ah, 0E0h
    mov     al, 0

loc_2298:
    call    sub_258F
    inc     ah
    cmp     ah, 0F6h
    jb      loc_2298
    mov     ah, 20h
    mov     al, 0

loc_22A6:
    call    sub_258F
    inc     ah
    cmp     ah, 36h
    jb      loc_22A6
    mov     ah, 40h
    mov     al, 3Fh

loc_22B4:
    call    sub_258F
    inc     ah
    cmp     ah, 56h
    jb      loc_22B4
    mov     ah, 60h
    mov     al, 0F0h

loc_22C2:
    call    sub_258F
    inc     ah
    cmp     ah, 76h
    jb      loc_22C2
    mov     ah, 80h
    mov     al, 1Fh

loc_22D0:
    call    sub_258F
    inc     ah
    cmp     ah, 96h
    jb      loc_22D0
    mov     ah, 0BDh
    mov     al, 40h
    call    sub_258F
    mov     ah, 1
    mov     al, 20h
    call    sub_258F
    call    sub_2C1F
    cmp     word [word_16F6], 0
    jne     loc_2321
    mov     dx, 226h
    mov     al, 1
    out     dx, al
    mov     cx, [word_7C]

loc_22FC:
    loop    loc_22FC
    mov     al, 0
    out     dx, al
    mov     cx, [word_7E]
    shl     cx, 2
    mov     dx, 22Eh

loc_230B:
    in      al, dx
    and     al, al
    js      loc_2314
    loop    loc_230B
    jmp     loc_2323

loc_2314:
    mov     dx, 22Ah
    in      al, dx
    cmp     al, 0AAh
    jne     loc_2323
    mov     al, 0D3h
    call    sub_2BC7

loc_2321:
    clc
    ret

loc_2323:
    mov     word [word_16F6], 1
    clc
    ret


;
; 232B:
;
sub_232B:
    mov     di, si
    shl     bx, 1
    mov     si, [bx + arr24_9C]
    and     si, si
    jne     loc_233A
    jmp     loc_23F2

loc_233A:
    mov     ch, [si + 11]
    mov     cl, 0
    cmp     ax, cx
    jb      loc_2346
    jmp     loc_23F2

loc_2346:
    mov     dx, ax
    mov     ax, 0
    div     cx
    mov     cx, 2000h
    cmp     ax, 23CCh
    jae     loc_235F

loc_2355:
    add     ch, 4
    shl     ax, 1
    cmp     ax, 23CCh
    jb      loc_2355

loc_235F:
    mov     bx, ax
    mov     dx, 47h
    mov     ax, 98B7h
    div     bx
    add     ax, cx
    push    di
    push    ax
    call    sub_23F3
    test    byte [si + 10], 80h
    je      loc_2390
    pop     ax
    push    ax
    mov     di, arr9_114
    mov     cx, ax
    and     cx, 0FC00h
    and     ax, 3FFh
    mov     dx, 0E412h
    mul     dx
    mov     ax, dx
    or      ax, cx
    call    sub_23F3

loc_2390:
    test    byte [si + 10], 40h
    je      loc_23B0
    pop     ax
    push    ax
    mov     di, arr9_114
    mov     cx, ax
    and     cx, 0FC00h
    and     ax, 3FFh
    mov     dx, 0D745h
    mul     dx
    mov     ax, dx
    or      ax, cx
    call    sub_23F3

loc_23B0:
    test    byte [si + 10], 20h
    je      loc_23D0

    pop     ax
    push    ax
    mov     di, arr9_126
    mov     cx, ax
    and     cx, 0FC00h
    and     ax, 3FFh
    mov     dx, 0BFC8h
    mul     dx
    mov     ax, dx
    or      ax, cx
    call    sub_23F3

loc_23D0:
    test    byte [si + 10], 10h
    je      loc_23F0

    pop     ax
    push    ax
    mov     di, arr9_126
    mov     cx, ax
    and     cx, 0FC00h
    and     ax, 3FFh
    mov     dx, 0AADCh
    mul     dx
    mov     ax, dx
    or      ax, cx
    call    sub_23F3

loc_23F0:
    pop     ax
    pop     di

loc_23F2:
    ret


;
; 23F3:
;
sub_23F3:
    mov     word [di + 6], 0


;
; 23F8:
;
sub_23F8:
    mov     [di + 4], ax
    push    ax
    mov     bx, [di]
    call    sub_2586
    mov     al, [si + 1]
    mov     [di + 2], al
    mov     ch, 0
    mov     al, [word_2C]
    cmp     al, 0FFh
    je      loc_241A
    push    bx
    mov     bh, 0
    mov     bl, al
    mov     ch, [bx + arr77_291]
    pop     bx

loc_241A:
    mov     cl, [bx + arr9_288]
    call    sub_2455
    push    si
    add     si, 5
    sub     cl, 3
    mov     ch, 0
    call    sub_2455
    pop     si
    mov     al, [si + 10]
    and     al, 0Fh
    mov     ah, bl
    add     ah, 0C0h
    call    sub_258F
    pop     ax
    cmp     byte [si + 12], 0
    jne     ret_2454
    mov     cl, ah
    mov     ah, bl
    add     ah, 0A0h
    call    sub_258F
    mov     al, cl
    add     ah, 10h
    call    sub_258F

ret_2454:
    ret


;
; 2455:
;
sub_2455:
    mov     ah, cl
    add     ah, 20h
    mov     al, [si]
    call    sub_258F
    add     ah, 20h
    mov     al, [si + 1]
    mov     dl, al
    and     dl, 0C0h
    and     al, 3Fh
    add     al, ch
    cmp     al, 40h
    jb      loc_2474
    mov     al, 3Fh

loc_2474:
    or      al, dl
    call    sub_258F
    add     ah, 20h
    mov     al, [si + 2]
    call    sub_258F
    add     ah, 20h
    mov     al, [si + 3]
    call    sub_258F
    add     ah, 60h
    mov     al, [si + 4]
    jmp     sub_258F


;
; 2494:
;
sub_2494:
    cmp     word [word_16F6], 0
    jne     loc_24AA
    cmp     cl, 0
    jne     loc_24AA
    cmp     al, 0
    jne     loc_24A7
    jmp     sub_2C1F

loc_24A7:
    jmp     loc_2AD7

loc_24AA:
    mov     bh, 0
    shl     bx, 1
    mov     si, [bx + arr24_9C + 2]
    and     si, si
    je      ret_24E4
    push    bx
    mov     [word_2C], al
    mov     bl, cl
    shl     bx, 1
    mov     di, [bx + arr8_8C]
    pop     bx
    mov     cx, [bx + arr_B83]
    mov     [di + 6], cx
    mov     word [di + 8], 0
    mov     ax, 0
    cmp     cx, ax
    jne     loc_24E1
    mov     al, [si + 11]
    mov     ah, 0
    shl     ax, 6
    or      ah, 20h

loc_24E1:
    call    sub_23F8

ret_24E4:
    ret


;
; 24E5:
;
sub_24E5:
    call    sub_2C8A
    inc     word [word_78]
    and     word [word_78], 3
    mov     bx, [word_78]
    shl     bx, 2
    mov     di, [bx + arr8_8C]
    push    word [bx + arr8_8C + 2]
    call    loc_2CE9
    pop     di
    jmp     loc_2CE9


;
; 2507:
;
sub_2507:
    cmp     word [di + 6], 0
    jne     loc_2550
    mov     bx, [di + 4]
    mov     cl, bh
    shr     cl, 2
    and     cl, 7
    and     bx, 3FFh
    shl     bx, cl
    mul     bx
    mov     al, ah
    mov     ah, dl
    mov     cl, 0
    jmp     loc_252B

loc_2528:
    shr     ax, 1
    inc     cx

loc_252B:
    test    ah, 0FCh
    jne     loc_2528
    cmp     cl, 7
    jbe     loc_2537
    mov     cl, 7

loc_2537:
    shl     cl, 2
    or      cl, ah
    or      cl, 20h
    mov     ah, [di]
    add     ah, 0A0h
    call    sub_258F
    add     ah, 10h
    mov     al, cl
    call    sub_258F
    ret

loc_2550:
    shr     ax, 2
    mov     [di + 16], ax
    ret


;
; 2557:
;
sub_2557:
    cmp     word [word_16F6], 0
    jne     loc_2564
    cmp     di, 0CCh
    je      loc_2580

loc_2564:
    mov     bh, 0
    mov     bl, al
    mov     al, [bx + arr77_291]
    add     al, [di + 2]
    cmp     al, 3Fh
    jb      loc_2575
    mov     al, 3Fh

loc_2575:
    mov     bx, [di]
    mov     ah, [bx + arr9_288]
    add     ah, 40h
    jmp     sub_258F

loc_2580:
    or      al, 1
    mov     [byte_5AE], al
    ret


;
; 2586:
;
sub_2586:
    mov     al, 0
    mov     ah, bl
    add     ah, 176
    jmp     sub_258F


;
; 258F:
;
sub_258F:
    pushf
    push    cx
    push    dx
    mov     dx, 388h                   ; address / status port (r/w)
    xchg    al, ah
    cli
    out     dx, al
    xchg    al, ah
    mov     cx, [word_7C]

loc_259F:
    loop    loc_259F
    inc     dx                         ; 389h - data port (w/o)
    out     dx, al
    mov     cx, [word_7E]

loc_25A7:
    loop    loc_25A7
    pop     dx
    pop     cx
    popf
    ret


;
; 25AD:
;
sub_25AD:
    mov     word [arr5_32A + 1], 0
    mov     word [arr5_32F + 1], 0
    mov     word [arr5_334 + 1], 0
    mov     word [arr5_339 + 1], 0
    mov     word [arr5_33E + 1], 0
    mov     word [arr5_343 + 1], 0
    mov     word [arr5_348 + 1], 0
    mov     word [arr5_34D + 1], 0
    cmp     byte [byte_3E1], 0FFh
    je      loc_264D
    cmp     byte [byte_3E1], 1
    je      loc_25FA
    mov     byte [byte_3E1], 0FFh
    call    sub_264F
    jb      loc_264D
    mov     byte [byte_3E1], 1

loc_25FA:
    mov     si, arr5_3C5
    call    sub_2864
    mov     si, arr23_3CA
    call    sub_2864
    mov     bx, 0B9B1h

loc_2609:
    mov     al, bl
    call    sub_28EB
    mov     al, 7Bh
    call    sub_28EB
    mov     al, 0
    call    sub_28EB
    mov     al, bl
    call    sub_28EB
    mov     al, 79h
    call    sub_28EB
    mov     al, 0
    call    sub_28EB
    mov     al, bl
    call    sub_28EB
    mov     al, 7
    call    sub_28EB
    mov     al, 7Fh
    call    sub_28EB
    mov     al, bl
    call    sub_28EB
    mov     al, 0Ah
    call    sub_28EB
    mov     al, 40h
    call    sub_28EB
    inc     bl
    cmp     bl, bh
    jbe     loc_2609
    clc
    ret

loc_264D:
    stc
    ret


;
; 264F:
;
sub_264F:
    mov     al, 0FFh
    call    sub_28AC                   ; al - port
    jae     loc_265D
    mov     al, 0FFh
    call    sub_28AC                   ; al - port
    jb      loc_2660

loc_265D:
    call    sub_28D2                   ; al - port

loc_2660:
    ret


;
; 2661:
;
sub_2661:
    cmp     byte [byte_3E1], 1
    je      loc_266B
    jmp     near ret_26EA

loc_266B:
    mov     bh, 0
    inc     bx
    shl     bx, 1
    mov     si, [bx + arr24_2FA]
    and     si, si
    jz      ret_26EA
    mov     bl, cl
    mov     bh, 0
    shl     bx, 1
    mov     di, [bx + arr8_2EA]
    call    sub_281D
    cmp     word [di + 1], 0
    je      loc_269C
    mov     al, [di + 3]
    call    sub_28EB
    mov     al, [di + 4]
    call    sub_28EB
    mov     al, 0
    call    sub_28EB

loc_269C:
    mov     al, 99h
    cmp     byte [si], 80h
    jae     loc_26C4
    mov     al, 0B0h
    add     al, [di]
    call    sub_28EB
    mov     al, 7Bh
    call    sub_28EB
    mov     al, 0
    call    sub_28EB
    mov     al, 0C0h
    add     al, [di]
    call    sub_28EB
    mov     al, [si]
    call    sub_28EB
    mov     al, 90h
    add     al, [di]

loc_26C4:
    mov     [di + 3], al
    call    sub_28EB
    mov     al, [si + 2]
    mov     [di + 4], al
    call    sub_28EB
    mov     al, [si + 3]
    call    sub_28EB
    mov     ah, 0
    mov     al, [si + 1]
    cmp     al, 0F0h
    jb      loc_26E7
    mov     ah, al
    and     ah, 0Fh

loc_26E7:
    mov     [di + 1], ax

ret_26EA:
    ret


;
; 26EB: Roland
;
sub_26EB:
    mov     di, si
    shl     bx, 1
    mov     si, [bx + arr24_2FA]
    and     si, si
    jnz     loc_26FA
    jmp     ret_27C2

loc_26FA:
    test    byte [si + 4], 1
    je      loc_2703
    jmp     ret_27C2

loc_2703:
    cmp     byte [si], 80h
    jb      loc_2722
    mov     al, 99h
    mov     [di + 3], al
    call    sub_28EB
    mov     al, [si + 2]
    mov     [di + 4], al
    call    sub_28EB
    mov     al, [si + 3]
    call    sub_28EB
    jmp     loc_27BA

loc_2722:
    mov     cx, 5
    cmp     ah, 0
    je      loc_2732

loc_272A:
    shr     ax, 1
    dec     cx
    cmp     ah, 0
    jne     loc_272A

loc_2732:
    and     al, al
    js      loc_273B
    shl     al, 1
    inc     cx
    jmp     loc_2732

loc_273B:
    and     cx, cx
    jns     loc_2742
    mov     cx, 0

loc_2742:
    cmp     cx, 8
    jb      loc_274A
    mov     cx, 8

loc_274A:
    mov     bx, ax
    mov     al, 12
    mul     cl
    add     al, [bx + arr5_3A2 + 1]
    push    ax
    mov     al, 0B0h
    add     al, [di]
    call    sub_28EB
    mov     al, 7Bh
    call    sub_28EB
    mov     al, 0
    call    sub_28EB
    mov     al, 0C0h
    add     al, [di]
    call    sub_28EB
    mov     al, [si]
    call    sub_28EB
    mov     al, [word_2C]
    cmp     al, 0FFh
    jne     loc_277B
    mov     al, 40h

loc_277B:
    call    sub_281D
    pop     ax
    push    ax
    call    sub_27C3
    pop     ax
    test    byte [si + 4], 80h
    je      loc_2792
    push    ax
    sub     ax, 2
    call    sub_27C3
    pop     ax

loc_2792:
    test    byte [si + 4], 40h
    je      loc_27A0
    push    ax
    sub     ax, 3
    call    sub_27C3
    pop     ax

loc_27A0:
    test    byte [si + 4], 20h
    je      loc_27AE
    push    ax
    sub     ax, 5
    call    sub_27C3
    pop     ax

loc_27AE:
    test    byte [si + 4], 10h
    je      loc_27BA
    sub     ax, 7
    call    sub_27C3

loc_27BA:
    mov     ah, 0
    mov     al, [si + 1]
    mov     [di + 1], ax

ret_27C2:
    ret


;
; 27C3:
;
sub_27C3:
    push    ax
    mov     al, 90h
    add     al, [di]
    mov     [di + 3], al
    call    sub_28EB
    pop     ax
    add     al, [si + 2]
    mov     [di + 4], al
    call    sub_28EB
    mov     al, [si + 3]
    call    sub_28EB
    ret


;
; 27DF:
;
sub_27DF:
    mov     si, arr5_32A

loc_27E2:
    cmp     word [si + 1], 0
    je      loc_2813
    dec     word [si + 1]
    jne     loc_2813
    mov     al, [si + 3]
    cmp     al, 99h
    je      loc_2805
    add     al, 20h
    call    sub_28EB
    mov     al, 7Bh
    call    sub_28EB
    mov     al, 0
    call    sub_28EB
    jmp     loc_2813

loc_2805:
    call    sub_28EB 
    mov     al, [si + 4]
    call    sub_28EB
    mov     al, 0
    call    sub_28EB

loc_2813:
    add     si, 5
    cmp     si, arr5_34D
    jbe     loc_27E2
    ret


;
; 281D: Roland
;
sub_281D:
    cmp     byte [byte_3E1], 1
    jne     ret_283B

    mov     bl, al
    mov     bh, 0
    mov     al, 0B0h
    add     al, [di]
    call    sub_28EB
    mov     al, 7
    call    sub_28EB
    mov     al, [bx + arr_3E2]
    call    sub_28EB

ret_283B:
    ret


;
; 283C:
;
sub_283C:
    cmp     byte [byte_3E1], 1
    jne     ret_2863
    shl     ax, 4
    shl     ax, 1
    shr     al, 1
    add     ah, 40h
    and     ah, 7Fh
    mov     bx, ax
    mov     al, 0E0h
    add     al, [di]
    call    sub_28EB
    mov     al, bl
    call    sub_28EB
    mov     al, bh
    call    sub_28EB

ret_2863:
    ret


;
; 2864:
;
sub_2864:
    mov     al, 0F0h
    call    sub_28EB
    mov     al, 41h
    call    sub_28EB
    mov     al, 10h
    call    sub_28EB
    mov     al, 16h
    call    sub_28EB
    mov     al, 12h
    call    sub_28EB
    mov     bl, 80h

loc_287F:
    lodsb
    and     al, al
    js      loc_288B
    sub     bl, al
    call    sub_28EB
    jmp     loc_287F

loc_288B:
    and     bl, 7Fh
    mov     al, bl
    call    sub_28EB
    mov     al, 0F7h
    call    sub_28EB
    ret


;
; 2899:
;
sub_2899:
    cmp     byte [byte_3E1], 1
    jne     ret_28AB
    mov     si, arr_74A

loc_28A3:
    call    sub_2864
    cmp     byte [si], 0
    jge     loc_28A3

ret_28AB:
    ret


;
; 28AC:
;
sub_28AC:
    push    cx
    push    ax
    mov     dx, 331h
    mov     cx, 0FFFFh

loc_28B4:
    in      al, dx
    test    al, 40h
    loopne  loc_28B4
    jne     loc_28CE
    pop     ax
    push    ax
    out     dx, al
    mov     cx, 0FFFFh

loc_28C1:
    in      al, dx
    test    al, 80h
    loopne  loc_28C1
    jne     loc_28CE
    dec     dx
    in      al, dx
    cmp     al, 0FEh
    je      loc_28CF

loc_28CE:
    stc

loc_28CF:
    pop     ax
    pop     cx
    ret


;
; 28D2:
;
sub_28D2:
    push    cx
    push    ax
    mov     dx, 331h
    mov     cx, 0FFFFh

loc_28DA:
    in      al, dx
    test    al, 40h
    loopne  loc_28DA
    jne     loc_28E7
    mov     al, 3Fh
    out     dx, al
    clc
    jmp     loc_28E8

loc_28E7:
    stc

loc_28E8:
    pop     ax
    pop     cx
    ret


;
; 28EB:
;
sub_28EB:
    push    cx
    push    dx
    push    ax
    mov     dx, 331h
    mov     cx, -1

loc_28F4:
    in      al, dx
    test    al, 40h                    ; make sure it isn't busy
    loopne  loc_28F4
    pop     ax
    dec     dx
    out     dx, al
    pop     dx
    pop     cx
    ret


;
; 28FF: PC speaker beep starts
;
sub_28FF:
    mov     di, arr6_4DC
    push    ds
    pop     es
    mov     cx, 24
    mov     al, 0
    rep stosb
    in      al, 61h
    and     al, 11111100b              ; reset first two bits
    out     61h, al
    mov     al, 0B6h                   ; set for channel 2 (8253)
    out     43h, al                    ; to command register
    ret


;
; 2916: PC speaker
;
sub_2916:
    mov     di, si
    shl     bx, 1
    mov     si, [bx + arr_500]
    and     si, si
    jz      ret_296A
    mov     dl, [si + 1]
    sub     dl, 12
    cmp     dl, 12
    jb      loc_2942
    jg      loc_2938

loc_292F:
    shl     ax, 1
    add     dl, 12
    jae     loc_292F
    jmp     loc_2942

loc_2938:
    shr     ax, 1
    sub     dl, 12
    cmp     dl, 12
    jae     loc_2938

loc_2942:
    mov     bl, dl
    mov     bh, 0
    shl     bx, 1
    mul     word [bx + arr12_4A5]
    mov     ax, 1366
    mul     dx
    mov     al, ah
    mov     ah, dl
    mov     [di + 4], ax
    mov     ah, 0
    mov     al, [si]
    cmp     al, 0FFh
    jne     loc_2962
    mov     ah, 7Fh

loc_2962:
    mov     [di], ax
    mov     al, [si + 2]
    mov     [di + 2], ax

ret_296A:
    ret


;
; 296B
;
sub_296B:
    cmp     cl, 5
    jb      ret_299C
    cmp     al, 16
    jb      ret_299C
    mov     di, [word_4BD]
    xor     word [word_4BD], 12h
    add     di, arr6_4DC
    mov     bh, 0
    shl     bx, 2
    mov     ax, [bx + word_54D]
    and     ax, ax
    jz      ret_299C
    mov     [di], ax
    mov     word [di + 2], 1
    mov     ax, [bx + word_54F]
    mov     [di + 4], ax

ret_299C:
    ret


;
; 299D:
;
sub_299D:
    cmp     di, arr6_4E2
    je      loc_29A9
    cmp     di, arr6_4E8
    jne     ret_29BF

loc_29A9:
    mov     word [di + 2], 1
    mov     word [di], 7FFFh
    mov     bx, ax
    mov     dx, 20
    mov     ax, 0
    div     bx
    mov     [di + 4], ax

ret_29BF:
    ret


;
; 29C0:
;
sub_29C0:
    cmp     al, 0
    jne     ret_29D5
    cmp     di, arr6_4E2
    je      loc_29D0
    cmp     di, arr6_4E8
    jne     ret_29D5

loc_29D0:
    mov     word [di + 2], 0

ret_29D5:
    ret


;
; 29D6:
;
sub_29D6:
    push    ds
    pop     es
    mov     cx, 4
    mov     si, arr6_4DC

loc_29DE:
    cmp     word [si], 0
    je      loc_29E7
    dec     word [si]
    jg      loc_29EC

loc_29E7:
    mov     word [si + 2], 0

loc_29EC:
    add     si, 6
    loop    loc_29DE
    dec     word [word_4C2]
    jg      ret_2A33
    mov     word [word_4C2], 4
    mov     bx, [word_4C0]
    mov     cx, 3

loc_2A04:
    add     bx, 2
    and     bx, 6
    mov     di, [bx + arr6_4D0]
    cmp     word [di + 2], 0
    loope   loc_2A04
    mov     [word_4C0], bx
    je      loc_2A2D
    mov     ax, [di + 4]
    out     42h, al
    mov     al, ah
    out     42h, al
    in      al, 61h
    and     al, 0FCh
    or      al, 3
    out     61h, al
    jmp     ret_2A33

loc_2A2D:
    in      al, 61h
    and     al, 0FCh
    out     61h, al

ret_2A33:
    ret


; 2A34: Play tune
;
; input:
; ax -- track number
play_music:
    push    ax
    call    sub_209C
    pop     ax
    mov     [song_num], al
    mov     ax, [cs:word_5168]
    mov     [word_63BA], ax
    mov     [word_26], ax
    cmp     byte [song_num], 0
    je      loc_2A5C
    mov     ah, 'T'
    mov     al, [song_num]
    call    res_load
    mov     [cs:word_5166], ax
    mov     [word_63BA], ax            ; unpacked data

loc_2A5C:
    call    sub_2A66                   ; A03
    call    sub_2A8D                   ; R03
    call    sub_2AB4                   ; P03
    ret


;
; 2A66:
;
sub_2A66:
    mov     ah, 'A'
    mov     al, [song_num]
    call    res_load
    push    ds
    push    ds
    pop     es
    mov     ds, [word_63BA]
    mov     si, 0
    mov     di, arr13_15C
    mov     cx, 195
    cmp     byte [es:song_num], 0
    jne     loc_2A89
    mov     cx, 299

loc_2A89:
    rep movsb
    pop     ds
    ret


;
; 2A8D:
;
sub_2A8D:
    mov     ah, 'R'
    mov     al, [song_num]
    call    res_load
    push    ds
    push    ds
    pop     es
    mov     ds, [word_63BA]
    mov     si, 0
    mov     di, 352h
    mov     cx, 75
    cmp     byte [es:song_num], 0
    jne     loc_2AB0
    mov     cx, 115

loc_2AB0:
    repe movsb
    pop     ds
    ret


;
; 2AB4:
;
sub_2AB4:
    cmp     byte [song_num], 0
    je      ret_2AD6
    mov     ah, 'P'
    mov     al, [song_num]
    call    res_load
    push    ds
    push    ds
    pop     es
    mov     ds, [word_63BA]
    mov     si, 0
    mov     di, arr3_520
    mov     cx, 45
    repe movsb
    pop     ds

ret_2AD6:
    ret


loc_2AD7:
    cmp     word [word_2AF9], 0
    jne     loc_2AE1
    jmp     ret_2BC6

loc_2AE1:
    mov     [byte_5AE], al
    mov     al, 0D0h
    call    sub_2BC7
    sub     ax, ax
    mov     es, ax
    mov     ax, cs
    cmp     ax, [es:3Eh]
    je      loc_2B11
    cli
    xchg    [es:3Eh], ax
    mov     [word_5AC], ax
    mov     ax, sub_2C49
    xchg    [es:3Ch], ax
    mov     [word_5AA], ax
    in      al, 21h
    and     al, 7Fh
    out     21h, al
    sti

loc_2B11:
    mov     ax, [word_2AF9]
    mov     dx, 0
    mov     cx, 100h
    div     cx
    mov     cx, ax
    mov     ax, [word_2AF9]
    mov     dx, 0
    div     cx
    mov     bx, ax
    mov     ax, 0
    div     cx
    mov     dx, ax
    mov     dl, 0
    mov     [word_5B4], cx
    mov     di, word_5C4
    mov     si, 0

loc_2B3B:
    mov     [di], si
    add     di, 4
    add     dl, dh
    adc     si, bx
    loop    loc_2B3B
    mov     cx, [word_5B4]
    mov     si, [word_2AF9]

loc_2B4E:
    sub     di, 4
    sub     si, [di]
    mov     [di + 2], si
    mov     si, [di]
    loop    loc_2B4E
    mov     ax, [word_63BA]
    mov     bx, ax
    shl     bx, 4
    add     bx, 35Dh
    jae     loc_2B6C
    or      ax, 0FFFh
    inc     ax

loc_2B6C:
    mov     es, ax
    mov     bx, 11h
    mov     dx, bx
    shl     dx, 4
    mov     [word_5B8], ax
    mov     [word_5BA], dx
    add     ax, bx
    mov     [word_5BC], ax
    mov     [word_5BE], dx
    add     ax, bx
    mov     [word_5C0], ax
    mov     [word_5C2], dx
    mov     cx, dx
    shl     cx, 1
    add     cx, dx
    mov     di, 0
    mov     al, 80h
    rep stosb
    mov     word [word_5B0], 0FFFFh
    mov     word [word_5B6], 0
    mov     al, 40h
    call    sub_2BC7
    mov     al, 83h
    call    sub_2BC7
    mov     ax, [word_5B8]
    mov     bx, [word_5BA]
    call    sub_2BE2
    mov     al, 0D4h
    call    sub_2BC7
    mov     al, 0D1h
    call    sub_2BC7

ret_2BC6:
    ret


;
; 2BC7:
;
sub_2BC7:
    mov     ah, al
    mov     cx, [word_7E]
    mov     dx, 22Ch

loc_2BD0:
    in      al, dx
    and     al, al
    jns     loc_2BDE
    loop    loc_2BD0
    mov     word [word_16F6], 1
    ret

loc_2BDE:
    mov     al, ah
    out     dx, al
    ret


;
; 2BE2:
;
sub_2BE2:
    dec     bx
    push    bx
    mov     bx, ax
    mov     al, 5
    out     0Ah, al
    mov     al, 0
    out     0Ch, al
    mov     al, 49h
    out     0Bh, al
    shl     bx, 4
    mov     al, bl
    out     2, al
    mov     al, bh
    out     2, al
    shr     ax, 12
    out     83h, al
    pop     bx
    mov     al, bl
    out     3, al
    mov     al, bh
    out     3, al
    mov     al, 1
    out     0Ah, al
    mov     al, 14h
    call    sub_2BC7
    mov     al, bl
    call    sub_2BC7
    mov     al, bh
    call    sub_2BC7
    ret


;
; 2C1F:
;
sub_2C1F:
    mov     byte [byte_5AE], 0
    mov     al, 0D0h
    call    sub_2BC7
    mov     al, 0D3h
    call    sub_2BC7
    sub     ax, ax
    cmp     [word_5AA], ax
    je      ret_2C48
    mov     es, ax
    cli
    mov     ax, [word_5AA]
    mov     [es:3Ch], ax
    mov     ax, [word_5AC]
    mov     [es:3Eh], ax
    sti

ret_2C48:
    ret


;
; 2C49:
;
sub_2C49:
    pusha
    push    ds
    mov     dx, 22Eh
    in      al, dx
    mov     ax, data_seg
    mov     ds, ax
    mov     ax, [word_5B0]
    inc     ax
    cmp     ax, [word_5B4]
    jb      loc_2C61
    mov     ax, 0

loc_2C61:
    mov     [word_5B0], ax
    mov     ax, [word_5B6]
    inc     ax
    cmp     ax, 3
    jb      loc_2C70
    mov     ax, 0

loc_2C70:
    mov     [word_5B6], ax
    shl     ax, 2
    mov     si, ax
    mov     ax, [si + word_5B8]
    mov     bx, [si + word_5BA]
    call    sub_2BE2
    mov     al, 20h
    out     20h, al
    pop     ds
    popa
    iret


;
; 2C8A:
;
sub_2C8A:
    cmp     byte [byte_5AE], 0
    je      ret_2CE8
    cli
    mov     ax, [word_5B6]
    mov     si, [word_5B0]
    sti
    cmp     si, [word_5B2]
    je      ret_2CE8
    mov     [word_5B2], si
    and     si, si
    js      ret_2CE8
    dec     ax
    jns     loc_2CAE
    add     ax, 3

loc_2CAE:
    shl     ax, 2
    mov     bx, word_5B8
    add     bx, ax
    mov     es, [bx]
    shl     si, 2
    mov     cx, [si + word_5C4 + 2]
    mov     [bx + 2], cx
    mov     si, [si + word_5C4]
    mov     di, 0
    mov     dl, [byte_5AE]
    cmp     dl, 40h
    jb      loc_2CD4
    mov     dl, 3Fh

loc_2CD4:
    shl     dl, 1
    push    ds
    mov     ds, [word_2AF7]

loc_2CDB:
    lodsb
    sub     al, 80h
    imul    dl
    mov     al, ah
    add     al, 80h
    stosb
    loop    loc_2CDB
    pop     ds

ret_2CE8:
    ret


loc_2CE9:
    mov     si, [di + 6]
    and     si, si
    jne     loc_2CF1
    ret

loc_2CF1:
    cmp     word [di + 8], 7FFFh
    je      loc_2D09
    cmp     word [di + 8], 0
    jne     loc_2D01
    jmp     loc_2DA6

loc_2D01:
    dec     word [di + 8]
    jne     loc_2D09
    dec     word [di + 8]

loc_2D09:
    mov     bh, 0
    cmp     byte [di + 11], 0
    je      loc_2D43
    mov     bl, [di + 10]
    dec     byte [di + 11]
    jne     loc_2D3A
    inc     bx
    cmp     bl, [si + 2]
    jb      loc_2D2D
    mov     bl, [si + 3]
    cmp     bl, [si + 2]
    jb      loc_2D2D
    mov     byte [di + 11], 0
    jmp     loc_2D43

loc_2D2D:
    mov     [di + 10], bl
    shl     bx, 1
    mov     al, [bx + si + 6]
    shr     bx, 1
    mov     [di + 11], al

loc_2D3A:
    shl     bx, 1
    mov     al, [bx + si + 7]
    cbw
    add     [di + 14], ax

loc_2D43:
    mov     ax, 0
    cmp     byte [di + 13], 0
    je      loc_2D6A
    mov     bl, [di + 12]
    inc     bx
    cmp     bl, [si + 4]
    jb      loc_2D63
    mov     bl, [si + 5]
    cmp     bl, [si + 4]
    jb      loc_2D63
    mov     byte [di + 13], 0
    jmp     loc_2D6A

loc_2D63:
    mov     [di + 12], bl
    mov     al, [bx + si + 16]
    cbw

loc_2D6A:
    add     ax, [di + 14]
    add     ax, [di + 16]
    cmp     ax, 180h
    jae     ret_2DA5
    mov     cl, 30h
    div     cl
    mov     ch, al
    shl     ch, 2
    cmp     word [di + 8], 0
    jl      loc_2D87
    or      ch, 20h

loc_2D87:
    mov     bl, ah
    mov     bh, 0
    shl     bx, 1
    mov     cl, 0
    or      cx, [bx + arr48_C77]
    mov     ah, [di]
    add     ah, 0A0h
    mov     al, cl
    call    sub_258F
    add     ah, 10h
    mov     al, ch
    call    sub_258F

ret_2DA5:
    ret

loc_2DA6:
    mov     al, [si]
    cbw
    add     al, [si - 1]
    adc     ah, 0
    mov     [di + 14], ax
    mov     word [di + 16], 0
    mov     ah, 0
    mov     al, [si + 1]
    and     ax, ax
    jne     loc_2DC3
    mov     ax, 7FFFh

loc_2DC3:
    mov     [di + 8], ax
    mov     byte [di + 11], 0
    mov     byte [di + 13], 0
    cmp     byte [si + 2], 0
    je      loc_2DDC
    mov     byte [di + 10], 0FEh       ; -2
    mov     byte [di + 11], 1

loc_2DDC:
    cmp     byte [si + 4], 0
    je      loc_2DEA
    mov     byte [di + 12], 0FEh       ; -2
    mov     byte [di + 13], 1

loc_2DEA:
    jmp     loc_2D09
