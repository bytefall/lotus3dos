;
;
;
sub_352C:								; 352C
	push	ds
	push	ds
	pop		es
	push	cx
	mov		ax, cx
	shl		cx, 1
	add		cx, ax
	mov		di, palette
	mov		ds, [word_F77]
	mov		si, 0
	rep movsb
	pop		ax
	mov		cx, 100h
	sub		cx, ax
	mov		ax, cx
	add		cx, ax
	mov		al, 0
	rep stosb
	pop		ds
	ret


default_logo:							; 3552
	call	fade_out
	mov		ax, [word_5166]
	mov		[word_63BA], ax
	mov		al, 18h
	mov		ah, 'Q'						; Q18 = Lotus logo
	call	res_load
	push	ds
	push	ds
	pop		es
	sub		ax, 30h
	mov		ds, ax
	mov		si, 0
	mov		di, palette
	mov		cx, 768
	rep movsb
	pop		ds
	mov		si, [word_63BA]
	mov		di, 0
	mov		ax, 320
	mov		bx, 200
	call	draw_sprite
	call	update_screen
	call	fade_in
	mov		word [word_3E18], 0
	mov		ax, 1400
	call	sleep
	ret


old_logo:								; 359A
	call	sub_D915					; Fill stack with some data.
	call	fade_out
	mov		ax, [word_5166]
	mov		[word_63BA], ax
	mov		al, 3
	cmp		[song_num], al
	jz		main_menu
	call	play_music
	call	sub_20ED


main_menu:								; 35B5
	mov		si, main_menu_fnt_ids		; 3, 4, 5, -1
	mov		word [word_2E78], 0
	call	chr_load_and_prepare_few
	mov		si, main_menu_res_ids		; 14, 15, 16, 17, 18, 19, 1A, 1B, 1F, 20, -1
	mov		di, res_ptr_I14
	mov		ah, 'I'
	call	load_resource_series
	mov		word [curr_menu_col], 1		; X = 2nd column
	mov		word [curr_menu_row], 0		; Y = 1st column

main_menu_loop:							; 35D8
	call	sub_D915					; Fill stack with some data.
	call	fade_out					; jumps here from sub_5336
	mov		ax, [res_ptr_I14]			; I14
	call	res_unpack_with_pal
	mov		si, [word_63BA]
	mov		di, 0
	mov		ax, 320
	mov		bx, 200
	call	draw_sprite					; draw I14
	mov		ax, [res_ptr_I15]			; I15
	call	res_unpack_simple
	call	draw_main_menu_items
	call	fade_in

loc_3600:
	mov		word [word_3E18], 0

loc_3606:
	call	draw_main_menu_items
	mov		ax, loc_DC70
	call	handle_esc_key
	call	sub_D6F9
	call	sub_575C
	cmp		byte [byte_1F58], 0
	jz		loc_364A
	push	ax
	push	bx
	mov		ax, [word_3E30]
	mov		dl, 0D6h
	div		dl
	mov		ah, 0
	mov		cx, ax
	xchg	cx, [curr_menu_col]
	mov		ax, [word_3E32]
	mov		dl, 28h
	div		dl
	mov		ah, 0
	mov		dx, ax
	xchg	dx, [curr_menu_row]
	pop		bx
	pop		ax
	cmp		cx, [curr_menu_col]
	jnz		loc_3600
	cmp		dx, [curr_menu_row]
	jnz		loc_3600

loc_364A:
	test	al, 1
	jz		loc_365B
	cmp		word [curr_menu_col], 0
	jz		loc_3600
	dec		word [curr_menu_col]
	jmp		loc_3600

loc_365B:
	test	al, 2
	jz		loc_366C
	cmp		word [curr_menu_col], 2
	jae		loc_3600
	inc		word [curr_menu_col]
	jmp		loc_3600

loc_366C:
	test	al, 8
	jz		loc_367D
	cmp		word [curr_menu_row], 0
	jz		loc_3600
	dec		word [curr_menu_row]
	jmp		loc_3600

loc_367D:
	test	al, 4
	jz		loc_3692
	cmp		word [curr_menu_row], 4
	jb		loc_368B
	jmp		loc_3600

loc_368B:
	inc		word [curr_menu_row]
	jmp		loc_3600

loc_3692:
	test	al, 48
	jnz		loc_3699
	jmp		loc_3606

loc_3699:
	mov		ax, 3
	mul		word [curr_menu_row]
	add		ax, [curr_menu_col]
	mov		bx, ax
	shl		bx, 2
	mov		cx, [bx + 0FA0h]
	mov		si, [bx + 0FA2h]
	cmp		cx, 5
	jae		loc_36C6
	inc		word [si]
	cmp		word [si], cx
	ja		loc_36BF
	jmp		loc_3600

loc_36BF:
	mov		word [si], 0
	jmp		loc_3600

loc_36C6:
	and		si, si
	jnz		loc_36CD
	jmp		loc_3600

loc_36CD:
	call	si							; jump to xxx_menu proc
										;
										; 522E - Start Menu
	jmp		loc_3600


;
; Draws main menu items (P1 and P2 name, gears, etc.) and a red frame.
;
draw_main_menu_items:					; 36D2
	mov		ax, [cfg_data + 4]
	mov		[p1_gears], ax
	mov		ax, [cfg_data + 6]
	mov		[p2_gears], ax
	mov		ax, [cfg_data + 8]
	mov		[p1_accel], ax
	mov		ax, [cfg_data + 10]
	mov		[p2_accel], ax
	mov		ax, [cfg_data + 2]
	mov		[num_of_players], ax
	mov		ax, [cfg_data + 0]
	mov		[race_type], ax

	mov		ax, 13
	mov		bx, 21
	mov		ch, 4
	mov		dx, 12
	mov		si, p1_name
	call	print_empty_string
	call	print_string_narrow

	mov		ax, 221
	mov		bx, 21
	mov		ch, 4
	mov		dx, 12
	mov		si, p2_name
	call	print_empty_string
	call	print_string_narrow

	mov		ax, 117
	mov		bx, 177
	mov		ch, 3
	mov		dx, 12
	mov		si, game_code
	call	print_empty_string
	call	print_string_narrow

	mov		ax, 6
	mov		bx, 52
	mov		cx, 0
	add		cx, [p1_gears]
	call	draw_menu_item

	mov		ax, 6
	mov		bx, 91
	mov		cx, 2
	add		cx, [p1_accel]
	call	draw_menu_item

	mov		ax, 214
	mov		bx, 52
	mov		cx, 0
	add		cx, [p2_gears]
	call	draw_menu_item

	mov		ax, 214
	mov		bx, 91
	mov		cx, 2
	add		cx, [p2_accel]
	call	draw_menu_item

	mov		ax, 110
	mov		bx, 52
	mov		cx, 6
	add		cx, [race_type]
	call	draw_menu_item

	mov		ax, 110
	mov		bx, 91
	mov		cx, 10
	add		cx, [course_type]
	call	draw_menu_item

	mov		ax, 110
	mov		bx, 130
	mov		cx, 8
	add		cx, [num_of_players]
	call	draw_menu_item

	call	sub_389E
	mov		ax, [curr_menu_row]
	mov		dx, 39
	mul		dx
	mov		bx, ax
	mov		ax, [curr_menu_col]
	mov		dx, 104
	mul		dx
	add		ax, 8
	add		bx, 7
	mov		cx, 95
	mov		dx, 30
	call	draw_menu_frame

	call	sub_37CA
	ret


;
;
;
sub_37CA:								; 37CA
	cmp		word [word_16FF], 2
	jnz		loc_37FE
	mov		ax, [word_3E30]
	shr		ax, 1
	add		ax, 1360
	mov		[dword_FDC], ax
	mov		ax, 21
	mul		word [word_3E32]
	add		ax, [word_63BC]
	mov		[dword_FDC + 2], ax
	mov		ax, 200
	sub		ax, [word_3E32]
	mov		[word_FE0], ax
	call	sub_3802
	call	update_screen
	call	sub_3834
	ret

loc_37FE:
	call	update_screen
	ret


;
;
;
sub_3802:								; 3802
	les		di, [dword_FDC]
	mov		dx, [word_FE0]
	and		dx, dx
	jz		ret_3833
	cmp		dx, 11
	jbe		loc_3816
	mov		dx, 11

loc_3816:
	mov		si, arr_FE2

loc_3819:
	mov		cx, 8

loc_381C:
	lodsb
	dec		al
	js		loc_3829
	neg		al
	xchg	al, [es:di]
	mov		[si + 57h], al

loc_3829:
	inc		di
	loop	loc_381C
	add		di, 148h
	dec		dx
	jnz		loc_3819

ret_3833:
	ret


;
;
;
sub_3834:								; 3834
	les		di, [dword_FDC]
	mov		dx, [word_FE0]
	and		dx, dx
	jz		ret_3863
	cmp		dx, 11
	jbe		loc_3848
	mov		dx, 11

loc_3848:
	mov		si, arr_FE2

loc_384B:
	mov		cx, 8

loc_384E:
	lodsb
	and		al, al
	jz		loc_3859
	mov		al, [si + 57h]
	mov		[es:di], al

loc_3859:
	inc		di
	loop	loc_384E
	add		di, 148h
	dec		dx
	jnz		loc_384B

ret_3863:
	ret


; Draws 104x26 sprite.
;
; input:
; (ax, bx) - x, y
; cx - unpacked texture index
; word_63BA - unpacked data
draw_menu_item:							; 3864
	mov		di, ax
	mov		ax, 336
	mul		bx
	add		di, ax
	mov		ax, 169
	mul		cx
	mov		si, ax
	add		si, [word_63BA]
	mov		ax, 104
	mov		bx, 26
	jmp		draw_sprite


