; dos.inc

;
; fade_out
;
fade_out:							; D0D8
	mov		si, 7256h
	cmp		byte [byte_3D6A], 0
	jz		short loc_D0E5
	jmp		sub_D18C				; copy palette
									;
									; input:
									; si - where palette is stored

loc_D0E5:
	mov		word [word_3D6C], 20
	call	sub_D12C				; Fades in/out some palette colors
									;
									; input:
									; ds:si - palette
									; word_3D6C - fade speed (greater = slower)
	call	sub_D161
	mov		byte [byte_3D6A], 0FFh
	retn
; - fade_out -


; TODO: place missing functions here


;
; sub_D1B6
;
sub_D1B6:							; D1B6
	cmp		word [word_3D6E], 0
	jz		loc_D1E9
	cmp		word [word_3D70], 0
	jnz		loc_D1CC
	mov		word [word_3D6E], 0
	jmp		sub_D1D7

loc_D1CC:
	call	sub_D1D7
	dec		word [word_3D70]
	jz		loc_D1E9
	jmp		sub_D174
; - sub_D1B6 -


;
; Fade out slowly
;
sub_D1D7:							; D1D7
	mov		al, 0
	mov		dx, 3C8h
	out		dx, al
	mov		dx, 3C9h
	mov		si, arr_6F56
	mov		cx, 256*3
	rep outsb
	retn

loc_D1E9:
	mov		word [word_3D6E], 0
	mov		word [word_3D70], 0
	retn
; - sub_D1D7 -


;
; set_video_mode_and_timer
;
set_video_mode_and_timer:			; D1F6
	in		al, 40h					; Timer 8253-5 (AT: 8254.2).
	mov		ah, al
	in		al, 40h					; Timer 8253-5 (AT: 8254.2).
	mov		[word_3E16], ax
	mov		ah, 19h
	int		21h						; DOS - GET DEFAULT DISK NUMBER

	mov		[byte_3D72], al
	mov		ah, 0Fh
	int		10h						; - VIDEO - GET CURRENT VIDEO MODE
									; Return: AH = number of columns on screen
									; AL = current video mode
									; BH = current active display page

	mov		[dos_vid_mode], al
	mov		al, 13h					; https://github.com/jagregory/abrash-black-book/blob/master/src/chapter-27.md#mode-13h320x200-with-256-colors
	mov		ah, 0
	int		10h						; - VIDEO - SET VIDEO MODE
									; AL = mode

	mov		ax, 0
	int		33h						; - MS MOUSE - RESET DRIVER AND READ STATUS
									; Return: AX = status
									; BX = number of buttons

	mov		[byte_3E2C], al
	; mov		es, cs:word_5160		; es = ds_from_packer = 0x0192
	; mov		ax, es:word_2			; es = 0x9FFF
	; sub		ax, 4371
	; mov		[word_63BC], ax			; video memory for A000, = 0x8EEC
	; sub		ax, 256
	; mov		[word_63BE], ax			; copy of unpacked data, = 0x8DEC
	; cli
	; sub		ax, ax
	; mov		es, ax
	; mov		ax, es:word_24			; = 0xE987
	; mov		[word_3D82], ax
	; mov		ax, es:word_26			; = 0xF000
	; mov		[word_3D84], ax
	; mov		ax, es:word_20			; = 0xFEA5
	; mov		[word_3E0A], ax
	; mov		ax, es:tmp_cs			; = 0xF000
	; mov		[word_3E0C], ax
	; mov		ax, es:word_90			; = 0x0110
	; mov		[word_3D7E], ax
	; mov		ax, es:word_92			; = 0x0118
	; mov		[word_3D80], ax
	mov		al, 10110000b
	out		43h, al
	mov		al, 0
	out		42h, al
	out		42h, al
	in		al, 61h
	or		al, 1
	out		61h, al				; PC/XT PPI port B bits:
								; 0: Tmr 2 gate --- OR 03H=spkr ON
								; 1: Tmr 2 data -+  AND 0fcH=spkr OFF
								; 3: 1=read high switches
								; 4: 0=enable RAM parity checking
								; 5: 0=enable I/O channel check
								; 6: 0=hold keyboard clock low
								; 7: 0=enable kbrd

	mov		dx, 3DAh			; Wait fro VSYNC

