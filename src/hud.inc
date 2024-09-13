;
; 8E0E: P2: Draw PAUSED, DEMO, RACE COMPLETED, TURBO ZONE, etc
;
sub_8E0E:
    jmp      draw_race_text


;
; Draw PAUSED, DEMO, RACE COMPLETED, TURBO ZONE, etc
;
draw_race_text:
    mov     si, [word_3ED8]
    cmp     word [is_paused], 0
    jz      loc_8E21
    mov     di, paused_txt
    jmp     print_text

loc_8E21:
    cmp     word [playing_demo], 0
    jz      loc_8E37
    mov     di, demo_txt
    test    word [word_3EE6], 16
    jz      ret_8E36
    jmp     print_text

ret_8E36:
    ret

loc_8E37:
    cmp     word [si + 26], 0
    jz      loc_8E6D
    mov     di, race_completed_txt
    cmp     word [si + 26], 2
    jne     loc_8E49
    jmp     print_text

loc_8E49:
    cmp     word [word_3EE4], 0
    jnz     loc_8E5E
    cmp     word [si + 32], 0
    jz      loc_8E59
    jmp     near print_text

loc_8E59:
    mov     di, out_of_time_txt
    jmp     print_text

loc_8E5E:
    mov     di, race_over_txt
    cmp     word [si + 222], 0
    jnz     print_text
    mov     di, out_of_fuel_txt
    jmp     print_text

loc_8E6D:
    cmp     word [si + 188], 0
    jz      loc_8E79
    mov     di, turbo_zone_txt
    jmp     print_text

loc_8E79:
    cmp     word [si + 168], 0
    jz      loc_8E8C
    mov     di, checkpoint_txt
    test    word [si + 168], 8
    jne     print_text
    ret

loc_8E8C:
    cmp     word [si + 222], 5C00h
    jae     loc_8EA0
    mov     di, low_fuel_txt
    test    word [word_3EE6], 16
    je      print_text
    ret

loc_8EA0:
    cmp     word [num_of_players], 0
    jz      ret_8ED6
    mov     di, word_4034
    mov     bp, p2_name
    cmp     si, di
    jnz     loc_8EB7
    mov     di, word_3F3A
    mov     bp, p1_name

loc_8EB7:
    mov     ax, [di + 2]
    sub     ax, [si + 2]
    mov     ax, [di]
    sbb     ax, [si]
    cmp     ax, 4
    jae     ret_8ED6
    mov     si, bp
    mov     di, ahead_txt
    push    di
    push    ds
    pop     es
    mov     cx, 6
    rep movsw
    pop     di
    jmp     print_text

ret_8ED6:
    ret


;
; 8ED7:
;
print_text:
    mov     ch, 1
    mov     bx, 15
    jmp     print_string


;
; 8EDE: Print text
;
; in:
; di - string to write
; bx - y
; ch - unpacked texture index
;
print_string:
    push    ds
    pop     es
    mov     [print_font_ix], ch
    mov     cx, 40
    mov     al, 20h
    repe scasb
    dec     di                         ; locate first non-space character
    mov     si, di
    mov     di, print_tmp_str
    push    di

next_char:
    cmp     byte [si], 0               ; "\0"
    jz      loc_8F0C
    cmp     word [si], 0020h           ; " \0"
    jz      loc_8F0C
    cmp     word [si], 2020h           ; "  "
    jnz     loc_8F05
    inc     si
    jmp     next_char

loc_8F05:
    movsb
    cmp     di, print_font_ix          ; < 40 chars?
    jb      next_char

loc_8F0C:
    mov     ax, si
    pop     si
    inc     ax
    push    ax
    mov     dx, di
    sub     dx, si                     ; dx = strlen
    jz      exit_8F33
    mov     ax, dx
    shl     ax, 3
    neg     ax
    add     ax, 320
    shr     ax, 1
    mov     ch, [print_font_ix]

draw_one_more_char:
    mov     cl, [si]
    inc     si                         ; x = (!(strlen << 3) + 320) >> 1
    call    draw_char_small
    add     ax, 8                      ; x += 8
    dec     dx
    jnz     draw_one_more_char

exit_8F33:
    pop     di
    ret


loc_8F35:
    jmp     brandish_the_flag


;
; 8F37: Brandish the flag
;
brandish_the_flag:
    mov     si, [word_3ED8]
    mov     ax, [word_3EE0]
    mov     cl, 0
    and     ax, ax
    js      loc_8F83
    cmp     ax, 75
    jae     loc_8F57
    mov     cl, 14
    cmp     al, 20
    jae     loc_8F83
    shr     al, 2
    inc     ax
    mov     cl, al
    jmp     loc_8F83

loc_8F57:
    mov     ax, [si + 216]
    and     ax, ax
    jz      loc_8F73
    cmp     ax, 75
    jae     loc_8F73
    mov     cl, 14
    cmp     al, 24
    jae     loc_8F83
    shr     al, 2
    add     al, 6
    mov     cl, al
    jmp     loc_8F83

loc_8F73:
    cmp     word [si + 228], 0
    jz      ret_8FA2
    cmp     word [si + 222], 0FFFFh
    jz      ret_8FA2
    mov     cl, 12

loc_8F83:
    push    cx
    mov     ax, 224
    mov     bx, 29
    mov     ch, 2
    mov     cl, 13                     ; draw background frame
    call    bmp_draw
    pop     cx
    cmp     cl, 13
    ja      ret_8FA2
    mov     ax, 224
    mov     bx, 29
    mov     ch, 2                      ; draw a flag
    call    bmp_draw

ret_8FA2:
    ret


loc_8FA3:
    jmp     draw_race_info


;
; 8FA5: Draw speed, gear, time, laps left, gas
;
draw_race_info:
    mov     si, [word_3ED8]
    mov     ax, 9A7h
    mul     word [si + 14]             ; 16 kmh = 01A9h
    ; 1 kmh ~= 20h
    mov     ax, dx
    mov     ch, 1                      ; C01
    mov     bl, 10
    div     bl
    mov     cl, ah
    push    cx
    mov     ah, 0
    div     bl
    mov     cl, ah
    push    cx
    mov     cl, al                     ; 1-st speed number
    mov     ax, 2
    mov     bx, 2
    call    bmp_draw
    pop     cx                         ; 2-nd speed number
    add     ax, 8
    call    bmp_draw
    pop     cx                         ; 3-rd speed number
    add     ax, 8
    call    bmp_draw
    mov     cl, 37                     ; hyphen
    add     ax, 8
    call    bmp_draw
    mov     cl, 20                     ; K
    add     ax, 8
    call    bmp_draw
    mov     cl, 22                     ; M
    add     ax, 8
    call    bmp_draw
    mov     cl, 17                     ; H
    add     ax, 8
    call    bmp_draw
    mov     cl, 37                     ; hyphen
    add     ax, 8
    call    bmp_draw
    mov     es, [word_63BC]
    mov     di, 336 * 17 + 18
    call    sub_9242
    mov     dx, [si + 44]
    shr     dx, 7
    cmp     dx, 2Eh                    ; '.'
    jb      loc_901A
    mov     dx, 2Eh                    ; '.'

