;
; sub_D3B6
;
sub_D3B6:						; D3B6
	; might not need this code (see set_video_mode_and_timer)
	; sub		ax, ax
	; mov		es, ax
	; mov		[es:word_90], unk_D3DA
	; mov		[es:word_92], cs
	retn


;
; sub_D3C7
;
sub_D3C7:						; D3C7
	; might not need this code (see set_video_mode_and_timer)
	; sub		ax, ax
	; mov		es, ax
	; mov		ax, [word_3D7E]
	; mov		[es:word_90], ax
	; mov		ax, [word_3D80]
	; mov		[es:word_92], ax
	retn


;
; sub_D3DD
;
sub_D3DD:						; D3DD
	call	sub_D3F3
	; might not need this code (see set_video_mode_and_timer)
	; cli
	; sub		ax, ax
	; mov		es, ax
	; mov		ax, sub_D445
	; mov		[es:word_24], ax
	; mov		[es:word_26], cs
	; sti
	retn


;
; sub_D3F3
;
sub_D3F3:						; D3F3
	mov		di, arr_3D88
	push	ds
	pop		es
	sub		ax, ax
	mov		cx, 64
	rep stosw
	retn


;
; sub_D400
;
sub_D400:						; D400
	; might not need this code (see set_video_mode_and_timer)
	; cli
	; sub		ax, ax
	; mov		es, ax
	; mov		ax, [word_3D82]
	; mov		[es:word_24], ax
	; mov		ax, [word_3D84]
	; mov		[es:word_26], ax
	; sti

loc_D414:
	mov		ah, 1
	int		16h					; KEYBOARD - CHECK BUFFER, DO NOT CLEAR
								; Return: ZF clear if character in buffer
								; AH = scan code, AL = character
								; ZF set if no character in buffer
	jz		locret_D420
	mov		ah, 0
	int		16h					; KEYBOARD - READ CHAR FROM BUFFER, WAIT IF EMPTY
								; Return: AH = scan code, AL = character
	jmp		loc_D414

locret_D420:
	retn


;
; sub_D421
;
sub_D421:						; D421
	mov		ax, 0
	xchg	ax, [word_3E08]
	and		ax, ax
	jz		return_no_key
	cmp		al, 0
	jnz		loc_D434
	xchg	al, ah
	or		al, 10000000b

loc_D434:
	and		ax, 11111111b
	cmp		al, 61h ; 'a'
	jb		locret_D441
	cmp		al, 7Ah ; 'z'
	ja		locret_D441
	sub		al, 20h ; ' '

locret_D441:
	retn

return_no_key:
	sub		ax, ax
	retn


;
; sub_D445
;
sub_D445:						; D445
	pusha
	push	ds
	push	es
	; mov		ds, [cs:word_5162]
	in		al, 60h				; AT Keyboard controller 8042.
	mov		bl, al
	mov		al, bl
	sub		al, 80h
	sbb		al, al
	and		bx, 1111111b
	cmp		bl, 60h ; '`'
	jz		loc_D475
	cmp		bl, 2Ah ; '*'
	jz		loc_D475
	mov		[byte_3D86], al
	mov		[byte_3D87], bl
	test	[bx + arr_3D88], al
	js		loc_D475
	mov		[bx + arr_3D88], al

loc_D475:
	cmp		bl, 37h ; '7'
	jz		short loc_D49D
	cmp		bl, 1Dh
	jz		short loc_D49D
	cmp		bl, 7Fh ; ''
	jz		short loc_D49D
	pushf
	call	far [word_3D82]			; E987
	cli

loc_D48A:
	mov		ah, 1
	int		16h					; KEYBOARD - CHECK BUFFER, DO NOT CLEAR
								; Return: ZF clear if character in buffer
								; AH = scan code, AL = character
								; ZF set if no character in buffer
	jz		iret_D499
	mov		ah, 0
	int		16h					; KEYBOARD - READ CHAR FROM BUFFER, WAIT IF EMPTY
								; Return: AH = scan code, AL = character
	mov		[word_3E08], ax
	jmp		loc_D48A

