;
; CC17:
;
sub_CC17:
    mov     ax, 128
    cmp     word [is_circular_track], 0
    jnz     loc_CC27
    mov     ax, [word_23F2]
    sub     ax, 16

loc_CC27:
    mov     [word_3C70], ax
    mov     word [word_3C72], 0
    mov     bx, 0
    mov     cx, 0
    cmp     word [is_2pl_mode], 0
    jnz     loc_CC3E
    dec     cx

loc_CC3E:
    mov     ax, 19
    and     bx, bx
    js      loc_CC48
    mov     bx, ax
    dec     ax

loc_CC48:
    and     cx, cx
    js      loc_CC4F
    mov     cx, ax
    dec     ax

loc_CC4F:
    mov     [word_3C74], ax
    mov     ah, 12
    mul     ah
    mov     [word_3C76], ax
    mov     word [word_6350], 20
    cmp     word [course_type], 3
    jz      loc_CC8A
    cmp     word [word_1F28], 0
    jz      loc_CC8A
    cmp     word [word_3EE4], 0
    jz      loc_CC8A
    and     bx, bx
    js      loc_CC7F
    mov     bx, 20
    sub     bx, [word_401C]

loc_CC7F:
    and     cx, cx
    js      loc_CC8A
    mov     cx, 20
    sub     cx, [word_4116]

loc_CC8A:
    mov     [word_401C], bx
    mov     [word_4116], cx
    mov     word [word_4026], 1
    mov     word [word_4120], 2
    mov     ax, 0
    mov     [word_3F3A], ax
    mov     [word_3F3C], ax
    mov     [word_4034], ax
    mov     [word_4036], ax
    mov     bx, [word_401C]
    mov     cx, [word_4116]
    mov     bp, 0
    mov     di, [word_4E78]
    add     di, 40
    mov     word [word_637A], word_3CD8
    mov     si, arr_417E

loc_CCC8:
    xchg    si, [word_637A]
    sub     si, 4
    mov     ax, [si]
    mov     [word_6354], ax
    mov     ax, [si + 2]
    xchg    si, [word_637A]
    cmp     word [is_circular_track], 0
    jz      loc_CCF1
    xchg    ax, [word_6354]
    sub     ax, 8
    add     ax, [word_23F2]
    xchg    ax, [word_6354]

loc_CCF1:
    cmp     bp, bx
    jz      loc_CD37
    cmp     bp, cx
    jz      loc_CD5C
    mov     [si + 2], ax
    mov     ax, [word_6354]
    mov     [si], ax
    add     si, 4
    sub     di, 2
    mov     ax, [di]
    mov     [si], ax
    add     si, 2
    mov     word [si], 0
    add     si, 2
    call    sub_AB9A
    and     ax, 7FFh
    sub     ax, 400h
    mov     [si], ax
    add     si, 2
    call    sub_AB9A
    and     ax, 3
    sub     ax, 2
    cmp     al, 1
    adc     al, 0
    mov     [si], ax
    add     si, 2
    jmp     loc_CD7F

loc_CD37:
    mov     [word_3F3C], ax
    mov     [word_3F44], ax
    or      ax, 3FFFh
    mov     [word_3F82], ax
    mov     ax, [word_6354]
    mov     [word_3F3A], ax
    mov     [word_3F42], ax
    mov     [word_3F80], ax
    sub     di, 2
    mov     ax, [di]
    mov     [word_3F3E], ax
    mov     [word_3F46], ax
    jmp     loc_CD7F

loc_CD5C:
    mov     [word_4036], ax
    mov     [word_403E], ax
    or      ax, 3FFFh
    mov     [word_407C], ax
    mov     ax, [word_6354]
    mov     [word_4034], ax
    mov     [word_403C], ax
    mov     [word_407A], ax
    sub     di, 2
    mov     ax, [di]
    mov     [word_4038], ax
    mov     [word_4040], ax

loc_CD7F:
    inc     bp
    cmp     bp, [word_6350]
    jnb     loc_CD89
    jmp     loc_CCC8

loc_CD89:
    mov     bx, [word_2AB2]
    or      bl, 0Eh
    mov     cx, [word_4026]
    mov     al, 1
    shl     al, cl
    not     al
    and     bl, al
    cmp     word [is_2pl_mode], 0
    jz      loc_CDAF
    mov     cx, [word_4120]
    mov     al, 1
    shl     al, cl
    not     al
    and     bl, al

loc_CDAF:
    mov     si, word_4306
    mov     bp, [word_3C74]

