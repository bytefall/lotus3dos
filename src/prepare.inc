;
; AC46:
;
prep_track:
    push    ds
    pop     es
    mov     di, tmp_file_buf
    mov     cx, 8192
    mov     ax, 0
    rep stosw
    call    prep_track_hills
    call    prep_track_turns
    call    sub_BCCF
    call    prep_track_signs
    call    sub_B0FC
    call    sub_B2B0
    call    sub_B5A1
    call    sub_B6BE 
    call    sub_B7FD
    call    sub_BAD4
    call    prep_track_bridges
    cmp     word [is_circular_track], 0
    jz      loc_AC8D
    mov     di, tmp_file_buf
    mov     si, di
    mov     ax, [word_23F2]
    shl     ax, 4
    add     di, ax
    mov     cx, 128
    rep movsw

loc_AC8D:
    mov     ax, [word_23F2]
    add     ax, 8
    cmp     word [is_circular_track], 0
    jnz     loc_AC9D
    add     ax, 8

loc_AC9D:
    shl     ax, 4
    mov     di, tmp_file_buf
    add     di, ax
    mov     cx, arr_C156
    sub     cx, di
    shr     cx, 1
    mov     ax, 0
    rep stosw
    ret


;
; ACB2: Add slopes and climbs.
;
prep_track_hills:
    cmp     word [word_63B4], 0
    jz      loc_ACC5
    mov     word [word_2448], 0
    mov     word [word_244A], 0

loc_ACC5:
    mov     ax, 192
    mul     word [word_2448]
    mov     bp, 100
    div     bp
    add     ax, 0
    mov     [word_245C], ax
    mov     ax, 160
    mul     word [word_2448]
    div     bp
    add     ax, 32
    mov     [word_245E], ax
    mov     ax, 128
    mul     word [word_244A]
    div     bp
    add     ax, 0
    mov     [word_2458], ax
    mov     ax, 160
    mul     word [word_244A]
    div     bp
    add     ax, 32
    mov     [word_245A], ax
    mov     si, [word_23FC]
    mov     ax, [word_23FE]
    mov     [word_636E], ax
    mov     word [word_6366], 0
    mov     word [word_6382], arr_2400
    mov     bx, 18
    call    sub_AE5F

loc_AD20:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_245C]
    jns     loc_AD87
    mov     bx, 2

loc_AD2E:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_245E]
    jns     loc_AD41
    add     bx, 2
    cmp     bx, 12
    jnz     loc_AD2E

loc_AD41:
    mov     cx, 1

loc_AD44:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_245A]
    jns     loc_AD55
    inc     cx
    cmp     cx, 6
    jnz     loc_AD44

loc_AD55:
    mov     dx, 0FFFFh
    cmp     byte [word_6366], 0
    jns     loc_AD61
    neg     dx

loc_AD61:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2458]
    jns     loc_AD6E
    neg     dx

loc_AD6E:
    push    dx
    mov     ax, dx
    imul    cx
    imul    bx
    add     al, byte [word_6366]
    pop     dx
    cmp     al, 12
    jns     loc_AD20
    cmp     al, 0F4h
    js      loc_AD20
    call    sub_AE3C
    jmp     loc_AD8D

loc_AD87:
    mov     bx, 2
    call    sub_AE5F

loc_AD8D:
    cmp     word [is_circular_track], 0
    jnz     loc_ADD8
    mov     di, [word_6382]
    mov     ax, [word_636E]
    cmp     ax, [di]
    js      loc_ADD8
    mov     ax, [di]
    add     word [word_6382], 2
    mov     bp, ax
    add     bp, 18
    mov     [word_636E], bp
    mov     si, tmp_file_buf
    shl     bp, 4
    add     si, bp
    shl     ax, 4
    mov     di, tmp_file_buf
    add     di, ax
    mov     bp, 18

loc_ADC2:
    mov     byte [di + 1], 0
    mov     al, [di + 13]
    mov     [di + 29], al
    add     di, 16
    dec     bp
    jnz     loc_ADC2
    mov     al, [di + 13]
    mov     byte [word_6366], al

loc_ADD8:
    mov     ax, [word_636E]
    cmp     ax, [word_23F2]
    ja      loc_ADE4
    jmp     loc_AD20

loc_ADE4:
    cmp     word [is_circular_track], 0
    jz      ret_AE3B
    mov     si, [word_23FC]
    mov     ax, [word_23F2]
    shl     ax, 4
    add     si, ax
    mov     word [word_6366], 0

loc_ADFD:
    inc     word [word_6366]
    sub     si, 16
    mov     bl, [si + 13]
    and     bl, bl
    jns     loc_AE0D
    neg     bl

loc_AE0D:
    cmp     bl, byte [word_6366]
    jz      loc_AE15
    jns     loc_ADFD

loc_AE15:
    cmp     byte [si + 13], 0
    mov     al, 0
    jz      loc_AE23
    mov     al, 0FFh
    jns     loc_AE23
    mov     al, 1

loc_AE23:
    mov     [si + 1], al
    mov     cl, al
    add     cl, [si + 13]
    jnz     loc_AE2F
    mov     al, 0

loc_AE2F:
    mov     [si + 29], cl
    add     si, 16
    dec     word [word_6366]
    jns     loc_AE23

ret_AE3B:
    ret


;
; AE3C:
;
; in:
; bx -
; cx -
; dx -
; si -
sub_AE3C:
    add     [word_636E], bx
    push    ax
    push    dx
    mov     ax, cx
    imul    dx
    mov     ah, [word_6366]

loc_AE4A:
    mov     [si + 1], al
    mov     [si + 13], ah
    add     ah, al
    add     si, 16
    dec     bx
    jnz     loc_AE4A
    mov     [word_6366], ah
    pop     dx
    pop     ax
    ret


;
; AE5F:
;
; in:
; ax -
; bx -
sub_AE5F:
    cmp     byte [word_6366], 0
    jz      loc_AE70
    call    smart_crc
    mov     ah, 0
    cmp     ax, 64
    js      loc_AE85

loc_AE70:
    add     [word_636E], bx

loc_AE74:
    mov     byte [si + 1], 0
    mov     al, [word_6366]
    mov     [si + 13], al
    add     si, 16
    dec     bx
    jnz     loc_AE74
    ret

loc_AE85:
    mov     dx, 0FFFFh
    mov     bl, [word_6366]
    and     bl, bl
    jns     loc_AE95
    mov     dx, 1
    neg     bl

loc_AE95:
    mov     cx, 1
    mov     bh, 0
    jmp     sub_AE3C


;
; Add left / right turns to the track
;
prep_track_turns:
    mov     ax, 160
    mul     word [word_2442]
    mov     bp, 100
    div     bp
    add     ax, 32
    mov     [word_2464], ax
    mov     ax, 160
    mul     word [word_2442]
    div     bp
    add     ax, 32
    mov     [word_2466], ax
    mov     ax, 160
    mul     word [word_2444]
    div     bp
    add     ax, 64
    mov     [word_2460], ax
    mov     ax, 160
    mul     word [word_2444]
    div     bp
    add     ax, 32
    mov     [word_2462], ax
    mov     si, [word_23FC]
    mov     ax, [word_23FE]
    mov     [word_636E], ax
    mov     word [word_636A], 0
    mov     word [word_6366], 0
    mov     dx, 1
    mov     bx, 16
    call    sub_B005

