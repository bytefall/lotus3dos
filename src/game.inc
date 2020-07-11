;
; Start a game menu
;
start_game:								; 522E
	mov		word [playing_demo], 0
	call	sub_D915 
	call	fade_out
	call	sub_537F
	call	pick_a_car

loc_5240:
	call	audio_tuner

loc_5243:
	call	sub_D915
	call	sub_53AA
	call	sub_D3F3
	mov		word [word_1F95], 0
	mov		ax, loc_5481
	call	sub_D740
	jmp		loc_6FDA					; demo gameplay

loc_525B:
	mov		ah, 'D'
	call	res_load
	push	ds
	mov		es, [word_63BE]
	mov		di, 0
	mov		ds, [word_63BA]
	mov		si, 0
	mov		cx, 2048
	rep movsw							; for i in 0..4096 { word_63BE[i] = word_63BA[i] }
	pop		ds
	mov		word [word_3E22], 0
	mov		word [playing_demo], 0FFFFh
	jmp		loc_5243

loc_5283:
	call	sub_D915
	mov		word [playing_demo], 0
	mov		word [word_1F26], loc_5222
	mov		ax, loc_5371
	call	sub_D740
	mov		ax, [demo_counter]
	call	sub_4EE6
	mov		ax, 0AF0h
	call	sleep
	jmp		loc_51E9

loc_52A7:
	call	sub_D915
	cmp		word [word_16F8], 0
	jnz		loc_52B4
	call	sub_209C

loc_52B4:
	call	sub_4B08
	inc		word [word_1F28]
	mov		ax, [word_1F28]
	cmp		ax, [word_23F6]
	jae		loc_5303
	cmp		word [word_3EE4], 0
	jz		loc_52E8
	cmp		word [word_401C], 10
	ja		loc_52D5
	jmp		loc_5240

loc_52D5:
	cmp		word [num_of_players], 0
	jz		loc_5303
	cmp		word [word_4116], 10
	ja		loc_52E6
	jmp		loc_5240

loc_52E6:
	jmp		loc_5303

loc_52E8:
	cmp		word [word_3F54], 2
	jnz		loc_52F2
	jmp		loc_5240

loc_52F2:
	cmp		word [num_of_players], 0
	jz		loc_5303
	cmp		word [word_404E], 2
	jnz		loc_5303
	jmp		loc_5240

loc_5303:
	mov		ax, [course_type]
	cmp		ax, 2
	jbe		loc_530E
	jmp		loc_5222

loc_530E:
	shl		ax, 1
	mov		bx, [race_type]
	and		bx, 1
	or		ax, bx
	push	ax
	call	sub_4FCD
	call	sub_4EAD
	pop		ax
	call	sub_4EE6
	mov		ax, 20D0h
	call	sub_C002
	jmp		loc_5222

loc_532D:
	mov		word [is_paused], 0
	jmp		loc_51C4


; input:
; cs:ax - place when you will appear
handle_esc_key:							; 5336
	test	byte [byte_3D89], 1
	jz		ret_5346
	mov		byte [byte_3D89], 128
	push	ax
	jmp		sub_D915

ret_5346:
	ret


;
; find out where it's called from
;
sub_5347:								; 5347
	push	ds
	pop		es
	mov		si, word_3EDA
	mov		cx, 426Eh
	sub		cx, si
	mov		es, [word_63BE]
	mov		di, 0
	rep movsb							; move 916 bytes
	ret


; Copy first 916 bytes from unpacked demo to ds:3EDA
copy_demo_header:						; 535B
	push	ds
	mov		di, word_3EDA
	mov		cx, 426Eh
	sub		cx, di						; cx = 0x426E - 0x3EDA = 0x394 = 916
	mov		ds, [word_63BE]
	mov		si, 0
	pop		es
	push	es
	rep movsb							; for i in 0..916 { word_3EDA[i] = word_63BE[i] }
	pop		ds
	ret

loc_5371:
	call	sub_C011
	jb		loc_537B
	call	sub_D7E9
	jmp		loc_5371

loc_537B:
	jmp		word [word_1F26]			; jmp 0x51C4


;
;
;
sub_537F:
	mov		bx, [course_type]
	shl		bx, 1
	mov		ax, [bx + 1F2Ah]
	mov		[word_23F6], ax
	mov		ax, [race_type]
	mov		[word_3EE4], ax
	sub		ax, ax
	mov		[word_3F68], ax
	mov		[word_3F6A], ax
	mov		[word_4062], ax
	mov		[word_4064], ax
	mov		[word_156B], ax
	mov		[word_156D], ax
	mov		[word_1F28], ax
	ret


;
;
;
sub_53AA:								; 53AA
	push	ds
	pop		es
	cmp		word [playing_demo], 0
	jz		is_a_gameplay
	call	copy_demo_header			; Copy first 916 bytes from unpacked demo to ds:3EDA
	mov		di, rnd_3EEE
	mov		si, arr_3F0E
	mov		cx, 16						; fill both rnd_3EEE and rnd_3EFE
	rep movsw							; make a duplicate one by one:
										;
										; 0F6C:3EEE     17 FD 13 B6 63 B7 40 68 33 17 D6 33 BE D8 5F 76
										; 0F6C:3EFE     9C 77 E1 E1 57 92 09 61 A1 38 97 56 36 9C 72 C4
										;
										; 0F6C:3F0E     17 FD 13 B6 63 B7 40 68 33 17 D6 33 BE D8 5F 76
										; 0F6C:3F1E     9C 77 E1 E1 57 92 09 61 A1 38 97 56 36 9C 72 C4
										;
										; for i in (52..52 + 32) { word_3EEE[j++] = word_3EDA[i] }
										;
	mov		si, arr_3F2E				; no change here since si = 0x3F2E already
	jmp		loc_53FA

is_a_gameplay:							; 53C6
	mov		si, game_code
	mov		di, arr_3F2E
	mov		cx, 12
	rep movsb

	mov		si, rnd_3EEE
	mov		di, arr_3F0E
	mov		cx, 16
	rep movsw

	mov		ax, 5
	mul		word [race_type]
	mov		si, ax
	add		si, [course_type]
	mov		al, [si + 1F34h]
	add		ax, [word_1F28]
	mov		ah, 12
	mul		ah
	mov		si, cfg_keys
	add		si, ax

loc_53FA:
	mov		[word_1F52], si
	mov		di, arr_1F3E
	call	sub_D03E
	call	sub_A9D3
	mov		ax, 200
	cmp		word [num_of_players], 0
	jz		loc_5414
	mov		ax, 96

loc_5414:
	mov		[word_633A], ax
	call	sub_BE52
	call	sub_CDF1
	call	sub_CF28
	mov		word [word_1F54], 0
	mov		word [word_1F56], 40h
	cmp		word [playing_demo], 0
	jz		loc_5436
	call	copy_demo_header

loc_5436:
	call	sub_543A
	ret


;
;
;
sub_543A:
	cmp		word [word_16F8], 0
	je		loc_5442
	ret

loc_5442:
	mov		ax, 260h
	mov		bl, 0
	call	sub_50B4
	cmp		word [num_of_players], 0
	jz		loc_5459
	mov		ax, 360h
	mov		bl, 0
	call	sub_50B4

loc_5459:
	cmp		word [word_63A4], 0
	jz		loc_5466
	mov		ax, 170h
	jmp		sub_50AC

loc_5466:
	cmp		word [word_63B0], 0
	jz		loc_5473
	mov		ax, 174h
	jmp		sub_50AC

loc_5473:
	cmp		word [word_63AA], 0
	jz		ret_5480
	mov		ax, 171h
	jmp		sub_50AC

ret_5480:
	ret


;
;
;
loc_5481:
	cmp		word [word_3D70], 0
	jnz		loc_54BC
	cmp		word [playing_demo], 0
	jz		loc_5499
	cmp		byte [byte_3D86], 0
	jz		loc_54AC
	jmp		loc_5222

loc_5499:
	mov		ax, loc_532D
	call	handle_esc_key
	mov		word [is_paused], 0
	test	byte [byte_3DA1], 1
	jne		loc_54C1

loc_54AC:
	call	sub_588E
	call	sub_5520
	cmp		word [word_3CEA], 0
	jnz		loc_54BC
	jmp		loc_52A7

loc_54BC:
	call	sub_D7E9
	jmp		loc_5481

loc_54C1:
	mov		byte [byte_3DA1], 80h
	mov		word [is_paused], 0FFFFh
	mov		ah, 0

loc_54CE:
	mov		al, [byte_1F0A]
	mov		bl, 0
	call	sub_50F8
	mov		ah, 1
	mov		al, [byte_1F0B]
	mov		bl, 0
	call	sub_50F8
	mov		ah, 2
	mov		al, [byte_1F0C]
	mov		bl, 0
	call	sub_50F8
	mov		ah, 3
	mov		al, [byte_1F0D]
	mov		bl, 0
	call	sub_50F8
	mov		ah, 4
	mov		al, [byte_1F0E]
	mov		bl, 0
	call	sub_50F8

loc_54FE:
	test	byte [byte_3D89], 1
	jz		loc_5508
	jmp		loc_532D

loc_5508:
	mov		word [word_1F95], 0FFFFh
	call	sub_D7E9
	test	byte [byte_3DA1], 1
	jz		loc_54FE
	mov		byte [byte_3DA1], 80h
	jmp		loc_5481


;
;
;
sub_5520:								; 5520
	mov		si, word_3F3A
	mov		ch, 1
	call	sub_5670
	cmp		word [num_of_players], 0
	jz		loc_5537
	mov		si, word_4034
	mov		ch, 2
	call	sub_5670

loc_5537:
	cmp		word [word_3CE4], 2
	jz		loc_5571
	cmp		word [word_3EE4], 0
	jnz		loc_5571
	cmp		word [word_3F5C], 0
	jnz		loc_555B
	mov		ax, [word_3F5A]
	dec		ax
	cmp		ax, 8
	jae		loc_555B
	mov		ax, 6Fh
	call	sub_50AC

loc_555B:
	cmp		word [word_4056], 0
	jnz		loc_5571
	mov		ax, [word_4054]
	dec		ax
	cmp		ax, 8
	jae		loc_5571
	mov		ax, 6Fh
	call	sub_50AC

loc_5571:
	mov		ax, [word_3EE0]
	cmp		ax, 9
	jge		loc_5591
	cmp		ax, 0FF6Ah
	je		loc_55DD
	cmp		ax, 0FF9Ch
	je		loc_55DD
	cmp		ax, 0FFCEh
	je		loc_55DD
	cmp		ax, 0
	jl		loc_5591
	test	al, 1
	je		loc_55DD

loc_5591:
	mov		ax, [word_3FE2]
	dec		ax
	and		al, 7
	jz		loc_55DD
	mov		ax, [word_40DC]
	dec		ax
	and		al, 7
	jz		loc_55DD
	cmp		word [word_3FE2], 0
	jnz		loc_55BF
	cmp		word [word_3F54], 0
	jnz		loc_55BF
	cmp		word [word_4018], 5C00h
	jae		loc_55BF
	mov		ax, [word_3EE6]
	dec		ax
	and		al, 1Fh
	jz		loc_55DD

loc_55BF:
	cmp		word [word_40DC], 0
	jnz		loc_55E3
	cmp		word [word_404E], 0
	jnz		loc_55E3
	cmp		word [word_4112], 5C00h
	jae		loc_55E3
	mov		ax, [word_3EE6]
	dec		ax
	and		al, 1Fh
	jnz		loc_55E3

loc_55DD:
	mov		ax, 66h
	call	sub_50AC

loc_55E3:
	cmp		word [word_63A4], 0
	jnz		loc_55F6
	mov		si, word_3F3A
	call	sub_56AF
	mov		si, word_4034
	call	sub_56AF

loc_55F6:
	cmp		word [word_63A4], 0
	jnz		loc_560C
	cmp		word [word_63B0], 0
	jnz		loc_5639
	cmp		word [word_63AA], 0
	jnz		loc_5643
	ret

loc_560C:
	call	sub_AB9A
	cmp		al, 4
	jae		loc_5617
	not		word [word_1F56]

loc_5617:
	mov		ax, [word_1F56]
	add		ax, [word_1F54]
	cmp		ah, 4
	jae		loc_5626
	mov		ax, 400h

loc_5626:
	cmp		ah, 18h
	jb		loc_562E
	mov		ax, 1800h

loc_562E:
	mov		[word_1F54], ax
	mov		bl, ah
	mov		ax, 70h						; 'p'
	jmp		sub_50F8

loc_5639:
	mov		bl, [word_3EEA + 1]
	mov		ax, 74h						; 't'
	jmp		sub_50F8

loc_5643:
	call	sub_AB9A
	cmp		al, 4
	jae		loc_564E
	not		word [word_1F56]

loc_564E:
	mov		ax, [word_1F56]
	add		ax, [word_1F54]
	cmp		ah, 20h						; ' '
	jae		loc_565D
	mov		ax, 2000h

loc_565D:
	cmp		ah, 40h						; '@'
	jb		loc_5665
	mov		ax, 4000h

loc_5665:
	mov		[word_1F54], ax
	mov		bl, ah
	mov		ax, 71h						; 'q'
	jmp		sub_50F8


;
;
;
sub_5670:
	mov		cl, 60h
	cmp		word [si + 14], 0
	jle		loc_56A7
	mov		ax, [si + 44]
	cmp		ax, 500h
	ja		loc_5683
	mov		ax, 500h

loc_5683:
	shr		ax, 4
	mov		bx, ax
	mov		ax, cx
	push	ax
	call	sub_5121
	pop		ax
	mov		bl, 20h						; ' '
	cmp		word [word_16F6], 2
	jz		loc_569A
	mov		bl, 30h						; '0'

loc_569A:
	cmp		word [si + 36], 0
	jz		loc_56A3
	add		bl, 10h

loc_56A3:
	call	sub_50F8
	ret

loc_56A7:
	mov		ax, cx
	mov		bl, 0
	call	sub_50F8
	ret


;
;
;
sub_56AF:
	cmp		word [si + 60], 0
	jz		loc_56B8
	jmp		loc_5755

loc_56B8:
	mov		ax, [word_634E]
	shl		ax, 4
	sub		ax, 80
	mov		bx, [si + 4]
	cmp		bx, ax
	jg		loc_56E2
	neg		ax
	cmp		bx, ax
	jl		loc_56E2
	cmp		word [word_63A6], 0
	jne		loc_56D8
	jmp		near loc_5755

loc_56D8:
	cmp		bx, 0FFC0h
	jl		loc_5755
	cmp		bx, 64
	jg		loc_5755

loc_56E2:
	cmp		word [word_63A8], 0
	jz		loc_5735
	cmp		word [si + 204], 0
	jnz		ret_575B
	cmp		word [si + 192], 0
	jnz		ret_575B
	mov		bx, [si]
	shl		bx, 4
	mov		bx, [bx - 7EA0h]
	xchg	bl, bh
	mov		cx, [si + 2]
	xchg	cl, ch
	shr		cx, 14
	xor		cl, 3
	shl		cl, 2
	shr		bx, cl
	and		bl, 0Fh
	cmp		bl, 2
	jnz		loc_5735
	mov		ax, 100
	call	sub_50AC
	mov		ax, [si + 4]
	mov		[si + 194], ax
	mov		word [si + 192], 1
	mov		word [si + 204], 1
	jmp		ret_575B

loc_5735:
	mov		ax, [si + 2]
	mov		dx, [si]
	cmp		dx, [si + 70]
	jl		loc_5755
	jg		loc_5746
	cmp		ax, [si + 72]
	jb		loc_5755

loc_5746:
	or		ax, 3FFFh
	mov		[si + 70], dx
	mov		[si + 72], ax
	mov		ax, 103
	call	sub_50AC

loc_5755:
	mov		word [si + 204], 0

ret_575B:
	ret


;
;
;
sub_575C:
	call	sub_D92B
	mov		ax, 0
	mov		ah, [byte_3DA4]
	shr		ah, 1
	rcl		al, 1
	mov		ah, [byte_3DD0]
	shr		ah, 1
	rcl		al, 1
	mov		ah, [byte_3DD8]
	shr		ah, 1
	rcl		al, 1
	mov		ah, [byte_3DD5]
	shr		ah, 1
	rcl		al, 1
	mov		ah, [byte_3DD3]
	shr		ah, 1
	rcl		al, 1
	cmp		word [word_16FF], 1
	jnz		loc_5795
	xor		al, [byte_16FE]

loc_5795:
	mov		byte [byte_1F58], 0
	cmp		word [word_16FF], 2
	jnz		loc_57AE
	mov		ah, [byte_3E2D]
	mov		[byte_1F58], ah
	and		ah, 10h
	or		al, ah

loc_57AE:
	mov		[byte_3F70], al
	mov		ah, al
	xchg	al, [byte_3F6C]
	xor		al, ah
	and		al, ah
	mov		[word_3F6E], al
	mov		bx, [byte_3F70]
	mov		ax, [word_3F6E]
	ret


;
;
;
sub_57C6:
	call	sub_D92B
	mov		al, [byte_16FE]
	mov		[byte_3F70], al
	mov		ah, al
	xchg	al, [byte_3F6C]
	xor		al, ah
	and		al, ah
	mov		[word_3F6E], al
	mov		si, word_3F3A
	call	sub_57FC
	mov		al, [byte_1715]
	mov		[byte_406A], al
	mov		ah, al
	xchg	al, [byte_4066]
	xor		al, ah
	and		al, ah
	mov		[byte_4068], al
	mov		si, word_4034
	call	sub_57FC
	ret


;
;
;
sub_57FC:
	mov		al, [si + 54]
	mov		ah, [si + 52]
	mov		word [si + 244], 0
	mov		word [si + 246], 0
	mov		word [si + 248], 0
	mov		bl, -1
	test	al, 1
	jz		loc_581E
	mov		[si + 244], bl

loc_581E:
	test	al, 2
	jz		loc_5826
	mov		[si + 245], bl

loc_5826:
	cmp		word [playing_demo], 0
	jnz		loc_586B
	mov		cl, byte [word_16FF]
	cmp		si, word_3F3A
	jz		loc_583B
	mov		cl, byte [word_1716]

loc_583B:
	cmp		cl, 1
	jb		loc_586B
	jnz		loc_5848
	cmp		byte [si + 56], 0
	jz		loc_586B

loc_5848:
	test	al, 8
	jz		loc_5850
	mov		[si + 246], bl

loc_5850:
	test	al, 4
	jz		loc_5858
	mov		[si + 247], bl

loc_5858:
	test	ah, 16
	jz		loc_5861
	mov		[si + 248], bl

loc_5861:
	test	ah, 32
	jz		ret_586A
	mov		[si + 249], bl

ret_586A:
	ret

loc_586B:
	test	al, 16
	jz		loc_5873
	mov		[si + 246], bl

loc_5873:
	test	al, 32
	jz		loc_587B
	mov		[si + 247], bl

loc_587B:
	test	ah, 8
	jz		loc_5884
	mov		[si + 248], bl

loc_5884:
	test	ah, 4
	jz		ret_588D
	mov		[si + 249], bl

ret_588D:
	ret


;
; update gameplay state
;
sub_588E:
	call	sub_6F55
	inc		word [word_3EE2]
	inc		word [word_3CE8]
	cmp		word [word_4012], 1
	sbb		word [word_4012], 0FFFFh
	cmp		word [word_410C], 1
	sbb		word [word_410C], 0FFFFh
	cmp		word [word_3FE2], 1
	adc		word [word_3FE2], 0FFFFh
	cmp		word [word_40DC], 1
	adc		word [word_40DC], 0FFFFh
	call	sub_57C6
	cmp		word [word_63A4], 0
	jz		loc_58D7
	mov		ax, [word_3F3A]
	call	sub_5A5A
	mov		ax, [word_4034]
	call	sub_5A5A

loc_58D7:
	inc		word [word_3EE6]
	mov		ax, [word_3EEA]
	shr		ax, 8
	inc		ax
	add		[word_3EE8], ax
	call	sub_ABF0
	cmp		ah, 4
	jae		loc_58F2
	not		word [word_3EEC]

loc_58F2:
	mov		ax, [word_3EEA]
	add		ax, [word_3EEC]
	jg		loc_58FE
	mov		ax, 0