loc_901A:
    mov     bp, 0Ch

loc_901D:
    push    di
    mov     cx, dx
    jcxz    loc_9038
    cmp     cx, 20h                    ; ' '
    jb      loc_902A
    mov     cx, 20h                    ; ' '

loc_902A:
    mov     al, 0E4h                   ; 'S'
    rep stosb
    mov     cx, dx
    sub     cx, 20h                    ; ' '
    jbe     loc_9038
    inc     ax
    rep stosb

loc_9038:
    mov     al, 0E0h                   ; 'a'
    stosb
    pop     di
    add     di, 336
    dec     bp
    jnz     loc_901D
    mov     cx, [si + 40]
    inc     cx                         ; gear: 1, 2, 3, 4, 5
    mov     ch, 0                      ; C00
    mov     ax, 1
    mov     bx, 29
    call    bmp_draw
    add     ax, 16
    add     cl, 9                      ; st, nd, rd, th
    call    bmp_draw
    cmp     word [word_3EE4], 0
    jnz     loc_9065
    jmp     loc_90E9                   ; when Race::TimeLimit

; draw gas level borders
loc_9065:
    mov     di, 336 * 6 + 270
    mov     ax, 0E0E0h                 ; blackblack
    mov     cx, 32
    rep stosw                          ; top bounding line
    mov     cx, 7

loc_9073:
    add     di, 335
    stosb                              ; right bounding line
    loop    loc_9073

    add     di, 334
    mov     cx, 32
    std                                ; decrease DI on rep
    rep stosw                          ; bottom bounding line
    cld

    sub     di, 334
    mov     cx, 7

loc_908C:
    stosb                              ; left bounding line
    sub     di, 337
    loop    loc_908C

    ; draw gas level
    add     di, 337
    mov     ax, [si + 222]
    rol     ax, 6
    and     ax, 3Fh
    cmp     ax, 1
    cmc
    sbb     ax, 0
    mov     dx, 8
    cmp     ax, dx
    jg      loc_90B1
    mov     dx, ax

loc_90B1:
    sub     ax, dx
    mov     bx, 16
    cmp     ax, bx
    jg      loc_90BC
    mov     bx, ax

loc_90BC:
    sub     ax, bx
    mov     bh, al
    mov     bp, 7                      ; height = 7 pixels

loc_90C3:
    push    di
    mov     cx, dx
    jcxz    loc_90CC
    mov     al, 0E5h                   ; light red
    rep stosb

loc_90CC:
    mov     cl, bl
    jcxz    loc_90D4
    mov     al, 0E4h                   ; dark red
    rep stosb

loc_90D4:
    mov     cl, bh
    jcxz    loc_90DC
    mov     al, 230                    ; green
    rep stosb

loc_90DC:
    mov     al, 0E0h                   ; black
    stosb                              ; right bounding line (inner)
    pop     di
    add     di, 336
    dec     bp
    jnz     loc_90C3
    jmp     loc_9102

loc_90E9:
    mov     cx, 254
    mov     bx, 2

loc_90EF:
    mov     dx, [si + 46]              ; score
    mov     ax, [si + 48]              ; score
    mov     bp, 10000
    div     bp
    push    dx
    call    sub_9277                   ; draw right part (4 numbers)
    pop     ax
    call    sub_9277                   ; draw left part (4 numbers)

loc_9102:
    mov     ax, [si + 32]
    cmp     word [word_3EE4], 0
    jz      loc_9110
    mov     ax, [si + 226]

    ; draw remaining time when Race::TimeLimit
loc_9110:
    mov     cl, 10
    div     cl
    mov     ch, 0
    mov     cl, ah
    push    cx
    mov     cl, al
    mov     ax, 287
    mov     bx, 29
    jcxz    loc_9126
    call    bmp_draw                   ; left number

loc_9126:
    pop     cx
    add     ax, 16
    call    bmp_draw                   ; right number
    mov     es, [word_63BC]

    ; draw track line borders
    mov     di, 336 * 51 + 316
    mov     bp, [num_of_tracks]
    mov     ax, 0E0E0h                 ; blackblack
    cmp     word [track_num], 1        ; Night
    je      loc_9150
    cmp     word [track_num], 2        ; Fog
    je      loc_9150
    cmp     word [track_num], 7        ; Storm
    jne     loc_9153

loc_9150:
    mov     ax, 0E2E2h                 ; lightgraylightgray

loc_9153:
    mov     cx, 9                      ; 18 px wide
    rep stosw                          ; draw top line
    add     di, 318
    stosb                              ; draw left (top) px
    add     di, 16
    stosb                              ; draw right (top) px
    add     di, 318
    stosb                              ; draw left (bottom) px
    add     di, 16
    stosb                              ; draw right (bottom) px
    add     di, 318
    dec     bp
    jnz     loc_9153                   ; for each track line
    mov     cx, 9
    rep stosw                          ; draw bottom line

    ; draw completed track progress bar
    mov     di, 336 * 52 + 317
    mov     bx, arr_2400
    mov     bp, [si]
    cmp     bp, [bx]
    jbe     loc_91D1
    mov     ax, 0E5E5h                 ; redred

loc_9185:
    cmp     word [bx + 2], 0FFFFh
    jz      loc_91D1
    cmp     bp, [bx + 2]
    jb      loc_91A7
    mov     cx, 8                      ; full width (16 px)
    rep stosw
    add     di, 320
    mov     cx, 8                      ; full width (16 px)
    rep stosw
    add     di, 336 * 1 + 320
    add     bx, 2
    jmp     loc_9185

loc_91A7:
    mov     cx, [bx + 2]
    sub     cx, [bx]
    mov     ax, bp
    sub     ax, [bx]
    shl     ax, 4
    mov     dx, 0
    jcxz    loc_91D1
    div     cx
    mov     dx, ax
    cmp     dx, 16
    jae     loc_91D1

    ; draw current track progress bar
    mov     al, 0E5h                   ; red
    push    di
    mov     cx, dx
    rep stosb                          ; top px
    pop     di
    add     di, 336
    mov     cx, dx
    rep stosb                          ; bottom px

loc_91D1:
    cmp     word [num_of_players], 0
    je      ret_9241

    ; for 2PL mode draw status bar on who is ahead
    mov     di, 336 * 17 + 286
    call    sub_9242
    mov     dx, [word_3FB6]
    mov     ax, [word_4026]
    cmp     si, word_4034
    jz      loc_91F2
    mov     dx, [word_40B0]
    mov     ax, [word_4120]

loc_91F2:
    sub     dx, [si + 124]
    sar     dx, 1
    jns     loc_91FC
    adc     dx, 0

loc_91FC:
    cmp     dx, -22
    jg      loc_9204
    mov     dx, -22

loc_9204:
    cmp     dx, 22
    jl      loc_920C
    mov     dx, 22

