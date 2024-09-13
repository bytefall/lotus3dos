;
; D097:
;
; if ax == 13 { 50 /* 50 = 0x32 = '2' */ } else if ax > 13 { (ax - 1) << 2 } else { ax << 2 }
;
; input:
; ax - word
;
; output:
; ax - converted word
sub_D097:
    cmp     ax, 0Dh
    jz      loc_D0A3
    js      loc_D09F
    dec     ax

loc_D09F:
    shl     ax, 2
    ret

loc_D0A3:
    mov     ax, 32h                    ; '2'
    ret


;
; D0A7: Fade in
;
fade_in:
    mov     si, palette
    cmp     byte [byte_3D6A], 0
    jnz     loc_D0B4
    jmp     sub_D18C

loc_D0B4:
    mov     word [word_3D6C], 20
    call    fade_by_color
    call    sub_D161
    mov     byte [byte_3D6A], 0
    ret


;
; D0C6:
;
sub_D0C6:
    mov     word [word_3D6C], 14h
    call    fade_by_color
    call    sub_D161
    mov     byte [byte_3D6A], 0
    ret


;
; D0D8: Fade out
;
fade_out:
    mov     si, palette2
    cmp     byte [byte_3D6A], 0
    jz      loc_D0E5
    jmp     sub_D18C

loc_D0E5:
    mov     word [word_3D6C], 20
    call    fade_by_color
    call    sub_D161
    mov     byte [byte_3D6A], 0FFh
    ret


;
; D0F7:
;
fade_in2:
    mov     si, palette
    cmp     byte [byte_3D6A], 0
    jnz     loc_D104
    jmp     sub_D18C

loc_D104:
    mov     word [word_3D6C], 20
    call    fade_by_color
    mov     byte [byte_3D6A], 0
    ret


;
; D113:
;
fade_out2:
    mov     si, palette2
    cmp     byte [byte_3D6A], 0
    jnz     sub_D18C
    mov     word [word_3D6C], 20
    call    fade_by_color
    mov     byte [byte_3D6A], 0FFh
    ret


;
; D12C: Fade in/out some palette colors
;
; input:
; ds:si - palette
; word_3D6C - fade speed (greater = slower)
;
fade_by_color:
    call    sub_D161
    push    ds
    pop     es
    mov     di, arr_C560
    mov     bx, arr_6F56
    mov     dl, 0
    mov     bp, [word_3D6C]
    mov     cx, 768                    ; = 256 * 3

loc_D140:
    mov     ah, [si]                   ; ds:si - palette
    inc     si
    sub     ah, [bx]
    mov     al, 0
    cwd
    idiv    bp
    stosw
    mov     al, 0
    mov     ah, [bx]
    inc     bx
    stosw
    loop    loc_D140

    call    sub_D174
    mov     [word_3D70], bp
    mov     word [word_3D6E], 0FFFFh
    ret


;
; D161:
;
sub_D161:
    call    sub_D6F9
    cmp     word [word_3D70], 0
    jnz     sub_D161
    ret


;
; D16C:
;
sub_D16C:
    cmp     word [word_3D6E], 0
    jnz     sub_D16C
    ret


;
; D174:
;
sub_D174:
    mov     si, arr_C560
    push    ds
    pop     es
    mov     di, arr_6F56
    mov     cx, 768

loc_D17F:
    lodsw
    add     ax, [si]
    mov     [si], ax
    inc     si
    inc     si
    mov     al, ah
    stosb
    loop    loc_D17F
    ret


;
; D18C: Copy palette
;
; input:
; si - where palette is stored
;
sub_D18C:
    call    sub_D161
    cmp     si, palette2
    mov     byte [byte_3D6A], 0FFh
    jz      loc_D19F
    mov     byte [byte_3D6A], 0

loc_D19F:
    mov     word [word_3D6E], 0
    push    ds
    pop     es
    mov     di, arr_6F56
    mov     cx, 768
    rep movsb

    mov     word [word_3D6E], 0FFFFh
    ret


;
; D1B6:
;
sub_D1B6:
    cmp     word [word_3D6E], 0
    jz      loc_D1E9
    cmp     word [word_3D70], 0
    jnz     loc_D1CC
    mov     word [word_3D6E], 0
    jmp     sub_D1D7

loc_D1CC:
    call    sub_D1D7
    dec     word [word_3D70]
    jz      loc_D1E9
    jmp     sub_D174


;
; D1D7: Fade out slowly
;
sub_D1D7:
    mov     al, 0
    mov     dx, 3C8h
    out     dx, al
    mov     dx, 3C9h
    mov     si, arr_6F56
    mov     cx, 256 * 3
    rep outsb
    ret

