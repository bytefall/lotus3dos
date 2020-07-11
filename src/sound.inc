;
;
;
sub_2000:								; 2000
	pusha
	shl		ax, 1
	nop
	and		ax, 3FFh
	mov		bx, ax
	shr		bx, 7
	or		al, 80h
	mov		bp, ax
	mov		al, [2Ch]
	cmp		al, 40h
	jb		loc_2019
	mov		al, 3Fh

loc_2019:
	shl		al, 2
	mov		dl, al
	call	sub_202F
	neg		bp
	dec		bx
	call	sub_202F
	add		bx, 2
	call	sub_202F
	popa
	ret


;
;
;
sub_202F:								; 202F
	cmp		bx, 8
	jae		ret_202F
	mov		ax, bp
	mul		dl
	mov		al, ah
	add		al, [bx]
	jae		loc_2042
	mov		al, 0FFh

loc_2042:
	mov		[bx], al
	cmp		[bx + 8], al
	jae		ret_202F
	mov		byte [bx + 8], al
	mov		byte [bx + 16], 100

ret_202F:
	ret


;
;
;
sub_2056:								; 2056
	mov		si, 0
	mov		cx, 8

loc_205C:
	cmp		byte [si], 0
	je		loc_2064
	sub		byte [si], 3

loc_2064:
	cmp		byte [si + 16], 0
	je		loc_206F
	dec		byte [si + 16]
	jne		sub_2078

loc_206F:
	mov		al, [si]
	mov		byte [si + 8], al
	mov		byte [si + 16], 100

sub_2078:
	inc		si
	loop	loc_205C
	ret


;
; Called from cs:5116
;
sub_207C:								; 207C
	push	ax
	mov		al, 6
	mul		cl
	mov		bx, ax
	pop		ax
	mov		di, [bx + 3Ah]
	jmp		word [word_36]				; = 2557h


;
;
;
sub_208C:								; 208C
	push	ax
	mov		al, 6
	mul		cl
	mov		bx, ax
	pop		ax
	mov		di, [bx + 3Ah]
	jmp		word [word_38]


;
;
;
sub_209C:								; 209C
	mov		ax, 2141h
	mov		[word_30], ax
	mov		[word_32], ax
	mov		[word_34], ax
	mov		byte [byte_22], 0
	mov		bx, [word_16F6]
	cmp		bl, 3
	ja		loc_20D9
	shl		bx, 1
	mov		si, [bx + 24]
	mov		[word_20], si
	lodsw
	mov		cx, ds
	mov		es, cx
	mov		di, word_30					; mov to word_30..=word_38
	mov		cx, 5
	rep movsw
	mov		cx, 8

loc_20D0:
	movsw
	add		di, 4
	loop	loc_20D0
	call	ax
	ret

loc_20D9:
	stc
	ret


;
;
;
sub_20DB:								; 20DB
	cmp		byte [song_num], 0
	jnz		ret_20EC
	pusha
	push	ds
	push	es

loc_20E5:
	call	word [word_34]
	pop		es
	pop		ds
	popa

ret_20EC:
	ret


;
;
;
sub_20ED:								; 20ED
	call	sub_209C
	jb		ret_211D
	cmp		byte [song_num], 0
	jz		loc_2113
	cmp		word [word_26], 0
	jz		ret_211D
	mov		al, 6
	call	sub_2207
	mov		byte [byte_23], 0
	call	sub_216D

loc_210D:
	mov		byte [byte_22], -1
	ret

loc_2113:
	cmp		word [word_16F6], 2
	jnz		short ret_211D
	call	sub_2899

ret_211D:
	ret


;
;
;
sub_211E:								; 211E
	call	word [word_30]
	cmp		byte [byte_22], 0
	jz		loc_213E
	mov		al, [byte_24]
	inc		byte [byte_23]
	cmp		byte [byte_23], al
	jb		loc_213E
	mov		byte [byte_23], 0
	call	sub_2142

loc_213E:
	call	sub_2056

sub_2142:								; 2142
	mov		es, [word_26]
	mov		di, [word_2A]
	mov		si, 3Ah
	call	sub_219F
	mov		si, 40h
	call	sub_219F
	mov		si, 46h
	call	sub_219F
	mov		si, 4Ch
	call	sub_219F
	cmp		word [es:di], 0FFFFh
	jz		short loc_2185
	xchg	di, [word_2A]
	ret


;
;
;
sub_216D:								; 216D
	mov		word [word_28], 0
	cmp		byte [song_num], 3
	jne		loc_2185
	cmp		word [word_16F6], 3
	jne		loc_2185
	inc		word [word_28]

loc_2185:
	mov		es, [word_26]
	mov		di, [word_28]
	inc		word [word_28]
	shl		di, 1
	mov		di, [es:di]					; di = 003C
	and		di, di
	jz		sub_216D
	mov		[word_2A], di				; clock
	ret


;
;
;
sub_219F:								; 219F
	mov		byte [word_2C], 0FFh
	mov		ax, [es:di]
	inc		di
	cmp		al, 0
	jz		ret_21FC
	inc		di
	test	al, 0C0h
	jz		loc_21BE
	test	al, 80h
	jnz		loc_21DF
	push	ax
	mov		al, [es:di]
	inc		di
	call	sub_21FD
	pop		ax