loc_920C:
    cmp     al, 3
    jb      loc_9212
    mov     al, 0

loc_9212:
    shl     al, 1
    add     al, 5
    add     al, [byte_2E81]
    mov     ah, 0E0h
    xchg    al, ah
    add     di, 21
    inc     dx
    jg      loc_922A
    dec     dx
    add     di, dx
    neg     dx
    inc     dx

loc_922A:
    inc     dx
    mov     bp, 12

loc_922E:
    push    di
    stosb
    mov     cx, dx
    xchg    al, ah
    rep stosb
    xchg    al, ah
    stosb
    pop     di
    add     di, 336
    dec     bp
    jnz     loc_922E

ret_9241:
    ret


;
; 9242: Draw black frame for "ahead HUD" in 2PL mode
;
sub_9242:
    mov     ax, 0E0E0h                 ; blackblack
    mov     cx, 24
    rep stosw
    mov     cx, 12
    add     di, 335

loc_9251:
    mov     [es:di], al
    add     di, 336
    loop    loc_9251
    dec     di
    mov     cx, 24
    std
    rep stosw
    cld
    sub     di, 334
    mov     cx, 12

loc_9269:
    mov     [es:di], al
    sub     di, 336
    loop    loc_9269
    add     di, 337
    ret


;
; 9277:
;
sub_9277:
    mov     dl, 100
    div     dl
    push    ax
    call    sub_9282
    pop     ax
    mov     al, ah

sub_9282:
    mov     ah, 0
    mov     dl, 10
    div     dl
    push    ax
    call    sub_928F
    pop     ax
    mov     al, ah

sub_928F:
    xchg    ax, cx
    mov     ch, 1
    call    bmp_draw
    add     ax, 8
    xchg    ax, cx
    ret


;
; 929A:
;
sub_929A:
    mov     di, 0
    jmp     loc_92CE


;
; 929F: P2: Update the screen
;
sub_929F:
    mov     di, 336 * 99 + 16
    jmp     loc_92CE


;
; 92A4:
;
sub_92A4:
    mov     bx, [word_63BC]
    mov     es, bx
    mov     di, VGA_DBL_BUF_START
    mov     ax, 0
    mov     cx, 16800
    rep stosw
    mov     di, VGA_DBL_BUF_START
    add     bx, 2100
    mov     es, bx
    mov     cx, 16800
    rep stosw
    ret


;
; 92C4:
;
update_screen:
    mov     di, 0
    mov     dx, 200
    call    vga_draw
    ret


loc_92CE:
    mov     dx, [word_633A]


;
; 92D2: VGA draw
;
; in:
; word_63BC - video data
; dx - height
; di - offset
;
vga_draw:
    push    ds
    mov     ax, 0A000h
    mov     es, ax
    shr     dx, 1
    mov     ds, [word_63BC]
    mov     si, VGA_DBL_BUF_START
    push    dx
    call    word [cs:off_92FD]
    pop     dx
    mov     cx, si
    and     si, 0Fh
    shr     cx, 4
    mov     ax, ds
    add     ax, cx
    mov     ds, ax
    call    word [cs:off_92FD]
    pop     ds
    ret


off_92FD:   dw sub_9303, sub_9319, sub_9325


;
; 9303:
;
sub_9303:
    push    bx
    mov     bx, [cs:word_D379]
    mov     bx, [cs:bx - 6D01h]
    mov     [cs:off_92FD], bx
    pop     bx
    jmp     word [cs:off_92FD]


;
; 9319:
;
sub_9319:
    mov     cx, 160
    rep movsw
    add     si, 16
    dec     dx
    jnz     sub_9319
    ret


;
; 9325:
;
sub_9325:
    mov     cx, 80
    rep movsd
    add     si, 16
    dec     dx
    jnz     sub_9325
    ret


;
; 9332
;
clear_screen:
    mov     ax, 0A000h
    mov     es, ax
    mov     ax, 0
    mov     di, ax
    mov     cx, 32000
    rep stosw
    ret


;
; 9342:
;
loc_9342:
    push    ax
    push    bx
    push    cx
    push    si
    push    di
    push    word [word_637A]
    mov     ax, [word_2060]
    mov     bh, 0
    mov     bl, ah
    mov     ah, al
    mov     al, 0
    shl     ax, 1
    rcl     bx, 1
    shl     ax, 1
    rcl     bx, 1
    shl     ax, 1
    rcl     bx, 1
    shl     ax, 1
    rcl     bx, 1
    mov     si, [word_3ED8]
    add     ax, [si + 134]
    adc     bx, [si + 132]
    cmp     word [is_circular_track], 0
    jz      loc_937F
    mov     bl, [bx + arr_7856]
    mov     bh, 0

loc_937F:
    shl     bx, 4
    mov     si, tmp_file_buf
    cmp     byte [bx + si + 10], 0
    jns     loc_9397
    mov     ax, [word_2060]
    mov     bx, [word_2062]
    mov     bh, 0FDh
    call    sub_94C0

loc_9397:
    mov     word [word_2060], 0FFFFh
    pop     word [word_637A]
    pop     di
    pop     si
    pop     cx
    pop     bx
    pop     ax
    ret


;
; 93A7:
;
sub_93A7:
    push    si
    push    di
    push    word [word_637A]
    mov     ax, [word_1FF4]
    mov     cx, [word_1FF6]
    mov     bx, [word_1FF8]
    mov     si, ax
    shl     si, 1
    mov     bp, [si + arr_6AC2]
    mov     [word_636E], bp
    and     bp, bp
    js      loc_93E5
    mov     bp, [word_1FFA]
    mov     word [word_2208], bp
    mov     word [word_2110], 0
    mov     word [word_3CE6], 99h
    call    sub_946A
    mov     word [word_3CE6], 0

loc_93E5:
    pop     word [word_637A]
    pop     di
    pop     si
    push    si
    push    di
    push    word [word_637A]
    call    sub_8DBC
    pop     word [word_637A]
    pop     di
    pop     si
    ret


;
; 93FB:
;
sub_93FB:
    mov     ax, [word_1FFE]
    mov     [word_221C], ax
    mov     cx, [word_2000]
    mov     bx, [word_2002]
    mov     si, ax
    shl     si, 1
    mov     bp, [si + arr_6AC2]
    mov     [word_636E], bp
    and     bp, bp
    js      ret_942A
    mov     bp, [word_2004]
    mov     [word_2208], bp
    mov     word [word_2110], 0
    call    sub_946A

ret_942A:
    ret


;
; 942B:
;
sub_942B:
    mov     ax, [word_200E]
    mov     bx, ax
    cbw
    mov     word [word_2214], ax
    and     word [word_2214], 0FFF8h
    mov     cx, bx
    and     bx, 3
    mov     [word_2208], bx
    mov     cl, 0
    mov     [word_2110], cx
    mov     ax, [word_2008]
    mov     [word_221C], ax
    mov     cx, [word_200A]
    mov     bx, [word_200C]
    mov     si, ax
    shl     si, 1
    mov     bp, [si + arr_6AC2]
    mov     [word_636E], bp
    and     bp, bp
    js      ret_9469
    call    sub_946A