loc_58FE:
	cmp		ax, 4000h
	jb		loc_5906
	mov		ax, 4000h

loc_5906:
	mov		[word_3EEA], ax
	mov		si, 412Eh
	mov		cx, 8

loc_590F:
	sub		word [si + 2], 400h
	sbb		word [si], 0
	add		si, 8
	loop	loc_590F
	cmp		word [word_3EE4], 0
	jnz		loc_5967
	cmp		word [is_circular_track], 0
	jnz		loc_5967
	mov		ax, [word_3F3C]
	mov		bx, [word_3F3A]
	cmp		ax, [word_4036]
	mov		bp, [word_4034]
	sbb		bp, bx
	jns		loc_5944
	mov		ax, [word_3F3C]
	mov		bx, [word_3F3A]

loc_5944:
	sub		ax, [word_41E0]
	sbb		bx, [word_41DE]
	xchg	ax, bx
	shl		ax, 7
	add		ax, [word_23FA]
	cmp		ax, 1F40h
	jb		loc_595C
	mov		ax, 1F40h

loc_595C:
	cmp		ax, 7D0h
	ja		loc_5964
	mov		ax, 7D0h

loc_5964:
	mov		[word_23F8], ax

loc_5967:
	cmp		word [word_3CEA], 0
	jns		loc_5981
	mov		si, word_3F3A
	call	sub_5B22
	cmp		word [num_of_players], 0
	jz		loc_5981
	mov		si, word_4034
	call	sub_5B22

loc_5981:
	call	sub_6E52
	call	sub_6E8F
	mov		ax, [word_400C]
	mov		[word_3F3E], ax
	mov		ax, [word_4106]
	mov		[word_4038], ax
	cmp		word [word_3CEA], 0
	js		loc_599D
	jmp		near loc_5A1A

loc_599D:
	cmp		word [word_3CE4], 2
	jz		loc_59C6
	call	sub_5B07
	cmp		word [word_3EE0], 0
	jns		loc_59DC
	call	sub_644D
	mov		si, word_3F3A
	call	sub_6EFC
	cmp		word [num_of_players], 0
	jz		loc_5A1A
	mov		si, word_4034
	call	sub_6EFC
	jmp		loc_5A1A

loc_59C6:
	cmp		word [word_3EE4], 0
	jnz		loc_59D2
	call	sub_63F0
	jnz		loc_59D7

loc_59D2:
	or		word [word_3CE4], 1

loc_59D7:
	call	sub_62C1
	jmp		loc_5A1A

loc_59DC:
	mov		ax, [word_3CDE]
	mov		bp, [word_3CDC]
	inc		ax
	cmp		ax, 5
	jnz		loc_59ED
	mov		ax, 0
	inc		bp

loc_59ED:
	mov		[word_3CDE], ax
	mov		[word_3CDC], bp
	call	sub_62C1
	cmp		word [word_3CE4], 0
	jnz		loc_5A1A
	mov		si, word_3F3A
	call	sub_64CE
	cmp		word [num_of_players], 0
	jz		loc_5A11
	mov		si, word_4034
	call	sub_64CE

loc_5A11:
	call	sub_6BEC
	call	sub_6DA6
	call	sub_644D

loc_5A1A:
	cmp		word [word_3CEA], 0
	jle		loc_5A25
	dec		word [word_3CEA]

loc_5A25:
	jns		ret_5A41
	test	word [word_3CE4], 1
	jz		loc_5A35
	mov		word [word_3CEA], 32h		; '2'

loc_5A35:
	mov		si, word_3F3A
	call	sub_5A42
	mov		si, word_4034
	call	sub_5A42

ret_5A41:
	ret


;
;
;
sub_5A42:
	mov		ax, [si + 4]
	mov		[si + 174], ax
	mov		al, [si + 16]
	and		al, 0FCh
	or		al, [si + 236]
	mov		ah, [si + 61]
	mov		[si + 176], ax
	ret


;
;
;
sub_5A5A:
	cmp		word [is_circular_track], 0
	jz		loc_5A6E
	mov		si, ax
	mov		al, [si + arr_7856]
	mov		ah, 0
	inc		ax
	mov		dx, ax
	jmp		loc_5A77

loc_5A6E:
	inc		ax
	cmp		ax, 8
	jns		loc_5A77
	mov		ax, 8

loc_5A77:
	shl		ax, 4
	mov		si, 8158h
	add		si, ax
	mov		bx, word [word_23F2]
	shl		bx, 4
	mov		cx, 8

loc_5A89:
	cmp		byte [si], 0
	jz		loc_5A9D
	cmp		byte [si], 96
	jae		loc_5A9D
	inc		byte [si]
	cmp		byte [si], 64
	jnz		loc_5A9D
	mov		byte [si], 184

loc_5A9D:
	add		si, 2
	cmp		byte [si], 0
	jle		loc_5AAF
	inc		byte [si]
	cmp		byte [si], 64
	jnz		loc_5AAF
	mov		byte [si], 184

loc_5AAF:
	add		si, 2
	cmp		byte [si], 0
	jle		loc_5AC1
	inc		byte [si]
	cmp		byte [si], 64
	jnz		loc_5AC1
	mov		byte [si], 184

loc_5AC1:
	add		si, 2
	cmp		byte [si], 0
	jle		loc_5AD3
	inc		byte [si]
	cmp		byte [si], 64
	jnz		loc_5AD3
	mov		byte [si], 184

loc_5AD3:
	sub		si, 6
	cmp		word [is_circular_track], 0
	jz		loc_5B01
	cmp		dx, 8
	jns		loc_5AF8
	mov		ax, [si]
	mov		[bx + si], ax
	mov		ax, [si + 2]
	mov		[bx + si + 2], ax
	mov		ax, [si + 4]
	mov		[bx + si + 4], ax
	mov		ax, [si + 6]
	mov		[bx + si + 6], ax

loc_5AF8:
	dec		dx
	jns		loc_5B01
	add		dx, word [word_23F2]
	add		si, bx

loc_5B01:
	sub		si, 16
	loop	loc_5A89
	ret


;
;
;
sub_5B07:
	cmp		word [word_3EE0], 7FFFh
	je		ret_5B21
	inc		word [word_3EE0]
	cmp		word [word_3EE0], 200h
	jne		ret_5B21
	mov		word [word_3EE0], 100h

ret_5B21:
	ret


;
;
;
sub_5B22:
	mov		ax, [si + 4]
	mov		[si + 210], ax
	call	sub_5B47
	mov		ax, [si + 4]
	xchg	ax, [si + 210]
	mov		[si + 4], ax
	call	sub_5FA7
	cmp		word [word_63A6], 0
	jz		loc_5B43
	call	sub_61AD

loc_5B43:
	call	sub_6237
	ret


;
;
;
sub_5B47:
	cmp		word [si + 172], 0
	jz		loc_5B57
	inc		word [si + 172]
	and		word [si + 172], 0Fh

loc_5B57:
	cmp		word [si + 192], 0
	jz		loc_5B75
	inc		word [si + 192]
	cmp		word [si + 192], 20
	jnz		loc_5B75
	mov		word [si + 192], 0
	mov		word [si + 194], 0

loc_5B75:
	cmp		word [si + 36], 0
	jz		loc_5B7E
	call	sub_5F5A

loc_5B7E:
	cmp		word [word_63B4], 0
	jz		loc_5B9F
	cmp		word [si + 4], 0FF40h
	jns		loc_5B9F
	mov		cx, [word_3D38]
	mov		bx, 0DFh
	mov		ax, [word_27F2]
	shr		ax, 8
	mov		[word_6352], ax
	jmp		loc_5F26

loc_5B9F:
	mov		bx, [si]
	cmp		word [is_circular_track], 0
	jz		loc_5BAE
	mov		bl, [bx + arr_7856]
	mov		bh, 0

loc_5BAE:
	shl		bx, 4
	mov		bx, [bx - 7EA0h]
	xchg	bl, bh
	mov		cx, [si + 2]
	shr		cx, 14
	xor		cl, 3
	shl		cl, 2
	shr		bx, cl
	and		bx, 0Fh
	cmp		word [word_63B2], 0
	jz		loc_5BE5					; nop this if you want turbo zone everywhere
	cmp		bl, 2
	jnz		loc_5BE5					; nop this if you want turbo zone everywhere
	mov		ax, 10
	xchg	ax, [si + 188]				; set turbo zone
	and		ax, ax
	jnz		loc_5BE5
	mov		ax, 117						; when car enters turbo zone
	call	sub_50AC

loc_5BE5:
	cmp		word [word_6392], 0
	jz		loc_5BFA
	cmp		bl, 1
	jnz		loc_5BFA
	mov		word [si + 194], 0
	jmp		loc_5E1D

loc_5BFA:
	mov		bx, [si]
	mov		ax, [si + 2]
	add		ax, 2000h
	adc		bx, 0
	test	ax, 2000h
	je		loc_5C13
	mov		word [si + 214], 0
	jmp		loc_5F53

loc_5C13:
	cmp		word [is_circular_track], 0
	jz		loc_5C20
	mov		bl, [bx + arr_7856]
	mov		bh, 0

loc_5C20:
	shl		bx, 4
	shr		ax, 13
	and		al, 6
	add		bx, ax
	lea		di, [bx - 7EAAh]
	mov		dl, [di + 2]
	and		dx, 0FFh
	jnz		loc_5C3A
	jmp		loc_5F53

loc_5C3A:
	cmp		dl, 0FAh
	jnz		loc_5C43
	call	sub_5F5A
	ret

loc_5C43:
	cmp		dl, 0F8h
	jb		loc_5C4B
	jmp		loc_5F53

loc_5C4B:
	mov		bx, dx
	sub		bx, 128
	shl		bx, 2
	mov		ax, [bx + 2676h]
	shr		ax, 8
	mov		[word_6352], ax
	mov		cl, [bx + 2674h]
	mov		ch, 0
	add		cx, 64
	shr		cx, 1
	neg		cx
	mov		[word_6362], cx
	mov		bx, dx
	cmp		bl, 0DBh
	jne		loc_5CC1
	mov		al, [di + 3]
	cbw
	shl		ax, 4
	add		ax, [word_3EE6]
	and		ax, 38h
	jnz		loc_5CB0
	mov		bx, 64
	mov		ax, 115
	call	sub_50B4
	mov		ax, 104
	call	sub_50AC
	mov		bx, 8
	call	sub_AB9A
	jns		loc_5C9F
	neg		bx

loc_5C9F:
	mov		[si + 212], bx
	shl		bx, 2
	mov		[si + 28], bx
	mov		cx, [word_3D3E]
	jmp		loc_5F40

loc_5CB0:
	mov		cx, 32
	cmp		word [si + 4], 0
	js		loc_5CBC
	jmp		loc_5D43

loc_5CBC:
	neg		cx
	jmp		loc_5D43

loc_5CC1:
	cmp		bl, 218
	jne		loc_5CF4
	mov		al, [di + 3]
	cbw
	shl		ax, 4
	mov		cx, ax
	shl		cx, 4
	add		cx, [word_3EE8]
	and		cx, 1FFFh
	sub		cx, 1000h
	and		ax, 3
	add		al, 2
	imul	cx
	sar		dx, 1
	rcr		ax, 1
	sar		dx, 1
	rcr		ax, 1
	mov		cx, ax
	sar		cx, 4
	jmp		loc_5D43

loc_5CF4:
	mov		dx, 0FFF4h
	cmp		bl, 210
	je		loc_5D03
	cmp		bl, 213
	jnz		loc_5D22
	neg		dx

loc_5D03:
	cmp		word [si + 214], 0
	jnz		loc_5D22
	mov		ax, 118
	call	sub_50AC
	call	sub_AB9A
	test	al, 4
	jz		loc_5D19
	neg		dx

loc_5D19:
	add		[si + 28], dx
	mov		word [si + 214], 1

loc_5D22:
	cmp		bl, 160
	jnz		loc_5D2A
	jmp		loc_5E43

loc_5D2A:
	mov		al, [di + 3]
	cbw
	mov		cx, ax
	add		cx, 3
	cmp		bl, 192
	je		loc_5D43
	sub		cx, 6
	cmp		bl, 245
	je		loc_5D43
	add		cx, 3

loc_5D43:
	shl		cx, 4
	sub		cx, [si + 4]
	mov		ax, [word_6362]
	cmp		cx, ax
	jae		loc_5D59
	neg		ax
	cmp		cx, ax
	jb		loc_5D59
	jmp		loc_5F53

loc_5D59:
	mov		[si + 194], cx
	mov		al, bl
	cmp		al, 235
	jnz		loc_5D66
	jmp		loc_5E1D

loc_5D66:
	cmp		al, 151
	jnz		loc_5D6D
	jmp		loc_5E1D

loc_5D6D:
	cmp		word [si + 164], 0
	jz		loc_5D77
	jmp		loc_5F4C

loc_5D77:
	mov		cx, [word_3D38]
	cmp		al, 136
	jnz		loc_5D82
	jmp		loc_5F4C

loc_5D82:
	cmp		al, 137
	jnz		loc_5D89
	jmp		loc_5F4C

loc_5D89:
	cmp		al, 138
	jnz		loc_5D90
	jmp		loc_5F4C

loc_5D90:
	cmp		al, 184
	jz		loc_5E0C
	cmp		al, 218
	jz		loc_5E10
	cmp		al, 64
	jae		loc_5D9F
	jmp		loc_5F4C

loc_5D9F:
	cmp		al, 202
	jnz		loc_5DA6
	jmp		loc_5F4C

loc_5DA6:
	cmp		al, 203
	jnz		loc_5DAD
	jmp		loc_5F4C

loc_5DAD:
	cmp		al, 177
	jnz		loc_5DB4
	jmp		loc_5E8F

loc_5DB4:
	cmp		al, 186
	jnz		loc_5DBB
	jmp		loc_5E8F

loc_5DBB:
	cmp		al, 242
	jnz		loc_5DC2
	jmp		loc_5E91

loc_5DC2:
	cmp		al, 243
	jnz		loc_5DC9
	jmp		loc_5E91

loc_5DC9:
	cmp		al, 149
	jnz		loc_5DD0
	jmp		loc_5EAA

loc_5DD0:
	cmp		al, 163
	jnz		loc_5DD7
	jmp		loc_5EAA

loc_5DD7:
	cmp		al, 206
	jnz		loc_5DDE
	jmp		loc_5EAA

loc_5DDE:
	cmp		al, 130
	jnz		loc_5DE5
	jmp		loc_5F53

loc_5DE5:
	cmp		al, 205
	jnz		loc_5DEC
	jmp		loc_5EED

loc_5DEC:
	cmp		al, 236
	jnz		loc_5DF3
	jmp		loc_5EED

loc_5DF3:
	cmp		al, 176
	jnz		loc_5DFA
	jmp		loc_5EED

loc_5DFA:
	cmp		al, 169
	jnz		loc_5E01
	jmp		loc_5EED

loc_5E01:
	cmp		al, 151
	jz		loc_5E1D
	cmp		al, 235
	jz		loc_5E1D
	jmp		loc_5F26

loc_5E0C:
	mov		byte [di + 2], 1

loc_5E10:
	mov		ax, 105
	call	sub_50AC
	mov		cx, [word_3D3C]
	jmp		loc_5F40

loc_5E1D:
	cmp		word [si + 60], 0
	jle		loc_5E26
	jmp		loc_5F53

loc_5E26:
	mov		cx, [word_3D3A]
	cmp		word [si + 164], 0
	jz		loc_5E34
	jmp		loc_5F40

loc_5E34:
	mov		ax, 100
	call	sub_50AC
	mov		word [si + 192], 1
	jmp		loc_5F40

loc_5E43:
	mov		al, [di + 3]
	cbw
	shl		ax, 4
	sub		ax, [word_3EE6]
	shl		ax, 4
	and		ax, 1FFFh
	sub		ax, 1000h
	sub		ax, [si + 4]
	neg		ax
	cmp		ax, 0FEC5h
	jns		loc_5E64
	jmp		loc_5F53

loc_5E64:
	cmp		ax, 0FFABh
	js		loc_5E88
	cmp		ax, 55h
	js		loc_5E76
	cmp		ax, 0A0h
	js		loc_5E88
	jmp		loc_5F53

loc_5E76:
	add		word [si + 48], 0C350h
	adc		word [si + 46], 0
	mov		ax, 117
	call	sub_50AC
	jmp		loc_5F53

loc_5E88:
	mov		cx, [word_3D40]
	jmp		loc_5F26

loc_5E8F:
	neg		cx

loc_5E91:
	mov		ax, [word_6352]
	call	sub_50AC
	mov		bx, [si + 194]
	add		bx, 112
	shr		bx, 3
	shl		bx, 1
	mov		cx, [bx + 1F59h]
	jmp		loc_5F40

loc_5EAA:
	mov		ax, [si + 60]
	cmp		ax, 2000h
	jb		loc_5EB5
	jmp		loc_5F53

loc_5EB5:
	cmp		word [si + 16], 0FFF1h
	jl		loc_5F26
	cmp		word [si + 16], 0Fh
	jg		loc_5F26
	mov		word [si + 16], 0
	mov		ax, [si + 14]
	cmp		ax, 800h
	js		loc_5F26
	shr		ax, 4
	add		ax, 600h
	mov		[si + 62], ax
	mov		ax, 114
	call	sub_50AC
	add		word [si + 48], 4E20h
	adc		word [si + 46], 0
	mov		word [si + 64], 1
	jmp		loc_5F4C

loc_5EED:
	cmp		word [si + 60], 0
	jnz		loc_5F53
	mov		ax, 107
	call	sub_50AC
	mov		ax, [si + 14]
	shr		ax, 8
	add		ax, 16
	mov		bx, 0FFF8h
	cmp		word [si + 16], 0
	jnz		loc_5F10
	push	ax
	call	sub_ABF0
	pop		ax

loc_5F10:
	js		loc_5F16
	neg		ax
	neg		bx

loc_5F16:
	cmp		word [si + 212], 0
	jnz		loc_5F4C
	mov		[si + 212], bx
	mov		[si + 28], ax
	jmp		loc_5F4C

loc_5F26:
	mov		ax, [word_6352]
	call	sub_50AC
	mov		ax, [si + 14]
	shr		ax, 8
	add		ax, 16
	cmp		word [si + 4], 0
	js		loc_5F3D
	neg		ax

loc_5F3D:
	mov		[si + 28], ax

loc_5F40:
	mov		ax, [si + 14]
	mul		cx
	mov		[si + 206], dx
	mov		[si + 14], dx

loc_5F4C:
	mov		word [si + 164], 1
	ret

loc_5F53:
	mov		word [si + 164], 0
	ret


;
;
;
sub_5F5A:
	mov		ax, [word_6338]
	cmp		[si + 4], ax
	jl		loc_5F69
	neg		ax
	cmp		[si + 4], ax
	jl		ret_5FA6

loc_5F69:
	mov		[si + 170], ax
	mov		word [si + 172], 1
	mov		[si + 4], ax
	mov		word [si + 6], 0
	mov		ax, 104
	call	sub_50AC
	mov		bx, [si + 14]
	mov		ax, bx
	mul		word [word_3D34]
	mov		[si + 206], dx
	mov		[si + 14], dx
	mov		al, bh
	mov		ah, 0
	add		ax, 10
	cmp		word [si + 4], 0
	js		loc_5FA0
	neg		ax

loc_5FA0:
	mov		[si + 28], ax
	add		sp, 2

ret_5FA6:
	ret


;
;
;
sub_5FA7:
	cmp		word [is_circular_track], 0
	jnz		loc_5FB1
	jmp		loc_60E2

loc_5FB1:
	mov		di, 417Eh
	mov		bx, [word_3C76]
	mov		dx, [di]
	mov		[word_6360], dx
	mov		dx, [di + 2]
	mov		cx, [bx + di]
	mov		[word_635C], cx
	mov		cx, [bx + di + 2]
	mov		bx, [si]
	mov		ax, [si + 2]
	sub		ax, 2000h
	sbb		bx, 0
	mov		[word_6368], bx
	mov		[word_6366], ax
	add		ax, 4000h
	adc		bx, 0
	mov		[word_636C], bx
	mov		[word_636A], ax
	mov		bx, [word_23F2]