loc_D1E9:
    mov     word [word_3D6E], 0
    mov     word [word_3D70], 0
    ret


;
; D1F6: Sets vga 320x200 mode.
;
set_video_mode_and_timer:
    ; Timer 8253-5 (AT: 8254.2).
    in      al, 40h                    
    mov     ah, al
    in      al, 40h
    mov     [word_3E16], ax

    ; DOS - GET DEFAULT DISK NUMBER
    mov     ah, 19h
    int     21h
    mov     [byte_3D72], al

    ; - VIDEO - GET CURRENT VIDEO MODE
    ; Return: AH = number of columns on screen
    ; AL = current video mode
    ; BH = current active display page
    mov     ah, 0Fh
    int     10h

    ; Set mode 13h
    ; https://github.com/jagregory/abrash-black-book/blob/master/src/chapter-27.md#mode-13h320x200-with-256-colors
    mov     [dos_vid_mode], al
    mov     al, 13h
    mov     ah, 0
    int     10h

    ; - MS MOUSE - RESET DRIVER AND READ STATUS
    ; Return: AX = status
    ; BX = number of buttons
    mov     ax, 0
    int     33h
    mov     [byte_3E2C], al

    ; mov     es, [cs:word_5160]
    ; mov     ax, [es:2]
    ; sub     ax, 4371
    ; mov     [word_63BC], ax
    ; sub     ax, 256
    ; mov     [word_63BE], ax
    times 21 nop

    cli                                ; D230

    ; https://wiki.osdev.org/Interrupt_Vector_Table
    sub     ax, ax
    mov     es, ax
    mov     ax, [es:24h]
    mov     [word_3D82], ax
    mov     ax, [es:26h]
    mov     [word_3D84], ax
    mov     ax, [es:20h]
    mov     [word_3E0A], ax
    mov     ax, [es:22h]
    mov     [word_3E0C], ax
    mov     ax, [es:90h]
    mov     [word_3D7E], ax
    mov     ax, [es:92h]
    mov     [word_3D80], ax
    mov     al, 10110000b
    out     43h, al
    mov     al, 0
    out     42h, al
    out     42h, al
    in      al, 61h
    or      al, 1
    out     61h, al
    ; PC/XT PPI port B bits:
    ; 0: Tmr 2 gate --- OR 03H=spkr ON
    ; 1: Tmr 2 data -+  AND 0fcH=spkr OFF
    ; 3: 1=read high switches
    ; 4: 0=enable RAM parity checking
    ; 5: 0=enable I/O channel check
    ; 6: 0=hold keyboard clock low
    ; 7: 0=enable kbrd

    ; Wait for VSYNC
    ;
    ; Video status bits:    
    ; 0: retrace.  1=display is in vert or horiz retrace.
    ; 1: 1=light pen is triggered; 0=armed
    ; 2: 1=light pen switch is open; 0=closed
    ; 3: 1=vertical sync pulse is occurring.
    mov     dx, 3DAh

vsync_1:
    in      al, dx
    test    al, 1000b
    jnz     vsync_1

vsync_2:
    in      al, dx
    test    al, 1000b
    jz      vsync_2

    ; timer 8253-5 (AT: 8254.2).
    mov     al, 10000000b
    out     43h, al    
    in      al, 42h
    mov     bl, al
    in      al, 42h
    mov     bh, al

    ; wait for VSYNC
vsync_3:
    in      al, dx
    test    al, 1000b
    jnz     vsync_3

    ; timer 8253-5 (AT: 8254.2).
    mov     al, 10000000b
    out     43h, al    
    in      al, 42h
    mov     cl, al
    in      al, 42h
    mov     ch, al

    ; wait for VSYNC
vsync_4:
    in      al, dx
    test    al, 1000b
    jz      vsync_4

    ; timer 8253-5 (AT: 8254.2).
    mov     al, 10000000b              ; counter 2 select
    out     43h, al    
    in      al, 42h
    mov     dl, al
    in      al, 42h
    mov     dh, al

    mov     ax, bx
    sub     ax, dx
    mov     dx, ax
    mov     [word_3D7A], dx            ; = bx - timerValue; dx == 0 ???
    sub     bx, cx
    sub     dx, bx
    mov     al, 0FFh
    cmp     bx, dx
    jb      loc_D2C0
    mov     al, 0

loc_D2C0:
    mov     [byte_3D74], al
    in      al, 61h
    ; PC/XT PPI port B bits:
    ; 0: Tmr 2 gate --- OR 03H=spkr ON
    ; 1: Tmr 2 data -+  AND 0fcH=spkr OFF
    ; 3: 1=read high switches
    ; 4: 0=enable RAM parity checking
    ; 5: 0=enable I/O channel check
    ; 6: 0=hold keyboard clock low
    ; 7: 0=enable kbrd
    and     al, 11111110b
    out     61h, al
    sub     cx, cx
    sub     dx, dx

    ; timer 8253-5 (AT: 8254.2).
