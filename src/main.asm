    format  MZ
    heap    0
    entry   code_seg:start

SCREEN_WIDTH = 336
VGA_DBL_BUF_START = SCREEN_WIDTH * 4 + 16

segment code_seg use16

    times 2000h ret

include 'sound.inc'
include 'magazine.inc'
include 'protection.inc'
include 'intro.inc'
include 'menu.inc'
include 'config.inc'
include 'vars.inc'

start:
    ; 5178:
    mov     [cs:word_5160], es
    mov     [cs:word_5164], ss
    mov     ax, data_seg
    mov     ds, ax
    times 3 nop

    ; 518A:
    call    set_video_mode_and_timer
    call    open_and_read_data_file
    call    cfg_open_and_read
    call    sub_D37B
    call    sub_DB28                                       ; set bitmap decode routing
    call    protection_screen
    mov     word [word_1F26], loc_51C4
    mov     ax, loc_5371
    call    sub_D740                                       ; Attach keys while plaing demo
    mov     al, 3                                          ; 3 - Lotus Theme
    call    play_music
    call    sub_20ED
    call    show_gremlin
    call    show_magnetic_fields
    call    show_credits
    call    show_lotus_logo
    call    show_magazine
    mov     byte [show_lotus_again], -1

loc_51C4:
    mov     al, 3
    cmp     [song_num], al
    je      loc_51D2
    call    play_music
    call    sub_20ED

loc_51D2:
    mov     word [playing_demo], 0
    call    sub_D915
    call    fade_out
    mov     word [demo_counter], 0FFFFh
    mov     byte [byte_3D86], 0

loc_51E9:
    call    sub_D915
    mov     word [word_1F26], loc_5222
    mov     ax, loc_5371
    call    sub_D740
    mov     al, 0
    xchg    al, [show_lotus_again]
    cmp     al, 0
    jnz     loc_5205
    call    show_lotus_logo

loc_5205:
    inc     word [demo_counter]                            ; for i in 0..6
    mov     ax, [cs:word_5166]
    mov     [word_63BA], ax
    cmp     word [demo_counter], 6
    jb      loc_521D
    mov     word [demo_counter], 0

loc_521D:
    mov     ax, [demo_counter]
    jmp     loc_525B

loc_5222:
    mov     word [playing_demo], 0
    call    sub_D915
    jmp     old_logo

include 'game.inc'
include 'hud.inc'
include 'bitmap.inc'
include 'crc.inc'
include 'prepare.inc'
include 'sprite.inc'
include 'chars.inc'
include 'archive.inc'
include 'state.inc'
include 'video.inc'
include 'timer.inc'
include 'dos.inc'

segment data_seg

include 'data.inc'

segment test_seg

    rb 410000

segment vga_dbl_buf_seg

    rb 336 * 200 + VGA_DBL_BUF_START

segment arc_header_seg

    rb 4096