loc_5FED:
	cmp		[word_6366], dx
	mov		bp, [word_6368]
	sbb		bp, [word_6360]
	js		loc_6005
	sub		[word_6368], bx
	sub		[word_636C], bx
	jmp		loc_5FED

loc_6005:
	cmp		[word_636A], cx
	mov		bp, [word_636C]
	sbb		bp, [word_635C]
	jns		loc_601D
	add		[word_6368], bx
	add		[word_636C], bx
	jmp		loc_6005

loc_601D:
	mov		bp, [word_3C74]
	mov		[word_636E], bp

loc_6025:
	mov		bx, [di]
	mov		[word_6358], bx
	mov		bx, [di + 2]
	add		di, 12
	cmp		bx, [word_6366]
	mov		bp, [word_6358]
	sbb		bp, [word_6368]
	js		ret_6057
	sub		bx, [word_636A]
	mov		bp, [word_6358]
	sbb		bp, [word_636C]
	mov		[word_6358], bp
	js		loc_6058
	dec		word [word_636E]
	jns		loc_6025

ret_6057:
	ret


;
;
;
loc_6058:
	mov		cx, [di - 8]
	sub		cx, [si + 4]
	cmp		cx, 0FFC0h
	js		ret_6057
	cmp		cx, 64
	jns		ret_6057
	add		bx, 2000h
	adc		word [word_6358], 0
	js		loc_607B
	mov		ax, [di - 6]
	cmp		ax, [si + 14]
	jb		loc_60A0

loc_607B:
	and		cx, cx
	jns		loc_608D
	mov		cx, 0FFC0h
	cmp		word [di - 2], 0
	js		loc_6099
	neg		word [di - 2]
	jmp		loc_6099

loc_608D:
	mov		cx, 64
	cmp		word [di - 2], 0
	jns		loc_6099
	neg		word [di - 2]

loc_6099:
	add		cx, [si + 4]
	mov		[di - 8], cx
	ret

loc_60A0:
	sub		bx, 2000h
	sbb		word [word_6358], 0
	add		[si + 2], bx
	mov		bx, [word_6358]
	adc		[si], bx
	mov		ax, 98
	call	sub_50AC
	mov		ax, [si + 14]
	mul		word [word_3D36]
	mov		[si + 206], dx
	mov		[si + 14], dx
	mov		ax, [si + 14]
	shr		ax, 11
	add		ax, 16
	mov		bx, 0FFF8h
	and		cx, cx
	js		loc_60DA
	neg		ax
	neg		bx

loc_60DA:
	mov		[si + 28], ax
	mov		[si + 212], bx
	ret

loc_60E2:
	mov		di, 417Eh
	mov		cx, [word_3C74]
	inc		cx

loc_60EA:
	mov		bp, [di]
	mov		bx, [di + 2]
	add		di, 12
	sub		bx, [si + 2]
	sbb		bp, [si]
	jg		loc_610E
	jz		loc_6108
	cmp		bp, 0FFFFh
	jnz		loc_610E
	cmp		bx, 0E000h
	jb		loc_610E
	jmp		loc_6133

loc_6108:
	cmp		bx, 2000h
	jb		loc_6113

loc_610E:
	loop	loc_60EA
	jmp		loc_61A6

loc_6113:
	mov		cx, [di - 8]
	sub		cx, [si + 4]
	cmp		cx, 0FFC0h
	jns		loc_6121
	jmp		loc_61A6

loc_6121:
	cmp		cx, 64
	js		loc_6129
	jmp		loc_61A6

loc_6129:
	mov		ax, [di - 6]
	cmp		ax, [si + 14]
	jb		loc_6169
	jmp		loc_6143

loc_6133:
	mov		cx, [di - 8]
	sub		cx, [si + 4]
	cmp		cx, 0FFC0h
	js		loc_61A6
	cmp		cx, 64
	jns		loc_61A6

loc_6143:
	and		cx, cx
	jns		loc_6155
	mov		cx, 0FFC0h
	cmp		word [di - 2], 0
	js		loc_6161
	neg		word [di - 2]
	jmp		loc_6161

loc_6155:
	mov		cx, 64
	cmp		word [di - 2], 0
	jns		loc_6161
	neg		word [di - 2]

loc_6161:
	add		cx, [si + 4]
	mov		[di - 8], cx
	jmp		loc_61A6

loc_6169:
	cmp		word [si + 184], 0
	jnz		ret_61AC
	mov		word [si + 184], 1
	mov		ax, 98
	call	sub_50AC
	mov		ax, [si + 14]
	mul		word [word_3D36]
	mov		[si + 206], dx
	mov		[si + 14], dx
	mov		ax, [si + 14]
	shr		ax, 11
	add		ax, 24
	mov		bx, 0FFF8h
	and		cx, cx
	js		loc_619E
	neg		ax
	neg		bx

loc_619E:
	mov		[si + 28], ax
	mov		[si + 212], bx
	ret

loc_61A6:
	mov		word [si + 184], 0

ret_61AC:
	ret


;
;
;
sub_61AD:
	mov		di, 412Eh
	mov		cx, 8

loc_61B3:
	mov		ax, [di]
	mov		bx, [di + 2]
	add		di, 8
	sub		bx, [si + 2]
	sbb		ax, [si]
	and		ax, 3Fh
	jnz		loc_61CB
	cmp		bx, 2000h
	jb		loc_61EC

loc_61CB:
	cmp		ax, 3
	jz		loc_61D4

loc_61D0:
	loop	loc_61B3
	jmp		loc_6230

loc_61D4:
	mov		ax, [di - 4]
	sub		ax, [si + 4]
	cmp		ax, 0FFC0h
	js		loc_61D0
	cmp		ax, 64
	jns		loc_61D0
	mov		ax, 110
	call	sub_50AC
	jmp		loc_61D0

loc_61EC:
	mov		cx, [di - 4]
	sub		cx, [si + 4]
	cmp		cx, 0FFC0h
	js		loc_6230
	cmp		cx, 64
	jns		loc_6230
	cmp		word [si + 184], 0
	jnz		ret_6236
	mov		word [si + 184], 1
	mov		ax, 98
	call	sub_50AC
	mov		ax, [si + 14]
	mul		word [word_3D42]
	mov		[si + 206], dx
	mov		[si + 14], dx
	mov		ax, [si + 14]
	shr		ax, 11
	add		ax, 24
	and		cx, cx
	js		loc_622C
	neg		ax

loc_622C:
	mov		[si + 28], ax
	ret

loc_6230:
	mov		word [si + 184], 0

ret_6236:
	ret


;
;
;
sub_6237:
	cmp		word [num_of_players], 0
	jnz		loc_6241
	jmp		ret_62C0

loc_6241:
	mov		di, word_4034
	cmp		si, di
	jnz		loc_624B
	mov		di, word_3F3A

loc_624B:
	mov		cx, [di + 4]
	sub		cx, [si + 4]
	cmp		cx, 0FFC0h
	js		ret_62C0
	cmp		cx, 64
	jns		ret_62C0
	mov		ax, [di + 2]
	mov		bx, [di]
	sub		ax, [si + 2]
	sbb		bx, [si]
	cmp		word [is_circular_track], 0
	jz		loc_6282
	and		bx, bx
	jns		loc_6278

loc_6270:
	add		bx, [word_23F2]
	js		loc_6270
	jmp		loc_6282

loc_6278:
	sub		bx, [word_23F2]
	jns		loc_6278
	add		bx, [word_23F2]

loc_6282:
	sub		ax, 2000h
	sbb		bx, 0
	jae		ret_62C0
	add		[si + 2], ax
	adc		[si], bx
	mov		ax, 98
	call	sub_50AC
	mov		ax, [si + 14]
	mul		word [word_3D36]
	mov		[si + 206], dx
	mov		[si + 14], dx
	add		word [di + 206], 100h
	add		word [di + 14], 100h
	mov		ax, [si + 14]
	shr		ax, 10
	add		ax, 16
	and		cx, cx
	js		loc_62BD
	neg		ax

loc_62BD:
	mov		[si + 28], ax

ret_62C0:
	ret


;
;
;
sub_62C1:
	mov		si, 417Eh
	mov		bp, [word_3C74]
	mov		[word_636E], bp

loc_62CC:
	mov		cx, [si + 8]
	mov		[word_635C], cx
	mov		cx, [si + 10]
	mov		dx, [si]
	mov		[word_6360], dx
	mov		dx, [si+2]
	mov		bp, [si+4]
	mov		[word_6362], bp
	mov		bp, [si+6]
	mov		[word_6366], bp
	mov		bx, [word_635C]
	add		bx, [word_23F8]
	mov		ax, bx
	sub		ax, [word_6366]
	shr		ax, 7
	inc		ax
	add		[word_6366], ax
	cmp		bx, [word_6366]
	jae		loc_630D
	mov		[word_6366], bx

loc_630D:
	mov		di, [word_6360]
	cmp		word [is_circular_track], 0
	jz		loc_6320
	mov		di, [di + arr_7856]
	and		di, 0FFh

loc_6320:
	shl		di, 4
	mov		al, [di - 7E9Bh]
	cbw
	mov		bx, ax
	mov		al, [di - 7E9Ch]
	cbw
	shl		ax, 4
	shl		bx, 4
	cmp		[word_6362], bx
	jns		loc_6354
	cmp		[word_6362], ax
	js		loc_6347
	add		[word_6362], cx
	jmp		loc_635F

loc_6347:
	add		word [word_6362], 4
	and		cx, cx
	jns		loc_635F
	neg		cx
	jmp		loc_635F

loc_6354:
	sub		word [word_6362], 4
	and		cx, cx
	js		loc_635F
	neg		cx

loc_635F:
	add		dx, [word_6366]
	adc		word [word_6360], 0
	mov		bp, [word_636E]
	cmp		bp, [word_3C74]
	jne		loc_638F
	mov		bx, [word_3C76]
	mov		ax, [bx + si + 2]
	mov		bp, [bx + si]
	add		ax, [word_3C72]
	adc		bp, [word_3C70]
	cmp		ax, dx
	mov		di, bp
	sbb		di, [word_6360]
	jae		loc_63C2
	jmp		loc_63A7

loc_638F:
	mov		bx, 0FFF4h
	mov		ax, [bx + si + 2]
	mov		bp, [bx + si]
	sub		ax, 4000h
	sbb		bp, 0
	cmp		ax, dx
	mov		di, bp
	sbb		di, [word_6360]
	jae		loc_63C2

loc_63A7:
	mov		dx, ax
	mov		[word_6360], bp
	mov		ax, [word_6366]
	xchg	[bx + si + 6], ax
	mov		[word_6366], ax
	mov		ax, [word_635C]
	xchg	[bx + si + 8], ax
	mov		[word_635C], ax
	xchg	[bx + si + 10], cx

loc_63C2:
	mov		[si + 2], dx
	mov		dx, [word_6360]
	mov		[si], dx
	mov		bp, [word_6362]
	mov		[si + 4], bp
	mov		bp, [word_6366]
	mov		[si + 6], bp
	mov		[si + 10], cx
	mov		cx, [word_635C]
	mov		[si + 8], cx
	add		si, 12
	dec		word [word_636E]
	js		ret_63EF
	jmp		loc_62CC

ret_63EF:
	ret


;
;
;
sub_63F0:
	test	word [word_3EE6], 7
	jnz		loc_643C
	mov		word [word_3F5C], 0
	cmp		word [word_3F5A], 0
	jz		loc_641A
	dec		word [word_3F5A]
	add		word [word_3F6A], 0C350h
	adc		word [word_3F68], 0
	mov		ax, 111
	call	sub_50AC

loc_641A:
	mov		word [word_4056], 0
	cmp		word [word_4054], 0
	jz		loc_643C
	dec		word [word_4054]
	add		word [word_4064], 0C350h
	adc		word [word_4062], 0
	mov		ax, 111
	call	sub_50AC

loc_643C:
	mov		ax, [word_3F5A]
	cmp		word [num_of_players], 0
	jz		loc_644A
	or		ax, [word_4054]

loc_644A:
	and		ax, ax
	ret


;
;
;
sub_644D:
	cmp		word [word_3EE4], 0
	jz		ret_64A7
	mov		ax, [word_4018]
	or		ax, [word_401A]
	jz		loc_6464
	cmp		word [word_3F54], 0
	jnz		loc_647A

loc_6464:
	mov		ax, [word_3F3A]
	mov		bx, [word_3F3C]
	mov		cx, [word_4034]
	mov		dx, [word_4036]
	call	sub_64A8
	mov		[word_401C], bp

loc_647A:
	cmp		word [num_of_players], 0
	jz		ret_64A7
	mov		ax, [word_4112]
	or		ax, [word_4114]
	jz		loc_6491
	cmp		word [word_404E], 0
	jnz		ret_64A7

loc_6491:
	mov		ax, [word_4034]
	mov		bx, [word_4036]
	mov		cx, [word_3F3A]
	mov		dx, [word_3F3C]
	call	sub_64A8
	mov		[word_4116], bp

ret_64A7:
	ret


;
;
;
sub_64A8:
	push	cx
	push	dx
	mov		bp, 1
	mov		di, 417Eh
	mov		cx, [word_3C74]
	inc		cx

loc_64B5:
	cmp		bx, [di + 2]
	mov		dx, ax
	sbb		dx, [di]
	adc		bp, 0
	add		di, 12
	loop	loc_64B5
	pop		dx
	pop		cx
	cmp		bx, dx
	sbb		ax, cx
	adc		bp, 0
	ret


;
;
;
sub_64CE:
	cmp		word [si + 228], 0
	jnz		loc_64FF
	call	sub_66DA
	call	sub_653A
	call	sub_6506
	call	sub_6522
	call	sub_66A3
	call	sub_6EFC
	cmp		word [word_3EE4], 0
	jz		loc_64F1
	call	sub_65CC

loc_64F1:
	call	sub_68FF
	cmp		word [word_3EE4], 0
	jz		ret_64FE
	call	sub_6685

ret_64FE:
	ret

loc_64FF:
	call	sub_6643
	call	sub_6685
	ret


;
;
;
sub_6506:
	mov		ax, [si + 32]
	or		ax, [si + 34]
	jz		ret_6521
	cmp		word [si + 26], 0
	jnz		ret_6521
	dec		word [si + 34]
	jge		ret_6521
	mov		word [si + 34], 49
	dec		word [si + 32]

ret_6521:
	ret


sub_6522:
	mov		ax, [si + 14]
	shr		ax, 7
	and		ax, 0FFF8h
	mov		bx, ax
	shr		ax, 2
	add		ax, bx
	add		[si + 48], ax
	adc		word [si + 46], 0
	ret


;
;
;
sub_653A:
	mov		bx, [si + 8]
	cmp		word [is_circular_track], 0
	jz		loc_654A
	mov		bl, [bx + arr_7856]
	mov		bh, 0

loc_654A:
	shl		bx, 4
	add		bx, 8156h
	mov		ax, [bx + 2]
	xchg	al, ah
	mov		dx, ax
	mov		al, 0
	sub		ax, dx
	cmp		dx, 8A00h
	jne		loc_65AA
	cmp		word [si + 24], 0
	jne		loc_65AF
	mov		word [si + 24], 1
	inc		word [si + 218]
	jz		loc_65AF
	add		word [si + 48], 4E20h
	adc		word [si + 46], 0
	mov		di, [si + 218]
	shl		di, 1
	mov		dx, [di + word_2422]
	mov		word [si + 168], 128
	mov		ax, [si + 34]
	add		dx, [si + 32]
	cmp		dx, 100
	jb		loc_659D
	mov		dx, 99
	mov		ax, 49

loc_659D:
	mov		[si + 34], ax
	mov		[si + 32], dx
	mov		word [si + 26], 0
	jmp		loc_65AF

loc_65AA:
	mov		word [si + 24], 0

loc_65AF:
	mov		ax, [bx + 10]
	xchg	al, ah
	and		ax, 8000h
	rol		ax, 1
	mov		[si + 36], ax
	mov		al, [bx + 114]
	cmp		al, 0FCh
	jne		ret_65CB
	mov		al, [bx + 115]
	cbw
	mov		[si + 182], ax

ret_65CB:
	ret


;
;
;
sub_65CC:
	mov		ax, [si + 222]
	or		ax, [si + 224]
	jz		loc_65DC
	cmp		word [si + 26], 0
	jnz		ret_6642

loc_65DC:
	mov		bx, [si]
	cmp		word [is_circular_track], 0
	jz		loc_65EB
	mov		bl, [bx + arr_7856]
	mov		bh, 0

loc_65EB:
	mov		word [si + 234], 0
	shl		bx, 4
	test	byte [bx - 7E9Fh], 8
	jz		ret_6642

loc_65FB:
	mov		word [si + 234], 1
	mov		ax, [word_633E]
	shl		ax, 2
	sub		ax, 24
	cmp		ax, [si + 4]
	jns		ret_6642
	add		ax, 64
	cmp		ax, [si + 4]
	js		ret_6642
	cmp		word [si + 14], 1066
	jae		ret_6642
	cmp		byte [si + 247], 0
	jz		ret_6642
	cmp		word [si + 232], 0
	jnz		ret_6642
	mov		word [si + 230], 1
	mov		word [si + 40], 0
	mov		word [si + 14], 0
	mov		word [si + 232], 25

ret_6642:
	ret


;
;
;
sub_6643:
	mov		word [si + 40], 0
	mov		word [si + 14], 0
	cmp		byte [si + 0F6h], 0
	jz		loc_6667
	cmp		word [si + 232], 0
	jnz		loc_6667
	mov		word [si + 230], 0
	mov		word [si + 232], 25

loc_6667:
	mov		ax, [si + 222]
	or		ax, [si + 224]
	jnz		loc_6676
	mov		word [si + 26], 0

loc_6676:
	add		word [si + 222], 128
	jae		ret_6684
	mov		word [si + 222], 0FFFFh

ret_6684:
	ret


;
;
;
sub_6685:
	cmp		word [si + 232], 0
	jz		loc_6690
	dec		word [si + 232]

loc_6690:
	mov		ax, [si + 230]
	and		ax, ax
	js		ret_66A2
	mov		[si + 228], ax
	mov		word [si + 230], 0FFFFh

ret_66A2:
	ret


;
;
;
sub_66A3:
	cmp		word [word_3EE4], 0
	jz		ret_66D9
	cmp		word [si + 26], 0
	jnz		ret_66D9
	mov		ax, [si + 44]
	sub		ax, 5000
	jns		loc_66BB
	mov		ax, 0

loc_66BB:
	add		ax, [si + 44]
	mov		dx, 64
	mul		dx
	sub		[si + 224], ax
	sbb		[si + 222], dx
	jae		ret_66D9
	mov		word [si + 222], 0
	mov		word [si + 224], 0

ret_66D9:
	ret


;
;
;
sub_66DA:
	mov		bp, [si + 4]
	mov		[word_6364], bp
	mov		bp, [si + 6]
	mov		[word_6362], bp
	mov		ax, [si + 206]
	and		ax, ax
	js		loc_66F6
	add		[si + 2], ax
	adc		word [si], 0

loc_66F6:
	cmp		word [si + 38], 0
	jz		loc_6708
	cmp		ax, [word_2AE4]
	jb		loc_6708
	add		ax, [word_2AE4]
	shr		ax, 1

loc_6708:
	cmp		ax, [word_2AE6]
	jae		loc_6714
	add		ax, [word_2AE6]
	shr		ax, 1

loc_6714:
	mov		bx, ax
	imul	word [si + 16]
	add		[word_6362], ax
	adc		[word_6364], dx
	shl		ax, 1
	rcl		dx, 1
	shl		ax, 1
	rcl		dx, 1
	add		[word_6362], ax
	adc		[word_6364], dx
	mov		ax, bx
	cmp		word [word_6394], 0
	jz		loc_673D
	jmp		loc_67CD

loc_673D:
	cmp		word [si + 26], 0
	jnz		loc_67BC
	cmp		word [si + 14], 0
	jz		loc_6755
	cmp		word [si + 196], 0
	jz		loc_6755
	mov		bx, 0FFFFh
	jmp		loc_6783

loc_6755:
	mov		bx, [si + 14]
	sub		bx, ax
	push	ax
	mov		ax, bx
	imul	word [si + 16]
	mov		bx, ax
	mov		[word_6358], dx
	pop		ax
	and		dx, dx
	jns		loc_6778
	neg		bx
	mov		dx, 0
	sbb		dx, [word_6358]
	mov		[word_6358], dx

