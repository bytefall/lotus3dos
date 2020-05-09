; 
; Opens DAT file and reads 2816 bytes from the header.
;
open_and_read_data_file:			; C98C
	mov		dx, arc_file_name		; "LOTUS.DAT"
	call	file_open

	mov		[arc_file_handle], bx
	mov		ax, ds
	mov		dx, arc_header
	mov		cx, 2816
	call	file_read				; ax:dx - buffer,
									; bx - file handler,
									; cx - num of bytes to read
	retn
