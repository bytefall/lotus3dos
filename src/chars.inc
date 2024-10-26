;
; C42C: Load bmp from Sxx
;
sub_C42C:
    mov     bx, 0

loc_C42F:
    push    bx
    mov     si, [word_6040]
    mov     al, [bx + si]
    mov     ah, 0
    cmp     al, 0
    jnz     loc_C43F
    jmp     loc_C4E6

loc_C43F:
    cmp     al, 196
    jnz     loc_C446
    jmp     loc_C4E6

loc_C446:
    cmp     al, 128
    jnb     loc_C44D
    jmp     loc_C4E6

loc_C44D:
    cmp     al, 144
    jb      loc_C45F
    cmp     al, 146
    ja      loc_C45F
    cmp     word [word_3EE4], 0
    jnz     loc_C45F
    jmp     loc_C4E6

loc_C45F:
    cmp     al, 173
    jnz     loc_C466
    jmp     loc_C4E6

loc_C466:
    cmp     al, 248
    jnz     loc_C46F
    call    sub_C68D
    jmp     loc_C4E6

loc_C46F:
    cmp     al, 249
    jnz     loc_C478
    call    sub_C794
    jmp     loc_C4E6

loc_C478:
    mov     cx, [word_63BA]
    mov     [word_2E76], cx
    mov     bx, ax
    shl     bx, 1
    mov     [bx + word_2C76], cx
    cmp     al, 240
    jb      loc_C4A5
    cmp     al, 247
    ja      loc_C4A5
    push    ax
    sub     al, 240
    mov     bx, ax
    mov     bl, [bx + word_2C6E]
    shl     bx, 1
    mov     ax, [bx + word_2C76]
    call    sub_C5E3
    pop     ax
    jmp     loc_C4B2

loc_C4A5:
    push    ax
    mov     ah, 'S'                    ; [88,89,8A,96,DF,E2,E3,E4,E5,84], 80,81,C6
    mov     word [word_2E78], 240
    call    bmp_load_and_prepare
    pop     ax

loc_C4B2:
    cmp     al, 223
    jnz     loc_C4CA
    mov     cx, [word_63BA]
    mov     [word_1F9D], cx
    mov     ah, 'E'
    mov     al, 0
    call    res_load
    mov     [word_63BA], ax
    jmp     loc_C4E6

loc_C4CA:
    sub     al, 128
    cmp     al, 112
    jnb     loc_C4E6
    mov     si, ax
    mov     es, [word_2E76]
    mov     al, [es:2]
    mov     ah, [es:4]
    shl     si, 2
    mov     [si + arr_2674], ax

loc_C4E6:
    call    sub_DC4F
    pop     bx
    inc     bx
    cmp     bl, 24
    jnb     loc_C4F3
    jmp     loc_C42F

loc_C4F3:
    call    sub_C83D
    ret


;
; C4F7:
;
; let mut vec_2D76: Vec<u16> = Vec::new();
; vec_2D76.resize(128, 0);
;
sub_C4F7:
    push    ds
    pop     es
    mov     di, word_2D76
    mov     cx, 128
    mov     ax, 0
    rep stosw
    ret


;
; C505: Loads a bitmap resource from DAT-file and prepares it.
;
; [Bitmap::from(...)]
;
; in:
; ah - resource prefix ASCII character ('C', 'S', etc)
; al - resource index (05, 88, E2)
; word_2E78 -
;
; out:
; es:0 - result data
;
bmp_load_and_prepare:
    push    word [word_63BA]
    add     word [word_63BA], 4096
    call    res_load
    pop     word [word_63BA]
    push    ds
    mov     ax, [word_63BA]
    mov     es, ax                     ; es:0 - result data
    add     ax, 4096
    mov     ds, ax                     ; ds:0 - unpacked "C03" data
    mov     si, 0
    mov     di, si

more_chunks:                           ; C526
    mov     cx, 4
    rep movsw                          ; copy chunks of 8 bytes to es:di
    cmp     byte [si - 1], 0FFh
    jnz     more_chunks
    test    di, 8
    jz      skip_extra_bytes
    mov     cx, 4                      ; when di = 0x18, 0x88
    rep movsw

skip_extra_bytes:                      ; C53C
    mov     bx, 0

