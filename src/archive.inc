res_pair_size = 10						; each resource pair (key and offset) is 10 bytes long
res_buff_size = 17408					; maximal size of packed resource


;
;
;
sub_C95F:								; C95F
	mov		si, 3126h
	push	ds
	pop		es
	mov		di, 77F6h
	mov		cx, 48
	rep movsb
	ret


;
;
;
sub_C96D:								; C96D
	mov		bx, 3156h
	mov		dx, bx
	mov		[bx], ah
	mov		ah, al
	shr		al, 4
	call	sub_C97E
	mov		al, ah


;
;
;
sub_C97E:
	and		al, 0Fh						; al = al > 15 ? 0 : al
	add		al, 30h						; '0'
	cmp		al, 39h						; '9'
	jbe		short loc_C988
	add		al, 7

loc_C988:
	inc		bx
	mov		[bx], al
	ret


; 
; Opens DAT file and reads 2816 bytes from the header.
;
open_and_read_data_file:				; C98C
	mov		dx, arc_file_name			; "LOTUS.DAT"
	call	file_open

	mov		[arc_file_handle], bx
	mov		ax, ds
	mov		dx, arc_header
	mov		cx, 2816
	call	file_read
	ret


;
;
;
sub_C9A2:								; C9A2
	mov		[err_str_ptr], dx
	mov		di, res_key
	mov		ax, ds
	mov		es, ax
	mov		al, 20h						; ' '
	mov		cx, 8
	rep stosb
	mov		si, dx						; = 3156
	mov		di, res_key
	mov		cx, 8

loc_C9BC:
	lodsb
	cmp		al, 0
	jz		loc_C9CE
	cmp		al, 61h						; 'a'
	jb		loc_C9CB
	cmp		al, 7Ah						; 'z'
	ja		loc_C9CB
	sub		al, 20h						; ' '

loc_C9CB:
	stosb
	loop	loc_C9BC

loc_C9CE:
	mov		bp, arc_header + 2

loc_C9D1:								; locate resource "X00" in the arc_header
	mov		di, bp
	cmp		byte [di], 0
	je		err_CA0F
	mov		si, res_key
	mov		cx, 4
	repe cmpsw
	je		loc_C9E7
	add		bp, res_pair_size
	jmp		loc_C9D1

loc_C9E7:
	mov		cx, [di]					; cx = resource offset
	mov		dl, 0
	mov		dh, cl
	mov		cl, ch
	mov		ch, 0
	shl		dx, 1
	rcl		cx, 1
	mov		bx, [arc_file_handle]
	push	di
	mov		ax, 4200h					; new position - cx:dx (E:4A00)
	int		21h							; DOS - 2+ - MOVE FILE READ/WRITE POINTER (LSEEK)
										; AL = method: offset from beginning of file
	pop		di
	jb		err_CA0F
	mov		bx, [arc_file_handle]
	mov		cx, [di + res_pair_size]	; next resource's offset
	sub		cx, [di]
	shl		cx, 9						; get the difference and shl by 9 to get file offset
	ret

err_CA0F:
	mov		si, open_error
	jmp		loc_DC60


; Loads a resource from DAT-file and unpacks it.
;
; input:
; ah - ASCII character
; al - index
;
; output:
; word_63BA:0 - unpacked data (head)
; ax:0 - points to the next segment / byte after unpacked data (tail)
; cx - number of unpacked bytes (length in bytes)
res_load:								; CA15
	call	sub_C96D
	call	sub_C9A2
	mov		[dat_file_handle], bx
	mov		ax, ds
	mov		dx, tmp_file_buf
	mov		cx, res_buff_size
	call	file_read

	mov		es, [word_63BA]
	mov		di, 0
	mov		si, tmp_file_buf
	mov		cx, res_buff_size
	call	res_unpack
	jae		loc_CA5A

loc_CA3C:
	pusha
	push	es
	mov		bx, [dat_file_handle]
	mov		ax, ds
	mov		dx, tmp_file_buf
	mov		cx, res_buff_size
	call	file_read
	pop		es
	popa
	mov		si, tmp_file_buf
	mov		cx, res_buff_size
	call	sub_CA75
	jb		loc_CA3C

loc_CA5A:
	push	di
	add		di, 15
	shr		di, 4
	mov		ax, es
	add		ax, di
	pop		cx
	ret									; ax = es + (di + 15) / 16


; input:
; ds:si - packed data
; cx - packed length
;
; output:
; es:0 - unpacked data
; di - unpacked length
; cf - need to read more
res_unpack:								; CA67
	mov		word [cs:word_5174], loc_CA93
	mov		word [cs:word_5176], loc_CB43

sub_CA75:								; CA75
	mov		bx, [cs:word_5174]
	mov		dx, [cs:word_5176]

loc_CA7F:
	lodsb
	call	bx 
	loop	loc_CA7F
	mov		[cs:word_5174], bx
	mov		[cs:word_5176], dx
	stc
	ret


loc_CA90:
	pop		ax
	clc
	ret

loc_CA93:
	mov		[cs:counter], al
	mov		bx, loc_CA9B
	ret

loc_CA9B:
	cmp		byte [cs:counter], 0
	jnz		loc_CAA7
	mov		bx, loc_CB41
	ret