loc_D272:
	in		al, dx				; Video status bits:
								; 0: retrace.  1=display is in vert or horiz retrace.
								; 1: 1=light pen is triggered; 0=armed
								; 2: 1=light pen switch is open; 0=closed
								; 3: 1=vertical sync pulse is occurring.
	test	al, 1000b
	jnz		loc_D272

loc_D277:
	in		al, dx				; Video status bits:
								; 0: retrace.  1=display is in vert or horiz retrace.
								; 1: 1=light pen is triggered; 0=armed
								; 2: 1=light pen switch is open; 0=closed
								; 3: 1=vertical sync pulse is occurring.
	test	al, 1000b
	jz		loc_D277

	mov		al, 10000000b
	out		43h, al				; Timer 8253-5 (AT: 8254.2).
	in		al, 42h				; Timer 8253-5 (AT: 8254.2).
	mov		bl, al
	in		al, 42h				; Timer 8253-5 (AT: 8254.2).
	mov		bh, al

loc_D288:
	in		al, dx				; Video status bits:
								; 0: retrace.  1=display is in vert or horiz retrace.
								; 1: 1=light pen is triggered; 0=armed
								; 2: 1=light pen switch is open; 0=closed
								; 3: 1=vertical sync pulse is occurring.

	test	al, 1000b
	jnz		loc_D288

	mov		al, 10000000b
	out		43h, al				; Timer 8253-5 (AT: 8254.2).
	in		al, 42h				; Timer 8253-5 (AT: 8254.2).
	mov		cl, al
	in		al, 42h				; Timer 8253-5 (AT: 8254.2).
	mov		ch, al

loc_D299:
	in		al, dx				; Video status bits:
								; 0: retrace.  1=display is in vert or horiz retrace.
								; 1: 1=light pen is triggered; 0=armed
								; 2: 1=light pen switch is open; 0=closed
								; 3: 1=vertical sync pulse is occurring.
	test	al, 1000b
	jz		loc_D299

	mov		al, 10000000b		; counter 2 select
	out		43h, al				; Timer 8253-5 (AT: 8254.2).
	in		al, 42h				; Timer 8253-5 (AT: 8254.2).
	mov		dl, al
	in		al, 42h				; Timer 8253-5 (AT: 8254.2).
	mov		dh, al
	mov		ax, bx
	sub		ax, dx
	mov		dx, ax
	mov		[word_3D7A], dx		; = bx - timerValue; dx == 0 ???
	sub		bx, cx
	sub		dx, bx
	mov		al, 0FFh
	cmp		bx, dx
	jb		loc_D2C0
	mov		al, 0

loc_D2C0:
	mov		[byte_3D74], al
	in		al, 61h				; PC/XT PPI port B bits:
								; 0: Tmr 2 gate --- OR 03H=spkr ON
								; 1: Tmr 2 data -+  AND 0fcH=spkr OFF
								; 3: 1=read high switches
								; 4: 0=enable RAM parity checking
								; 5: 0=enable I/O channel check
								; 6: 0=hold keyboard clock low
								; 7: 0=enable kbrd
	and		al, 11111110b
	out		61h, al
	sub		cx, cx
	sub		dx, dx

loc_D2CD:
	mov		al, 0
	out		43h, al				; Timer 8253-5 (AT: 8254.2).
	in		al, 40h				; Timer 8253-5 (AT: 8254.2).
	mov		bl, al
	in		al, 40h				; Timer 8253-5 (AT: 8254.2).
	mov		bh, al
	cmp		bx, dx
	jb		loc_D2DF
	mov		dx, bx