loop_C53F:
    call    sub_C557
    add     bx, 8
    cmp     byte [bx - 1], 0FFh
    jnz     loop_C53F
    pop     ds
    add     di, 15
    shr     di, 4
    add     [word_63BA], di            ; word_63BA:0 - empty segment after unpacked data (es:0)
    ;
    ; edi << 4 - length of data
    ret


;
; C557:
;
; in:
; bx -
; es - target data
; di - moved data length
; ds - source data
;
sub_C557:
    mov     ax, di
    shr     ax, 4
    mov     [es:bx], ax
    push    ds

loc_C560:
    mov     ax, data_seg
    mov     ds, ax
    mov     ax, [word_2E78]
    cmp     ah, 0

loc_C56B:
    jz      skip_C578
    mov     si, bx
    shr     si, 3
    add     si, [word_2E7A]
    add     al, [si]

skip_C578:
    pop     ds
    mov     [cs:byte_C5E2], al
    mov     si, [bx]
    shl     si, 4
    mov     bp, 1

loop2_C585:
    mov     dx, [bx + 2]

loop3_C588:
    mov     cx, 8
    cmp     cx, dx
    jbe     loc_C591
    mov     cx, dx

loc_C591:
    sub     dx, cx
    call    sub_C5B0
    and     dx, dx
    jnz     loop3_C588                 ; if(dx > 0) goto loc_C588;
    dec     word [bx + 4]
    jnz     loop2_C585
    mov     cx, di
    and     cx, 0Fh
    jz      ret_C5AF
    neg     cx
    add     cx, 16
    mov     al, 0
    rep stosb                          ; for _ in 0..(16 - buffer.len() % 16) { buffer.push(0); }

ret_C5AF:
    ret


;
; C5B0:
;
; in:
; di - target data ptr
; cl - counter
;
sub_C5B0:
    push    bx
    push    dx
    push    di
    mov     dl, [bx + 6]
    mov     dh, 0
    mov     ch, [cs:byte_C5E2]
    mov     ax, 8000h
    stosb

loc_C5C1:
    lodsb                              ; for _ in 0..cl {
    neg     bp
    jns     loc_C5CA
    dec     si
    shr     al, 4

loc_C5CA:
    and     al, 0Fh
    cmp     al, dl
    jz      loc_C5D5
    add     al, ch
    stosb
    or      dh, ah

loc_C5D5:
    shr     ah, 1
    dec     cl
    jnz     loc_C5C1                   ; }
    pop     bx
    mov     [es:bx], dh
    pop     dx
    pop     bx
    ret


byte_C5E2:  db 0


;
; C5E3:
;
sub_C5E3:
    push    ds
    mov     es, [word_63BA]
    mov     ds, ax
    mov     cx, [0]
    shl     cx, 3
    mov     si, 0
    mov     di, 0
    rep movsw
    mov     bx, 0

loc_C5FC:
    cmp     byte [bx + 7], 0FFh
    jz      loc_C60A
    call    sub_C616
    add     bx, 8
    jmp     loc_C5FC

loc_C60A:
    add     di, 0Fh
    shr     di, 4
    pop     ds
    add     [word_63BA], di
    ret


;
; C616:
;
sub_C616:
    mov     si, [bx]
    shl     si, 4
    mov     di, si
    mov     ax, [bx + 2]
    add     ax, 7
    shr     ax, 3
    mov     [cs:word_A1CC], ax
    mov     cx, [bx + 4]

loc_C62D:
    push    bx
    push    cx
    call    sub_C63F
    pop     cx
    pop     bx
    loop    loc_C62D
    mov     ax, 0
    mov     cx, 8
    rep stosw
    ret


;
; C63F:
;
sub_C63F:
    push    di
    mov     di, 0FF30h
    mov     ax, 0
    mov     cx, 4
    rep stosw
    mov     dx, [cs:word_A1CC]

loc_C650:
    lodsb
    mov     ah, al
    mov     cx, 8

loc_C656:
    mov     al, 0
    shl     ah, 1
    jnb     loc_C65D
    lodsb

loc_C65D:
    stosb
    loop    loc_C656
    dec     dx
    jnz     loc_C650
    pop     di
    push    si
    push    ds
    mov     si, [bx + 2]
    add     si, 0FF38h
    push    es
    pop     ds
    mov     cx, [cs:word_A1CC]