iret_D499:
	pop		es
	pop		ds
	popa
	iret

loc_D49D:
	mov		al, 20h
	out		20h, al				; Interrupt controller, 8259A.
	in		al, 61h				; PC/XT PPI port B bits:
								; 0: Tmr 2 gate --- OR 03H=spkr ON
								; 1: Tmr 2 data -+  AND 0fcH=spkr OFF
								; 3: 1=read high switches
								; 4: 0=enable RAM parity checking
								; 5: 0=enable I/O channel check
								; 6: 0=hold keyboard clock low
								; 7: 0=enable kbrd
	mov		ah, al
	or		al, 80h
	out		61h, al				; PC/XT PPI port B bits:
								; 0: Tmr 2 gate --- OR 03H=spkr ON
								; 1: Tmr 2 data -+  AND 0fcH=spkr OFF
								; 3: 1=read high switches
								; 4: 0=enable RAM parity checking
								; 5: 0=enable I/O channel check
								; 6: 0=hold keyboard clock low
								; 7: 0=enable kbrd
	xchg	ah, al
	out		61h, al				; PC/XT PPI port B bits:
								; 0: Tmr 2 gate --- OR 03H=spkr ON
								; 1: Tmr 2 data -+  AND 0fcH=spkr OFF
								; 3: 1=read high switches
								; 4: 0=enable RAM parity checking
								; 5: 0=enable I/O channel check
								; 6: 0=hold keyboard clock low
								; 7: 0=enable kbrd
	jmp		iret_D499


;
; set_timer
;
set_timer:						; D4AF
	mov		ax, [word_3D7A]
	shr		ax, 2
	sub		ax, 90
	mov		[word_3E12], ax		; timerTick = word_3D7A / 4 - 90
	mov		byte [byte_3E0E], 0
	cli
	mov		cx, [word_3E12]
	mov		al, 110110b
	out		43h, al				; Timer 8253-5 (AT: 8254.2).
	mov		al, cl
	out		40h, al
	mov		al, ch
	out		40h, al
	sub		ax, ax
	mov		es, ax
	mov		ax, sub_D508
	mov		[es:word_20], ax
	mov		[es:tmp_cs], cs
	sti
	retn


;
; Restore timer
;
sub_D4E3:						; D4E3
	cli
	mov		cx, [word_3D78]
	mov		al, 36h
	out		43h, al				; Timer 8253-5 (AT: 8254.2).
	mov		al, cl
	out		40h, al				; Timer 8253-5 (AT: 8254.2).
	mov		al, ch
	out		40h, al				; Timer 8253-5 (AT: 8254.2).
	sub		ax, ax
	mov		es, ax
	mov		ax, [word_3E0A]
	mov		[es:word_20], ax
	mov		ax, [word_3E0C]
	mov		[es:tmp_cs], ax
	sti
	retn


;
; sub_D508
;
sub_D508:						; D508
	pusha
	push	ds
	push	es
	mov		ds, [cs:word_5162]
	push	word ptr ds:6352h
	push	word ptr ds:6354h
	push	word ptr ds:6356h
	push	word ptr ds:6358h
	push	word ptr ds:635Ah
	push	word ptr ds:635Ch
	push	word ptr ds:635Eh
	push	word ptr ds:6360h
	push	word ptr ds:6362h
	push	word ptr ds:6364h
	push	word ptr ds:6366h
	push	word ptr ds:6368h
	push	word ptr ds:636Ah
	push	word ptr ds:636Ch
	push	word ptr ds:636Eh
	push	word ptr ds:6370h
	push	word ptr ds:6372h
	push	word ptr ds:6374h
	push	word ptr ds:6376h
	push	word ptr ds:6378h
	push	word ptr ds:637Ah
	push	word ptr ds:637Ch
	push	word ptr ds:637Eh
	push	word ptr ds:6380h
	push	word ptr ds:6382h
	push	word ptr ds:6384h
	push	word ptr ds:6386h
	push	word ptr ds:6388h
	push	word ptr ds:638Ah
	push	word ptr ds:638Ch
	push	word ptr ds:638Eh
	push	word ptr ds:6390h
	mov		ds, [cs:word_5162]
	cld
	in		al, 21h				; Interrupt controller, 8259A.
	mov		[byte_3E10], al
	or		al, 7Fh
	out		21h, al				; Interrupt controller, 8259A.
	inc		byte [byte_3E0E]
	cmp		byte [byte_3E0E], 4
	jb		loc_D5CD
	mov		byte [byte_3E0E], 0
	mov		al, 36h
	out		43h, al				; Timer 8253-5 (AT: 8254.2).
	mov		dx, 3DAh
	mov		ah, [byte_3D74]

