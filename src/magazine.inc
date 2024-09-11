;
; 2DED: Show automotive magazine with a short video
;
show_magazine:
    mov     ax, [cs:word_5166]
    mov     [word_63BA], ax
    call    fade_out
    mov     al, 32h
    mov     ah, 'V'
    call    sub_CBC3
    xchg    [word_63BA], ax
    call    res_unpack_with_pal
    mov     si, [word_63BA]
    mov     di, 0
    mov     ax, 320
    mov     bx, 200
    call    draw_sprite
    call    update_screen
    mov     ax, [cs:word_5166]
    mov     [word_63BA], ax
    mov     si, arr_intro_video
    mov     di, arr_D01
    mov     ah, 'V'
    call    load_resource_series
    mov     cx, 0FFFFh
    mov     ax, 0
    call    sub_2EB2
    cmp     word [word_3E18], 3
    jae     loc_2E7E
    mov     cx, 0
    mov     ax, 0
    call    sub_2EB2
    call    fade_in
    mov     word [word_3E18], 18h

loc_2E4C:
    mov     ax, [word_3E18]
    cmp     ax, 984
    jae     loc_2E5C
    mov     dl, 24
    div     dl
    mov     ah, 0
    jmp     loc_2E5F

loc_2E5C:
    mov     ax, 40

loc_2E5F:
    push    ax
    mov     cx, 0
    call    sub_2EB2
    pop     ax
    cmp     ax, 40
    jb      loc_2E4C
    push    ds
    pop     es
    mov     di, palette + 48
    mov     al, 3Fh
    mov     cx, 720
    rep stosb
    mov     si, palette
    call    sub_D0C6

loc_2E7E:
    mov     ax, [cs:word_5166]
    mov     [word_63BA], ax
    mov     al, 33h
    mov     ah, 'V'
    call    sub_CBC3
    xchg    [word_63BA], ax
    mov     [arr_D01], ax
    mov     ax, 0
    mov     cx, 1
    call    sub_2EB2
    mov     si, palette
    call    sub_D0C6
    mov     word [word_3E18], 0
    mov     ax, 1400
    call    sleep
    call    fade_out
    ret


;
; 2EB2:
;
sub_2EB2:
    push    cx
    mov     bx, ax
    shl     bx, 1
    mov     ax, [bx + arr_D01]
    call    res_unpack_simple
    pop     cx
    push    cx
    push    ds
    push    ds
    pop     es
    mov     di, palette + 48
    mov     ds, [word_63BA]
    mov     si, 0
    mov     cx, 720
    rep movsb
    pop     ds
    pop     cx
    cmp     cx, 1
    je      loc_2EFB
    push    cx
    mov     si, palette2
    cmp     cx, -1
    je      loc_2EE5
    mov     si, palette

loc_2EE5:
    call    sub_D18C
    call    sub_D16C
    pop     cx
    cmp     cx, -1
    jne     loc_2EFB
    cli
    mov     al, [byte_3E0E]
    mov     ah, 0
    mov     [word_3E18], ax
    sti

loc_2EFB:
    push    ds
    mov     ax, 0A000h
    mov     es, ax
    mov     ds, [word_63BA]
    mov     si, 720
    mov     di, 12296
    mov     dx, 112

loc_2F0E:
    mov     cx, 80
    rep movsw
    add     di, 160
    dec     dx
    jne     loc_2F0E
    pop     ds
    ret