loc_21BE:
	mov		bl, al
	shr		bl, 2
	and		bx, 0Fh
	xchg	al, ah
	and		ax, 3FFh
	call	sub_2000
	mov		[si + 2], ax
	push	es
	push	di
	push	si
	mov		si, [si]
	call	word [word_32]
	pop		si
	pop		di
	pop		es
	jmp		loc_21F2

loc_21DF:
	dec		di

loc_21E0:
	call	sub_21FD
	mov		ax, [word_2C]
	cmp		al, 0FFh
	jz		ret_21FC
	push	di
	mov		di, [si]
	call	word [word_36]
	pop		di

loc_21F2:
	mov		ax, [word_2C]
	cmp		al, 0FFh
	jz		ret_21FC
	mov		[si + 4], ax

ret_21FC:
	ret


;
;
;
sub_21FD:								; 21FD
	test	al, 40h
	jne		sub_2207
	and		al, 3Fh
	mov		byte [word_2C], al
	ret


;
;
;
sub_2207:								; 2207
	and		ax, 0Fh
	push	bx
	mov		bl, [song_num]
	mov		bh, 0
	shl		bx, 1
	mov		dx, word [bx + 106]
	pop		bx
	mul		dx
	mov		[byte_24], ah
	ret


;
; called from cs:20D6 (call near ax) from sub_209C
;
unk_221F:								; 221F
	mov		ax, [word_3D76]
	mov		dx, 0
	mov		bx, 303
	div		bx
	mov		[word_7C], ax
	mov		ax, [word_3D76]
	mov		dx, 0
	mov		bx, 43
	div		bx
	mov		[word_7E], ax
	mov		di, 0xcc

loc_223E:
	mov		bx, word [di]
	call	sub_2586
	mov		byte [di + 2], 0
	mov		word [di + 6], 0
	add		di, 18
	cmp		di, 294
	jbe		loc_223E
	mov		ah, 1
	mov		al, 0
	call	sub_258F
	mov		ah, 4
	mov		al, 0xe0
	call	sub_258F
	mov		ah, 8
	mov		al, 0
	call	sub_258F
	mov		ah, 176
	mov		al, 0

loc_226E:
	call	sub_258F
	inc		ah
	cmp		ah, 185
	jb		loc_226E
	mov		ah, 0xa0
	mov		al, 0

loc_227C:
	call	sub_258F
	inc		ah
	cmp		ah, 0xa9
	jb		loc_227C
	mov		ah, 0xc0
	mov		al, 0

loc_228A:
	call	sub_258F
	inc		ah
	cmp		ah, 0xc9
	jb		loc_228A
	mov		ah, 0xe0
	mov		al, 0

loc_2298:
	call	sub_258F
	inc		ah
	cmp		ah, 0xf6
	jb		loc_2298
	mov		ah, 0x20
	mov		al, 0

loc_22A6:
	call	sub_258F
	inc		ah
	cmp		ah, 0x36
	jb		loc_22A6
	mov		ah, 0x40
	mov		al, 0x3f

loc_22B4:
	call	sub_258F
	inc		ah
	cmp		ah, 0x56
	jb		loc_22B4
	mov		ah, 0x60
	mov		al, 0xf0

loc_22C2:
	call	sub_258F
	inc		ah
	cmp		ah, 0x76
	jb		loc_22C2
	mov		ah, 0x80
	mov		al, 0x1f

loc_22D0:
	call	sub_258F
	inc		ah
	cmp		ah, 0x96
	jb		loc_22D0
	mov		ah, 0xbd
	mov		al, 0x40
	call	sub_258F
	mov		ah, 1
	mov		al, 0x20
	call	sub_258F
	call	sub_2C1F
	cmp		word [0x16f6], 0
	jne		loc_2321
	mov		dx, 0x226
	mov		al, 1
	out		dx, al
	mov		cx, word [0x7c]

loc_22FC:
	loop	loc_22FC
	mov		al, 0
	out		dx, al
	mov		cx, word [0x7e]
	shl		cx, 2
	mov		dx, 0x22e

loc_230B:
	in		al, dx
	and		al, al
	js		loc_2314
	loop	loc_230B
	jmp		loc_2323

loc_2314:
	mov		dx, 0x22a
	in		al, dx
	cmp		al, 0xaa
	jne		loc_2323
	mov		al, 0xd3
	call	sub_2BC7

loc_2321:
	clc
	ret

loc_2323:
	mov		word [word_16F6], 1
	clc
	ret


;
;
;
unk_232B:								; 232B
	mov		di, si
	shl		bx, 1
	mov		si, word [bx + 0x9c]
	and		si, si
	jne		loc_233A
	jmp		loc_23F2

loc_233A:
	mov		ch, byte [si + 0xb]
	mov		cl, 0
	cmp		ax, cx
	jb		loc_2346
	jmp		loc_23F2

loc_2346:
	mov		dx, ax
	mov		ax, 0
	div		cx
	mov		cx, 2000h
	cmp		ax, 23CCh
	jae		loc_235F

loc_2355:
	add		ch, 4
	shl		ax, 1
	cmp		ax, 23CCh
	jb		loc_2355

loc_235F:
	mov		bx, ax
	mov		dx, 47h
	mov		ax, 98B7h
	div		bx
	add		ax, cx
	push	di
	push	ax
	call	sub_23F3
	test	byte [si + 0xa], 0x80
	je		loc_2390
	pop		ax
	push	ax
	mov		di, 0x114
	mov		cx, ax
	and		cx, 0xfc00
	and		ax, 0x3ff
	mov		dx, 0xe412
	mul		dx
	mov		ax, dx
	or		ax, cx
	call	sub_23F3

