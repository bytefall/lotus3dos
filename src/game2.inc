;
; Draws black frame for "ahead HUD" in 2PL mode.
;
sub_9242:								; 9242
	mov		ax, 0E0E0h					; blackblack
	mov		cx, 24
	rep stosw
	mov		cx, 12
	add		di, 335

loc_9251:
	mov		[es:di], al
	add		di, 336
	loop	loc_9251
	dec		di
	mov		cx, 24
	std
	rep stosw
	cld
	sub		di, 334
	mov		cx, 12

loc_9269:
	mov		[es:di], al
	sub		di, 336
	loop	loc_9269
	add		di, 337
	ret


;
;
;
sub_9277:								; 9277
	mov		dl, 100
	div		dl
	push	ax
	call	sub_9282
	pop		ax
	mov		al, ah

sub_9282:
	mov		ah, 0
	mov		dl, 10
	div		dl
	push	ax
	call	sub_928F
	pop		ax
	mov		al, ah

sub_928F:
	xchg	ax, cx
	mov		ch, 1
	call	bmp_draw
	add		ax, 8
	xchg	ax, cx
	ret

sub_929A:								; 929A
	mov		di, 0
	jmp		loc_92CE


;
; P2: Updates screen.
;
sub_929F:								; 929F
	mov		di, 336 * 99 + 16			; 0x73A8
	jmp		loc_92CE


;
;
;
sub_92A4:								; 92A4
	mov		bx, [word_63BC]
	mov		es, bx
	mov		di, 1360
	mov		ax, 0
	mov		cx, 16800
	rep stosw
	mov		di, 1360
	add		bx, 2100
	mov		es, bx
	mov		cx, 16800
	rep stosw
	ret


;
;
;
update_screen:							; 92C4
	mov		di, 0
	mov		dx, 200
	call	vga_draw
	ret


loc_92CE:
	mov		dx, [word_633A]


; input:
; word_63BC - video data
; dx - height
; di - offset
vga_draw:								; 92D2
	push	ds
	mov		ax, 0A000h
	mov		es, ax
	shr		dx, 1
	mov		ds, [word_63BC]				; video memory for A000
	mov		si, 1360					; const x-offset = 1360
	push	dx
	call	word [cs:off_92FD]			; 9303, 9325
	pop		dx
	mov		cx, si
	and		si, 0Fh
	shr		cx, 4
	mov		ax, ds
	add		ax, cx
	mov		ds, ax
	call	word [cs:off_92FD]			; 9325
	pop		ds
	ret


off_92FD:
	dw sub_9303
	dw sub_9319
	dw sub_9325


sub_9303:
	push	bx
	mov		bx, [cs:word_D379]
	mov		bx, [cs:bx - 6D01h]
	mov		[cs:off_92FD], bx
	pop		bx
	jmp		word [cs:off_92FD]			; cs:9325


sub_9319:								; 9319
	mov		cx, 160
	rep movsw
	add		si, 16
	dec		dx
	jnz		sub_9319
	ret


sub_9325:								; 9325
	mov		cx, 80
	rep movsd
	add		si, 16
	dec		dx
	jnz		sub_9325
	ret


;
;
;
clear_screen:							; 9332
	mov		ax, 0A000h
	mov		es, ax
	mov		ax, 0
	mov		di, ax
	mov		cx, 32000
	rep stosw
	ret


loc_9342:								; 9342
	push	ax
	push	bx
	push	cx
	push	si
	push	di
	push	word [word_637A]
	mov		ax, [word_2060]
	mov		bh, 0
	mov		bl, ah
	mov		ah, al
	mov		al, 0
	shl		ax, 1
	rcl		bx, 1
	shl		ax, 1
	rcl		bx, 1
	shl		ax, 1
	rcl		bx, 1
	shl		ax, 1
	rcl		bx, 1
	mov		si, [word_3ED8]
	add		ax, [si + 134]
	adc		bx, [si + 132]
	cmp		word [is_circular_track], 0
	jz		loc_937F
	mov		bl, [bx + arr_7856]
	mov		bh, 0

loc_937F:
	shl		bx, 4
	mov		si, 8156h
	cmp		byte [bx + si + 10], 0
	jns		loc_9397
	mov		ax, [word_2060]
	mov		bx, [word_2062]
	mov		bh, 0FDh
	call	sub_94C0

