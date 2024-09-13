;
; 30DF:
;
show_gremlin:
    call    fade_out
    mov     ax, [cs:word_5166]
    mov     [word_63BA], ax
    mov     al, 0
    mov     ah, 'Q'
    call    sub_CBC3
    xchg    ax, [word_63BA]
    call    res_unpack_with_pal
    mov     si, [word_63BA]
    mov     di, 0
    mov     ax, 320
    mov     bx, 200

loc_3104:
    call    draw_sprite
    mov     al, 1
    mov     ah, 'Q'
    call    res_load
    call    update_screen
    call    fade_in
    mov     word [word_3E18], 0
    mov     ax, 280
    call    sleep
    mov     word [word_3E18], 0

loc_3126:
    call    sub_D6F9
    mov     ax, [word_3E18]
    shr     ax, 5
    cmp     ax, 7
    jnb     loc_3158
    cmp     ax, 4
    jb      loc_313E
    neg     ax
    add     ax, 6

loc_313E:
    shl     ax, 3
    add     ax, [word_63BA]
    mov     si, ax
    mov     di, 85 * 336 + 112
    mov     ax, 16
    mov     bx, 8
    call    draw_sprite
    call    update_screen
    jmp     loc_3126

loc_3158:
    mov     word [word_3E18], 0
    mov     ax, 140
    call    sleep
    mov     word [word_3E18], 0

loc_316A:
    call    sub_D6F9
    mov     ax, [word_3E18]            ; on every cycle word_3E18 is changing somewhere
    shr     ax, 5
    cmp     ax, 7
    jnb     loc_319F
    cmp     ax, 4
    jb      loc_3182
    neg     ax                         ; when ax >= 4
    add     ax, 6

loc_3182:
    add     ax, 4                      ; + 4
    shl     ax, 3                      ; * 8
    add     ax, [word_63BA]
    mov     si, ax                     ; si = &word_63BA[(ax + 4) * 8]
    mov     di, 37104                  ; y = 37104 / 336 = 110
    mov     ax, 16
    mov     bx, 8
    call    draw_sprite
    call    update_screen
    jmp     loc_316A

loc_319F:
    mov     word [word_3E18], 0
    ret


;
; 31A6:
;
show_magnetic_fields:
    mov     ax, [cs:word_5166]
    mov     [word_63BA], ax
    mov     si, magn_fields_ids
    mov     di, magn_fields_ptr
    mov     ah, 'Q'
    call    load_resource_series
    mov     ax, 280
    call    sleep
    call    fade_out
    mov     ax, [magn_fields_ptr + 21 * 2] ; last resource's (0x17) data
    call    res_unpack_with_pal
    call    sub_92A4
    call    update_screen
    mov     si, palette
    call    sub_D18C
    mov     word [word_3E18], 0
    mov     cx, 0

loc_31DC:
    call    sub_D6F9
    mov     ax, [word_3E18]
    shr     ax, 3
    cmp     ax, cx
    jz      loc_31DC
    push    ax
    cmp     al, 20
    jb      loc_31F0
    mov     al, 20

loc_31F0:
    mov     bx, ax
    shl     bx, 1
    mov     ax, [magn_fields_ptr + bx]
    call    res_unpack_simple
    mov     si, [word_63BA]
    mov     di, 0
    mov     ax, 320
    mov     bx, 200
    call    draw_sprite
    call    update_screen
    pop     cx
    cmp     cx, 20
    jb      loc_31DC

    mov     ax, [magn_fields_ptr + 21 * 2] ; last resource's Q17 data
    call    res_unpack_simple
    mov     si, [word_63BA]
    mov     di, 0
    mov     ax, 320
    mov     bx, 200
    call    draw_sprite
    call    update_screen
    mov     word [word_3E18], 0
    mov     ax, 1120
    call    sleep
    call    fade_out
    ret


;
; 323D:
;
show_credits:
    mov     ax, [cs:word_5166]
    mov     [word_63BA], ax
    mov     si, credits_ids
    mov     di, credits_ptr
    mov     ah, 'Q'
    call    load_resources
    call    fade_out
    mov     ax, [credits_ptr + 2]
    sub     ax, 48
    push    ds
    push    ds
    pop     es
    mov     di, palette
    mov     ds, ax
    mov     si, 0
    mov     cx, 768
    rep movsb
    pop     ds
    call    sub_33E6
    mov     si, [credits_ptr]
    mov     di, 0
    mov     ax, 320
    mov     bx, 200
    call    draw_sprite
    call    update_screen
    call    fade_in
    mov     word [word_3E18], 0
    mov     al, 1Ah
    mov     ah, 'Q'
    call    res_load
    mov     ax, 280
    call    sleep
    mov     si, credits_txt            ; E6 38 "A GAME" 00 82 58 "BY" ...