loc_2390:
	test	byte [si + 0xa], 0x40
	je		loc_23B0
	pop		ax
	push	ax
	mov		di, 0x114
	mov		cx, ax
	and		cx, 0xfc00
	and		ax, 0x3ff
	inc		word [bp + di]
	mov		dx, 0xd745
	mul		dx
	mov		ax, dx
	or		ax, cx
	call	sub_23F3

loc_23B0:
	test	byte [si + 0xa], 0x20
	je		loc_23D0

	pop		ax
	push	ax
	mov		di, 0x126
	mov		cx, ax
	and		cx, 0xfc00
	and		ax, 0x3ff
	mov		dx, 0xbfc8
	mul		dx
	mov		ax, dx
	or		ax, cx
	call	sub_23F3

loc_23D0:
	test	byte [si + 0xa], 0x10
	je		loc_23F0

	pop		ax
	push	ax
	mov		di, 0x126
	mov		cx, ax
	and		cx, 0xfc00
	and		ax, 0x3ff
	mov		dx, 0xaadc
	mul		dx
	mov		ax, dx
	or		ax, cx
	call	sub_23F3

loc_23F0:
	pop		ax
	pop		di

loc_23F2:
	ret


;
;
;
sub_23F3:								; 23F3
	mov		word [di + 6], 0


;
;
;
sub_23F8:								; 23F8
	mov		word [di + 4], ax
	push	ax
	mov		bx, word [di]
	call	sub_2586
	mov		al, byte [si + 1]
	mov		byte [di + 2], al
	mov		ch, 0
	mov		al, byte [0x2c]
	cmp		al, 0xff
	je		loc_241A
	push	bx
	mov		bh, 0
	mov		bl, al
	mov		ch, byte [bx + 0x291]
	pop		bx

loc_241A:
	mov		cl, byte [bx + 0x288]
	call	sub_2455
	push	si
	add		si, 5
	sub		cl, 3
	mov		ch, 0
	call	sub_2455
	pop		si
	mov		al, byte [si + 0xa]
	and		al, 0xf
	mov		ah, bl
	add		ah, 0xc0
	call	sub_258F
	pop		ax
	cmp		byte [si + 0xc], 0
	jne		ret_2454
	mov		cl, ah
	mov		ah, bl
	add		ah, 0xa0
	call	sub_258F
	mov		al, cl
	add		ah, 0x10
	call	sub_258F

ret_2454:
	ret


;
;
;
sub_2455:								; 2455
	mov		ah, cl
	add		ah, 0x20
	mov		al, byte [si]
	call	sub_258F
	add		ah, 0x20
	mov		al, byte [si + 1]
	mov		dl, al
	and		dl, 0xc0
	and		al, 0x3f
	add		al, ch
	cmp		al, 0x40
	jb		loc_2474
	mov		al, 0x3f

loc_2474:
	or		al, dl
	call	sub_258F
	add		ah, 0x20
	mov		al, byte [si + 2]
	call	sub_258F
	add		ah, 0x20
	mov		al, byte [si + 3]
	call	sub_258F
	add		ah, 0x60
	mov		al, byte [si + 4]
	jmp		sub_258F


;
;
;
unk_2494:								; 2494
	cmp		word [0x16f6], 0
	jne		loc_24AA
	cmp		cl, 0
	jne		loc_24AA
	cmp		al, 0
	jne		loc_24A7
	jmp		sub_2C1F

loc_24A7:
	jmp		loc_2AD7

loc_24AA:
	mov		bh, 0
	shl		bx, 1
	mov		si, word [bx + 0x9e]
	and		si, si
	je		ret_24E4
	push	bx
	mov		byte [0x2c], al
	mov		bl, cl
	shl		bx, 1
	mov		di, word [bx + 0x8c]
	pop		bx
	mov		cx, word [bx + 0xb83]
	mov		word [di + 6], cx
	mov		word [di + 8], 0
	mov		ax, 0
	cmp		cx, ax
	jne		loc_24E1
	mov		al, byte [si + 0xb]
	mov		ah, 0
	shl		ax, 6
	or		ah, 0x20

loc_24E1:
	call	sub_23F8

ret_24E4:
	ret


;
;
;
unk_24E5:								; 24E5
	call	sub_2C8A
	inc		word [0x78]
	and		word [0x78], 3
	mov		bx, [0x78]
	shl		bx, 2
	mov		di, [bx + 0x8c]
	push	word [bx + 0x8e]
	call	loc_2CE9
	pop		di
	jmp		loc_2CE9


;
;
;
unk_2507:								; 2507
	cmp		word [di + 6], 0
	jne		loc_2550
	mov		bx, word [di + 4]
	mov		cl, bh
	shr		cl, 2
	and		cl, 7
	and		bx, 0x3ff
	shl		bx, cl
	mul		bx
	mov		al, ah
	mov		ah, dl
	mov		cl, 0
	jmp		loc_252B

loc_2528:
	shr		ax, 1
	inc		cx

loc_252B:
	test	ah, 0xfc
	jne		loc_2528
	cmp		cl, 7
	jbe		loc_2537
	mov		cl, 7

loc_2537:
	shl		cl, 2
	or		cl, ah
	or		cl, 0x20
	mov		ah, byte [di]
	add		ah, 0xa0
	call	sub_258F
	add		ah, 0x10
	mov		al, cl
	call	sub_258F
	ret