loc_D5BA:
	in		al, dx				; Video status bits:
								; 0: retrace.  1=display is in vert or horiz retrace.
								; 1: 1=light pen is triggered; 0=armed
								; 2: 1=light pen switch is open; 0=closed
								; 3: 1=vertical sync pulse is occurring.
	xor		al, ah
	test	al, 8
	jnz		loc_D5BA

	mov		cx, [word_3E12]
	mov		al, cl
	out		40h, al				; Timer 8253-5 (AT: 8254.2).
	mov		al, ch
	out		40h, al				; Timer 8253-5 (AT: 8254.2).

loc_D5CD:
	mov		ax, [word_3D7A]
	shr		ax, 2
	sub		[word_3E14], ax
	jnb		loc_D5E7
	mov		ax, [word_3D78]
	add		[word_3E14], ax
	pushf
	call	far [word_3E0A]
	jmp		loc_D5EB

loc_D5E7:
	mov		al, 20h
	out		20h, al				; Interrupt controller, 8259A.

loc_D5EB:
	sti
	cmp		byte [byte_3E0E], 0
	jnz		loc_D5F6
	call	sub_D1B6

loc_D5F6:
	dec		byte [byte_3E0F]
	jg		loc_D63E
	add		byte [byte_3E0F], 6
	jns		loc_D608
	mov		byte [byte_3E0F], 0

loc_D608:
	test	word [word_3E1C], 8000h
	jnz		loc_D63E
	cmp		word [word_3E1C], 0
	jnz		loc_D63E
	mov		ax, ss
	cmp		ax, [cs:word_5164]
	jnz		loc_D63E
	mov		bp, sp
	cmp		word [bp + 56h], 01A2h
	jnz		loc_D63E
	call	sub_D9EB
	mov		bx, [word_3E1C]
	mov		[bx + 3E1Eh], sp
	mov		sp, [word_3E20]
	mov		word [word_3E1C], 2

loc_D63E:
	inc		word [word_3E16]
	inc		word [word_3E18]
	cli
	mov		al, [byte_3E10]
	out		21h, al				; Interrupt controller, 8259A.
	inc		word [word_3E1A]
	cmp		word [word_3E1A], 1
	ja		loc_D670
	push	word [word_3E1C]
	or		word [word_3E1C], 8000h

loc_D661:
	sti
	call	sub_211E
	cli
	dec		word [word_3E1A]
	jnz		loc_D661
	pop		word [word_3E1C]

