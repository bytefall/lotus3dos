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


;
; Opens a file.
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


;
; Reads a file.
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
	; mov		ds, [cs:word_5162]
	mov		[word_3EB9], si
	mov		byte [byte_3EBB], 1
	jmp		loc_DC70

loc_DC70:
	; mov		ds, [cs:word_5162]
	cld
	; TODO:
	call	sub_D396
	; call	sub_209C
	call	sub_D3B6
	; call	sub_5080
	call	sub_D3C7

	mov		si, [word_3EB9]
	call	printf				; (si* string)

	mov		al, [byte_3EBB]
	mov		ah, 4Ch
	int		21h					; DOS - 2+ - QUIT WITH EXIT CODE (EXIT)


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