; Clear screen area with an empty string.
;
; input:
; (ax, bx) - x, y
; ch - unpacked texture index
; dx - length
print_empty_string:						; 3881
	push	ax
	push	dx

loc_3883:
	mov		cl, 0
	call	draw_char_small
	add		ax, 7
	dec		dx
	jnz		loc_3883
	pop		dx
	pop		ax
	ret


; Prints a text with narrow spacing between letters.
;
; input:
; (ax, bx) - x, y
; ch - unpacked texture index
; dx - length
; ds:si - string
print_string_narrow:					; 3891
	mov		cl, [si]
	inc		si
	call	draw_char_small
	add		ax, 7
	dec		dx
	jnz		print_string_narrow
	ret


;
;
;
sub_389E:								; 389E
	push	ds
	mov		ax, 0A8h
	mul		word [word_1094]
	mov		cx, ax
	jcxz	loc_38BB
	mov		ds, [word_1092]
	mov		di, 0
	mov		ax, 1F1Fh

loc_38B4:
	and		[di], ax
	add		di, 2
	loop	loc_38B4

loc_38BB:
	pop		ds
	ret


; Draws a red frame around current menu item.
;
; input:
; ax - col * 104 + 8
; bx - row * 39 + 7
; cx - frame width (95 for standard frame)
; dx - frame height (30 for standard frame)
draw_menu_frame:						; 38BD
	push	ds
	add		cx, 4
	add		dx, 4
	push	cx
	push	dx
	add		dx, 8
	mov		[word_1094], dx				; = frame_height + 4 + 8
	sub		ax, 6
	sub		bx, 6
	mov		di, 1360					; = 1360 = 336 * 4
	add		di, ax
	mov		ax, 336
	mul		bx
	add		di, ax						; offset = x_pos(ax) - 6 + y_pos + 4_row
	mov		ax, di
	and		di, 0Fh
	shr		ax, 4
	add		ax, [word_63BC]
	mov		[word_1092], ax
	mov		ds, ax
	; draw upper left corner:
	or		word [di + 2], 6060h
	or		word [di + 336], 6000h
	or		word [di + 338], 2040h
	or		word [di + 672], 4060h
	or		word [di + 674], 4020h
	or		word [di + 1008], 2060h
	or		word [di + 1010], 6040h
	add		di, 4
	pop		dx
	pop		cx
	push	cx
	push	dx

loc_3920:								; draw upper line
	or		byte [di], 60h				; black
	or		byte [di + 336], 20h		; red
	or		byte [di + 672], 60h		; black
	inc		di
	loop	loc_3920
	or		word [di], 6060h
	or		word [di + 150h], 4020h
	or		word [di + 152h], 60h
	or		word [di + 2A0h], 2040h
	or		word [di + 2A2h], 6040h
	or		word [di + 3F0h], 4060h
	or		word [di + 3F2h], 6020h
	add		di, 540h
	pop		cx
	push	cx

loc_395D:
	or		byte [di + 1], 60h
	or		word [di + 2], 6020h
	add		di, 150h
	loop	loc_395D
	or		word [di], 4060h
	or		word [di + 2], 6020h
	or		word [di + 150h], 2040h
	or		word [di + 152h], 6040h
	or		word [di + 2A0h], 4020h
	or		word [di + 2A2h], 60h
	or		word [di + 3F0h], 6060h
	pop		dx
	pop		cx
	push	dx

loc_3995:
	dec		di
	or		byte [di + 150h], 60h
	or		byte [di + 2A0h], 20h
	or		byte [di + 3F0h], 60h
	loop	loc_3995
	sub		di, 4
	or		word [di], 2060h
	or		word [di + 2], 6040h
	or		word [di + 150h], 4060h
	or		word [di + 152h], 4020h
	or		word [di + 2A0h], 6000h
	or		word [di + 2A2h], 2040h
	or		word [di + 3F2h], 6060h
	pop		cx

loc_39D2:
	sub		di, 336
	or		word [di], 2060h
	or		byte [di + 2], 60h
	loop	loc_39D2
	pop		ds
	ret


;
;
;
sub_39E2:								; 39E2
	mov		word [y_pos], 13
	mov		word [x_pos], 21
	mov		byte [byte_12A3], 4
	mov		word [str_ptr], p1_name
	mov		word [word_129D], 12
	mov		word [word_129F], 0
	mov		word [word_12A1], 11
	mov		byte [byte_12A4], 3
	jmp		handle_input

loc_3A13:
	mov		word [y_pos], 221
	mov		word [x_pos], 21
	mov		byte [byte_12A3], 4
	mov		word [str_ptr], p2_name
	mov		word [word_129D], 12
	mov		word [word_129F], 0
	mov		word [word_12A1], 11
	mov		byte [byte_12A4], 3
	jmp		handle_input

loc_3A44:
	mov		word [y_pos], 117
	mov		word [x_pos], 177
	mov		byte [byte_12A3], 3
	mov		word [str_ptr], game_code
	call	sub_3A66
	cmp		byte [game_code], ' '
	je		loc_3A44
	ret





sub_3A66:								; 3A66
	mov		word [word_129D], 0Ch

loc_3A6C:
	mov		word [word_129F], 0
	mov		word [word_12A1], 8
	mov		byte [byte_12A4], 2
	call	handle_input
	cmp		al, 0CBh
	jz		loc_3A88
	cmp		al, 0CDh
	jnz		ret_3AAB

loc_3A88:
	cmp		word [word_1299], 0
	jz		loc_3A6C
	mov		word [word_129F], 0Ah
	mov		word [word_12A1], 0Bh
	mov		byte [byte_12A4], 5
	call	handle_input
	cmp		al, 0CBh
	jz		loc_3A6C
	cmp		al, 0CDh
	jz		loc_3A6C

ret_3AAB:
	ret


;
;
;
sub_3AAC:								; 3AAC
	add		sp, 2
	call	fade_out
	mov		ax, [res_ptr_I20]			; I20
	call	res_unpack_with_pal
	mov		si, [word_63BA]
	mov		di, 0
	mov		ax, 320
	mov		bx, 200
	call	draw_sprite
	call	sub_3B30
	call	fade_in

loc_3ACE:
	call	sub_3B30
	call	sub_D6F9
	mov		ax, main_menu_loop
	call	handle_esc_key
	call	sub_575C
	cmp		byte [byte_1F58], 0
	jz		loc_3AFB
	push	ax
	mov		ax, [word_3E32]
	mov		dl, 40
	div		dl
	mov		ah, 0
	mov		dx, ax
	pop		ax
	xchg	dx, [snd_setting]
	cmp		dx, [snd_setting]
	jnz		loc_3ACE

loc_3AFB:
	test	al, 8
	jz		loc_3B0C
	cmp		word [snd_setting], 0
	jz		loc_3ACE
	dec		word [snd_setting]
	jmp		loc_3ACE

loc_3B0C:
	test	al, 4
	jz		loc_3B1D
	cmp		word [snd_setting], 4
	jae		loc_3ACE
	inc		word [snd_setting]
	jmp		loc_3ACE

loc_3B1D:
	test	al, 30h
	jz		loc_3ACE
	call	sub_209C
	mov		ax, [snd_setting]
	mov		[word_16F6], ax
	call	sub_20ED
	jmp		main_menu_loop


;
;
;
sub_3B30:								; 3B30
	call	sub_389E
	mov		ax, 39
	mul		word [snd_setting]
	mov		bx, ax
	mov		ax, 112
	add		bx, 8
	mov		cx, 95
	mov		dx, 30
	call	draw_menu_frame
	call	sub_37CA
	ret


;
;
;
sub_3B4F:
	add		sp, 2
	mov		word [word_1096], 1
	mov		word [word_1098], 3

loc_3B5E:
	call	fade_out
	mov		ax, word [res_ptr_I19]
	call	res_unpack_with_pal
	mov		si, [word_63BA]
	mov		di, 0
	mov		ax, 320
	mov		bx, 200
	call	draw_sprite
	mov		ax, [res_ptr_I1A]
	call	res_unpack_simple
	call	sub_3C87
	call	fade_in

loc_3B83:
	call	sub_3C87
	call	sub_D6F9
	mov		ax, main_menu_loop
	call	handle_esc_key
	call	sub_575C
	cmp		byte [byte_1F58], 0
	jz		loc_3BDF
	push	ax
	push	bx
	mov		ax, [word_3E30]
	mov		dl, 214
	div		dl
	mov		ah, 0
	mov		cx, ax
	mov		ax, [word_3E32]
	sub		ax, 22
	mov		dx, 0
	jb		loc_3BBF
	mov		dl, 39
	div		dl
	mov		ah, 0
	mov		dx, ax
	cmp		al, 3
	jb		loc_3BBF
	mov		dl, 3

loc_3BBF:
	pop		bx
	pop		ax
	cmp		dx, 3
	jz		loc_3BCB
	cmp		cx, 1
	jz		loc_3B83

loc_3BCB:
	xchg	cx, [word_1096]
	xchg	dx, [word_1098]
	cmp		cx, [word_1096]
	jnz		loc_3B83
	cmp		dx, [word_1098]
	jnz		loc_3B83

loc_3BDF:
	test	al, 30h
	jz		loc_3BE6
	jmp		loc_3C63

loc_3BE6:
	test	al, 1
	jz		loc_3C07
	cmp		word [word_1096], 0
	jz		loc_3B83
	cmp		word [word_1098], 3
	jz		loc_3C00
	mov		word [word_1096], 0
	jmp		loc_3B83

loc_3C00:
	dec		word [word_1096]
	jmp		loc_3B83

loc_3C07:
	test	al, 2
	jz		loc_3C2C
	cmp		word [word_1096], 2
	jb		loc_3C15
	jmp		loc_3B83

loc_3C15:
	cmp		word [word_1098], 3
	jz		loc_3C25
	mov		word [word_1096], 2
	jmp		loc_3B83