for_each_line:
    call    draw_credits               ; ds:si -- [[x, y, "text", 0], .., 0xFFFF]
    cmp     word [si], 0FFFFh
    jne     for_each_line

    call    draw_car_approaching
    mov     ax, [credits_ptr + 4]      ; "Q1C"
    call    sub_32E2
    mov     ax, [credits_ptr + 6]      ; "Q1D"
    call    sub_32E2
    mov     ax, [credits_ptr + 8]      ; "Q1E"
    call    sub_32E2
    mov     word [word_3E18], 0
    mov     ax, 560
    call    sleep
    mov     word [palette + 60 * 3], 0
    mov     byte [palette + 60 * 3 + 2], 0
    mov     si, palette
    mov     word [word_3D6C], 140
    call    fade_by_color
    call    sub_D161
    mov     word [word_3E18], 0
    ret


;
; 32E2:
;
sub_32E2:
    mov     si, ax
    mov     word [word_3E18], 0
    mov     ax, 32
    call    sleep
    mov     di, 0
    mov     ax, 320
    mov     bx, 200
    call    draw_sprite
    call    update_screen
    ret


;
; 3300: Draws animation with a car that is approaching.
;
; in:
; credits_ptr - background image
; word_E3A - car images (from Q1B)
;
draw_car_approaching:
    mov     word [word_3E18], 0
    mov     bx, 0

loc_3309:
    call    sub_D6F9
    mov     ax, [word_3E18]
    shr     ax, 5
    cmp     ax, bx
    jz      loc_3309
    cmp     ax, 36                     ; ax = 1
    jb      loc_331E
    mov     ax, 36

loc_331E:
    push    ax
    mov     si, [credits_ptr]
    mov     di, 0
    mov     ax, 320
    mov     bx, 200
    call    draw_sprite
    pop     ax
    push    ax                         ; ax = 1, 2, 3...
    call    draw_a_car
    call    update_screen
    pop     bx
    cmp     bx, 36
    jb      loc_3309
    ret


;
; 333E: Draw a car (when car is approaching in the intro)
;
; input:
; ax - step (1..=36)
; word_E3A -
;
draw_a_car:
    neg     ax
    add     ax, 36
    mov     dx, 512
    mul     dx
    add     ax, 256
    mov     cx, ax                     ; cx = (36 - ax) * 512 + 256
    mov     dx, 0
    mov     ax, 57344
    div     cx                         ; ax = ((336 * 170) + 224) / cx
    shr     ax, 1
    mov     di, 160
    sub     di, ax
    add     di, 21504                  ; di = 160 - (ax >> 1) + (336 * 64)
    mov     dx, 0
    mov     ax, 39936
    div     cx                         ; ax = ((336 * 118) + 288) / cx
    mov     dx, 10922
    mul     dx
    mov     ax, 336
    mul     dx
    sub     di, ax                     ; di = di - (eax * (336 * 32 + 170)) >> 16 * 336
    push    ds
    add     di, VGA_DBL_BUF_START
    ;
    ; shift top left start pixel of a car
    mov     ax, di                     ; ax = di
    and     di, 15                     ; di = di & 0xF
    shr     ax, 4
    add     ax, [word_63BC]
    mov     es, ax                     ; es = ax >> 4 + video_mem_offset
    mov     ds, [credits_ptr + 2]      ; "Q1B"
    mov     si, 0
    mov     dx, 0

loc_3391:
    push    di
    mov     al, 224
    mul     dh
    mov     si, ax                     ; si = dh * 224
    mov     ah, 0
    lea     bp, [si + 224]
    mov     bl, ch
    mov     bh, 0                      ; bx = cx >> 8

loc_33A2:
    mov     al, [si]
    cmp     al, 0FFh
    je      loc_33AB
    mov     [es:di], al                ; draw a pixel

loc_33AB:
    inc     di
    add     ah, cl                     ; ah += cx & 0xFF
    adc     si, bx                     ; si += bx
    ;
    ; it looks like there is no case when CF = 1,
    ; so in the source code "adc" is treated as "add"
    cmp     si, bp
    jb      loc_33A2
    pop     di
    add     di, 336                    ; y += 336
    add     dx, cx
    cmp     dh, 9Ch                    ; while dx < (336 * 118)
    jb      loc_3391
    pop     ds
    ret


;
; 33C2: when commented out - then text is fully transparent
;
; for row in pal.chunks_exact_mut(12).take(11 * 3) {
;     row[3] = 0x30;
;     row[4] = 0x30;
;     row[5] = 0x30;
;     row[6] = 0x20;
;     row[7] = 0x20;
;     row[8] = 0x20;
;     row[9] = 0;
;     row[10] = 0;
;     row[11] = 0;
; }
;
set_text_palette:
    mov     si, palette
    mov     cx, 32