loc_9397:
	mov		word [word_2060], 0FFFFh
	pop		word [word_637A]
	pop		di
	pop		si
	pop		cx
	pop		bx
	pop		ax
	ret


;
;
;
sub_93A7:								; 93A7
	push	si
	push	di
	push	word [word_637A]
	mov		ax, [word_1FF4]
	mov		cx, [word_1FF6]
	mov		bx, [word_1FF8]
	mov		si, ax
	shl		si, 1
	mov		bp, [si + arr_6AC2]
	mov		[word_636E], bp
	and		bp, bp
	js		loc_93E5
	mov		bp, [word_1FFA]
	mov		word [word_2208], bp
	mov		word [word_2110], 0
	mov		word [word_3CE6], 99h
	call	sub_946A
	mov		word [word_3CE6], 0

loc_93E5:
	pop		word [word_637A]
	pop		di
	pop		si
	push	si
	push	di
	push	word [word_637A]
	call	sub_8DBC
	pop		word [word_637A]
	pop		di
	pop		si
	ret


;
;
;
sub_93FB:								; 93FB
	mov		ax, [word_1FFE]
	mov		[word_221C], ax
	mov		cx, [word_2000]
	mov		bx, [word_2002]
	mov		si, ax
	shl		si, 1
	mov		bp, [si + arr_6AC2]
	mov		[word_636E], bp
	and		bp, bp
	js		ret_942A
	mov		bp, [word_2004]
	mov		[word_2208], bp
	mov		word [word_2110], 0
	call	sub_946A

ret_942A:
	ret


;
;
;
sub_942B:								; 942B
	mov		ax, [word_200E]
	mov		bx, ax
	cbw
	mov		word [word_2214], ax
	and		word [word_2214], 0FFF8h
	mov		cx, bx
	and		bx, 3
	mov		[word_2208], bx
	mov		cl, 0
	mov		[word_2110], cx
	mov		ax, [word_2008]
	mov		[word_221C], ax
	mov		cx, [word_200A]
	mov		bx, [word_200C]
	mov		si, ax
	shl		si, 1
	mov		bp, [si + arr_6AC2]
	mov		[word_636E], bp
	and		bp, bp
	js		ret_9469
	call	sub_946A

ret_9469:
	ret


;
;
;
sub_946A:								; 946A
	mov		di, [word_3ED8]
	mov		bp, [di + 122]
	mov		[word_21FC], bp
	mov		bp, [di + 136]
	mov		[word_2202], bp
	mov		bp, [di + 132]
	mov		[word_21FE], bp
	mov		bp, [di + 134]
	mov		[word_2200], bp
	mov		word [word_637A], 0
	mov		di, [word_2E7C]
	mov		bp, [word_2110]
	mov		[word_6362], bp
	mov		word [word_2114], 0
	cmp		word [word_3CE6], 0
	jz		loc_94B6
	mov		di, [word_2DB8]
	mov		word [word_2208 + 1], 0FFFFh

loc_94B6:
	jmp		sub_9A1E


;
; Draws all objects.
;
sub_94B9:								; 94B9
	mov		ax, [word_1FEE]
	mov		bx, [word_1FF0]


sub_94C0:								; 94C0
	mov		[word_2112], bx
	mov		cl, bh
	mov		ch, 0
	mov		[word_2114], cx
	shl		bl, 1
	sbb		bh, bh
	shl		bx, 3
	mov		si, ax
	shl		si, 1
	mov		bp, [si + arr_69C2]
	mov		[word_636E], bp
	and		bp, bp
	js		ret_94EA
	mov		cx, [word_1FEC]
	call	sub_94EB

ret_94EA:
	ret


;
;
;
sub_94EB:								; 94EB
	mov		di, [word_3ED8]
	mov		bp, [di + 122]
	mov		[word_21FC], bp
	mov		bp, [di + 136]
	mov		[word_2202], bp
	mov		bp, [di + 132]
	mov		[word_21FE], bp
	mov		bp, [di + 134]
	mov		[word_2200], bp
	cmp		word [word_2114], 8Ah
	jne		loc_953B
	cmp		word [is_circular_track], 0
	jz		loc_953B
	mov		bp, [di + 218]
	cmp		bp, 0
	jl		loc_9535
	inc		bp
	cmp		bp, [num_of_tracks]
	jb		loc_953B
	mov		word [word_2114], 137
	jmp		loc_953B

