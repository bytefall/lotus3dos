	format	MZ
	heap	0
	stack	8000h	
	entry	main:start

segment main use16

	rb 2000h

include 'sound.inc'
include 'magazine.inc'
include 'protection.inc'
include 'intro.inc'
include 'menu.inc'
include 'config.inc'
include 'vars.inc'

start:
	; bp cs:060b

	; cs:5178
	; mov		ss, [cs:word_5164]
	; mov		sp, 1800h

	; mov		[cs:word_5160], ds
	; mov		ds, [cs:word_5162]

	; this piece is missing in the original code
	mov		ax, text
	mov		ds, ax
	mov		[cs:word_5162], ax

	times 23 nop

	; cs:518A
	call	set_video_mode_and_timer
	call	open_and_read_data_file
	call	cfg_open_and_read
	call	sub_D37B
	call	sub_DB28
	call	protection_screen
	mov		word [word_1F26], loc_51C4
	mov		ax, loc_5371
	call	sub_D740					; Attach keys while plaing demo
	mov		al, 3						; 3 - Mail Lotus Theme
	call	play_music
	call	sub_20ED
	call	show_gremlin
	call	show_magnetic_fields
	call	show_credits
	call	show_lotus_logo
	call	show_magazine
	mov		byte [show_lotus_again], -1

loc_51C4:
	mov		al, 3
	cmp		[song_num], al
	je		loc_51D2
	call	play_music
	call	sub_20ED

loc_51D2:
	mov		word [playing_demo], 0
	call	sub_D915
	call	fade_out
	mov		word [demo_counter], 0FFFFh
	mov		byte [byte_3D86], 0

loc_51E9:
	call	sub_D915
	mov		word [word_1F26], loc_5222
	mov		ax, loc_5371
	call	sub_D740
	mov		al, 0
	xchg	al, [show_lotus_again]
	cmp		al, 0
	jnz		loc_5205
	call	show_lotus_logo

loc_5205:
	inc		word [demo_counter]			; for i in 0..6
	mov		ax, [cs:word_5166]
	mov		[word_63BA], ax
	cmp		word [demo_counter], 6
	jb		loc_521D
	mov		word [demo_counter], 0

loc_521D:
	mov		ax, [demo_counter]
	jmp		loc_525B

loc_5222:
	mov		word [playing_demo], 0
	call	sub_D915
	jmp		old_logo

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

segment text

unkn_00:			times 8 dw 0							; 00
unkn_10:			times 4 dw 0							; 10
word_18:			dw 0080h								; 18
word_1A:			dw 0080h								; 1A
word_1C:			dw 02DEh								; 1C
word_1E:			dw 04C4h								; 1E
word_20:			dw 0									; 20
byte_22:			db 0									; 22
byte_23:			db 0									; 23
byte_24:			db 0									; 24
					db 0									; 25
word_26:			dw 0									; 26
word_28:			dw 0									; 28
word_2A:			dw 0									; 2A
word_2C:			dw 0									; 2C
					dw 0									; 2E
word_30:			dw 2141h								; 30
word_32:			dw 2141h								; 32
word_34:			dw 2141h								; 34
word_36:			dw 2141h								; 36
word_38:			dw 2141h								; 38
					times 22 dw 0
					db 0									; 66
					db 0									; 67
					db 0									; 68
					db 0									; 69

word_7C:			dw 0									; 7C
word_7E:			dw 0									; 7E

song_num:			db 0									; 5A9, 0 - sound of engines, 1.. - sound tracks
word_5AA:			dw 0									; 5AA

arr_intro_video:											; CD7
					db 00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 08h, 09h, 0Ah, 0Bh, 0Ch, 0Dh, 0Eh, 0Fh
					db 10h, 11h, 12h, 13h, 14h, 15h, 16h, 17h, 18h, 19h, 1Ah, 1Bh, 1Ch, 1Dh, 1Eh, 1Fh
					db 20h, 21h, 22h, 23h, 24h, 25h, 26h, 27h, 28h, -1
; 0D01

prot_fonts:			db 3, -1								; D53
prot_res_ids:		db 21h, 22h, -1							; D55
prot_res_ptr:		times 2 dw 0							; D58
prot_d5c:			dw 0									; D5C
prot_d5e:			dw 0									; D5E
prot_code:			dw 0									; D60, actual "??" code is prot_code + 1
prot_text:			db 'ENTER CODE FOR WINDOW ??', 0		; D62
prot_d7b:			dw 2020h								; D7B
prot_d7d:			db 20h									; D7D
prot_d7e:			dw 2020h								; D7E
prot_d80:			db 20h									; D80
					db 0									; D81
prot_d82:			db 3									; D82
prot_d83:													; D83
					db 0, 0,	0, 4,	0, 8,	0, 10,	0, 13,	0, 17,	0, 19,	0, 21
					db 0, 25,	0, 28,	0, 30,	0, 35,	1, 2,	1, 5,	1, 11,	1, 12
					db 1, 16,	1, 20,	1, 24,	1, 29,	1, 31,	1, 34,	2, 0,	2, 2
					db 2, 4,	2, 6,	2, 10,	2, 12,	2, 14,	2, 17,	2, 18,	2, 21
					db 3, 22,	3, 1,	3, 3,	3, 5,	3, 7,	3, 9,	3, 11,	3, 13
					db 3, 15,	3, 16,	3, 21,	4, 11,	4, 2,	4, 4,	4, 7,	4, 9