loc_6778:
	sub		bx, 8000h
	sbb		word [word_6358], 0
	js		loc_67BC

loc_6783:
	cmp		word [si + 178], 0
	jns		loc_67A5
	cmp		word [word_3EE0], 50
	jl		loc_67BC
	mov		ax, 108
	mov		ah, 4
	cmp		si, word_3F3A
	jz		loc_679E
	inc		ah

loc_679E:
	call	sub_50AC
	mov		[si + 178], ax

loc_67A5:
	mov		ax, [si + 178]
	and		ax, ax
	js		loc_67CD
	shr		bx, 8
	cmp		bl, 64
	jb		loc_67B7
	mov		bl, 64

loc_67B7:
	call	sub_50F8
	jmp		loc_67CD

loc_67BC:
	mov		ax, [si + 178]
	and		ax, ax
	js		loc_67CD
	call	sub_514A
	mov		word [si + 178], 0FFFFh

loc_67CD:
	cmp		word [word_63B0], 0
	jz		loc_6803
	mov		ax, [word_3EEA]
	sub		ax, 2000h
	js		loc_6803
	mul		word [si + 14]
	shr		dx, 1
	rcr		ax, 1
	shr		dx, 1
	rcr		ax, 1
	shr		dx, 1
	rcr		ax, 1
	shr		dx, 1
	rcr		ax, 1
	shr		dx, 1
	rcr		ax, 1
	shr		dx, 1
	rcr		ax, 1
	shr		dx, 1
	rcr		ax, 1
	add		[word_6362], ax
	adc		[word_6364], dx

loc_6803:
	mov		ax, [si + 18]
	mov		bx, ax
	add		ax, bx
	add		ax, bx
	shl		ax, 2
	imul	word [si + 14]
	add		[word_6362], ax
	adc		[word_6364], dx
	mov		ax, [si + 30]
	mov		dx, [si + 28]
	sar		dx, 1
	rcr		ax, 1
	add		[word_6362], ax
	adc		[word_6364], dx
	mov		dx, [word_6364]
	mov		cx, [word_6362]
	mov		ax, [word_6334]
	cmp		dx, ax
	jg		loc_6840
	mov		dx, ax
	mov		cx, 0

loc_6840:
	mov		ax, [word_6336]
	cmp		dx, ax
	jl		loc_684C
	mov		dx, ax
	mov		cx, 0

loc_684C:
	mov		[si + 4], dx
	mov		[si + 6], cx
	mov		dx, 0
	mov		ax, [si]
	cmp		word [is_circular_track], 0
	jz		loc_6866
	mov		bx, ax
	mov		al, [bx + arr_7856]
	mov		ah, 0

loc_6866:
	shl		ax, 4
	mov		di, 8156h
	add		di, ax
	mov		bp, [di + 10]
	ror		bp, 8
	mov		ax, [si + 2]
	shr		ax, 14
	xor		al, 3
	shl		ax, 2
	mov		cl, al
	shr		bp, cl
	and		bp, 0Fh
	cmp		bp, 2
	jz		loc_689A
	cmp		word [word_6392], 0
	jz		loc_68BB
	cmp		bp, 1
	jnz		loc_68BB
	mov		dx, 400h

loc_689A:
	cmp		word [word_63A8], 0
	jz		loc_68BB
	mov		ax, [si + 4]
	add		ax, 200h
	shr		ax, 4
	mov		di, [word_46E8]
	add		di, ax
	mov		bl, [di]
	shl		bx, 9
	cmp		bx, dx
	js		loc_68BB
	mov		dx, bx

loc_68BB:
	mov		[si + 202], dx
	mov		ax, [si + 200]
	cmp		ax, dx
	je		loc_68DD
	jns		loc_68D4
	add		ax, 200h
	cmp		ax, dx
	js		loc_68DD 
	mov		ax, dx
	jmp		loc_68DD

loc_68D4:
	sub		ax, 200h
	cmp		ax, dx
	jns		loc_68DD
	mov		ax, dx

loc_68DD:
	mov		[si + 200], ax
	mov		ax, [si + 14]
	shr		ax, 1
	cmp		ax, 800h
	jb		loc_68EE
	mov		ax, 800h

loc_68EE:
	add		ax, [si + 208]
	cmp		ax, 2000h
	jb		loc_68FA
	sub		ax, 2000h

loc_68FA:
	mov		[si + 208], ax
	ret


;
;
;
sub_68FF:
	cmp		word [si + 14], 0
	jnz		loc_6917
	mov		word [si + 244], 0
	mov		word [si + 246], 0
	mov		word [si + 248], 0

loc_6917:
	cmp		word [si + 26], 0
	jz		sub_6934
	push	word [si + 14]
	call	sub_6934
	pop		ax
	sub		ax, 24
	jns		loc_692C
	mov		ax, 0

loc_692C:
	mov		[si + 14], ax
	mov		[si + 206], ax
	ret


;
;
;
sub_6934:
	cmp		word [si + 64], 0
	jz		loc_6985
	mov		bx, [si + 200]
	neg		bx
	sub		word [si + 62], 80
	mov		ax, [si + 62]
	add		ax, [si + 60]
	cmp		ax, bx
	jns		loc_6980
	and		bx, bx
	jz		loc_6966
	mov		word [si + 194], 0
	mov		word [si + 192], 1
	mov		ax, 100
	call	sub_50AC
	jmp		loc_6973

loc_6966:
	neg		word [si + 62]
	shr		word [si + 62], 1
	cmp		word [si + 62], 100h
	jns		loc_697D

loc_6973:
	mov		word [si + 64], 0
	mov		word [si + 62], 0

loc_697D:
	mov		ax, 0

loc_6980:
	mov		[si + 60], ax
	jmp		loc_698E

loc_6985:
	mov		ax, [si + 200]
	neg		ax
	mov		[si + 60], ax

loc_698E:
	mov		bp, [si + 16]
	mov		[word_636A], bp
	mov		bp, [si + 14]
	mov		[word_636E], bp
	mov		bp, [si + 4]
	mov		[word_6364], bp
	mov		bp, [si + 6]
	mov		[word_6362], bp
	mov		dx, [si + 40]
	mov		word [si + 38], 0
	cmp		word [si + 64], 0
	jz		loc_69BB
	jmp		loc_6A7B

loc_69BB:
	mov		bp, [word_2AE8]
	cmp		byte [si + 244], 0
	jz		loc_69CA
	sub		[word_636A], bp

loc_69CA:
	cmp		byte [si + 245], 0
	jz		loc_69D5
	add		[word_636A], bp

loc_69D5:
	mov		cx, dx
	mov		di, [word_2A62]
	shl		cx, 1
	add		di, cx
	mov		cx, [di]
	push	dx
	mov		dx, [word_636E]
	mov		ax, 0
	div		cx
	pop		dx
	cmp		ax, 1F40h
	jb		loc_69F4
	mov		ax, 1F3Fh

loc_69F4:
	cmp		word [si + 188], 0
	jz		loc_6A04					; if is not a turbo zone?
	dec		word [si + 188]
	mov		di, 5436h
	jmp		loc_6A13

; not a turbo zone
loc_6A04:
	mov		di, [word_2A60]
	cmp		byte [si + 246], 0
	jz		loc_6A18
	mov		di, [word_2A5E]

loc_6A13:
	mov		word [si + 38], 0FFFFh

loc_6A18:
	shr		ax, 7
	shl		ax, 1
	mov		bx, ax
	mov		ax, [bx + di]
	push	dx
	mov		dx, 0C00h
	imul	dx
	shr		cx, 1
	idiv	cx
	pop		dx
	add		[word_636E], ax
	cmp		di, [word_2A60]
	jz		loc_6A4A
	mov		word [si + 196], 0
	mov		bx, [word_636E]
	sub		bx, [si + 206]
	cmp		bx, [word_2AE2]
	jns		loc_6A5A

loc_6A4A:
	mov		bp, [word_636E]
	mov		[si + 206], bp
	mov		word [si + 196], 0
	jmp		loc_6A7B

loc_6A5A:
	mov		word [si + 196], 1
	sar		bx, 5
	add		[si + 206], bx
	cmp		word [si + 206], 1AAh
	jns		loc_6A7B
	mov		word [si + 206], 1AAh
	mov		word [si + 196], 0

loc_6A7B:
	mov		bp, [si + 212]
	add		[word_636A], bp
	jz		loc_6A91
	js		loc_6A8D
	dec		word [word_636A]
	jmp		loc_6A91

loc_6A8D:
	inc		word [word_636A]

loc_6A91:
	cmp		word [word_636A], 20h
	jle		loc_6A9E
	mov		word [word_636A], 20h

loc_6A9E:
	cmp		word [word_636A], 0FFE0h
	jge		loc_6AAB
	mov		word [word_636A], 0FFE0h

loc_6AAB:
	cmp		word [si + 212], 0
	jz		loc_6ABE
	jns		loc_6ABA
	inc		word [si + 212]
	jmp		loc_6ABE

loc_6ABA:
	dec		word [si + 212]

loc_6ABE:
	cmp		word [si + 28], 0
	jz		loc_6ACE
	jns		loc_6ACB
	inc		word [si + 28]
	jmp		loc_6ACE

loc_6ACB:
	dec		word [si + 28]

loc_6ACE:
	cmp		word [si + 60], 0
	jg		loc_6B0D
	mov		ax, [word_6364]
	add		ax, 512
	shr		ax, 4
	mov		di, [word_43A6]
	add		di, ax
	mov		al, [di]
	cmp		al, 0
	jz		loc_6AF7
	cbw
	shl		ax, 6
	push	dx
	mul		word [word_636E]
	mov		[word_636E], dx
	pop		dx

loc_6AF7:
	mov		ax, [si + 22]
	sar		ax, 6
	add		[word_636E], ax
	cmp		byte [si + 247], 0
	jz		loc_6B0D
	sub		word [word_636E], 48

loc_6B0D:
	cmp		word [word_636E], 1AAh
	jns		loc_6B1B
	mov		word [word_636E], 1AAh

loc_6B1B:
	mov		cx, dx
	mov		di, [word_2A62]
	shl		cx, 1
	add		di, cx
	mov		cx, [di]
	push	dx
	mov		dx, [word_636E]
	mov		ax, 0
	div		cx
	pop		dx
	cmp		ax, 3E8h
	jns		loc_6B3A
	mov		ax, 3E8h

loc_6B3A:
	cmp		ax, 1F3Fh
	js		loc_6B42
	mov		ax, 1F3Fh

loc_6B42:
	mov		[word_1F93], ax
	push	dx
	mul		cx
	mov		[word_636E], dx
	pop		dx
	mov		bx, dx
	cmp		word [si + 26], 0
	jnz		loc_6B81
	cmp		word [si + 188], 0
	jnz		loc_6B81
	cmp		word [si + 58], 0
	jnz		loc_6B81
	cmp		byte [si + 248], 0
	jz		loc_6B71
	cmp		dx, 4
	jz		loc_6B71
	inc		bx
	jmp		loc_6BA0

loc_6B71:
	cmp		byte [si + 249], 0
	jz		loc_6B7F
	and		dx, dx
	jz		loc_6B7F
	dec		bx
	jmp		loc_6BA0

loc_6B7F:
	jmp		loc_6BD4

loc_6B81:
	mov		ax, [word_1F93]
	cmp		ax, [si + 44]
	ja		loc_6B95
	cmp		ax, 0DACh
	jae		loc_6BD4
	and		bx, bx
	jz		loc_6BD4
	dec		bx
	jmp		loc_6BA0

loc_6B95:
	cmp		ax, 1388h
	jb		loc_6BD4
	cmp		bx, 4
	jz		loc_6BD4
	inc		bx

loc_6BA0:
	mov		cx, bx
	mov		di, [word_2A62]
	shl		cx, 1
	add		di, cx
	mov		cx, [di]
	push	dx
	mov		dx, [word_636E]
	mov		ax, 0
	div		cx
	pop		dx
	cmp		ax, 3E8h
	jb		loc_6BD4
	cmp		ax, 1F3Fh
	jae		loc_6BD4
	mov		[word_1F93], ax
	mul		cx
	mov		[word_636E], dx
	mov		dx, bx
	mov		bp, [word_636E]
	mov		[si + 206], bp

loc_6BD4:
	mov		[si + 40], dx
	mov		bp, [word_636A]
	mov		[si + 16], bp
	mov		bp, [word_636E]
	mov		[si + 14], bp				; set speed
	mov		ax, [word_1F93]
	mov		[si + 44], ax
	ret


;
;
;
sub_6BEC:
	cmp		word [word_3EE4], 0
	jnz		loc_6BF6
	jmp		loc_6D56

loc_6BF6:
	mov		di, 3CECh
	mov		dx, [word_3CE2]
	mov		cx, dx
	shl		cx, 1
	add		di, cx
	mov		si, 417Eh
	mov		bx, [word_3CE0]
	mov		cx, bx
	mov		bp, cx
	add		cx, bp
	add		cx, bp
	shl		cx, 2
	add		si, cx
	cmp		word [word_3F54], 0
	jnz		loc_6C2E
	mov		bp, [word_4018]
	or		bp, [word_401A]
	jnz		loc_6C2E
	mov		word [word_3F54], 1

loc_6C2E:
	cmp		word [word_404E], 0
	jnz		loc_6C45
	mov		bp, [word_4112]
	or		bp, [word_4114]
	jnz		loc_6C45
	mov		word [word_404E], 1

loc_6C45:
	mov		ax, [word_3CDA]
	mov		bp, [word_3CD8]
	cmp		word [word_401C], 11
	jae		loc_6C95
	cmp		[word_3F3A], bp
	jl		loc_6C95
	jg		loc_6C61
	cmp		[word_3F3C], ax
	jl		loc_6C95

loc_6C61:
	cmp		word [word_3F54], 0
	jz		loc_6C78
	mov		bp, [word_4018]
	or		bp, [word_401A]
	jnz		loc_6C95
	mov		word [word_4018], 1

loc_6C78:
	mov		word [word_3F54], 2
	inc		dx
	mov		bp, [word_3CDC]
	mov		[di], bp
	add		di, 2
	cmp		word [word_4012], 0
	jnz		loc_6C95
	mov		word [word_4012], 1

loc_6C95:
	cmp		word [num_of_players], 0
	jz		loc_6CEC
	mov		ax, [word_3CDA]
	mov		bp, [word_3CD8]
	cmp		word [word_4116], 11
	jae		loc_6CEC
	cmp		[word_4034], bp
	jl		loc_6CEC
	jg		loc_6CB8
	cmp		[word_4036], ax
	jl		loc_6CEC

loc_6CB8:
	cmp		word [word_404E], 0
	jz		loc_6CCF
	mov		bp, [word_4112]
	or		bp, [word_4114]
	jnz		loc_6CEC
	mov		word [word_4112], 1

loc_6CCF:
	mov		word [word_404E], 2
	inc		dx
	mov		bp, [word_3CDC]
	mov		[di], bp
	add		di, 2
	cmp		word [word_410C], 0
	jnz		loc_6CEC
	mov		word [word_410C], 1

loc_6CEC:
	mov		cx, [word_3C74]
	inc		cx
	cmp		bx, cx
	jz		loc_6D15
	mov		ax, [word_3CD8]
	cmp		ax, [si]
	jg		loc_6D15
	jl		loc_6D06
	mov		ax, [word_3CDA]
	cmp		ax, [si + 2]
	jge		loc_6D15

loc_6D06:
	mov		ax, [word_3CDC]
	mov		[di], ax
	add		di, 2
	inc		bx
	inc		dx
	add		si, 12
	jmp		loc_6CEC

loc_6D15:
	mov		[word_3CE0], bx
	mov		[word_3CE2], dx
	cmp		dx, 10
	jb		loc_6D3C
	cmp		word [word_401C], 11
	jb		loc_6D2F
	mov		word [word_3F54], 1

loc_6D2F:
	cmp		word [word_4116], 11
	jb		loc_6D3C
	mov		word [word_404E], 1

loc_6D3C:
	mov		bp, bx

loc_6D3E:
	mov		ax, [word_3CD8]
	mul		word [word_3CDC]
	div		word [si]
	add		si, 12
	mov		[di], ax
	add		di, 2
	inc		bx
	cmp		bx, 11
	jbe		loc_6D3E
	ret


loc_6D56:
	mov		si, word_3F3A
	call	sub_6D5F
	mov		si, word_4034


;
;
;
sub_6D5F:
	mov		ax, [word_3CDA]
	mov		bp, [word_3CD8]
	cmp		bp, [si]
	jl		loc_6D80
	jg		loc_6D71
	cmp		ax, [si + 2]
	jl		loc_6D80

loc_6D71:
	mov		bx, [si + 32]
	or		bx, [si + 34]
	jnz		loc_6D92
	mov		word [si + 26], 1
	jmp		loc_6D92

loc_6D80:
	mov		word [si + 26], 2
	cmp		word [si + 216], 0
	jnz		loc_6D92
	mov		word [si + 216], 1

loc_6D92:
	sub		bp, 16
	cmp		bp, [si]
	jg		ret_6DA5
	jl		loc_6D9F
	cmp		ax, [si]
	jge		ret_6DA5

loc_6D9F:
	mov		word [si + 220], 1

ret_6DA5:
	ret


;
;
;
sub_6DA6:
	cmp		word [word_3EE4], 0
	jz		loc_6E05
	cmp		word [word_3F54], 0
	jz		loc_6DFE
	cmp		word [word_401E], 0
	jnz		loc_6DC2
	cmp		word [word_3F48], 0
	jnz		loc_6DFE

loc_6DC2:
	cmp		word [num_of_players], 0
	jz		loc_6DDE
	cmp		word [word_404E], 0
	jz		loc_6DFE
	cmp		word [word_4118], 0
	jnz		loc_6DDE
	cmp		word [word_4042], 0
	jnz		loc_6DFE

loc_6DDE:
	mov		ax, 1
	cmp		word [word_401C], 11
	jae		loc_6DEB
	mov		ax, 2

loc_6DEB:
	cmp		word [num_of_players], 0
	jz		loc_6DFC
	cmp		word [word_4116], 11
	jae		loc_6DFC
	mov		ax, 2

loc_6DFC:
	jmp		loc_6E01

loc_6DFE:
	mov		ax, 0

loc_6E01:
	mov		[word_3CE4], ax
	ret

loc_6E05:
	cmp		word [word_3F54], 0
	jz		loc_6E4B
	cmp		word [word_3F48], 0
	jnz		loc_6E4B
	cmp		word [num_of_players], 0
	jz		loc_6E28
	cmp		word [word_404E], 0
	jz		loc_6E4B
	cmp		word [word_4042], 0
	jnz		loc_6E4B

loc_6E28:
	cmp		word [word_3F54], 2
	jz		loc_6E44
	cmp		word [num_of_players], 0
	jz		loc_6E3D
	cmp		word [word_404E], 2
	jz		loc_6E44

loc_6E3D:
	mov		word [word_3CE4], 1
	ret

loc_6E44:
	mov		word [word_3CE4], 2
	ret

loc_6E4B:
	mov		word [word_3CE4], 0
	ret


;
;
;
sub_6E52:
	mov		si, word_3F3A
	call	sub_6E5B
	mov		si, word_4034


sub_6E5B:
	cmp		word [word_3EE0], 0
	js		ret_6E8E
	mov		ax, [si + 26]
	and		ax, ax
	jz		loc_6E7D
	cmp		ax, 2
	jz		ret_6E8E
	cmp		word [word_3EE4], 0
	jnz		loc_6E7D
	mov		ax, [si + 32]
	or		ax, [si + 34]
	jnz		ret_6E8E

loc_6E7D:
	mov		ax, [si + 4]
	mov		[si + 12], ax
	mov		ax, [si]
	mov		[si + 8], ax
	mov		ax, [si + 2]
	mov		[si + 10], ax

ret_6E8E:
	ret


;
;
;
sub_6E8F:
	cmp		word [word_1F95], 1
	jz		ret_6EBD
	push	ds
	pop		es
	mov		si, 417Eh
	mov		di, 427Eh
	mov		cx, [word_3C74]
	inc		cx