loc_9535:
	mov		word [word_2114], 136

loc_953B:
	mov		word [word_637A], 0
	mov		word [word_637C], 0
	mov		di, [word_2114]
	shl		di, 1
	mov		di, [di + 2C76h]
	mov		word [word_6362], 0
	mov		word [word_2208], 0FFFFh
	mov		bp, [word_2114]
	cmp		bp, 64
	jns		loc_9569
	jmp		loc_9789

loc_9569:
	cmp		bp, 218
	jne		loc_9572
	jmp		loc_97A4

loc_9572:
	cmp		bp, 160
	jne		loc_957B
	jmp		loc_9619

loc_957B:
	cmp		bp, 155
	jne		loc_9584
	jmp		loc_9999

loc_9584:
	cmp		bp, 219
	jne		loc_958D
	jmp		loc_97FD

loc_958D:
	cmp		bp, 150
	jne		loc_9596
	jmp		loc_9910

loc_9596:
	cmp		bp, 226
	jne		loc_959F
	jmp		loc_9910

loc_959F:
	cmp		bp, 136
	js		loc_95F1
	cmp		bp, 139
	jns		loc_95F1
	mov		bx, 0
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
	call	sub_9A1E					; Draws START banner.
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
	call	sub_95F4
	mov		word [word_2208], 0FF00h
	jmp		loc_9A4B

loc_95F1:
	jmp		sub_9A1E					; Draws objects one-by-one.


;
;
;
sub_95F4:								; 95F4
	cmp		word [word_63A0], 0
	jnz		loc_9603
	cmp		word [word_639E], 0
	jnz		loc_960E
	ret

loc_9603:
	mov		di, [word_2114]
	shl		di, 1
	mov		di, [di + 2CBAh]
	ret

loc_960E:
	mov		di, [word_2114]
	shl		di, 1
	mov		di, [di + 2CF2h]
	ret


;
;
;
loc_9619:								; 9619
	mov		word [word_2212], 0FFFFh
	sub		bx, [word_3EE6]
	shl		bx, 4
	and		bx, 1FFFh
	sub		bx, 1000h
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
	call	sub_9A1E
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
	cmp		word [word_2212], 0
	jns		loc_966F
	jmp		ret_9788

loc_966F:
	push	word [word_2212]
	push	word [word_220C]
	cmp		word [word_636E], 9
	js		loc_9681
	jmp		loc_974B

loc_9681:
	mov		di, [word_2DB2]
	mov		bx, [word_220E]
	mov		cx, [word_2212]
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
	call	sub_9CA1
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
	mov		di, [word_2DB0]
	pop		bx
	mov		cx, [word_2212]
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
	call	sub_9CB1
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
	push	word [word_220C]
	mov		di, [word_2DB4]
	mov		bx, [word_220C]
	mov		cx, [word_2210]
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
	call	sub_9CA1
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

 loc_974B:
	mov		di, [word_2DAE]
	pop		bx
	pop		cx
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
	call	sub_9CB1
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

ret_9788:
	ret


loc_9789:								; 9789
	mov		di, 184
	xchg	di, [word_2114]
	shl		di, 1
	mov		di, [di + 2116h]
	shl		di, 8
	mov		[word_6362], di
	mov		di, [word_2DE6]
	jmp		sub_9A1E


loc_97A4:
	push	ax
	push	dx
	mov		ax, bx
	shl		bx, 4
	add		bx, [word_3EE8]
	and		bx, 1FFFh
	sub		bx, 1000h
	push	bx
	and		ax, 3
	add		ax, 2
	imul	bx
	mov		bx, ax
	sar		bx, 2
	pop		ax
	and		ax, 3FFh
	cmp		ax, 512
	js		loc_97D1
	xor		ax, 3FFh

loc_97D1:
	mul		word [word_3EEA]
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
	shr		dx, 1
	rcr		ax, 1
	mov		[word_6362], ax
	pop		dx
	pop		ax
	jmp		sub_9A1E