loc_D670:
	mov		ds, [cs:word_5162]
	pop		word ptr ds:6390h
	pop		word ptr ds:638Eh
	pop		word ptr ds:638Ch
	pop		word ptr ds:638Ah
	pop		word ptr ds:6388h
	pop		word ptr ds:6386h
	pop		word ptr ds:6384h
	pop		word ptr ds:6382h
	pop		word ptr ds:6380h
	pop		word ptr ds:637Eh
	pop		word ptr ds:637Ch
	pop		word ptr ds:637Ah
	pop		word ptr ds:6378h
	pop		word ptr ds:6376h
	pop		word ptr ds:6374h
	pop		word ptr ds:6372h
	pop		word ptr ds:6370h
	pop		word ptr ds:636Eh
	pop		word ptr ds:636Ch
	pop		word ptr ds:636Ah
	pop		word ptr ds:6368h
	pop		word ptr ds:6366h
	pop		word ptr ds:6364h
	pop		word ptr ds:6362h
	pop		word ptr ds:6360h
	pop		word ptr ds:635Eh
	pop		word ptr ds:635Ch
	pop		word ptr ds:635Ah
	pop		word ptr ds:6358h
	pop		word ptr ds:6356h
	pop		word ptr ds:6354h
	pop		word ptr ds:6352h
	pop		es
	pop		ds
	popa
	iret


;
; sub_D6F9						; D6F9
;
sub_D6F9:
	push	ax
	push	bx
	push	cx

loc_D6FC:
	mov		al, 0
	cli
	out		43h, al				; Timer 8253-5 (AT: 8254.2).
	in		al, 40h				; Timer 8253-5 (AT: 8254.2).
	mov		bl, al
	in		al, 40h				; Timer 8253-5 (AT: 8254.2).
	sti
	mov		bh, al
	mov		cx, [word_3D76]

loc_D70E:
	loop	loc_D70E
	mov		al, 0
	cli
	out		43h, al				; Timer 8253-5 (AT: 8254.2).
	in		al, 40h				; Timer 8253-5 (AT: 8254.2).
	mov		cl, al
	in		al, 40h				; Timer 8253-5 (AT: 8254.2).
	sti
	mov		ch, al
	cmp		bx, cx
	jz		loc_D728
	cmp		bx, [word_3E12]
	jb		loc_D73C

loc_D728:
	mov		cx, [word_3E12]
	mov		al, 36h
	cli
	out		43h, al				; Timer 8253-5 (AT: 8254.2).
	mov		al, cl
	out		40h, al				; Timer 8253-5 (AT: 8254.2).
	mov		al, ch
	out		40h, al				; Timer 8253-5 (AT: 8254.2).
	sti
	jmp		loc_D6FC

loc_D73C:
	pop		cx
	pop		bx
	pop		ax
	retn


;
; sub_D740
;
sub_D740:						; D740
	mov		ds, [cs:word_5162]
	or		word [word_3E1C], 8000h
	mov		[word_3E20], sp
	mov		sp, 1400h
	sti
	pushf
	push	cs
	push	ax
	pusha
	push	ds
	push	es
	mov		ds, [cs:word_5162]
	push	word ptr ds:6352h ; 32 times
	push	word ptr ds:6354h
	push	word ptr ds:6356h
	push	word ptr ds:6358h
	push	word ptr ds:635Ah
	push	word ptr ds:635Ch
	push	word ptr ds:635Eh
	push	word ptr ds:6360h
	push	word ptr ds:6362h
	push	word ptr ds:6364h
	push	word ptr ds:6366h
	push	word ptr ds:6368h
	push	word ptr ds:636Ah
	push	word ptr ds:636Ch
	push	word ptr ds:636Eh
	push	word ptr ds:6370h
	push	word ptr ds:6372h
	push	word ptr ds:6374h
	push	word ptr ds:6376h
	push	word ptr ds:6378h
	push	word ptr ds:637Ah
	push	word ptr ds:637Ch
	push	word ptr ds:637Eh
	push	word ptr ds:6380h
	push	word ptr ds:6382h
	push	word ptr ds:6384h
	push	word ptr ds:6386h
	push	word ptr ds:6388h
	push	word ptr ds:638Ah
	push	word ptr ds:638Ch
	push	word ptr ds:638Eh
	push	word ptr ds:6390h
	xchg	sp, [word_3E20]
	and		word [word_3E1C], 7FFFh
	retn