prot_de3:			db 'D', 'C', 'B', 'A', '6', '?', '>', '=', 'H', 'G', 'F', 'E'	; DE3
magn_fields_ids:	db 2, 3, 4, 5, 6, 7, 8, 9, 0Ah, 0Bh, 0Ch, 0Dh, 0Eh, 0Fh			; DEF
					db 10h, 11h, 12h, 13h, 14h, 15h, 16h, 17h, -1
magn_fields_ptr:	rw 22									; E06
; E22
credits_ids:		db 19h, 1Bh, 1Ch, 1Dh, 1Eh, -1			; E32
credits_ptr:		rw 5									; E38
; E42
credits_txt:												; E48
					dw 038E6h								; 38E6h = 14566 = 336 * 43 + 118 = xy(118, 43)
					db 'A GAME', 0
					dw 05882h
					db 'BY', 0
					dw 077B5h
					db 'ANDREW MORRIS', 0
					dw 0B6AEh
					db 'AND', 0
					dw 0B6AEh
					db 'SHAUN SOUTHERN', 0
					dw 0FBA0h
					dw 0583Ch
					db 'LEVEL DESIGN', 0
					dw 07802h
					db 'BY', 0
					dw 09735h
					db 'PETER LIGGETT', 0
					dw 0FCB8h
					dw 0586Dh
					db 'MUSIC', 0
					dw 07802h
					db 'BY', 0
					dw 0972Eh
					db 'PATRICK PHELAN', 0
					dw 0FCB8h
					dw 038B5h
					db 'PC CONVERSION', 0
					dw 05882h
					db 'BY', 0
					dw 077A0h
					db 'JON MEDHURST FOR', 0
					dw 09727h
					db 'CYGNUS SOFTWARE', 0
					dw 0B6A4h
					db 'ENGINEERING LTD.', 0
					dw 0FA88h
					dw 038AEh
					db 'COPYRIGHT 1993', 0
					dw 05827h
					db 'MAGNETIC FIELDS', 0
					dw 0777Ah
					db '(SOFTWARE DESIGN) LTD.', 0
					dw 09720h
					db 'GREMLIN GRAPHICS', 0
					dw 0B6B9h
					db 'SOFTWARE LTD.', 0
					dw 0F858h
					dw 0FFFFh
word_F77:			dw ?															; F77
main_menu_res_ids:	db 14h, 15h, 16h, 17h, 18h, 19h, 1Ah, 1Bh, 1Fh, 20h, -1			; F79
main_menu_fnt_ids:	db 3, 4, 5, -1							; F84
res_ptr_I14:		dw ?									; F88 = *I14
res_ptr_I15:		dw ?									; F8A = *I15
res_ptr_I16:		dw ?									; F8C = *I16
res_ptr_I17:		dw ?									; F8E = *I17
res_ptr_I18:		dw ?									; F90 = *I18
res_ptr_I19:		dw ?									; F92 = *I19
res_ptr_I1A:		dw ?									; F94 = *I1A
res_ptr_I1B:		dw ?									; F96 = *I1B
res_ptr_I1F:		dw ?									; F98 = *I1F
res_ptr_I20:		dw ?									; F9A = *I20
curr_menu_col:		dw 0									; F9C
curr_menu_row:		dw 0									; F9E

dword_FDC:			dd ?									; 0FDC
word_FE0:			dw ?									; 0FE0
arr_FE2:			rb 11									; 0FE2

word_1092:			dw ?									; 1092
word_1094:			dw ?									; 1094
word_1096:			dw ?									; 1096
word_1098:			dw ?									; 1098

word_122F:			dw ?									; 122F
word_1231:			dw ?									; 1231
word_1233:			dw ?									; 1233

word_1271:			dw ?									; 1271
word_1273:			dw ?									; 1273

y_pos:				dw ?									; 1295
x_pos:				dw ?									; 1297
word_1299:			dw ?									; 1299
str_ptr:			dw ?									; 129B
word_129D:			dw ?									; 129D
word_129F:			dw ?									; 129F
word_12A1:			dw ?									; 12A1
byte_12A3:			db ?									; 12A3
byte_12A4:			db ?									; 12A4
car_sel_res_ids:	db 1Dh, 1Eh, 10h, 11h, 12h, 13h, -1		; 12A6
car_sel_res_ptr:	rw 6									; 12AD
tuner_fnt_ids:		db 6, -1								; 12B9
tuner_res_ids:		db 1Ch, -1								; 12BB
tuner_res_ptr:		dw ?									; 12BD
next_race_txt:		db 'NEXT RACE', 0						; 12BF
course_txt:			db 'COURSE - '							; 12C9
course_val_txt:		db 'xxxxxxxxxxxx', 0					; 12D2
level_race_txt:		db 'LEVEL '								; 12DF
level_txt:			db '1 - RACE '							; 12E5
race_start_txt:		db '99 OF '								; 12EE
race_end_txt:		db '99', 0								; 12F4
user_course_txt:	db 'USER DEFINED COURSE', 0				; 12F7
distance_txt:		db '01.234 KM OVER '					; 130B
stages_txt:			db '99 STAGES', 0						; 131A
laps_txt:			db '99 LAPS OF 01.234 KM', 0			; 1324
					db 0									; 1339