loc_3C25:
	inc		word [word_1096]
	jmp		loc_3B83

loc_3C2C:
	test	al, 8
	jz		loc_3C4B
	cmp		word [word_1096], 1
	jnz		loc_3C3A
	jmp		loc_3B83

loc_3C3A:
	cmp		word [word_1098], 0
	jnz		loc_3C44
	jmp		loc_3B83

loc_3C44:
	dec		word [word_1098]
	jmp		loc_3B83

loc_3C4B:
	test	al, 4
	jz		loc_3C60
	cmp		word [word_1098], 3
	jb		loc_3C59
	jmp		loc_3B83

loc_3C59:
	inc		word [word_1098]
	jmp		loc_3B83

loc_3C60:
	jmp		loc_3B83

loc_3C63:
	mov		ax, 3
	mul		word [word_1098]
	add		ax, [word_1096]
	mov		bx, ax
	shl		bx, 2
	mov		si, [bx + 109Ch]
	mov		bx, [bx + 109Ah]
	and		si, si
	jnz		loc_3C82
	jmp		loc_3B83

loc_3C82:
	call	si
	jmp		loc_3B83


;
;
;
sub_3C87:								; 3C87
	mov		ax, 8
	mov		bx, 19h
	mov		cx, 0
	cmp		word [word_16FF], 0
	jz		loc_3C98
	inc		cx

loc_3C98:
	call	draw_middle_menu_item
	mov		ax, 8
	mov		bx, 40h
	mov		cx, 2
	cmp		word [word_16FF], 2
	jz		loc_3CAC
	inc		cx

loc_3CAC:
	call	draw_middle_menu_item
	mov		ax, 8
	mov		bx, 67h
	mov		cx, 4
	cmp		word [word_16FF], 1
	jz		loc_3CC0
	inc		cx

loc_3CC0:
	call	draw_middle_menu_item
	mov		ax, 8
	mov		bx, 8Eh
	mov		cx, 0Ch
	cmp		word [word_16FF], 0
	jz		loc_3CDC
	inc		cx
	cmp		word [word_16FF], 2
	jz		loc_3CDC
	inc		cx

loc_3CDC:
	call	draw_middle_menu_item
	mov		ax, 0D8h
	mov		bx, 19h
	mov		cx, 6
	cmp		word [word_1716], 0
	jz		loc_3CF0
	inc		cx

loc_3CF0:
	call	draw_middle_menu_item
	mov		ax, 0D8h
	mov		bx, 40h
	mov		cx, 8
	cmp		word [word_1716], 2
	jz		loc_3D04
	inc		cx

loc_3D04:
	call	draw_middle_menu_item
	mov		ax, 0D8h
	mov		bx, 67h
	mov		cx, 0Ah
	cmp		word [word_1716], 1
	jz		loc_3D18
	inc		cx

loc_3D18:
	call	draw_middle_menu_item
	mov		ax, 0D8h
	mov		bx, 8Eh
	mov		cx, 0Fh
	cmp		word [word_1716], 0
	jz		loc_3D34
	inc		cx
	cmp		word [word_1716], 2
	jz		loc_3D34
	inc		cx

loc_3D34:
	call	draw_middle_menu_item
	call	sub_389E
	mov		ax, [word_1098]
	mov		dx, 27h
	mul		dx
	mov		bx, ax
	mov		ax, [word_1096]
	mov		dx, 104
	mul		dx
	add		ax, 8
	add		bx, 27
	mov		cx, 95
	mov		dx, 30
	call	draw_menu_frame
	call	sub_37CA
	ret


; Draws 96x34 sprite.
;
; input:
; (ax, bx) - x, y
; cx - unpacked texture index
; word_63BA - unpacked data
draw_middle_menu_item:					; 3D5F
	mov		di, ax
	mov		ax, 336
	mul		bx
	add		di, ax
	mov		ax, 204
	mul		cx
	mov		si, ax
	add		si, [word_63BA]
	mov		ax, 96
	mov		bx, 34
	jmp		draw_sprite


;
;
;
sub_3D7C:								; 3D7C
	cmp		bl, 2
	jnz		loc_3D87
	cmp		[word_1716], bx
	jz		ret_3D8B

loc_3D87:
	mov		[word_16FF], bx

ret_3D8B:
	ret


;
;
;
sub_3D8C:								; 3D8C
	cmp		bl, 2
	jnz		loc_3D97
	cmp		[word_16FF], bx
	jz		ret_3D9B

loc_3D97:
	mov		[word_1716], bx

ret_3D9B:
	ret


;
;
;
sub_3D9C:
	mov		bx, 1701h
	cmp		word [word_16FF], 1
	jae		loc_3DA9
	jmp		loc_3E63

loc_3DA9:
	mov		bx, 1707h
	jnz		loc_3DB1
	jmp		loc_3F21

loc_3DB1:
	jmp		loc_3DCA

loc_3DB3:
	mov		bx, 1718h
	cmp		word [word_1716], 1
	jae		loc_3DC0
	jmp		loc_3E63

loc_3DC0:
	mov		bx, 171Eh
	jnz		loc_3DC8
	jmp		loc_3F21

loc_3DC8:
	jmp		loc_3DCA

loc_3DCA:
	add		sp, 2						; Controls -> Mouse -> Mouse options
	call	fade_out
	mov		ax, [res_ptr_I1F]
	call	res_unpack_with_pal
	mov		si, [word_63BA]
	mov		di, 0
	mov		ax, 320
	mov		bx, 200
	call	draw_sprite
	call	sub_3E43
	call	fade_in

loc_3DEC:
	call	sub_3E43
	call	sub_D6F9
	mov		ax, main_menu_loop
	call	handle_esc_key
	call	sub_575C
	cmp		byte [byte_1F58], 0
	jz		loc_3E1A
	mov		cx, [word_3E30]
	cmp		cx, 140h
	cmc
	sbb		cx, cx
	and		cx, 1
	xchg	cx, [word_16F2]
	cmp		cx, [word_16F2]
	jnz		loc_3DEC

loc_3E1A:
	test	al, 1
	jz		loc_3E2B
	cmp		word [word_16F2], 0
	jz		loc_3DEC
	dec		word [word_16F2]
	jmp		loc_3DEC

loc_3E2B:
	test	al, 2
	jz		loc_3E3C
	cmp		word [word_16F2], 1
	jae		loc_3DEC
	inc		word [word_16F2]
	jmp		loc_3DEC

loc_3E3C:
	test	al, 30h
	jz		loc_3DEC
	jmp		loc_3B5E


;
; Mouse options menu
;
sub_3E43:
	call	sub_389E
	mov		ax, 56
	mov		bx, 65
	cmp		word [word_16F2], 0
	jz		loc_3E56
	add		ax, 104

loc_3E56:
	mov		cx, 95
	mov		dx, 70
	call	draw_menu_frame
	call	sub_37CA
	ret


loc_3E63:
	add		sp, 2
	push	bx
	call	fade_out
	mov		ax, [res_ptr_I1B]
	call	res_unpack_with_pal
	mov		si, [word_63BA]
	mov		di, 0
	mov		ax, 320
	mov		bx, 200
	call	draw_sprite
	call	update_screen
	call	fade_in
	pop		si
	push	si
	mov		ax, 7F7Fh
	mov		[si], ax
	mov		[si + 2], ax
	mov		[si + 4], ax
	call	sub_DA94
	pop		si
	mov		di, 10CAh

loc_3E9A:
	call	sub_D6F9
	cmp		byte [byte_3D86], 0
	jnz		loc_3E9A
	push	si
	push	di
	call	sub_3EF4
	pop		bp
	pop		si

loc_3EAB:
	call	sub_D6F9
	mov		ax, [byte_3D86]
	cmp		al, 0
	jz		loc_3EAB
	mov		bl, ah
	mov		bh, 0
	xchg	al, [bx + 172Ch]
	cmp		al, 0
	jnz		loc_3ECD
	mov		[si], bl
	inc		si
	cmp		di, 116Ah
	jb		loc_3E9A
	jmp		loc_3B5E

loc_3ECD:
	push	si
	push	bp
	mov		di, 116Ah
	call	sub_3EF4

loc_3ED5:
	call	sub_D6F9
	cmp		byte [byte_3D86], 0
	jnz		loc_3ED5

loc_3EDF:
	call	sub_D6F9
	cmp		byte [byte_3D86], 0
	jz		loc_3EDF
	cmp		byte [byte_3D87], 39h		; '9'
	jnz		loc_3ED5
	pop		di
	pop		si
	jmp		loc_3E9A


;
;
;
sub_3EF4:
	push	di
	mov		si, [word_63BA]
	mov		di, 0
	mov		ax, 320
	mov		bx, 200
	call	draw_sprite
	pop		di
	call	sub_3F0F
	push	di
	call	update_screen
	pop		di
	ret


;
;
;
sub_3F0F:
	mov		bl, [di]
	inc		di
	cmp		bl, 0FFh
	jz		ret_3F20
	mov		bh, 0
	mov		ch, 3
	call	print_string
	jmp		sub_3F0F

ret_3F20:
	ret


loc_3F21:
	add		sp, 2
	push	bx
	call	fade_out
	mov		ax, [res_ptr_I1B]
	call	res_unpack_with_pal
	mov		si, [word_63BA]
	mov		di, 0
	mov		ax, 320
	mov		bx, 200
	call	draw_sprite
	call	update_screen
	call	fade_in
	pop		si
	push	word [word_16FA]
	mov		word [word_16FA], 0FFFFh
	mov		di, 11A6h
	call	sub_3FAF
	mov		[si + 6], ax
	mov		[si + 10], bx
	call	sub_3FAF
	mov		[si + 8], ax
	mov		[si + 12], bx
	call	sub_3FAF
	mov		cx, [si + 6]
	mov		dx, [si + 10]
	sub		cx, ax
	sar		cx, 1
	add		cx, ax
	mov		[si + 6], cx
	sub		dx, bx
	sar		dx, 1
	add		dx, bx
	mov		[si + 10], dx
	mov		cx, [si + 8]
	mov		dx, [si + 12]
	mov		bp, cx
	cmp		bp, dx
	ja		loc_3F8D
	mov		bp, dx