loc_97FD:
	push	bx
	mov		bx, 0FE00h
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
	call	sub_9A1E
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
	push	word [word_220E]
	mov		di, [word_2E2E]
	neg		bx
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
	call	sub_9A1E
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
	mov		bp, [word_220C]
	mov		[word_6362], bp
	pop		cx
	push	si
	mov		si, [word_220A]
	shl		si, 1
	mov		dx, [si + 2196h]
	add		dx, [word_2210]
	mov		[word_6366], dx
	add		dx, [si + 21B8h]
	xchg	dx, [word_6366]
	pop		si
	mov		word [word_2206], 0Fh
	pop		ax
	add		ax, [word_3EE6]
	and		ax, 38h
	jnz		ret_990F
	push	bx
	mov		bx, [word_1FEE]
	xor		bx, 7Fh
	shr		bx, 1
	mov		ax, 115
	call	sub_50B4
	pop		bx
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
	call	sub_A51E
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
	push	si
	mov		si, [word_220A]
	shl		si, 1
	mov		ax, [si + 21DAh]
	pop		si
	and		ax, ax
	jz		ret_990F
	add		dx, ax
	add		[word_6366], ax
	call	sub_A51E

ret_990F:
	ret


loc_9910:
	push	word [word_2114]
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
	mov		word [word_2114], 223
	mov		bx, 0FF20h
	mov		di, [word_2E34]
	call	sub_9A1E
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
	pop		word [word_2114]
	pusha
	call	sub_7545
	popa
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
	call	sub_9A1E
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
	ret


loc_9999:
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
	call	sub_9A1E
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
	mov		cx, [word_2210]
	mov		bx, [word_220C]
	add		bx, [word_220E]
	sar		bx, 1
	sub		bx, 160
	mov		di, [word_2DAA]
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
	ret


;
;
;
sub_9A1E:								; 9A1E
	mov		bp, [word_6362]
	mov		[word_2204], bp
	mov		bp, [word_2114]
	cmp		bp, 88h
	jb		loc_9A4B
	cmp		bp, 8Ah
	jbe		loc_9A42
	cmp		bp, 0FAh
	jb		loc_9A4B
	cmp		bp, 0FDh
	ja		loc_9A4B

loc_9A42:
	mov		word [word_2208], 0FFFEh
	mov		bx, 0

loc_9A4B:
	cmp		ax, 64
	jb		loc_9A53
	jmp		loc_9B03

loc_9A53:
	cmp		word [word_2208], 0FFFEh
	jnz		loc_9A5D
	jmp		loc_9B03

loc_9A5D:
	dec		word [word_21FC]
	cmp		word [word_2114], 0FDh
	jz		loc_9A70
	cmp		ax, [word_21FC]
	jb		loc_9A7A
	ret

loc_9A70:
	cmp		ax, [word_21FC]
	jb		loc_9A7A
	mov		ax, [word_21FC]
	dec		ax

loc_9A7A:
	shr		cx, 1
	mov		dx, cx
	shl		ax, 1
	mov		si, ax
	shl		si, 2
	add		si, arr_C568
	mov		bp, [si + 4]
	mov		[word_2218], bp
	mov		bp, [si + 6]
	mov		[word_221A], bp
	mov		cx, [si + 8]
	mov		bp, [si]
	sub		cx, bp
	push	ax
	push	dx
	mov		ax, dx
	imul	cx
	shl		ax, 1
	rcl		dx, 1
	mov		cx, dx
	pop		dx
	pop		ax
	add		cx, bp
	sub		bx, [word_2202]
	shl		bx, 2
	sub		bx, cx
	mov		cx, [si + 10]
	mov		bp, [si + 2]
	sub		cx, bp
	push	ax
	push	dx
	mov		ax, dx
	imul	cx
	shl		ax, 1
	rcl		dx, 1
	mov		cx, dx
	pop		dx
	pop		ax
	add		cx, bp
	mov		si, arr_68C2
	add		si, ax
	mov		bp, [si]
	mov		[word_2216], bp
	mov		ax, [si + 2]
	mov		bp, [si]
	sub		ax, bp
	push	dx
	imul	dx
	shl		ax, 1
	rcl		dx, 1
	mov		ax, dx
	add		ax, bp
	shl		ax, 2
	imul	bx
	mov		bx, dx
	pop		dx
	mov		bp, [word_633A]
	sub		bp, 2
	cmp		cx, bp
	jb		loc_9B63
	mov		cx, bp
	jmp		loc_9B63

loc_9B03:
	cmp		word [word_2114], 0FDh
	jz		loc_9B12
	cmp		ax, [word_21FC]
	jb		loc_9B1C
	ret