ret_9469:
    ret


;
; 946A:
;
sub_946A:
    mov     di, [word_3ED8]
    mov     bp, [di + 122]
    mov     [word_21FC], bp
    mov     bp, [di + 136]
    mov     [word_2202], bp
    mov     bp, [di + 132]
    mov     [word_21FE], bp
    mov     bp, [di + 134]
    mov     [word_2200], bp
    mov     word [word_637A], 0
    mov     di, [word_2E7C]
    mov     bp, [word_2110]
    mov     [word_6362], bp
    mov     word [word_2114], 0
    cmp     word [word_3CE6], 0
    jz      loc_94B6
    mov     di, [word_2DB8]
    mov     word [word_2208], 0FFFFh

loc_94B6:
    jmp     sub_9A1E


;
; 94B9: Draw all objects
;
sub_94B9:
    mov     ax, [word_1FEE]
    mov     bx, [word_1FF0]


;
; 94C0:
;
sub_94C0:
    mov     [word_2112], bx
    mov     cl, bh
    mov     ch, 0
    mov     [word_2114], cx
    shl     bl, 1
    sbb     bh, bh
    shl     bx, 3
    mov     si, ax
    shl     si, 1
    mov     bp, [si + arr_69C2]
    mov     [word_636E], bp
    and     bp, bp
    js      ret_94EA
    mov     cx, [word_1FEC]
    call    sub_94EB

ret_94EA:
    ret


;
; 94EB:
;
sub_94EB:
    mov     di, [word_3ED8]
    mov     bp, [di + 122]
    mov     [word_21FC], bp
    mov     bp, [di + 136]
    mov     [word_2202], bp
    mov     bp, [di + 132]
    mov     [word_21FE], bp
    mov     bp, [di + 134]
    mov     [word_2200], bp
    cmp     word [word_2114], 8Ah
    jne     loc_953B
    cmp     word [is_circular_track], 0
    jz      loc_953B
    mov     bp, [di + 218]
    cmp     bp, 0
    jl      loc_9535
    inc     bp
    cmp     bp, [num_of_tracks]
    jb      loc_953B
    mov     word [word_2114], 137
    jmp     loc_953B

loc_9535:
    mov     word [word_2114], 136

loc_953B:
    mov     word [word_637A], 0
    mov     word [word_637C], 0
    mov     di, [word_2114]
    shl     di, 1
    mov     di, [di + word_2C76]
    mov     word [word_6362], 0
    mov     word [word_2208], 0FFFFh
    mov     bp, [word_2114]
    cmp     bp, 64
    jns     loc_9569
    jmp     loc_9789

loc_9569:
    cmp     bp, 218
    jne     loc_9572
    jmp     loc_97A4

loc_9572:
    cmp     bp, 160
    jne     loc_957B
    jmp     loc_9619

loc_957B:
    cmp     bp, 155
    jne     loc_9584
    jmp     loc_9999

loc_9584:
    cmp     bp, 219
    jne     loc_958D
    jmp     loc_97FD

loc_958D:
    cmp     bp, 150
    jne     loc_9596
    jmp     loc_9910

loc_9596:
    cmp     bp, 226
    jne     loc_959F
    jmp     loc_9910

loc_959F:
    cmp     bp, 136
    js      loc_95F1
    cmp     bp, 139
    jns     loc_95F1
    mov     bx, 0
    push    ax
    push    bx
    push    cx
    push    dx
    push    word [word_6362]
    push    word [word_6366]
    push    word [word_636A]
    push    word [word_636E]
    push    si
    push    di
    push    word [word_637A]
    call    sub_9A1E                   ; Draw START banner.
    pop     word [word_637A]
    pop     di
    pop     si
    pop     word [word_636E]
    pop     word [word_636A]
    pop     word [word_6366]
    pop     word [word_6362]
    pop     dx
    pop     cx
    pop     bx
    pop     ax
    call    sub_95F4
    mov     word [word_2208], 0FF00h
    jmp     loc_9A4B

loc_95F1:
    jmp     sub_9A1E                   ; Draw objects one-by-one.


;
; 95F4:
;
sub_95F4:
    cmp     word [word_63A0], 0
    jnz     loc_9603
    cmp     word [word_639E], 0
    jnz     loc_960E
    ret

loc_9603:
    mov     di, [word_2114]
    shl     di, 1
    mov     di, [di + arr_2CBA]
    ret

loc_960E:
    mov     di, [word_2114]
    shl     di, 1
    mov     di, [di + arr_2CF2]
    ret


;
; 9619:
;
loc_9619:
    mov     word [word_2212], 0FFFFh
    sub     bx, [word_3EE6]
    shl     bx, 4
    and     bx, 1FFFh
    sub     bx, 1000h
    push    ax
    push    bx
    push    cx
    push    dx
    push    word [word_6362]
    push    word [word_6366]
    push    word [word_636A]
    push    word [word_636E]
    push    si
    push    di
    push    word [word_637A]
    call    sub_9A1E
    pop     word [word_637A]
    pop     di
    pop     si
    pop     word [word_636E]
    pop     word [word_636A]
    pop     word [word_6366]
    pop     word [word_6362]
    pop     dx
    pop     cx
    pop     bx
    pop     ax
    cmp     word [word_2212], 0
    jns     loc_966F
    jmp     ret_9788

loc_966F:
    push    word [word_2212]
    push    word [word_220C]
    cmp     word [word_636E], 9
    js      loc_9681
    jmp     loc_974B

loc_9681:
    mov     di, [word_2DB2]
    mov     bx, [word_220E]
    mov     cx, [word_2212]
    push    ax
    push    bx
    push    cx
    push    dx
    push    word [word_6362]
    push    word [word_6366]
    push    word [word_636A]
    push    word [word_636E]
    push    si
    push    di
    push    word [word_637A]
    call    sub_9CA1
    pop     word [word_637A]
    pop     di
    pop     si
    pop     word [word_636E]
    pop     word [word_636A]
    pop     word [word_6366]
    pop     word [word_6362]
    pop     dx
    pop     cx
    pop     bx
    pop     ax
    mov     di, [word_2DB0]
    pop     bx
    mov     cx, [word_2212]
    push    ax
    push    bx
    push    cx
    push    dx
    push    word [word_6362]
    push    word [word_6366]
    push    word [word_636A]
    push    word [word_636E]
    push    si
    push    di
    push    word [word_637A]
    call    sub_9CB1
    pop     word [word_637A]
    pop     di
    pop     si
    pop     word [word_636E]
    pop     word [word_636A]
    pop     word [word_6366]
    pop     word [word_6362]
    pop     dx
    pop     cx
    pop     bx
    pop     ax
    push    word [word_220C]
    mov     di, [word_2DB4]
    mov     bx, [word_220C]
    mov     cx, [word_2210]
    push    ax
    push    bx
    push    cx
    push    dx
    push    word [word_6362]
    push    word [word_6366]
    push    word [word_636A]
    push    word [word_636E]
    push    si
    push    di
    push    word [word_637A]
    call    sub_9CA1
    pop     word [word_637A]
    pop     di
    pop     si
    pop     word [word_636E]
    pop     word [word_636A]
    pop     word [word_6366]
    pop     word [word_6362]
    pop     dx
    pop     cx
    pop     bx
    pop     ax

 loc_974B:
    mov     di, [word_2DAE]
    pop     bx
    pop     cx
    push    ax
    push    bx
    push    cx
    push    dx
    push    word [word_6362]
    push    word [word_6366]
    push    word [word_636A]
    push    word [word_636E]
    push    si
    push    di
    push    word [word_637A]
    call    sub_9CB1
    pop     word [word_637A]
    pop     di
    pop     si
    pop     word [word_636E]
    pop     word [word_636A]
    pop     word [word_6366]
    pop     word [word_6362]
    pop     dx
    pop     cx
    pop     bx
    pop     ax