loc_3F8D:
	sub		cx, ax
	sar		cx, 1
	add		cx, ax
	mov		[si + 8], cx
	sub		dx, bx
	sar		dx, 1
	add		dx, bx
	mov		[si + 12], dx
	mov		byte [si], 0FFh
	pop		ax
	cmp		ax, bp
	ja		loc_3FA9
	mov		ax, bp

loc_3FA9:
	mov		[word_16FA], ax
	jmp		loc_3B5E


;
;
;
sub_3FAF:								; 3FAF
	push	si
	call	sub_3EF4
	pop		si
	mov		bx, 1707h
	cmp		si, bx
	jnz		loc_3FBE
	mov		bx, 171Eh

loc_3FBE:
	call	sub_D6F9
	call	sub_3FF6
	cmp		byte [byte_1708], 0
	jnz		loc_3FBE
	cmp		byte [byte_171F], 0
	jnz		loc_3FBE

loc_3FD2:
	call	sub_D6F9
	call	sub_3FF6
	cmp		byte [si + 1], 0
	jnz		loc_3FEF
	cmp		byte [bx + 1], 0
	jz		loc_3FD2
	mov		ax, [bx + 2]
	mov		bx, [bx + 4]
	not		word [word_16FC]
	ret


loc_3FEF:
	mov		ax, [si + 2]
	mov		bx, [si + 4]
	ret


sub_3FF6:								; 3FF6
	test	byte [byte_3D89], 1
	jz		ret_4018
	mov		byte [byte_3D89], 80h
	add		sp, 4
	pop		word [word_16FA]
	cmp		si, 1707h
	jnz		loc_4015
	mov		word [word_16FF], 0

loc_4015:
	jmp		loc_3B5E

ret_4018:
	ret


;
;
;
define_menu:							; 4019
	add		sp, 2
	call	fade_out
	mov		ax, [res_ptr_I16]
	call	res_unpack_with_pal
	mov		si, [word_63BA]

loc_4029:
	mov		di, 0
	mov		ax, 320
	mov		bx, 200
	call	draw_sprite
	mov		word [word_122F], 0
	call	draw_keys_and_frame
	call	sub_37CA
	call	fade_in

loc_4044:
	call	draw_keys_and_frame

loc_4047:
	call	sub_37CA
	call	sub_D6F9
	mov		ax, main_menu_loop
	call	handle_esc_key
	call	sub_575C
	cmp		byte [byte_1F58], 0
	jz		loc_4072
	cmp		word [word_3E32], 2Eh		; '.'
	cmc
	sbb		cx, cx
	and		cx, 1
	xchg	cx, [word_122F]
	cmp		cx, [word_122F]
	jnz		loc_4044

loc_4072:
	test	al, 8
	jz		loc_4085
	cmp		word [word_122F], 1
	jnz		loc_4044
	mov		word [word_122F], 0
	jmp		loc_4044

loc_4085:
	test	al, 4
	jz		loc_4098
	cmp		word [word_122F], 0
	jnz		loc_4044
	mov		word [word_122F], 1
	jmp		loc_4044

loc_4098:
	test	al, 30h
	jz		loc_4047
	cmp		word [word_122F], 0
	jnz		loc_40A6
	jmp		main_menu_loop

loc_40A6:
	mov		word [y_pos], 117
	mov		word [x_pos], 56
	mov		byte [byte_12A3], 4
	mov		word [str_ptr], game_keys

loc_40BD:
	int		3							; Trap to Debugger
	call	sub_3A66
	cmp		al, 13
	jnz		loc_40C8
	jmp		loc_4044

loc_40C8:
	cmp		al, 0C8h ; '+'
	jnz		loc_40DF
	cmp		word [x_pos], 56
	jbe		loc_40BD
	sub		word [x_pos], 15
	sub		word [str_ptr], 0Ch
	jmp		loc_40BD

loc_40DF:
	cmp		al, 0D0h ; '-'
	jnz		loc_40F7
	cmp		word [x_pos], 176
	jae		loc_40BD
	add		word [x_pos], 15
	add		word [str_ptr], 0Ch
	jmp		loc_40BD

loc_40F7:
	jmp		loc_4044


;
; Draws 9 string keys and a red frame for Define menu.
;
draw_keys_and_frame:					; 40FA
	mov		si, game_keys
	mov		bx, 56
	mov		cx, 9

loc_4103:
	push	cx
	mov		ax, 117
	mov		ch, 4
	mov		dx, 12
	call	print_string_narrow
	pop		cx
	add		bx, 15
	loop	loc_4103
	call	sub_389E
	mov		ax, 112
	mov		bx, 7
	mov		cx, 95						; frame width
	mov		dx, 30
	cmp		word [word_122F], 0
	jz		loc_4131
	mov		bx, 46
	mov		dx, 147

loc_4131:
	call	draw_menu_frame
	ret


;
; RECS menu
;
sub_4135:								; 4135
	add		sp, 2
	call	fade_out
	mov		ax, [res_ptr_I17]
	call	res_unpack_with_pal
	add		word [word_63BA], 0FA0h
	mov		ax, [res_ptr_I18]
	call	res_unpack_simple
	sub		word [word_63BA], 0FA0h
	mov		si, game_code
	mov		di, arr_1F3E
	call	sub_D03E
	mov		word [word_1231], 1
	mov		word [word_1233], 0
	call	sub_438D
	call	sub_37CA
	call	fade_in

loc_4171:								; redraw
	mov		si, arr_1F3E
	mov		di, game_code
	call	sub_D001
	call	sub_438D

loc_417D:
	call	sub_37CA
	call	sub_D6F9
	mov		ax, main_menu_loop
	call	handle_esc_key
	call	sub_575C
	cmp		byte [byte_1F58], 0
	jz		loc_41C1
	push	ax
	push	bx
	mov		ax, [word_3E30]
	mov		dl, 214
	div		dl
	mov		ah, 0
	mov		cx, ax
	xchg	cx, [word_1231]
	mov		ax, [word_3E32]
	mov		dl, 40
	div		dl
	mov		ah, 0
	mov		dx, ax
	xchg	dx, [word_1233]
	pop		bx
	pop		ax
	cmp		cx, [word_1231]
	jnz		loc_4171
	cmp		dx, [word_1233]
	jnz		loc_4171

loc_41C1:
	test	al, 1
	jz		loc_41D2
	cmp		word [word_1231], 0
	jz		loc_4171
	dec		word [word_1231]
	jmp		loc_4171

loc_41D2:
	test	al, 2
	jz		loc_41E3
	cmp		word [word_1231], 2
	jae		loc_4171
	inc		word [word_1231]
	jmp		loc_4171

loc_41E3:
	test	al, 8
	jz		loc_41F5
	cmp		word [word_1233], 0
	jz		loc_4171
	dec		word [word_1233]
	jmp		loc_4171

loc_41F5:
	test	al, 4
	jz		loc_420A
	cmp		word [word_1233], 4
	jb		loc_4203
	jmp		loc_4171

loc_4203:
	inc		word [word_1233]
	jmp		loc_4171

loc_420A:
	mov		cl, [byte_3DD6]
	mov		ch, [byte_3DD2]
	and		cx, 101h
	or		cl, ch
	jz		loc_422A
	cmp		word [word_1233], 0
	jz		loc_422A
	cmp		word [word_1233], 4
	jz		loc_422A
	mov		al, 10h

loc_422A:
	test	al, 30h
	jnz		loc_4231
	jmp		loc_417D

loc_4231:
	mov		ax, 3
	mul		word [word_1233]
	add		ax, [word_1231]
	mov		bx, ax
	shl		bx, 2
	mov		si, [bx + 1237h]
	mov		bx, [bx + 1235h]
	and		si, si
	jnz		loc_4250
	jmp		loc_4171

loc_4250:
	call	si							; sub_4333
	jmp		loc_4171

loc_4255:
	mov		[word_1271], bx
	mov		word [word_1273], 0FFFFh

loc_425F:
	mov		bx, [word_1271]
	call	sub_445D
	call	sub_37CA

loc_4269:
	call	sub_D6F9
	mov		ax, main_menu_loop
	call	handle_esc_key
	call	sub_575C
	mov		cl, [byte_3DD6]
	mov		ch, [byte_3DD2]
	and		cx, 101h
	shl		ch, 1
	or		cl, ch
	jz		loc_428C
	mov		bl, cl
	or		bl, 10h

loc_428C:
	cmp		byte [byte_1F58], 0
	jz		loc_429A
	mov		bx, [word_3E2E]
	or		bl, 10h

loc_429A:
	test	bl, 30h
	jz		ret_4310
	mov		ax, bx
	xchg	ax, [word_1273]
	cmp		ax, bx
	jz		loc_42B1
	mov		word [word_3E18], 0
	jmp		loc_42C1

loc_42B1:
	cmp		word [word_3E18], 80h
	jb		loc_4269
	test	word [word_3E18], 0Fh
	jnz		loc_4269

loc_42C1:
	mov		si, [word_1271]
	mov		dx, 26
	cmp		si, 8
	jnz		loc_42D0
	mov		dx, 99

loc_42D0:
	shl		si, 1
	mov		ax, [si + 1F40h]
	test	bl, 1
	jz		loc_42E6
	cmp		ax, 0
	jnz		loc_42E3
	jmp		loc_425F

loc_42E3:
	dec		ax
	jmp		loc_4309