race_result_txt:	db 'RACE RESULT', 0						; 133A
race_columns_txt:	db 'POS   NAME              TIME    PTS' ; 1346
race_time_txt:		db '99.99.9'							; 1369
retired_txt:		db 'RETIRED'							; 1370
cast_txt:			db 'nijel mainsail      '				; 1377
					db 'alain phosphate     '
					db 'm. carburettor      '
					db 'ayrton sendup       '
					db 't. hairy bootson    '
					db 'mickey louder       '
					db 'ricardo pastry      '
					db 'nelson pickets      '
					db 'demon hill          '
					db 'crashhard banger    '
					db 'rissole brookes     '
					db 'stag bloomvest      '
					db 'merry walker        '
					db 'macaulay schenker   '
					db 'jackie stewpot      '
					db 'starling mess       '
					db 'derek werek         '
					db 'vim clark           '
arr_14DF:			times 12 db 20							; 14DF
arr_14F3:			times 12 db 20							; 14F3
arr_1507:			db 20, 15, 12, 10, 8, 6, 4, 3, 2, 1		; 1507

					db '20151210 8 6 4 3 2 1 0 0 0 0 0 0 0 0 0 0'; 151B
arr_1543:			rw 20									; 1543
word_156B:			dw ?									; 156B
word_156D:			dw ?									; 156D
scores_so_far_txt:	db 'SCORES SO FAR', 0					; 156F
final_scores_txt:	db 'FINAL SCORES', 0					; 157D 
pos_name_pts_txt:	db 'POS   NAME               PTS'		; 158A
arr_15A6:			rb 20									; 15A6
arr_15BA:			rw 20									; 15BA
current_pos_txt:	db 'CURRENT POSITIONS', 0				; 15E2
final_pos_txt:		db 'FINAL POSITIONS', 0					; 15F4
question_marks_txt:	db '????????'							; 1604
					db ' 1ST 2ND'

cfg_file_name:		db 'LOTUS.CFG', 0						; 16D8
cfg_data:			times 2087 db 0							; 16E2 .. 1F09

course_type:		dw ?									; 16EE: T1, T2, T3, Circular, Unknown

word_16F2:			dw ?									; 16F2
snd_setting:		dw ?									; 16F4: 4 - sound off
word_16F6:			dw ?									; 16F6
word_16F8:			dw ?									; 16F8
word_16FA:			dw ?
word_16FC:			dw ?
byte_16FE:			db ?
word_16FF:			dw ?

byte_1708:			db ?
word_1709:			dw ?
word_170B:			dw ?
byte_1715:			db ?
word_1716:			dw ?
byte_171F:			db ?
word_1720:			dw ?
word_1722:			dw ?
byte_172D:			db ?
byte_1745:			db ?

p1_name:			rb 12									; 17AC
p2_name:			rb 12									; 17B8
cfg_keys:			rb 64 * 12								; 17C4: 64 keys (12 chars each), e.g.: pwrwvwhnm-30
game_keys:			rb 9 * 12								; 1AC4: 9 keys (12 chars each), e.g.: xKXCJGFJH-33
; 1B30
game_code:			rb 12									; 1B3C

byte_1F08:			db ?									; 1F08
byte_1F09:			db ?									; 1F09
byte_1F0A:			db ?									; 1F0A
byte_1F0B:			db ?									; 1F0B
byte_1F0C:			db ?									; 1F0C
byte_1F0D:			db ?									; 1F0D
byte_1F0E:			db ?									; 1F0E

word_1F20:			dw ?									; 1F20

show_lotus_again:	db ?									; 1F23
demo_counter:		dw ?									; 1F24
word_1F26:			dw ?									; 1F26
word_1F28:			dw ?									; 1F28
arr_1F2A:			rw 10									; 1F2A
arr_1F3E:			rw 10									; 1F3E
word_1F52:			dw ?									; 1F52
word_1F54:			dw ?									; 1F54
word_1F56:			dw ?									; 1F56
byte_1F58:			db ?									; 1F58

word_1F93:			dw ?									; 1F93
word_1F95:			dw ?									; 1F95
word_1F97:			dw ?									; 1F97
word_1F99:			dw ?									; 1F99
					dw ?									; 1F9B
word_1F9D:			dw ?									; 1F9D
byte_1F9F:			db ?									; 1F9F
word_1FA0:			dw ?									; 1FA0
word_1FA2:			dw ?									; 1FA2
word_1FA4:			dw ?									; 1FA4
word_1FA6:			dw ?									; 1FA6
word_1FA8:			dw ?									; 1FA8
word_1FAA:			dw ?									; 1FAA
word_1FAC:			dw ?									; 1FAC
word_1FAE:			dw ?									; 1FAE