loc_AEFA:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2464]
    jns     loc_AF72
    mov     bx, 4

loc_AF08:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2466]
    jns     loc_AF1B
    add     bx, 4
    cmp     bx, 24
    jnz     loc_AF08

loc_AF1B:
    mov     cx, 4

loc_AF1E:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2462]
    jns     loc_AF2F
    inc     cx
    cmp     cx, 6
    jnz     loc_AF1E

loc_AF2F:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2460]
    jns     loc_AF3C
    neg     dx

loc_AF3C:
    cmp     word [is_circular_track], 0
    jz      loc_AF6D
    mov     ax, [word_636E]
    add     ax, bx
    push    dx
    mov     bp, 0FFA0h                 ; -96
    imul    bp
    idiv    word [word_23F2]
    pop     dx
    push    ax
    push    dx
    mov     ax, dx
    imul    cx
    imul    bx
    add     ax, [word_6366]
    pop     dx
    pop     bp
    sub     ax, bp
    cmp     ax, 32
    jns     loc_AEFA
    cmp     ax, 0FFE0h                 ; -32
    js      loc_AEFA

loc_AF6D:
    call    sub_AFE0
    jmp     loc_AFA3

loc_AF72:
    mov     bx, 4
    cmp     word [is_circular_track], 0
    jz      loc_AFA0
    push    dx
    mov     ax, [word_636E]
    add     ax, bx
    mov     bp, 0FFA0h                 ; -96
    imul    bp
    idiv    word [word_23F2]
    pop     dx
    sub     ax, [word_6366]
    cmp     ax, 32
    js      loc_AF98
    jmp     loc_AEFA

loc_AF98:
    cmp     ax, 0FFE0h
    jns     loc_AFA0
    jmp     loc_AEFA

loc_AFA0:
    call    sub_B005

loc_AFA3:
    cmp     word [is_circular_track], 0
    jz      loc_AFCE
    mov     ax, [word_636E]
    cmp     ax, [word_23F2]
    jnz     loc_AFB6
    jmp     loc_AEFA

loc_AFB6:
    jns     loc_AFBB
    jmp     loc_AEFA

loc_AFBB:
    mov     bx, [word_23F2]
    shl     bx, 4
    mov     al, [bx - 7E9Eh]
    neg     al
    mov     ah, 0
    mov     [word_249E], ax
    ret

loc_AFCE:
    cmp     word [word_636E], 1024
    jns     loc_AFD9
    jmp     loc_AEFA

loc_AFD9:
    mov     word [word_249E], 128
    ret


;
; AFE0:
;
; in:
; bx -
; cx -
; dx -
sub_AFE0:
    add     [word_636E], bx
    push    dx
    mov     ax, dx
    imul    cx
    mov     [word_636A], ax
    pop     dx
    mov     bp, [word_6366]

loc_AFF1:
    mov     [si], al
    xchg    ax, bp
    mov     [si + 12], al
    xchg    ax, bp
    add     bp, ax
    add     si, 16
    dec     bx
    jnz     loc_AFF1
    mov     [word_6366], bp
    ret


;
; B005:
;
; in:
; bx -
; si -
sub_B005:
    add     [word_636E], bx
    mov     ax, [word_636A]
    mov     bp, [word_6366]

loc_B010:
    and     ax, ax
    jz      loc_B01A
    jns     loc_B019
    inc     ax
    jmp     loc_B01A

loc_B019:
    dec     ax

loc_B01A:
    mov     [si], al
    xchg    ax, bp
    mov     [si + 12], al
    xchg    ax, bp
    add     bp, ax
    add     si, 16
    dec     bx
    jnz     loc_B010
    mov     [word_636A], ax
    mov     [word_6366], bp
    ret


;
; Add turn signs to the track (except for the Desert, Rally, Mountains)
;
prep_track_signs:
    mov     bx, [track_num]
    cmp     bl, 12
    jz      ret_B044
    cmp     bl, 9
    jz      ret_B044
    cmp     bl, 4
    jnz     loc_B045

ret_B044:
    ret

loc_B045:
    shl     bx, 2
    mov     cx, [bx + arr_24A2]
    mov     bx, [bx + arr_24A0]
    mov     ax, [word_2AB6]
    add     ax, 2
    shr     ax, 2
    add     ax, 2
    mov     cl, al
    xchg    cl, ch
    neg     al
    mov     bl, al
    xchg    bl, bh
    mov     si, tmp_file_buf
    mov     dx, 0
    mov     bp, 0

loc_B06F:
    mov     al, [si + 64]
    cmp     al, 6
    jz      loc_B08C
    cmp     al, 5
    jz      loc_B09F
    cmp     al, 4
    je      loc_B09F
    cmp     al, 0FAh
    jz      loc_B0AC
    cmp     al, 0FBh
    jz      loc_B0BF
    cmp     al, 0FCh
    jz      loc_B0BF
    jmp     loc_B0CA

loc_B08C:
    cmp     bp, 4
    jns     loc_B097
    mov     [si + 4], cx
    mov     [si + 8], cx

loc_B097:
    mov     [si + 2], cx
    mov     [si + 6], cx
    jmp     loc_B0CA

loc_B09F:
    cmp     bp, 4
    jns     loc_B0A7
    mov     [si + 6], cx

loc_B0A7:
    mov     [si + 2], cx
    jmp     loc_B0CA

loc_B0AC:
    cmp     bp, 4
    jns     loc_B0B7
    mov     [si + 4], bx
    mov     [si + 8], bx

loc_B0B7:
    mov     [si + 2], bx
    mov     [si + 6], bx
    jmp     loc_B0CA

loc_B0BF:
    cmp     bp, 4
    jns     loc_B0C7
    mov     [si + 6], bx

loc_B0C7:
    mov     [si + 2], bx

loc_B0CA:
    cmp     dl, ah
    jnz     loc_B0D1
    inc     bp
    jmp     loc_B0D6

loc_B0D1:
    mov     bp, 0
    mov     dh, al

loc_B0D6:
    cmp     word [word_63B2], 0
    jz      loc_B0EF
    cmp     al, 0
    jz      loc_B0EF
    jns     loc_B0EA
    mov     word [si + 8], 28D5h
    jmp     loc_B0EF

loc_B0EA:
    mov     word [si + 8], 0D8D2h

loc_B0EF:
    add     si, 16
    cmp     si, arr_C156
    jnb     ret_B0FB
    jmp     loc_B06F

ret_B0FB:
    ret


;
; B0FC:
;
sub_B0FC:
    cmp     word [word_63B4], 0
    jz      loc_B14A
    mov     si, tmp_file_buf
    mov     bl, 96h
    mov     cl, 0E2h

loc_B10A:
    mov     dl, bl
    call    smart_crc
    jns     loc_B113
    mov     dl, cl

loc_B113:
    mov     [si + 2], dl
    call    sub_AB9A
    and     al, 3
    add     al, 11h
    mov     [si + 3], al
    mov     word [si + 4], 0
    mov     dl, bl
    call    smart_crc
    jns     loc_B12E
    mov     dl, cl

