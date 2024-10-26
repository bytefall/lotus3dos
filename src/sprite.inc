;
; C047: Draw a sprite
;
; input:
; (ax, bx) - (width, height)
; si - source of data (si:0000)
; di - (y coord on a screen) * 336
;
draw_sprite:
    push    ds
    mov     es, [word_63BC]
    add     di, VGA_DBL_BUF_START
    mov     ds, si
    mov     si, 0
    shr     ax, 1

for_each_height1:
    and     di, di
    jns     loc_C067
    mov     cx, es
    add     cx, 2048
    mov     es, cx
    sub     di, 32768                  ; 320 * 200 + 256 * 3

loc_C067:
    mov     cx, ax
    push    di
    rep movsw
    pop     di
    add     di, 336
    dec     bx
    jnz     for_each_height1
    pop     ds
    ret


;
; C076: Draw a single character
;
; input:
; ax - width
; bx - height
; si - segment of characted data (si:0)
;
draw_char:
    push    ds
    mov     es, [word_63BC]
    add     di, VGA_DBL_BUF_START
    mov     ds, si
    mov     si, 0
    mov     bp, ax

for_each_height2:
    and     di, di
    jns     loc_C096
    mov     cx, es
    add     cx, 2048
    mov     es, cx
    sub     di, 32768

loc_C096:
    mov     cx, bp
    push    di

for_each_width2:
    lodsb
    or      [es:di], al
    inc     di
    loop    for_each_width2
    pop     di
    add     di, 336
    dec     bx
    jnz     for_each_height2
    pop     ds
    ret


;
; C0AA: Get B{track_num} data with palette.
;
; input:
; track_num - track number
;
; output:
; word_2AFC:0 - data
; word_63BA:0 - palette
; vec_7556 - palette copy
; word_1F99 - length / 640
;
sub_C0AA:
    mov     ax, [word_63BA]
    mov     [word_2AFC], ax            ; B0X resource
    mov     ax, [track_num]
    mov     ah, 'B'
    call    res_load

    sub     ax, 48                     ; 48 * 16 = 768
    mov     [word_63BA], ax            ; word_63BA = ax = *(tail - 768)
    sub     ax, [word_2AFC]            ; B0X resource
    cwd
    mov     bp, 40                     ; 40 * 16 = 640
    div     bp
    mov     [word_1F99], ax            ; word_1F99 = ax / 640
    push    ds
    push    ds
    pop     es
    mov     di, palette
    mov     ds, [word_63BA]
    mov     si, 0
    mov     cx, 768
    rep movsb
    pop     ds
    ret


;
; C0DF:
;
sub_C0DF:
    mov     ax, [word_63BA]
    mov     [word_6330], ax
    call    sub_C1CB
    mov     di, arr_63C2
    mov     cx, 512
    mov     ax, 0
    push    ds
    pop     es
    rep stosw
    les     si, [word_632E]            ; load es:si
    mov     ax, [word_2AB6]            ; P03
    mov     [word_633E], ax
    mov     [word_6340], ax
    mov     word [word_6344], 0
    mov     word [word_6342], 8

loc_C10E:
    call    sub_C155
    inc     byte [word_6342]
    jnz     loc_C10E
    mov     ax, [word_2AB6]    ; P03
    mov     [word_633E], ax
    add     ax, 10
    mov     [word_6340], ax
    mov     word [word_6344], 512
    mov     word [word_6346], 0

loc_C12F:
    mov     bx, [word_6346]
    shl     bx, 1
    mov     ax, [bx + arr_5ED0]
    mov     [word_6342], ax
    call    sub_C155
    inc     word [word_6346]
    cmp     word [word_6346], ARR_5ED0_LEN
    jnz     loc_C12F
    add     si, 15
    shr     si, 4
    add     [word_63BA], si
    ret


;
; C155:
;
; in:
; word_4A2A -
; word_6340 -
; word_6342 -
; word_6344 -
;
sub_C155:
    mov     bx, [word_6342]
    shl     bx, 1
    add     bx, [word_6344]
    mov     [arr_63C2 + bx], si
    mov     ax, 32
    mov     dx, 0
    div     word [word_6342]
    mov     word [word_6354], ax
    mov     ax, 0
    div     word [word_6342]
    mov     word [word_6352], ax
    mov     di, [word_4A2A]
    mov     dx, 0
    mov     bp, 0
    mov     ax, di
    add     ax, [word_6340]
    mov     [word_6366], ax
    add     si, 2