word_1FD2:			dw ?									; 1FD2
word_1FD4:			dw ?									; 1FD4
word_1FD6:			dw ?									; 1FD6
word_1FD8:			dw ?									; 1FD8
word_1FDA:			dw ?									; 1FDA
word_1FDC:			dw ?									; 1FDC
word_1FDE:			dw ?									; 1FDE
word_1FE0:			dw ?									; 1FE0
word_1FE2:			dw ?									; 1FE2
word_1FE4:			dw ?									; 1FE4
word_1FE6:			dw ?									; 1FE6
word_1FE8:			dw ?									; 1FE8
word_1FEA:			dw ?									; 1FEA
word_1FEC:			dw ?									; 1FEC
word_1FEE:			dw ?									; 1FEE
word_1FF0:			dw ?									; 1FF0
word_1FF2:			dw ?									; 1FF2
word_1FF4:			dw ?									; 1FF4
word_1FF6:			dw ?									; 1FF6
word_1FF8:			dw ?									; 1FF8
word_1FFA:			dw ?									; 1FFA
word_1FFC:			dw ?									; 1FFC
word_1FFE:			dw ?									; 1FFE
word_2000:			dw ?									; 2000
word_2002:			dw ?									; 2002
word_2004:			dw ?									; 2004
word_2006:			dw ?									; 2006
word_2008:			dw ?									; 2008
word_200A:			dw ?									; 200A
word_200C:			dw ?									; 200C
word_200E:			dw ?									; 200E
arr_2010:			rw 40									; 2010
word_2060:			dw ?									; 2060
word_2062:			dw ?									; 2062
word_2064:			dw ?									; 2064
struct_2066:		dw ?									; 2066
					dw ?									; +2
					dw ?									; +4
					dw ?									; +6
					dw ?									; +8
					dw ?									; +10
					dw ?									; +12
					dw ?									; +14
paused_txt:			db 'PAUSED', 0							; 2076
demo_txt:			db 'DEMO', 0							; 207D
race_completed_txt:	db 'RACE COMPLETED', 0					; 2082
out_of_time_txt:	db 'OUT OF TIME', 0						; 2091
race_over_txt:		db 'RACE OVER', 0						; 209D
out_of_fuel_txt:	db 'OUT OF FUEL', 0						; 20A7
turbo_zone_txt:		db 'TURBO ZONE', 0						; 20B3
checkpoint_txt:		db 'CHECKPOINT', 0						; 20BE
low_fuel_txt:		db 'LOW FUEL', 0						; 20C9
ahead_txt:			db '???????????? AHEAD', 0				; 20D2
					db 0									; 20E5
print_tmp_str:		times 40 db 0							; 20E6
print_font_ix:		db 0									; 210E
					db 0									; 210F
word_2110:			dw ?									; 2110
word_2112:			dw ?									; 2112
word_2114:			dw ?									; 2114

; 21FA
word_21FC:			dw ?									; 21FC
word_21FE:			dw ?									; 21FE
word_2200:			dw ?									; 2200
word_2202:			dw ?									; 2202
word_2204:			dw ?									; 2204
word_2206:			dw ?									; 2206
word_2208:			dw ?									; 2208
word_220A:			dw ?									; 220A
word_220C:			dw ?									; 220C
word_220E:			dw ?									; 220E
word_2210:			dw ?									; 2210
word_2212:			dw ?									; 2212
word_2214:			dw ?									; 2214
word_2216:			dw ?									; 2216
word_2218:			dw ?									; 2218
word_221A:			dw ?									; 221A
word_221C:			dw ?									; 221C
; 221E

word_2350:			dw ?									; 2350
word_2352:			dw ?									; 2352
word_2354:			dw ?									; 2354

word_239A:			dw ?									; 239A
word_239C:			dw ?									; 239C
word_239E:			dw ?									; 239E
word_23A0:			dw ?									; 23A0
arr_23A2:			dw sub_A5F3								; 23A2
					dw sub_A64C								; 23A4
					dw sub_A69A								; 23A6
					dw sub_A6F2								; 23A8
					dw sub_A74E								; 23AA
					dw sub_A7B0								; 23AC
					dw sub_A803								; 23AE
					dw sub_A85F								; 23B0

					dw sub_A860								; 23B2
					dw sub_A860								; 23B4
					dw sub_A860								; 23B6
					dw sub_A860								; 23B8
					dw sub_A867								; 23BA
					dw sub_A86E								; 23BC
					dw sub_A875								; 23BE
					dw sub_A87C								; 23C0

					dw sub_A884								; 23C2
					dw sub_A896								; 23C4
					dw sub_A8AA								; 23C6
					dw sub_A8B9								; 23C8
					dw sub_A8C9								; 23CA
					dw sub_A8DB								; 23CC
					dw sub_A8ED								; 23CE
					dw sub_A900								; 23D0

					dw sub_A914								; 23D2
					dw sub_A92C								; 23D4
					dw sub_A944								; 23D6
					dw sub_A95C								; 23D8
					dw sub_A974								; 23DA
					dw sub_A98C								; 23DC
					dw sub_A9A4								; 23DE
					dw sub_A9BB								; 23E0