loc_6EA3:
	movsw
	movsw
	movsw
	add		si, 6
	loop	loc_6EA3
	mov		si, word_3F3A
	call	sub_6EBE
	mov		si, word_4034
	call	sub_6EBE
	mov		word [word_1F95], 0FFFFh

ret_6EBD:
	ret


;
;
;
sub_6EBE:
	mov		ax, [si]
	mov		[si + 78], ax
	mov		ax, [si + 2]
	mov		[si + 80], ax
	mov		ax, [si + 174]
	mov		[si + 82], ax
	mov		ax, [si + 176]
	mov		[si + 84], ax
	mov		ax, [si + 8]
	mov		[si + 86], ax
	mov		ax, [si + 10]
	mov		[si + 88], ax
	mov		ax, [si + 12]
	mov		[si + 90], ax
	mov		ax, [si + 36]
	mov		[si + 96], ax
	mov		ax, [si + 20]
	mov		[si + 92], ax
	mov		ax, [si + 22]
	mov		[si + 94], ax
	ret


;
;
;
sub_6EFC:
	mov		di, [si + 8]
	cmp		word [is_circular_track], 0
	jz		loc_6F0E
	mov		di, [di + arr_7856]
	and		di, 0FFh

loc_6F0E:
	shl		di, 4
	add		di, 8156h
	mov		bp, [si + 10]
	shr		bp, 4
	mov		al, [di + 1]
	cbw
	shl		ax, 1
	imul	bp
	mov		cl, ah
	mov		ch, dl
	mov		al, [di + 13]
	cbw
	shl		ax, 5
	add		ax, cx
	neg		ax
	mov		[si + 22], ax
	mov		al, [di]
	cbw
	shl		ax, 1
	mov		[si + 18], ax
	imul	bp
	mov		cl, ah
	mov		ch, dl
	mov		al, [di + 12]
	cbw
	shl		ax, 5
	add		ax, cx
	neg		ax
	and		ax, 1FFFh
	mov		[si + 20], ax
	ret


;
;
;
sub_6F55:
	cmp		word [word_63A2], 0
	jz		loc_6F9E
	mov		ax, [word_3EE6]
	inc		ax
	test	ax, 1FFh
	jnz		loc_6F9E
	cmp		ax, arr_2400
	jae		loc_6F9E
	mov		es, [word_6330]
	mov		ax, [es:240h]
	push	ax
	xchg	al, ah
	push	ax
	mov		ax, [es:640h]
	push	ax
	xchg	al, ah
	push	ax
	mov		bp, 4

loc_6F81:
	mov		si, 7556h
	pop		ax
	mov		ah, 0
	add		si, ax
	add		si, ax
	add		si, ax
	inc		byte [si]
	inc		byte [si + 1]
	inc		byte [si + 2]
	dec		bp
	jnz		loc_6F81
	mov		si, palette
	call	sub_D18C

loc_6F9E:
	cmp		byte [byte_3D6A], 0
	jnz		ret_6FD9
	cmp		word [word_63AA], 0
	jz		ret_6FD9
	test	word [word_3EE6], 3
	jnz		ret_6FD9
	call	sub_AB9A
	and		al, 3Fh
	cmp		al, 3
	mov		ax, 1300h
	mov		bl, ah
	jae		loc_6FCD
	mov		ax, 6Dh
	call	sub_50AC
	mov		ax, 3030h
	mov		bl, 30h

loc_6FCD:
	mov		si, palette
	mov		[si + 36], ax
	mov		[si + 38], bl
	call	sub_D18C

ret_6FD9:
	ret


; ---------------------------------------------------------------------------
; demo gameplay
loc_6FDA:
	call	clear_screen
	call	sub_7044

loc_6FE0:
	call	sub_7044
	mov		word [word_3ED8], word_3F3A
	call	sub_70EC
	call	sub_7214
	call	sub_7329
	call	sub_73BA
	call	p1_draw_background
	call	p1_draw_the_road
	call	sub_853E

loc_6FFE:
	call	draw_race_info
	call	brandish_the_flag
	call	draw_race_text
	call	sub_929A
	cmp		word [num_of_players], 0
	je		loc_7038
	mov		word [word_3ED8], word_4034
	call	sub_70FE
	call	sub_7229
	call	sub_732E
	call	sub_73D5
	call	p2_draw_background
	call	p2_draw_the_road
	call	sub_853C
	call	loc_8FA3
	call	loc_8F35
	call	sub_8E0E
	call	sub_929F

; if a single player
loc_7038:
	cmp		byte [byte_3D6A], 0
	jz		loc_6FE0
	call	fade_in
	jmp		loc_6FE0


;
;
;
sub_7044:
	mov		ax, 0

loc_7047:
	call	sub_D6F9
	xchg	ax, [word_1F95]
	and		ax, ax
	jz		loc_7047
	mov		word [word_1F95], 1
	push	ds
	pop		es
	mov		si, 426Eh
	mov		di, word_42F6
	movsw
	movsw
	mov		si, 4272h
	mov		di, word_42FA
	movsw
	movsw
	mov		si, 4276h
	mov		di, word_42FE
	movsw
	movsw
	mov		si, 427Ah
	mov		di, word_4302
	movsw
	movsw
	mov		si, 427Eh
	mov		di, word_4306
	mov		cx, [word_3C74]
	inc		cx

loc_7085:
	movsw
	movsw
	movsw
	add		di, 2
	loop	loc_7085
	mov		si, word_3F3A
	call	sub_70A0
	mov		si, word_4034
	call	sub_70A0
	mov		word [word_1F95], 0
	ret


;
;
;
sub_70A0:
	mov		ax, [si + 86]
	mov		[si + 132], ax				; word_3FBE = word_3F90
	mov		ax, [si + 88]
	mov		[si + 134], ax				; word_3FC0 = word_3F92
	mov		ax, [si + 90]
	mov		[si + 136], ax				; word_3FC2 = word_3F94
	mov		ax, [si + 78]
	mov		[si + 124], ax				; word_3FB6 = word_3F88
	mov		ax, [si + 80]
	mov		[si + 126], ax				; word_3FB8 = word_3F8A
	mov		ax, [si + 82]
	mov		[si + 128], ax				; word_3FBA = word_3F8C
	mov		ax, [si + 84]
	mov		[si + 130], ax				; word_3FBC = word_3F8E
	mov		ax, [si + 96]
	mov		[si + 120], ax				; word_3FB2 = word_3F9A
	mov		ax, [si + 92]
	mov		[si + 142], ax				; word_3FC8 = word_3F96
	mov		ax, [si + 94]
	mov		[si + 140], ax				; word_3FC6 = word_3F98
	mov		ax, [si + 208]
	mov		[si + 242], ax				; word_402C = word_400A
	ret


;
;
;
sub_70EC:
	mov		ax, [word_3FBE]
	mov		bp, [word_3FC0]
	call	sub_7110
	mov		[word_3FB4], ax
	mov		[word_3FCA], bx
	ret


;
;
;
sub_70FE:
	mov		ax, [word_40B8]
	mov		bp, [word_40BA]
	call	sub_7110
	mov		[word_40AE], ax
	mov		[word_40C4], bx
	ret


;
;
;
sub_7110:
	push	ds
	pop		es
	mov		di, arr_C568
	mov		bx, arr_67C2
	and		bp, 0F000h
	mov		cx, 80h
	cmp		word [is_circular_track], 0
	jz		loc_712E
	mov		si, ax
	mov		al, [si + arr_7856]
	mov		ah, 0

loc_712E:
	shl		ax, 4
	mov		si, 8151h
	add		si, ax
	mov		word [word_6352], 0
	mov		word [word_6356], 0
	mov		word [word_635A], 0
	mov		word [word_635E], 0
	mov		ax, [word_633A]
	mov		[word_636E], ax

loc_7154:
	add		si, 16
	mov		al, [si - 11]
	cbw
	mov		[word_6362], ax
	mov		al, [si - 10]
	cbw
	shl		ax, 1
	mov		[word_6366], ax

loc_7167:
	mov		ax, [word_6352]
	add		ax, [word_6362]
	mov		[word_6352], ax
	sar		ax, 1
	add		[word_635A], ax
	mov		ax, [word_6356]
	sub		ax, [word_6366]
	mov		[word_6356], ax
	add		[word_635E], ax
	mov		ax, [word_635A]
	and		al, 0FEh
	mov		dl, [si]
	shr		dl, 3
	and		dl, 1
	or		al, dl
	stosw
	mov		ax, [bx + 100h]
	imul	word [word_635E]
	mov		ax, dx
	add		ax, [bx]
	add		bx, 2
	stosw
	cmp		ax, [word_633A]
	jae		loc_71CF
	cmp		ax, [word_636E]
	jns		loc_71B4
	mov		[word_636E], al

loc_71B4:
	mov		ax, [word_636E]
	stosw
	mov		ax, [word_6352]
	stosw
	add		bp, 1000h
	loopne	loc_7167
	and		cx, cx
	jnz		loc_7154
	mov		bx, [word_636E]
	mov		ax, 80h
	jmp		loc_71F8

loc_71CF:
	cmp		ax, [word_633A]
	jns		loc_71EC
	mov		word [di], 0
	mov		word [di - 2], 0
	mov		bx, 0
	mov		ax, di
	sub		ax, arr_C568
	shr		ax, 3
	inc		ax
	jmp		loc_71F8

loc_71EC:
	mov		bx, [word_636E]
	mov		ax, di
	sub		ax, arr_C568
	shr		ax, 3

loc_71F8:
	mov		di, arr_C568
	and		word [di], 1
	add		di, 2
	mov		bp, [word_633A]
	mov		[di], bp
	add		di, 2
	mov		[di], bp
	add		di, 2
	mov		word [di], 0
	ret


;
;
;
sub_7214:
	mov		ax, [word_3FB4]
	mov		bp, [word_3FC0]
	mov		[word_6362], bp
	mov		bp, [word_3FBE]
	mov		[word_6364], bp
	jmp		loc_723E


;
;
;
sub_7229:
	mov		ax, [word_40AE]
	mov		bp, [word_40BA]
	mov		[word_6362], bp
	mov		bp, [word_40B8]
	mov		[word_6364], bp
	jmp		loc_723E


loc_723E:
	mov		di, 0C968h
	push	ds
	pop		es
	mov		word [word_6382], arr_C568
	mov		dx, ax
	dec		dx
	mov		dh, dl
	mov		dl, 0
	mov		bp, ax
	shl		bp, 1

loc_7254:
	lea		si, [bp + arr_68C2]
	shl		bp, 2
	add		[word_6382], bp
	mov		bx, [word_6382]
	mov		bx, [bx - 6]
	sub		word [word_6382], 12
	mov		bp, bx
	shl		bp, 1
	add		bp, bx
	shl		bp, 1
	add		di, bp

loc_7275:
	sub		si, 2
	mov		ax, [si]
	xchg	si, [word_6382]
	sub		si, 2
	mov		bp, [si]
	sub		si, 2
	mov		cx, [si]
	sub		si, 4
	xchg	si, [word_6382]
	cmp		bx, bp
	jnz		loc_7298
	dec		dh
	jns		loc_7275
	ret


loc_7298:
	sub		bx, bp
	cmp		bx, 0FFFFh
	jz		loc_72B0
	js		loc_72C2
	shl		bx, 1
	sub		di, bx
	shl		bx, 1
	sub		di, bx
	mov		bx, bp
	dec		dh
	jns		loc_7275
	ret


loc_72B0:
	mov		[di], cx
	add		di, 2
	stosw
	mov		[di], dx
	add		di, 2
	mov		bx, bp
	dec		dh
	jns		loc_7275
	ret


loc_72C2:
	push	bp
	neg		bx
	push	ax
	push	dx
	neg		ax
	add		ax, [si - 2]
	shl		ax, 4
	mov		al, 0
	mov		dx, 0
	div		bx
	mov		dx, 1000h
	mul		dx
	mov		[word_635E], ax
	mov		[word_6360], dx
	mov		ax, 100h
	mov		dx, 0
	div		bx
	mov		[word_1F97], ax
	pop		dx
	pop		ax
	sub		bx, 2
	mov		bp, 0

loc_72F5:
	mov		[di], cx
	add		di, 2
	stosw
	mov		[di], dx
	add		di, 2
	sub		dx, [word_1F97]
	add		bp, [word_635E]
	adc		ax, [word_6360]
	dec		bx
	jns		loc_72F5
	mov		[di], cx
	add		di, 2
	stosw
	mov		[di], dx
	add		di, 2
	sub		dx, [word_1F97]
	and		dx, 0FF00h
	pop		bx
	js		ret_7328
	jmp		loc_7275

ret_7328:
	ret


;
;
;
sub_7329:
	mov		di, word_3F3A
	jmp		loc_7333


;
;
;
sub_732E:
	mov		di, word_4034
	jmp		loc_7333

loc_7333:
	mov		ax, [di + 140]
	mov		[di + 166], ax
	mov		bx, [di + 144]
	sar		ax, 1
	mov		dx, [word_633A]
	sub		dx, 38h
	sub		dx, [word_1F99]
	sub		dx, ax
	mov		cx, dx
	add		dx, [word_1F99]
	mov		word [word_6362], 0
	mov		ax, cx
	and		ax, ax
	jns		loc_7368
	mov		cx, 0
	neg		ax
	mov		[word_6362], ax

loc_7368:
	and		dx, dx
	jns		loc_736F
	mov		dx, 0

loc_736F:
	mov		ax, bx
	sub		ax, dx
	jns		loc_7377
	mov		dx, bx

loc_7377:
	mov		ax, bx
	sub		ax, cx
	jns		loc_737F
	mov		cx, bx

loc_737F:
	mov		ax, bx
	sub		ax, dx
	mov		[word_6366], ax
	mov		ax, dx
	sub		ax, cx
	mov		[word_636A], ax
	mov		[word_636E], cx
	mov		[di + 146], cx
	mov		[di + 152], dx
	mov		bp, [word_6362]
	mov		[di + 150], bp
	mov		bp, [word_6366]
	mov		[di + 154], bp
	mov		bp, [word_636A]
	mov		[di + 148], bp
	mov		bp, [word_636E]
	mov		[di + 156], bp
	ret


;
;
;
sub_73BA:
	mov		dx, [word_3FC2]
	mov		bx, [word_3FCA]
	mov		ax, [word_3FF0]
	call	sub_73F0
	add		dx, 0A0h
	mov		[word_4028], dx
	mov		[word_402A], cx
	ret


;
;
;
sub_73D5:
	mov		dx, [word_40BC]
	mov		bx, [word_40C4]
	mov		ax, [word_40EA]
	call	sub_73F0
	add		dx, 0A0h
	mov		[word_4122], dx
	mov		[word_4124], cx
	ret


;
;
;
sub_73F0:
	mov		si, 0C968h
	mov		bp, bx
	shl		bx, 1
	add		si, bx
	add		si, bx
	add		si, bx
	mov		cx, 7FFFh
	shl		dx, 2
	mov		[word_6362], dx
	cmp		word [word_6396], 0
	jnz		loc_7411
	jmp		loc_7507

loc_7411:
	cmp		ax, 2
	jnz		loc_7419
	jmp		loc_74B7

loc_7419:
	cmp		ax, 0
	jnz		loc_7421
	jmp		loc_7507

loc_7421:
	jns		loc_7470
	jmp		loc_7425

loc_7425:
	mov		dx, 1000h

loc_7428:
	lodsw
	mov		di, ax
	and		di, 1
	ror		di, 4
	mov		bx, [si]
	or		di, bx
	shr		di, 4
	mov		[si], di
	add		si, 4
	and		di, 0FFh
	shl		bx, 2
	add		ax, [word_6362]
	neg		ax
	push	dx
	imul	bx
	mov		bx, dx
	pop		dx
	shl		di, 1
	mov		di, [di + arr_6BC2]
	add		bx, di
	cmp		bx, dx
	jns		loc_7461
	mov		dx, bx
	mov		cx, [si - 2]

loc_7461:
	sub		bx, di
	sub		bx, di
	mov		[si - 6], bx
	inc		bp
	cmp		bp, [word_633A]
	jnz		loc_7428
	ret


loc_7470:
	mov		dx, 0F000h

loc_7473:
	lodsw
	mov		di, ax
	and		di, 1
	ror		di, 4
	mov		bx, [si]
	or		di, bx
	shr		di, 4
	mov		[si], di
	add		si, 4
	and		di, 0FFh
	shl		bx, 2
	add		ax, [word_6362]
	neg		ax
	push	dx
	imul	bx
	mov		bx, dx
	pop		dx
	shl		di, 1
	mov		di, [di + arr_6BC2]
	sub		bx, di
	cmp		bx, dx
	js		loc_74AC
	mov		dx, bx
	mov		cx, [si - 2]

loc_74AC:
	mov		[si - 6], bx
	inc		bp
	cmp		bp, [word_633A]
	jnz		loc_7473
	ret


loc_74B7:
	mov		dx, 0

loc_74BA:
	lodsw
	mov		di, ax
	and		di, 1
	ror		di, 4
	mov		bx, [si]
	or		di, bx
	shr		di, 4
	mov		[si], di
	add		si, 4
	and		di, 0FFh
	shl		bx, 2
	add		ax, [word_6362]
	neg		ax
	push	dx
	imul	bx
	mov		bx, dx
	pop		dx
	shl		di, 1
	mov		di, [di + arr_6BC2]
	mov		ax, [si - 4]
	shr		ax, 1
	neg		ax
	add		ax, bp
	cmp		ax, dx
	js		loc_74FA
	mov		dx, ax
	mov		cx, [si - 2]

loc_74FA:
	sub		bx, di
	mov		[si - 6], bx
	inc		bp
	cmp		bp, [word_633A]
	jnz		loc_74BA
	ret


loc_7507:
	lodsw
	mov		di, ax
	and		di, 1
	ror		di, 4
	mov		bx, [si]
	or		di, bx
	shr		di, 4
	mov		[si], di
	add		si, 4
	and		di, 0FFh
	shl		bx, 2
	add		ax, [word_6362]
	neg		ax
	push	dx
	imul	bx
	mov		bx, dx
	pop		dx
	shl		di, 1
	mov		di, [di + arr_6BC2]
	sub		bx, di
	mov		[si - 6], bx
	inc		bp
	cmp		bp, [word_633A]
	jnz		loc_7507
	mov		cx, 0FFh
	ret


;
;
;
sub_7545:
	call	sub_770F
	call	loc_75B7
	mov		ax, [word_1FA2]
	mov		dx, 168
	mul		dx
	add		ax, 680
	shr		ax, 3
	add		ax, [word_63BC]
	sub		ax, 800h
	mov		es, ax
	mov		di, [word_1FA0]
	add		di, 8000h
	mov		dx, [word_1FA4]
	mov		ax, dx
	shr		ax, 3
	adc		ax, 1
	add		dx, ax
	cmp		dx, 2
	ja		loc_7580
	mov		dx, 2

loc_7580:
	mov		al, 85
	mul		dl
	mov		bl, ah
	mov		bh, 0
	cmp		bx, 1
	ja		loc_7590
	mov		bx, 1

loc_7590:
	mov		ax, bx
	shr		ax, 1
	sub		di, ax
	mov		si, bx
	shl		si, 3
	mov		ax, si
	shl		si, 1
	add		si, ax
	push	ds
	mov		ds, [word_1F9D]

loc_75A6:
	mov		bp, di
	mov		cx, bx
	rep movsb
	sub		si, bx
	lea		di, [bp - 336]
	dec		dx
	jnz		loc_75A6
	pop		ds
	ret


loc_75B7:
	mov		ax, [word_220C]
	add		ax, [word_220E]
	sar		ax, 1
	cmp		ax, 140h
	jb		loc_75C9
	add		sp, 2
	ret

loc_75C9:
	mov		bx, [word_2212]
	mov		cx, bx
	sub		cx, [word_633A]
	add		cx, 3Ah
	mov		dl, 0FFh
	xchg	dl, [byte_1F9F]
	and		dl, dl
	jz		loc_761B
	push	ax
	push	bx
	push	cx
	sub		bx, cx
	mov		cx, [word_1FA4]
	mov		dx, [word_1FA2]
	sub		dx, cx
	mov		cx, [word_1FA0]
	call	sub_775E
	pop		cx
	pop		bx
	pop		ax
	cmp		cx, 4
	jb		loc_761B
	push	ax
	push	bx
	push	cx
	sar		cx, 1
	sub		bx, cx
	mov		cx, [word_1FA4]
	mov		dx, [word_1FA2]
	sar		cx, 1
	sub		dx, cx
	mov		cx, [word_1FA0]
	call	sub_775E
	pop		cx
	pop		bx
	pop		ax