loc_42E6:
	test	bl, 2
	jz		loc_42F5
	cmp		ax, dx
	jb		loc_42F2
	jmp		loc_425F

loc_42F2:
	inc		ax
	jmp		loc_4309

loc_42F5:
	test	bl, 8
	jz		loc_42FE
	mov		ax, dx
	jmp		loc_4309

loc_42FE:
	test	bl, 4
	jnz		loc_4306
	jmp		loc_425F

loc_4306:
	mov		ax, 0

loc_4309:
	mov		[si + 1F40h], ax
	jmp		loc_425F

ret_4310:
	ret


sub_4311:
	mov		si, [word_1271]
	mov		dx, 1Ah
	cmp		si, 8
	jnz		loc_4320
	mov		dx, 63h

loc_4320:
	mov		ax, 8000h
	mov		bx, 280h
	div		bx
	mul		word [word_3E30]
	shl		si, 1
	mov		[si + 1F40h], dx
	ret


;
; When EXIT option is entered on the RECS menu
;
sub_4333:
	add		sp, 2
	jmp		main_menu_loop

loc_4339:
	mov     ax, [arr_1F3E]
	cmp     al, 13
	jb      loc_4342
	dec     al

loc_4342:
	xor     al, 1
	cmp     al, 13
	jb      loc_434A
	inc     al

loc_434A:
	mov		[arr_1F3E], ax
	ret


;
;
;
sub_434E:
	mov		ax, [arr_1F3E]
	cmp		al, 13
	jb		loc_4357
	dec		al

loc_4357:
	add		al, 2
	cmp		al, 1Ah
	jb		loc_435F
	sub		al, 1Ah

loc_435F:
	cmp		al, 13
	jb		loc_4365
	inc		al

loc_4365:
	mov		[arr_1F3E], ax
	ret


;
;
;
sub_4369:
	mov		word [y_pos], 221
	mov		word [x_pos], 21
	mov		byte [byte_12A3], 3
	mov		word [str_ptr], game_code
	call	sub_3A66
	mov		si, game_code
	mov		di, arr_1F3E
	call	sub_D03E
	ret


;
; Draws RECS menu
;
sub_438D:
	mov		si, [word_63BA]
	mov		di, 0
	mov		ax, 320
	mov		bx, 200
	call	draw_sprite
	mov		ax, [arr_1F3E]
	cmp		al, 13
	jb		loc_43A6
	dec		al

loc_43A6:
	shr		ax, 1
	push	ax
	jb		loc_43C5
	mov		ax, 16
	mov		bx, 13
	mov		cx, 13						; A-B route (left piece)
	call	draw_small_menu_item
	mov		ax, 40
	mov		bx, 13
	mov		cx, 14						; A-B route (right piece)
	call	draw_small_menu_item
	jmp		loc_43D1

loc_43C5:
	mov		ax, 72
	mov		bx, 13
	mov		cx, 15						; circular track
	call	draw_small_menu_item

loc_43D1:
	mov		ax, 221
	mov		bx, 21
	mov		ch, 3
	mov		dx, 12
	mov		si, game_code
	call	print_empty_string
	call	print_string_narrow
	pop		cx
	mov		ax, 24
	mul		cx
	add		ax, 4
	mov		bx, 169
	call	draw_small_menu_item		; draw selected track (in SCENARIO bar)
	mov		ax, [word_1233]
	cmp		ax, 4
	jz		loc_441E
	mov		dx, 39
	mul		dx
	mov		bx, ax
	mov		ax, [word_1231]
	mov		dx, 104
	mul		dx
	add		ax, 8
	add		bx, 7
	mov		cx, 95
	mov		dx, 30
	cmp		word [word_1233], 4
	jmp		loc_442A

loc_441E:								; when SCENARIO is selected
	mov		ax, 8
	mov		bx, 163
	mov		cx, 303
	mov		dx, 30

loc_442A:
	call	draw_menu_frame
	mov		bx, 0

loc_4430:
	push	bx
	call	sub_445D
	pop		bx
	inc		bx
	cmp		bx, 8
	jbe		loc_4430
	ret


; Draws 24x26 sprite.
;
; input:
; (ax, bx) - x, y
; cx - unpacked texture index
; word_63BA - unpacked data
draw_small_menu_item:					; 443C
	mov		di, ax
	mov		ax, 336
	mul		bx
	add		di, ax
	mov		ax, 39
	mul		cx
	mov		si, ax
	add		si, [word_63BA]
	add		si, 0FA0h
	mov		ax, 24
	mov		bx, 26
	jmp		draw_sprite


;
;
;
sub_445D:
	cmp		bl, 8
	jnz		loc_4465
	jmp		loc_452B

loc_4465:
	shl		bx, 1
	mov		cx, [bx + 1F40h]
	shl		bx, 1
	mov		ax, [bx + 1275h]
	mov		bx, [bx + 1277h]
	push	ax
	push	bx
	push	cx
	mov		di, ax
	mov		ax, 336
	mul		bx
	add		di, ax
	add		di, 1360					; = 1360 = 336 * 4
	mov		es, [word_63BC]
	mov		bp, 25h
	cmp		cx, 13
	jb		loc_4494
	jz		loc_449A
	dec		cx

loc_4494:
	mov		bp, cx
	add		bp, cx
	add		bp, cx

loc_449A:
	mov		dx, 74
	sub		dx, bp
	jae		loc_44A4
	mov		dx, 0

loc_44A4:
	cmp		bp, 0
	jnz		loc_44AA
	inc		dx

loc_44AA:
	call	sub_4515
	add		di, 336
	mov		si, 20

loc_44B4:
	push	di
	mov		cx, bp
	jcxz	loc_44C0
	mov		al, 26
	rep stosb
	mov		al, 0
	stosb

loc_44C0:
	mov		cx, dx
	jcxz	loc_44C8
	mov		al, 30
	rep stosb

loc_44C8:
	pop		di
	add		di, 336
	dec		si
	jnz		loc_44B4
	call	sub_4515
	pop		ax
	call	sub_D097
	mov		dl, 10
	div		dl
	mov		cx, ax
	pop		bx
	pop		ax
	add		ax, 26
	add		bx, 5
	push	cx
	mov		ch, 4
	cmp		cl, 0
	jz		loc_4501
	cmp		cl, 10
	jb		loc_44FE
	sub		ax, 7
	mov		cl, 1
	call	bmp_draw
	add		ax, 7
	dec		cx

loc_44FE:
	call	bmp_draw

loc_4501:
	add		ax, 7
	pop		cx
	mov		cl, ch
	mov		ch, 4
	call	bmp_draw
	add		ax, 7
	mov		cl, 39						; '%' character
	call	bmp_draw
	ret


;
;
;
sub_4515:
	push	di
	mov		cx, bp
	jcxz	loc_451E
	mov		al, 28
	rep stosb

loc_451E:
	mov		al, 0
	stosb
	mov		cx, dx
	jcxz	loc_4529
	mov		al, 13
	rep stosb

loc_4529:
	pop		di
	ret


;
;
;
loc_452B:
	mov		ax, [arr_1F3E + 18]
	mov		bl, 10
	div		bl
	mov		cx, ax
	mov		ax, 144
	mov		bx, 132
	push	cx
	mov		ch, 5
	call	bmp_draw
	add		ax, 16
	pop		cx
	mov		cl, ch
	mov		ch, 5
	call	bmp_draw
	ret


;
;
;
handle_input:							; 454C
	call	sub_D421
	mov		cx, word_129F
	test	byte [byte_12A4], 4
	jnz		loc_4572
	mov		di, [str_ptr]
	mov		cx, [word_12A1]
	inc		cx
	add		di, cx

loc_4565:
	dec		di
	cmp		byte [di], ' '
	jnz		loc_4572
	dec		cx
	cmp		cx, [word_129F]
	ja		loc_4565

loc_4572:
	mov		[word_1299], cx

loc_4576:
	call	draw_user_input				; Draws user's secret code and cursor.
	call	sub_D6F9
	call	sub_D421
	jz		loc_4576
	cmp		al, ' '
	jz		loc_45E6
	cmp		al, 0CBh					; '-'
	jnz		loc_458C
	jmp		exit_462E

loc_458C:
	cmp		al, 0CDh					; '-'
	jnz		loc_4593
	jmp		exit_462E

loc_4593:
	cmp		al, 0C8h					; '+'
	jnz		loc_459A
	jmp		exit_462E

loc_459A:
	cmp		al, 0D0h					; '-'
	jnz		loc_45A1
	jmp		exit_462E

loc_45A1:
	cmp		al, 13
	jnz		loc_45A8
	jmp		exit_462E

loc_45A8:
	cmp		al, 8
	jnz		loc_45CD
	test	byte [byte_12A4], 4
	jnz		loc_4576
	mov		cx, [word_1299]
	cmp		cx, [word_129F]
	jbe		loc_4576
	dec		cx
	mov		[word_1299], cx
	mov		di, [str_ptr]
	add		di, cx
	mov		byte [di], ' '
	jmp		loc_4576

loc_45CD:
	cmp		al, '0'
	jb		loc_4576
	cmp		al, '9'
	ja		loc_45DE
	test	byte [byte_12A4], 1
	jz		loc_4576
	jmp		loc_45ED

loc_45DE:
	cmp		al, 'A'
	jb		loc_4576
	cmp		al, 'Z'
	ja		loc_462B

loc_45E6:
	test	byte [byte_12A4], 2
	jz		loc_4576

loc_45ED:
	mov		cx, [word_1299]
	mov		di, [str_ptr]
	add		di, cx
	test	byte [byte_12A4], 4
	jnz		loc_4610
	cmp		cx, [word_12A1]
	jbe		loc_4607
	jmp		loc_4576

loc_4607:
	mov		[di], al
	inc		word [word_1299]
	jmp		loc_4576