loc_B12E:
    mov     [si + 6], dl
    call    smart_crc
    and     al, 3
    add     al, 17
    mov     [si + 7], al
    mov     word [si + 8], 0
    add     si, 16
    cmp     si, arr_C156
    jb      loc_B10A
    ret

loc_B14A:
    mov     ax, 0FFD0h
    imul    word [word_2450]
    mov     bp, 64h
    idiv    bp
    add     ax, 40h
    mov     [word_246E], ax
    mov     ax, 0FFA0h
    imul    word [word_2450]
    idiv    bp
    add     ax, 0E0h
    mov     [word_246A], ax
    mov     ax, 80h
    imul    word [word_244E]
    idiv    bp
    add     ax, 40h
    mov     [word_2468], ax
    mov     ax, 40h
    imul    word [word_244E]
    idiv    bp
    add     ax, 0A0h
    mov     [word_246C], ax
    mov     di, [track_num]
    shl     di, 4
    add     di, arr_24D4
    mov     si, tmp_file_buf

loc_B197:
    mov     cx, 1
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_246E]
    js      loc_B1A8
    jmp     loc_B2A1

loc_B1A8:
    call    smart_crc
    and     ax, 0Eh
    add     di, ax
    mov     bp, [di]
    sub     di, ax
    mov     cx, bp
    and     bp, 0FFFCh
    jz      loc_B1A8
    xchg    ax, [word_6354]
    mov     ah, 0
    cmp     ax, bp
    jnb     loc_B1A8
    and     bp, 0FF00h
    mov     [word_6362], bp
    mov     ax, bp
    shr     ax, 8
    call    sub_B67C
    mov     dx, bx
    call    smart_crc
    jns     loc_B1DE
    neg     dx

loc_B1DE:
    mov     [word_6362], dl
    mov     [word_636A], cx
    and     cx, 3
    jz      loc_B210
    cmp     cl, 1
    jz      loc_B1FC
    cmp     cl, 2
    jz      loc_B205
    mov     byte [word_6362], 0
    jmp     loc_B210

loc_B1FC:
    cmp     byte [word_6362], 0
    js      loc_B210
    jmp     loc_B20C

loc_B205:
    cmp     byte [word_6362], 0
    jns     loc_B210

loc_B20C:
    neg     byte [word_6362]

loc_B210:
    mov     cx, 4

loc_B213:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_246A]
    jns     loc_B226
    add     cx, 2
    cmp     cx, 0Ch
    jnz     loc_B213

loc_B226:
    mov     dx, 4

loc_B229:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2468]
    jns     loc_B23B
    shr     dx, 1
    cmp     dx, 1
    jnz     loc_B229

loc_B23B:
    and     word [word_636A], 8
    jz      loc_B249
    cmp     dx, 1
    jnz     loc_B249
    shl     dx, 1

loc_B249:
    inc     cx

loc_B24A:
    mov     al, [word_6362 + 1]
    call    sub_B7CD
    jb      loc_B2A1
    cmp     word [si + 2], 0
    jnz     loc_B2A1
    mov     bp, [word_6362]
    ror     bp, 8
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_246C]
    jnb     loc_B26D
    mov     [si + 2], bp

loc_B26D:
    cmp     dx, 4
    jz      loc_B2A1
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_246C]
    jnb     loc_B280
    mov     [si + 6], bp

loc_B280:
    cmp     dx, 2
    jz      loc_B2A1
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_246C]
    jnb     loc_B293
    mov     [si + 8], bp

loc_B293:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_246C]
    jnb     loc_B2A1
    mov     [si + 4], bp

loc_B2A1:
    add     si, 16
    loop    loc_B24A
    cmp     si, arr_C156
    jnb     ret_B2AF
    jmp     loc_B197

ret_B2AF:
    ret


;
; B2B0:
;
sub_B2B0:
    mov     bp, 64h
    mov     si, arr_8256
    cmp     word [word_63AC], 0
    jz      loc_B2C0
    jmp     loc_B470

loc_B2C0:
    cmp     word [word_639C], 0
    jnz     loc_B2ED
    cmp     word [word_63AE], 0
    jnz     loc_B33D
    cmp     word [word_63A6], 0
    jz      loc_B2D8
    jmp     loc_B36F

loc_B2D8:
    cmp     word [word_63A8], 0
    jz      loc_B2E2
    jmp     loc_B3AE

loc_B2E2:
    cmp     word [word_63B2], 0
    jz      ret_B2EC
    jmp     loc_B538

ret_B2EC:
    ret

loc_B2ED:
    mov     ax, 16
    imul    word [word_2452]
    idiv    bp
    add     ax, 0
    mov     [word_2472], ax

loc_B2FC:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2472]
    jns     loc_B333
    call    smart_crc
    and     ax, 18h
    sub     ax, 0Ch
    cmp     byte [si + 45], 0
    jnz     loc_B333
    cmp     byte [si], 0
    jnz     loc_B333
    cmp     word [si + 42], 0
    jnz     loc_B333
    cmp     byte [si + 4], 0
    jnz     loc_B333
    mov     byte [si + 4], 95h
    mov     [si + 5], al
    mov     word [si + 42], 100h

loc_B333:
    add     si, 16
    cmp     si, arr_C156
    jb      loc_B2FC
    ret

loc_B33D:
    mov     ax, 24
    imul    word [word_2452]
    idiv    bp
    add     ax, 8
    mov     [word_2474], ax

loc_B34C:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2474]
    jns     loc_B365
    call    smart_crc
    cmp     byte [si + 13], 0
    jnz     loc_B365
    mov     word [si + 10], 1000h

loc_B365:
    add     si, 16
    cmp     si, arr_C156
    jb      loc_B34C
    ret

loc_B36F:
    mov     ax, 16
    imul    word [word_2452]
    idiv    bp
    add     ax, 0
    mov     [word_2470], ax

loc_B37E:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2470]
    jns     loc_B3A4
    call    smart_crc
    cmp     word [si + 10], 0
    jnz     loc_B3A4
    cmp     byte [si + 4], 0
    jnz     loc_B3A4
    mov     byte [si + 4], 0A0h
    mov     [si + 5], al
    mov     word [si + 10], 2022h

loc_B3A4:
    add     si, 16
    cmp     si, arr_C156
    jb      loc_B37E
    ret

loc_B3AE:
    mov     word [word_247E], 8
    mov     ax, 0FF80h
    imul    word [word_2450]
    idiv    bp
    add     ax, 0E0h
    mov     [word_2480], ax

loc_B3C3:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_247E]
    jns     loc_B413
    mov     cx, 16

loc_B3D1:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2480]
    jns     loc_B3E4
    add     cx, 8
    cmp     cx, 64
    jne     loc_B3D1

loc_B3E4:
    inc     cx

loc_B3E5:
    cmp     byte [si + 13], 0
    jne     loc_B40F
    mov     word [si + 2], 0
    mov     word [si + 4], 0
    mov     word [si + 6], 0
    mov     word [si + 8], 0
    mov     word [si + 10], 2222h
    add     si, 16
    cmp     si, arr_C156
    je      loc_B41C
    loop    loc_B3E5