loc_D2DF:
	loop	loc_D2CD

	mov		cx, dx
	sub		ax, ax
	mov		dx, 1
	div		cx
	shl		dx, 1
	cmp		cx, dx
	adc		ax, 0
	mov		cx, ax
	sub		ax, ax
	mov		dx, 1
	cmp		cx, 1
	jz		loc_D306

	div		cx
	shl		dx, 1
	cmp		cx, dx
	adc		ax, 0

loc_D306:
	mov		[word_3D78], ax
	mov		al, 10110000b
	out		43h, al				; Timer 8253-5 (AT: 8254.2).
	mov		al, 0
	out		42h, al				; Timer 8253-5 (AT: 8254.2).
	out		42h, al				; Timer 8253-5 (AT: 8254.2).
	in		al, 61h				; PC/XT PPI port B bits:
								; 0: Tmr 2 gate --- OR 03H=spkr ON
								; 1: Tmr 2 data -+  AND 0fcH=spkr OFF
								; 3: 1=read high switches
								; 4: 0=enable RAM parity checking
								; 5: 0=enable I/O channel check
								; 6: 0=hold keyboard clock low
								; 7: 0=enable kbrd
	or		al, 1
	out		61h, al				; PC/XT PPI port B bits:
								; 0: Tmr 2 gate --- OR 03H=spkr ON
								; 1: Tmr 2 data -+  AND 0fcH=spkr OFF
								; 3: 1=read high switches
								; 4: 0=enable RAM parity checking
								; 5: 0=enable I/O channel check
								; 6: 0=hold keyboard clock low
								; 7: 0=enable kbrd
	mov		cx, 1388h
	mov		al, 10000000b
	out		43h, al				; Timer 8253-5 (AT: 8254.2).
	in		al, 42h				; Timer 8253-5 (AT: 8254.2).
	mov		bl, al
	in		al, 42h				; Timer 8253-5 (AT: 8254.2).
	mov		bh, al
	mov		al, 10000000b
	out		43h, al				; Timer 8253-5 (AT: 8254.2).
	in		al, 42h				; Timer 8253-5 (AT: 8254.2).
	mov		dl, al
	in		al, 42h				; Timer 8253-5 (AT: 8254.2).
	mov		dh, al

loop_myself:
	loop	loop_myself

	mov		al, 10000000b
	out		43h, al				; Timer 8253-5 (AT: 8254.2).
	in		al, 42h				; Timer 8253-5 (AT: 8254.2).
	mov		cl, al
	in		al, 42h				; Timer 8253-5 (AT: 8254.2).
	mov		ch, al
	sub		bx, dx
	sub		dx, cx
	sub		dx, bx
	mov		cx, dx				; cx = dx - bx
	mov		dx, 5Ah				; 'Z'
	mov		ax, 0FB04h
	div		cx					; comment out this line to resolve speed issue.
								; see https://www.vogons.org/viewtopic.php?p=308588#p308588
	mov		[word_3D76], ax		; word_3D76 = 0x9C1 (was word_3D76 = 0)
	in		al, 61h				; PC/XT PPI port B bits:
								; 0: Tmr 2 gate --- OR 03H=spkr ON
								; 1: Tmr 2 data -+  AND 0fcH=spkr OFF
								; 3: 1=read high switches
								; 4: 0=enable RAM parity checking
								; 5: 0=enable I/O channel check
								; 6: 0=hold keyboard clock low
								; 7: 0=enable kbrd
	and		al, 11111110b
	out		61h, al				; PC/XT PPI port B bits:
								; 0: Tmr 2 gate --- OR 03H=spkr ON
								; 1: Tmr 2 data -+  AND 0fcH=spkr OFF
								; 3: 1=read high switches
								; 4: 0=enable RAM parity checking
								; 5: 0=enable I/O channel check
								; 6: 0=hold keyboard clock low
								; 7: 0=enable kbrd
	sti
	cli
	pushf
	pop		ax
	or		ah, 110000b
	push	ax
	popf
	pushf
	pop		ax
	test	ah, 110000b
	jz		loc_D377

	and		ah, 0CFh
	push	ax
	popf
	mov		word [cs:word_D379], 2

loc_D377:
	sti
	retn