loc_4610:
	mov		[di], al
	inc		cx
	mov		[word_1299], cx
	cmp		cx, [word_12A1]
	ja		loc_4620
	jmp		loc_4576

loc_4620:
	mov		cx, [word_129F]
	mov		[word_1299], cx
	jmp		loc_4576

loc_462B:
	jmp		loc_4576

exit_462E:
	push	ax
	call	sub_465E
	call	print_string_narrow
	pop		ax
	ret


;
; Draws user's secret code and cursor.
;
draw_user_input:						; 4637
	call	sub_465E
	call	print_string_narrow
	add		bx, 9
	mov		ax, [word_1299]
	cmp		ax, [word_129D]
	jb		loc_464D
	mov		ax, [word_129D]
	dec		ax

loc_464D:
	mov		ah, 7
	mul		ah
	add		ax, [y_pos]
	mov		cl, 2Eh						; '.'   ; cursor
	call	draw_char_small
	call	update_screen
	ret


;
;
;
sub_465E:								; 465E
	mov		ax, [y_pos]
	mov		bx, [x_pos]
	mov		ch, [byte_12A3]
	mov		dx, [word_129D]
	mov		si, [str_ptr]
	call	print_empty_string
	add		bx, 3
	call	print_empty_string
	sub		bx, 3
	ret

loc_467E:
	ret


;
;
;
pick_a_car:								; 467F
	call	fade_out
	mov		ax, [cs:word_5166]			; ax = 1F45
	mov		[word_63BA], ax
	mov		si, car_sel_res_ids
	mov		di, car_sel_res_ptr
	mov		ah, 'I'
	call	load_resource_series
	mov		word [word_3EDA], 0

loc_469A:
	call	fade_out
	mov		bx, [word_3EDA]
	shl		bx, 2
	mov		ax, [car_sel_res_ptr + bx + 2]	; unpack background image
	call	res_unpack_with_pal
	mov		si, [word_63BA]
	mov		di, 0
	mov		ax, 320
	mov		bx, 200
	call	draw_sprite
	mov		bx, [word_3EDA]
	shl		bx, 2
	mov		ax, [car_sel_res_ptr + bx]		; unpack animated car
	call	res_unpack_simple
	call	sub_37CA
	mov		word [word_3E18], 0
	call	fade_in2
	call	sub_4756

loc_46D8:
	call	sub_4764
	call	sub_D6F9
	mov		ax, old_logo
	call	handle_esc_key
	call	sub_575C

loc_46E7:
	cmp		byte [byte_1F58], 0
	jz		loc_471C
	cmp		word [word_3E32], 36
	jae		loc_4704
	cmp		word [word_3E30], 80
	jb		loc_4732					; if left button is pressed
	cmp		word [word_3E30], 560
	ja		loc_4720					; if right button is pressed

loc_4704:
	mov		ax, [word_3E30]
	sub		ax, 80
	cmp		ax, 480
	jae		loc_46D8
	mov		ax, [word_3E32]
	sub		ax, 26
	cmp		ax, 60
	jae		loc_46D8
	jmp		loc_4741

loc_471C:
	test	al, 2
	jz		loc_472E

; right button is pressed
loc_4720:
	mov		ax, [word_3EDA]
	inc		ax
	cmp		ax, 2
	jbe		loc_4748
	mov		ax, 0						; goto first car - Esprit S4
	jmp		loc_4748

loc_472E:
	test	al, 1
	jz		loc_473D

; left button is pressed
loc_4732:
	mov		ax, [word_3EDA]
	dec		ax
	jge		loc_4748
	mov		ax, 2						; goto last car - M200
	jmp		loc_4748

loc_473D:
	test	al, 30h
	jz		loc_46D8

loc_4741:
	call	fade_out2
	call	sub_4756
	ret

loc_4748:
	push	ax
	call	fade_out2
	call	sub_4756
	pop		word [word_3EDA]
	jmp		loc_469A


;
;
;
sub_4756:								; 4756
	call	sub_D6F9
	call	sub_4764
	cmp		word [word_3D70], 0
	jnz		sub_4756
	ret


; input:
; word_3E18 -
sub_4764:								; 4764
	mov		ax, [word_3E18]				; 6, 10, 13, 17, 19, 23, 26, 30 ...
	mov		dx, 0
	mov		bx, 24
	div		bx
	and		ax, 1111b
	mov		dx, 132
	mul		dx

	add		ax, [word_63BA]
	mov		si, ax
	mov		di, 32683					; x = 91, y = 97
	mov		ax, 88
	mov		bx, 24
	call	draw_sprite

	call	sub_37CA
	ret


; Unpacks a resource. Use res_unpack_with_pal when resource has palette.
;
; input:
; ax - packed data
;
; output:
; word_63BA - unpacked data
res_unpack_simple:						; 478D
	push    ds
	mov     es, [word_63BA]
	mov     di, 0
	mov     ds, ax
	mov     si, 0
	mov     cx, 0FFFFh
	call    res_unpack
	pop     ds
	ret


; Unpacks a resource with palette.
;
; input:
; ax:0 - packed data
;
; output:
; word_63BA - unpacked data
; cx -
res_unpack_with_pal:					; 47A2
	push	ds
	mov		es, [word_63BA]
	mov		di, 0
	mov		ds, ax
	mov		si, 0
	mov		cx, 0FFFFh
	call	res_unpack

	mov		ax, es
	sub		ax, 48
	mov     ds, ax
	mov		si, di
	mov		es, [cs:word_5162]
	mov		di, palette
	mov		cx, 768						; 768 = 256 * 3
	rep movsb
	pop		ds
	ret


;
;
;
audio_tuner:							; 47CD
	cmp		word [snd_setting], 4		; 4 - sound off
	jnz		has_sound
	ret

has_sound:								; 47D5
	call	fade_out
	mov		ax, [cs:word_5166]
	add		ax, 2000h
	mov		[word_63BA], ax
	mov		si, tuner_fnt_ids
	mov		word [word_2E78], 0
	call	chr_load_and_prepare_few
	mov		si, tuner_res_ids
	mov		di, tuner_res_ptr
	mov		ah, 'I'
	call	load_resource_series
	mov		ax, [tuner_res_ptr]
	call	res_unpack_with_pal
	mov		si, [word_63BA]
	mov		di, 0
	mov		ax, 320
	mov		bx, 200
	call	draw_sprite
	mov		word [word_3E18], 0FC00h
	call	sub_48BF
	call	fade_in
	jmp		loc_48A2

loc_481E:
	call	sub_48BF
	call	sub_D6F9
	mov		ax, old_logo
	call	handle_esc_key
	call	sub_575C
	cmp		byte [byte_1F58], 0
	jz		loc_486E
	test	word [word_3E2E], 2
	jnz		loc_489B
	mov		ax, [word_3E30]
	sub		ax, 138
	cmp		ax, 96
	jae		loc_481E
	shr		ax, 5
	inc		ax
	mov		dx, [word_3E32]
	sub		dx, 101
	cmp		dx, 48
	ja		loc_481E
	cmp		dx, 14
	jb		loc_489F
	add		ax, 3
	cmp		dx, 28
	jb		loc_489F
	cmp		ax, 5
	jnz		loc_481E
	mov		ax, 0
	jmp		loc_489F

loc_486E:
	test	al, 1
	jz		loc_4880
	dec		word [word_16F8]
	jns		loc_48A2
	mov		word [word_16F8], 6
	jmp		loc_48A2

loc_4880:
	test	al, 2
	jz		loc_4897
	inc		word [word_16F8]
	cmp		word [word_16F8], 6
	jbe		loc_48A2
	mov		word [word_16F8], 0
	jmp		loc_48A2

loc_4897:
	test	al, 48
	je		loc_481E

loc_489B:
	call	fade_out
	ret

loc_489F:
	mov		word [word_16F8], ax

loc_48A2:
	and		word [word_3E18], 7Fh
	or		word [word_3E18], 0FC00h
	mov		ax, [word_16F8]
	call	play_music
	call	sub_20ED
	mov		word [word_3E18], 0
	jmp		loc_481E


;
;
;
sub_48BF:								; 48BF
	call	sub_492E					; Draws 8 bars.
	mov		cx, [word_16F8]
	jcxz	loc_48DD
	xchg	cl, ch
	cmp		word [word_3E18], 0F510h
	jb		loc_48DD
	test	word [word_3E18], 40h
	jnz		loc_48DD
	mov		cx, 0A0Ah

loc_48DD:
	mov		ax, 80						; x = 80
	call	sub_4917
	mov		ax, [word_3E18]
	cmp		ax, 0F510h
	jb		loc_48ED
	sub		ax, ax

loc_48ED:
	mov		dx, 0
	mov		bx, 280
	div		bx
	mov		dx, 0
	mov		bx, 60
	div		bx
	push	dx
	mov		bx, 104
	call	sub_490F
	pop		ax
	mov		bx, 128
	call	sub_490F
	call	sub_37CA
	ret


;
;
;
sub_490F:
	mov		dl, 10
	div		dl
	mov		cx, ax
	mov		ax, bx

sub_4917:
	add		ax, 44
	mov		bx, 112
	push	cx
	mov		ch, 6
	call	bmp_draw
	add		ax, 8
	pop		cx
	mov		cl, ch
	mov		ch, 6
	jmp		bmp_draw


;
; Draws 8 bars.
;
sub_492E:
	mov		si, 0
	mov		di, 336 * 174 + 168
	mov		es, [word_63BC]

for_each_col:
	push	di
	mov		dh, 0
	mov		dl, [si]					; [si] values are set here: fcn.0000202f, fcn.00002056
	shr		dl, 5
	push	dx
	neg		dl
	add		dl, 7
	jz		loc_4956
	mov		al, 9						; background bar color