loc_B40F:
    add     si, 100h

loc_B413:
    add     si, 16
    cmp     si, arr_C156
    jb      loc_B3C3

loc_B41C:
    mov     ax, 16
    imul    word [word_2452]
    mov     bp, 64h
    idiv    bp
    add     ax, 0
    mov     [word_2472], ax
    mov     si, arr_8256

loc_B431:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2472]
    jns     loc_B466
    call    smart_crc
    and     al, 18h
    sub     al, 0Ch
    cmp     byte [si + 45], 0
    jnz     loc_B466
    cmp     byte [si], 0
    jnz     loc_B466
    cmp     word [si + 42], 0
    jnz     loc_B466
    cmp     byte [si + 4], 0
    jnz     loc_B466
    mov     byte [si + 4], 0CEh
    mov     [si + 5], al
    mov     word [si + 42], 100h

loc_B466:
    add     si, 16
    cmp     si, arr_C156
    jb      loc_B431
    ret

loc_B470:
    mov     ax, 0FFD0h
    imul    word [word_2452]
    idiv    bp
    add     ax, 40h
    mov     [word_2478], ax
    mov     ax, 0FFA0h
    imul    word [word_2450]
    idiv    bp
    add     ax, 0E0h
    mov     [word_2476], ax

loc_B48E:
    mov     cx, 1
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2478]
    jns     loc_B512
    mov     dx, 0FFF0h
    call    smart_crc
    jns     loc_B4A6
    neg     dx

loc_B4A6:
    mov     [word_6362], dx
    call    smart_crc
    and     ax, 0Fh
    add     ax, 0F8h
    mov     [word_6366], ax
    mov     cx, 4

loc_B4B9:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2476]
    jns     loc_B4CC
    add     cx, 2
    cmp     cx, 0Ch
    jnz     loc_B4B9

loc_B4CC:
    inc     cx

loc_B4CD:
    mov     al, 0D1h
    mov     ah, [word_6362]
    mov     [si + 2], ax
    call    sub_B521
    mov     bl, 0D4h
    call    smart_crc
    cmp     ax, 4000h
    jae     loc_B4E5
    mov     bl, 0D3h

loc_B4E5:
    mov     [si + 4], bl
    mov     al, [word_6362]
    and     dx, dx
    jns     loc_B4F3
    sub     al, 8
    jmp     loc_B4F5

loc_B4F3:
    add     al, 8

loc_B4F5:
    mov     [si + 5], al
    call    sub_B521
    mov     al, 0D1h
    mov     ah, [word_6362]
    mov     [si + 6], ax
    call    sub_B521
    mov     al, 0D8h
    and     dx, dx
    jns     loc_B50F
    mov     al, 0F6h

loc_B50F:
    mov     [si + 8], ax

loc_B512:
    add     si, 16
    loop    loc_B4CD
    cmp     si, arr_C156
    jnb     ret_B520
    jmp     loc_B48E

ret_B520:
    ret


;
; B521:
;
sub_B521:
    push    ax
    mov     al, [word_6362]
    cmp     al, [word_6366]
    pop     ax
    jz      ret_B537
    jns     loc_B533
    inc     byte [word_6362]
    ret

loc_B533:
    dec     byte [word_6362]

ret_B537:
    ret


;
; B538:
;
loc_B538:
    mov     word [word_247A], 4
    mov     ax, 0FF80h
    imul    word [word_2450]
    idiv    bp
    add     ax, 0E0h
    mov     [word_247C], ax

loc_B54D:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_247A]
    jns     loc_B597
    mov     cx, 16

loc_B55B:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_247C]
    jns     loc_B56E
    add     cx, 8
    cmp     cx, 64
    jne     loc_B55B

loc_B56E:
    inc     cx

loc_B56F:
    mov     word [si + 2], 0E0DEh
    mov     word [si + 4], 20DEh
    mov     word [si + 6], 0E0DEh
    mov     word [si + 8], 20DEh
    mov     word [si + 10], 2222h
    add     si, 16
    cmp     si, arr_C156
    je      ret_B5A0
    loop    loc_B56F
    add     si, 256

loc_B597:
    add     si, 16
    cmp     si, arr_C156
    jb      loc_B54D

ret_B5A0:
    ret


;
; B5A1: Add laser beams to the Futuristic track
;
sub_B5A1:
    mov     ax, 16
    mul     word [word_2452]
    mov     bp, 100
    div     bp
    add     ax, 0
    mov     [word_248C], ax
    mov     di, [track_num]
    shl     di, 4
    add     di, arr_25A4
    mov     si, arr_8256

loc_B5C1:
    lea     ax, [si + 2]
    mov     [word_6376], ax
    mov     word [word_636A], 4

loc_B5CD:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_248C]
    jb      loc_B5DB
    jmp     loc_B661

loc_B5DB:
    call    smart_crc
    and     ax, 0Eh
    mov     bx, ax
    mov     cx, [bx + di]
    mov     [word_6362], cx
    and     word [word_6362], 0FFFCh
    jz      loc_B5DB
    mov     al, [word_6362]
    cmp     [word_6354], al
    jnb     loc_B5DB
    mov     byte [word_6362], 0
    mov     ax, [word_6362]
    shr     ax, 8
    call    sub_B69D

loc_B607:
    call    smart_crc
    and     ax, 3
    jz      loc_B607
    dec     ax
    mov     dx, bx
    sub     dx, ax
    call    smart_crc
    jns     loc_B61B
    neg     dx

loc_B61B:
    mov     [word_6362], dl
    and     cl, 3
    jz      loc_B649
    cmp     cl, 1
    jz      loc_B635
    cmp     cl, 2
    jz      loc_B63E
    mov     byte [word_6362], 0
    jmp     loc_B649

loc_B635:
    cmp     byte [word_6362], 0
    js      loc_B649
    jmp     loc_B645

loc_B63E:
    cmp     byte [word_6362], 0
    jns     loc_B649

loc_B645:
    neg     byte [word_6362]

loc_B649:
    mov     al, [word_6362 + 1]
    call    sub_B7CD
    jb      loc_B661
    mov     bx, [word_6376]
    cmp     word [bx], 0
    jnz     loc_B661
    mov     ax, [word_6362]
    xchg    al, ah
    mov     [bx], ax

loc_B661:
    add     word [word_6376], 2
    dec     word [word_636A]
    jz      loc_B66F
    jmp     loc_B5CD

loc_B66F:
    add     si, 16
    cmp     si, arr_C156
    jnb     ret_B67B
    jmp     loc_B5C1

ret_B67B:
    ret


;
; B67C:
;
sub_B67C:
    sub     ax, 128
    shl     ax, 2
    mov     bx, ax
    mov     al, [bx + arr_2674]
    mov     ah, 0
    add     ax, 0Fh
    shr     ax, 4
    mov     bx, [word_2AB6]
    add     bx, 2
    shr     bx, 2
    add     bx, ax
    ret