arr_23E2:			db 9, 11, 1, 6, 12, 3, 8, 7, 4, 2, 5, 10, 0		; 23E2
; 23EF

num_of_tracks:		dw ?									; 23F0
word_23F2:			dw ?									; 23F2
is_circular_track:	dw 0									; 23F4
word_23F6:			dw 1									; 23F6
word_23F8:			dw ?									; 23F8
word_23FA:			dw ?									; 23FA
word_23FC:			dw ?									; 23FC
word_23FE:			dw ?									; 23FE
arr_2400:			rw 17									; 2400
word_2422:			rw 16									; 2422
word_2442:			dw ?									; 2442
word_2444:			dw ?									; 2444
word_2446:			dw ?									; 2446
word_2448:			dw ?									; 2448
word_244A:			dw ?									; 244A
word_244C:			dw ?									; 244C
word_244E:			dw ?									; 244E
word_2450:			dw ?									; 2450
word_2452:			dw ?									; 2452
word_2454:			dw ?									; 2454
word_2456:			dw ?									; 2456
word_2458:			dw ?									; 2458
word_245A:			dw ?									; 245A
word_245C:			dw ?									; 245C
word_245E:			dw ?									; 245E
word_2460:			dw ?									; 2460
word_2462:			dw ?									; 2462
word_2464:			dw ?									; 2464
word_2466:			dw ?									; 2466
word_2468:			dw ?									; 2468
word_246A:			dw ?									; 246A
word_246C:			dw ?									; 246C
word_246E:			dw ?									; 246E
word_2470:			dw ?									; 2470
word_2472:			dw ?									; 2472
word_2474:			dw ?									; 2474
word_2476:			dw ?									; 2476
word_2478:			dw ?									; 2478
word_247A:			dw ?									; 247A
word_247C:			dw ?									; 247C
word_247E:			dw ?									; 247E
word_2480:			dw ?									; 2480
word_2482:			dw ?									; 2482
word_2484:			dw ?									; 2484
word_2486:			dw ?									; 2486
word_2488:			dw ?									; 2488
word_248A:			dw ?									; 248A
word_248C:			dw ?									; 248C
rnd_248E:			rw 8									; 248E
word_249E:			dw ?									; 249E

word_27F2:			dw ?									; 27F2

arr_2A4C:			dw 5082h, 511Ah, 51B2h, 51BCh, 5254h, 52ECh, 52F6h, 5394h, 542Ch	; 2A4C
word_2A5E:			dw ?									; 2A5E
word_2A60:			dw ?									; 2A60
word_2A62:			dw ?									; 2A62

word_2AB2:			dw ?									; 2AB2
; 2AB4
word_2AB6:			dw ?									; 2AB6
word_2AB8:			dw ?									; 2AB8
arr_2ABA:			dw 0Fh, 355h, 6AAh, 8					; 2ABA
arr_2AC2:			dw 0Fh, 355h, 6AAh, 8					; 2AC2
arr_2ACA:			dw 14h, 0, 0A00h, 4						; 2ACA
arr_2AD2:			dw 19h, 6AAh, 6AAh, 4					; 2AD2
arr_2ADA:			dw 1Eh, 0A00h, 0A00h, 2					; 2ADA
word_2AE2:			dw ?									; 2AE2
word_2AE4:			dw ?									; 2AE4
word_2AE6:			dw ?									; 2AE6
word_2AE8:			dw ?									; 2AE8
arr_2AEA:			db 0, 22, 13, 3, 4, 5, 6, 31, 8, 9, 10, 11, 12		; 2AEA
word_2AF7:			dw ?									; 2AF7
word_2AF9:			dw ?									; 2AF9
					db ?									; 2AFB
word_2AFC:			dw ?									; 2AFC
word_2AFE:			dw ?									; 2AFE
byte_2B00:			db ?									; 2B00
					db ?									; 2B01
word_2B02:			dw ?									; 2B02
arr_2B04:			rb 32									; 2B04
; 2B24

word_2C24:			dw ?									; 2C24
byte_2C26:			db ?									; 2C26

byte_2C66:			db ?									; 2C66

word_2C76:			dw ?									; 2C76
word_2C78:			dw ?									; 2C78
word_2C7A:			dw ?									; 2C7A
word_2C7C:			dw ?									; 2C7C

; struct word_2D76
word_2D76:			dw ?									; 2D76
					dw ?									; 2D78
					dw ?									; 2D7A
word_2D7C:			dw ?									; 2D7C
word_2D7E:			dw ?									; 2D7E
word_2D80:			dw ?									; 2D80
					rw 7									; 2D82..=2D8E
word_2D90:			dw ?									; 2D90

word_2DAA:			dw ?									; 2DAA
word_2DAE:			dw ?									; 2DAE
word_2DB0:			dw ?									; 2DB0
word_2DB2:			dw ?									; 2DB2
word_2DB4:			dw ?									; 2DB4
					dw ?									; 2DB6