loc_D2CD:
    mov     al, 0
    out     43h, al    
    in      al, 40h
    mov     bl, al
    in      al, 40h
    mov     bh, al
    cmp     bx, dx
    jb      loc_D2DF
    mov     dx, bx

loc_D2DF:
    loop    loc_D2CD

    mov     cx, dx
    sub     ax, ax
    mov     dx, 1
    div     cx
    shl     dx, 1
    cmp     cx, dx
    adc     ax, 0
    mov     cx, ax
    sub     ax, ax
    mov     dx, 1
    cmp     cx, 1
    jz      loc_D306

    div     cx
    shl     dx, 1
    cmp     cx, dx
    adc     ax, 0

loc_D306:
    mov     [word_3D78], ax

    ; timer 8253-5 (AT: 8254.2).
    mov     al, 10110000b
    out     43h, al                    
    mov     al, 0
    out     42h, al
    out     42h, al
    in      al, 61h
    ; PC/XT PPI port B bits:
    ; 0: Tmr 2 gate --- OR 03H=spkr ON
    ; 1: Tmr 2 data -+  AND 0fcH=spkr OFF
    ; 3: 1=read high switches
    ; 4: 0=enable RAM parity checking
    ; 5: 0=enable I/O channel check
    ; 6: 0=hold keyboard clock low
    ; 7: 0=enable kbrd
    or      al, 1
    out     61h, al
    ; PC/XT PPI port B bits:
    ; 0: Tmr 2 gate --- OR 03H=spkr ON
    ; 1: Tmr 2 data -+  AND 0fcH=spkr OFF
    ; 3: 1=read high switches
    ; 4: 0=enable RAM parity checking
    ; 5: 0=enable I/O channel check
    ; 6: 0=hold keyboard clock low
    ; 7: 0=enable kbrd
    mov     cx, 5000

    ; timer 8253-5 (AT: 8254.2).
    mov     al, 10000000b
    out     43h, al    
    in      al, 42h
    mov     bl, al
    in      al, 42h
    mov     bh, al

    ; timer 8253-5 (AT: 8254.2).
    mov     al, 10000000b
    out     43h, al
    in      al, 42h
    mov     dl, al
    in      al, 42h
    mov     dh, al

loop_myself:
    loop    loop_myself

    ; timer 8253-5 (AT: 8254.2).
    mov     al, 10000000b
    out     43h, al    
    in      al, 42h
    mov     cl, al
    in      al, 42h
    mov     ch, al

    ; word_3D76 = 5962500 / (timerB - timerC - timerA - timerB)
    sub     bx, dx
    sub     dx, cx
    sub     dx, bx
    mov     cx, dx
    mov     dx, 5Ah
    mov     ax, 0FB04h                 ; 0x5AFB04 = 5962500
    ; comment out this line to resolve division by zero issue:
    ; see https://www.vogons.org/viewtopic.php?p=308588#p308588
    div     cx
    mov     [word_3D76], ax            ; word_3D76 = 0x9C1 (was word_3D76 = 0)

    ; PC/XT PPI port B bits:
    ; 0: Tmr 2 gate --- OR 03H=spkr ON
    ; 1: Tmr 2 data -+  AND 0fcH=spkr OFF
    ; 3: 1=read high switches
    ; 4: 0=enable RAM parity checking
    ; 5: 0=enable I/O channel check
    ; 6: 0=hold keyboard clock low
    ; 7: 0=enable kbrd
    in      al, 61h
    and     al, 11111110b
    out     61h, al
    sti
    cli
    pushf
    pop     ax
    or      ah, 110000b
    push    ax
    popf
    pushf
    pop     ax
    test    ah, 110000b
    jz      loc_D377

    and     ah, 0CFh
    push    ax
    popf
    mov     word [cs:word_D379], 2

loc_D377:
    sti
    ret


word_D379:  dw ?                       ; D379


;
; D37B:
;
sub_D37B:
    call    sub_D3B6
    call    sub_D3DD
    mov     ax, sub_D926
    call    sub_D740
    call    set_timer
    mov     si, palette2
    call    sub_D18C
    mov     byte [byte_3D7C], 0FFh
    ret


;
; D396:
;
sub_D396:
    cmp     byte [byte_3D7C], 0
    jz      loc_D3AE

    call    fade_out
    call    sub_D4E3
    call    sub_D400
    call    sub_D3C7
    mov     byte [byte_3D7C], 0

loc_D3AE:
    mov     al, [dos_vid_mode]
    mov     ah, 0
    int     10h
    ret