loc_761B:
	xchg	ax, [word_1FA0]
	xchg	bx, [word_1FA2]
	xchg	cx, [word_1FA4]
	mov		[word_1FA6], ax
	mov		[word_1FA8], bx
	mov		[word_1FAA], cx
	ret


;
;
;
sub_7633:
	cmp		word [word_63B4], 0
	jnz		loc_763B
	ret

loc_763B:
	mov		ax, [word_1FA0]
	mov		bx, [word_1FA2]
	sub		bx, [word_1FA4]
	mov		cx, ax
	mov		cx, 0
	mov		dx, bx
	call	sub_775E
	mov		ax, [word_1FA4]
	shr		ax, 1
	sub		[word_1FA2], ax
	mov		ax, [word_1FAA]
	shr		ax, 1
	sub		[word_1FA8], ax
	mov		ax, [word_633A]
	mov		dx, 168
	mul		dx
	add		ax, 200h
	shr		ax, 3
	add		ax, [word_63BC]
	mov		es, ax
	mov		di, 0
	mov		al, [es:di]
	cmp		al, 5
	jz		loc_7684
	cmp		al, 0F1h
	jnz		loc_7697

loc_7684:
	mov		cx, 320
	repe scasb
	mov		ax, di
	add		ax, 20h
	mov		bx, [word_633A]
	sub		bx, 1Dh
	jmp		loc_769E

loc_7697:
	mov		ax, [word_1FA0]
	mov		bx, [word_1FA2]

loc_769E:
	sub		ax, [word_1FA6]
	jae		ret_770E
	neg		ax
	sub		bx, [word_1FA8]
	jbe		ret_770E
	mov		bp, ax
	add		bp, ax
	cmp		bp, 14h
	jb		ret_770E
	mov		bp, ax
	mov		si, bx
	cmp		ax, 4
	jb		ret_770E
	xchg	ax, bx
	mov		dx, 100h
	mul		dx
	div		bx
	mul		word [word_1FA6]
	and		dx, dx
	jnz		loc_76E0
	shr		ax, 8
	adc		ax, [word_1FA8]
	cmp		ax, [word_633A]
	mov		bx, ax
	mov		ax, 0FFFFh
	jb		loc_7703

loc_76E0:
	cmp		si, 4
	jb		ret_770E
	mov		ax, 100h
	mul		bp
	div		si
	mov		dx, [word_633A]
	sub		dx, [word_1FA8]
	mul		dx
	shr		ax, 8
	neg		ax
	add		ax, [word_1FA6]
	mov		bx, [word_633A]

loc_7703:
	mov		cx, [word_1FA0]
	mov		dx, [word_1FA2]
	call	sub_775E

ret_770E:
	ret


;
;
;
sub_770F:
	mov		ax, [word_2212]
	mov		dx, 0A8h
	mul		dx
	add		ax, 2A8h
	shr		ax, 3
	add		ax, [word_63BC]
	mov		es, ax
	mov		di, [word_220C]
	cmp		di, 0
	jg		loc_772F
	mov		di, 0

loc_772F:
	mov		dx, 140h
	sub		dx, di
	jle		ret_775D
	mov		bp, [word_633A]
	sub		bp, [word_2212]
	jle		ret_775D

loc_7740:
	mov		bx, di
	mov		cx, dx
	mov		al, 5
	repe scasb
	inc		cx
	neg		cx
	add		cx, dx
	jz		loc_7756
	dec		di
	sub		di, cx
	mov		al, 0F1h
	rep stosb

loc_7756:
	lea		di, [bx + 336]
	dec		bp
	jnz		loc_7740

ret_775D:
	ret


;
;
;
sub_775E:
	cmp		ax, 320
	jg		loc_77BA
	cmp		cx, 320
	jae		loc_77BA
	cmp		bx, dx
	jb		loc_7770
	xchg	ax, cx
	xchg	bx, dx

loc_7770:
	sub		dx, bx
	inc		dx
	mov		bp, dx
	sub		cx, ax
	mov		di, ax
	mov		ax, 0A8h
	mul		bx
	add		ax, 2A8h
	shr		ax, 3
	add		ax, [word_63BC]
	sub		ax, 800h
	mov		es, ax
	add		di, 8000h
	mov		ax, cx
	and		ax, ax
	jns		loc_779A
	neg		ax
	std

loc_779A:
	mov		dx, 0
	inc		ax
	shl		ax, 8
	div		bp
	mov		dx, ax
	mov		cx, 0
	mov		bx, 0
	mov		al, 0

loc_77AD:
	add		bx, dx
	xchg	cl, bh
	rep stosb
	add		di, 336
	dec		bp
	jnz		loc_77AD

loc_77BA:
	cld
	ret


;
; P1: Draws the road.
;
p1_draw_the_road:						; 77BC
	mov		word [word_6372], 550h
	mov		bp, [word_3FC2]
	mov		[word_6362], bp
	mov		bp, [word_3FC0]
	mov		[word_6366], bp
	mov		bp, [word_3FBE]
	mov		[word_6368], bp
	mov		bx, [word_3FCA]
	mov		cx, [word_3FD2]
	call	draw_the_road
	ret


;
; P2: Draws the road.
;
p2_draw_the_road:					; 77E6
	mov		word [word_6372], 550h
	mov		bp, [word_40BC]
	mov		[word_6362], bp
	mov		bp, [word_40BA]
	mov		[word_6366], bp
	mov		bp, [word_40B8]
	mov		[word_6368], bp
	mov		bx, [word_40C4]
	mov		cx, [word_40CC]
	call	draw_the_road
	ret


;
;
;
draw_the_road:						; 7810
	mov		word [word_6382], 0C968h
	mov		ax, [word_6366]
	mov		dx, [word_6368]
	cmp		word [is_circular_track], 0
	jz		loc_782C
	mov		di, dx
	mov		dx, [di + arr_7856]
	mov		dh, 0

loc_782C:
	shl		ax, 1
	rcl		dx, 1
	shl		ax, 1
	rcl		dx, 1
	mov		[word_1FAC], dx
	mov		dx, [word_6366]
	ror		dx, 4
	and		dx, 3FFh
	mov		[word_636E], bx
	shl		bx, 1
	add		[word_6382], bx
	add		[word_6382], bx
	add		[word_6382], bx
	mov		al, 168
	mul		byte [word_636E]
	shl		ax, 1
	add		[word_6372], ax
	shl		word [word_6362], 3
	push	ds
	pop		es
	mov		di, word_1FAE
	mov		si, 8160h
	mov		ax, [word_1FAC]
	shl		ax, 2
	and		ax, 0FFF0h
	add		si, ax
	mov		cx, 9

loc_787C:
	lodsb
	shl		al, 1
	inc		al
	mov		ah, al
	shr		al, 4
	and		ax, 707h
	stosw
	lodsb
	and		al, 77h
	shl		al, 1
	inc		al
	mov		ah, al
	shr		al, 4
	and		ax, 707h
	stosw
	add	si, 14
	loop	loc_787C
	and		word [word_1FAC], 3
	mov		si, [word_6382]
	mov		ax, [word_6372]
	mov		di, ax
	and		di, 0Fh
	shr		ax, 4
	add		ax, [word_63BC]
	mov		es, ax
	mov		cx, [word_633A]
	sub		cx, [word_636E]
	mov		bx, dx
	cmp		word [word_6398], 0
	jz		loc_78CD
	jmp		loc_7A17

loc_78CD:
	pusha
	push	ds
	push	es
	mov		ds, [cs:word_5162]
	push	word [6352h]
	push	word [6354h]
	push	word [6356h]
	push	word [6358h]
	push	word [635Ah]
	push	word [635Ch]
	push	word [635Eh]
	push	word [6360h]
	push	word [6362h]
	push	word [6364h]
	push	word [6366h]
	push	word [6368h]
	push	word [636Ah]
	push	word [636Ch]
	push	word [636Eh]
	push	word [6370h]
	push	word [6372h]
	push	word [6374h]
	push	word [6376h]
	push	word [6378h]
	push	word [637Ah]
	push	word [637Ch]
	push	word [637Eh]
	push	word [6380h]
	push	word [6382h]
	push	word [6384h]
	push	word [6386h]
	push	word [6388h]
	push	word [638Ah]
	push	word [638Ch]
	push	word [638Eh]
	push	word [6390h]
	add		bx, [si + 4]
	jns		loc_795D
	mov		bx, 7FFFh

loc_795D:
	shr		bx, 10
	add		bx, [1FACh]
	mov		al, [bx + 1FAEh]
	mov		cx, [si]
	add		cx, 160
	mov		si, [si + 2]
	shl		si, 1
	mov		si, [si + 63C2h]
	and		si, si
	jz		loc_7980
	call	word [cs:off_7B6C]

loc_7980:
	mov		ds, [cs:word_5162]
	pop		word [6390h]
	pop		word [638Eh]
	pop		word [638Ch]
	pop		word [638Ah]
	pop		word [6388h]
	pop		word [6386h]
	pop		word [6384h]
	pop		word [6382h]
	pop		word [6380h]
	pop		word [637Eh]
	pop		word [637Ch]
	pop		word [637Ah]
	pop		word [6378h]
	pop		word [6376h]
	pop		word [6374h]
	pop		word [6372h]
	pop		word [6370h]
	pop		word [636Eh]
	pop		word [636Ch]
	pop		word [636Ah]
	pop		word [6368h]
	pop		word [6366h]
	pop		word [6364h]
	pop		word [6362h]
	pop		word [6360h]
	pop		word [635Eh]
	pop		word [635Ch]
	pop		word [635Ah]
	pop		word [6358h]
	pop		word [6356h]
	pop		word [6354h]
	pop		word [6352h]
	pop		es
	pop		ds
	popa
	add		si, 6
	add		di, 336
	loop	loc_7A13
	jmp		ret_7A16

loc_7A13:
	jmp		loc_78CD

ret_7A16:
	ret


loc_7A17:
	pusha
	push	ds
	push	es
	mov		ds, [cs:word_5162]
	push	word [6352h]
	push	word [6354h]
	push	word [6356h]
	push	word [6358h]
	push	word [635Ah]
	push	word [635Ch]
	push	word [635Eh]
	push	word [6360h]
	push	word [6362h]
	push	word [6364h]
	push	word [6366h]
	push	word [6368h]
	push	word [636Ah]
	push	word [636Ch]
	push	word [636Eh]
	push	word [6370h]
	push	word [6372h]
	push	word [6374h]
	push	word [6376h]
	push	word [6378h]
	push	word [637Ah]
	push	word [637Ch]
	push	word [637Eh]
	push	word [6380h]
	push	word [6382h]
	push	word [6384h]
	push	word [6386h]
	push	word [6388h]
	push	word [638Ah]
	push	word [638Ch]
	push	word [638Eh]
	push	word [6390h]
	add		bx, [si + 4]
	jns		loc_7AA7
	mov		bx, 7FFFh

loc_7AA7:
	shr		bx, 10
	mov		ax, bx
	cmp		al, 8
	jb		loc_7AB2
	mov		al, 8

loc_7AB2:
	shl		al, 3
	add		bx, [1FACh]
	add		al, [bx + 1FAEh]
	mov		cx, [si]
	add		cx, 160
	mov		si, [si + 2]
	shl		si, 1
	mov		si, [si + 63C2h]
	and		si, si
	jz		loc_7AD5
	call	word [cs:off_7B6C]

loc_7AD5:
	mov		ds, [cs:word_5162]
	pop		word [6390h]
	pop		word [638Eh]
	pop		word [638Ch]
	pop		word [638Ah]
	pop		word [6388h]
	pop		word [6386h]
	pop		word [6384h]
	pop		word [6382h]
	pop		word [6380h]
	pop		word [637Eh]
	pop		word [637Ch]
	pop		word [637Ah]
	pop		word [6378h]
	pop		word [6376h]
	pop		word [6374h]
	pop		word [6372h]
	pop		word [6370h]
	pop		word [636Eh]
	pop		word [636Ch]
	pop		word [636Ah]
	pop		word [6368h]
	pop		word [6366h]
	pop		word [6364h]
	pop		word [6362h]
	pop		word [6360h]
	pop		word [635Eh]
	pop		word [635Ch]
	pop		word [635Ah]
	pop		word [6358h]
	pop		word [6356h]
	pop		word [6354h]
	pop		word [6352h]
	pop		es
	pop		ds
	popa
	add		si, 6
	add		di, 336
	loop	loc_7B68
	jmp		ret_7B6B

loc_7B68:
	jmp		loc_7A17

ret_7B6B:
	ret


off_7B6C:	dw sub_7B72
off_7B6E:	dw sub_7B88
off_7B70:	dw sub_7F6E


;
;
;
sub_7B72:
	push	bx
	mov		bx, [cs:word_D379]
	mov		bx, [cs:bx + off_7B6E]
	mov		[cs:off_7B6C], bx
	pop		bx
	jmp		word [cs:off_7B6C]


;
;
;
sub_7B88:
	mov		bx, 2C26h
	xlatb
	mov		dh, al
	mov		ds, [word_6330]
	mov		bl, 0FEh
	mov		bh, dh
	shl		bx, 2
	mov		ax, [bx]
	mov		bp, 140h
	cmp		cx, bp
	jge		loc_7BE8
	jae		loc_7BBF
	sub		bp, cx
	shr		cx, 1
	jcxz	loc_7BAC
	rep stosw

loc_7BAC:
	jae		loc_7BAF
	stosb

loc_7BAF:
	mov		cx, [si]
	add		si, 2
	cmp		cx, bp
	jae		loc_7C22
	sub		bp, cx
	call	sub_7C24
	jmp		loc_7BD3

loc_7BBF:
	neg		cx
	mov		bx, cx
	mov		cx, [si]
	add		si, 2
	sub		cx, bx
	jbe		loc_7BE8
	sub		bp, cx
	jbe		loc_7BEE
	call	sub_7BF1

loc_7BD3:
	mov		bl, 0FFh
	mov		bh, dh
	shl		bx, 2
	mov		ax, [bx]
	mov		cx, bp
	shr		cx, 1
	jae		loc_7BE3
	stosb

loc_7BE3:
	jcxz	ret_7BE7
	rep stosw

ret_7BE7:
	ret

loc_7BE8:
	mov		cx, 160
	rep stosw
	ret

loc_7BEE:
	mov		cx, 320


;
;
;
sub_7BF1:
	mov		ax, bx
	shr		ax, 2
	add		si, ax
	and		bx, 3
	jz		sub_7C24
	neg		bx
	add		bx, 4
	sub		cx, bx
	push	cx
	mov		cx, bx
	mov		bx, si
	mov		ax, dx
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	add		si, 4
	sub		si, cx
	rep movsb
	pop		cx
	and		cx, cx
	jg		loc_7C28
	add		di, cx
	ret


loc_7C22:
	mov		cx, bp


;
;
;
sub_7C24:
	mov		bx, si
	mov		ax, dx

loc_7C28:
	mov		si, 7F5Ch
	mov		dx, cx
	and		dx, 0FFFCh
	sub		si, dx
	sub		si, dx
	shr		dx, 1
	sub		si, dx
	jmp		si


;
;
;
sub_7C3A:
	xchg	bx, bx
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsw
	movsw
	and		cx, 3
	je		loc_7F6B
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	rep movsb

loc_7F6B:
	mov		dx, ax
	ret


;
;
;
sub_7F6E:
	mov		bx, 2C26h
	xlatb
	mov		dh, al
	mov		ds, [word_6330]
	mov		bl, 254
	mov		bh, dh
	shl		bx, 2
	mov		eax, [bx]
	mov		bp, 320
	cmp		cx, bp
	jge		loc_7FE2
	jae		loc_7FB0
	sub		bp, cx
	mov		bx, cx
	shr		cx, 2
	jcxz	loc_7F97
	rep stosd

loc_7F97:
	mov		cx, bx
	and		cx, 3
	jz		loc_7FA0
	rep stosb

loc_7FA0:
	mov		cx, [si]
	add		si, 2
	cmp		cx, bp
	jae		loc_801D
	sub		bp, cx

loc_7FAB:
	call	sub_801F
	jmp		loc_7FC4

loc_7FB0:
	neg		cx
	mov		bx, cx
	mov		cx, [si]
	add		si, 2
	sub		cx, bx
	jbe		loc_7FE2
	sub		bp, cx
	jbe		loc_7FE9
	call	sub_7FEC

loc_7FC4:
	mov		bl, 0FFh
	mov		bh, dh
	shl		bx, 2
	mov		eax, [bx]
	mov		cx, bp
	and		cx, 3
	jz		loc_7FD7
	rep stosb

loc_7FD7:
	add		cx, bp
	jz		ret_7FE1
	shr		cx, 2
	rep stosd

ret_7FE1:
	ret

loc_7FE2:
	mov		cx, 80
	rep stosd
	ret

loc_7FE9:
	mov		cx, 320


;
;
;
sub_7FEC:
	mov		ax, bx
	shr		ax, 2
	add		si, ax
	and		bx, 3
	jz		sub_801F
	neg		bx
	add		bx, 4
	sub		cx, bx

loc_7FFF:
	push	cx

loc_8000:
	mov		cx, bx
	mov		bx, si
	mov		ax, dx
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	add		si, 4
	sub		si, cx
	rep movsb
	pop		cx
	and		cx, cx
	jg		loc_8023
	add		di, cx
	ret

loc_801D:
	mov		cx, bp

sub_801F:
	mov		bx, si
	mov		ax, dx

loc_8023:
	mov		si, 8358h
	mov		dx, cx
	and		dx, 0FFFCh
	sub		si, dx
	sub		si, dx
	shr		dx, 1
	sub		si, dx
	jmp		si


;
;
;
unk_8035:
	xchg	bx, bx
	nop
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	movsd
	and		cx, 3
	je		loc_8367
	mov		al, [bx]
	inc		bx
	mov		si, ax
	shl		si, 2
	rep movsb

loc_8367:
	mov		dx, ax
	ret


;
; Draws background and the sky.
;
p1_draw_background:						; 836A
	mov		si, word_3F3A
	mov		di, 550h
	call	sub_8388
	call	sub_83E7
	jmp		loc_8504


;
; P2: Draws background and the sky.
;
p2_draw_background:						; 8379
	mov		si, word_4034
	mov		di, 550h
	call	sub_8388
	call	sub_83E7
	jmp		loc_8504


;
;
;
sub_8388:
	push	si
	push	di
	mov		ax, [si + 156]
	and		ax, ax
	jz		loc_83A0
	mov		dx, ax
	mov		si, 0
	mov		es, [word_2AFC]
	call	word [cs:off_83A3]

loc_83A0:
	pop		di
	pop		si
	ret


off_83A3:	dw sub_83A9
off_83A5:	dw sub_83BF
off_83A7:	dw sub_83D2


sub_83A9:
	push	bx
	mov		bx, [cs:word_D379]
	mov		bx, [cs:bx - 7C5Bh]
	mov		[cs:off_83A3], bx
	pop		bx
	jmp		word [cs:off_83A3]


;
;
;
sub_83BF:
	mov		ax, [es:si]
	mov		es, [word_63BC]

loc_83C6:
	mov		cx, 160
	rep stosw
	add		di, 16
	dec		dx
	jnz		loc_83C6
	ret


;
;
;
sub_83D2:
	mov		eax, [es:si]
	mov		es, [word_63BC]

loc_83DA:
	mov		cx, 80
	rep stosd
	add		di, 16
	dec		dx
	jnz		loc_83DA
	ret