word_2DB8:			dw ?									; 2DB8

word_2DDE:			dw ?									; 2DDE

word_2DE6:			dw ?									; 2DE6

word_2DEE:			dw ?									; 2DEE

; 2D74
; -- struct word_2D76 ends here

word_2E2E:			dw ?									; 2E2E

word_2E34:			dw ?									; 2E34

word_2E76:			dw ?									; 2E76
word_2E78:			dw ?									; 2E78
word_2E7A:			dw ?									; 2E7A
word_2E7C:			dw ?									; 2E7C

byte_2E81:			db ?									; 2E81

chr_bmp_ptr:		rw 6									; 3106

res_key:			rb 8									; 315A
; 3162

arc_header:			rb 2816									; 3164
arc_file_name:		db 'LOTUS.DAT', 0						; 3C64
arc_file_handle:	dw ?									; 3C6E
word_3C70:			dw ?									; 3C70
word_3C72:			dw ?									; 3C72
word_3C74:			dw ?									; 3C74
word_3C76:			dw ?									; 3C76
arr_3C78:			dw 0, 6, 12h, 1Ah, 1Eh, 24h, 2Eh, 36h	; 3C78
					dw 0, 0CA00h, 1,  2800h, 1,  8600h, 1, 0E400h
					dw 2, 0A200h, 2, 0A000h, 2, 0FE00h, 3,  5C00h
					dw 3, 0BA00h, 4,  1800h, 4,  7200h, 4, 0D000h
					dw 5,  2E00h, 5,  8C00h, 5, 0EA00h, 6,  4800h
					dw 6, 0A600h, 7,   400h, 7,  6200h, 7, 0C000h
word_3CD8:			dw ?									; 3CD8
word_3CDA:			dw ?									; 3CDA
word_3CDC:			dw ?									; 3CDC
word_3CDE:			dw ?									; 3CDE
word_3CE0:			dw ?									; 3CE0
word_3CE2:			dw ?									; 3CE2
word_3CE4:			dw ?									; 3CE4
word_3CE6:			dw ?									; 3CE6
word_3CE8:			dw ?									; 3CE8
word_3CEA:			dw ?									; 3CEA

word_3D10:			dw ?									; 3D10
word_3D12:			dw ?									; 3D12

word_3D34:			dw ?									; 3D34
word_3D36:			dw ?									; 3D36
word_3D38:			dw ?									; 3D38
word_3D3A:			dw ?									; 3D3A
word_3D3C:			dw ?									; 3D3C
word_3D3E:			dw ?									; 3D3E
word_3D40:			dw ?									; 3D40
word_3D42:			dw ?									; 3D42
arr_3D44:			rb 9									; 3D44
arr_3D4E:			db 18h									; a
					db 12h									; b
					db 17h									; c
					db 10h									; d
					db 16h									; e
					db 11h									; f
					db 0Ch									; g
					db 19h									; h
					db 0Eh									; i
					db 13h									; j
					db 1Ah									; k
					db 0Fh									; l
					db 6									; m
					db 0Dh									; _
					db 8									; n
					db 0Bh									; o
					db 3									; p
					db 5									; q
					db 1									; r
					db 9									; s
					db 15h									; t
					db 14h									; u
					db 4									; v
					db 2									; w
					db 0									; x
					db 7									; y
					db 0Ah									; z
					db 0									; 3D69
byte_3D6A:			db ?
word_3D6C:			dw ?
word_3D6E:			dw ?
word_3D70:			dw ?
byte_3D72:			db ?
dos_vid_mode:		db ?									; 3D73
byte_3D74:			db ?
word_3D76:			dw ?
word_3D78:			dw ?
word_3D7A:			dw ?
byte_3D7C:			db ?
word_3D7E:			dw ?
word_3D80:			dw ?
word_3D82:			dw ?
word_3D84:			dw ?
byte_3D86:			db ?
byte_3D87:			db ?
byte_3D88:			db ?									; 3D88
byte_3D89:			db ?									; 3D89
byte_3DA1:			db ?									; 3DA1

byte_3DA4:			db ?									; 3DA4

byte_3DD0:			db ?
byte_3DD2:			db ?									; 3DD2
byte_3DD3:			db ?									; 3DD3
byte_3DD5:			db ?									; 3DD5
byte_3DD6:			db ?									; 3DD6
byte_3DD8:			db ?
word_3E08:			dw ?
word_3E0A:			dw ?
word_3E0C:			dw ?
byte_3E0E:			db ?
byte_3E0F:			db ?
byte_3E10:			db ?
word_3E12:			dw ?
word_3E14:			dw ?
word_3E16:			dw ?
word_3E18:			dw ?
word_3E1A:			dw ?
word_3E1C:			dw ?

word_3E20:			dw ?
word_3E22:			dw ?
byte_3E24:			db ?
byte_3E25:			db ?
byte_3E2C:			db ?
byte_3E2D:			db ?
word_3E2E:			dw ?

