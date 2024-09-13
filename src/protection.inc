;
; 2F1C:
;
protection_screen:
    call    fade_out
    mov     ax, [cs:word_5166]
    mov     [word_63BA], ax

    mov     si, prot_fonts
    mov     word [word_2E78], 0
    call    chr_load_and_prepare_few   ; C03

    mov     si, prot_res_ids
    mov     di, prot_res_ptr
    mov     ah, 'I'
    call    load_resource_series       ; I21, I22

loc_2F3D:
    call    sub_ABF0
    mov     dx, 48
    mul     dx
    mov     [prot_code], dx

    call    sub_ABF0
    mov     dx, 12
    mul     dx
    mov     [prot_d5c], dx

    call    sub_ABF0
    mov     dx, 12
    mul     dx
    mov     [prot_d5e], dx

    mov     di, prot_d7b
    mov     word [di], 2020h
    mov     byte [di + 2], 20h
    mov     si, [prot_code]
    shl     si, 1
    add     si, prot_d83
    mov     dx, [prot_d5c]
    sub     dx, [prot_d5e]
    jns     loc_2F83
    add     dx, 12

loc_2F83:
    mov     ah, [si]
    shr     ah, 1
    mov     al, 3
    sub     al, ah
    mov     cl, al
    mul     dl
    mov     dx, ax
    add     dl, [si + 1]
    mov     al, 12
    mul     cl
    cmp     dx, ax
    jb      loc_2F9E
    sub     dx, ax

loc_2F9E:
    mov     al, [si]
    cmp     al, 1
    jae     loc_2FA9
    add     dx, 1
    jmp     loc_2FD2

loc_2FA9:
    jnz     loc_2FB2
    neg     dx
    add     dx, 106
    jmp     loc_2FD2

loc_2FB2:
    cmp     al, 3
    jae     loc_2FBB
    add     dx, 37
    jmp     loc_2FD2

loc_2FBB:
    jnz     loc_2FCC
    add     dl, 83
    cmp     dl, 89
    jb      loc_2FC8
    sub     dl, 24

loc_2FC8:
    mov     [di], dl
    jmp     loc_2FF5

loc_2FCC:
    mov     bx, dx
    mov     dl, [prot_de3 + bx]

loc_2FD2:
    mov     cl, 0
    cmp     dl, 100
    jb      loc_2FE1
    sub     dl, 100
    mov     byte [di], 49
    inc     di
    dec     cx

loc_2FE1:
    mov     ax, dx
    mov     dl, 10
    div     dl
    cmp     al, cl
    jz      loc_2FF0
    add     al, 30h                    ; '0'
    mov     [di], al
    inc     di

loc_2FF0:
    add     ah, 30h                    ; '0'
    mov     [di], ah

loc_2FF5:
    mov     ax, [prot_res_ptr]
    call    res_unpack_with_pal

    mov     si, [word_63BA]
    mov     di, 0
    mov     ax, 320
    mov     bx, 200
    call    draw_sprite

    mov     ax, [prot_res_ptr + 2]     ; 0D5A, ptr to I22
    call    res_unpack_simple

    mov     ax, 141
    mov     bx, 13
    mov     cx, [prot_d5c]
    call    draw_helmet

    mov     ax, 141
    mov     bx, 73
    mov     cx, [prot_d5e]
    add     cl, 12
    call    draw_helmet

loc_302E:
    mov     ax, [prot_code]
    inc     ax
    mov     bl, 10
    div     bl
    add     ax, 3030h
    cmp     al, 30h                    ; '0'
    jnz     loc_3041
    mov     al, ah                     ; if code is < 10
    mov     ah, 0

loc_3041:
    mov     [prot_text_num], ax
    mov     di, prot_text
    mov     bx, 140
    mov     ch, 3                      ; C03
    call    print_string

    call    update_screen
    call    fade_in

    mov     word [y_pos], 150
    mov     word [x_pos], 165
    mov     byte [byte_12A3], 3
    mov     word [str_ptr], 0D7Eh
    mov     word [prot_d7e], 2020h
    mov     byte [prot_d80], 20h
    mov     word [word_129D], 3
    mov     word [word_129F], 0
    mov     word [word_12A1], 2
    mov     byte [byte_12A4], 3

    call    handle_input
    call    fade_out
    ret


;
; 3095:
;
unk_3095:
    and     bl, [bx]
    nop
    add     [si + 8], dh
    cmp     word [prot_d7e], 2020h
    je      ret_30C1
    mov     ax, [prot_d7e]
    cmp     ax, [prot_d7b]
    jne     loc_30B5
    mov     al, [prot_d80]
    cmp     al, [prot_d7d]
    je      ret_30C1

loc_30B5:
    dec     byte [prot_d82]
    je      loc_30BE
    jmp     loc_2F3D

loc_30BE:
    jmp     loc_DC70

ret_30C1:
    ret


;
; 30C2:
;
; in:
; ax - x
; bx - y
; cx -
;
draw_helmet:
    mov     di, ax
    mov     ax, 336
    mul     bx
    add     di, ax
    mov     ax, 120
    mul     cx
    mov     si, ax
    add     si, [word_63BA]
    mov     ax, 48
    mov     bx, 40
    jmp     draw_sprite