loc_9B12:
	cmp		ax, [word_21FC]
	jb		loc_9B1C
	mov		ax, [word_21FC]
	dec		ax

loc_9B1C:
	shl		ax, 1
	mov		si, ax
	shl		si, 2
	add		si, arr_C568
	mov		bp, [si + 4]
	mov		[word_2218], bp
	mov		bp, [si + 6]
	mov		[word_221A], bp
	sub		bx, [word_2202]
	shl		bx, 3
	sar		bx, 1
	sub		bx, [si]
	mov		cx, [si + 2]
	mov		si, arr_68C2
	add		si, ax
	mov		ax, [si]
	mov		[word_2216], ax
	shl		ax, 2
	push	dx
	imul	bx
	mov		bx, dx
	pop		dx
	mov		bp, [word_633A]
	sub		bp, 2
	cmp		cx, bp
	jb		loc_9B63
	mov		cx, bp

loc_9B63:
	cmp		cx, [word_2218]
	jns		loc_9B6D
	mov		[word_2218], cx

loc_9B6D:
	mov		ax, [word_2204]
	and		ax, ax
	jz		loc_9B81
	push	dx
	imul	word [word_2216]
	mov		ax, dx
	pop		dx
	sar		ax, 5
	sub		cx, ax

loc_9B81:
	cmp		word [word_2114], 82h
	jnz		loc_9B9D
	mov		ax, [word_2216]
	shr		ax, 5
	sub		cx, ax
	js		loc_9B9D
	cmp		cx, [word_1FD4]
	jae		loc_9B9D
	mov		[word_1FD4], cx

loc_9B9D:
	cmp		word [word_2208], 0FFFEh
	jnz		loc_9BA7
	jmp		sub_9CC5

loc_9BA7:
	cmp		di, [word_2DB8]
	jz		loc_9BB6
	cmp		di, [word_2E7C]
	jz		loc_9BB6
	jmp		sub_9CC5

loc_9BB6:
	mov		bp, [word_636E]
	mov		[word_6370], bp
	shl		bp, 3
	add		[word_636E], bp
	mov		bp, bx
	neg		bp
	add		bp, 144
	sar		bp, 2
	mov		ax, [word_4026]
	cmp		ax, [word_2208]
	jz		loc_9BE9
	cmp		word [num_of_players], 0
	jz		loc_9BED
	mov		ax, [word_4120]
	cmp		ax, [word_2208]
	jnz		loc_9BED

loc_9BE9:
	add		bp, [word_2214]

loc_9BED:
	mov		ax, [word_221A]
	sar		ax, 2
	sub		bp, ax
	sar		bp, 3
	and		bp, bp
	jg		loc_9BFF
	mov		bp, 0

loc_9BFF:
	cmp		bp, 8
	jb		loc_9C07
	mov		bp, 8

loc_9C07:
	add		bp, [word_636E]
	add		bp, [word_3CE6]
	mov		bp, [ds:bp + 221Eh]
	and		bp, 0FFh
	mov		[word_636E], bp
	cmp		word [word_639E], 0
	jz		loc_9C70
	cmp		bp, 9
	js		loc_9C70
	mov		ax, [word_2200]
	mov		bp, [word_21FE]
	shl		ax, 1
	rcl		bp, 1
	shl		ax, 1
	rcl		bp, 1
	shl		ax, 1
	rcl		bp, 1
	shl		ax, 1
	rcl		bp, 1
	mov		ax, bp
	add		ax, [word_221C]
	shr		ax, 4
	cmp		word [is_circular_track], 0
	jz		loc_9C57
	mov		si, ax
	mov		al, [si + arr_7856]
	mov		ah, 0

loc_9C57:
	shl		ax, 4
	mov		si, ax
	cmp		byte [si - 7EA0h], 0
	jns		loc_9C70
	mov		ax, [word_6370]
	mov		ah, 10
	mul		ah
	neg		ax
	mov		[cs:word_A1D2], ax

loc_9C70:
	call	sub_9CC5
	mov		word [cs:word_A1D2], 0
	ret


;
;
;
sub_9C7B:								; 9C7B
	cmp		di, 0
	jz		loc_9C9E
	mov		si, [word_636E]
	mov		[word_220A], si
	shl		si, 3
	mov		es, di
	mov		ax, [es:si + 2]
	mov		[word_6362], ax
	mov		dx, [es:si + 4]
	mov		si, [es:si]
	add		si, di
	ret