loc_2550:
	shr		ax, 2
	mov		word [di + 0x10], ax
	ret


;
;
;
unk_2557:								; 2557
	cmp		word [0x16f6], 0
	jne		loc_2564
	cmp		di, 0xcc
	je		loc_2580

loc_2564:
	mov		bh, 0
	mov		bl, al
	mov		al, byte [bx + 0x291]
	add		al, byte [di + 2]
	cmp		al, 0x3f
	jb		loc_2575
	mov		al, 0x3f

loc_2575:
	mov		bx, word [di]
	mov		ah, byte [bx + 0x288]
	add		ah, 0x40
	jmp		sub_258F

loc_2580:
	or		al, 1
	mov		byte [0x5ae], al
	ret


;
;
;
sub_2586:								; 2586
	mov		al, 0
	mov		ah, bl
	add		ah, 176
	jmp		sub_258F


;
;
;
sub_258F:								; 258F
	pushf
	push	cx
	push	dx
	mov		dx, 0x388
	xchg	ah, al
	cli
	out		dx, al
	xchg	ah, al
	mov		cx, word [0x7c]

self_259F:
	loop	self_259F
	inc		dx
	out		dx, al
	mov		cx, word [0x7e]

self_25A7:
	loop	self_25A7
	pop		dx
	pop		cx
	popf
	ret


;
;
;
sub_25AD:								; 25AD
	mov		word [0x32b], 0
	mov		word [0x330], 0
	mov		word [0x335], 0
	mov		word [0x33a], 0
	mov		word [0x33f], 0
	mov		word [0x344], 0
	mov		word [0x349], 0
	mov		word [0x34e], 0
	cmp		byte [0x3e1], 0xff
	je		loc_264D
	cmp		byte [0x3e1], 1
	je		loc_25FA
	mov		byte [0x3e1], 0xff
	call	sub_264F
	jb		loc_264D
	mov		byte [0x3e1], 1

loc_25FA:
	mov		si, 0x3c5
	call	sub_2864
	mov		si, 0x3ca
	call	sub_2864
	mov		bx, 0xb9b1

loc_2609:
	mov		al, bl
	call	sub_28EB
	mov		al, 0x7b
	call	sub_28EB
	mov		al, 0
	call	sub_28EB
	mov		al, bl
	call	sub_28EB
	mov		al, 0x79
	call	sub_28EB
	mov		al, 0
	call	sub_28EB
	mov		al, bl
	call	sub_28EB
	mov		al, 7
	call	sub_28EB
	mov		al, 0x7f
	call	sub_28EB
	mov		al, bl
	call	sub_28EB
	mov		al, 0xa
	call	sub_28EB
	mov		al, 0x40
	call	sub_28EB
	inc		bl
	cmp		bl, bh
	jbe		loc_2609
	clc
	ret

loc_264D:
	stc
	ret


;
;
;
sub_264F:								; 264F
	mov		al, 0xff
	call	sub_28AC					; al - port
	jae		loc_265D
	mov		al, 0xff
	call	sub_28AC					; al - port
	jb		loc_2660

loc_265D:
	call	sub_28D2					; al - port

loc_2660:
	ret

loc_2661:
	cmp		byte [3E1h], 1
	je		loc_266B
	jmp		ret_26EA

loc_266B:
	mov		bh, 0
	inc		bx
	shl		bx, 1
	mov		si, word [bx + 2FAh]
	and		si, si
	je		ret_26EA
	mov		bl, cl
	mov		bh, 0
	shl		bx, 1
	mov		di, word [bx + 2EAh]
	call	sub_281D
	cmp		word [di + 1], 0
	je		loc_269C
	mov		al, byte [di + 3]
	call	sub_28EB
	mov		al, byte [di + 4]
	call	sub_28EB
	mov		al, 0
	call	sub_28EB

loc_269C:
	mov		al, 0x99
	cmp		byte [si], 0x80
	jae		loc_26C4
	mov		al, 0xb0
	add		al, byte [di]
	call	sub_28EB
	mov		al, 0x7b
	call	sub_28EB
	mov		al, 0
	call	sub_28EB
	mov		al, 0xc0
	add		al, byte [di]
	call	sub_28EB
	mov		al, byte [si]
	call	sub_28EB
	mov		al, 0x90
	add		al, byte [di]

loc_26C4:
	mov		byte [di + 3], al
	call	sub_28EB
	mov		al, byte [si + 2]
	mov		byte [di + 4], al
	call	sub_28EB
	mov		al, byte [si + 3]
	call	sub_28EB
	mov		ah, 0
	mov		al, byte [si + 1]
	cmp		al, 0xf0
	jb		loc_26E7
	mov		ah, al
	and		ah, 0xf

loc_26E7:
	mov		word [di + 1], ax

ret_26EA:
	ret


;
;
;
unk_26EB:								; 26EB
	mov		di, si
	shl		bx, 1
	mov		si, word [bx + 0x2fa]
	and		si, si
	jne		loc_26FA
	jmp		ret_27C2

loc_26FA:
	test	byte [si + 4], 1
	je		loc_2703
	jmp		ret_27C2

loc_2703:
	cmp		byte [si], 0x80
	jb		loc_2722
	mov		al, 0x99
	mov		byte [di + 3], al
	call	sub_28EB
	mov		al, byte [si + 2]
	mov		byte [di + 4], al
	call	sub_28EB
	mov		al, byte [si + 3]
	call	sub_28EB
	jmp		loc_27BA