loc_CDB6:
    call    sub_AB9A
    and     ax, 7
    mov     cx, ax
    mov     al, 1
    shl     al, cl
    test    al, bl
    jz      loc_CDB6
    mov     [si + 6], cx
    add     si, 8
    dec     bp
    jns     loc_CDB6
    push    ds
    pop     es
    mov     si, arr_3C78
    mov     di, arr_412E
    mov     cx, 8

loc_CDDA:
    movsw
    mov     ax, 0
    stosw
    call    sub_AB9A
    mov     ah, 0
    add     ax, 64
    neg     ax
    stosw
    mov     ax, 1
    stosw
    loop    loc_CDDA
    ret


;
; CDF1:
;
sub_CDF1:
    push    ds
    pop     es
    mov     si, word_3D24
    cmp     word [word_3EE4], 0
    jnz     loc_CE00
    mov     si, word_3D14

loc_CE00:
    mov     di, word_3D34
    mov     cx, 8
    rep movsw
    mov     di, arr_7856
    mov     ax, 0
    mov     cx, 2304

loc_CE11:
    stosb
    inc     ax
    cmp     ax, [word_23F2]
    jne     loc_CE1C
    mov     ax, 0

loc_CE1C:
    loop    loc_CE11
    mov     ax, 0
    mov     bx, [word_2422]
    cmp     word [word_3EE4], 0
    jz      loc_CE2F
    mov     bx, 0

loc_CE2F:
    mov     cx, -1
    cmp     word [is_circular_track], 0
    jnz     loc_CE3C
    mov     cx, 0

loc_CE3C:
    mov     si, word_3F3A
    call    sub_CEB9
    cmp     word [is_2pl_mode], 0
    jnz     loc_CE4C
    mov     bx, 0

loc_CE4C:
    mov     si, word_4034
    call    sub_CEB9
    mov     di, arr_3CEC
    mov     ax, 0
    mov     cx, 20
    rep stosw
    mov     [word_3CDC], ax
    mov     [word_3CDE], ax
    mov     [word_3CE0], ax
    mov     [word_3CE2], ax
    mov     ax, [word_23F2]
    cmp     word [is_circular_track], 0
    jnz     loc_CE78
    add     ax, 8
    jmp     loc_CE7F

loc_CE78:
    mov     bx, [num_of_tracks]
    inc     bx
    mul     bx

loc_CE7F:
    mov     [word_3CD8], ax
    mov     word [word_3CDA], 0
    mov     word [word_3CE4], 0
    mov     word [word_3CE6], 0
    mov     word [word_3CEA], -1
    mov     word [word_3EE0], -250
    mov     word [word_3EE2], 0
    mov     word [word_3EE6], 0
    mov     word [word_3EEA], 0
    mov     word [word_3EEC], 40h
    ret


;
; CEB9:
;
sub_CEB9:
    mov     word [si + 222], -1
    mov     word [si + 224], -1
    mov     [si + 218], cx
    mov     [si + 32], bx
    mov     word [si + 34], 0
    mov     [si + 228], ax
    mov     [si + 230], ax
    mov     [si + 232], ax
    mov     [si + 220], ax
    mov     [si + 216], ax
    mov     [si + 168], ax
    mov     [si + 188], ax
    mov     [si + 190], ax
    mov     [si + 60], ax
    mov     [si + 62], ax
    mov     [si + 64], ax
    mov     [si + 40], ax
    mov     [si + 14], ax
    mov     [si + 20], ax
    mov     [si + 18], ax
    mov     [si + 16], ax
    mov     [si + 22], ax
    mov     [si + 196], ax
    mov     [si + 206], ax
    mov     [si + 28], ax
    mov     [si + 212], ax
    mov     [si + 38], ax
    mov     [si + 44], ax
    mov     [si + 36], ax
    mov     [si + 26], ax
    ret


;
; CF28:
;
sub_CF28:
    mov     ax, [word_2AB8]
    shl     ax, 2
    neg     ax
    sub     ax, 32
    mov     [word_6334], ax
    neg     ax
    mov     [word_6336], ax
    sub     ax, 72
    neg     ax
    mov     [word_6338], ax
    cmp     word [word_63B4], 0
    jz      loc_CF50
    mov     word [word_6334], 0FF30h

loc_CF50:
    mov     di, arr_68C2
    push    ds
    pop     es
    mov     cx, 0

loc_CF58:
    mov     al, 0F5h
    mul     cl
    add     ax, 4F6h
    mov     bx, ax
    mov     ax, 10A0h
    mov     dx, 4Fh
    div     bx
    stosw
    inc     cl
    jns     loc_CF58                   ; while cl != 128 (80h)
    mov     si, arr_68C2
    mov     di, arr_67C2
    mov     cx, 128