;
; B69D:
;
sub_B69D:
    sub      ax, 128
    shl      ax, 2
    mov      bx, ax
    mov      al, [bx + arr_2674]
    mov      ah, 0
    add      ax, 0Fh
    shr      ax, 4
    mov      bx, [word_2AB6]
    add      bx, 2
    shr      bx, 2
    sub      bx, ax
    ret


;
; B6BE: Add trees, rocks, bushes on a sides of a road
;
sub_B6BE:
    mov     ax, 0B0h
    mul     word [word_244E]
    mov     bp, 100
    div     bp
    add     ax, 16
    mov     [word_2488], ax
    mov     ax, 38h
    mul     word [word_2450]
    div     bp
    add     ax, 40h
    mov     [word_248A], ax
    mov     di, [track_num]
    shl     di, 4
    add     di, arr_2874
    mov     si, tmp_file_buf

loc_B6ED:
    lea     ax, [si + 2]
    mov     [word_6376], ax
    mov     word [word_636A], 4

loc_B6F9:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2488]
    jb      loc_B707
    jmp     loc_B7B2

loc_B707:
    call    smart_crc
    and     ax, 0Eh
    mov     bx, ax
    mov     cx, [bx + di]
    mov     [word_6362], cx
    and     word [word_6362], 0FFFCh
    jz      loc_B707
    mov     al, [word_6362]
    cmp     [word_6354], al
    jnb     loc_B707
    mov     byte [word_6362], 0
    mov     ax, [word_6362]
    shr     ax, 8
    call    sub_B67C
    push    cx
    mov     cx, [word_248A]
    sub     cx, bx
    call    smart_crc
    mov     ah, al
    mul     ah
    mul     cx
    add     dx, bx
    call    smart_crc
    jns     loc_B74C
    neg     dx

loc_B74C:
    mov     [word_6362], dl
    pop     cx
    and     cl, 3
    jz      loc_B77B
    cmp     cl, 1
    jz      loc_B767
    cmp     cl, 2
    jz      loc_B770
    mov     byte [word_6362], 0
    jmp     loc_B77B

loc_B767:
    cmp     byte [word_6362], 0
    js      loc_B77B
    jmp     loc_B777

loc_B770:
    cmp     byte [word_6362], 0
    jns     loc_B77B

loc_B777:
    neg     byte [word_6362]

loc_B77B:
    mov     al, [word_6362 + 1]
    call    sub_B7CD
    jb      loc_B7B2
    cmp     word [word_63A8], 0
    jz      loc_B7A2
    cmp     al, 0CAh
    jz      loc_B792
    cmp     al, 0CBh
    jnz     loc_B79B

loc_B792:
    cmp     word [si + 10], 2222h
    jnz     loc_B7B2
    jmp     loc_B7A2

loc_B79B:
    cmp     word [si + 10], 2222h
    jz      loc_B7B2

loc_B7A2:
    mov     bx, [word_6376]
    cmp     word [bx], 0
    jnz     loc_B7B2
    mov     ax, [word_6362]
    xchg    al, ah
    mov     [bx], ax

loc_B7B2:
    add     word [word_6376], 2
    dec     word [word_636A]
    jz      loc_B7C0
    jmp     loc_B6F9

loc_B7C0:
    add     si, 16
    cmp     si, arr_C156
    jnb     ret_B7CC
    jmp     loc_B6ED

ret_B7CC:
    ret


;
; B7CD:
;
sub_B7CD:
    cmp     al, 0B0h
    jz      loc_B7E7
    cmp     al, 0ECh
    jz      loc_B7E7
    cmp     al, 0EBh
    jz      loc_B7E7
    cmp     al, 0A9h
    jz      loc_B7E7
    cmp     al, 0CDh
    jz      loc_B7E7
    cmp     al, 97h
    jz      loc_B7E7
    clc
    ret

loc_B7E7:
    cmp     byte [si + 1], 0
    jnz     loc_B7FB
    cmp     byte [si - 0Fh], 0
    jnz     loc_B7FB
    cmp     byte [si + 11h], 0
    jnz     loc_B7FB
    clc
    ret

loc_B7FB:
    stc
    ret


;
; B7FD:
;
sub_B7FD:
    call    sub_B803
    jmp     loc_B97F


sub_B803:
    cmp     word [word_3EE4], 0
    jz      loc_B80D
    jmp     loc_B913

loc_B80D:
    cmp     word [is_circular_track], 0
    jz      loc_B817
    jmp     loc_B8A3

loc_B817:
    call    sub_BA67
    mov     si, arr_2400
    mov     di, word_2422
    mov     bp, 0

loc_B823:
    mov     ax, [si + 2]
    sub     ax, [si]
    mov     cx, 0C13h
    mul     cx
    mov     cx, 0E1h
    div     cx
    cwd
    div     bx
    add     ax, [num_of_tracks]
    add     ax, [num_of_tracks]
    sub     ax, bp
    sub     ax, bp
    sub     ax, bp
    sub     ax, bp
    cmp     si, arr_2400
    jne     loc_B84E
    add     ax, 7

loc_B84E:
    inc     ax
    cmp     ax, 5
    jns     loc_B857
    mov     ax, 5

loc_B857:
    cmp     ax, 63h
    js      loc_B85F
    mov     ax, 63h

loc_B85F:
    add     si, 2
    mov     [di], ax
    add     di, 2
    inc     bp
    cmp     bp, [num_of_tracks]
    jne     loc_B823
    mov     si, arr_2400
    lodsw
    shl     ax, 4
    mov     di, tmp_file_buf
    add     di, ax
    mov     word [di + 2], 88h
    mov     word [di + 10], 30h
    mov     cx, [num_of_tracks]

loc_B888:
    lodsw
    shl     ax, 4
    mov     di, tmp_file_buf
    add     di, ax
    mov     word [di + 2], 8Ah
    mov     word [di + 10], 30h
    loop    loc_B888
    mov     word [di + 2], 89h
    ret

loc_B8A3:
    mov     si, tmp_file_buf
    mov     word [si + 2], 8Ah
    mov     word [si + 10], 30h
    mov     bx, [word_23F2]
    shl     bx, 4
    mov     word [bx + si + 2], 8Ah
    mov     word [bx + si + 10], 30h
    call    sub_BA67
    mov     ax, 0C13h
    mul     word [word_23F2]
    mov     cx, 0E1h
    div     cx
    cwd
    div     bx
    mov     bp, 0
    mov     di, word_2422

loc_B8D9:
    mov     cx, [num_of_tracks]
    sub     cx, bp
    sub     cx, bp
    shl     cx, 1
    add     cx, ax
    mov     dx, bp
    shr     dx, 2
    adc     cx, dx
    cmp     bp, 0
    jnz     loc_B8F4
    add     cx, 7

loc_B8F4:
    cmp     cx, 5
    jns     loc_B8FC
    mov     cx, 5

loc_B8FC:
    cmp     cx, 63h
    js      loc_B904
    mov     cx, 63h

loc_B904:
    mov     [di], cx
    add     di, 2
    inc     bp
    cmp     bp, [num_of_tracks]
    jnz     loc_B8D9
    jmp     sub_B9DD