;
; sub_D7E9
;
sub_D7E9:
	pop		word [cs:word_516A]
	pushf
	push	cs
	push	word [cs:word_516A]
	pusha
	push	ds
	push	es
	mov		ds, [cs:word_5162]
	push	word ptr ds:6352h
	push	word ptr ds:6354h
	push	word ptr ds:6356h
	push	word ptr ds:6358h
	push	word ptr ds:635Ah
	push	word ptr ds:635Ch
	push	word ptr ds:635Eh
	push	word ptr ds:6360h
	push	word ptr ds:6362h
	push	word ptr ds:6364h
	push	word ptr ds:6366h
	push	word ptr ds:6368h
	push	word ptr ds:636Ah
	push	word ptr ds:636Ch
	push	word ptr ds:636Eh
	push	word ptr ds:6370h
	push	word ptr ds:6372h
	push	word ptr ds:6374h
	push	word ptr ds:6376h
	push	word ptr ds:6378h
	push	word ptr ds:637Ah
	push	word ptr ds:637Ch
	push	word ptr ds:637Eh
	push	word ptr ds:6380h
	push	word ptr ds:6382h
	push	word ptr ds:6384h
	push	word ptr ds:6386h
	push	word ptr ds:6388h
	push	word ptr ds:638Ah
	push	word ptr ds:638Ch
	push	word ptr ds:638Eh
	push	word ptr ds:6390h
	cli
	mov		[word_3E20], sp
	mov		word [word_3E1C], 0
	mov		sp, word ptr ds:3E1Eh
	mov		ds, [cs:word_5162]
	pop		word ptr ds:6390h
	pop		word ptr ds:638Eh
	pop		word ptr ds:638Ch
	pop		word ptr ds:638Ah
	pop		word ptr ds:6388h
	pop		word ptr ds:6386h
	pop		word ptr ds:6384h
	pop		word ptr ds:6382h
	pop		word ptr ds:6380h
	pop		word ptr ds:637Eh
	pop		word ptr ds:637Ch
	pop		word ptr ds:637Ah
	pop		word ptr ds:6378h
	pop		word ptr ds:6376h
	pop		word ptr ds:6374h
	pop		word ptr ds:6372h
	pop		word ptr ds:6370h
	pop		word ptr ds:636Eh
	pop		word ptr ds:636Ch
	pop		word ptr ds:636Ah
	pop		word ptr ds:6368h
	pop		word ptr ds:6366h
	pop		word ptr ds:6364h
	pop		word ptr ds:6362h
	pop		word ptr ds:6360h
	pop		word ptr ds:635Eh
	pop		word ptr ds:635Ch
	pop		word ptr ds:635Ah
	pop		word ptr ds:6358h
	pop		word ptr ds:6356h
	pop		word ptr ds:6354h
	pop		word ptr ds:6352h
	pop		es
	pop		ds
	popa
	iret


;
; Fill stack with some data.
;
sub_D915:						; D915
	mov		word [word_3E1C], 8000h
	pop		ax					; ax = return point from sub_D915
	mov		sp, 1800h
	push	ax
	mov		ax, sub_D926
	jmp		sub_D740


;
; sub_D926
;
sub_D926:						; D926
	call	sub_D7E9
	jmp		sub_D926


;
; sub_D92B
;
sub_D92B:						; D92B
	cmp		word [playing_demo], 0
	jz		sub_D962
	mov		es, [word_63BE]		; copy of unpacked data
	mov		bx, [word_3E22]
	cmp		bx, 0
	jnz		loc_D942
	mov		bx, 394h

loc_D942:
	mov		ax, [es:bx]
	cmp		ax, 0FFFFh
	jnz		loc_D953
	mov		word [playing_demo], 0
	jmp		loc_5283

loc_D953:
	add		bx, 2
	mov		[word_3E22], bx
	mov		[byte_16FE], al
	mov		[byte_1715], ah
	retn