loc_9C9E:
	mov		si, di
	ret


;
;
;
sub_9CA1:								; 9CA1
	call	sub_9C7B
	mov		[word_636E], cx
	sub		cx, dx
	inc		cx
	mov		[word_6366], cx
	jmp		loc_9D1E


;
;
;
sub_9CB1:								; 9CB1
	call	sub_9C7B
	mov		[word_636E], cx
	sub		cx, dx
	inc		cx
	mov		[word_6366], cx
	sub		bx, [word_6362]
	jmp		loc_9D1E


;
;
;
sub_9CC5:								; 9CC5
	cmp		word [word_2208], 0FF00h
	jnz		loc_9CFB
	mov		word [word_2208], 0FFFFh
	call	sub_9C7B
	add		bx, 160
	mov		bp, [word_2350]
	mov		ax, dx
	shr		ax, 1
	add		bp, ax
	mov		[word_636E], bp
	dec		word [word_636E]
	sub		bp, dx
	mov		[word_6366], bp
	mov		ax, [word_6362]
	sar		ax, 1
	sub		bx, ax
	jmp		loc_9D1E

loc_9CFB:
	cmp		word [word_2208], 0FFFEh
	jnz		loc_9D05
	jmp		loc_A27F

loc_9D05:
	call	sub_9C7B
	add		bx, 160
	mov		[word_636E], cx
	sub		cx, dx
	inc		cx
	mov		[word_6366], cx
	mov		ax, [word_6362]
	sar		ax, 1
	sub		bx, ax

loc_9D1E:
	mov		[word_220C], bx
	mov		cx, bx
	add		cx, [word_6362]
	mov		[word_220E], cx
	mov		bp, [word_6366]
	mov		[word_2210], bp
	mov		bp, [word_636E]
	mov		[word_2212], bp
	cmp		word [word_2114], 0DFh
	jne		loc_9D47
	jmp		ret_9F32

loc_9D47:
	and		si, si
	jnz		loc_9D4E
	jmp		ret_9F32

loc_9D4E:
	cmp		word [word_2114], 150
	je		loc_9D61
	cmp		word [word_2114], 226
	je		loc_9D61
	jmp		loc_9E01

loc_9D61:
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
	cmp		word [word_1FEE], 14h
	jns		loc_9DA1
	mov		cx, [word_220E]
	mov		word [word_6362], 140h
	mov		dx, [word_2210]
	mov		bp, [word_2212]
	mov		[word_6366], bp
	mov		word [word_2206], 10
	call	sub_A51E

loc_9DA1:
	cmp		word [word_1FD6], 0
	js		loc_9DCF
	mov		cx, [word_1FD6]
	mov		bp, [word_220E]
	add		bp, 0Fh
	and		bp, 0FFF0h
	mov		[word_6362], bp
	mov		dx, [word_1FD8]
	mov		bp, [word_1FDA]
	mov		[word_6366], bp
	mov		word [word_2206], 10
	call	sub_A51E

loc_9DCF:
	mov		bp, [word_220E]
	mov		[word_1FD6], bp
	mov		bp, [word_2210]
	mov		[word_1FD8], bp
	mov		bp, [word_2212]
	mov		[word_1FDA], bp
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

loc_9E01:
	pusha
	push	ds
	push	es
	mov		ds, [cs:word_5162]
	push	word [word_6352]
	push	word [word_6354]
	push	word [word_6356]
	push	word [word_6358]
	push	word [word_635A]
	push	word [word_635C]
	push	word [word_635E]
	push	word [word_6360]
	push	word [word_6362]
	push	word [word_6364]
	push	word [word_6366]
	push	word [word_6368]
	push	word [word_636A]
	push	word [word_636C]
	push	word [word_636E]
	push	word [word_6370]
	push	word [word_6372]
	push	word [word_6374]
	push	word [word_6376]
	push	word [word_6378]
	push	word [word_637A]
	push	word [word_637C]
	push	word [word_637E]
	push	word [word_6380]
	push	word [word_6382]
	push	word [word_6384]
	push	word [word_6386]
	push	word [word_6388]
	push	word [word_638A]
	push	word [word_638C]
	push	word [word_638E]
	push	word [word_6390]
	mov		ax, [word_2208]
	cmp		ax, 3
	jb		loc_9E94
	mov		ax, 0