; - set_video_mode_and_timer -


word_D379:			dw ?		; D379


;
; sub_D37B
;
sub_D37B:						; D37B
	call	sub_D3B6
	call	sub_D3DD
	mov		ax, sub_D926
	call	sub_D740
	call	set_timer
	mov		si, 7256h
	call	sub_D18C			; copy palette
								;
								; input:
								; si - where palette is stored
	mov		byte [byte_3D7C], 0FFh
	retn
; - sub_D37B -


;
; sub_D396
;
sub_D396:						; D396
	cmp		byte [byte_3D7C], 0
	jz		loc_D3AE

	call	fade_out
	call	sub_D4E3
	call	sub_D400
	call	sub_D3C7
	mov		byte [byte_3D7C], 0

loc_D3AE:
	mov		al, [dos_vid_mode]
	mov		ah, 0
	int		10h					; - VIDEO - SET VIDEO MODE
								; AL = mode
	retn
; - sub_D396 -


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
; - sub_D3B6 -


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
; - sub_D3C7 -


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
; - sub_D3DD -


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
; - sub_D3F3 -

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
; - sub_D400 -


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
; - sub_D421 -


;
; sub_D445
;
sub_D445:						; D445
	pusha
	push	ds
	push	es
	mov		ds, [cs:word_5162]
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
	test	arr_3D88[bx], al
	js		loc_D475
	mov		arr_3D88[bx], al

loc_D475:
	cmp		bl, 37h ; '7'
	jz		short loc_D49D
	cmp		bl, 1Dh
	jz		short loc_D49D
	cmp		bl, 7Fh ; ''
	jz		short loc_D49D
	pushf
	call	[word_3D82]			; E987
	cli

loc_D48A:
	mov		ah, 1
	int		16h					; KEYBOARD - CHECK BUFFER, DO NOT CLEAR
								; Return: ZF clear if character in buffer
								; AH = scan code, AL = character
								; ZF set if no character in buffer
	jz		loc_D499			; iret
	mov		ah, 0
	int		16h					; KEYBOARD - READ CHAR FROM BUFFER, WAIT IF EMPTY
								; Return: AH = scan code, AL = character
	mov		[word_3E08], ax
	jmp		loc_D48A

loc_D499:
	pop		es					; iret
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
	jmp		loc_D499			; iret
; - sub_D445 -


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
; - set_timer -


;
; sub_D4E3
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
; - sub_D4E3 -


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
	call	[word_3E0A]
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
	cmp		word ptr [bp + 56h], 01A2h
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
; - sub_D508 -


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
; - sub_D6F9 -


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
; - sub_D740 -


;
; sub_D7E9
;
sub_D7E9:
	pop		[cs:word_516A]
	pushf
	push	cs
	push	[cs:word_516A]
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
	mov		sp, ds:3E1Eh
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
; - sub_D7E9 -


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
; - sub_D915 -


;
; sub_D926
;
sub_D926:						; D926
	call	sub_D7E9
	jmp		sub_D926
; - sub_D926 -


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
; - sub_D92B -


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
	call	word ptr [bx + 3E26h]
	call	sub_D989
	mov		[byte_1715], al
	retn
; - sub_D962 -


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
; - sub_D989 -


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
; - sub_D99E -


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
; - sub_D9B4 -


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
; - sub_D9EB -


;
; sub_DA94
;
sub_DA94:						; DA94
	push	ds
	pop		es
	mov		di, 172Ch
	mov		cx, 128
	mov		al, 0
	rep stosb
	mov		byte [byte_1745], 0FFh
	mov		byte [byte_172D], 0FFh
	mov		si, 1701h
	mov		bh, 0

loc_DAAF:
	mov		bl, [si]
	inc		si
	mov		byte [bx + 172Ch], 0FFh
	cmp		si, 1706h
	jb		loc_DAAF

	mov		si, 1718h
	mov		bh, 0

loc_DAC2:
	mov		bl, [si]
	inc		si
	mov		byte [bx + 172Ch], 0FFh
	cmp		si, 171Dh
	jb		loc_DAC2