;
; sub_D962
;
sub_D962:						; D962
	mov		si, 1701h
	mov		bx, [word_16FF]
	shl		bx, 1
	call	word [bx + 3E26h]
	call	sub_D989
	mov		[byte_16FE], al
	mov		si, 1718h
	mov		bx, [word_1716]
	shl		bx, 1
	call	word [bx + 3E26h]
	call	sub_D989
	mov		[byte_1715], al
	retn


;
; sub_D989
;
sub_D989:						; D989
	mov		ah, al
	mov		bh, al
	and		ah, 8
	and		bh, 4
	shr		ah, 1
	shl		bh, 1
	or		ah, bh
	and		al, 0F3h
	or		al, ah
	retn


;
; sub_D99E
;
sub_D99E:						; D99E
	sub		dx, dx
	mov		bx, 3D88h
	mov		cx, 6

loc_D9A6:
	lodsb
	xlat	byte [bx]
	shr		al, 1
	rcr		dl, 1
	loop	loc_D9A6

	shr		dl, 2
	mov		al, dl
	retn


;
; sub_D9B4
;
sub_D9B4:						; D9B4
	add		si, 6
	mov		al, 0
	cmp		[si], al
	jz		locret_D9EA

	sub		dx, dx
	mov		ax, [si + 2]
	cmp		ax, [si + 6]
	rcr		dl, 1
	mov		ax, [si + 8]
	cmp		ax, [si + 2]
	rcr		dl, 1
	mov		ax, [si + 4]
	cmp		ax, [si + 0Ah]
	rcr		dl, 1
	mov		ax, [si + 0Ch]
	cmp		ax, [si + 4]
	rcr		dl, 1
	shr		dl, 4
	mov		al, [si + 1]
	shl		al, 4
	or		al, dl

locret_D9EA:
	retn


;
; sub_D9EB
;
sub_D9EB:						; D9EB
	mov		byte [byte_3E25], 0
	sub		bp, bp
	mov		bx, bp
	mov		si, bp
	mov		di, bp
	mov		cx, [word_16FA]
	cmp		cx, 1000h
	jb		loc_DA05
	mov		cx, 1000h

loc_DA05:
	inc		cx
	mov		al, 0
	mov		ah, [byte_3E24]
	mov		dx, 201h
	out		dx, al				; Game I/O port
								; bits 0-3: Coordinates (resistive, time-dependent inputs)
								; bits 4-7: Buttons/Triggers (digital inputs)

loc_DA10:
	ror		al, 1
	adc		bx, 0
	ror		al, 1
	adc		bp, 0
	ror		al, 1
	adc		si, 0
	ror		al, 1
	adc		di, 0
	in		al, dx				; Game I/O port
								; bits 0-3: Coordinates (resistive, time-dependent inputs)
								; bits 4-7: Buttons/Triggers (digital inputs)
	test	al, ah
	loopne	loc_DA10

	cmp		byte [byte_3E25], 0
	jnz		locret_DA93
	cmp		bx, 1000h
	jb		loc_DA3B
	and		byte [byte_3E24], 0FCh

loc_DA3B:
	cmp		si, 1000h
	jb		loc_DA46
	and		byte [byte_3E24], 0F3h

loc_DA46:
	shl		ax, 1
	shl		ax, 1
	rol		al, 1
	rol		al, 1
	not		ax
	mov		cx, ax
	and		ax, 101h
	and		cx, 202h
	shr		cx, 1
	shl		ax, 1
	or		ax, cx
	cmp		word [word_16FC], 0
	jz		loc_DA6C
	xchg	al, ah
	xchg	bx, si
	xchg	bp, di

loc_DA6C:
	mov		[byte_1708], al
	mov		[byte_171F], ah
	add		[word_1709], bx
	shr		word [word_1709], 1
	add		[word_170B], bp
	shr		word [word_170B], 1
	add		[word_1720], si
	shr		word [word_1720], 1
	add		[word_1722], di
	shr		word [word_1722], 1

locret_DA93:
	retn