loc_9E94:
	mov		[cs:word_A1D0], ax
	mov		ax, [word_220C]
	mov		bx, [word_220E]
	mov		cx, [word_2210]
	mov		dx, [word_2212]
	call	sub_9F33
	mov		ds, [cs:word_5162]
	pop		word [word_6390]
	pop		word [word_638E]
	pop		word [word_638C]
	pop		word [word_638A]
	pop		word [word_6388]
	pop		word [word_6386]
	pop		word [word_6384]
	pop		word [word_6382]
	pop		word [word_6380]
	pop		word [word_637E]
	pop		word [word_637C]
	pop		word [word_637A]
	pop		word [word_6378]
	pop		word [word_6376]
	pop		word [word_6374]
	pop		word [word_6372]
	pop		word [word_6370]
	pop		word [word_636E]
	pop		word [word_636C]
	pop		word [word_636A]
	pop		word [word_6368]
	pop		word [word_6366]
	pop		word [word_6364]
	pop		word [word_6362]
	pop		word [word_6360]
	pop		word [word_635E]
	pop		word [word_635C]
	pop		word [word_635A]
	pop		word [word_6358]
	pop		word [word_6356]
	pop		word [word_6354]
	pop		word [word_6352]
	pop		es
	pop		ds
	popa

ret_9F32:
	ret


sub_9F33:
	cmp		ax, 320
	jl		loc_9F3B
	jmp		ret_A061

loc_9F3B:
	cmp		bx, 0
	jg		loc_9F43
	jmp		ret_A061

loc_9F43:
	cmp		cx, [word_2218]
	jl		loc_9F4C
	jmp		ret_A061

loc_9F4C:
	cmp		dx, 0
	jg		loc_9F54
	jmp		ret_A061

loc_9F54:
	mov		bp, bx
	sub		bp, ax
	add		bp, 7
	shr		bp, 3
	jnz		loc_9F63
	jmp		ret_A061

loc_9F63:
	mov		[cs:word_A1CC], bp
	mov		bp, 0
	mov		di, 0
	cmp		ax, 0FFF8h
	jg		loc_9F7D

loc_9F73:
	add		ax, 8
	inc		bp
	inc		di
	cmp		ax, 0FFF8h
	jle		loc_9F73

loc_9F7D:
	cmp		bx, 328
	jl		loc_9F8D

loc_9F83:
	sub		bx, 8
	inc		di
	cmp		bx, 328
	jge		loc_9F83

loc_9F8D:
	cmp		cx, 0
	jge		loc_9FA1
	xchg	ax, cx
	neg		ax
	mul		byte [cs:word_A1CC]
	add		bp, ax
	mov		ax, cx
	mov		cx, 0

loc_9FA1:
	cmp		dx, [word_2218]
	jle		loc_9FAB
	mov		dx, [word_2218]

loc_9FAB:
	mov		[cs:word_A1CE], di
	sub		[cs:word_A1CC], di
	jg		loc_9FBA
	jmp		ret_A061

loc_9FBA:
	sub		dx, cx
	jge		loc_9FC1
	jmp		ret_A061

loc_9FC1:
	inc		dx
	mov		di, 550h
	add		di, ax
	mov		al, 168
	mul		cl
	mov		cx, ax
	shl		ax, 1
	and		ax, 0Fh
	add		di, ax
	mov		ax, di
	and		di, 0Fh
	shr		ax, 4
	shr		cx, 3
	add		ax, cx
	add		ax, [word_63BC]
	mov		es, ax
	mov		[word_2352], di
	mov		[word_2354], es
	mov		ds, si
	mov		si, 0
	mov		cx, bp
	jcxz	loc_A005
	mov		ah, 0

loc_9FFA:
	lodsb
	mov		bp, ax
	mov		al, [bp + 0C00h]
	add		si, ax
	loop    loc_9FFA

loc_A005:
	mov		ch, dl
	mov		dx, [cs:word_A1CC]
	shl		dx, 3
	neg		dx
	add		dx, 336
	mov		bx, [cs:word_A1D2]
	and		bx, bx
	jz		loc_A021
	jmp		loc_A106

loc_A021:
	mov		bx, [cs:word_A1D0]
	and		bx, bx
	jnz		loc_A062
	mov		bx, loc_A04E
	cmp		word [cs:word_A1CE], 0
	jz		loc_A054
	mov		bx, loc_A03A
	jmp		loc_A054