ret_9788:
    ret


;
; 9789:
;
loc_9789:
    mov     di, 184
    xchg    di, [word_2114]
    shl     di, 1
    mov     di, [di + arr64_2116]
    shl     di, 8
    mov     [word_6362], di
    mov     di, [word_2DE6]
    jmp     sub_9A1E


loc_97A4:
    push    ax
    push    dx
    mov     ax, bx
    shl     bx, 4
    add     bx, [word_3EE8]
    and     bx, 1FFFh
    sub     bx, 1000h
    push    bx
    and     ax, 3
    add     ax, 2
    imul    bx
    mov     bx, ax
    sar     bx, 2
    pop     ax
    and     ax, 3FFh
    cmp     ax, 512
    js      loc_97D1
    xor     ax, 3FFh

loc_97D1:
    mul     word [word_3EEA]
    shr     dx, 1
    rcr     ax, 1
    shr     dx, 1
    rcr     ax, 1
    shr     dx, 1
    rcr     ax, 1
    shr     dx, 1
    rcr     ax, 1
    shr     dx, 1
    rcr     ax, 1
    shr     dx, 1
    rcr     ax, 1
    shr     dx, 1
    rcr     ax, 1
    shr     dx, 1
    rcr     ax, 1
    mov     [word_6362], ax
    pop     dx
    pop     ax
    jmp     sub_9A1E

loc_97FD:
    push    bx
    mov     bx, 0FE00h
    push    ax
    push    bx
    push    cx
    push    dx
    push    word [word_6362]
    push    word [word_6366]
    push    word [word_636A]
    push    word [word_636E]
    push    si
    push    di
    push    word [word_637A]
    call    sub_9A1E
    pop     word [word_637A]
    pop     di
    pop     si
    pop     word [word_636E]
    pop     word [word_636A]
    pop     word [word_6366]
    pop     word [word_6362]
    pop     dx
    pop     cx
    pop     bx
    pop     ax
    push    word [word_220E]
    mov     di, [word_2E2E]
    neg     bx
    push    ax
    push    bx
    push    cx
    push    dx
    push    word [word_6362]
    push    word [word_6366]
    push    word [word_636A]
    push    word [word_636E]
    push    si
    push    di
    push    word [word_637A]
    call    sub_9A1E
    pop     word [word_637A]
    pop     di
    pop     si
    pop     word [word_636E]
    pop     word [word_636A]
    pop     word [word_6366]
    pop     word [word_6362]
    pop     dx
    pop     cx
    pop     bx
    pop     ax
    mov     bp, [word_220C]
    mov     [word_6362], bp
    pop     cx
    push    si
    mov     si, [word_220A]
    shl     si, 1
    mov     dx, [si + arr17_2196]
    add     dx, [word_2210]
    mov     [word_6366], dx
    add     dx, [si + arr17_21B8]
    xchg    dx, [word_6366]
    pop     si
    mov     word [word_2206], 0Fh
    pop     ax
    add     ax, [word_3EE6]
    and     ax, 38h
    jnz     ret_990F
    push    bx
    mov     bx, [word_1FEE]
    xor     bx, 7Fh
    shr     bx, 1
    mov     ax, 115
    call    sub_50B4
    pop     bx
    push    ax
    push    bx
    push    cx
    push    dx
    push    word [word_6362]
    push    word [word_6366]
    push    word [word_636A]
    push    word [word_636E]
    push    si
    push    di
    push    word [word_637A]
    call    sub_A51E
    pop     word [word_637A]
    pop     di
    pop     si
    pop     word [word_636E]
    pop     word [word_636A]
    pop     word [word_6366]
    pop     word [word_6362]
    pop     dx
    pop     cx
    pop     bx
    pop     ax
    push    si
    mov     si, [word_220A]
    shl     si, 1
    mov     ax, [si + arr17_21DA]
    pop     si
    and     ax, ax
    jz      ret_990F
    add     dx, ax
    add     [word_6366], ax
    call    sub_A51E

ret_990F:
    ret


loc_9910:
    push    word [word_2114]
    push    ax
    push    bx
    push    cx
    push    dx
    push    word [word_6362]
    push    word [word_6366]
    push    word [word_636A]
    push    word [word_636E]
    push    si
    push    di
    push    word [word_637A]
    mov     word [word_2114], 223
    mov     bx, 0FF20h
    mov     di, [word_2E34]
    call    sub_9A1E
    pop     word [word_637A]
    pop     di
    pop     si
    pop     word [word_636E]
    pop     word [word_636A]
    pop     word [word_6366]
    pop     word [word_6362]
    pop     dx
    pop     cx
    pop     bx
    pop     ax
    pop     word [word_2114]
    pusha
    call    sub_7545
    popa
    push    ax
    push    bx
    push    cx
    push    dx
    push    word [word_6362]
    push    word [word_6366]
    push    word [word_636A]
    push    word [word_636E]
    push    si
    push    di
    push    word [word_637A]
    call    sub_9A1E
    pop     word [word_637A]
    pop     di
    pop     si
    pop     word [word_636E]
    pop     word [word_636A]
    pop     word [word_6366]
    pop     word [word_6362]
    pop     dx
    pop     cx
    pop     bx
    pop     ax
    ret


loc_9999:
    push    ax
    push    bx
    push    cx
    push    dx
    push    word [word_6362]
    push    word [word_6366]
    push    word [word_636A]
    push    word [word_636E]
    push    si
    push    di
    push    word [word_637A]
    call    sub_9A1E
    pop     word [word_637A]
    pop     di
    pop     si
    pop     word [word_636E]
    pop     word [word_636A]
    pop     word [word_6366]
    pop     word [word_6362]
    pop     dx
    pop     cx
    pop     bx
    pop     ax
    mov     cx, [word_2210]
    mov     bx, [word_220C]
    add     bx, [word_220E]
    sar     bx, 1
    sub     bx, 160
    mov     di, [word_2DAA]
    push    ax
    push    bx
    push    cx
    push    dx
    push    word [word_6362]
    push    word [word_6366]
    push    word [word_636A]
    push    word [word_636E]
    push    si
    push    di
    push    word [word_637A]
    call    sub_9CC5
    pop     word [word_637A]
    pop     di
    pop     si
    pop     word [word_636E]
    pop     word [word_636A]
    pop     word [word_6366]
    pop     word [word_6362]
    pop     dx
    pop     cx
    pop     bx
    pop     ax
    ret