loc_494A:
	mov		cx, 5						; 5 pixels wide
	rep stosb
	add		di, 667						; = 1 * 336 + 331
										; = 2 * 336 + 0 (1 * 336 + 331 + 5 from rep stosb)
	dec		dx
	jnz		loc_494A

loc_4956:
	pop		dx
	and		dx, dx
	jz		loc_4969
	mov		al, 1

loc_495D:
	mov		cx, 5
	rep stosb
	add		di, 667
	dec		dx
	jnz		loc_495D

loc_4969:
	pop		di
	push	di
	mov		al, [si + 8]
	shr		al, 5
	neg		al
	cmp		al, 0
	jz		loc_4989
	add		al, 7
	mov		ah, 0
	mov		dx, 672
	mul		dx
	add		di, ax
	mov		cx, 5
	mov		al, 1
	rep stosb

loc_4989:
	pop		di
	add		di, 8
	inc		si
	cmp		si, 8
	jb		for_each_col
	ret


;
;
;
sub_4995:								; 4995
	call	sub_4AB2					; Draw "Next Race" screen.
	mov		ax, [track_num]
	inc		ax
	mov		ah, 'I'
	call	res_load
	push	ds
	push	ds
	pop		es
	mov		di, 336 * 89 + 134
	sub		ax, 48
	mov		ds, ax
	mov		si, 0
	mov		cx, 96
	rep movsb
	pop		ds
	mov		si, [word_63BA]
	mov		di, 336 * 50 + 80
	mov		ax, 160
	mov		bx, 100
	call	draw_sprite
	call	sub_C95F
	mov		di, next_race_txt
	mov		bx, 20
	mov		ch, 1
	call	print_string
	push	ds
	pop		es
	mov		si, [word_1F52]
	mov		di, course_val_txt
	mov		cx, 12
	rep movsb
	mov		di, course_txt
	mov		bx, 156
	mov		ch, 1
	call	print_string
	mov		di, user_course_txt
	cmp		word [course_type], 3
	je		loc_4A36
	mov		di, level_txt
	mov		ax, [course_type]
	add		al, 31h ; '1'
	cmp		al, 35h ; '5'
	jnz		loc_4A04
	mov		al, 55h ; 'U'

loc_4A04:
	stosb
	mov		di, race_start_txt
	mov		ax, [word_1F28]
	inc		ax
	call	sub_4A8F
	mov		di, race_end_txt
	mov		ax, [word_23F6]
	cmp		word [course_type], 4
	jnz		loc_4A30
	mov		si, game_keys
	mov		ax, 0

loc_4A22:
	cmp		byte [si], ' '
	je		loc_4A30
	inc		ax

loc_4A28:
	add		si, 12
	cmp		ax, 9
	jnz		loc_4A22

loc_4A30:
	call	sub_4A8F
	mov		di, level_race_txt

loc_4A36:
	mov		bx, 168
	mov		ch, 1
	call	print_string
	mov		di, stages_txt
	mov		ax, [num_of_tracks]
	call	sub_4A8F
	mov		di, laps_txt
	mov		ax, [num_of_tracks]
	call	sub_4A8F
	mov		ax, 3091
	mul		word [word_23F2]
	mov		bp, 225
	div		bp
	mov		bp, 1000
	mov		dx, 0
	div		bp
	mov		si, distance_txt
	lea		di, [si]
	cmp		word [is_circular_track], 0
	jz		loc_4A76
	mov		si, laps_txt
	lea		di, [si + 11]				; '01.234 KM',0

loc_4A76:
	push	dx
	call	sub_4A8F
	pop		ax
	inc		di
	call	sub_4A9E
	mov		di, si
	mov		bx, 180
	mov		ch, 1
	call	print_string
	call	update_screen
	jmp		fade_in


sub_4A8F:
	mov		dl, 10
	div		dl
	add		ax, 3030h
	cmp		al, '0'
	jne		loc_4A9C
	mov		al, ' '

loc_4A9C:
	stosw
	ret


;
;
;
sub_4A9E:								; 4A9E
	mov		dl, 100
	div		dl
	add		al, '0'
	stosb
	mov		al, ah
	mov		ah, 0
	mov		dl, 10
	div		dl
	add		ax, 3030h
	stosw
	ret


;
;
;
sub_4AB2:
	mov		al, 0
	mov		ah, 'I'
	call	res_load
	push	ds
	push	ds
	pop		es
	mov		di, palette
	sub		ax, 48
	mov		ds, ax
	mov		si, 0
	mov		cx, 768
	rep movsb
	pop		ds
	mov		word [palette], 0
	mov		byte [palette + 2], 0
	mov		si, [word_63BA]
	cmp		word [word_3EE4], 0
	jz		loc_4AE7
	add		si, 1000

loc_4AE7:
	mov		di, 0
	mov		ax, 320
	mov		bx, 50
	call	draw_sprite
	mov		si, [word_63BA]
	add		si, 2000
	mov		di, 336 * 50
	mov		ax, 320
	mov		bx, 150
	call	draw_sprite
	ret


;
;
;
sub_4B08:
	call	fade_out
	mov		ax, [cs:word_5166]
	mov		[word_63BA], ax
	call	sub_C939
	call	sub_4AB2
	call	sub_C95F
	call	race_results
	call	update_screen
	call	fade_in
	mov		word [word_3E18], 0
	mov		ax, 0AF0h
	call	sub_C002
	cmp		word [word_3EE4], 0
	jz		ret_4B47
	mov		ax, [word_1F28]
	inc		ax
	cmp		ax, [word_23F6]
	jae		ret_4B47
	mov		di, current_pos_txt
	call	sub_4DE9

ret_4B47:
	ret


;
;
;
race_results:							; 4B48
	cmp		word [word_3EE4], 0
	jnz		loc_4B52					; if Race::Competition
	jmp		loc_4C4F					; if Race::TimeLimit

loc_4B52:
	mov		di, race_result_txt
	mov		bx, 20
	mov		ch, 1
	call	print_string
	mov		si, race_columns_txt
	mov		ax, 34
	mov		bx, 53
	mov		dx, 35
	mov		ch, 1
	call	print_string_narrow
	call	sub_4C9A
	mov		bp, 0
	mov		bx, 67

loc_4B77:
	call	sub_4BB6
	add		bx, 10
	inc		bp
	cmp		bp, 10
	jb		loc_4B77
	add		bx, 3
	mov		bp, [word_401C]
	mov		di, 0
	cmp		word [num_of_players], 0
	jz		loc_4B98
	mov		di, [word_4116]

loc_4B98:
	cmp		bp, di
	jb		loc_4B9E
	xchg	bp, di

loc_4B9E:
	push	di
	cmp		bp, 10
	jbe		loc_4BAB
	dec		bp
	call	sub_4BB6
	add		bx, 13

loc_4BAB:
	pop		bp
	cmp		bp, 10
	jbe		ret_4BB5
	dec		bp
	call	sub_4BB6

ret_4BB5:
	ret


;
;
;
sub_4BB6:
	push	bp
	shl		bp, 2
	lea		si, [bp + 160Ch]
	mov		ax, 34
	mov		dx, 4
	mov		ch, 1
	call	print_string_narrow
	pop		si
	push	si
	shl		si, 1
	push	ax
	mov		al, 20
	mul		byte [si + 1543h]
	mov		si, cast_txt
	add		si, ax
	pop		ax
	add		ax, 14
	mov		dx, 18
	mov		ch, 1
	call	print_string_narrow
	pop		si
	push	si
	shl		si, 1
	mov		cx, [si + 3CECh]
	call	sub_4C05
	pop		si
	push	si
	shl		si, 1
	add		si, 151Bh
	add		ax, 14
	mov		dx, 2
	mov		ch, 1
	call	print_string_narrow
	pop		bp
	ret


;
;
;
sub_4C05:
	mov		si, retired_txt
	cmp		cx, 1
	jz		loc_4C35
	push	ax
	mov		di, race_time_txt
	mov		ax, cx
	mov		dx, 0
	mov		cx, 600
	div		cx
	push	dx
	call	sub_4C3E
	pop		ax
	mov		dx, 0
	mov		cx, 10
	div		cx
	push	dx
	call	sub_4C3E
	pop		ax
	add		al, '0'
	mov		[di], al
	pop		ax
	mov		si, race_time_txt

loc_4C35:
	mov		dx, 7
	mov		ch, 1
	call	print_string_narrow
	ret


;
;
;
sub_4C3E:
	mov		cl, 10
	div		cl
	add		ax, 3030h
	mov		[di], ax
	add		di, 3
	mov		byte [di - 1], 2Eh ; '.'
	ret


loc_4C4F:
	mov		di, scores_so_far_txt


;
;
;
sub_4C52:
	mov		bx, 20
	mov		ch, 1
	call	print_string
	mov		ax, 90
	mov		bx, 90
	mov		ch, 1
	mov		si, p1_name
	mov		dx, 12
	call	print_string_narrow
	mov		cx, [word_3F6A]
	mov		dx, [word_3F68]
	call	sub_4F81
	cmp		word [num_of_players], 0
	jz		ret_4C99
	mov		ax, 90
	add		bx, 12
	mov		ch, 1
	mov		si, p2_name
	mov		dx, 12
	call	print_string_narrow
	mov		cx, [word_4064]
	mov		dx, [word_4062]
	call	sub_4F81

ret_4C99:
	ret


;
;
;
sub_4C9A:
	push	ds
	pop		es
	mov		si, p1_name
	mov		di, arr_14F3
	mov		cx, 12
	rep movsb
	mov		si, p2_name
	mov		di, arr_14DF
	mov		cx, 12
	rep movsb
	mov		ax, [word_4018]
	or		ax, [word_401A]
	jnz		loc_4CC7
	mov		word [word_3D12], 1
	mov		word [word_401C], 20