loc_B913:
    cmp     word [is_circular_track], 0
    jnz     loc_B95C
    mov     si, arr_2400
    lodsw
    shl     ax, 4
    mov     di, tmp_file_buf
    add     di, ax
    mov     word [di + 2], 88h
    mov     word [di + 10], 30h
    call    sub_B9F8
    mov     cx, [num_of_tracks]

loc_B937:
    lodsw
    shl     ax, 4
    mov     di, tmp_file_buf
    add     di, ax
    mov     word [di + 2], 8Ah
    mov     word [di + 10], 30h
    call    sub_B9F8
    loop    loc_B937
    mov     word [di + 2], 89h
    mov     word [di + 10], 30h
    jmp     sub_BA67

loc_B95C:
    mov     di, tmp_file_buf
    call    sub_B9F8
    mov     word [di + 2], 8Ah
    mov     word [di + 10], 30h
    mov     ax, [word_23F2]
    shl     ax, 4
    add     di, ax
    mov     word [di + 2], 8Ah
    call    sub_B9DD
    jmp     sub_BA67


loc_B97F:
    cmp     word [word_63B2], 0
    jz      ret_B9DC
    cmp     word [is_circular_track], 0
    jnz     loc_B9B1
    mov     si, arr_2400
    mov     bp, [num_of_tracks]

loc_B994:
    lodsw
    sub     ax, 8
    shl     ax, 4
    mov     di, tmp_file_buf
    add     di, ax
    mov     cx, 16

loc_B9A3:
    mov     word [di + 10], 3333h
    add     di, 16
    loop    loc_B9A3
    dec     bp
    jns     loc_B994
    ret

loc_B9B1:
    mov     di, tmp_file_buf
    mov     cx, 8

loc_B9B7:
    mov     word [di + 10], 3333h
    add     di, 16
    loop    loc_B9B7
    mov     ax, [word_23F2]
    sub     ax, 8
    shl     ax, 4
    mov     di, tmp_file_buf
    add     di, ax
    mov     cx, 8

loc_B9D2:
    mov     word [di + 10], 3333h
    add     di, 16
    loop    loc_B9D2

ret_B9DC:
    ret


;
; B9DD:
;
sub_B9DD:
    mov     si, arr_2400
    mov     ax, 0
    mov     cx, [num_of_tracks]
    inc     cx

loc_B9E8:
    add     ax, [word_23F2]
    mov     [si], ax
    add     si, 2
    loop    loc_B9E8
    mov     word [si], 0FFFFh
    ret


;
; B9F8:
;
sub_B9F8:
    push    cx
    push    di
    mov     bx, [track_num]
    shl     bx, 1
    mov     bx, [bx + arr13_2944]
    mov     ax, [word_2AB6]
    add     ax, 2
    shr     ax, 2
    add     ax, 2
    mov     bl, al
    xchg    bl, bh
    mov     cx, 8

loc_BA17:
    cmp     word [word_63B4], 0
    jnz     loc_BA24
    mov     [di + 4], bx
    mov     [di + 8], bx

loc_BA24:
    add     di, 16
    loop    loc_BA17
    mov     cx, 8

loc_BA2C:
    add     di, 2
    call    sub_BA51
    add     di, 2
    call    sub_BA51
    add     di, 2
    call    sub_BA51
    add     di, 2
    call    sub_BA51
    mov     word [di + 2], 800h
    add     di, 8
    loop    loc_BA2C
    pop     di
    pop     cx
    ret


;
; BA51:
;
sub_BA51:
    cmp     byte [di+1], 0
    jle     ret_BA66
    add     byte [di+1], 6
    cmp     word [word_63AC], 0
    jz      ret_BA66
    mov     word [di], 0

ret_BA66:
    ret


;
; BA67:
;
sub_BA67:
    mov     ax, 26
    mul     word [car_num]
    add     ax, [track_num]
    shl     ax, 1
    mov     bx, arr_295E
    add     bx, ax
    mov     cx, [bx + 26]              ; arr_295E[car_num * 26 + track_num + 13]
    mov     bx, [bx]                   ; arr_295E[car_num * 26 + track_num]
    sub     cx, bx
    mov     ax, cx
    mul     word [word_244C]
    mov     bp, 99
    div     bp
    add     bx, ax
    push    bx
    mov     ax, 5091
    mul     bx
    mov     bp, 192
    div     bp
    mov     bx, ax
    mov     cx, [word_23F2]
    mov     dx, cx
    add     dx, 128
    cmp     word [is_circular_track], 0
    je      loc_BAB8
    mov     ax, [num_of_tracks]
    mul     cx
    mov     cx, ax
    mov     dx, ax
    add     dx, [word_23F2]

loc_BAB8:
    xchg    cx, dx
    mov     ax, bx
    mul     dx
    div     cx
    mov     [word_23F8], ax
    mov     [word_23FA], ax
    pop     ax
    mov     bp, 1000
    mul     bp
    mov     bp, 3600
    div     bp
    mov     bx, ax
    ret


;
; BAD4: Add tunnels to the Night, MotorWay and Futuristic tracks
;
sub_BAD4:
    mov     ax, [track_num]
    cmp     al, 1
    jz      loc_BAE4
    cmp     al, 5
    jz      loc_BB18
    cmp     al, 11
    jz      loc_BAFE
    ret

loc_BAE4:
    mov     word [word_635E], 0
    mov     word [word_6360], 82EEh
    mov     word [word_6362], 9111h
    mov     word [word_6364], 8212h
    jmp     loc_BB30

loc_BAFE:
    mov     word [word_635E], 8200h
    mov     word [word_6360], 82E2h
    mov     word [word_6362], 9111h
    mov     word [word_6364], 821Eh
    jmp     loc_BB30

loc_BB18:
    mov     word [word_635E], 8200h
    mov     word [word_6360], 82E8h
    mov     word [word_6362], 9111h
    mov     word [word_6364], 8218h

loc_BB30:
    mov     ax, 20h
    imul    word [word_244E]
    mov     bp, 64h
    idiv    bp
    add     ax, 0
    mov     [word_2482], ax
    mov     ax, 60h
    imul    word [word_244E]
    idiv    bp
    add     ax, 80h
    mov     [word_2484], ax
    mov     si, arr_8256

loc_BB54:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2482]
    js      loc_BB62
    jmp     loc_BC4B

loc_BB62:
    mov     cx, 4

loc_BB65:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2484]
    jns     loc_BB78
    add     cx, 2
    cmp     cx, 16
    jnz     loc_BB65

loc_BB78:
    mov     word [word_636A], 4
    mov     bx, 0

loc_BB81:
    cmp     byte [si], 0
    jz      loc_BB90
    jns     loc_BB8D
    or      bl, 1
    jmp     loc_BB90

loc_BB8D:
    or      bl, 2

loc_BB90:
    cmp     byte [si + 1], 0
    jz      loc_BB99
    or      bl, 4

loc_BB99:
    cmp     byte [si + 2], 8Ah
    jnz     loc_BBA2
    jmp     loc_BC4B

loc_BBA2:
    cmp     byte [si + 2], 89h
    jnz     loc_BBAB
    jmp     loc_BC4B

loc_BBAB:
    add     si, 16
    dec     word [word_636A]
    jnz     loc_BB81
    sub     si, 40h
    cmp     bl, 2
    jbe     loc_BBC4
    cmp     bl, 4
    jz      loc_BBC4
    jmp     loc_BC4B

