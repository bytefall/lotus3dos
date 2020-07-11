
; input:
; (ax, bx) - (width, height)
; si - source of data (si:0000)
; di - (y coord on a screen) * 336
draw_sprite:							; C047
	push	ds
	mov		es, [word_63BC]				; video memory for A000
	add		di, 1360					; const x-offset = 1360
	mov		ds, si
	mov		si, 0
	shr		ax, 1

for_each_height1:
	and		di, di
	jns		loc_C067
	mov		cx, es
	add		cx, 2048
	mov		es, cx
	sub		di, 32768					; 320 * 200 + 256 * 3

loc_C067:
	mov		cx, ax
	push	di
	rep movsw
	pop		di
	add		di, 336
	dec		bx
	jnz		for_each_height1
	pop		ds
	ret


; input:
; ax - width
; bx - height
; si - segment of characted data (si:0)
draw_char:								; C076
	push	ds
	mov		es, [word_63BC]				; video memory for A000
	add		di, 1360					; const x-offset = 1360 = 336 * 4 + 16
	mov		ds, si
	mov		si, 0
	mov		bp, ax

for_each_height2:
	and		di, di
	jns		loc_C096
	mov		cx, es
	add		cx, 2048
	mov		es, cx
	sub		di, 32768

loc_C096:
	mov		cx, bp
	push	di

for_each_width2:
	lodsb
	or		[es:di], al
	inc		di
	loop	for_each_width2
	pop		di
	add		di, 336
	dec		bx
	jnz		for_each_height2
	pop		ds
	ret


; Get B{track_num} data with palette.
;
; input:
; track_num - track number
;
; output:
; word_2AFC:0 - data
; word_63BA:0 - palette
; vec_7556 - palette copy
; word_1F99 - length / 640
sub_C0AA:								; C0AA
	mov		ax, [word_63BA]
	mov		[word_2AFC], ax				; B0X resource
	mov		ax, [track_num]
	mov		ah, 'B'
	call	res_load

	sub		ax, 48						; 48 * 16 = 768
	mov		[word_63BA], ax				; word_63BA = ax = *(tail - 768)
	sub		ax, [word_2AFC]				; B0X resource
	cwd
	mov		bp, 40						; 40 * 16 = 640
	div		bp
	mov		[word_1F99], ax				; word_1F99 = ax / 640
	push	ds
	push	ds
	pop		es
	mov		di, palette
	mov		ds, [word_63BA]
	mov		si, 0
	mov		cx, 768
	rep movsb
	pop		ds
	ret


;
;
;
sub_C0DF:								; C0DF
	mov		ax, [word_63BA]
	mov		[word_6330], ax
	call	sub_C1CB
	mov		di, arr_63C2
	mov		cx, 512
	mov		ax, 0
	push	ds
	pop		es
	rep stosw
	les		si, [word_632E]				; load es:si
	mov		ax, [word_2AB6]				; P03
	mov		[word_633E], ax
	mov		[word_6340], ax
	mov		word [word_6344], 0
	mov		word [word_6342], 8

loc_C10E:
	call	sub_C155
	inc		byte [word_6342]
	jnz		loc_C10E
	mov		ax, [word_2AB6]				; P03
	mov		[word_633E], ax
	add		ax, 10
	mov		[word_6340], ax
	mov		word [word_6344], 512
	mov		word [word_6346], 0

loc_C12F:
	mov		bx, [word_6346]
	shl		bx, 1
	mov		ax, [bx + 5ED0h]			; TODO: offset?
	mov		[word_6342], ax
	call	sub_C155
	inc		word [word_6346]
	cmp		word [word_6346], 56
	jnz		loc_C12F
	add		si, 15
	shr		si, 4
	add		[word_63BA], si
	ret


; input:
; word_4A2A -
; word_6340 -
; word_6342 -
; word_6344 -
sub_C155:								; C155
	mov		bx, [word_6342]
	shl		bx, 1
	add		bx, [word_6344]
	mov		[arr_63C2 + bx], si
	mov		ax, 32
	mov		dx, 0
	div		word [word_6342]
	mov		word [word_6354], ax
	mov		ax, 0
	div		word [word_6342]
	mov		word [word_6352], ax
	mov		di, [word_4A2A]
	mov		dx, 0
	mov		bp, 0
	mov		ax, di
	add		ax, [word_6340]
	mov		[word_6366], ax
	add		si, 2