loc_33C8:
    mov     word [si + 3], 3030h
    mov     word [si + 5], 2030h
    mov     word [si + 7], 2020h
    mov     word [si + 9], 0
    mov     byte [si + 11], 0
    add     si, 12
    loop    loc_33C8
    ret


;
; 33E6: fade-in / fade-out font
;
; for row in pal.chunks_exact_mut(12).take(11 * 3) {
;     let (r, g, b) = (row[0], row[1], row[2]);
; 
;     row[3] = r;
;     row[4] = g;
;     row[5] = b;
; 
;     row[6] = r;
;     row[7] = g;
;     row[8] = b;
; 
;     row[9] = r;
;     row[10] = g;
;     row[11] = b;
; }
;
sub_33E6:
    mov     si, palette
    mov     cx, 32

loc_33EC:
    mov     ax, [si]
    mov     [si + 3], ax
    mov     [si + 6], ax
    mov     [si + 9], ax
    mov     al, [si + 2]
    mov     [si + 5], al
    mov     [si + 8], al
    mov     [si + 11], al
    add     si, 12
    loop    loc_33EC
    ret


;
; 3409:
;
clear_text_texture:
    push    ds
    mov     ds, [word_63BC]
    mov     di, VGA_DBL_BUF_START 
    mov     cx, 32768                  ; 320 x 200 + 255 * 3

loc_3414:
    and     word [di], 0FCFCh
    add     di, 2
    loop    loc_3414
    pop     ds
    ret


;
; 341F:
;
draw_text_large:
    lodsw
    cmp     ax, 0EC78h
    ja      ret_346C
    mov     di, ax

loc_3427:
    lodsb
    cmp     al, 0
    jz      draw_text_large            ; is end of string
    cmp     al, ' '
    jz      loc_3467                   ; is space
    cmp     al, '.'
    jnz     loc_3438
    mov     al, 36
    jmp     loc_3450

loc_3438:
    cmp     al, '('
    jnz     loc_3440
    mov     al, 37
    jmp     loc_3450

loc_3440:
    cmp     al, ')'
    jnz     loc_3448
    mov     al, 38
    jmp     loc_3450

loc_3448:
    sub     al, 30h
    cmp     al, 0Ah
    jb      loc_3450
    sub     al, 7

loc_3450:
    push    si
    push    di
    mov     ah, 18
    mul     ah
    mov     si, [word_63BA]
    add     si, ax                     ; offset of letter in loaded resource data "Q1A"
    mov     ax, 16
    mov     bx, 18
    call    draw_char
    pop     di
    pop     si

loc_3467:
    add     di, 14
    jmp     loc_3427

ret_346C:
    ret


;
; 346D:
;
; ds:si -- [[x, y, "text", 0], .., 0xFFFF]
;
draw_credits:
    push    si
    call    clear_text_texture
    pop     si
    call    draw_text_large
    push    si
    push    ax
    call    update_screen
    call    set_text_palette           ; when commented out - then text is fully transparent
    mov     si, palette                ; fade in a text
    call    fade_by_color
    call    sub_D161
    mov     word [word_3E18], 0
    pop     ax
    neg     ax
    call    sleep
    call    sub_33E6
    mov     si, palette
    call    fade_by_color
    call    sub_D161
    mov     word [word_3E18], 0
    mov     ax, 280
    call    sleep
    pop     si
    ret


;
; 34AC:
;
show_lotus_logo:
    cmp     word [word_1F20], 0
    jnz     alt_lotus_logo
    jmp     default_logo

alt_lotus_logo:
    mov     word [word_1F20], 0        ; alternative Lotus logo appearance
    ; (shows "LOTUS" and fades in "The Ultimate Challenge")
    mov     ax, [cs:word_5166]
    mov     [word_63BA], ax
    mov     al, 18h                    ; LOTUS The Ultimate Challenge
    mov     ah, 'Q'
    call    res_load
    sub     ax, 30h
    mov     [word_F77], ax
    call    sub_92A4
    mov     si, [word_63BA]
    mov     di, 0
    mov     ax, 320
    mov     bx, 200
    call    draw_sprite
    mov     ax, 560
    call    sleep
    mov     si, palette2
    call    sub_D18C
    call    update_screen
    mov     cx, 10h
    call    sub_352C
    mov     si, palette
    call    sub_D18C
    mov     word [word_3E18], 0
    mov     ax, 560
    call    sleep
    mov     cx, 30h
    call    sub_352C
    mov     word [word_3D6C], 140
    mov     si, palette
    call    fade_by_color
    call    sub_D161
    mov     word [word_3E18], 0
    mov     ax, 1400
    call    sleep
    ret