loc_C674:
    mov     bx, di
    inc     di
    mov     ah, 1

loc_C679:
    dec     si
    mov     al, [si]
    cmp     al, 0
    jz      loc_C682
    stosb
    stc

loc_C682:
    rcl     ah, 1
    jnb     loc_C679
    mov     [bx], ah
    loop    loc_C674
    pop     ds
    pop     si
    ret


;
; C68D:
;
sub_C68D:
    mov     es, [word_63BA]
    mov     di, 0
    mov     [word_2C76], es
    mov     bp, 0
    mov     cx, 80h

loc_C69E:
    call    sub_ABF0
    mov     dx, 20h
    mul     dx
    mov     ax, dx
    add     ax, bp
    stosw
    call    sub_ABF0
    and     ax, 0Eh
    mov     bx, ax
    mov     ax, [bx + 23D2h]
    stosw
    add     bp, 11Ch
    cmp     bp, 150h
    jb      loc_C6C6
    sub     bp, 150h

loc_C6C6:
    loop    loc_C69E
    add     di, 0Fh
    shr     di, 4
    add     [word_63BA], di
    mov     es, [word_63BA]
    mov     di, 0
    mov     [word_2C78], es
    mov     bp, 0
    mov     cx, 100h

loc_C6E3:
    call    sub_ABF0
    mov     dx, 12h
    mul     dx
    mov     ax, dx
    add     ax, bp
    stosw
    call    sub_ABF0
    and     ax, 0Eh
    mov     bx, ax
    mov     ax, [bx + 23C2h]
    stosw
    add     bp, 11Ch
    cmp     bp, 150h
    jb      loc_C70B
    sub     bp, 150h

loc_C70B:
    loop    loc_C6E3
    add     di, 0Fh
    shr     di, 4
    add     [word_63BA], di
    mov     es, [word_63BA]
    mov     di, 0
    mov     [word_2C7A], es
    mov     bp, 0
    mov     cx, 200h

loc_C728:
    call    sub_ABF0
    mov     dx, 0Ch
    mul     dx
    mov     ax, dx
    add     ax, bp
    stosw
    call    sub_ABF0
    and     ax, 0Eh
    mov     bx, ax
    mov     ax, [bx + 23B2h]
    stosw
    add     bp, 93h
    cmp     bp, 150h
    jb      loc_C750
    sub     bp, 150h

loc_C750:
    loop    loc_C728
    add     di, 0Fh
    shr     di, 4
    add     [word_63BA], di
    mov     es, [word_63BA]
    mov     di, 0
    mov     [word_2C7C], es
    mov     bp, 0
    mov     cx, 400h

loc_C76D:
    call    sub_ABF0
    mov     dx, 0Ch
    mul     dx
    mov     ax, dx
    add     ax, bp
    stosw
    add     bp, 51h
    cmp     bp, 150h
    jb      loc_C787
    sub     bp, 150h

loc_C787:
    loop    loc_C76D
    add     di, 0Fh
    shr     di, 4
    add     [word_63BA], di
    ret


;
; C794:
;
sub_C794:
    mov     es, [word_63BA]
    mov     di, 0
    mov     [word_2C76], es
    mov     bp, 0
    mov     cx, 80h

loc_C7A5:
    call    sub_ABF0
    mov     dx, 20h
    mul     dx
    mov     ax, dx
    add     ax, bp
    stosw
    add     bp, 11Ch
    cmp     bp, 150h
    jb      loc_C7C0
    sub     bp, 150h

loc_C7C0:
    loop    loc_C7A5
    add     di, 0Fh
    shr     di, 4
    add     [word_63BA], di
    mov     es, [word_63BA]
    mov     di, 0
    mov     [word_2C78], es
    mov     bp, 0
    mov     cx, 100h

loc_C7DD:
    call    sub_ABF0
    mov     dx, 12h
    mul     dx
    mov     ax, dx
    add     ax, bp
    stosw
    add     bp, 11Ch
    cmp     bp, 150h
    jb      loc_C7F8
    sub     bp, 150h

loc_C7F8:
    loop    loc_C7DD
    add     di, 0Fh
    shr     di, 4
    add     [word_63BA], di
    mov     es, [word_63BA]
    mov     di, 0
    mov     [word_2C7A], es
    mov     bp, 0
    mov     cx, 200h