loc_2722:
	mov		cx, 5
	cmp		ah, 0
	je		loc_2732

loc_272A:
	shr		ax, 1
	dec		cx
	cmp		ah, 0
	jne		loc_272A

loc_2732:
	and		al, al
	js		loc_273B
	shl		al, 1
	inc		cx
	jmp		loc_2732

loc_273B:
	and		cx, cx
	jns		loc_2742
	mov		cx, 0

loc_2742:
	cmp		cx, 8
	jb		loc_274A
	mov		cx, 8

loc_274A:
	mov		bx, ax
	mov		al, 0xc
	mul		cl
	add		al, byte [bx + 0x3a3]
	push	ax
	mov		al, 0xb0
	add		al, byte [di]
	call	sub_28EB
	mov		al, 0x7b
	call	sub_28EB
	mov		al, 0
	call	sub_28EB
	mov		al, 0xc0
	add		al, byte [di]
	call	sub_28EB
	mov		al, byte [si]
	call	sub_28EB
	mov		al, byte [0x2c]
	cmp		al, 0xff
	jne		loc_277B
	mov		al, 0x40

loc_277B:
	call	sub_281D
	pop		ax
	push	ax
	call	sub_27C3
	pop		ax
	test	byte [si + 4], 0x80
	je		loc_2792
	push	ax
	sub		ax, 2
	call	sub_27C3
	pop		ax

loc_2792:
	test	byte [si + 4], 0x40
	je		loc_27A0
	push	ax
	sub		ax, 3
	call	sub_27C3
	pop		ax

loc_27A0:
	test	byte [si + 4], 0x20
	je		loc_27AE
	push	ax
	sub		ax, 5
	call	sub_27C3
	pop		ax

loc_27AE:
	test	byte [si + 4], 0x10
	je		loc_27BA
	sub		ax, 7
	call	sub_27C3

loc_27BA:
	mov		ah, 0
	mov		al, byte [si + 1]
	mov		word [di + 1], ax

ret_27C2:
	ret


;
;
;
sub_27C3:								; 27C3
	push	ax
	mov		al, 0x90
	add		al, byte [di]
	mov		byte [di + 3], al
	call	sub_28EB
	pop		ax
	add		al, byte [si + 2]
	mov		byte [di + 4], al
	call	sub_28EB
	mov		al, byte [si + 3]
	call	sub_28EB
	ret

unk_27DF:								; 27DF
	mov		si, 0x32a

loc_27E2:
	cmp		word [si + 1], 0
	je		loc_2813
	dec		word [si + 1]
	jne		loc_2813
	mov		al, byte [si + 3]
	cmp		al, 0x99
	je		loc_2805
	add		al, 0x20
	call	sub_28EB
	mov		al, 0x7b
	call	sub_28EB
	mov		al, 0
	call	sub_28EB
	jmp		loc_2813

loc_2805:
	call	sub_28EB 
	mov		al, byte [si + 4]
	call	sub_28EB
	mov		al, 0
	call	sub_28EB

loc_2813:
	add		si, 5
	cmp		si, 0x34d
	jbe		loc_27E2
	ret


;
;
;
sub_281D:								; 281D
	cmp		byte [0x3e1], 1
	jne		ret_283B

	mov		bl, al
	mov		bh, 0
	mov		al, 0xb0
	add		al, byte [di]
	call	sub_28EB
	mov		al, 7
	call	sub_28EB
	mov		al, byte [bx + 0x3e2]
	call	sub_28EB

ret_283B:
	ret


;
;
;
unk_283C:								; 283C
	cmp		byte [0x3e1], 1
	jne		ret_2863
	shl		ax, 4
	shl		ax, 1
	shr		al, 1
	add		ah, 0x40
	and		ah, 0x7f
	mov		bx, ax
	mov		al, 0xe0
	add		al, byte [di]
	call	sub_28EB
	mov		al, bl
	call	sub_28EB
	mov		al, bh
	call	sub_28EB

ret_2863:
	ret


;
;
;
sub_2864:								; 2864
	mov		al, 0xf0
	call	sub_28EB
	mov		al, 0x41
	call	sub_28EB
	mov		al, 0x10
	call	sub_28EB
	mov		al, 0x16
	call	sub_28EB
	mov		al, 0x12
	call	sub_28EB
	mov		bl, 0x80

loc_287F:
	lodsb
	and		al, al
	js		loc_288B
	sub		bl, al
	call	sub_28EB
	jmp		loc_287F

loc_288B:
	and		bl, 0x7f
	mov		al, bl
	call	sub_28EB
	mov		al, 0xf7
	call	sub_28EB
	ret


;
;
;
sub_2899:								; 2899
	cmp		byte [0x3e1], 1
	jne		ret_28AB
	mov		si, 0x74a

loc_28A3:
	call	sub_2864
	cmp		byte [si], 0
	jge		loc_28A3

ret_28AB:
	ret


;
;
;
sub_28AC:								; 28AC
	push	cx
	push	ax
	mov		dx, 0x331
	mov		cx, 0xffff

loc_28B4:
	in		al, dx
	test	al, 0x40
	loopne	loc_28B4
	jne		loc_28CE
	pop		ax
	push	ax
	out		dx, al
	mov		cx, 0xffff

loc_28C1:
	in		al, dx
	test	al, 0x80
	loopne	loc_28C1
	jne		loc_28CE
	dec		dx
	in		al, dx
	cmp		al, 0xfe
	je		loc_28CF

loc_28CE:
	stc

