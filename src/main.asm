	format	MZ
	heap	0
	stack	8000h	
	entry	main:start

segment main use16

start:
	; cs:5178

	call	dos:set_video_mode_and_timer
	call	arc:open_and_read_data_file

	mov		ax, 4c00h
	int		21h

word_5162:			dw ?									; cs:5162 - temporary storage for data segment (0F6C)
word_5164:			dw ?

segment text

arc_file_name:		db 'LOTUS.DAT', 0
arc_file_handle:	dw ?
arc_header:			times 2816 db 0

create_error:		db 'ERROR: Can''t create $', 0			; 3E34
open_error:			db 'ERROR: Can''t open $', 0			; 3E4A
read_error:			db 'ERROR: Read error in $', 0			; 3E5E
write_error:		db 'ERROR: Write error in $', 0			; 3E76
close_error:		db 'ERROR: Can''t close $', 0			; 3E8E

file_name:			dw ?									; 3EA4

memory_error:		db 'HELP! Memory full.', 0				; 3EA6

word_16F2:			dw ?
word_16FA:			dw ?
word_16FC:			dw ?
byte_16FE:			db ?
word_16FF:			dw ?

byte_1708:			db ?
word_1709:			dw ?
word_170B:			dw ?
byte_1715:			db ?
word_1716:			dw ?
byte_171F:			db ?
word_1720:			dw ?
word_1722:			dw ?
byte_172D:			db ?
byte_1745:			db ?

byte_3D6A:			db ?
word_3D6C:			dw ?
word_3D6E:			dw ?
word_3D70:			dw ?
byte_3D72:			db ?
dos_vid_mode:		db ?									; 3D73
byte_3D74:			db ?
word_3D76:			dw ?
word_3D78:			dw ?
word_3D7A:			dw ?
byte_3D7C:			db ?
word_3D7E:			dw ?
word_3D80:			dw ?
byte_3D86:			db ?
byte_3D87:			db ?
arr_3D88:			times 64 db 0							; 3D88: 64? maybe need less
byte_3DD0:			db ?
byte_3DD8:			db ?
word_3E08:			dw ?
byte_3E0E:			db ?
byte_3E0F:			db ?
byte_3E10:			db ?
word_3E12:			dw ?
word_3E14:			dw ?
word_3E16:			dw ?
word_3E18:			dw ?
word_3E1A:			dw ?
word_3E1C:			dw ?

word_3E20:			dw ?
word_3E22:			dw ?
byte_3E24:			db ?
byte_3E25:			db ?
byte_3E2C:			db ?
byte_3E2D:			db ?
word_3E2E:			dw ?

word_3E30:			dw ?
word_3E32:			dw ?
word_3EB9:			dw ?
byte_3EBB:			db ?

arr_3EEE:			times 16 dw 0							; 3EEE

playing_demo:		dw ?									; 63B6
word_63BA:			dw ?
word_63BC:			dw ?									; 63BC
word_63BE:			dw ?

arr_6F56:			times 256*3 db 0						; 6F56: palette

arr_DBB4:			times 14 db 0							; DBB4

word_20:			dw ?									; es:0020
tmp_cs:				dw ?									; es:0022

segment arc
	include 'archive.inc'

segment dos
	include 'dos.inc'