word_3E30:			dw ?
word_3E32:			dw ?
create_error:		db 'ERROR: Can''t create $', 0			; 3E34
open_error:			db 'ERROR: Can''t open $', 0			; 3E4A
read_error:			db 'ERROR: Read error in $', 0			; 3E5E
write_error:		db 'ERROR: Write error in $', 0			; 3E76
close_error:		db 'ERROR: Can''t close $', 0			; 3E8E
					db 0									; 3EA3
err_str_ptr:		dw 0									; 3EA4
memory_error:		db 'HELP! Memory full.', 0				; 3EA6
word_3EB9:			dw 3EBCh								; 3EB9
byte_3EBB:			db 0									; 3EBB
version_str:		db 'LOTUS III  Version 14/07/93', 0		; 3EBC
word_3ED8:			dw ?									; 3ED8
word_3EDA:			dw ?									; 3EDA: -------------------------------
num_of_players:		dw ?									; 3EDC: P1 or P1 + P2
race_type:			dw ?									; 3EDE: TimeLimit, Competition
word_3EE0:			dw ?									; 3EE0
word_3EE2:			dw ?									; 3EE2
word_3EE4:			dw ?									; 3EE4
word_3EE6:			dw ?									; 3EE6
word_3EE8:			dw ?									; 3EE8
word_3EEA:			dw ?									; 3EEA
word_3EEC:			dw ?									; 3EEC
rnd_3EEE:			rw 8									; 3EEE
rnd_3EFE:			rw 8									; 3EFE
arr_3F0E:			rw 16									; 3F0E
arr_3F2E:			rb 12									; 3F2E
word_3F3A:			dw ?									; 3F3A, is a struct
word_3F3C:			dw ?									; 3F3C
word_3F3E:			dw ?									; 3F3E
					dw ?									; 3F40
word_3F42:			dw ?									; 3F42
word_3F44:			dw ?									; 3F44
word_3F46:			db ?									; 3F46
					db ?									; 3F47
word_3F48:			dw ?									; 3F48
					dw ?									; 3F4A

word_3F54:			dw ?									; 3F54

word_3F5A:			dw ?									; 3F5A
word_3F5C:			dw ?									; 3F5C

word_3F68:			dw ?									; 3F68
word_3F6A:			dw ?									; 3F6A
byte_3F6C:			db ?									; 3F6C
byte_3F6D:			db ?									; 3F6D
word_3F6E:			dw ?									; 3F6E
byte_3F70:			db ?									; 3F70
p1_accel:			dw ?									; 3F72: P1 acceleration
p1_gears:			dw ?									; 3F74: P1 gears

word_3F80:			dw ?									; 3F80
word_3F82:			dw ?									; 3F82

word_3FB4:			dw ?									; 3FB4
word_3FB6:			dw ?									; 3FB6
word_3FB8:			dw ?									; 3FB8
word_3FBA:			dw ?									; 3FBA
word_3FBC:			dw ?									; 3FBC
word_3FBE:			dw ?									; 3FBE
word_3FC0:			dw ?									; 3FC0
word_3FC2:			dw ?									; 3FC2

word_3FCA:			dw ?									; 3FCA

word_3FD2:			dw ?									; 3FD2

word_3FE2:			dw ?									; 3FE2

word_3FF0:			dw ?									; 3FF0

word_400C:			dw ?									; 400C

word_4012:			dw ?									; 4012

word_4018:			dw ?									; 4018
word_401A:			dw ?									; 401A
word_401C:			dw ?									; 401C
word_401E:			dw ?									; 401E

word_4026:			dw ?									; 4026
word_4028:			dw ?									; 4028
word_402A:			dw ?									; 402A

word_4034:			dw ?									; 4034
word_4036:			dw ?									; 4036
word_4038:			dw ?									; 4038
					dw ?									; 403A
word_403C:			dw ?									; 403C
word_403E:			dw ?									; 403E
word_4040:			dw ?									; 4040
word_4042:			dw ?									; 4042
					dw ?									; 4044
					dw ?									; 4046
					dw ?									; 4048
					dw ?									; 404A
					dw ?									; 404C
word_404E:			dw ?									; 404E

word_4054:			dw ?									; 4054
word_4056:			dw ?									; 4056

word_4062:			dw ?									; 4062
word_4064:			dw ?									; 4064
byte_4066:			db ?									; 4066
					db ?									; 4067
byte_4068:			db ?									; 4068
					db ?									; 4069
byte_406A:			db ?									; 406A
					db ?									; 406B
p2_accel:			dw ?									; 406C: P2 acceleration
p2_gears:			dw ?									; 406E: P2 gears
					rw 6									; 4070..=4078
word_407A:			dw ?									; 407A
word_407C:			dw ?									; 407C

; 40AC
word_40AE:			dw ?									; 40AE
word_40B0:			dw ?									; 40B0
word_40B2:			dw ?									; 40B2
word_40B4:			dw ?									; 40B4
word_40B6:			dw ?									; 40B6
word_40B8:			dw ?									; 40B8
word_40BA:			dw ?									; 40BA
word_40BC:			dw ?									; 40BC