loc_28CF:
	pop		ax
	pop		cx
	ret


;
;
;
sub_28D2:								; 28D2
	push	cx
	push	ax
	mov		dx, 0x331
	mov		cx, 0xffff

loc_28DA:
	in		al, dx
	test	al, 0x40
	loopne	loc_28DA
	jne		loc_28E7
	mov		al, 0x3f
	out		dx, al
	clc
	jmp		loc_28E8

loc_28E7:
	stc

loc_28E8:
	pop		ax
	pop		cx
	ret


;
;
;
sub_28EB:								; 28EB
	push	cx
	push	dx
	push	ax
	mov		dx, 0x331
	mov		cx, -1

loc_28F4:
	in		al, dx
	test	al, 40h						; make sure it isn't busy
	loopne	loc_28F4
	pop		ax
	dec		dx
	out		dx, al
	pop		dx
	pop		cx
	ret


;
;
;
unk_28FF:								; 28FF
	mov		di, 0x4dc
	push	ds
	pop		es
	mov		cx, 0x18
	mov		al, 0
	rep stosb
	in		al, 0x61
	and		al, 0xfc
	out		0x61, al
	mov		al, 0xb6
	out		0x43, al
	ret


;
;
;
unk_2916:								; 2916
	mov		di, si
	shl		bx, 1
	mov		si, word [bx + 0x500]
	and		si, si
	je		ret_296A
	mov		dl, byte [si + 1]
	sub		dl, 0xc
	cmp		dl, 0xc
	jb		loc_2942
	jg		loc_2938

loc_292F:
	shl		ax, 1
	add		dl, 0xc
	jae		loc_292F
	jmp		loc_2942

loc_2938:
	shr		ax, 1
	sub		dl, 0xc
	cmp		dl, 0xc
	jae		loc_2938

loc_2942:
	mov		bl, dl
	mov		bh, 0
	shl		bx, 1
	mul		word [bx + 0x4a5]
	mov		ax, 0x556
	mul		dx
	mov		al, ah
	mov		ah, dl
	mov		word [di + 4], ax
	mov		ah, 0
	mov		al, byte [si]
	cmp		al, 0xff
	jne		loc_2962
	mov		ah, 0x7f

loc_2962:
	mov		word [di], ax
	mov		al, byte [si + 2]
	mov		word [di + 2], ax

ret_296A:
	ret


;
;
;
unk_296B:								; 296B
	cmp		cl, 5
	jb		ret_299C
	cmp		al, 0x10
	jb		ret_299C
	mov		di, word [0x4bd]
	xor		word [0x4bd], 0x12
	add		di, 0x4dc
	mov		bh, 0
	shl		bx, 2
	mov		ax, word [bx + 0x54d]
	and		ax, ax
	je		ret_299C
	mov		word [di], ax
	mov		word [di + 2], 1
	mov		ax, word [bx + 0x54f]
	mov		word [di + 4], ax

ret_299C:
	ret


;
;
;
unk_299D:								; 299D
	cmp		di, 0x4e2
	je		loc_29A9
	cmp		di, 0x4e8
	jne		ret_29BF

loc_29A9:
	mov		word [di + 2], 1
	mov		word [di], 7FFFh
	mov		bx, ax
	mov		dx, 20
	mov		ax, 0
	div		bx
	mov		word [di + 4], ax

ret_29BF:
	ret


;
;
;
unk_29C0:								; 29C0
	cmp		al, 0
	jne		ret_29D5
	cmp		di, 0x4e2
	je		loc_29D0
	cmp		di, 0x4e8
	jne		ret_29D5

loc_29D0:
	mov		word [di + 2], 0

ret_29D5:
	ret


;
;
;
unk_29D6:								; 29D6
	push	ds
	pop		es
	mov		cx, 4
	mov		si, 0x4dc

loc_29DE:
	cmp		word [si], 0
	je		loc_29E7
	dec		word [si]
	jg		loc_29EC

loc_29E7:
	mov		word [si + 2], 0

loc_29EC:
	add		si, 6
	loop	loc_29DE
	dec		word [0x4c2]
	jg		ret_2A33
	mov		word [0x4c2], 4
	mov		bx, word [0x4c0]
	mov		cx, 3

loc_2A04:
	add		bx, 2
	and		bx, 6
	mov		di, word [bx + 0x4d0]
	cmp		word [di + 2], 0
	loope	loc_2A04
	mov		word [0x4c0], bx
	je		loc_2A2D
	mov		ax, word [di + 4]
	out		0x42, al
	mov		al, ah
	out		0x42, al
	in		al, 0x61
	and		al, 0xfc
	or		al, 3
	out		0x61, al
	jmp		ret_2A33

loc_2A2D:
	in		al, 0x61
	and		al, 0xfc
	out		0x61, al

ret_2A33:
	ret


; input:
; ax -- track number
play_music:								; 2A34
	push	ax
	call	sub_209C
	pop		ax
	mov		[song_num], al
	mov		ax, [cs:word_5168]
	mov		[word_63BA], ax
	mov		[word_26], ax
	cmp		byte [song_num], 0
	je		loc_2A5C
	mov		ah, 'T'
	mov		al, [song_num]
	call	res_load
	mov		[cs:word_5166], ax
	mov		[word_63BA], ax				; unpacked data

loc_2A5C:
	call	sub_2A66					; A03
	call	sub_2A8D					; R03
	call	sub_2AB4					; P03
	ret