;
; 9A1E:
;
sub_9A1E:
    mov     bp, [word_6362]
    mov     [word_2204], bp
    mov     bp, [word_2114]
    cmp     bp, 88h
    jb      loc_9A4B
    cmp     bp, 8Ah
    jbe     loc_9A42
    cmp     bp, 0FAh
    jb      loc_9A4B
    cmp     bp, 0FDh
    ja      loc_9A4B

loc_9A42:
    mov     word [word_2208], 0FFFEh
    mov     bx, 0

loc_9A4B:
    cmp     ax, 64
    jb      loc_9A53
    jmp     loc_9B03

loc_9A53:
    cmp     word [word_2208], 0FFFEh
    jnz     loc_9A5D
    jmp     loc_9B03

loc_9A5D:
    dec     word [word_21FC]
    cmp     word [word_2114], 0FDh
    jz      loc_9A70
    cmp     ax, [word_21FC]
    jb      loc_9A7A
    ret

loc_9A70:
    cmp     ax, [word_21FC]
    jb      loc_9A7A
    mov     ax, [word_21FC]
    dec     ax

loc_9A7A:
    shr     cx, 1
    mov     dx, cx
    shl     ax, 1
    mov     si, ax
    shl     si, 2
    add     si, arr_C568
    mov     bp, [si + 4]
    mov     [word_2218], bp
    mov     bp, [si + 6]
    mov     [word_221A], bp
    mov     cx, [si + 8]
    mov     bp, [si]
    sub     cx, bp
    push    ax
    push    dx
    mov     ax, dx
    imul    cx
    shl     ax, 1
    rcl     dx, 1
    mov     cx, dx
    pop     dx
    pop     ax
    add     cx, bp
    sub     bx, [word_2202]
    shl     bx, 2
    sub     bx, cx
    mov     cx, [si + 10]
    mov     bp, [si + 2]
    sub     cx, bp
    push    ax
    push    dx
    mov     ax, dx
    imul    cx
    shl     ax, 1
    rcl     dx, 1
    mov     cx, dx
    pop     dx
    pop     ax
    add     cx, bp
    mov     si, arr_68C2
    add     si, ax
    mov     bp, [si]
    mov     [word_2216], bp
    mov     ax, [si + 2]
    mov     bp, [si]
    sub     ax, bp
    push    dx
    imul    dx
    shl     ax, 1
    rcl     dx, 1
    mov     ax, dx
    add     ax, bp
    shl     ax, 2
    imul    bx
    mov     bx, dx
    pop     dx
    mov     bp, [word_633A]
    sub     bp, 2
    cmp     cx, bp
    jb      loc_9B63
    mov     cx, bp
    jmp     loc_9B63

loc_9B03:
    cmp     word [word_2114], 0FDh
    jz      loc_9B12
    cmp     ax, [word_21FC]
    jb      loc_9B1C
    ret

loc_9B12:
    cmp     ax, [word_21FC]
    jb      loc_9B1C
    mov     ax, [word_21FC]
    dec     ax

loc_9B1C:
    shl     ax, 1
    mov     si, ax
    shl     si, 2
    add     si, arr_C568
    mov     bp, [si + 4]
    mov     [word_2218], bp
    mov     bp, [si + 6]
    mov     [word_221A], bp
    sub     bx, [word_2202]
    shl     bx, 3
    sar     bx, 1
    sub     bx, [si]
    mov     cx, [si + 2]
    mov     si, arr_68C2
    add     si, ax
    mov     ax, [si]
    mov     [word_2216], ax
    shl     ax, 2
    push    dx
    imul    bx
    mov     bx, dx
    pop     dx
    mov     bp, [word_633A]
    sub     bp, 2
    cmp     cx, bp
    jb      loc_9B63
    mov     cx, bp

loc_9B63:
    cmp     cx, [word_2218]
    jns     loc_9B6D
    mov     [word_2218], cx

loc_9B6D:
    mov     ax, [word_2204]
    and     ax, ax
    jz      loc_9B81
    push    dx
    imul    word [word_2216]
    mov     ax, dx
    pop     dx
    sar     ax, 5
    sub     cx, ax

loc_9B81:
    cmp     word [word_2114], 82h
    jnz     loc_9B9D
    mov     ax, [word_2216]
    shr     ax, 5
    sub     cx, ax
    js      loc_9B9D
    cmp     cx, [word_1FD4]
    jae     loc_9B9D
    mov     [word_1FD4], cx

loc_9B9D:
    cmp     word [word_2208], 0FFFEh
    jnz     loc_9BA7
    jmp     sub_9CC5

loc_9BA7:
    cmp     di, [word_2DB8]
    jz      loc_9BB6
    cmp     di, [word_2E7C]
    jz      loc_9BB6
    jmp     sub_9CC5

loc_9BB6:
    mov     bp, [word_636E]
    mov     [word_6370], bp
    shl     bp, 3
    add     [word_636E], bp
    mov     bp, bx
    neg     bp
    add     bp, 144
    sar     bp, 2
    mov     ax, [word_4026]
    cmp     ax, [word_2208]
    jz      loc_9BE9
    cmp     word [num_of_players], 0
    jz      loc_9BED
    mov     ax, [word_4120]
    cmp     ax, [word_2208]
    jnz     loc_9BED

loc_9BE9:
    add     bp, [word_2214]

loc_9BED:
    mov     ax, [word_221A]
    sar     ax, 2
    sub     bp, ax
    sar     bp, 3
    and     bp, bp
    jg      loc_9BFF
    mov     bp, 0

loc_9BFF:
    cmp     bp, 8
    jb      loc_9C07
    mov     bp, 8

loc_9C07:
    add     bp, [word_636E]
    add     bp, [word_3CE6]
    mov     bp, [ds:bp + arr306_221E]
    and     bp, 0FFh
    mov     [word_636E], bp
    cmp     word [word_639E], 0
    jz      loc_9C70
    cmp     bp, 9
    js      loc_9C70
    mov     ax, [word_2200]
    mov     bp, [word_21FE]
    shl     ax, 1
    rcl     bp, 1
    shl     ax, 1
    rcl     bp, 1
    shl     ax, 1
    rcl     bp, 1
    shl     ax, 1
    rcl     bp, 1
    mov     ax, bp
    add     ax, [word_221C]
    shr     ax, 4
    cmp     word [is_circular_track], 0
    jz      loc_9C57
    mov     si, ax
    mov     al, [si + arr_7856]
    mov     ah, 0

loc_9C57:
    shl     ax, 4
    mov     si, ax
    cmp     byte [si - 7EA0h], 0
    jns     loc_9C70
    mov     ax, [word_6370]
    mov     ah, 10
    mul     ah
    neg     ax
    mov     [cs:word_A1D2], ax