retn
; - sub_DA94 -


;
; sub_DAD1
;
sub_DAD1:						; DAD1
	mov		al, 0
	cmp		byte [byte_3E2C], al
	jz		locret_DB27

	mov		ax, 3
	int		33h					; - MS MOUSE - RETURN POSITION AND BUTTON STATUS
								; Return: BX = button status, CX = column, DX = row
	and		bx, 3
	mov		[word_3E2E], bx
	mov		al, bl
	add		al, 0FFh
	sbb		al, al
	mov		[byte_3E2D], al
	mov		[word_3E30], cx
	mov		[word_3E32], dx
	mov		al, [byte_3DD0]
	and		al, 1
	mov		ah, [byte_3DD8]
	and		ah, 1
	shl		ah, 1
	or		ah, al
	shl		ah, 2
	mov		al, bl
	cmp		word [word_16F2], 0
	jnz		loc_DB18

	shr		ah, 2
	shl		al, 2

loc_DB18:
	or		al, ah
	cmp		cx, 200h
	cmc
	rcl		al, 1
	cmp		cx, 80h
	rcl		al, 1

locret_DB27:
	retn


;
; sub_DB28
;
sub_DB28:						; DB28
	call	sub_DA94
	mov		ax, [word_3E16]
	mov		di, arr_3EEE
	push	ds
	pop		es
	mov		cx, 16
	rep stosw
	mov		bp, 0C00h			; TODO: change to offset?

loc_DB3B:
	mov		ax, bp
	mov		ah, 0
	mov		cx, 8

loc_DB42:
	shl		al, 1
	adc		ah, 0
	loop	loc_DB42

	mov		[bp], ah
	inc		bp
	cmp		bp, 0D00h			; TODO: same here?
	jb		loc_DB3B

	push	cs
	pop		es
	mov		di, 0
	mov		dh, 0

loc_DB5A:
	mov		dl, dh
	push	di
	mov		cx, 8

loc_DB60:
	dec		cx
	shl		dl, 1
	jb		loc_DB7C

	mov		al, 47h
	jcxz	loc_DB9D
	js		loc_DB9D
	mov		ax, 0C783h
	stosw
	mov		al, 1

loc_DB71:
	inc		al
	dec		cx
	shl		dl, 1
	jcxz	loc_DB9D
	jns		loc_DB71
	jmp		loc_DB9D

loc_DB7C:
	mov		al, 0A4h
	jns		loc_DB9D
	mov		al, 0A5h
	dec		cx
	shl		dl, 1
	cmp		word [cs:word_D379], 0
	jz		loc_DB9D
	cmp		dl, 0C0h
	jb		loc_DB9D
	sub		cx, 2
	shl		dl, 2
	mov		al, 66h
	stosb
	mov		al, 0A5h

loc_DB9D:
	stosb
	and		cx, cx
	jg		loc_DB60

	; TODO:
	; mov		si, arr_DBB4
	mov		cx, 14
	rep movs byte [es:di], [cs:si]
	pop		di
	add		di, 20h
	inc		dh
	jnz		loc_DB5A
	retn
; - sub_DB28 -


;
; sub_DBB4
;
sub_DBB4:						; DBB4
	dec		cl
	jz		loc_DBC0

	mov		ah, 0
	lodsb
	shl		ax, 5
	jmp		ax

loc_DBC0:
	jmp		bx

	mov		[file_name], dx
	mov		ax, 3C00h
	mov		cx, 0
	int		21h					; DOS - 2+ - CREATE A FILE WITH HANDLE (CREAT)
								; CX = attributes for file
								; DS:DX -> ASCIZ filename (may include drive and path)
	jb		loc_DBD3
	mov		bx, ax
	retn

loc_DBD3:
	mov		si, create_error
	jmp		loc_DC60
; - sub_DBB4 -


;
; Opens a file
;
file_open:						; DBD9
	mov		[file_name], dx
	mov		ax, 3D02h
	int		21h					; DOS - 2+ - OPEN DISK FILE WITH HANDLE
								; DS:DX -> ASCIZ filename
								; AL = access mode
								; 2 - read & write
	jb		file_open_err
	mov		bx, ax
	retn