;
;
;
sub_2A66:								; 2A66
	mov		ah, 'A'
	mov		al, [song_num]
	call	res_load
	push	ds
	push	ds
	pop		es
	mov		ds, [word_63BA]
	mov		si, 0
	mov		di, 15Ch
	mov		cx, 195
	cmp		byte [es:song_num], 0
	jne		loc_2A89
	mov		cx, 299

loc_2A89:
	rep movsb
	pop		ds
	ret


;
;
;
sub_2A8D:								; 2A8D
	mov		ah, 'R'
	mov		al, [song_num]
	call	res_load
	push	ds
	push	ds
	pop		es
	mov		ds, [word_63BA]
	mov		si, 0
	mov		di, 352h
	mov		cx, 75
	cmp		byte [es:song_num], 0
	jne		loc_2AB0
	mov		cx, 115

loc_2AB0:
	repe movsb
	pop		ds
	ret


;
;
;
sub_2AB4:								; 2AB4
	cmp		byte [song_num], 0
	je		ret_2AD6
	mov		ah, 'P'
	mov		al, [song_num]
	call	res_load
	push	ds
	push	ds
	pop		es
	mov		ds, [word_63BA]
	mov		si, 0
	mov		di, 520h
	mov		cx, 45
	repe movsb
	pop		ds

ret_2AD6:
	ret


loc_2AD7:
	cmp		word [0x2af9], 0
	jne		loc_2AE1
	jmp		ret_2BC6

loc_2AE1:
	mov		byte [0x5ae], al
	mov		al, 0xd0
	call	sub_2BC7
	sub		ax, ax
	mov		es, ax
	mov		ax, cs
	cmp		ax, [es:3Eh]
	je		loc_2B11
	cli
	xchg	[es:3Eh], ax
	mov		[5ACh], ax
	mov		ax, 0x2c49
	xchg	[es:3Ch], ax
	mov		[word_5AA], ax
	in		al, 0x21
	and		al, 0x7f
	out		0x21, al
	sti

loc_2B11:
	mov		ax, word [0x2af9]
	mov		dx, 0
	mov		cx, 0x100
	div		cx
	mov		cx, ax
	mov		ax, word [0x2af9]
	mov		dx, 0
	div		cx
	mov		bx, ax
	mov		ax, 0
	div		cx
	mov		dx, ax
	mov		dl, 0
	mov		word [0x5b4], cx
	mov		di, 0x5c4
	mov		si, 0

loc_2B3B:
	mov		word [di], si
	add		di, 4
	add		dl, dh
	adc		si, bx
	loop	loc_2B3B
	mov		cx, word [0x5b4]
	mov		si, word [0x2af9]

loc_2B4E:
	sub		di, 4
	sub		si, word [di]
	mov		word [di + 2], si
	mov		si, word [di]
	loop	loc_2B4E
	mov		ax, [word_63BA]
	mov		bx, ax
	shl		bx, 4
	add		bx, 0x35d
	jae		loc_2B6C
	or		ax, 0xfff
	inc		ax

loc_2B6C:
	mov		es, ax
	mov		bx, 0x11
	mov		dx, bx
	shl		dx, 4
	mov		word [0x5b8], ax
	mov		word [0x5ba], dx
	add		ax, bx
	mov		word [0x5bc], ax
	mov		word [0x5be], dx
	add		ax, bx
	mov		word [0x5c0], ax
	mov		word [0x5c2], dx
	mov		cx, dx
	shl		cx, 1
	add		cx, dx
	mov		di, 0
	mov		al, 0x80
	rep stosb
	mov		word [0x5b0], 0xffff
	mov		word [0x5b6], 0
	mov		al, 0x40
	call	sub_2BC7
	mov		al, 0x83
	call	sub_2BC7
	mov		ax, word [0x5b8]
	mov		bx, word [0x5ba]
	call	sub_2BE2
	mov		al, 0xd4
	call	sub_2BC7
	mov		al, 0xd1
	call	sub_2BC7

ret_2BC6:
	ret


;
;
;
sub_2BC7:								; 2BC7
	mov		ah, al
	mov		cx, word [0x7e]
	mov		dx, 0x22c

loc_2BD0:
	in		al, dx
	and		al, al
	jns		loc_2BDE
	loop	loc_2BD0
	mov		word [0x16f6], 1
	ret

loc_2BDE:
	mov		al, ah
	out		dx, al
	ret


;
;
;
sub_2BE2:								; 2BE2
	dec		bx
	push	bx
	mov		bx, ax
	mov		al, 5
	out		0Ah, al
	mov		al, 0
	out		0Ch, al
	mov		al, 0x49
	out		0Bh, al
	shl		bx, 4
	mov		al, bl
	out		2, al
	mov		al, bh
	out		2, al
	shr		ax, 0xc
	out		83h, al
	pop		bx
	mov		al, bl
	out		3, al
	mov		al, bh
	out		3, al
	mov		al, 1
	out		0Ah, al
	mov		al, 0x14
	call	sub_2BC7
	mov		al, bl
	call	sub_2BC7
	mov		al, bh
	call	sub_2BC7
	ret


;
;
;
sub_2C1F:								; 2C1F
	mov		byte [0x5ae], 0
	mov		al, 0xd0
	call	sub_2BC7
	mov		al, 0xd3
	call	sub_2BC7
	sub		ax, ax
	cmp		[word_5AA], ax
	je		ret_2C48
	mov		es, ax
	cli
	mov		ax, [word_5AA]
	mov		[es:3Ch], ax
	mov		ax, [5ACh]
	mov		[es:3Eh], ax
	sti