loc_C190:
	mov		bx, bp
	mov		cl, bl
	and		cl, 3
	shl		cl, 1
	mov		al, [di]
	ror		al, 2
	mov		ah, 3Fh
	ror		al, cl
	ror		ah, cl
	shr		bx, 2
	and		ah, [es:bx + si]
	or		al, ah
	mov		[es:bx + si], al
	inc		bp
	add		dx, [word_6352]
	adc		di, [word_6354]
	cmp		di, [word_6366]
	jb		loc_C190
	mov		[es:si - 2], bp
	add		bp, 3
	shr		bp, 2
	add		si, bp
	ret


;
;
;
sub_C1CB:								; C1CB
	push	ds
	pop		es
	mov		di, 7556h
	mov		cx, 768
	mov		al, 3Fh						; scan pallete for value 0x3F
	repne scasb
	dec		di
	mov		[word_2AFE], di				; word_2AFE = pos of 0x3F in palette
	mov		ax, di
	sub		ax, 7556h
	mov		cl, 3
	div		cl
	mov		[byte_2B00], al				; byte_2B00 = num of colors
	mov		word [word_2B02], arr_2B04
	mov		word [word_2C24], 2C26h
	mov		word [word_632E], 0
	mov		si, [word_54CE]
	mov		dx, 32
	cmp		word [word_6398], 0
	jz		loc_C20B
	mov		dx, 288

loc_C20B:
	lodsw
	jmp		loc_C21D

loc_C20E:
	mov		di, [word_54CE]
	mov		cx, si
	sub		cx, di
	shr		cx, 1
	lodsw
	repne scasw
	jz		loc_C231

loc_C21D:
	mov		di, [word_2AFE]
	call	sub_C2A8
	mov		[word_2AFE], di
	mov		al, [byte_2B00]
	inc		byte [byte_2B00]			; increment since in sub_C2A8 we've added 3 more colors
	jmp		loc_C23E

loc_C231:
	sub		di, 2
	sub		di, [word_54CE]
	shr		di, 1
	mov		al, [arr_2B04 + di]

loc_C23E:
	mov		di, [word_2B02]
	stosb								; arr_2B04[i++] = al;
	mov		[word_2B02], di
	mov		al, dl
	and		al, 3
	cmp		al, 2
	jnz		loc_C255
	lodsw
	inc		word [word_2B02]
	dec		dx

loc_C255:
	dec		dx
	jnz		loc_C20E
	mov		cx, 8						; cx = if word_6398 == 0 { 8 } else { 72 };
	cmp		word [word_6398], 0
	jz		loc_C265
	mov		cx, 72

loc_C265:
	mov		bx, arr_2B04
	jmp		loc_C282

loc_C26A:
	mov		ax, [bx]
	mov		dx, [bx + 2]
	mov		si, arr_2B04

loc_C272:
	cmp		ax, [si]
	jnz		loc_C27B
	cmp		dx, [si + 2]
	jz		loc_C28D

loc_C27B:
	add		si, 4
	cmp		si, bx
	jb		loc_C272

loc_C282:
	mov		ax, [word_632E]
	shr		ax, 10
	call	sub_C2C2
	jmp		loc_C298

loc_C28D:
	sub		si, arr_2B04
	shr		si, 2
	mov		al, [si + 2C26h]

loc_C298:
	mov		di, [word_2C24]
	stosb
	mov		[word_2C24], di
	add		bx, 4
	loop	loc_C26A
	ret
	ret									; C2A7


; di[r] = ((ax >> 8) & 0xF) << 2;
; di[g] = ((ax as u8) >> 4) << 2;
; di[b] = ((ax as u8) & 0xF) << 2;
sub_C2A8:								; C2A8
	xchg	al, ah
	and		al, 0Fh
	shl		al, 2
	stosb
	mov		al, ah
	shr		al, 4
	shl		al, 2
	stosb
	mov		al, ah
	and		al, 0Fh
	shl		al, 2
	stosb
	ret


;
;
;
sub_C2C2:								; C2C2
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
	les		di, [632Eh]
	mov		dl, 0

loc_C350:
	mov		dh, dl
	rol		dh, 2
	mov		al, dh
	and		al, 3
	xlatb
	stosb
	rol		dh, 2
	mov		al, dh
	and		al, 3
	xlatb
	stosb
	rol     dh, 2
	mov     al, dh
	and     al, 3
	xlatb
	stosb
	rol		dh, 2
	mov		al, dh
	and		al, 3
	xlatb
	stosb
	inc		dl
	jnz		loc_C350
	mov		al, [bx]
	mov		ah, al
	mov		cx, ax
	cmp		word [word_63B4], 0
	jz		loc_C38F
	mov		cl, [bx + 2]
	mov		ch, cl
	mov		ax, 505h

loc_C38F:
	mov		[es:di - 8], ax
	mov		[es:di - 6], ax
	mov		[es:di - 4], cx
	mov		[es:di - 2], cx
	mov		[word_632E], di
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
	ret