file_open_err:
	mov		ax, 3E00h
	int		21h					; DOS - 2+ - CLOSE A FILE WITH HANDLE
								; BX = file handle
	mov		si, open_error
	jmp		loc_DC60
; - file_open -


;
; Reads a file
;
; ax:dx - buffer,
; bx - file handler,
; cx - num of bytes to read
file_read:						; DBF1
	push	bx
	push	ds
	mov		ds, ax
	mov		ax, 3F00h
	int		21h					; DOS - 2+ - READ FROM FILE WITH HANDLE
								; BX = file handle, CX = number of bytes to read
								; DS:DX -> buffer
	pop		ds
	pop		bx
	mov		cx, ax
	jb		file_read_err
	retn

file_read_err:
	mov		ax, 3E00h
	int		21h					; DOS - 2+ - CLOSE A FILE WITH HANDLE
								; BX = file handle
	mov		si, read_error
	jmp		loc_DC60
; - file_read -


;
; Is not known where it is called from
;
unk_DC0B:						; DC0B
	push	bx
	push	ds
	mov		ds, ax
	mov		ax, 4000h
	int		21h					; DOS - 2+ - WRITE TO FILE WITH HANDLE
								; BX = file handle, CX = number of bytes to write, DS:DX -> buffer
	pop		ds
	pop		bx
	jb		loc_DC19
	retn

loc_DC19:
	mov		ax, 3E00h
	int		21h					; DOS - 2+ - CLOSE A FILE WITH HANDLE
								; BX = file handle
	mov		si, write_error
	jmp		loc_DC60

	mov		ax, 3E00h
	int		21h					; DOS - 2+ - CLOSE A FILE WITH HANDLE
								; BX = file handle
	jb		loc_DC2B
	retn

loc_DC2B:
	mov		si, close_error
	jmp		loc_DC60
; - unk_DC0B -


;
; printf
;
; (si* string)
printf:							; DC30
	lodsb
	cmp		al, 0
	jz		locret_DC4E

	cmp		al, '$'
	jz		loc_DC43

	push	si
	mov		dl, al
	mov		ah, 2
	int		21h					; DOS - DISPLAY OUTPUT
								; DL = character to send to standard output
	pop		si
	jmp		printf

loc_DC43:
	push	si
	mov		si, [file_name]
	call	printf				; (si* string)
	pop		si
	jmp		printf				; (si* string)

locret_DC4E:
	retn
; - printf -


;
; sub_DC4F
;
sub_DC4F:						; DC4F
	push	ax
	mov		ax, [word_63BA]		; unpacked data
	cmp		ax, [word_63BE]		; copy of unpacked data
	jnb		loc_DC5B
	pop		ax
	retn

loc_DC5B:
	mov		si, memory_error
	jmp		loc_DC60

loc_DC60:
	mov		ds, [cs:word_5162]
	mov		[word_3EB9], si
	mov		byte [byte_3EBB], 1
	jmp		loc_DC70

loc_DC70:
	mov		ds, [cs:word_5162]
	cld
	; TODO:
	call	sub_D396
	; call	sub_209C
	call	sub_D3B6
	; call	sub_5080
	; call	sub_D3C7

	mov		si, [word_3EB9]
	call	printf				; (si* string)

	mov		al, [byte_3EBB]
	mov		ah, 4Ch
	int		21h					; DOS - 2+ - QUIT WITH EXIT CODE (EXIT)
; - sub_DC4F -


;
; sub_E987 - is this some kind of BIOS function?
;
sub_E987:						; E987
	push	ax
	in		al, 60h
	mov		ah, 4Fh
	stc
	int		15h
	jnc		loc_E995
	;callback 0011  (IRQ 1 Keyboard) ; FE381100

loc_E995:
	cli
	mov		al, 20h
	out		20h, al
	pop		ax
	iret
; - sub_E987 -