loc_4CC7:
	cmp		word [num_of_players], 0
	jz		loc_4CF2
	mov		ax, [word_4112]
	or		ax, [word_4114]
	jnz		loc_4CF2
	mov		ax, 1
	xchg	ax, [word_3D12]
	mov		word [word_4116], 20
	cmp		word [word_401C], 20
	jnz		loc_4CF2
	mov		[word_3D10], ax
	dec		word [word_401C]

loc_4CF2:
	mov		dx, 99
	mov		cx, [word_401C]
	dec		cx
	cmp		word [num_of_players], 0
	jz		loc_4D06
	mov		dx, [word_4116]
	dec		dx

loc_4D06:
	mov		bx, 0
	mov		ax, 0
	mov		di, arr_1543

loc_4D0F:
	cmp		bx, cx
	jnz		loc_4D19
	mov		word [di], 8013h
	jmp		loc_4D26

loc_4D19:
	cmp		bx, dx
	jne		loc_4D23
	mov		word [di], 8012h
	jmp		loc_4D26

loc_4D23:
	mov		[di], ax
	inc		ax

loc_4D26:
	add		di, 2
	inc		bx
	cmp		bx, 20
	jb		loc_4D0F
	mov		cx, 10

loc_4D32:
	call	sub_ABF0
	mov		dx, 20
	mul		dx
	push	dx
	call	sub_ABF0
	mov		dx, 20
	mul		dx
	pop		ax
	shl		ax, 1
	mov		si, arr_1543
	add		si, ax
	mov		ax, [si]
	cmp		al, 18
	jae		loc_4D32
	shl		dx, 1
	mov		di, arr_1543
	add		di, dx
	mov		dx, [di]
	cmp		dl, 18
	jae		loc_4D32
	mov		[si], dx
	mov		[di], ax
	loop	loc_4D32
	cmp		word [word_1F28], 0
	jnz		loc_4D79
	push	ds
	pop		es
	mov		di, arr_15BA
	mov		ax, 0
	mov		cx, 20
	rep stosw

loc_4D79:
	mov		si, arr_1507
	mov		di, arr_1543
	mov		cx, 10

loc_4D82:
	lodsb
	mov		ah, 0
	mov		bx, [di]
	add		di, 2
	shl		bx, 1
	add		[bx + arr_15BA], ax
	loop	loc_4D82
	mov		ax, [arr_15BA + 19 * 2]
	mov		[word_3F6A], ax
	mov		word [word_3F68], 0
	mov		ax, [arr_15BA + 18 * 2]
	mov		[word_4064], ax
	mov		word [word_4062], 0
	mov		di, arr_15BA + 1
	mov		cx, 20

loc_4DB0:
	or		byte [di], 80h
	add		di, 2
	loop	loc_4DB0
	mov		di, 0

loc_4DBB:
	mov		bx, 0
	mov		ax, 0
	mov		cx, 20

loc_4DC4:
	cmp		ax, [bx + arr_15BA]
	jae		loc_4DD0
	mov		ax, [bx + arr_15BA]
	mov		si, bx

loc_4DD0:
	add		bx, 2
	loop	loc_4DC4
	and		byte [si + arr_15BA + 1], 7Fh
	mov		ax, si
	shr		ax, 1
	mov		[di + arr_15A6], al
	inc		di
	cmp		di, 20
	jb		loc_4DBB
	ret


;
;
;
sub_4DE9:
	push	di
	call	fade_out
	mov		ax, [cs:word_5166]
	mov		[word_63BA], ax
	call	sub_C939
	call	sub_4AB2
	call	sub_C95F
	pop		di
	call	sub_4E14
	call	update_screen
	call	fade_in
	mov		word [word_3E18], 0
	mov		ax, 15E0h
	call	sub_C002
	ret


;
;
;
sub_4E14:								; 4E14
	mov		bx, 20
	mov		ch, 1
	call	print_string
	mov		si, pos_name_pts_txt
	mov		ax, 62
	mov		bx, 53
	mov		dx, 28
	mov		ch, 1
	call	print_string_narrow
	mov		bp, 0
	mov		bx, 67

loc_4E33:
	call	sub_4E66
	add		bx, 10
	inc		bp
	cmp		bp, 10
	jb		loc_4E33
	add		bx, 3

loc_4E42:
	mov		si, bp
	cmp		byte [si + arr_15A6], 13h
	jz		loc_4E59
	cmp		word [num_of_players], 0
	jz		loc_4E5F
	cmp		byte [si + arr_15A6], 12h
	jnz		loc_4E5F

loc_4E59:
	call	sub_4E66
	add		bx, 13

loc_4E5F:
	inc		bp
	cmp		bp, 20
	jb		loc_4E42
	ret


;
;
;
sub_4E66:								; 4E66
	push    bp
	shl     bp, 2
	lea     si, [bp + 160Ch]
	mov     ax, 62
	mov     dx, 4
	mov     ch, 1
	call	print_string_narrow
	pop		si
	push	si
	push	ax
	mov		al, 20
	mul		byte [si + 15A6h]
	mov		si, 1377h
	add		si, ax
	pop		ax
	add		ax, 14
	mov		dx, 18
	mov		ch, 1
	call	print_string_narrow
	pop		si
	push	si
	sub		ax, 29
	mov		si, [si + 15A6h]
	and		si, 7Fh
	shl		si, 1
	mov		cx, [si + 15BAh]
	mov		dx, 0
	call	sub_4F81
	pop		bp
	ret


;
;
;
sub_4EAD:								; 4EAD
	cmp		word [word_3EE4], 0
	jnz		loc_4EE0
	call	fade_out
	mov		ax, [cs:word_5166]
	mov		[word_63BA], ax
	call	sub_C939
	call	sub_4AB2
	call	sub_C95F
	mov		di, final_scores_txt
	call	sub_4C52
	call	update_screen
	call	fade_in
	mov		word [word_3E18], 0
	mov		ax, 0AF0h
	call	sub_C002
	ret

loc_4EE0:
	mov		di, final_pos_txt
	jmp		sub_4DE9


;
;
;
sub_4EE6:								; 4EE6
	push	ax
	call	fade_out
	mov		ax, [cs:word_5166]
	mov		[word_63BA], ax
	call	sub_C939
	call	sub_4AB2
	call	sub_C95F
	pop		ax
	call	sub_4F0B
	call	update_screen
	call	fade_in
	mov		word [word_3E18], 0
	ret


;
;
;
sub_4F0B:								; 4F0B
	push	ax
	shl		ax, 1
	mov		si, 165Ch
	add		si, ax
	mov		di, [si]
	mov		bx, 20
	mov		ch, 1
	call	print_string
	pop		ax
	mov		dx, 160
	mul		dx
	mov		si, 1B48h
	add		si, ax
	mov		bp, 0
	mov		bx, 60

loc_4F2E:
	push	si
	push	bp
	shl		bp, 2
	lea		si, [bp + 160Ch]
	mov		ax, 45
	mov		dx, 4
	mov		ch, 1
	call	print_string_narrow
	pop		bp
	pop		si
	push	si
	push	bp
	shl		bp, 4
	add		si, bp
	push	word [si + 14]
	push	word [si + 12]
	add		ax, 14
	mov		dx, 12
	mov		ch, 1
	call	print_string_narrow
	pop		cx
	pop		dx
	add		ax, 7
	push	dx
	and		dx, 3FFFh
	call	sub_4F81
	pop		cx
	add		ax, 7
	shr		cx, 14
	mov		ch, 7
	call	bmp_draw
	pop		bp
	pop		si
	add		bx, 13
	inc		bp
	cmp		bp, 10
	jb		loc_4F2E
	ret


;
;
;
sub_4F81:								; 4F81
	push	ax
	push	bx
	mov		di, question_marks_txt
	mov		ax, cx
	mov		cx, 10000
	div		cx
	push	dx
	call	sub_4FB3
	pop		ax
	call	sub_4FB3
	mov		si, question_marks_txt
	mov		cx, 7

loc_4F9B:
	cmp		byte [si], '0'
	jnz		loc_4FA6
	mov		byte [si], ' '
	inc		si
	loop	loc_4F9B

loc_4FA6:
	pop		bx
	pop		ax
	mov		ch, 1
	mov		dx, 8
	mov		si, question_marks_txt
	jmp		print_string_narrow


;
;
;
sub_4FB3:								; 4FB3
	mov		dx, 0
	mov		cx, 100
	div		cx
	push	dx
	call	sub_4FC0
	pop		ax


sub_4FC0:
	mov		cl, 10
	div		cl
	add		ax, 3030h
	mov		[di], ax
	add		di, 2
	ret


;
;
;
sub_4FCD:								; 4FCD
	mov		dx, 160
	mul		dx
	mov		di, 1B48h
	add		di, ax
	mov		bp, p1_name
	mov		bx, 3F68h
	push	di
	call	sub_4FEF
	pop		di
	cmp		word [num_of_players], 0
	jz		ret_500E
	mov		bp, p2_name
	mov		bx, 4062h

sub_4FEF:
	mov		si, di
	mov		cx, 10

loc_4FF4:
	mov		ax, [si + 12]
	mov		dx, [si + 14]
	and		dx, 3FFFh
	sub		ax, [bx + 2]
	sbb		dx, [bx]
	jb		loc_500F
	or		ax, dx
	jz		loc_500F
	add		si, 16
	loop	loc_4FF4

ret_500E:
	ret

loc_500F:
	push	es
	pop		ds
	add		si, 15
	add		di, 159
	mov		cx, di
	sub		cx, si
	jz		loc_5025
	lea		si, [di - 16]
	std
	rep movsb
	cld

loc_5025:
	sub		di, 15
	mov		si, bp
	mov		cx, 12
	rep movsb
	mov		ax, [bx + 2]
	stosw
	mov		ax, [word_3EDA]
	shl		ax, 14
	add		ax, [bx]
	stosw
	ret