loc_C815:
    call    sub_ABF0
    mov     dx, 18h
    mul     dx
    mov     ax, dx
    add     ax, bp
    stosw
    add     bp, 93h
    cmp     bp, 150h
    jb      loc_C830
    sub     bp, 150h

loc_C830:
    loop    loc_C815
    add     di, 0Fh
    shr     di, 4
    add     [word_63BA], di
    ret


;
; C83D:
;
sub_C83D:
    mov     si, [track_num]
    shl     si, 5
    add     si, arr_618E
    mov     cx, 10h
    mov     di, arr_7856 - 48          ; palette + 720
    push    ds
    pop     es

loc_C850:
    lodsw
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
    loop    loc_C850
    ret


;
; Loads S70 resource (player's cars) and fixes palette.
;
prep_cars_and_pals:
    mov     ax, [word_63BA]
    mov     [word_2E7C], ax
    mov     al, [byte_2B00]
    mov     [byte_2E81], al
    mov     ah, 0FFh
    mov     [word_2E78], ax
    mov     word [word_2E7A], arr89_30A7
    mov     si, [car_num]
    mov     al, [si + word_2E7E]
    mov     ah, 'S'                    ; sub_C505('S', 70, BE)
    call    bmp_load_and_prepare
    call    sub_DC4F
    mov     bl, [byte_2E81]
    mov     bh, 0
    mov     dx, 17

loc_C89D:
    mov     cx, 4

loc_C8A0:
    mov     [ss:bx + 0D00h], bl
    mov     [ss:bx + 0E00h], bl
    mov     [ss:bx + 0F00h], bl
    inc     bx
    loop    loc_C8A0
    mov     al, bl
    add     al, 2
    mov     ah, al
    add     ah, 2
    mov     [ss:bx + 0D00h], bl
    mov     [ss:bx + 0E00h], al
    mov     [ss:bx + 0F00h], ah
    add     ax, 101h
    inc     bx
    mov     [ss:bx + 0D00h], bl
    mov     [ss:bx + 0E00h], al
    mov     [ss:bx + 0F00h], ah
    add     bx, 5
    dec     dx
    jnz     loc_C89D
    mov     bx, arr_2FF0
    cmp     word [word_63A0], 0
    jnz     loc_C8FA
    mov     bx, arr_2F39
    cmp     word [word_639E], 0
    jnz     loc_C8FA
    mov     bx, arr_2E82

loc_C8FA:
    mov     ax, 61
    mul     word [car_num]
    add     bx, ax
    push    ds
    pop     es
    mov     di, [palette_ptr]
    mov     dl, 17
    mov     dh, 0

loc_C90D:
    lea     si, [bx + 1]
    mov     cx, 30

loc_C913:
    mov     al, [si + 30]
    sub     al, [si]
    imul    dh
    sar     ax, 7
    adc     al, 0
    add     al, [si]
    inc     si
    stosb
    loop    loc_C913
    add     byte [byte_2B00], 10
    add     dh, [bx]
    jns     loc_C930
    mov     dh, 127                    ; this is on the Fog track only

loc_C930:
    dec     dl
    jnz     loc_C90D
    mov     [palette_ptr], di
    ret


;
; C939: Easy level scores
;
; Get C00, C01, C02, C07
;
sub_C939:
    mov     si, arr5_3100              ; let data_3100 = vec![00, 01, 02, 07, -1];
    mov     word [word_2E78], 224


;
; C942: Load series of 'C' resources.
;
; in:
; si - array of numbers ending with -1
;
; out:
; chr_bmp_ptr[num * 2] - data of ('C' + num) resource
;
chr_load_and_prepare_few:
    lodsb
    cmp     al, -1
    jz      ret_C95E
    push    si
    mov     bh, 0
    mov     bl, al
    shl     bx, 1
    mov     cx, [word_63BA]            ; cx = segment (cx:0) where the result data will be
    mov     [chr_bmp_ptr + bx], cx     ; chr_bmp_ptr[al] = word_63BA
    mov     ah, 'C'
    call    bmp_load_and_prepare
    pop     si
    jmp     chr_load_and_prepare_few

ret_C95E:
    ret