loc_9C70:
    call    sub_9CC5
    mov     word [cs:word_A1D2], 0
    ret


;
; 9C7B:
;
sub_9C7B:
    cmp     di, 0
    jz      loc_9C9E
    mov     si, [word_636E]
    mov     [word_220A], si
    shl     si, 3
    mov     es, di
    mov     ax, [es:si + 2]
    mov     [word_6362], ax
    mov     dx, [es:si + 4]
    mov     si, [es:si]
    add     si, di
    ret

loc_9C9E:
    mov     si, di
    ret


;
; 9CA1:
;
sub_9CA1:
    call    sub_9C7B
    mov     [word_636E], cx
    sub     cx, dx
    inc     cx
    mov     [word_6366], cx
    jmp     loc_9D1E


;
; 9CB1:
;
sub_9CB1:
    call    sub_9C7B
    mov     [word_636E], cx
    sub     cx, dx
    inc     cx
    mov     [word_6366], cx
    sub     bx, [word_6362]
    jmp     loc_9D1E


;
; 9CC5:
;
sub_9CC5:
    cmp     word [word_2208], 0FF00h
    jnz     loc_9CFB
    mov     word [word_2208], 0FFFFh
    call    sub_9C7B
    add     bx, 160
    mov     bp, [word_2350]
    mov     ax, dx
    shr     ax, 1
    add     bp, ax
    mov     [word_636E], bp
    dec     word [word_636E]
    sub     bp, dx
    mov     [word_6366], bp
    mov     ax, [word_6362]
    sar     ax, 1
    sub     bx, ax
    jmp     loc_9D1E

loc_9CFB:
    cmp     word [word_2208], 0FFFEh
    jnz     loc_9D05
    jmp     loc_A27F

loc_9D05:
    call    sub_9C7B
    add     bx, 160
    mov     [word_636E], cx
    sub     cx, dx
    inc     cx
    mov     [word_6366], cx
    mov     ax, [word_6362]
    sar     ax, 1
    sub     bx, ax

loc_9D1E:
    mov     [word_220C], bx
    mov     cx, bx
    add     cx, [word_6362]
    mov     [word_220E], cx
    mov     bp, [word_6366]
    mov     [word_2210], bp
    mov     bp, [word_636E]
    mov     [word_2212], bp
    cmp     word [word_2114], 0DFh
    jne     loc_9D47
    jmp     ret_9F32

loc_9D47:
    and     si, si
    jnz     loc_9D4E
    jmp     ret_9F32

loc_9D4E:
    cmp     word [word_2114], 150
    je      loc_9D61
    cmp     word [word_2114], 226
    je      loc_9D61
    jmp     loc_9E01

loc_9D61:
    push    ax
    push    bx
    push    cx
    push    dx
    push    word [word_6362]
    push    word [word_6366]
    push    word [word_636A]
    push    word [word_636E]
    push    si
    push    di
    push    word [word_637A]
    cmp     word [word_1FEE], 14h
    jns     loc_9DA1
    mov     cx, [word_220E]
    mov     word [word_6362], 140h
    mov     dx, [word_2210]
    mov     bp, [word_2212]
    mov     [word_6366], bp
    mov     word [word_2206], 10
    call    sub_A51E

loc_9DA1:
    cmp     word [word_1FD6], 0
    js      loc_9DCF
    mov     cx, [word_1FD6]
    mov     bp, [word_220E]
    add     bp, 0Fh
    and     bp, 0FFF0h
    mov     [word_6362], bp
    mov     dx, [word_1FD8]
    mov     bp, [word_1FDA]
    mov     [word_6366], bp
    mov     word [word_2206], 10
    call    sub_A51E

loc_9DCF:
    mov     bp, [word_220E]
    mov     [word_1FD6], bp
    mov     bp, [word_2210]
    mov     [word_1FD8], bp
    mov     bp, [word_2212]
    mov     [word_1FDA], bp
    pop     word [word_637A]
    pop     di
    pop     si
    pop     word [word_636E]
    pop     word [word_636A]
    pop     word [word_6366]
    pop     word [word_6362]
    pop     dx
    pop     cx
    pop     bx
    pop     ax

loc_9E01:
    pusha
    push    ds
    push    es
    mov     ds, [cs:word_5162]
    push    word [word_6352]
    push    word [word_6354]
    push    word [word_6356]
    push    word [word_6358]
    push    word [word_635A]
    push    word [word_635C]
    push    word [word_635E]
    push    word [word_6360]
    push    word [word_6362]
    push    word [word_6364]
    push    word [word_6366]
    push    word [word_6368]
    push    word [word_636A]
    push    word [word_636C]
    push    word [word_636E]
    push    word [word_6370]
    push    word [word_6372]
    push    word [word_6374]
    push    word [word_6376]
    push    word [word_6378]
    push    word [word_637A]
    push    word [word_637C]
    push    word [word_637E]
    push    word [word_6380]
    push    word [word_6382]
    push    word [word_6384]
    push    word [word_6386]
    push    word [word_6388]
    push    word [word_638A]
    push    word [word_638C]
    push    word [word_638E]
    push    word [word_6390]
    mov     ax, [word_2208]
    cmp     ax, 3
    jb      loc_9E94
    mov     ax, 0

loc_9E94:
    mov     [cs:word_A1D0], ax
    mov     ax, [word_220C]
    mov     bx, [word_220E]
    mov     cx, [word_2210]
    mov     dx, [word_2212]
    call    sub_9F33
    mov     ds, [cs:word_5162]
    pop     word [word_6390]
    pop     word [word_638E]
    pop     word [word_638C]
    pop     word [word_638A]
    pop     word [word_6388]
    pop     word [word_6386]
    pop     word [word_6384]
    pop     word [word_6382]
    pop     word [word_6380]
    pop     word [word_637E]
    pop     word [word_637C]
    pop     word [word_637A]
    pop     word [word_6378]
    pop     word [word_6376]
    pop     word [word_6374]
    pop     word [word_6372]
    pop     word [word_6370]
    pop     word [word_636E]
    pop     word [word_636C]
    pop     word [word_636A]
    pop     word [word_6368]
    pop     word [word_6366]
    pop     word [word_6364]
    pop     word [word_6362]
    pop     word [word_6360]
    pop     word [word_635E]
    pop     word [word_635C]
    pop     word [word_635A]
    pop     word [word_6358]
    pop     word [word_6356]
    pop     word [word_6354]
    pop     word [word_6352]
    pop     es
    pop     ds
    popa

ret_9F32:
    ret


;
; 9F33:
;
sub_9F33:
    cmp     ax, 320
    jl      loc_9F3B
    jmp     ret_A061

loc_9F3B:
    cmp     bx, 0
    jg      loc_9F43
    jmp     ret_A061

loc_9F43:
    cmp     cx, [word_2218]
    jl      loc_9F4C
    jmp     ret_A061