loc_A03A:
	mov		cl, byte [cs:word_A1CE]
	mov		ah, 0

loc_A041:
	lodsb
	mov		bp, ax
	mov		al, [bp + 0C00h]
	add		si, ax
	dec		cl
	jne		loc_A041

loc_A04E:
	add		di, dx
	dec		ch
	je		ret_A061

loc_A054:
	mov		cl, byte [cs:word_A1CC]
	mov		ah, 0
	lodsb
	shl		ax, 5						; 0x7F0B * 32
	jmp		ax							; 0x7F0E

ret_A061:
	ret


loc_A062:
	xchg	bl, bh
	add		bx, 0D00h

loc_A068:
	mov		cl, [cs:word_A1CC]

loc_A06D:
	lodsb
	mov		ah, al
	shl		ah, 1
	jae		loc_A07D
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	mov		[es:di], al

loc_A07D:
	inc		di
	shl		ah, 1
	jae		loc_A08B
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	mov		[es:di], al

loc_A08B:
	inc		di
	shl		ah, 1
	jae		loc_A099
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	mov		[es:di], al

loc_A099:
	inc		di
	shl		ah, 1
	jae		loc_A0A7
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	mov		[es:di], al

loc_A0A7:
	inc		di
	shl		ah, 1
	jae		loc_A0B5
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	mov		[es:di], al

loc_A0B5:
	inc		di
	shl		ah, 1
	jae		loc_A0C3
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	mov		[es:di], al

loc_A0C3:
	inc		di
	shl		ah, 1
	jae		loc_A0D1
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	mov		[es:di], al

loc_A0D1:
	inc		di
	shl		ah, 1
	jae		loc_A0DF
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	mov		[es:di], al

loc_A0DF:
	inc		di
	dec		cl
	jnz		loc_A06D
	mov		cl, [cs:word_A1CE]
	and		cl, cl
	jz		loc_A0FC
	mov		ah, 0

loc_A0EF:
	lodsb
	mov		bp, ax
	mov		al, [bp + 0C00h]
	add		si, ax
	dec		cl
	jnz		loc_A0EF

loc_A0FC:
	add		di, dx
	dec		ch
	jz		ret_A105
	jmp		loc_A068

ret_A105:
	ret

loc_A106:
	mov		[cs:word_A1D4], dx
	mov		dx, bx
	mov		bx, [cs:word_A1D0]
	xchg	bl, bh
	add		bx, 0D00h

loc_A118:
	mov		cl, [cs:word_A1CC]

loc_A11D:
	lodsb
	mov		ah, al
	shl		ah, 1
	jae		loc_A12F
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	add		al, dl
	mov		[es:di], al

loc_A12F:
	inc		di
	shl		ah, 1
	jae		loc_A13F
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	add		al, dl
	mov		[es:di], al

loc_A13F:
	inc		di
	shl		ah, 1
	jae		loc_A14F
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	add		al, dl
	mov		[es:di], al

loc_A14F:
	inc		di
	shl		ah, 1
	jae		loc_A15F
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	add		al, dl
	mov		[es:di], al

loc_A15F:
	inc		di
	shl		ah, 1
	jae		loc_A16F
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	add		al, dl
	mov		[es:di], al

loc_A16F:
	inc		di
	shl		ah, 1
	jae		loc_A17F
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	add		al, dl
	mov		[es:di], al

loc_A17F:
	inc		di
	shl		ah, 1
	jae		loc_A18F
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	add		al, dl
	mov		[es:di], al

loc_A18F:
	inc		di
	shl		ah, 1
	jae		loc_A19F
	lodsb
	mov		bl, al
	mov		al, [ss:bx]
	add		al, dl
	mov		[es:di], al

loc_A19F:
	inc		di
	dec		cl
	jz		loc_A1A7
	jmp		loc_A11D

loc_A1A7:
	mov		cl, [cs:word_A1CE]
	and		cl, cl
	jz		loc_A1BF
	mov		ah, 0

loc_A1B2:
	lodsb
	mov		bp, ax
	mov		al, [bp + 0C00h]
	add		si, ax
	dec		cl
	jnz		loc_A1B2

loc_A1BF:
	add		di, [cs:word_A1D4]
	dec		ch
	jz		ret_A1CB
	jmp		loc_A118

ret_A1CB:
	ret