loc_BBC4:
    mov     word [si + 2], 0FCh
    mov     bx, 0
    lea     di, [si + 2]
    jmp     loc_BBD6

loc_BBD1:
    mov     word [si + 2], 0

loc_BBD6:
    mov     ax, [word_6360]
    xchg    al, ah
    mov     [si + 4], ax
    mov     ax, [word_635E]
    xchg    al, ah
    mov     [si + 6], ax
    mov     ax, [word_6364]
    xchg    al, ah
    mov     [si + 8], ax
    mov     ax, [word_6362]
    xchg    al, ah
    mov     [si + 10], ax
    cmp     byte [si + 34], 8Ah
    je      loc_BC38
    cmp     byte [si + 34], 89h
    je      loc_BC38
    cmp     byte [si + 1], 0
    je      loc_BC14
    cmp     bl, 0
    jz      loc_BC12
    cmp     bl, 2
    jnz     loc_BC38

loc_BC12:
    mov     bl, 2

loc_BC14:
    cmp     byte [si], 0
    jns     loc_BC25
    cmp     bl, 0
    je      loc_BC23
    cmp     bl, 0FFh
    jne     loc_BC38

loc_BC23:
    mov     bl, 0FFh

loc_BC25:
    cmp     byte [si], 0
    jle     loc_BC36
    cmp     bl, 0
    jz      loc_BC34
    cmp     bl, 1
    jnz     loc_BC38

loc_BC34:
    mov     bl, 1

loc_BC36:
    jmp     loc_BC3B

loc_BC38:
    mov     cx, 1

loc_BC3B:
    add     si, 16
    loop    loc_BBD1
    mov     word [si + 2], 0FDh
    mov     [di + 1], bl
    add     si, 16

loc_BC4B:
    add     si, 16
    cmp     si, arr_C156
    jnb     ret_BC57
    jmp     loc_BB54

ret_BC57:
    ret


;
; BC58: Add bridges to the MotorWay and Roadworks tracks
;
prep_track_bridges:
    mov     ax, [track_num]
    cmp     al, 5
    je      loc_BC64
    cmp     al, 8
    je      loc_BC64
    ret

loc_BC64:
    mov     ax, 16
    imul    word [word_244E]
    mov     bp, 100
    idiv    bp
    add     ax, 0
    mov     [word_2486], ax
    mov     si, arr_8256

loc_BC79:
    call    smart_crc
    mov     ah, 0
    cmp     ax, [word_2486]
    jns     advance
    cmp     byte [si + 2], 138
    jz      extra_add
    cmp     byte [si + 18], 138
    jz      extra_add
    cmp     byte [si + 2], 137
    jz      extra_add
    cmp     byte [si + 18], 137
    jz      extra_add
    cmp     byte [si + 10], 0
    js      advance
    cmp     byte [si + 26], 0
    js      advance
    cmp     byte [si - 6], 0
    js      advance
    mov     word [si + 2], 250
    mov     word [si + 4], 251
    mov     word [si + 10], 16

extra_add:                             ; BCBD
    add     si, 16

advance:                               ; BCC0
    add     si, 16
    cmp     si, arr_C156
    jb      loc_BC79
    ret


;
; BCCA:
;
sub_BCCA:
    call    sub_BCCF
    jmp     loc_BCFE


;
; BCCF:
;
sub_BCCF:
    mov     si, tmp_file_buf
    mov     ax, 0
    mov     dx, 0
    mov     cx, 1024

loc_BCDB:
    mov     [si + 12], ax
    add     al, [si]
    add     ah, [si + 1]
    cmp     byte [si + 2], 0FCh
    jnz     loc_BCEC
    mov     dx, 8000h

loc_BCEC:
    cmp     byte [si + 2], 0FDh
    jnz     loc_BCF5
    mov     dx, 0

loc_BCF5:
    or      [si + 10], dx
    add     si, 16
    loop    loc_BCDB
    ret


loc_BCFE:
    mov     si, tmp_file_buf

loc_BD01:
    mov     dx, [word_634E]
    mov     cx, dx
    neg     cx
    cmp     word [word_63A6], 0
    je      loc_BD13
    mov     cx, 2

loc_BD13:
    mov     bx, 6

loc_BD16:
    mov     al, [bx + si + 2]
    cmp     al, 0
    jz      loc_BD6A
    cmp     al, 88h
    jz      loc_BD6A
    cmp     al, 89h
    jz      loc_BD6A
    cmp     al, 8Ah
    jz      loc_BD6A
    cmp     al, 97h
    jz      loc_BD6A
    cmp     al, 0EBh
    jz      loc_BD6A
    cmp     al, 82h
    jz      loc_BD6A
    cmp     al, 0B8h
    jz      loc_BD6A
    cmp     al, 0DAh
    jz      loc_BD6A
    cmp     al, 0FCh
    jz      loc_BD6A
    cmp     al, 0FDh
    jz      loc_BD6A
    cmp     al, 0A9h
    jz      loc_BD6A
    cmp     al, 0B0h
    jz      loc_BD6A
    cmp     al, 0A0h
    jz      loc_BD6A
    cmp     al, 0CDh
    jz      loc_BD6A
    mov     al, [bx + si + 3]
    cmp     al, 0
    jg      loc_BD64
    cmp     al, cl
    jnb     loc_BD6A
    mov     cl, al
    jmp     loc_BD6A

loc_BD64:
    cmp     al, dl
    jnb     loc_BD6A
    mov     dl, al

loc_BD6A:
    sub     bl, 2
    jns     loc_BD16
    add     cl, 8
    sub     dl, 8
    mov     [si + 14], cl
    mov     [si + 15], dl
    add     si, 16
    cmp     si, arr_C156
    jnb     loc_BD87
    jmp     loc_BD01

loc_BD87:
    mov     si, 0C146h
    mov     cl, 0F6h
    mov     dl, 0Ah

loc_BD8E:
    mov     al, [si + 14]
    cmp     al, cl
    jz      loc_BD9D
    jns     loc_BD9B
    dec     cl
    jmp     loc_BD9D

loc_BD9B:
    mov     cl, al

loc_BD9D:
    mov     [si + 14], cl
    mov     al, [si + 15]
    cmp     al, dl
    jz      loc_BDAF
    js      loc_BDAD
    inc     dl
    jmp     loc_BDAF

loc_BDAD:
    mov     dl, al

loc_BDAF:
    mov     [si + 15], dl
    sub     si, 16
    cmp     si, tmp_file_buf
    jnb     loc_BD8E
    ret


;
; BDBC:
;
sub_BDBC:
    cmp     word [is_2pl_mode], 0
    jne     loc_BDC4
    ret

loc_BDC4:
    mov     si, tmp_file_buf
    mov     cx, [word_634E]
    mov     dx, cx
    neg     dx
    inc     cx

loc_BDD0:
    mov     bp, 0
    mov     ax, [si + 2]
    call    sub_BE01
    mov     [si + 2], ax
    mov     ax, [si + 4]
    call    sub_BE01
    mov     [si + 4], ax
    mov     ax, [si + 6]
    call    sub_BE01
    mov     [si + 6], ax
    mov     ax, [si + 8]
    call    sub_BE01
    mov     [si + 8], ax
    add     si, 16
    cmp     si, arr_C156
    jb      loc_BDD0
    ret