loc_9F4C:
    cmp     dx, 0
    jg      loc_9F54
    jmp     ret_A061

loc_9F54:
    mov     bp, bx
    sub     bp, ax
    add     bp, 7
    shr     bp, 3
    jnz     loc_9F63
    jmp     ret_A061

loc_9F63:
    mov     [cs:word_A1CC], bp
    mov     bp, 0
    mov     di, 0
    cmp     ax, 0FFF8h
    jg      loc_9F7D

loc_9F73:
    add     ax, 8
    inc     bp
    inc     di
    cmp     ax, 0FFF8h
    jle     loc_9F73

loc_9F7D:
    cmp     bx, 328
    jl      loc_9F8D

loc_9F83:
    sub     bx, 8
    inc     di
    cmp     bx, 328
    jge     loc_9F83

loc_9F8D:
    cmp     cx, 0
    jge     loc_9FA1
    xchg    ax, cx
    neg     ax
    mul     byte [cs:word_A1CC]
    add     bp, ax
    mov     ax, cx
    mov     cx, 0

loc_9FA1:
    cmp     dx, [word_2218]
    jle     loc_9FAB
    mov     dx, [word_2218]

loc_9FAB:
    mov     [cs:word_A1CE], di
    sub     [cs:word_A1CC], di
    jg      loc_9FBA
    jmp     ret_A061

loc_9FBA:
    sub     dx, cx
    jge     loc_9FC1
    jmp     ret_A061

loc_9FC1:
    inc     dx
    mov     di, 550h
    add     di, ax
    mov     al, 168
    mul     cl
    mov     cx, ax
    shl     ax, 1
    and     ax, 0Fh
    add     di, ax
    mov     ax, di
    and     di, 0Fh
    shr     ax, 4
    shr     cx, 3
    add     ax, cx
    add     ax, [word_63BC]
    mov     es, ax
    mov     [word_2352], di
    mov     [word_2354], es
    mov     ds, si
    mov     si, 0
    mov     cx, bp
    jcxz    loc_A005
    mov     ah, 0

loc_9FFA:
    lodsb
    mov     bp, ax
    mov     al, [bp + 0C00h]
    add     si, ax
    loop    loc_9FFA

loc_A005:
    mov     ch, dl
    mov     dx, [cs:word_A1CC]
    shl     dx, 3
    neg     dx
    add     dx, 336
    mov     bx, [cs:word_A1D2]
    and     bx, bx
    jz      loc_A021
    jmp     loc_A106

loc_A021:
    mov     bx, [cs:word_A1D0]
    and     bx, bx
    jnz     loc_A062
    mov     bx, loc_A04E
    cmp     word [cs:word_A1CE], 0
    jz      loc_A054
    mov     bx, loc_A03A
    jmp     loc_A054

loc_A03A:
    mov     cl, byte [cs:word_A1CE]
    mov     ah, 0

loc_A041:
    lodsb
    mov     bp, ax
    mov     al, [bp + 0C00h]
    add     si, ax
    dec     cl
    jne     loc_A041

loc_A04E:
    add     di, dx
    dec     ch
    je      ret_A061

loc_A054:
    mov     cl, byte [cs:word_A1CC]
    mov     ah, 0
    lodsb
    shl     ax, 5                      ; 0x7F0B * 32
    jmp     ax                         ; TODO: 0x7F0E

ret_A061:
    ret


loc_A062:
    xchg    bl, bh
    add     bx, 0D00h

loc_A068:
    mov     cl, [cs:word_A1CC]

loc_A06D:
    lodsb
    mov     ah, al
    shl     ah, 1
    jae     loc_A07D
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    mov     [es:di], al

loc_A07D:
    inc     di
    shl     ah, 1
    jae     loc_A08B
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    mov     [es:di], al

loc_A08B:
    inc     di
    shl     ah, 1
    jae     loc_A099
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    mov     [es:di], al

loc_A099:
    inc     di
    shl     ah, 1
    jae     loc_A0A7
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    mov     [es:di], al

loc_A0A7:
    inc     di
    shl     ah, 1
    jae     loc_A0B5
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    mov     [es:di], al

loc_A0B5:
    inc     di
    shl     ah, 1
    jae     loc_A0C3
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    mov     [es:di], al

loc_A0C3:
    inc     di
    shl     ah, 1
    jae     loc_A0D1
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    mov     [es:di], al

loc_A0D1:
    inc     di
    shl     ah, 1
    jae     loc_A0DF
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    mov     [es:di], al

loc_A0DF:
    inc     di
    dec     cl
    jnz     loc_A06D
    mov     cl, [cs:word_A1CE]
    and     cl, cl
    jz      loc_A0FC
    mov     ah, 0

loc_A0EF:
    lodsb
    mov     bp, ax
    mov     al, [bp + 0C00h]
    add     si, ax
    dec     cl
    jnz     loc_A0EF

loc_A0FC:
    add     di, dx
    dec     ch
    jz      ret_A105
    jmp     loc_A068

ret_A105:
    ret

loc_A106:
    mov     [cs:word_A1D4], dx
    mov     dx, bx
    mov     bx, [cs:word_A1D0]
    xchg    bl, bh
    add     bx, 0D00h

loc_A118:
    mov     cl, [cs:word_A1CC]

loc_A11D:
    lodsb
    mov     ah, al
    shl     ah, 1
    jae     loc_A12F
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    add     al, dl
    mov     [es:di], al

loc_A12F:
    inc     di
    shl     ah, 1
    jae     loc_A13F
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    add     al, dl
    mov     [es:di], al

loc_A13F:
    inc     di
    shl     ah, 1
    jae     loc_A14F
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    add     al, dl
    mov     [es:di], al

loc_A14F:
    inc     di
    shl     ah, 1
    jae     loc_A15F
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    add     al, dl
    mov     [es:di], al

loc_A15F:
    inc     di
    shl     ah, 1
    jae     loc_A16F
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    add     al, dl
    mov     [es:di], al

loc_A16F:
    inc     di
    shl     ah, 1
    jae     loc_A17F
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    add     al, dl
    mov     [es:di], al

loc_A17F:
    inc     di
    shl     ah, 1
    jae     loc_A18F
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    add     al, dl
    mov     [es:di], al

loc_A18F:
    inc     di
    shl     ah, 1
    jae     loc_A19F
    lodsb
    mov     bl, al
    mov     al, [ss:bx]
    add     al, dl
    mov     [es:di], al

loc_A19F:
    inc     di
    dec     cl
    jz      loc_A1A7
    jmp     loc_A11D

loc_A1A7:
    mov     cl, [cs:word_A1CE]
    and     cl, cl
    jz      loc_A1BF
    mov     ah, 0

loc_A1B2:
    lodsb
    mov     bp, ax
    mov     al, [bp + 0C00h]
    add     si, ax
    dec     cl
    jnz     loc_A1B2

loc_A1BF:
    add     di, [cs:word_A1D4]
    dec     ch
    jz      ret_A1CB
    jmp     loc_A118

ret_A1CB:
    ret