;
;
;
sub_83E7:
	push	si
	push	di
	cmp		word [si + 148], 0
	jz		loc_8458
	mov		bp, [word_249E]
	shl		bp, 5
	mov		ax, [si + 142]
	shl		ax, 3
	sar		ax, 3
	cwd
	add		ax, bp
	adc		dx, 0
	add		ax, bp
	adc		dx, 0
	add		ax, bp
	adc		dx, 0
	add		ax, bp
	adc		dx, 0
	div		bp
	mov		ax, 128
	mul		dx
	idiv	word [word_249E]
	and		ax, 0FFFh
	mov		dx, 10240
	mul		dx
	mov		bx, dx
	mov		ax, [si + 150]
	mov		bp, 640
	mul		bp
	add		ax, bx
	mov		cx, ax
	mov		ax, [si + 146]
	mov		bp, 336
	mul		bp
	add		di, ax
	push	ds
	mov		dx, [si + 148]
	mov		es, [word_63BC]
	mov		ds, [word_2AFC]
	mov		si, cx
	call	word [cs:off_845B]
	pop		ds

loc_8458:
	pop		di
	pop		si
	ret


off_845B:	dw sub_8461
off_845D:	dw sub_8477
off_845F:	dw sub_84B4


sub_8461:
	push	bx
	mov		bx, [cs:word_D379]
	mov		bx, [cs:bx - 7BA3h]
	mov		[cs:off_845B], bx
	pop		bx
	jmp		word [cs:off_845B]


;
;
;
sub_8477:
	push	si
	cmp		bx, 320
	jbe		loc_84A3
	mov		cx, 640
	sub		cx, bx
	mov		ax, cx
	shr		cx, 1
	jcxz	loc_848B
	rep movsw

loc_848B:
	jae		loc_848E
	movsb

loc_848E:
	sub		si, 640
	mov		cx, bx
	sub		cx, 320
	shr		cx, 1
	jae		loc_849D
	movsb

loc_849D:
	jcxz	loc_84A8
	rep movsw
	jmp		loc_84A8

loc_84A3:
	mov		cx, 160
	rep movsw

loc_84A8:
	pop		si
	add		si, 640
	add		di, 16
	dec		dx
	jnz		sub_8477
	ret


;
;
;
sub_84B4:
	push	si
	cmp		bx, 320
	jbe		loc_84F2
	mov		cx, 640
	sub		cx, bx
	mov		ax, cx
	shr		cx, 2
	jcxz	loc_84CA
	rep movsd

loc_84CA:
	and		ax, 3
	jz		loc_84D3
	mov		cx, ax
	rep movsb

loc_84D3:
	sub		si, 640
	mov		cx, bx
	sub		cx, 320
	mov		ax, cx
	and		cx, 3
	jz		loc_84E6
	rep movsb

loc_84E6:
	shr		ax, 2
	mov		cx, ax
	jcxz	loc_84F8
	rep movsd
	jmp		loc_84F8

loc_84F2:
	mov		cx, 80
	rep movsd

loc_84F8:
	pop		si
	add		si, 640
	add		di, 16
	dec		dx
	jnz		sub_84B4
	ret


;
;
;
loc_8504:
	push	si
	push	di
	cmp		word [si + 154], 0
	jz		loc_8539
	mov		ax, 336
	mul		word [si + 152]
	add		di, ax
	mov		dx, [si + 154]
	mov		es, [word_6330]
	mov		ah, [byte_2C26]
	cmp		word [word_6398], 0
	jz		loc_852D
	mov		ah, [byte_2C66]

loc_852D:
	mov		al, 0
	mov		si, ax
	shl		si, 2
	call	word [cs:off_83A3]

loc_8539:
	pop		di
	pop		si
	ret


;
; P2: Draws objects.
;
sub_853C:
	jmp		sub_853E


;
; Draws objects: car, opponents, trees, obstacles.
;
sub_853E:
	mov		word [word_1FD2], 0FFFFh
	mov		word [word_1FD4], 0FFFFh
	mov		word [word_1FD6], 0FFFFh
	mov		word [word_1FDC], 0
	mov		byte [byte_1F9F], 0
	mov		si, [word_3ED8]
	mov		ax, [si + 132]
	mov		[word_1FDE], ax
	mov		ax, [si + 134]
	mov		[word_1FE0], ax
	mov		dx, [word_4306]
	mov		ax, [word_4308]
	mov		[word_1FE2], dx
	mov		[word_1FE4], ax
	sub		ax, [si + 134]
	sbb		dx, [si + 132]
	mov		bx, dx

loc_8585:
	add		bx, [word_23F2]
	js		loc_8585
	mov		dl, [bx + arr_7856]
	mov		dh, 0
	mov		[word_1FE6], dx
	mov		[word_1FE8], ax
	mov		bx, [si + 132]
	mov		di, arr_2010
	push	ds
	pop		es
	cmp		word [is_circular_track], 0
	jz		loc_85AE
	mov		bl, [bx + arr_7856]
	mov		bh, 0

loc_85AE:
	shl		bx, 4
	lea		si, [bx - 7EA8h]
	mov		cx, 10

loc_85B8:
	movsw
	movsw
	movsw
	movsw
	add		si, 8
	loop	loc_85B8
	mov		dx, 9
	mov		ax, 0
	mov		di, [word_3ED8]
	sub		ax, [di + 134]
	sbb		dx, 0
	shl		ax, 1
	rcl		dx, 1
	shl		ax, 1
	rcl		dx, 1
	shl		ax, 1
	rcl		dx, 1
	shl		ax, 1
	rcl		dx, 1
	mov		[word_1FEC], ax
	mov		bx, dx
	mov		di, 2058h
	mov		ax, bx
	and		ax, 3
	or		ax, 7Ch
	mov		[word_1FEE], ax
	sub		bx, ax
	shr		bx, 1
	sub		di, bx
	mov		[word_637A], di
	sub		di, 64
	mov		[word_1FEA], di
	mov		word [word_1FF2], 8
	cmp		word [word_63A6], 0
	jnz		loc_8619
	mov		word [word_1FF2], 0

loc_8619:
	mov		ax, [word_3C74]
	inc		ax
	mov		[word_1FFC], ax
	mov		word [word_2006], 2
	mov		word [word_2060], 0FFFFh
	cmp		word [word_6396], 0
	jnz		loc_8636
	jmp		loc_86D6

loc_8636:
	mov		di, [word_3ED8]
	mov		ax, [di + 240]
	shr		ax, 8
	mov		[word_2060], ax
	mov		word [word_23A0], 0
	mov		si, [word_637A]
	sub		si, 64
	mov		word [word_636E], 20h
	mov		bp, [word_1FEE]
	and		bp, 3
	sub		bp, 4
	shl		bp, 1
	cmp		word [di + 120], 0
	jz		loc_866E
	mov		cx, 0
	jmp		loc_869E

loc_866E:
	lodsw
	cmp		al, 0FCh
	jne		loc_8693
	and		bp, bp
	js		loc_868B
	mov		di, bp
	mov		cx, [di + arr_68C2]
	sar		cx, 5
	shl		di, 2
	sub		cx, [di - 3A96h]
	neg		cx
	jns		loc_868E

loc_868B:
	mov		cx, 0

loc_868E:
	mov		[si - 1], cl
	jmp		loc_86A8

loc_8693:
	add		bp, 8
	dec		word [word_636E]
	jnz		loc_866E
	jmp		loc_86CB

loc_869E:
	lodsw
	cmp		al, 0FDh
	jne		loc_86A8
	mov		[si - 1], cl
	jmp		loc_8693

loc_86A8:
	add		bp, 8
	dec		word [word_636E]
	jnz		loc_869E
	add		bp, 4
	mov		[word_636A], bp
	mov		[word_2062], cx
	mov		ah, 0FDh
	mov		al, cl
	mov		[word_1FF0], ax
	mov		word [word_23A0], 1
	jmp		loc_86D9

loc_86CB:
	add		bp, 4
	mov		[word_636A], bp
	mov		[word_2062], cx

loc_86D6:
	call	sub_8B79

loc_86D9:
	mov		si, 4306h
	call	sub_8BA8
	call	sub_8DBC
	mov		bx, [word_3ED8]
	mov		di, [bx + 132]
	mov		[word_6378], di
	mov		di, [bx + 134]
	call	sub_8CDC
	mov		di, struct_2066
	call	sub_8C63
	mov		word [word_2064], 0FFFEh
	cmp		word [word_639A], 0
	jz		loc_870E
	mov		word [word_2064], 60h

loc_870E:
	mov		ax, [word_1FEE]
	mov		bx, [word_1FFE]
	mov		cx, [word_2008]
	mov		bp, ax
	and		bp, bx
	and		bp, cx
	inc		bp
	jnz		loc_8725
	jmp		loc_87E2

loc_8725:
	cmp		bx, ax
	jg		loc_872F
	cmp		ax, cx
	jge		loc_8735
	jmp		loc_87A8

loc_872F:
	cmp		bx, cx
	jge		loc_876E
	jmp		loc_87A8

loc_8735:
	cmp		ax, [word_2064]
	jge		loc_8740
	call	sub_A58B
	jmp		loc_8735

loc_8740:
	cmp		ax, [word_2060]
	jg		loc_8749
	call	loc_9342

loc_8749:
	cmp		ax, [word_1FF4]
	jg		loc_875A
	push	ax
	push	bx
	push	cx
	call	sub_93A7
	pop		cx
	pop		bx
	pop		ax
	jmp		loc_8749

loc_875A:
	push	si
	push	di
	push	word [word_637A]
	call	sub_94B9
	pop		word [word_637A]
	pop		di
	pop		si
	call	sub_8B79
	jmp		loc_870E

loc_876E:
	cmp		bx, [word_2064]
	jge		loc_8779
	call	sub_A58B
	jmp		loc_876E

loc_8779:
	cmp		bx, [word_2060]
	jg		loc_8782
	call	loc_9342

loc_8782:
	cmp		bx, [word_1FF4]
	jg		loc_8793
	push	ax
	push	bx
	push	cx
	call	sub_93A7
	pop		cx
	pop		bx
	pop		ax
	jmp		loc_8782

loc_8793:
	push	si
	push	di
	push	word [word_637A]
	call	sub_93FB
	pop		word [word_637A]
	pop		di
	pop		si
	call	sub_8BA8
	jmp		loc_870E

loc_87A8:
	cmp		cx, [word_2064]
	jge		loc_87B3
	call	sub_A58B
	jmp		loc_87A8

loc_87B3:
	cmp		cx, [word_2060]
	jg		loc_87BC
	call	loc_9342

loc_87BC:
	cmp		cx, [word_1FF4]
	jg		loc_87CD
	push	ax
	push	bx
	push	cx
	call	sub_93A7
	pop		cx
	pop		bx
	pop		ax
	jmp		loc_87BC

loc_87CD:
	push	si
	push	di
	push	word [word_637A]
	call	sub_942B
	pop		word [word_637A]
	pop		di
	pop		si
	call	sub_8C63
	jmp		loc_870E

loc_87E2:
	call	sub_A58B
	cmp		word [word_2064], 0
	jge		loc_87E2
	cmp		word [word_2110], 0
	jge		loc_87F6
	jmp		loc_8B75

loc_87F6:
	mov		si, [word_3ED8]
	cmp		word [si + 26], 0
	jz		loc_8803
	jmp		loc_8884

loc_8803:
	cmp		word [si + 228], 0
	jnz		loc_8884
	mov		bp, [si + 242]
	shr		bp, 0Bh
	dec		bp
	js		loc_8884
	mov		bx, [word_2214]
	add		bx, 32
	shr		bx, 3
	add		bp, bx
	add		bp, bx
	add		bp, bx
	add		bp, 63
	mov		[word_636E], bp
	mov		word [word_637A], 0
	mov		bx, [word_220C]
	add		bx, [word_220E]
	shr		bx, 1
	sub		bx, 160
	mov		cx, [word_2212]
	mov		di, [word_2E7C]
	mov		word [word_2114], 0
	push	ax
	push	bx
	push	cx
	push	dx
	push	word [word_6362]
	push	word [word_6366]
	push	word [word_636A]
	push	word [word_636E]
	push	si
	push	di
	push	word [word_637A]
	call	sub_9CC5
	pop		word [word_637A]
	pop		di
	pop		si
	pop		word [word_636E]
	pop		word [word_636A]
	pop		word [word_6366]
	pop		word [word_6362]
	pop		dx
	pop		cx
	pop		bx
	pop		ax

loc_8884:
	cmp		word [word_2110], 0
	jz		loc_888E
	jmp		loc_8B75

loc_888E:
	mov		bp, [si + 172]
	mov		[word_636E], bp
	and		bp, bp
	jz		loc_88FF
	mov		bp, [word_3EE0]
	shr		bp, 2
	and		bp, 3
	xor		bp, 3
	mov		bx, 0FFD2h
	cmp		word [si + 170], 0
	js		loc_88B6
	add		bp, 4
	neg		bx

loc_88B6:
	mov		[word_636E], bp
	add		bx, [si + 128]
	mov		ax, 0
	mov		cx, 0
	mov		dx, [si + 122]
	mov		[word_21FC], dx
	mov		dx, [si + 128]
	mov		[word_2202], dx
	mov		dx, [si + 124]
	mov		[word_21FE], dx
	mov		dx, [si + 126]
	mov		[word_2200], dx
	mov		word [word_637A], 0
	mov		di, [word_2D7C]
	mov		dx, 1400h
	mov		word [word_2208], 0FFFFh
	mov		word [word_2114], 0
	push	si
	call	sub_9A1E
	pop		si

loc_88FF:
	mov		word [word_637A], 0
	mov		word [word_637C], 0
	cmp		word [si + 26], 0
	jz		loc_8914
	jmp		loc_89DF

loc_8914:
	mov		bp, [si + 192]
	mov		[word_636E], bp
	and		bp, bp
	jnz		loc_8923
	jmp		loc_89DF

loc_8923:
	shr		bp, 2
	mov		[word_636E], bp
	cmp		word [si + 194], 0
	jg		loc_8982
	mov		bx, 0FFD1h
	mov		cx, [word_633A]
	sub		cx, 3
	mov		di, [word_2D80]
	mov		word [word_2114], 0
	mov		word [word_2208], 0FFFFh
	push	ax
	push	bx
	push	cx
	push	dx
	push	word [word_6362]
	push	word [word_6366]
	push	word [word_636A]
	push	word [word_636E]
	push	si
	push	di
	push	word [word_637A]
	call	sub_9CC5
	pop		word [word_637A]
	pop		di
	pop		si
	pop		word [word_636E]
	pop		word [word_636A]
	pop		word [word_6366]
	pop		word [word_6362]
	pop		dx
	pop		cx
	pop		bx
	pop		ax

loc_8982:
	cmp		word [si + 194], 0
	js		loc_89DF
	add		word [word_636E], 5
	mov		bx, 2Fh
	mov		cx, [word_633A]
	sub		cx, 3
	mov		di, [word_2D80]
	mov		word [word_2114], 0
	mov		word [word_2208], 0FFFFh
	push	ax
	push	bx
	push	cx
	push	dx
	push	word [word_6362]
	push	word [word_6366]
	push	word [word_636A]
	push	word [word_636E]
	push	si
	push	di
	push	word [word_637A]
	call	sub_9CC5
	pop		word [word_637A]
	pop		di
	pop		si
	pop		word [word_636E]
	pop		word [word_636A]
	pop		word [word_6366]
	pop		word [word_6362]
	pop		dx
	pop		cx
	pop		bx
	pop		ax

loc_89DF:
	cmp		word [si + 192], 0
	jz		loc_89E9
	jmp		loc_8A7F

loc_89E9:
	cmp		word [si + 26], 0
	jz		loc_89F2
	jmp		loc_8A7F

loc_89F2:
	cmp		word [si + 14], 0C00h
	jns		loc_89FC
	jmp		loc_8A7F

loc_89FC:
	mov		di, [word_2D90]
	cmp		word [word_63AA], 0
	jnz		loc_8A1D
	mov		di, [word_2DEE]
	cmp		word [word_63A4], 0
	jnz		loc_8A1D
	mov		di, [word_2DDE]
	cmp		word [word_63A2], 0
	jz		loc_8A7F

loc_8A1D:
	mov		ax, [word_3EE6]
	shr		ax, 2
	cwd
	mov		bp, 3
	div		bp
	mov		[word_636E], dx
	mov		bx, [si + 16]
	neg		bx
	sar		bx, 2
	mov		cx, [word_633A]
	sub		cx, 2
	mov		word [word_2114], 0
	mov		word [word_2208], 0FFFFh
	push	ax
	push	bx
	push	cx
	push	dx
	push	word [word_6362]
	push	word [word_6366]
	push	word [word_636A]
	push	word [word_636E]
	push	si
	push	di
	push	word [word_637A]
	call	sub_9CC5
	pop		word [word_637A]
	pop		di
	pop		si
	pop		word [word_636E]
	pop		word [word_636A]
	pop		word [word_6366]
	pop		word [word_6362]
	pop		dx
	pop		cx
	pop		bx
	pop		ax

loc_8A7F:
	cmp		word [si + 14], 0
	jnz		loc_8A88
	jmp		loc_8B75

loc_8A88:
	cmp		word [si + 196], 0
	jnz		loc_8A92
	jmp		loc_8B75

loc_8A92:
	cmp		word [si + 26], 0
	jz		loc_8A9B
	jmp		loc_8B75

loc_8A9B:
	cmp		word [si + 202], 0
	jz		loc_8AA5
	jmp		loc_8B75

loc_8AA5:
	cmp		word [word_63AA], 0
	jz		loc_8AAF
	jmp		loc_8B75

loc_8AAF:
	cmp		word [word_63AE], 0
	jz		loc_8AB9
	jmp		loc_8B75

loc_8AB9:
	cmp		word [word_63A4], 0
	jz		loc_8AC3
	jmp		loc_8B75

loc_8AC3:
	cmp		word [word_63A2], 0
	jz		loc_8ACD
	jmp		loc_8B75

loc_8ACD:
	mov		ax, [word_3EE6]
	shr		ax, 2
	and		ax, 3
	mov		[word_636E], ax
	mov		bx, 36
	mov		cx, [word_633A]
	sub		cx, 2
	mov		di, [word_2D7E]
	mov		word [word_2114], 0
	mov		word [word_2208], 0FFFFh
	push	ax
	push	bx
	push	cx
	push	dx
	push	word [word_6362]
	push	word [word_6366]
	push	word [word_636A]
	push	word [word_636E]
	push	si
	push	di
	push	word [word_637A]
	call	sub_9CC5
	pop		word [word_637A]
	pop		di
	pop		si
	pop		word [word_636E]
	pop		word [word_636A]
	pop		word [word_6366]
	pop		word [word_6362]
	pop		dx
	pop		cx
	pop		bx
	pop		ax
	add		word [word_636E], 4
	mov		bx, 0FFDCh
	mov		word [word_2114], 0
	mov		word [word_2208], 0FFFFh
	push	ax
	push	bx
	push	cx
	push	dx
	push	word [word_6362]
	push	word [word_6366]
	push	word [word_636A]
	push	word [word_636E]
	push	si
	push	di
	push	word [word_637A]
	call	sub_9CC5
	pop		word [word_637A]
	pop		di
	pop		si
	pop		word [word_636E]
	pop		word [word_636A]
	pop		word [word_6366]
	pop		word [word_6362]
	pop		dx
	pop		cx
	pop		bx
	pop		ax

loc_8B75:
	call	sub_7633
	ret


;
;
;
sub_8B79:
	xchg	si, [word_637A]

loc_8B7D:
	sub		word [word_1FEE], 4
	js		loc_8B9D
	sub		si, 2
	mov		ax, [si]
	xchg	al, ah
	mov		[word_1FF0], ax
	and		ax, 0FF00h
	jz		loc_8B7D
	cmp		ah, 0FFh
	jz		loc_8B7D
	xchg	si, [word_637A]
	ret

loc_8B9D:
	xchg	si, [word_637A]
	mov		word [word_1FEE], 0FFFFh
	ret


;
;
;
sub_8BA8:
	cmp		word [is_circular_track], 0
	jnz		loc_8BF4

loc_8BAF:
	dec		word [word_1FFC]
	js		loc_8BED
	mov		ax, [si + 4]
	mov		[word_2002], ax
	mov		ax, [si + 6]
	mov		[word_2004], ax
	lodsw
	mov		bp, ax
	lodsw
	add		si, 4
	sub		ax, [word_1FE0]
	sbb		bp, [word_1FDE]
	cmp		bp, 8
	jae		loc_8BAF
	shl		ax, 1
	rcl		bp, 1
	shl		ax, 1
	rcl		bp, 1
	shl		ax, 1
	rcl		bp, 1
	shl		ax, 1
	rcl		bp, 1
	mov		[word_2000], ax
	mov		[word_1FFE], bp
	ret