;
; BE01:
;
sub_BE01:
    cmp     al, 0
    je      ret_BE51
    cmp     al, 80h
    je      loc_BE4E
    cmp     al, 70h
    je      loc_BE4E
    cmp     al, 82h
    je      loc_BE4E
    cmp     al, 0A0h
    je      loc_BE4E
    cmp     al, 0DAh
    je      loc_BE4E
    cmp     al, 0B8h
    je      loc_BE4E
    cmp     al, 0A5h
    je      loc_BE4E
    cmp     al, 71h
    je      loc_BE4E
    cmp     al, 0BDh
    je      loc_BE4E

loc_BE29:
    cmp     al, 74h
    je      loc_BE4E
    cmp     al, 0DBh
    je      loc_BE4E
    cmp     al, 0DCh
    je      loc_BE4E
    mov     bl, ah
    mov     bh, ah
    shl     bh, 1
    sbb     bh, bh
    cmp     bx, dx
    js      loc_BE45
    cmp     bx, cx
    js      loc_BE4E

loc_BE45:
    cmp     bp, 0
    je      loc_BE4E
    mov     ax, 0
    ret

loc_BE4E:
    mov     bp, 1

ret_BE51:
    ret


;
; BE52:
;
sub_BE52:
    mov     ax, [cs:word_5166]
    mov     [word_63BA], ax
    push    ds
    pop     es
    mov     di, word_6392
    mov     cx, playing_demo
    sub     cx, di

loc_BE63:
    mov     al, 0
    rep stosb
    mov     bx, [track_num]
    shl     bx, 1
    mov     word [bx + word_639C], 1
    mov     si, [bx + arr_29FA]

loc_BE77:
    lodsw
    and     ax, ax
    jz      loc_BE84
    mov     di, ax
    mov     word [di], 1
    jmp     loc_BE77

loc_BE84:
    mov     si, arr_2A4C
    mov     ax, 6
    mul     word [car_num]
    add     si, ax
    lodsw
    mov     [word_2A5E], ax
    lodsw
    mov     [word_2A60], ax
    lodsw
    mov     [word_2A62], ax
    mov     word [word_6348], 1
    mov     word [word_634A], 6
    mov     word [word_634C], 3
    mov     bx, [track_num]
    shl     bx, 1
    mov     ax, [bx + arr13_2A64]
    mov     [word_2AB2], ax
    mov     ax, [bx + arr13_4A46]

loc_BEBF:
    mov     [word_2AB6], ax
    add     ax, [bx + arr_2A98]
    mov     [word_2AB8], ax
    mov     si, arr_2ABA
    cmp     word [word_63AE], 0
    jnz     loc_BEF4
    mov     si, arr_2AD2
    cmp     word [word_63AA], 0
    jnz     loc_BEF4
    mov     si, arr_2ACA
    cmp     word [word_63A4], 0
    jnz     loc_BEF4
    mov     si, arr_2AC2
    cmp     word [word_63A2], 0
    jnz     loc_BEF4
    mov     si, arr_2ADA

loc_BEF4:
    lodsw
    mov     [word_2AE2], ax
    lodsw
    mov     [word_2AE4], ax
    lodsw
    mov     [word_2AE6], ax
    lodsw
    mov     [word_2AE8], ax
    mov     ax, [word_2AB6]
    shr     ax, 2
    add     ax, 2
    mov     [word_634E], ax
    mov     bx, [track_num]
    mov     al, 64
    mul     byte [bx + arr_2AEA]
    add     ax, 54D0h

loc_BF1D:
    mov     [word_54CE], ax
    mov     ax, 64
    mul     word [track_num]
    add     ax, 43A8h
    mov     [word_43A6], ax
    mov     bx, [track_num]
    shl     bx, 1
    mov     ax, [bx + arr13_4A2C]
    mov     [word_4A2A], ax
    mov     ax, 64
    mul     word [track_num]
    add     ax, 46EAh
    mov     [word_46E8], ax
    mov     ax, 40
    mul     word [track_num]
    add     ax, 4E7Ah
    mov     [word_4E78], ax
    mov     ax, 24
    mul     word [track_num]
    add     ax, arr_6042
    mov     [word_6040], ax
    call    sub_C939
    call    fade_out
    cmp     word [playing_demo], 0
    jnz     loc_BF71
    call    sub_4995

loc_BF71:
    mov     word [word_3E18], 0
    call    sub_C0AA
    call    sub_C0DF
    call    sub_C4F7
    call    sub_C42C
    call    prep_cars_and_pals
    call    prep_sndblaster_efx
    push    ss
    pop     es
    mov     di, 0
    mov     ax, di
    mov     cx, 1536
    rep stosw
    call    prep_track
    call    sub_BCCA
    call    sub_BDBC
    call    sub_CC17
    call    sub_C95F
    cmp     word [playing_demo], 0
    jnz     ret_BFB4
    mov     ax, 1400
    call    sub_C002
    call    fade_out

ret_BFB4:
    ret


;
; BFB5: Loads (Sound Blaster only) effects when one of the following tracks has been selected: Desert - S60, Storm - S61, Wind - S62.
;
prep_sndblaster_efx:
    mov     word [word_2AF9], 0
    cmp     word [word_16F6], 0
    jnz     ret_BFF7
    mov     ax, 5360h    ; 'S60'
    mov     bx, [track_num]
    cmp     bl, 4
    jz      loc_BFDA
    inc     ax
    cmp     bl, 7
    jz      loc_BFDA
    inc     ax
    cmp     bl, 10
    jnz     ret_BFF7

loc_BFDA:
    call    res_load
    xchg    ax, [word_63BA]
    mov     [word_2AF7], ax
    sub     ax, [word_63BA]
    neg     ax
    shl     ax, 4
    neg     cx
    and     cx, 0Fh
    sub     ax, cx
    mov     [word_2AF9], ax

ret_BFF7:
    ret


;
; BFF8: Sleep
;
; in:
; ax - delay
;
sleep:
    call    sub_D6F9
    cmp     [word_3E18], ax
    jb      sleep
    ret


;
; C002: Sleep
;
; in:
; ax - delay
;
sub_C002:
    call    sub_D6F9
    cmp     [word_3E18], ax
    jnb     ret_C010
    call    sub_C011
    jnb     sub_C002

ret_C010:
    ret


;
; C011:
;
sub_C011:
    cmp     byte [byte_3D86], 0
    jz      loc_C025
    mov     bl, [byte_3D87]
    mov     bh, 0
    mov     byte [bx + byte_3D88], 80h

loc_C023:
    stc
    ret

loc_C025:
    mov     al, [byte_16FE]
    push    ax
    mov     byte [byte_3E2D], 0
    call    sub_D962
    pop     ax
    xor     al, [byte_16FE]
    and     al, [byte_16FE]
    and     al, 30h
    jnz     loc_C023
    cmp     byte [byte_3E2D], 0
    jnz     loc_C023
    clc
    ret