loc_CAA7:
	mov		[cs:byte_5170], al
	mov		bp, 0
	mov		ax, 0

loc_CAB1:
	mov		[bp], ax
	add		bp, 4
	inc		al
	jnz		loc_CAB1
	mov		bx, loc_CABF				; while counter != 0
	ret

loc_CABF:
	mov		byte [cs:idx], al			; while counter != 0
	mov		bx, loc_CAC7
	ret

loc_CAC7:
	mov		[cs:byte_516D], al
	mov		bx, loc_CACF
	ret

loc_CACF:
	mov		bp, [cs:idx]
	shl		bp, 2
	mov		bl, al
	mov		bh, 0
	shl		bx, 2
	mov		ah, 1
	cmp		byte [ss:bx + 1], 0
	jz		loc_CAE9
	inc		ah

loc_CAE9:
	mov		[bp + 2], ax
	mov		al, [cs:byte_516D]
	mov		bl, al
	mov		bh, 0
	shl		bx, 2
	mov		ah, 1
	cmp		byte [ss:bx + 1], 0
	jz		loc_CB02
	inc		ah

loc_CB02:
	mov		[bp], ax
	dec		byte [cs:counter]
	jz		loc_CB10
	mov		bx, loc_CABF				; while counter != 0
	ret

loc_CB10:
	mov		bx, loc_CB14
	ret

loc_CB14:
	cmp		al, [cs:byte_5170]
	jz		loc_CB38

loc_CB1B:
	mov		ah, 0
	mov		bp, ax
	shl		bp, 2
	mov		ax, [bp]
	cmp		ah, 0
	jz		loc_CB36
	push	word [bp + 2]
	call	sub_CB31
	pop		ax

sub_CB31:
	cmp		ah, 1
	jne		loc_CB1B

loc_CB36:
	jmp		dx

loc_CB38:
	mov		bx, loc_CB3C
	ret

loc_CB3C:
	mov		bx, loc_CB14
	jmp		dx

loc_CB41:
	jmp		dx

loc_CB43:
	cmp		al, 0
	jz		loc_CB7D
	cmp		al, 40h
	jb		loc_CB72
	cmp		al, 80h
	jb		loc_CB68
	cmp		al, 0C0h
	jb		loc_CB5D
	and		al, 3Fh
	mov		[cs:word_516E + 1], al
	mov		dx, loc_CB9E
	ret

loc_CB5D:
	and		ax, 3Fh
	mov		[cs:word_516E], ax
	mov		dx, loc_CBA6
	ret

loc_CB68:
	and		al, 3Fh
	mov		[cs:word_516E + 1], al
	mov		dx, loc_CB85
	ret

loc_CB72:
	and		ax, 3Fh
	mov		[cs:word_516E], ax
	mov		dx, loc_CB8D
	ret

loc_CB7D:
	mov		bx, loc_CA90
	mov		dx, ret_CB84
	ret

ret_CB84:
	ret

loc_CB85:
	mov		[cs:word_516E], al
	mov		dx, loc_CB8D
	ret

loc_CB8D:
	stosb								; store unpacked byte
	dec		word [cs:word_516E]
	jz		loc_CB96
	ret

loc_CB96:
	mov		dx, loc_CB43
	and		di, di
	js		loc_CBB7
	ret

loc_CB9E:
	mov		[cs:word_516E], al
	mov		dx, loc_CBA6
	ret

loc_CBA6:
	push	cx
	mov		cx, [cs:word_516E]
	rep stosb
	pop		cx
	mov		dx, loc_CB43
	and		di, di
	js		loc_CBB7
	ret

loc_CBB7:
	sub		di, 8000h					; di = 0x8087 - 0x8000
	mov		ax, es
	add		ax, 800h
	mov		es, ax
	ret


; out:
; word_63BA = packed data
; cx * 16 = length
sub_CBC3:								; CBC3
	call	sub_C96D
	call	sub_C9A2
	mov		ax, [word_63BA]
	mov		dx, 0
	push	ax
	call	file_read
	pop		ax
	add		cx, 15
	shr		cx, 4
	add		ax, cx
	ret


; input:
; ah - key char
; ds:si - resource keys, ending with 0xFF
load_resources:							; CBDD
	lodsb
	cmp		al, 0FFh
	jz		ret_CBF9
	mov		bx, [word_63BA]
	mov		[di], bx
	add		di, 2
	push	ax
	push	si
	push	di
	call	res_load
	mov		[word_63BA], ax
	pop		di
	pop		si
	pop		ax
	jmp		load_resources

ret_CBF9:
	ret


; Load a series of resources. Palette is taken from the last one.
;
; input:
; ah - ASCII character
; si - array of numbers ending with -1
;
; output:
; di - array of words pointers to data.
; Ends with num of loaded resources (byte) and fixed byte 0xFF.
; word_63BA -
load_resource_series:					; CBFA
	lodsb
	cmp		al, 0FFh
	jz		ret_CC16
	mov		bx, [word_63BA]
	mov		[di], bx
	add		di, 2
	push	ax
	push	si
	push	di
	call	sub_CBC3
	mov		[word_63BA], ax
	pop		di
	pop		si
	pop		ax
	jmp		load_resource_series

ret_CC16:
	ret