loc_8BED:
	mov		word [word_1FFE], 0FFFFh
	ret

loc_8BF4:
	dec		word [word_1FFC]
	js		loc_8C5C
	mov		ax, [si + 4]
	mov		[word_2002], ax
	mov		ax, [si + 6]
	mov		[word_2004], ax
	lodsw
	mov		bp, ax
	lodsw
	add		si, 4
	sub		ax, [word_1FE4]
	sbb		bp, [word_1FE2]
	add		[word_1FE4], ax
	adc		[word_1FE2], bp
	add		ax, [word_1FE8]
	adc		bp, [word_1FE6]
	jns		loc_8C2B
	add		bp, [word_23F2]

loc_8C2B:
	mov		[word_1FE6], bp
	mov		[word_1FE8], ax
	cmp		bp, 8
	jae		loc_8C55
	shl		ax, 1
	rcl		bp, 1
	shl		ax, 1
	rcl		bp, 1
	shl		ax, 1
	rcl		bp, 1
	shl		ax, 1
	rcl		bp, 1
	mov		[word_2000], ax
	mov		[word_1FFE], bp
	mov		word [word_1FDC], 1
	ret

loc_8C55:
	cmp		word [word_1FDC], 0
	jz		loc_8BF4

loc_8C5C:
	mov		word [word_1FFE], 0FFFFh
	ret


;
;
;
sub_8C63:
	cmp		word [is_circular_track], 0
	jnz		loc_8CAB

loc_8C6A:
	dec		word [word_2006]
	js		loc_8CD5
	mov		ax, [di + 4]
	mov		[word_200C], ax
	mov		ax, [di + 6]
	mov		[word_200E], ax
	mov		bp, [di]
	mov		ax, [di + 2]
	add		di, 8
	sub		ax, [word_1FE0]
	sbb		bp, [word_1FDE]
	js		loc_8CD5
	cmp		bp, 8
	jae		loc_8C6A

loc_8C93:
	shl		ax, 1
	rcl		bp, 1
	shl		ax, 1
	rcl		bp, 1
	shl		ax, 1
	rcl		bp, 1
	shl		ax, 1
	rcl		bp, 1
	mov		[word_200A], ax
	mov		[word_2008], bp
	ret

loc_8CAB:
	dec		word [word_2006]
	js		loc_8CD5
	mov		ax, [di + 4]
	mov		[word_200C], ax
	mov		ax, [di + 6]
	mov		[word_200E], ax
	mov		bp, [di]
	mov		ax, [di + 2]
	add		di, 8
	cmp		ax, 0FFFFh
	jnz		loc_8CCE
	cmp		bp, ax
	jz		loc_8CAB

loc_8CCE:
	cmp		bp, 8
	jae		loc_8CAB
	jmp		loc_8C93

loc_8CD5:
	mov		word [word_2008], 0FFFFh
	ret


;
;
;
sub_8CDC:
	cmp		word [is_circular_track], 0
	jz		loc_8D07
	mov		ax, [word_40B0]
	mov		[word_6354], ax
	mov		ax, [word_40B2]
	call	sub_8D85
	mov		cx, [word_6354]
	mov		[word_635C], cx
	mov		cx, ax
	mov		ax, [word_3FB6]
	mov		[word_6354], ax
	mov		ax, [word_3FB8]
	call	sub_8D85
	jmp		loc_8D1C

loc_8D07:
	mov		ax, [word_3FB6]
	mov		[word_6354], ax
	mov		ax, [word_3FB8]
	mov		cx, [word_40B0]
	mov		[word_635C], cx
	mov		cx, [word_40B2]

loc_8D1C:
	mov		bx, [word_3FBA]
	mov		[word_6358], bx
	mov		bx, [word_3FBC]
	mov		dx, [word_40B4]
	mov		[word_6360], dx
	mov		dx, [word_40B6]
	cmp		cx, ax
	mov		bp, [word_635C]
	sbb		bp, [word_6354]
	jb		loc_8D5B
	xchg	ax, cx
	mov		bp, [word_6354]
	xchg	bp, [word_635C]
	mov		[word_6354], bp
	xchg	bx, dx
	mov		bp, [word_6358]
	xchg	bp, [word_6360]
	mov		[word_6358], bp

loc_8D5B:
	mov		di, struct_2066
	mov		[di + 2], ax
	mov		ax, [word_6354]
	mov		[di], ax
	mov		[di + 6], bx
	mov		bx, [word_6358]
	mov		[di + 4], bx
	mov		[di + 10], cx
	mov		cx, [word_635C]
	mov		[di + 8], cx
	mov		[di + 14], dx
	mov		dx, [word_6360]
	mov		[di + 12], dx
	ret


;
;
;
sub_8D85:
	cmp		word [word_6354], 0
	jz		loc_8DB5
	sub		ax, di
	mov		bp, [word_6378]
	sbb		[word_6354], bp
	xchg	ax, [word_6354]
	and		ax, ax
	jns		loc_8DA6

loc_8D9E:
	add		ax, [word_23F2]
	js		loc_8D9E
	jmp		loc_8DB0

loc_8DA6:
	sub		ax, [word_23F2]
	jns		loc_8DA6
	add		ax, [word_23F2]

loc_8DB0:
	xchg	ax, [word_6354]
	ret

loc_8DB5:
	mov		ax, 0FFFFh
	mov		[word_6354], ax
	ret


;
;
;
sub_8DBC:
	dec		word [word_1FF2]
	js		loc_8E07
	push	si
	mov		si, [word_1FF2]
	shl		si, 3
	add		si, 412Eh
	mov		ax, [si + 4]
	mov		[word_1FF8], ax
	mov		ax, [si + 6]
	mov		[word_1FFA], ax
	lodsw
	mov		bp, ax
	lodsw
	pop		si
	sub		ax, [word_1FE0]
	sbb		bp, [word_1FDE]
	and		bp, 3Fh
	cmp		bp, 8
	jae		sub_8DBC
	shl		ax, 1
	rcl		bp, 1
	shl		ax, 1
	rcl		bp, 1
	shl		ax, 1
	rcl		bp, 1
	shl		ax, 1
	rcl		bp, 1
	mov		[word_1FF6], ax
	mov		[word_1FF4], bp
	ret

loc_8E07:
	mov		word [word_1FF4], 0FFFFh
	ret


;
; P2: Draws PAUSED, DEMO, RACE COMPLETED, TURBO ZONE, etc.
;
sub_8E0E:
	jmp     draw_race_text


;
; Draws PAUSED, DEMO, RACE COMPLETED, TURBO ZONE, etc.
;
draw_race_text:
	mov		si, [word_3ED8]
	cmp		word [is_paused], 0
	jz		loc_8E21
	mov		di, paused_txt
	jmp		print_text

loc_8E21:
	cmp		word [playing_demo], 0
	jz		loc_8E37
	mov		di, demo_txt
	test	word [word_3EE6], 16
	jz		ret_8E36
	jmp		print_text

ret_8E36:
	ret

loc_8E37:
	cmp		word [si + 26], 0
	jz		loc_8E6D
	mov		di, race_completed_txt
	cmp		word [si + 26], 2
	jne		loc_8E49
	jmp		print_text

loc_8E49:
	cmp		word [word_3EE4], 0
	jnz		loc_8E5E
	cmp		word [si + 32], 0
	jz		loc_8E59
	jmp		print_text

loc_8E59:
	mov		di, out_of_time_txt
	jmp		print_text

loc_8E5E:
	mov		di, race_over_txt
	cmp		word [si + 222], 0
	jnz		print_text
	mov		di, out_of_fuel_txt
	jmp		print_text

loc_8E6D:
	cmp		word [si + 188], 0
	jz		loc_8E79
	mov		di, turbo_zone_txt
	jmp		print_text

loc_8E79:
	cmp		word [si + 168], 0
	jz		loc_8E8C
	mov		di, checkpoint_txt
	test	word [si + 168], 8
	jne		print_text
	ret

loc_8E8C:
	cmp		word [si + 222], 5C00h
	jae		loc_8EA0
	mov		di, low_fuel_txt
	test	word [word_3EE6], 16
	je		print_text
	ret

loc_8EA0:
	cmp		word [num_of_players], 0
	jz		ret_8ED6
	mov		di, word_4034
	mov		bp, p2_name
	cmp		si, di
	jnz		loc_8EB7
	mov		di, word_3F3A
	mov		bp, p1_name

loc_8EB7:
	mov		ax, [di + 2]
	sub		ax, [si + 2]
	mov		ax, [di]
	sbb		ax, [si]
	cmp		ax, 4
	jae		ret_8ED6
	mov		si, bp
	mov		di, ahead_txt
	push	di
	push	ds
	pop		es
	mov		cx, 6
	rep movsw
	pop		di
	jmp		print_text

ret_8ED6:
	ret

print_text:
	mov		ch, 1
	mov		bx, 15
	jmp		print_string


; Prints a text.
;
; input:
; di - string to write
; bx - y
; ch - unpacked texture index
print_string:							; 8EDE
	push	ds
	pop		es
	mov		[print_font_ix], ch
	mov		cx, 40
	mov		al, 20h
	repe scasb
	dec		di							; locate first non-space character
	mov		si, di
	mov		di, print_tmp_str
	push	di

next_char:
	cmp		byte [si], 0				; "\0"
	jz		loc_8F0C
	cmp		word [si], 0020h			; " \0"
	jz		loc_8F0C
	cmp		word [si], 2020h			; "  "
	jnz		loc_8F05
	inc		si
	jmp		next_char

loc_8F05:
	movsb
	cmp		di, print_font_ix			; < 40 chars?
	jb		next_char

loc_8F0C:
	mov		ax, si
	pop		si
	inc		ax
	push	ax
	mov		dx, di
	sub		dx, si						; dx = strlen
	jz		exit_8F33
	mov		ax, dx
	shl		ax, 3
	neg		ax
	add		ax, 320
	shr		ax, 1
	mov		ch, [print_font_ix]

draw_one_more_char:
	mov		cl, [si]
	inc		si							; x = (!(strlen << 3) + 320) >> 1
	call	draw_char_small
	add		ax, 8						; x += 8
	dec		dx
	jnz		draw_one_more_char

exit_8F33:
	pop		di
	ret


loc_8F35:
	jmp		brandish_the_flag


;
; Brandishes the flag.
;
brandish_the_flag:						; 8F37
	mov		si, [word_3ED8]
	mov		ax, [word_3EE0]
	mov		cl, 0
	and		ax, ax
	js		loc_8F83
	cmp		ax, 75
	jae		loc_8F57
	mov		cl, 14
	cmp		al, 20
	jae		loc_8F83
	shr		al, 2
	inc		ax
	mov		cl, al
	jmp		loc_8F83

loc_8F57:
	mov		ax, [si + 216]
	and		ax, ax
	jz		loc_8F73
	cmp		ax, 75
	jae		loc_8F73
	mov		cl, 14
	cmp		al, 24
	jae		loc_8F83
	shr		al, 2
	add		al, 6
	mov		cl, al
	jmp		loc_8F83

loc_8F73:
	cmp		word [si + 228], 0
	jz		ret_8FA2
	cmp		word [si + 222], 0FFFFh
	jz		ret_8FA2
	mov		cl, 12

loc_8F83:
	push	cx
	mov		ax, 224
	mov		bx, 29
	mov		ch, 2
	mov		cl, 13						; draw background frame
	call	bmp_draw
	pop		cx
	cmp		cl, 13
	ja		ret_8FA2
	mov		ax, 224
	mov		bx, 29
	mov		ch, 2						; draw a flag
	call	bmp_draw

ret_8FA2:
	ret


loc_8FA3:
	jmp		draw_race_info


;
; Draws speed, gear, time, laps left, gas.
;
draw_race_info:							; 8FA5
	mov		si, [word_3ED8]
	mov		ax, 9A7h
	mul		word [si + 14]				; 16 kmh = 01A9h
										; 1 kmh ~= 20h
	mov		ax, dx
	mov		ch, 1						; C01
	mov		bl, 10
	div		bl
	mov		cl, ah
	push	cx
	mov		ah, 0
	div		bl
	mov		cl, ah
	push	cx
	mov		cl, al						; 1-st speed number
	mov		ax, 2
	mov		bx, 2
	call	bmp_draw
	pop		cx							; 2-nd speed number
	add		ax, 8
	call	bmp_draw
	pop		cx							; 3-rd speed number
	add		ax, 8
	call	bmp_draw
	mov		cl, 37						; hyphen
	add		ax, 8
	call	bmp_draw
	mov		cl, 20						; K
	add		ax, 8
	call	bmp_draw
	mov		cl, 22						; M
	add		ax, 8
	call	bmp_draw
	mov		cl, 17						; H
	add		ax, 8
	call	bmp_draw
	mov		cl, 37						; hyphen
	add		ax, 8
	call	bmp_draw
	mov		es, [word_63BC]
	mov		di, 336 * 17 + 18
	call	sub_9242
	mov		dx, [si + 44]
	shr		dx, 7
	cmp		dx, 2Eh						; '.'
	jb		loc_901A
	mov		dx, 2Eh						; '.'

loc_901A:
	mov		bp, 0Ch

loc_901D:
	push	di
	mov		cx, dx
	jcxz	loc_9038
	cmp		cx, 20h						; ' '
	jb		loc_902A
	mov		cx, 20h						; ' '

loc_902A:
	mov		al, 0E4h					; 'S'
	rep stosb
	mov		cx, dx
	sub		cx, 20h						; ' '
	jbe		loc_9038
	inc		ax
	rep stosb

loc_9038:
	mov		al, 0E0h					; 'a'
	stosb
	pop		di
	add		di, 336
	dec		bp
	jnz		loc_901D
	mov		cx, [si + 40]
	inc		cx							; gear: 1, 2, 3, 4, 5
	mov		ch, 0						; C00
	mov		ax, 1
	mov		bx, 29
	call	bmp_draw
	add		ax, 16
	add		cl, 9						; st, nd, rd, th
	call	bmp_draw
	cmp		word [word_3EE4], 0
	jnz		loc_9065
	jmp		loc_90E9					; when Race::TimeLimit

; draw gas level borders
loc_9065:
	mov		di, 336 * 6 + 270
	mov		ax, 0E0E0h					; blackblack
	mov		cx, 32
	rep stosw							; top bounding line
	mov		cx, 7

loc_9073:
	add		di, 335
	stosb								; right bounding line
	loop	loc_9073

	add     di, 334
	mov     cx, 32
	std									; decrease DI on rep
	rep stosw							; bottom bounding line
	cld

	sub     di, 334
	mov     cx, 7

loc_908C:
	stosb								; left bounding line
	sub		di, 337
	loop	loc_908C

; draw gas level
	add		di, 337
	mov		ax, [si + 222]
	rol		ax, 6
	and		ax, 3Fh
	cmp		ax, 1
	cmc
	sbb		ax, 0
	mov		dx, 8
	cmp		ax, dx
	jg		loc_90B1
	mov		dx, ax

loc_90B1:
	sub		ax, dx
	mov		bx, 16
	cmp		ax, bx
	jg		loc_90BC
	mov		bx, ax

loc_90BC:
	sub		ax, bx
	mov		bh, al
	mov		bp, 7						; height = 7 pixels

loc_90C3:
	push	di
	mov		cx, dx
	jcxz	loc_90CC
	mov		al, 0E5h					; light red
	rep stosb

loc_90CC:
	mov		cl, bl
	jcxz	loc_90D4
	mov		al, 0E4h					; dark red
	rep stosb

loc_90D4:
	mov		cl, bh
	jcxz	loc_90DC
	mov		al, 230					; green
	rep stosb

loc_90DC:
	mov		al, 0E0h					; black
	stosb								; right bounding line (inner)
	pop		di
	add		di, 336
	dec		bp
	jnz		loc_90C3
	jmp		loc_9102

loc_90E9:
	mov		cx, 254
	mov		bx, 2

loc_90EF:
	mov		dx, [si + 46]				; score
	mov		ax, [si + 48]				; score
	mov		bp, 10000
	div		bp
	push	dx
	call	sub_9277					; draw right part (4 numbers)
	pop		ax
	call	sub_9277					; draw left part (4 numbers)

loc_9102:
	mov		ax, [si + 32]
	cmp		word [word_3EE4], 0
	jz		loc_9110
	mov		ax, [si + 226]

; draw remaining time when Race::TimeLimit
loc_9110:
	mov		cl, 10
	div		cl
	mov		ch, 0
	mov		cl, ah
	push	cx
	mov		cl, al
	mov		ax, 287
	mov		bx, 29
	jcxz	loc_9126
	call	bmp_draw					; left number

loc_9126:
	pop		cx
	add		ax, 16
	call	bmp_draw					; right number
	mov		es, [word_63BC]

; draw track line borders
	mov		di, 336 * 51 + 316
	mov		bp, [num_of_tracks]
	mov		ax, 0E0E0h					; blackblack
	cmp		word [track_num], 1			; Night
	je		loc_9150
	cmp		word [track_num], 2			; Fog
	je		loc_9150
	cmp		word [track_num], 7			; Storm
	jne		loc_9153

loc_9150:
	mov		ax, 0E2E2h					; lightgraylightgray

loc_9153:
	mov		cx, 9						; 18 px wide
	rep stosw							; draw top line
	add		di, 318
	stosb								; draw left (top) px
	add		di, 16
	stosb								; draw right (top) px
	add		di, 318
	stosb								; draw left (bottom) px
	add		di, 16
	stosb								; draw right (bottom) px
	add		di, 318
	dec		bp
	jnz		loc_9153					; for each track line
	mov		cx, 9
	rep stosw							; draw bottom line

; draw completed track progress bar
	mov		di, 336 * 52 + 317
	mov		bx, arr_2400
	mov		bp, [si]
	cmp		bp, [bx]
	jbe		loc_91D1
	mov		ax, 0E5E5h					; redred

loc_9185:
	cmp		word [bx + 2], 0FFFFh
	jz		loc_91D1
	cmp		bp, [bx + 2]
	jb		loc_91A7
	mov		cx, 8						; full width (16 px)
	rep stosw
	add		di, 320
	mov		cx, 8						; full width (16 px)
	rep stosw
	add		di, 336 * 1 + 320
	add		bx, 2
	jmp		loc_9185

loc_91A7:
	mov		cx, [bx + 2]
	sub		cx, [bx]
	mov		ax, bp
	sub		ax, [bx]
	shl		ax, 4
	mov		dx, 0
	jcxz	loc_91D1
	div		cx
	mov		dx, ax
	cmp		dx, 16
	jae		loc_91D1

; draw current track progress bar
	mov		al, 0E5h					; red
	push	di
	mov		cx, dx
	rep stosb							; top px
	pop		di
	add		di, 336
	mov		cx, dx
	rep stosb							; bottom px

loc_91D1:
	cmp		word [num_of_players], 0
	je		ret_9241

; for 2PL mode draw status bar on who is ahead
	mov		di, 336 * 17 + 286
	call	sub_9242
	mov		dx, [word_3FB6]
	mov		ax, [word_4026]
	cmp		si, word_4034
	jz		loc_91F2
	mov		dx, [word_40B0]
	mov		ax, [word_4120]

loc_91F2:
	sub		dx, [si + 124]
	sar		dx, 1
	jns		loc_91FC
	adc		dx, 0

loc_91FC:
	cmp		dx, -22
	jg		loc_9204
	mov		dx, -22

loc_9204:
	cmp		dx, 22
	jl		loc_920C
	mov		dx, 22

loc_920C:
	cmp		al, 3
	jb		loc_9212
	mov		al, 0

loc_9212:
	shl		al, 1
	add		al, 5
	add		al, [byte_2E81]
	mov		ah, 0E0h
	xchg	al, ah
	add		di, 21
	inc		dx
	jg		loc_922A
	dec		dx
	add		di, dx
	neg		dx
	inc		dx

loc_922A:
	inc		dx
	mov		bp, 12

loc_922E:
	push	di
	stosb
	mov		cx, dx
	xchg	al, ah
	rep stosb
	xchg	al, ah
	stosb
	pop		di
	add		di, 336
	dec		bp
	jnz		loc_922E

ret_9241:
	ret