loc_C190:
    mov     bx, bp
    mov     cl, bl
    and     cl, 3
    shl     cl, 1
    mov     al, [di]
    ror     al, 2
    mov     ah, 3Fh
    ror     al, cl
    ror     ah, cl
    shr     bx, 2
    and     ah, [es:bx + si]
    or      al, ah
    mov     [es:bx + si], al
    inc     bp
    add     dx, [word_6352]
    adc     di, [word_6354]
    cmp     di, [word_6366]
    jb      loc_C190
    mov     [es:si - 2], bp
    add     bp, 3
    shr     bp, 2
    add     si, bp
    ret


;
; C1CB:
;
sub_C1CB:
    push    ds
    pop     es
    mov     di, palette
    mov     cx, 768
    mov     al, 3Fh                    ; scan pallete for value 0x3F
    repne scasb
    dec     di
    mov     [palette_ptr], di          ; position of 0x3F in palette
    mov     ax, di
    sub     ax, palette
    mov     cl, 3
    div     cl
    mov     [byte_2B00], al            ; byte_2B00 = num of colors
    mov     word [word_2B02], arr_2B04
    mov     word [word_2C24], arr_2C26
    mov     word [word_632E], 0
    mov     si, [word_54CE]
    mov     dx, 32
    cmp     word [word_6398], 0
    jz      loc_C20B
    mov     dx, 288

loc_C20B:
    lodsw
    jmp     loc_C21D

loc_C20E:
    mov     di, [word_54CE]
    mov     cx, si
    sub     cx, di
    shr     cx, 1
    lodsw
    repne scasw
    jz      loc_C231

loc_C21D:
    mov     di, [palette_ptr]
    call    sub_C2A8
    mov     [palette_ptr], di
    mov     al, [byte_2B00]
    inc     byte [byte_2B00]           ; increment since in sub_C2A8 we've added 3 more colors
    jmp     loc_C23E

loc_C231:
    sub     di, 2
    sub     di, [word_54CE]
    shr     di, 1
    mov     al, [arr_2B04 + di]

loc_C23E:
    mov     di, [word_2B02]
    stosb                              ; arr_2B04[i++] = al;
    mov     [word_2B02], di
    mov     al, dl
    and     al, 3
    cmp     al, 2
    jnz     loc_C255
    lodsw
    inc     word [word_2B02]
    dec     dx

loc_C255:
    dec     dx
    jnz     loc_C20E
    mov     cx, 8                      ; cx = if word_6398 == 0 { 8 } else { 72 };
    cmp     word [word_6398], 0
    jz      loc_C265
    mov     cx, 72

loc_C265:
    mov     bx, arr_2B04
    jmp     loc_C282

loc_C26A:
    mov     ax, [bx]
    mov     dx, [bx + 2]
    mov     si, arr_2B04

loc_C272:
    cmp     ax, [si]
    jnz     loc_C27B
    cmp     dx, [si + 2]
    jz      loc_C28D

loc_C27B:
    add     si, 4
    cmp     si, bx
    jb      loc_C272

loc_C282:
    mov     ax, [word_632E]
    shr     ax, 10
    call    sub_C2C2
    jmp     loc_C298

loc_C28D:
    sub     si, arr_2B04
    shr     si, 2
    mov     al, [si + arr_2C26]

loc_C298:
    mov     di, [word_2C24]
    stosb
    mov     [word_2C24], di
    add     bx, 4
    loop    loc_C26A
    ret
    ret


;
; C2A8:
;
; di[r] = ((ax >> 8) & 0xF) << 2;
; di[g] = ((ax as u8) >> 4) << 2;
; di[b] = ((ax as u8) & 0xF) << 2;
;
sub_C2A8:
    xchg    al, ah
    and     al, 0Fh
    shl     al, 2
    stosb
    mov     al, ah
    shr     al, 4
    shl     al, 2
    stosb
    mov     al, ah
    and     al, 0Fh
    shl     al, 2
    stosb
    ret


;
; C2C2:
;
sub_C2C2:
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
    les     di, [word_632E]
    mov     dl, 0

loc_C350:
    mov     dh, dl
    rol     dh, 2
    mov     al, dh
    and     al, 3
    xlatb
    stosb
    rol     dh, 2
    mov     al, dh
    and     al, 3
    xlatb
    stosb
    rol     dh, 2
    mov     al, dh
    and     al, 3
    xlatb
    stosb
    rol     dh, 2
    mov     al, dh
    and     al, 3
    xlatb
    stosb
    inc     dl
    jnz     loc_C350
    mov     al, [bx]
    mov     ah, al
    mov     cx, ax
    cmp     word [word_63B4], 0
    jz      loc_C38F
    mov     cl, [bx + 2]
    mov     ch, cl
    mov     ax, 505h

loc_C38F:
    mov     [es:di - 8], ax
    mov     [es:di - 6], ax
    mov     [es:di - 4], cx
    mov     [es:di - 2], cx
    mov     [word_632E], di
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
    ret