ret_2C48:
	ret


;
;
;
unk_2C49:								; 2C49
	pushaw
	push	ds
	mov		dx, 0x22e
	in		al, dx
	mov		ax, 0x1be2
	mov		ds, ax
	mov		ax, word [0x5b0]
	inc		ax
	cmp		ax, word [0x5b4]
	jb		loc_2C61
	mov		ax, 0

loc_2C61:
	mov		word [0x5b0], ax
	mov		ax, word [0x5b6]
	inc		ax
	cmp		ax, 3
	jb		loc_2C70
	mov		ax, 0

loc_2C70:
	mov		word [0x5b6], ax
	shl		ax, 2
	mov		si, ax
	mov		ax, word [si + 0x5b8]
	mov		bx, word [si + 0x5ba]
	call	sub_2BE2
	mov		al, 0x20
	out		0x20, al
	pop		ds
	popaw
	iret


;
;
;
sub_2C8A:								; 2C8A
	cmp		byte [0x5ae], 0
	je		ret_2CE8
	cli
	mov		ax, word [0x5b6]
	mov		si, word [0x5b0]
	sti
	cmp		si, word [0x5b2]
	je		ret_2CE8
	mov		word [0x5b2], si
	and		si, si
	js		ret_2CE8
	dec		ax
	jns		loc_2CAE
	add		ax, 3

loc_2CAE:
	shl		ax, 2
	mov		bx, 0x5b8
	add		bx, ax
	mov		es, [bx]
	shl		si, 2
	mov		cx, [si + 0x5c6]
	mov		[bx + 2], cx
	mov		si, [si + 0x5c4]
	mov		di, 0
	mov		dl, byte [0x5ae]
	cmp		dl, 0x40
	jb		loc_2CD4
	mov		dl, 0x3f

loc_2CD4:
	shl		dl, 1
	push	ds
	mov		ds, [word_2AF7]

loc_2CDB:
	lodsb
	sub		al, 0x80
	imul	dl
	mov		al, ah
	add		al, 0x80
	stosb
	loop	loc_2CDB
	pop		ds

ret_2CE8:
	ret


loc_2CE9:
	mov		si, [di + 6]
	and		si, si
	jne		loc_2CF1
	ret

loc_2CF1:
	cmp		word [di + 8], 7FFFh
	je		loc_2D09
	cmp		word [di + 8], 0
	jne		loc_2D01
	jmp		loc_2DA6

loc_2D01:
	dec		word [di + 8]
	jne		loc_2D09
	dec		word [di + 8]

loc_2D09:
	mov		bh, 0
	cmp		byte [di + 11], 0
	je		loc_2D43
	mov		bl, [di + 10]
	dec		byte [di + 11]
	jne		loc_2D3A
	inc		bx
	cmp		bl, [si + 2]
	jb		loc_2D2D
	mov		bl, [si + 3]
	cmp		bl, [si + 2]
	jb		loc_2D2D
	mov		byte [di + 11], 0
	jmp		loc_2D43

loc_2D2D:
	mov		[di + 10], bl
	shl		bx, 1
	mov		al, [bx + si + 6]
	shr		bx, 1
	mov		[di + 11], al

loc_2D3A:
	shl		bx, 1
	mov		al, [bx + si + 7]
	cwde
	add		word [di + 14], ax

loc_2D43:
	mov		ax, 0
	cmp		byte [di + 13], 0
	je		loc_2D6A
	mov		bl, [di + 12]
	inc		bx
	cmp		bl, [si + 4]
	jb		loc_2D63
	mov		bl, [si + 5]
	cmp		bl, [si + 4]
	jb		loc_2D63
	mov		byte [di + 13], 0
	jmp		loc_2D6A

loc_2D63:
	mov		[di + 12], bl
	mov		al, [bx + si + 16]
	cwde

loc_2D6A:
	add		ax, [di + 14]
	add		ax, [di + 16]
	cmp		ax, 0x180
	jae		ret_2DA5
	mov		cl, 0x30
	div		cl
	mov		ch, al
	shl		ch, 2
	cmp		word [di + 8], 0
	jl		loc_2D87
	or		ch, 0x20

loc_2D87:
	mov		bl, ah
	mov		bh, 0
	shl		bx, 1
	mov		cl, 0
	or		cx, [bx + 0xc77]
	mov		ah, [di]
	add		ah, 0xa0
	mov		al, cl
	call	sub_258F
	add		ah, 0x10
	mov		al, ch
	call	sub_258F

ret_2DA5:
	ret

loc_2DA6:
	mov		al, [si]
	cbw
	add		al, [si - 1]
	adc		ah, 0
	mov		word [di + 14], ax
	mov		word [di + 16], 0
	mov		ah, 0
	mov		al, byte [si + 1]
	and		ax, ax
	jne		loc_2DC3
	mov		ax, 7FFFh

loc_2DC3:
	mov		[di + 8], ax
	mov		byte [di + 11], 0
	mov		byte [di + 13], 0
	cmp		byte [si + 2], 0
	je		loc_2DDC
	mov		byte [di + 10], 0xfe ; -2
	mov		byte [di + 11], 1

loc_2DDC:
	cmp		byte [si + 4], 0
	je		loc_2DEA
	mov		byte [di + 12], 0xfe ; -2
	mov		byte [di + 13], 1

loc_2DEA:
	jmp		loc_2D09