loc_CF77:
    lodsw
    shr     ax, 4
    sub     ax, 0Ah
    mov     dx, 3A83h
    mul     dx
    mov     ax, dx
    add     ax, [word_633A]
    sub     ax, 38h
    stosw
    loop    loc_CF77                   ; 128 times
    mov     word [arr_68C2], 0FFFh
    mov     ax, [word_633A]
    dec     ax
    mov     [arr_67C2], ax
    mov     di, arr_6DC4
    mov     ax, 0
    mov     cx, 201

loc_CFA5:
    stosw
    add     ax, 2Ah
    loop    loc_CFA5
    mov     si, arr_68C2
    mov     di, arr_69C2
    mov     cx, 128

loc_CFB4:
    lodsw
    mov     dx, 100h
    mul     dx
    mov     bx, 1000h
    div     bx
    mov     bx, ax
    mov     al, [bx + arr_5F40]
    cbw
    stosw
    loop    loc_CFB4                   ; 128 times
    mov     si, arr_68C2
    mov     di, arr_6AC2
    mov     cx, 128

loc_CFD2:
    lodsw
    mov     dx, 0C0h
    mul     dx
    mov     bx, 1000h
    div     bx
    mov     bx, ax
    mov     al, [bx + arr_5F40]
    cbw
    stosw
    loop    loc_CFD2                   ; 128 times
    mov     di, arr_6BC2
    mov     cx, 0

loc_CFED:
    mov     ax, cx
    mul     word [word_2AB6]
    mov     bx, 64
    div     bx
    stosw
    inc     cx
    cmp     cx, 257
    jne     loc_CFED
    ret


;
; D001:
;
sub_D001:
    push    ds
    pop     es
    mov     bx, arr_3D44
    mov     cx, 9

loc_D009:
    lodsw
    mov     [bx], al
    inc     bx
    loop    loc_D009
    lodsw
    push    ax
    mov     bx, arr_3D44
    call    sub_D085
    mov     si, arr_3D44
    mov     cx, 9
    mov     ah, 0

loc_D01F:
    lodsb
    cmp     al, 0Dh
    jz      loc_D02C
    js      loc_D028
    dec     al

loc_D028:
    add     al, 'a'
    jmp     loc_D02E

loc_D02C:
    mov     al, ' '

loc_D02E:
    stosb
    loop    loc_D01F
    mov     al, '-'
    stosb
    pop     ax
    mov     bl, 10
    div     bl
    add     ax, 3030h
    stosw
    ret


;
; D03E: Converts ASCII game code to binary presentation.
;
; in:
; ds:si - code: ^[a-z ]{9}-[\d ]{2}$ (eg: `abcdefghj-12`)
; es:di - result data location
;
; out:
; arr_3D44 - 'decrypted' letters
;
sub_D03E:
    mov     bx, arr_3D44
    mov     cx, 9                      ; 9 letters

loc_D044:
    lodsb
    cmp     al, ' '
    je      loc_D059
    cmp     al, 'a'
    jae     loc_D04F
    add     al, ' '

loc_D04F:
    cmp     al, 'n'
    js      loc_D055
    inc     al

loc_D055:
    sub     al, 'a'
    jmp     loc_D05B

loc_D059:
    mov     al, 0Dh

loc_D05B:
    mov     [bx], al
    inc     bx
    loop    loc_D044                   ; load next byte
    mov     bx, arr_3D44
    call    sub_D085
    push    ds
    pop     es
    mov     bx, arr_3D44
    mov     cx, 9
    mov     ah, 0

loc_D070:
    mov     al, [bx]
    inc     bx
    stosw
    loop    loc_D070                   ; for i in 0..9 { es:di = arr_3D44[i] }
    inc     si                         ; skip the `-`
    ; convert numeric ASCII to binary value and store it
    lodsw
    sub     ax, 3030h
    mov     bl, ah
    mov     ah, 10
    mul     ah
    add     al, bl
    stosw
    ret


;
; D085:
;
; for i in 0..9 { arr_3D44[i] = arr_3D4E[arr_3D44[i]]; }
;
; in:
; bx - source data;
;
sub_D085:
    push    si
    mov     si, bx
    mov     bx, arr_3D4E
    mov     cx, 9

loc_D08E:
    lodsb
    xlatb
    mov     [si - 1], al
    loop    loc_D08E                   ; for i in 0..9 { .. }
    pop     si
    ret