word_40C4:			dw ?									; 40C4

word_40CC:			dw ?									; 40CC

word_40DC:			dw ?									; 40DC

word_40EA:			dw ?									; 40EA

word_4106:			dw ?									; 4106

word_410C:			dw ?									; 410C

word_4112:			dw ?									; 4112
word_4114:			dw ?									; 4114
word_4116:			dw ?									; 4116
word_4118:			dw ?									; 4118

word_4120:			dw ?									; 4120
word_4122:			dw ?									; 4122
word_4124:			dw ?									; 4124

word_41DE:			dw ?									; 41DE
word_41E0:			dw ?									; 41E0

; 426E: ------------------------------------

word_42F6:			dw ?									; 42F6
					dw ?									; 42F8
word_42FA:			dw ?									; 42FA
					dw ?									; 42FC
word_42FE:			dw ?									; 42FE
					dw ?									; 4300
word_4302:			dw ?									; 4302
word_4306:			dw ?									; 4306
word_4308:			dw ?									; 4308

word_43A6:			dw ?									; 43A6
; 43A8

word_46E8:			dw ?									; 46E8

word_4A2A:			dw ?									; 4A2A

word_4E78:			dw ?									; 4E78

word_54CE:			dw ?									; 54CE

word_6040:			dw ?									; 6040

; 632C
word_632E:			dw ?									; 632E, si
word_6330:			dw ?									; 6330, es
; 6332
word_6334:			dw ?									; 6334
word_6336:			dw ?									; 6336
word_6338:			dw ?									; 6338
word_633A:			dw ?									; 633A
track_num:			dw ?									; 633C
word_633E:			dw ?									; 633E
word_6340:			dw ?									; 6340
word_6342:			dw ?									; 6342
word_6344:			dw ?									; 6344
word_6346:			dw ?									; 6346
word_6348:			dw ?									; 6348
word_634A:			dw ?									; 634A
word_634C:			dw ?									; 634C
word_634E:			dw ?									; 634E
word_6350:			dw ?									; 6350
word_6352:			dw ?									; 6352
word_6354:			dw ?									; 6354
word_6356:			dw ?									; 6356
word_6358:			dw ?									; 6358
word_635A:			dw ?									; 635A
word_635C:			dw ?									; 635C
word_635E:			dw ?									; 635E
word_6360:			dw ?									; 6360
word_6362:			dw ?									; 6362
word_6364:			dw ?									; 6364
word_6366:			dw ?									; 6366
word_6368:			dw ?									; 6368
word_636A:			dw ?									; 636A
word_636C:			dw ?									; 636C
word_636E:			dw ?									; 636E
word_6370:			dw ?									; 6370
word_6372:			dw ?									; 6372
word_6374:			dw ?									; 6374
word_6376:			dw ?									; 6376
word_6378:			dw ?									; 6378
word_637A:			dw ?									; 637A
word_637C:			dw ?									; 637C
word_637E:			dw ?									; 637E
word_6380:			dw ?									; 6380
word_6382:			dw ?									; 6382
word_6384:			dw ?									; 6384
word_6386:			dw ?									; 6386
word_6388:			dw ?									; 6388
word_638A:			dw ?									; 638A
word_638C:			dw ?									; 638C
word_638E:			dw ?									; 638E
word_6390:			dw ?									; 6390
word_6392:			dw ?									; 6392
word_6394:			dw ?									; 6394
word_6396:			dw ?									; 6396
word_6398:			dw ?									; 6398
word_639A:			dw ?									; 639A
word_639C:			dw ?									; 639C
word_639E:			dw ?									; 639E
word_63A0:			dw ?									; 63A0
word_63A2:			dw ?									; 63A2
word_63A4:			dw ?									; 63A4
word_63A6:			dw ?									; 63A6
word_63A8:			dw ?									; 63A8
word_63AA:			dw ?									; 63AA
word_63AC:			dw ?									; 63AC
word_63AE:			dw ?									; 63AE
word_63B0:			dw ?									; 63B0
word_63B2:			dw ?									; 63B2
word_63B4:			dw ?									; 63B4
playing_demo:		dw ?									; 63B6
is_paused:			dw ?									; 63B8
word_63BA:			dw ?									; 63BA, unpacked data
word_63BC:			dw ?									; 63BC
word_63BE:			dw ?									; 63BE
dat_file_handle:	dw ?									; 63C0
arr_63C2:			rw 512									; 63C2
arr_67C2:			rw 128									; 67C2
arr_68C2:			rw 128									; 68C2
arr_69C2:			rw 128									; 69C2
arr_6AC2:			rw 128									; 6AC2
arr_6BC2:			rw 257									; 6BC2
arr_6DC4:			rw 201									; 6DC4
arr_6F56:			rb 256 * 3								; 6F56
palette2:			rb 256 * 3								; 7256
palette:			rb 256 * 3								; 7556
arr_7856:			rb 2304									; 7856
tmp_file_buf:		rb 17408								; 8156
; C556

arr_C568:			rw 512									; C568
; C968
