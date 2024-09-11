screen_width = 336

unkn_00:            rw 8                                    ; 00
unkn_10:            rw 4                                    ; 10
word_18:            dw arr6_80                              ; 18: for Sound Blaster
word_1A:            dw arr6_80                              ; 1A: for Adlib
word_1C:            dw arr6_2DE                             ; 1C: for Roland
word_1E:            dw arr6_4C4                             ; 1E: for PC speaker
word_20:            dw ?                                    ; 20
byte_22:            db ?                                    ; 22
byte_23:            db ?                                    ; 23
byte_24:            db ?                                    ; 24
                    db ?                                    ; 25
word_26:            dw ?                                    ; 26 segment where T0X sound data is stored
word_28:            dw ?                                    ; 28
word_2A:            dw ?                                    ; 2A
word_2C:            dw ?                                    ; 2C
                    dw ?                                    ; 2E
word_30:            dw sub_2141                             ; 30
word_32:            dw sub_2141                             ; 32
word_34:            dw sub_2141                             ; 34
word_36:            dw sub_2141                             ; 36
word_38:            dw sub_2141                             ; 38
arr_3A:             db 0, 0, 0, 0, 0, 0                     ; 3A
arr_40:             db 0, 0, 0, 0, 0, 0                     ; 40
arr_46:             db 0, 0, 0, 0, 0, 0                     ; 46
arr_4C:             db 0, 0, 0, 0, 0, 0                     ; 4C
arr_52:             db 0, 0, 0, 0, 0, 0                     ; 52
arr_58:             db 0, 0, 0, 0, 0, 0                     ; 58
arr_5E:             db 0, 0, 0, 0, 0, 0                     ; 5E
arr_64:             db 0, 0, 0, 0, 0, 0                     ; 64
tune_bpms:          dw 1433, 1280, 1433, 1433, 896, 1433, 1433 ; 6A
word_78:            dw ?                                    ; 78
                    dw ?                                    ; 7A
word_7C:            dw ?                                    ; 7C
word_7E:            dw ?                                    ; 7E

arr6_80:            dw sub_221F, sub_24E5, sub_232B, sub_2494, sub_2557, sub_2507                               ; 80
arr8_8C:            dw arr9_CC, arr9_DE, arr9_F0, arr9_102, arr9_114, arr9_126, arr9_138, arr9_14A              ; 8C

arr24_9C:           dw 0                                    ; 9C
                    dw arr13_15C, arr13_169, arr13_176, arr13_183, arr13_190, arr13_19D, arr13_1AA
                    dw arr13_1B7, arr13_1C4, arr13_1D1, arr13_1DE, arr13_1EB, arr13_1F8, arr13_205, arr13_212
                    dw arr13_21F, arr13_22C, arr13_239, arr13_246, arr13_253, arr13_260, arr13_26D, arr13_27A

arr9_CC:            dw 0, 0, 0, 0, 0, 0, 0, 0, 0
arr9_DE:            dw 1, 0, 0, 0, 0, 0, 0, 0, 0
arr9_F0:            dw 2, 0, 0, 0, 0, 0, 0, 0, 0
arr9_102:           dw 3, 0, 0, 0, 0, 0, 0, 0, 0
arr9_114:           dw 4, 0, 0, 0, 0, 0, 0, 0, 0
arr9_126:           dw 5, 0, 0, 0, 0, 0, 0, 0, 0
arr9_138:           dw 6, 0, 0, 0, 0, 0, 0, 0, 0
arr9_14A:           dw 7, 0, 0, 0, 0, 0, 0, 0, 0

arr13_15C:          rb 13                                   ; 15C
arr13_169:          rb 13                                   ; 169
arr13_176:          rb 13                                   ; 176
arr13_183:          rb 13                                   ; 183
arr13_190:          rb 13                                   ; 190
arr13_19D:          rb 13                                   ; 19D
arr13_1AA:          rb 13                                   ; 1AA
arr13_1B7:          rb 13                                   ; 1B7
arr13_1C4:          rb 13                                   ; 1C4
arr13_1D1:          rb 13                                   ; 1D1
arr13_1DE:          rb 13                                   ; 1DE
arr13_1EB:          rb 13                                   ; 1EB
arr13_1F8:          rb 13                                   ; 1F8
arr13_205:          rb 13                                   ; 205
arr13_212:          rb 13                                   ; 212
arr13_21F:          rb 13                                   ; 21F - filled in sub_2A66 when song_num = 0
arr13_22C:          rb 13                                   ; 22C
arr13_239:          rb 13                                   ; 239
arr13_246:          rb 13                                   ; 246
arr13_253:          rb 13                                   ; 253
arr13_260:          rb 13                                   ; 260
arr13_26D:          rb 13                                   ; 26D
arr13_27A:          rb 13                                   ; 27A
                    db ?                                    ; 287

arr9_288:           db 3, 4, 5, 11, 12, 13, 19, 20, 21                                                          ; 288
arr77_291:          db 63, 48, 40, 35, 32, 29, 27, 26, 24, 23, 21, 20, 19, 18, 18                               ; 291
                    db 17, 16, 15, 15, 14, 13, 13, 12, 12, 11, 11, 10, 10, 10, 9, 9
                    db 8, 8, 8, 7, 7, 7, 6, 6, 6, 5, 5, 5, 5, 4, 4, 4
                    db 4, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0
                    db 0, 0, 0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 0, 0

arr6_2DE:           dw sub_25AD, sub_27DF, sub_26EB, sub_2661, sub_281D, sub_283C                               ; 2DE
arr8_2EA:           dw arr5_32A, arr5_32F, arr5_334, arr5_339, arr5_33E, arr5_343, arr5_348, arr5_34D           ; 2EA
arr24_2FA:          dw 0                                                                                        ; 2FA
                    dw arr5_352, arr5_357, arr5_35C, arr5_361, arr5_366, arr5_36B, arr5_370
                    dw arr5_375, arr5_37A, arr5_37F, arr5_384, arr5_389, arr5_38E, arr5_393, arr5_398
                    dw arr5_39D, arr5_3A2, arr5_3A7, arr5_3AC, arr5_3B1, arr5_3B6, arr5_3BB, arr5_3C0
arr5_32A:           db 0, 0, 0, 0, 0                        ; 32A
arr5_32F:           db 1, 0, 0, 0, 0                        ; 32F
arr5_334:           db 2, 0, 0, 0, 0                        ; 334
arr5_339:           db 3, 0, 0, 0, 0                        ; 339
arr5_33E:           db 4, 0, 0, 0, 0                        ; 33E
arr5_343:           db 5, 0, 0, 0, 0                        ; 343
arr5_348:           db 6, 0, 0, 0, 0                        ; 348
arr5_34D:           db 7, 0, 0, 0, 0                        ; 34D
arr5_352:           rb 5                                    ; 352
arr5_357:           rb 5                                    ; 357
arr5_35C:           rb 5                                    ; 35C
arr5_361:           rb 5                                    ; 361
arr5_366:           rb 5                                    ; 366
arr5_36B:           rb 5                                    ; 36B
arr5_370:           rb 5                                    ; 370
arr5_375:           rb 5                                    ; 375
arr5_37A:           rb 5                                    ; 37A
arr5_37F:           rb 5                                    ; 37F
arr5_384:           rb 5                                    ; 384
arr5_389:           rb 5                                    ; 389
arr5_38E:           rb 5                                    ; 38E
arr5_393:           rb 5                                    ; 393
arr5_398:           rb 5                                    ; 398
arr5_39D:           rb 5                                    ; 39D
arr5_3A2:           rb 5                                    ; 3A2
arr5_3A7:           rb 5                                    ; 3A7
arr5_3AC:           rb 5                                    ; 3AC
arr5_3B1:           rb 5                                    ; 3B1
arr5_3B6:           rb 5                                    ; 3B6
arr5_3BB:           rb 5                                    ; 3BB
arr5_3C0:           rb 5                                    ; 3C0
arr5_3C5:           db 127, 0, 0, 0, -1                     ; 3C5
arr23_3CA:          db 16, 0, 3, 2, 0, 0, 0, 0, 4, 4, 4, 4, 16, 16, 16, 16, 16, 0, 1, 2, 3, 9, -1
byte_3E1:           db ?                                    ; 3E1

arr_3E2:            db 0, 13h, 19h, 1Fh, 25h, 2Bh, 2Eh, 31h, 34h, 37h, 3Ah, 3Dh, 40h, 43h
                    db 46h, 49h
                    db 4Ch, 4Ch
                    db 4Fh, 4Fh
                    db 52h, 52h
                    db 55h, 55h
                    db 58h, 58h
                    db 5Bh, 5Bh
                    db 5Eh, 5Eh
                    db 61h, 61h
                    db 64h, 64h, 64h
                    db 67h, 67h, 67h
                    db 6Ah, 6Ah, 6Ah
                    db 6Dh, 6Dh, 6Dh
                    db 70h, 70h, 70h
                    db 73h, 73h, 73h
                    db 76h, 76h, 76h
                    db 79h, 79h, 79h, 79h
                    db 7Ch, 7Ch, 7Ch, 7Ch, 7Ch
                    db 7Fh, 7Fh, 7Fh
                    db 12, 12, 12, 12
                    db 11, 11, 11, 11, 11, 11, 11, 11
                    db 10, 10, 10, 10, 10, 10, 10, 10
                    db 9, 9, 9, 9, 9, 9, 9, 9
                    db 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
                    db 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
                    db 6, 6, 6, 6, 6, 6, 6, 6, 6, 6
                    db 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
                    db 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
                    db 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
                    db 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
                    db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

arr12_4A5:          dw 0FFFFh, 0F1A2h, 0E412h, 0D745h, 0CB30h, 0BFC8h
                    dw 0B505h, 0AADCh, 0A145h, 09838h, 08FADh, 0879Ch

word_4BD:           dw ?                                    ; 4BD
                    db ?                                    ; 4BF
word_4C0:           dw ?                                    ; 4C0
word_4C2:           dw ?                                    ; 4C2

arr6_4C4:           dw sub_28FF, sub_29D6, sub_2916, sub_296B, sub_29C0, sub_299D ; 4C4
arr6_4D0:           dw arr6_4DC, arr6_4E2, arr6_4E8, arr6_4EE, arr6_4F4, arr6_4FA ; 4D0
arr6_4DC:           rb 6                                    ; 4DC
arr6_4E2:           rb 6                                    ; 4E2
arr6_4E8:           rb 6                                    ; 4E8
arr6_4EE:           rb 6                                    ; 4EE
arr6_4F4:           rb 6                                    ; 4F4
arr6_4FA:           rb 6                                    ; 4FA
arr_500:            dw 0                                    ; 500
                    dw arr3_520, arr3_523, arr3_526, arr3_529, arr3_52C, arr3_52F, arr3_532
                    dw arr3_535, arr3_538, arr3_53B, arr3_53E, arr3_541, arr3_544, arr3_547, arr3_54A
arr3_520:           rb 3                                    ; 520
arr3_523:           rb 3                                    ; 523
arr3_526:           rb 3                                    ; 526
arr3_529:           rb 3                                    ; 529
arr3_52C:           rb 3                                    ; 52C
arr3_52F:           rb 3                                    ; 52F
arr3_532:           rb 3                                    ; 532
arr3_535:           rb 3                                    ; 535
arr3_538:           rb 3                                    ; 538
arr3_53B:           rb 3                                    ; 53B
arr3_53E:           rb 3                                    ; 53E
arr3_541:           rb 3                                    ; 541
arr3_544:           rb 3                                    ; 544
arr3_547:           rb 3                                    ; 547
arr3_54A:           rb 3                                    ; 54A
word_54D:           dw ?                                    ; 54D
word_54F:           dw ?                                    ; 54F
unk_551:            db 0, 0, 0, 0, 64h, 0, 70h, 17h, 64h, 0, 70h, 17h, 0, 0, 0 ; 551
                    db 0, 64h, 0, 70h, 17h, 32h, 0, 0F4h, 1, 0, 0, 0, 0, 32h, 0, 0B8h
                    db 0Bh, 32h, 0, 70h, 17h, 32h, 0, 70h, 17h, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 19h, 0, 0F4h, 1, 0, 0, 0
                    rb 25
song_num:           db ?                                    ; 5A9, 0 - sound of engines, 1.. - sound tracks
word_5AA:           dw ?                                    ; 5AA
word_5AC:           dw ?                                    ; 5AC
byte_5AE:           db ?                                    ; 5AE
                    db ?                                    ; 5AF
word_5B0:           dw ?                                    ; 5B0
word_5B2:           dw ?                                    ; 5B2
word_5B4:           dw ?                                    ; 5B4
word_5B6:           dw ?                                    ; 5B6
word_5B8:           dw ?                                    ; 5B8
word_5BA:           dw ?                                    ; 5BA
word_5BC:           dw ?                                    ; 5BC
word_5BE:           dw ?                                    ; 5BE
word_5C0:           dw ?                                    ; 5C0
word_5C2:           dw ?                                    ; 5C2
word_5C4:           rw 40                                   ; 5C4
unk_614:            rb 310                                  ; 614

arr_74A:            db 8, 0, 10, 6, 0, 1, 0, 48, 50, 11, 1, 2, 14, 34, 14, 10, 0, 0
                    db 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 41h, 28h, 0, 64h, 14h, 0Bh, 40h, 7, 64h
                    db 0, 0, 0, 32h, 32h, 32h, 32h, 32h, 64h, 50h, 5Ah, 46h, 64h, 64h, 40h, 0Ch, 40h, 0Ch
                    db 0, 0, 0, 14h, 32h, 32h, 46h, 3Ch, 64h, 50h, 5Ah, -1

                    db 8, 2, 10, 6, 0, 1, 0, 48, 50, 6, 0, 3, 15, 90, 7, 10, 0, 0, 63
                    db 0, 0, 0, 15h, 1Ah, 3Eh, 40h, 49h, 41h, 28h, 0, 64h, 14h, 0Bh, 40h, 7, 3
                    db 0, 0, 0, 32h, 32h, 32h, 32h, 32h, 64h, 50h, 5Ah, 64h, 54h, 64h, 40h, 0Ch, 40h, 0Ch
                    db 0, 0, 0, 37h, 16h, 0, 64h, 64h, 3Eh, 1Eh, 2Ah, -1

                    db 8, 4, 10, 6, 6, 1, 0, 8, 50, 0, 0, 3, 50, 0, 0, 10, 0, 0
                    db 32h, 32h, 64h, 32h, 32h, 32h, 32h, 32h, 32h, 2, 1, 0Fh, 64h, 14h, 0Bh, 40h, 7, 64h, 0, 0, 0
                    db 32h, 32h, 32h, 32h, 32h, 64h, 50h, 5Ah, 46h, 64h, 64h, 40h, 0Ch, 40h, 0Ch, 4, 4, 0, 2, 8, 7, 2, 64h, 64h, 64h, 64h, -1

                    db 8, 6, 10, 5, 3, 3, 0, 29, 50, 11, 1, 3, 49, 90, 7, 10, 0, 0
                    db 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 59h, 62h, 0, 64h, 0, 5, 7Fh, 7, 64h, 1Bh, 4, 3, 4Fh
                    db 32h, 32h, 32h, 32h, 4Fh, 3Ch, 38h, 58h, 64h, 64h, 40h, 0Ch, 40h, 0Ch, 0, 0, 0, 0, 0, 0, 0
                    db 64h, 64h, 64h, 64h, 17h, 0, 0Bh, 1, 3, 31h, 57h, 0Bh, 0Ah, 0, 0
                    db 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 4Eh, 55h, 52h, 64h, 1Ah, 0, 3Fh, 0Eh, 64h, 4, 3, 0
                    db 32h, 32h, 32h, 32h, 32h, 64h, 64h, 64h, 64h, 64h, 64h, 40h, 0Ch, 40h, 0Ch, 0, 0, 0
                    db 32h, 32h, 32h, 46h, 64h, 64h, 64h, 64h, -1

                    db 8, 8, 10, 5, 0, 1, 0, 29, 50, 11, 0, 3, 49, 90, 7, 10, 0, 0
                    db 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 41h, 28h, 0, 64h, 2, 0Eh, 0, 9, 64h
                    db 64h, 3, 4, 0, 0, 4, 0, 26h, 64h, 64h, 64h, 64h, 64h, 64h, 58h, 0Ch, 40h, 0Ch, 0, 3, 0, 0, 0, 0, 0, 64h, 64h, 64h, 64h, -1

                    db 8, 10, 10, 8, 0, 3, 0, 48, 50, 11, 1, 1, 0, 90, 7, 10
                    db 0, 0, 25h, 24h, 43h, 57h, 63h, 43h, 32h, 20h
                    db 0, 64h, 64h, 5Ch, 64h, 14h, 0Bh, 40h, 7, 64h
                    db 0, 0, 0, 0, 32h, 3Ah, 3Eh, 32h, 64h, 64h, 34h, 13h, 64h, 64h, 40h, 0Ch, 40h, 0Ch
                    db 0, 0, 0, 0, 0, 0, 5, 64h, 62h, 64h, 64h, 0Ch, 32h, 0Bh, 1, 2, 2Bh, 5Ah, 7, 0Ah
                    db 0, 0, 28h, 43h, 56h, 57h, 16h, 28h, 37h, 42h, 4Ch, 41h, 28h
                    db 0, 64h, 14h, 0Bh, 40h, 7h, 64h
                    db 0, 0, 0, 32h, 32h, 32h, 32h, 32h, 64h, 50h, 5Ah, 46h, 64h, 64h, 40h, 0Ch, 40h, 0Ch
                    db 0, 0, 0, 14h, 32h, 32h, 46h, 3Ch, 64h, 50h, 5Ah, -1

                    db 8, 12, 10, 5, 5, 15, 0, 48, 50, 11, 1, 2, 112, 90, 7, 10, 0, 0
                    db 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 41h, 28h, 0, 64h, 14h, 0Bh, 40h, 7, 64h
                    db 0, 0, 0, 32h, 32h, 32h, 32h, 32h, 64h, 50h, 5Ah, 46h, 64h, 64h, 40h, 0Ch, 40h, 0Ch
                    db 0, 0, 0, 64h, 64h, 63h, 64h, 64h, 64h, 64h, 64h, 31h, 32h, 0Bh, 1, 1, 0, 5Ah, 7, 0Ah
                    db 0, 0, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 41h, 28h, 0, 64h, 14h, 0Bh, 40h, 7, 64h
                    db 0, 0, 0, 32h, 32h, 32h, 32h, 32h, 64h, 50h, 5Ah, 46h, 64h, 64h, 40h, 0Ch, 40h, 0Ch
                    db 0, 0, 0, 14h, 32h, 32h, 46h, 64h, 64h, 63h, 5Ah, 18h, 32h, 0Bh, 1, 3, 1Bh, 5Ah, 7, 0Ah
                    db 0, 0, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 41h, 28h, 00h, 64h, 14h, 0Bh, 40h, 7, 64h
                    db 0, 0, 0, 32h, 32h, 32h, 32h, 32h, 64h, 50h, 5Ah, 46h, 64h, 64h, 40h, 0Ch, 40h, 0Ch
                    db 0, 0, 0, 14h, 32h, 32h, 46h, 64h, 64h, 64h, 64h, 37h, 32h, 0Bh, 1, 3, 4, 5Ah, 7, 0Ah
                    db 0, 0, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 41h, 28h, 0, 64h, 14h, 0Bh, 40h, 7, 64h
                    db 0, 0, 0, 32h, 32h, 32h, 32h, 32h, 64h, 50h, 5Ah, 46h, 64h, 64h, 40h, 0Ch, 40h, 0Ch
                    db 0, 0, 0, 14h, 32h, 32h, 46h, 64h, 64h, 64h, 64h, -1

                    db 8, 14, 10, 10, 0, 3, 0, 48, 50, 11, 1, 3, 43, 90, 7, 10, 0, 0
                    db 32h, 32h, 32h, 32h, 15h, 32h, 32h, 32h, 12h, 64h, 64h, 0, 5Eh, 19h, 0, 40h, 1, 64h
                    db 0, 0, 0, 32h, 32h, 32h, 32h, 32h, 64h, 50h, 5Ah, 46h, 64h, 64h, 40h, 0Ch, 40h, 0Ch, 0, 0, 12h
                    db 0, 0, 0, 3Ah, 64h, 64h, 64h, 64h, 30h, 32h, 10h, 0, 1, 6Dh, 5Ah, 7, 0Ah
                    db 0, 0, 31h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 41h, 28h, 0, 64h, 0Fh, 0Dh, 7Fh, 7, 64h, 64h
                    db 2, 1, 7, 64h, 32h, 32h, 32h, 64h, 0, 15h, 46h, 30h, 64h, 4Eh, 0Ch, 40h, 0Ch
                    db 2, 1, 37h, 14h, 32h, 32h, 46h, 64h, 64h, 62h, 64h, -1

                    db 8, 16, 10, 6, 6, 3, 0, 30h, 32h, 0Bh, 1, 3, 0Eh, 5Ah, 7, 0Ah
                    db 0, 0, 32h, 64h, 32h, 32h, 46h, 24h, 19h, 15h, 16h, 41h, 28h, 0, 64h, 14h, 0Bh, 40h, 7, 64h
                    db 0, 0, 0, 0, 0, 5, 32h, 32h, 64h, 63h, 64h, 46h, 64h, 64h, 40h, 0Ch, 40h, 0Ch
                    db 0, 0, 0, 0, 4, 2, 27h, 64h, 64h, 64h, 64h, 30h, 32h, 0Bh, 1, 3, 33h, 5Ah, 7, 0Ah
                    db 0, 0, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 32h, 41h, 28h, 0, 64h, 14h, 0Bh, 40h, 7, 64h
                    db 0, 0, 0, 32h, 32h, 32h, 32h, 32h, 64h, 50h, 5Ah, 46h, 64h, 64h, 40h, 0Ch, 40h, 0Ch
                    db 0, 0, 0, 0, 19h, 32h, 46h, 64h, 64h, 64h, 64h, -1

                    db 5, 0, 0, 2, 0, -1
                    db 5, 0, 8, 2, 1, -1
                    db 5, 0, 16, 2, 2, -1
                    db 5, 0, 24, 2, 3, 24, 50, 24, -1
                    db 5, 0, 32, 2, 4, -1
                    db 5, 0, 40, 2, 5, -1
                    db 5, 0, 48, 2, 6, -1
                    db 5, 0, 56, 2, 7, -1
                    db 5, 0, 64, 2, 8, -1
                    db 16, 0, 3, 0, 4, 4, 4, 4, 4, 4, 0, 0, 8, 0, 1, 2, 3, 4, 5, 6, 7, 9, -1

                    db 0FFh                                 ; B82

arr_B83:            dw 0BB2h, 0BB2h, 0C57h, 0, 0, 0, 0, 0, 0C36h, 0, 0, 0
                    dw 0BD3h, 0C15h, 0, 0, 0, 0, 0, 0, 0BF4h, 0, 0, 0A780h
                    dw 0, 0C01h, 2700h
                    ; db 0, 80h, 0A7h, 0, 0, 1, 0Ch, 0, 27h
                    db 1, 2, 0FEh, 0, 0, 0, 0, 0, 0, 13h, 0F3h, 13h, 0F3h, 13h, 0F3h, 14h, 0F3h, 13h, 0F2h, 12h, 0F2h, 0, 0, 0, 0, 96h ; 0BB0
arr_BD3:            db 99h, 0, 2, 0, 10h, 0, 1, -1, 1, 1, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 0F0h ; BD3
arr_BF4:            db 80h, 0, 0, 0, 0, 1, 0D8h, -1, 0, 0, 0, 0, 0, 0, 0, 0, 42h, 5Ch, 34h, 01h, 17h, 0BCh, 5Bh, 0, 0D4h, 57h, 0, 5Ah, 90h, 0B2h, 4Dh, 5Ah, 0 ; BF4
arr_C15:            db 4Eh, 20h, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1Ch, 9Fh, 3Bh, 0EFh, 0FAh, 12h, 7Dh, 7Dh, 7Dh, 0D0h, 7Ah, -1, 0, 0, 0, 0, 0B4h ; C15
arr_C36:            db 76h, 0Fh, 0, 0, 2, 4, 0D8h, -1, 0, 0, 0, 0, 0, 0, 0, 0, 59h, 37h, 7Fh, 1, 1, 1, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 3Ch ; C36
arr_C57:            db 4Eh, 13h, 2, 0, 4, 3, 3, 0Ch, 0Eh, 0F5h, 0, 0, 0, 0, 0, 0, 1Ch, 9Fh, 3Bh, 0EFh, 0FAh, 12h, 7Dh, 7Dh, 7Dh, 0D0h, 7Ah, -1, 0, 0, 0, 0 ; C57 

arr48_C77:          dw 200h, 207h, 20Fh, 217h, 21Eh, 226h, 22Eh, 236h
                    dw 23Fh, 247h, 250h, 258h, 261h, 26Ah, 273h, 27Ch
                    dw 285h, 28Eh, 298h, 2A2h, 2ABh, 2B5h, 2BFh, 2CAh
                    dw 2D4h, 2DFh, 2E9h, 2F4h, 2FFh, 30Ah, 316h, 321h
                    dw 32Dh, 339h, 345h, 351h, 35Dh, 36Ah, 376h, 383h
                    dw 390h, 39Eh, 3ABh, 3B9h, 3C7h, 3D5h, 3E3h, 3F1h

arr_intro_video:                                            ; CD7
                    db 00h, 01h, 02h, 03h, 04h, 05h, 06h, 07h, 08h, 09h, 0Ah, 0Bh, 0Ch, 0Dh, 0Eh, 0Fh
                    db 10h, 11h, 12h, 13h, 14h, 15h, 16h, 17h, 18h, 19h, 1Ah, 1Bh, 1Ch, 1Dh, 1Eh, 1Fh
                    db 20h, 21h, 22h, 23h, 24h, 25h, 26h, 27h, 28h, -1

arr_D01:            rb 82                                   ; D01

prot_fonts:         db 3, -1                                ; D53
prot_res_ids:       db 21h, 22h, -1                         ; D55
prot_res_ptr:       times 2 dw 0                            ; D58
prot_d5c:           dw 0                                    ; D5C
prot_d5e:           dw 0                                    ; D5E
prot_code:          dw 0                                    ; D60, actual "??" code is prot_code + 1
prot_text:          db 'ENTER CODE FOR WINDOW '             ; D62
prot_text_num:      db '??', 0                              ; D78
prot_d7b:           dw 2020h                                ; D7B
prot_d7d:           db 20h                                  ; D7D
; entered code: D7E, D7F, D80
prot_d7e:           dw 2020h                                ; D7E
prot_d80:           db 20h                                  ; D80
                    db 0                                    ; D81
prot_d82:           db 3                                    ; D82
prot_d83:                                                   ; D83
                    db 0, 0,    0, 4,   0, 8,   0, 10,  0, 13,  0, 17,  0, 19,  0, 21
                    db 0, 25,   0, 28,  0, 30,  0, 35,  1, 2,   1, 5,   1, 11,  1, 12
                    db 1, 16,   1, 20,  1, 24,  1, 29,  1, 31,  1, 34,  2, 0,   2, 2
                    db 2, 4,    2, 6,   2, 10,  2, 12,  2, 14,  2, 17,  2, 18,  2, 21
                    db 3, 22,   3, 1,   3, 3,   3, 5,   3, 7,   3, 9,   3, 11,  3, 13
                    db 3, 15,   3, 16,  3, 21,  4, 11,  4, 2,   4, 4,   4, 7,   4, 9

prot_de3:           db 'D', 'C', 'B', 'A', '6', '?', '>', '=', 'H', 'G', 'F', 'E'   ; DE3
magn_fields_ids:    db 2, 3, 4, 5, 6, 7, 8, 9, 0Ah, 0Bh, 0Ch, 0Dh, 0Eh, 0Fh         ; DEF
                    db 10h, 11h, 12h, 13h, 14h, 15h, 16h, 17h, -1
magn_fields_ptr:    rw 22                                   ; E06
credits_ids:        db 19h, 1Bh, 1Ch, 1Dh, 1Eh, -1          ; E32
credits_ptr:        rw 8                                    ; E38
credits_txt:                                                ; E48
                    dw 118 + 43 * screen_width
                    db 'A GAME', 0
                    dw 146 + 67 * screen_width
                    db 'BY', 0
                    dw 69 + 91 * screen_width
                    db 'ANDREW MORRIS', 0
                    dw 139 + 115 * screen_width
                    db 'AND', 0
                    dw 62 + 139 * screen_width
                    db 'SHAUN SOUTHERN', 0
                    dw 0FBA0h
                    dw 76 + 67 * screen_width
                    db 'LEVEL DESIGN', 0
                    dw 146 + 91 * screen_width
                    db 'BY', 0
                    dw 69 + 115 * screen_width
                    db 'PETER LIGGETT', 0
                    dw 0FCB8h
                    dw 125 + 67 * screen_width
                    db 'MUSIC', 0
                    dw 146 + 91 * screen_width
                    db 'BY', 0
                    dw 62 + 115 * screen_width
                    db 'PATRICK PHELAN', 0
                    dw 0FCB8h
                    dw 69 + 43 * screen_width
                    db 'PC CONVERSION', 0
                    dw 146 + 67 * screen_width
                    db 'BY', 0
                    dw 48 + 91 * screen_width
                    db 'JON MEDHURST FOR', 0
                    dw 55 + 115 * screen_width
                    db 'CYGNUS SOFTWARE', 0
                    dw 52 + 139 * screen_width
                    db 'ENGINEERING LTD.', 0
                    dw 0FA88h
                    dw 62 + 43 * screen_width
                    db 'COPYRIGHT 1993', 0
                    dw 55 + 67 * screen_width
                    db 'MAGNETIC FIELDS', 0
                    dw 10 + 91 * screen_width
                    db '(SOFTWARE DESIGN) LTD.', 0
                    dw 48 + 115 * screen_width
                    db 'GREMLIN GRAPHICS', 0
                    dw 73 + 139 * screen_width
                    db 'SOFTWARE LTD.', 0
                    dw 0F858h
                    dw 0FFFFh
word_F77:           dw ?                                    ; F77
main_menu_res_ids:  db 14h, 15h, 16h, 17h, 18h, 19h, 1Ah, 1Bh, 1Fh, 20h, -1 ; F79
main_menu_fnt_ids:  db 3, 4, 5, -1                          ; F84
res_ptr_I14:        dw ?                                    ; F88 = *I14
res_ptr_I15:        dw ?                                    ; F8A = *I15
res_ptr_I16:        dw ?                                    ; F8C = *I16
res_ptr_I17:        dw ?                                    ; F8E = *I17
res_ptr_I18:        dw ?                                    ; F90 = *I18
res_ptr_I19:        dw ?                                    ; F92 = *I19
res_ptr_I1A:        dw ?                                    ; F94 = *I1A
res_ptr_I1B:        dw ?                                    ; F96 = *I1B
res_ptr_I1F:        dw ?                                    ; F98 = *I1F
res_ptr_I20:        dw ?                                    ; F9A = *I20
curr_menu_col:      dw 0                                    ; F9C
curr_menu_row:      dw 0                                    ; F9E
unk_FA0:            db 0xFF, 0xFF, 0xE2, 0x39, 0xFF, 0xFF, 0x2E, 0x52, 0xFF, 0xFF, 0x13, 0x3A, 0x01, 0x00, 0xE6, 0x16
                    db 0x01, 0x00, 0xE2, 0x16, 0x01, 0x00, 0xE8, 0x16, 0x01, 0x00, 0xEA, 0x16, 0x04, 0x00, 0xEE, 0x16
                    db 0x01, 0x00, 0xEC, 0x16, 0xFF, 0xFF, 0x4F, 0x3B, 0x01, 0x00, 0xE4, 0x16, 0xFF, 0xFF, 0xAC, 0x3A
                    db 0xFF, 0xFF, 0x35, 0x41, 0xFF, 0xFF, 0x44, 0x3A, 0xFF, 0xFF, 0x19, 0x40
dword_FDC:          dd ?                                    ; FDC
word_FE0:           dw ?                                    ; FE0
arr176_FE2:         db 1, 1, 0, 0, 0, 0, 0, 0, 1, 2, 1
                    db 0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0
                    db 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 1
                    db 2, 2, 2, 2, 1, 0, 0, 1, 2, 2, 2
                    db 2, 2, 1, 0, 1, 1, 1, 2, 1, 1, 1
                    db 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0
                    db 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2
                    db 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
word_1092:          dw ?                                    ; 1092
word_1094:          dw ?                                    ; 1094
word_1096:          dw ?                                    ; 1096
word_1098:          dw ?                                    ; 1098
word_109A:          dw ?                                    ; 109A
word_109C:          db 7Ch, 3Dh, 0, 0
                    db 0D8h, 35h, 0, 0
                    db 8Ch, 3Dh, 2, 0
                    db 7Ch, 3Dh, 0, 0
                    db 0D8h, 35h, 2, 0
                    db 8Ch, 3Dh, 1, 0
                    db 7Ch, 3Dh, 0, 0
                    db 0D8h, 35h, 1, 0
                    db 8Ch, 3Dh, 0, 0
                    db 9Ch, 3Dh, 0, 0
                    db 0D8h, 35h, 0, 0
                    db 0B3h, 3Dh

arr_10CA:           db 60h, 'PRESS KEY FOR LEFT', 0, -1     ; 10CA
                    db 60h, 'PRESS KEY FOR RIGHT', 0, -1
                    db 60h, 'PRESS KEY FOR CHANGE UP A GEAR', 0, -1
                    db 60h, 'PRESS KEY FOR CHANGE DOWN A GEAR', 0, -1
                    db 60h, 'PRESS KEY FOR ACCELERATE', 0, -1
                    db 60h, 'PRESS KEY FOR BRAKE', 0, -1

arr_116A:           db 5Ah, 'THAT KEY IS ALREADY USED', 0   ; 116A
                    db 66h, 'PRESS SPACE THEN SELECT ANOTHER', 0, -1
                    db 5Ah, 'PUSH JOYSTICK TO TOP LEFT', 0
                    db 66h, 'THEN PRESS FIRE', 0, -1
                    db 5Ah, 'PUSH JOYSTICK TO BOTTOM RIGHT', 0
                    db 66h, 'THEN PRESS FIRE', 0, -1
                    db 5Ah, 'PUSH JOYSTICK TO CENTRE', 0
                    db 66h, 'THEN PRESS FIRE', 0, -1

word_122F:          dw ?                                    ; 122F
word_1231:          dw ?                                    ; 1231
word_1233:          dw ?                                    ; 1233
arr_1235:           dw 0                                    ; 1235
                    db 39h, 43h, 0, 0
                    db 33h, 43h, 0, 0
                    db 69h, 43h, 0, 0
                    db 55h, 42h, 3, 0
                    db 55h, 42h, 5, 0
                    db 55h, 42h, 1, 0
                    db 55h, 42h, 4, 0
                    db 55h, 42h, 6, 0
                    db 55h, 42h, 2, 0
                    db 55h, 42h, 8, 0
                    db 55h, 42h, 7, 0
                    db 55h, 42h, 0, 0
                    db 4Eh, 43h, 0, 0
                    db 4Eh, 43h, 0, 0
                    db 4Eh, 43h

word_1271:          dw 0                                    ; 1271
word_1273:          dw 0, 12h, 36h, 12h, 5Dh, 12h, 84h, 7Ah, 36h, 7Ah, 5Dh, 0E2h, 36h, 0E2h, 5Dh, 0E2h, 84h

y_pos:              dw ?                                    ; 1295
x_pos:              dw ?                                    ; 1297
word_1299:          dw ?                                    ; 1299
str_ptr:            dw ?                                    ; 129B
word_129D:          dw ?                                    ; 129D
word_129F:          dw ?                                    ; 129F
word_12A1:          dw ?                                    ; 12A1
byte_12A3:          db ?                                    ; 12A3
byte_12A4:          db ?                                    ; 12A4
                    db ?                                    ; 12A5
car_sel_res_ids:    db 1Dh, 1Eh, 10h, 11h, 12h, 13h, -1     ; 12A6
car_sel_res_ptr:    rw 6                                    ; 12AD
tuner_fnt_ids:      db 6, -1                                ; 12B9
tuner_res_ids:      db 1Ch, -1                              ; 12BB
tuner_res_ptr:      dw ?                                    ; 12BD
next_race_txt:      db 'NEXT RACE', 0                       ; 12BF
course_txt:         db 'COURSE - '                          ; 12C9
course_val_txt:     db 'xxxxxxxxxxxx', 0                    ; 12D2
level_race_txt:     db 'LEVEL '                             ; 12DF
level_txt:          db '1 - RACE '                          ; 12E5
race_start_txt:     db '99 OF '                             ; 12EE
race_end_txt:       db '99', 0                              ; 12F4
user_course_txt:    db 'USER DEFINED COURSE', 0             ; 12F7
distance_txt:       db '01.234 KM OVER '                    ; 130B
stages_txt:         db '99 STAGES', 0                       ; 131A
laps_txt:           db '99 LAPS OF 01.234 KM', 0            ; 1324
                    db 0                                    ; 1339
race_result_txt:    db 'RACE RESULT', 0                     ; 133A
race_columns_txt:   db 'POS   NAME              TIME    PTS' ; 1346
race_time_txt:      db '99.99.9'                            ; 1369
retired_txt:        db 'RETIRED'                            ; 1370
cast_txt:           db 'nijel mainsail      '               ; 1377
                    db 'alain phosphate     '
                    db 'm. carburettor      '
                    db 'ayrton sendup       '
                    db 't. hairy bootson    '
                    db 'mickey louder       '
                    db 'ricardo pastry      '
                    db 'nelson pickets      '
                    db 'demon hill          '
                    db 'crashhard banger    '
                    db 'rissole brookes     '
                    db 'stag bloomvest      '
                    db 'merry walker        '
                    db 'macaulay schenker   '
                    db 'jackie stewpot      '
                    db 'starling mess       '
                    db 'derek werek         '
                    db 'vim clark           '
arr_14DF:           times 20 db ' '                         ; 14DF..=14F2
arr_14F3:           times 20 db ' '                         ; 14F3..=1506
arr_1507:           db 20, 15, 12, 10, 8, 6, 4, 3, 2, 1     ; 1507
                    rb 10                                   ; 1511..=151A
arr_151B:           db '20151210 8 6 4 3 2 1 0 0 0 0 0 0 0 0 0 0' ; 151B
arr_1543:           rb 40                                   ; 1543
word_156B:          dw ?                                    ; 156B
word_156D:          dw ?                                    ; 156D
scores_so_far_txt:  db 'SCORES SO FAR', 0                   ; 156F
final_scores_txt:   db 'FINAL SCORES', 0                    ; 157D 
pos_name_pts_txt:   db 'POS   NAME               PTS'       ; 158A
arr_15A6:           rb 20                                   ; 15A6
arr_15BA:           rw 20                                   ; 15BA
current_pos_txt:    db 'CURRENT POSITIONS', 0               ; 15E2
final_pos_txt:      db 'FINAL POSITIONS', 0                 ; 15F4
question_marks_txt: db '????????'                           ; 1604
gears_txt:          db ' 1ST'                               ; 160C
                    db ' 2ND'                               ; 1610
                    db ' 3RD'                               ; 1614
                    db ' 4TH'                               ; 1618
                    db ' 5TH'                               ; 161C
                    db ' 6TH'                               ; 1620
                    db ' 7TH'                               ; 1624
                    db ' 8TH'                               ; 1628
                    db ' 9TH'                               ; 162C
                    db '10TH'                               ; 1630
                    db '11TH'                               ; 1634
                    db '12TH'                               ; 1638
                    db '13TH'                               ; 163C
                    db '14TH'                               ; 1640
                    db '15TH'                               ; 1644
                    db '16TH'                               ; 1648
                    db '17TH'                               ; 164C
                    db '18TH'                               ; 1650
                    db '19TH'                               ; 1654
                    db '20TH'                               ; 1658

arr_165C:           dw easy_lvl_scrs_txt, easy_lvl_pts_txt, med_lvl_scrs_txt, med_lvl_pts_txt, hard_lvl_scrs_txt, hard_lvl_pts_txt ; 165C
easy_lvl_scrs_txt:  db 'EASY LEVEL SCORES', 0               ; 1668
easy_lvl_pts_txt:   db 'EASY LEVEL POINTS', 0               ; 167A
med_lvl_scrs_txt:   db 'MEDIUM LEVEL SCORES', 0             ; 168C
med_lvl_pts_txt:    db 'MEDIUM LEVEL POINTS', 0             ; 16A0
hard_lvl_scrs_txt:  db 'HARD LEVEL SCORES', 0               ; 16B4
hard_lvl_pts_txt:   db 'HARD LEVEL POINTS', 0               ; 16C6

cfg_file_name:      db 'LOTUS.CFG', 0                       ; 16D8

; 16E2..=1F08, len = 2087
cfg_data:           dw 0, 0, 1, 1, 0, 0                     ; 16E2
course_type:        dw ?                                    ; 16EE: T1, T2, T3, Circular, Unknown
                    dw ?                                    ; 16F0
word_16F2:          dw ?                                    ; 16F2
snd_setting:        dw 3                                    ; 16F4: 1 - Adlib, 2 - Sound Blaster, 3 - PC speaker, 4 - sound off
word_16F6:          dw 3                                    ; 16F6: same as above
word_16F8:          dw ?                                    ; 16F8
word_16FA:          dw ?                                    ; 16FA
word_16FC:          dw ?                                    ; 16FC
byte_16FE:          db ?                                    ; 16FE
word_16FF:          dw ?                                    ; 16FF
arr_1701:           db 'KMHP', 1Ch, 'R'                     ; 1701
byte_1707:          db 0                                    ; 1707
byte_1708:          db ?                                    ; 1708
word_1709:          dw ?                                    ; 1709
word_170B:          dw ?                                    ; 170B
                    rb 8                                    ; 170D..=1714
byte_1715:          db ?                                    ; 1715
word_1716:          dw ?                                    ; 1716
arr_1718:           db 7Fh, 7Fh, 7Fh, 7Fh, 7Fh, 7Fh         ; 1718
byte_171E:          db 0                                    ; 171E
byte_171F:          db ?                                    ; 171F
word_1720:          dw ?                                    ; 1720
word_1722:          dw ?                                    ; 1722
                    rb 8                                    ; 1724
arr_172C:           rb 128                                  ; 172C
p1_name:            db 'PLAYER 1    '                       ; 17AC
p2_name:            db 'PLAYER 2    '                       ; 17B8
cfg_keys:           db 'pwrwvwhnm-30'                       ; 17C4: 64 keys (12 chars each), e.g.: pwrwvwhnm-30
                    db 'xmqiyskas-80'
                    db 'uvqsnpbcm-70'
                    db 'cwvbqpcav-50'
                    db 'sfxuxxxxp-60'
                    db 'hsywyskcg-50'
                    db 'ivvemmkoz-50'
                    db 'annsmqlpn-60'
                    db 'vzvdophcy-50'
                    db 'rtlmyjkhb-60'
                    db 'errurv   -67'
                    db 'nsssxxxxs-60'
                    db 'wsvuqpcsj-70'
                    db 'oundefacg-99'
                    db 'gxwdypacv-68'
                    db 'bz zf bat-90'
                    db 'lwnjwkacn-90'
                    db 'iyvvnveqr-35'
                    db 'kazznikai-45'
                    db 'fgqljgdaf-65'
                    db 'mffsrpydu-60'
                    db 'plqtzqdpe-80'
                    db 'zkzgkjkkk-50'
                    db 'tggjggttt-63'
                    db 'afzybqcjt-70'
                    db 'jboukjhka-99'
                    db 'dasicotet-80'
                    db 'xdnuseece-85'
                    db 'qdscjvebt-75'
                    db 'skgyxxxxk-57'
                    db 'ykgjwvnak-92'
                    db 'wjmegmeqh-60'
                    db 'crripwbxx-28'
                    db 'qpwmvqkcq-34'
                    db 'xgpgpzhhs-42'
                    db 'fgwlsyckm-51'
                    db 'prrumpumv-68'
                    db 'nancxxxxz-39'
                    db 'ipwonwobp-65'
                    db 'rlqydvaka-48'
                    db 'hdmoqfaka-51'
                    db 'wxqbqmdxd-88'
                    db 'udonajhal-47'
                    db 'nkwcxxxxk-33'
                    db 'aonglqktc-63'
                    db 'zxjghbkhf-70'
                    db 'dpgtqkbhq-42'
                    db 'ipmijobhq-62'
                    db 'muyurwfha-86'
                    db 'pprggqfvl-52'
                    db 'jpiqkuhce-65'
                    db 'eiibggafe-48'
                    db 'cigiuqclt-92'
                    db 'knhuphhke-64'
                    db 'vvoshgsig-86'
                    db 'rghsvbret-89'
                    db 'ydoeractj-86'
                    db 'gxqfsumpp-45'
                    db 'tvqlsyufu-89'
                    db 'wmqhymtvj-85'
                    db 'okuobjiac-86'
                    db 'fimjjibck-68'
                    db 'sigtxxxxh-35'
                    db 'wnqkmphvn-80'

game_keys:          db 'x        -00'                       ; 1AC4: 9 keys (12 chars each), e.g.: xKXCJGFJH-33
                    db '         -00'
                    db '         -00'
                    db '         -00'
                    db '         -00'
                    db '         -00'
                    db '         -00'
                    db '         -00'
                    db '         -00'
                    db '         -00'
game_code:          db 'x        -00'                       ; 1B3C

arr_1B48:           db 'mf ltd      '                       ; 1B48
                    db 40h, 4Bh, 4Ch                        ; 5000000
                    db 0                                    ; Esprit S4
                    db 'shaun       '
                    db 0, 9, 3Dh                            ; 4000000
                    db 40h                                  ; Elan SE
                    db 'andrew      '
                    db 0C0h, 0C6h, 2Dh                      ; 3000000
                    db 80h                                  ; M200
                    db 'peter       '                       ; 2500000
                    db 0A0h, 25h, 26h
                    db 0
                    db 'chris       '
                    db 80h, 84h, 1Eh
                    db 40h
                    db 'andy        '
                    db 60h, 0E3h, 16h
                    db 80h
                    db 'doug        '
                    db 40h, 42h, 0Fh
                    db 0
                    db 'dave        '
                    db 20h, 0A1h, 7
                    db 40h
                    db 'luga        '
                    db 40h, 0Dh, 3
                    db 80h
                    db 'michelangelo'
                    db 0A0h, 86h, 1
                    db 0
                    db 'sout        '
                    db 32h, 0, 0
                    db 0
                    db 'ric         '
                    db 28h, 0, 0
                    db 40h
                    db 'craig       '
                    db 01Eh, 0, 0
                    db 80h
                    db 'nige        '
                    db 19h, 0, 0
                    db 0
                    db 'rachell     '
                    db 20, 0, 0
                    db 40h
                    db 'esther      '
                    db 15, 0, 0
                    db 80h
                    db 'rich        '
                    db 10, 0, 0
                    db 0
                    db 'stuart      '
                    db 5, 0, 0
                    db 40h
                    db 'tim         '
                    db 2, 0, 0
                    db 80h
                    db 'andy        '
                    db 1, 0, 0
                    db 0
                    db 'a morris    '
                    db 40h, 4Bh, 4Ch
                    db 0
                    db 'janet       '
                    db 00h, 09h, 3Dh
                    db 40h
                    db 'lorna       '
                    db 0C0h, 0C6h, 2Dh
                    db 80h
                    db 'vicky       '
                    db 0A0h, 25h, 26h
                    db 0
                    db 'carly       '
                    db 80h, 84h, 1Eh
                    db 40h
                    db 'gary        '
                    db 60h, 0E3h, 16h
                    db 80h
                    db 'sharon x 2  '
                    db 40h, 42h, 0Fh
                    db 0
                    db 'fiona       '
                    db 20h, 0A1h, 07h
                    db 40h
                    db 'sam the dog '
                    db 40h, 0Dh, 03h
                    db 80h
                    db 'all vegans  '
                    db 0A0h, 86h, 01h
                    db 0
                    db 'brian hobbs '
                    db 50, 0, 0
                    db 0
                    db 'stacey green'
                    db 40, 0, 0
                    db 40h
                    db 'ross morris '
                    db 30, 0, 0
                    db 80h
                    db 'chris clark '
                    db 25, 0, 0
                    db 0
                    db 'andy turner '
                    db 20, 0, 0
                    db 40h
                    db 'iwan        '
                    db 15, 0, 0
                    db 80h
                    db 'eric        '
                    db 10, 0, 0
                    db 0
                    db 'dafydd      '
                    db 5, 0, 0
                    db 40h
                    db 'darren      '
                    db 2, 0, 0
                    db 80h
                    db 'tom         '
                    db 1, 0, 0
                    db 0
                    db 'peter       '
                    db 40h, 4Bh, 4Ch
                    db 0
                    db 'ernie       '
                    db 0, 09h, 3Dh
                    db 40h
                    db 'gaz hawley  '
                    db 0C0h, 0C6h, 02Dh
                    db 80h
                    db 'frank       '
                    db 0A0h, 25h, 26h
                    db 0
                    db 'annette     '
                    db 80h, 84h, 1Eh
                    db 40h
                    db 'ritchie     '
                    db 60h, 0E3h, 16h
                    db 80h
                    db 'sue         '
                    db 40h, 42h, 0Fh
                    db 0
                    db 'scotty      '
                    db 20h, 0A1h, 07h
                    db 40h
                    db 'colin       '
                    db 40h, 0Dh, 03h
                    db 80h
                    db 'billy west  '
                    db 0A0h, 86h, 1
                    db 0
                    db 'sue         '
                    db 32h, 0, 0
                    db 0
                    db 'mel         '    
                    db 28h, 0, 0
                    db 40h
                    db 'ali         '
                    db 1Eh, 0, 0
                    db 80h
                    db 'anne        '
                    db 19h, 0, 0
                    db 0
                    db 'mandy       '
                    db 20, 0, 0
                    db 40h
                    db 'janet       '
                    db 15, 0, 0
                    db 80h
                    db 'christine   '
                    db 10, 0, 0
                    db 0
                    db 'becca       '
                    db 5, 0, 0
                    db 40h
                    db 'tim         '
                    db 2, 0, 0
                    db 80h
                    db 'maggie      '
                    db 1, 0, 0
                    db 0

byte_1F08:          db ?                                    ; 1F08
; cfg data ends

byte_1F09:          db 63h                                  ; 1F09
byte_1F0A:          db ?                                    ; 1F0A
byte_1F0B:          db ?                                    ; 1F0B
byte_1F0C:          db ?                                    ; 1F0C
byte_1F0D:          db ?                                    ; 1F0D
byte_1F0E:          db ?                                    ; 1F0E
                    rb 17                                   ; 1F0F..=1F1F
word_1F20:          dw ?                                    ; 1F20
                    rb 1                                    ; 1F22
show_lotus_again:   db ?                                    ; 1F23
demo_counter:       dw ?                                    ; 1F24
word_1F26:          dw loc_DC70                             ; 1F26
word_1F28:          dw ?                                    ; 1F28
arr_1F2A:           dw 7, 0Ah, 0Fh, 1, 9, 700h, 4A11h, 2040h, 3127h, 404Ah ; 1F2A

arr_1F3E:           dw ?                                    ; 1F3E
arr_1F40:           rw 8                                    ; 1F40
word_1F50:          dw ?                                    ; 1F50

word_1F52:          dw ?                                    ; 1F52
word_1F54:          dw ?                                    ; 1F54
word_1F56:          dw ?                                    ; 1F56
byte_1F58:          db ?                                    ; 1F58
arr_1F59:           dw -1                                   ; 1F59..=1F92
                    dw 0FE00h
                    dw 0FC00h
                    dw 0FA00h
                    dw 0F800h
                    dw 0F600h
                    dw 0F400h
                    dw 0F200h
                    dw 0F000h
                    dw 0EE00h
                    dw 0EC00h
                    dw 0EA00h
                    dw 0E800h
                    dw 0E600h
                    dw 0E400h
                    dw 0E200h
                    dw 0E000h
                    dw 0DE00h
                    dw 0DC00h
                    dw 0DC00h
                    dw 0E000h
                    dw 0E400h
                    dw 0E800h
                    dw 0EC00h
                    dw 0F000h
                    dw 0F400h
                    dw 0F800h
                    dw 0FC00h
                    dw -1
word_1F93:          dw ?                                    ; 1F93
word_1F95:          dw ?                                    ; 1F95
word_1F97:          dw ?                                    ; 1F97
;
word_1F99:          dw ?                                    ; 1F99
                    dw ?                                    ; 1F9B
word_1F9D:          dw ?                                    ; 1F9D
byte_1F9F:          db ?                                    ; 1F9F
word_1FA0:          dw ?                                    ; 1FA0
word_1FA2:          dw ?                                    ; 1FA2
word_1FA4:          dw ?                                    ; 1FA4
word_1FA6:          dw ?                                    ; 1FA6
word_1FA8:          dw ?                                    ; 1FA8
word_1FAA:          dw ?                                    ; 1FAA
word_1FAC:          dw ?                                    ; 1FAC
word_1FAE:          dw ?                                    ; 1FAE
                    rb 34                                   ; 1FB0..=1FD1
;
word_1FD2:          dw ?                                    ; 1FD2
word_1FD4:          dw ?                                    ; 1FD4
word_1FD6:          dw ?                                    ; 1FD6
word_1FD8:          dw ?                                    ; 1FD8
word_1FDA:          dw ?                                    ; 1FDA
word_1FDC:          dw ?                                    ; 1FDC
word_1FDE:          dw ?                                    ; 1FDE
word_1FE0:          dw ?                                    ; 1FE0
word_1FE2:          dw ?                                    ; 1FE2
word_1FE4:          dw ?                                    ; 1FE4
word_1FE6:          dw ?                                    ; 1FE6
word_1FE8:          dw ?                                    ; 1FE8
word_1FEA:          dw ?                                    ; 1FEA
word_1FEC:          dw ?                                    ; 1FEC
word_1FEE:          dw ?                                    ; 1FEE
word_1FF0:          dw ?                                    ; 1FF0
word_1FF2:          dw ?                                    ; 1FF2
word_1FF4:          dw ?                                    ; 1FF4
word_1FF6:          dw ?                                    ; 1FF6
word_1FF8:          dw ?                                    ; 1FF8
word_1FFA:          dw ?                                    ; 1FFA
word_1FFC:          dw ?                                    ; 1FFC
word_1FFE:          dw ?                                    ; 1FFE
word_2000:          dw ?                                    ; 2000
word_2002:          dw ?                                    ; 2002
word_2004:          dw ?                                    ; 2004
word_2006:          dw ?                                    ; 2006
word_2008:          dw ?                                    ; 2008
word_200A:          dw ?                                    ; 200A
word_200C:          dw ?                                    ; 200C
word_200E:          dw ?                                    ; 200E
arr_2010:           rw 40                                   ; 2010
word_2060:          dw ?                                    ; 2060
word_2062:          dw ?                                    ; 2062
word_2064:          dw ?                                    ; 2064
struct_2066:        dw ?                                    ; 2066
                    dw ?                                    ; +2
                    dw ?                                    ; +4
                    dw ?                                    ; +6
                    dw ?                                    ; +8
                    dw ?                                    ; +10
                    dw ?                                    ; +12
                    dw ?                                    ; +14
paused_txt:         db 'PAUSED', 0                          ; 2076
demo_txt:           db 'DEMO', 0                            ; 207D
race_completed_txt: db 'RACE COMPLETED', 0                  ; 2082
out_of_time_txt:    db 'OUT OF TIME', 0                     ; 2091
race_over_txt:      db 'RACE OVER', 0                       ; 209D
out_of_fuel_txt:    db 'OUT OF FUEL', 0                     ; 20A7
turbo_zone_txt:     db 'TURBO ZONE', 0                      ; 20B3
checkpoint_txt:     db 'CHECKPOINT', 0                      ; 20BE
low_fuel_txt:       db 'LOW FUEL', 0                        ; 20C9
ahead_txt:          db '???????????? AHEAD', 0              ; 20D2
                    db 0                                    ; 20E5
print_tmp_str:      times 40 db 0                           ; 20E6
print_font_ix:      db 0                                    ; 210E
                    db 0                                    ; 210F
word_2110:          dw ?                                    ; 2110
word_2112:          dw ?                                    ; 2112
word_2114:          dw ?                                    ; 2114
arr64_2116:         dw 0, 10h, 20h, 30h, 40h, 50h, 60h, 70h
                    dw 7Fh, 8Dh, 9Ah, 0A6h, 0B1h, 0BBh, 0C4h, 0CCh
                    dw 0D3h, 0D9h, 0DEh, 0E2h, 0E5h, 0E7h, 0E8h, 0E7h
                    dw 0E5h, 0E2h, 0DEh, 0D9h, 0D3h, 0CCh, 0C4h, 0BBh
                    dw 0B1h, 0A6h, 9Ah, 8Dh, 7Fh, 70h, 60h, 50h
                    dw 40h, 30h, 20h, 10h, 00h, 08h, 0Fh, 15h
                    dw 1Ah, 1Eh, 21h, 23h, 24h, 23h, 21h, 1Eh
                    dw 1Ah, 15h, 0Fh, 8, 0, 4, 6, 4
arr17_2196:         dw 60, 48, 43, 37, 30, 24, 21, 18, 15, 12, 10, 9, 7, 6, 5, 4, 2
arr17_21B8:         dw 8, 6, 5, 4, 4, 3, 6, 6, 4, 3, 2, 2, 2, 1, 1, 1, 1
arr17_21DA:         dw 12, 9, 8, 6, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
word_21FC:          dw ?                                    ; 21FC
word_21FE:          dw ?                                    ; 21FE
word_2200:          dw ?                                    ; 2200
word_2202:          dw ?                                    ; 2202
word_2204:          dw ?                                    ; 2204
word_2206:          dw ?                                    ; 2206
word_2208:          dw ?                                    ; 2208
word_220A:          dw ?                                    ; 220A
word_220C:          dw ?                                    ; 220C
word_220E:          dw ?                                    ; 220E
word_2210:          dw ?                                    ; 2210
word_2212:          dw ?                                    ; 2212
word_2214:          dw ?                                    ; 2214
word_2216:          dw ?                                    ; 2216
word_2218:          dw ?                                    ; 2218
word_221A:          dw ?                                    ; 221A
word_221C:          dw ?                                    ; 221C
arr306_221E:        db 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
                    db 9, 10, 10, 11, 12, 12, 13, 13, 14, 14
                    db 15, 15
                    db 10h, 11h, 11h, 12h, 12h, 13h, 13h, 14h, 14h, 15h, 16h, 16h
                    db 17h, 17h, 18h, 18h, 19h, 19h, 1Ah, 1Bh, 1Bh, 1Ch, 1Ch, 1Dh, 1Dh, 1Dh, 1Eh, 1Eh
                    db 1Eh, 1Fh, 1Fh, 1Fh, 20h, 20h, 20h, 21h, 21h, 21h, 22h, 22h, 22h, 23h, 23h, 23h
                    db 24h, 24h, 24h, 25h, 25h, 25h, 26h, 26h, 26h, 27h, 27h, 27h, 28h, 28h, 28h, 2Bh
                    db 2Bh, 2Bh, 2Ah, 2Ah, 2Ah, 29h, 29h, 29h, 2Eh, 2Eh, 2Eh, 2Dh, 2Dh, 2Dh, 2Ch, 2Ch
                    db 2Ch, 31h, 31h, 31h, 30h, 30h, 30h, 2Fh, 2Fh, 2Fh, 34h, 34h, 34h, 33h, 33h, 33h
                    db 32h, 32h, 32h, 37h, 37h, 37h, 36h, 36h, 36h, 35h, 35h, 35h, 3Ah, 3Ah, 3Ah, 39h
                    db 39h, 39h, 38h, 38h, 38h, 3Dh, 3Dh, 3Dh, 3Ch, 3Ch, 3Ch, 3Bh, 3Bh, 3Bh, 3Eh, 3Eh
                    db 3Eh, 3Eh, 3Eh, 3Eh, 3Eh, 3Eh, 3Eh, 05h, 05h, 05h, 04h, 04h, 04h, 03h, 03h, 03h
                    db 05h, 05h, 05h, 04h, 04h, 04h, 03h, 03h, 03h, 08h, 08h, 08h, 07h, 07h, 07h, 06h
                    db 06h, 06h, 0Bh, 0Bh, 0Bh, 0Ah, 0Ah, 0Ah, 09h, 09h, 09h, 0Eh, 0Eh, 0Eh, 0Dh, 0Dh
                    db 0Dh, 0Ch, 0Ch, 0Ch, 11h, 11h, 11h, 10h, 10h, 10h, 0Fh, 0Fh, 0Fh, 14h, 14h, 14h
                    db 13h, 13h, 13h, 12h, 12h, 12h, 17h, 17h, 17h, 16h, 16h, 16h, 15h, 15h, 15h, 1Ah
                    db 1Ah, 1Ah, 19h, 19h, 19h, 18h, 18h, 18h, 1Dh, 1Dh, 1Dh, 1Ch, 1Ch, 1Ch, 1Bh, 1Bh
                    db 1Bh, 20h, 20h, 20h, 1Fh, 1Fh, 1Fh, 1Eh, 1Eh, 1Eh, 23h, 23h, 23h, 22h, 22h, 22h
                    db 21h, 21h, 21h, 26h, 26h, 26h, 25h, 25h, 25h, 24h, 24h, 24h, 29h, 29h, 29h, 28h
                    db 28h, 28h, 27h, 27h, 27h, 2Ch, 2Ch, 2Ch, 2Bh, 2Bh, 2Bh, 2Ah, 2Ah, 2Ah, 2Fh, 2Fh
                    db 2Fh, 2Eh, 2Eh, 2Eh, 2Dh, 2Dh, 2Dh, 30h, 30h, 30h, 30h, 30h, 30h, 30h, 30h, 30h
word_2350:          dw ?                                    ; 2350
word_2352:          dw ?                                    ; 2352
word_2354:          dw ?                                    ; 2354
arr34_2356:         db 1, 1, 1, 1, 1
                    db 9, 9, 9, 9, 9
                    db 2, 2, 2, 2, 2
                    db 0, 0
                    db 13, 13, 13, 13
                    db 1, 1, 1, 1
                    db 9, 9, 9, 9
                    db 2, 2, 2, 2, 2
arr34_2378:         db 0, 0, 0, 0
                    db 10, 10, 10
                    db 2, 2
                    db 9, 9
                    db 14, 14
                    db 13, 13
                    db 1, 1
                    db 9, 9, 9, 9
                    db 14, 14, 14, 14
                    db 13, 13, 13, 13
                    db 1, 1, 1, 1, 1
word_239A:          dw ?                                    ; 239A
word_239C:          dw ?                                    ; 239C
word_239E:          dw ?                                    ; 239E
word_23A0:          dw ?                                    ; 23A0
arr_23A2:           dw sub_A5F3                             ; 23A2
                    dw sub_A64C                             ; 23A4
                    dw sub_A69A                             ; 23A6
                    dw sub_A6F2                             ; 23A8
                    dw sub_A74E                             ; 23AA
                    dw sub_A7B0                             ; 23AC
                    dw sub_A803                             ; 23AE
                    dw sub_A85F                             ; 23B0

                    dw sub_A860                             ; 23B2
                    dw sub_A860                             ; 23B4
                    dw sub_A860                             ; 23B6
                    dw sub_A860                             ; 23B8
                    dw sub_A867                             ; 23BA
                    dw sub_A86E                             ; 23BC
                    dw sub_A875                             ; 23BE
                    dw sub_A87C                             ; 23C0

                    dw sub_A884                             ; 23C2
                    dw sub_A896                             ; 23C4
                    dw sub_A8AA                             ; 23C6
                    dw sub_A8B9                             ; 23C8
                    dw sub_A8C9                             ; 23CA
                    dw sub_A8DB                             ; 23CC
                    dw sub_A8ED                             ; 23CE
                    dw sub_A900                             ; 23D0

                    dw sub_A914                             ; 23D2
                    dw sub_A92C                             ; 23D4
                    dw sub_A944                             ; 23D6
                    dw sub_A95C                             ; 23D8
                    dw sub_A974                             ; 23DA
                    dw sub_A98C                             ; 23DC
                    dw sub_A9A4                             ; 23DE
                    dw sub_A9BB                             ; 23E0

arr_23E2:           db 9, 11, 1, 6, 12, 3, 8, 7, 4, 2, 5, 10, 0 ; 23E2
                    db ?                                    ; 23EF
num_of_tracks:      dw ?                                    ; 23F0
word_23F2:          dw ?                                    ; 23F2
is_circular_track:  dw 0                                    ; 23F4
word_23F6:          dw 1                                    ; 23F6
word_23F8:          dw ?                                    ; 23F8
word_23FA:          dw ?                                    ; 23FA
word_23FC:          dw ?                                    ; 23FC
word_23FE:          dw ?                                    ; 23FE
arr_2400:           rw 17                                   ; 2400
word_2422:          rw 16                                   ; 2422
word_2442:          dw ?                                    ; 2442
word_2444:          dw ?                                    ; 2444
word_2446:          dw ?                                    ; 2446
word_2448:          dw ?                                    ; 2448
word_244A:          dw ?                                    ; 244A
word_244C:          dw ?                                    ; 244C
word_244E:          dw ?                                    ; 244E
word_2450:          dw ?                                    ; 2450
word_2452:          dw ?                                    ; 2452
word_2454:          dw ?                                    ; 2454
word_2456:          dw ?                                    ; 2456
word_2458:          dw ?                                    ; 2458
word_245A:          dw ?                                    ; 245A
word_245C:          dw ?                                    ; 245C
word_245E:          dw ?                                    ; 245E
word_2460:          dw ?                                    ; 2460
word_2462:          dw ?                                    ; 2462
word_2464:          dw ?                                    ; 2464
word_2466:          dw ?                                    ; 2466
word_2468:          dw ?                                    ; 2468
word_246A:          dw ?                                    ; 246A
word_246C:          dw ?                                    ; 246C
word_246E:          dw ?                                    ; 246E
word_2470:          dw ?                                    ; 2470
word_2472:          dw ?                                    ; 2472
word_2474:          dw ?                                    ; 2474
word_2476:          dw ?                                    ; 2476
word_2478:          dw ?                                    ; 2478
word_247A:          dw ?                                    ; 247A
word_247C:          dw ?                                    ; 247C
word_247E:          dw ?                                    ; 247E
word_2480:          dw ?                                    ; 2480
word_2482:          dw ?                                    ; 2482
word_2484:          dw ?                                    ; 2484
word_2486:          dw ?                                    ; 2486
word_2488:          dw ?                                    ; 2488
word_248A:          dw ?                                    ; 248A
word_248C:          dw ?                                    ; 248C
rnd_248E:           rw 8                                    ; 248E
word_249E:          dw ?                                    ; 249E
arr_24A0:           dw 0F0EEh                               ; 24A0
arr_24A2:           dw 8012h                                ; 24A2
                    db 0EEh, 0F4h
                    db 12h, 0BDh
                    db 0EEh, 0F1h
                    db 12h, 0A5h
                    db 0EEh, 0F0h
                    db 12h, 80h
                    db 0EEh, 0F0h
                    db 12h, 80h
                    db 0EEh, 0F0h
                    db 12h, 80h
                    db 0EEh, 0F0h
                    db 12h, 80h
                    db 0EEh, 0F0h
                    db 12h, 80h
                    db 0EEh, 0F0h
                    db 12h, 80h
                    db 0EEh, 0F0h
                    db 12h, 80h
                    db 0EEh, 0F0h
                    db 12h, 80h
                    db 0EEh, 0F0h
                    db 12h, 80h
                    db 0EEh, 0F0h
                    db 12h, 80h

arr_24D4:           db 0C8h, 94h, 0, 0, 80h, 99h, 80h, 98h, 0, 0, 10h, 95h
                    db 20h, 97h, 0, 0, 0F2h, 0C0h, 0F1h, 0F5h, 0F8h, 0C1h, 0F8h, 0C2h, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0F0h, 0A3h, 0F8h, 0A4h
                    db 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0F8h, 0ADh, 0, 0, 0F0h, 0AFh, 0F0h, 0B0h, 0F1h, 0B1h, 0F2h, 0F2h
                    db 0F0h, 0B3h, 0, 0, 0F0h, 0B5h, 0F0h, 0B6h, 0F0h, 0B7h, 0F0h, 0B8h, 0F0h, 0B9h, 0F1h, 0BAh
                    db 0F2h, 0F3h, 0, 0, 0F0h, 09Bh, 0F0h, 0A2h, 0F0h, 0A2h, 0F3h, 0A2h, 0F0h, 09Bh, 0F0h, 0A2h
                    db 0F0h, 0A2h, 0F3h, 0A2h, 0F8h, 0C9h
                    db 0, 0, 0, 0, 0F0h, 0CCh
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0, 0F8h, 0D0h, 0F0h, 097h, 0F0h, 0E8h, 0F0h, 0EFh
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0F0h, 0D9h, 0F8h, 0D7h
                    db 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0F8h, 0E7h, 0, 0, 20h, 0E9h, 20h, 0EAh, 20h, 0EDh, 0, 0
                    db 0, 0, 0, 0, 0F8h, 0B2h, 0F8h, 0A6h, 0C0h, 86h, 0F0h, 0BBh, 0F0h, 81h, 0, 0
                    db 0, 0, 0, 0, 0F0h, 0DDh
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0F1h, 086h, 0F1h, 086h, 0F1h, 086h, 0F1h, 86h
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0

arr_25A4:           db 0, 0, 0, 0, 0, 0, 40h, 98h, 0, 0, 20h, 95h
                    db 0F0h, 97h, 0, 0, 0F0h, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0F0h, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0F0h, 0B0h, 81h, 0B1h, 82h, 0F2h
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0F0h, 0B8h, 40h, 0B9h, 0, 0
                    db 0, 0, 0, 0, 0F0h, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0F0h, 0CDh, 0, 0
                    db 0, 0, 0C0h, 97h, 0, 0, 0F0h, 97h, 80h, 0EFh, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0F0h, 0D3h, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0F0h, 0EBh, 0, 0, 0F0h, 0ECh, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0F0h, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0F0h, 0DBh, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0F2h, 0E3h, 0C2h, 0E4h, 82h, 0E5h, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0

arr_2674:           db 0, 0
arr_2676:           db 0, 63h, 0, 0, 0, 63h, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65h
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 63h, 0, 0, 0, 63h, 0, 0, 0, 63h
                    db 0, 0, 0, 69h, 0, 0, 0, 69h, 0, 0, 0, 6Ah, 0, 0, 0, 65h
                    db 0, 0, 0, 64h, 0, 0, 0, 65h, 0, 0, 0, 69h, 0, 0, 0, 63h
                    db 0, 0, 0, 63h, 0, 0, 0, 65h, 0, 0, 0, 65h, 0, 0, 0, 65h
                    db 0, 0, 0, 65h, 0, 0, 0, 65h, 0, 0, 0, 65h, 0, 0, 0, 63h
                    db 0, 0, 0, 69h, 0, 0, 0, 69h, 0, 0, 0, 63h, 0, 0, 0, 63h
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6Bh, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 69h, 0, 0, 0, 69h
                    db 0, 0, 0, 69h, 0, 0, 0, 6Bh, 0, 0, 0, 6Ah, 0, 0, 0, 63h
                    db 0, 0, 0, 63h, 0, 0, 0, 0, 0, 0, 0, 69h, 0, 0, 0, 69h
                    db 0, 0, 0, 69h, 0, 0, 0, 69h, 0, 0, 0, 65h, 0, 0, 0, 6Ah
                    db 0, 0, 0, 65h, 0, 0, 0, 0, 0, 0, 0, 63h, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 65h, 0, 0, 0, 63h, 0, 0, 0, 63h
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 69h, 0, 0, 0, 69h
                    db 0, 0, 0, 69h, 0, 0, 0, 69h, 0, 0, 0, 6Ch, 0, 0, 0, 69h
                    db 0, 0, 0, 0, 0, 0, 0, 69h, 0, 0, 0, 6Ah, 0, 0, 0, 63h
                    db 0, 0, 0, 6Ah, 0, 0, 0, 63h, 0, 0, 0, 63h, 0, 0, 0, 6Ah
                    db 0, 0, 0, 63h, 0, 0, 0, 63h, 0, 0, 0, 63h, 0, 0, 0, 69h
                    db 0, 0, 0, 63h, 0, 0, 0, 63h, 0, 0, 0, 69h, 0, 0, 0, 63h
                    db 0, 0

word_27F2:          dw 6300h                                ; 27F2
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 65h
                    db 0, 0, 0, 65h
                    db 0, 0, 0, 65h
                    db 0, 0, 0, 65h
                    db 0, 0, 0, 0
                    db 0, 0, 0, 69h
                    db 0, 0, 0, 69h
                    db 0, 0, 0, 69h
                    db 0, 0, 0, 69h
                    db 0, 0, 0, 65h
                    db 0, 0, 0, 6Bh
                    db 0, 0, 0, 63h
                    db 0, 0, 0, 69h
                    db 0, 0, 0, 63h
                    db 0, 0, 0, 63h
                    db 0, 0, 0, 63h
                    db 0, 0, 0, 6Ah
                    db 0, 0, 0, 6Ah
                    db 0, 0, 0, 63h
                    db 0, 0, 0, 65h
                    db 0, 0, 0, 63h
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0 

arr_2874:           db 0F0h, 94h, 0, 0
                    db 20h, 99h, 20h, 98h
                    db 0, 0, 10h, 95h
                    db 20h, 97h, 0, 0
                    db 0F0h, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0F0h, 0A9h, 0F0h, 0A3h
                    db 0F0h, 0A4h, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0F0h, 0ADh, 0, 0
                    db 0F0h, 0AFh, 0F0h, 0B0h
                    db 0F1h, 0B1h, 0F2h, 0F2h
                    db 0, 0, 0, 0
                    db 0F0h, 0B5h, 0F0h, 0B6h
                    db 0F0h, 0B7h, 0F0h, 0B8h
                    db 0F0h, 0B9h, 0F1h, 0BAh
                    db 0F2h, 0F3h, 0, 0
                    db 0F0h, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0F0h, 0C9h, 0F0h, 0CAh
                    db 0F0h, 0CBh, 0F0h, 0CCh
                    db 0F0h, 0CDh, 0F0h, 0CEh
                    db 0, 0, 0F0h, 97h
                    db 0F0h, 0D0h, 0F0h, 97h
                    db 0F0h, 0E8h, 0F0h, 0EFh
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0F0h, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0F0h, 0E7h, 0, 0
                    db 20h, 0E9h, 20h, 0EAh
                    db 0, 0, 20h, 0EBh
                    db 20h, 0ECh, 0, 0
                    db 40h, 81h, 40h, 86h
                    db 0, 0, 0, 0
                    db 40h, 0BBh, 0F0h, 0DAh
                    db 0F0h, 0DAh, 0F0h, 0DAh
                    db 0, 0, 0, 0
                    db 0F0h, 0DDh, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0F0h, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0
                    db 0, 0, 0, 0 

arr_2944:           db 0, 90h
                    db 0, 92h
                    db 0, 91h
                    db 0, 90h
                    db 0, 90h
                    db 0, 90h
                    db 0, 90h
                    db 0, 90h
                    db 0, 90h
                    db 0, 90h
                    db 0, 90h
                    db 0, 90h
                    db 0, 90h
                    db 0AAh, 0
                    db 0B4h, 0
                    db 0AAh, 0
                    db 0A0h, 0
                    db 082h, 0
                    db 0AAh, 0
                    db 08Ch, 0
                    db 0B4h, 0
                    db 0AAh, 0
                    db 082h, 0
                    db 0AAh, 0
                    db 0BEh, 0
                    db 0AAh, 0
                    db 0Eh, 1
                    db 18h, 1
                    db 0Eh, 1
                    db 4, 1
                    db 0E6h, 0
                    db 0Eh, 1
                    db 0F0h, 0
                    db 18h, 1
                    db 0Eh, 1
                    db 0E6h, 0
                    db 0Eh, 1
                    db 22h, 1
                    db 0Eh, 1
                    db 82h, 0
                    db 8Ch, 0
                    db 82h, 0
                    db 78h, 0
                    db 5Ah, 0
                    db 82h, 0
                    db 64h, 0
                    db 8Ch, 0
                    db 82h, 0
                    db 5Ah, 0
                    db 82h, 0
                    db 96h, 0
                    db 82h, 0
                    db 0E6h, 0
                    db 0F0h, 0
                    db 0E6h, 0
                    db 0DCh, 0
                    db 0BEh, 0
                    db 0E6h, 0
                    db 0C8h, 0
                    db 0F0h, 0
                    db 0E6h, 0
                    db 0BEh, 0
                    db 0E6h, 0
                    db 0FAh, 0
                    db 0E6h, 0
                    db 96h, 0
                    db 0A0h, 0
                    db 96h, 0
                    db 8Ch, 0
                    db 6Eh, 0
                    db 96h, 0
                    db 78h, 0
                    db 0A0h, 0
                    db 96h, 0
                    db 6Eh, 0
                    db 96h, 0
                    db 0AAh, 0
                    db 096h, 0
                    db 0FAh, 0
                    db 4, 1
                    db 0FAh, 0
                    db 0F0h, 0
                    db 0D2h, 0
                    db 0FAh, 0
                    db 0DCh, 0
                    db 4, 1
                    db 0FAh, 0
                    db 0D2h, 0
                    db 0FAh, 0
                    db 14, 1
                    db 0FAh, 0

arr_29FA:           db 14h, 2Ah
                    db 18h, 2Ah
                    db 1Eh, 2Ah
                    db 22h, 2Ah
                    db 26h, 2Ah
                    db 2Ah, 2Ah
                    db 2Eh, 2Ah
                    db 32h, 2Ah
                    db 3Ch, 2Ah
                    db 3Eh, 2Ah
                    db 44h, 2Ah
                    db 46h, 2Ah
                    db 4Ah, 2Ah
                    db 92h, 63h
                    db 0, 0
                    db 96h, 63h
                    db 98h, 63h
                    db 0, 0
                    db 98h, 63h
                    db 0, 0
                    db 9Ah, 63h
                    db 0, 0
                    db 94h, 63h
                    db 0, 0
                    db 96h, 63h
                    db 0, 0
                    db 92h, 63h
                    db 0, 0
                    db 98h, 63h
                    db 9Ah, 63h
                    db 94h, 63h
                    db 92h, 63h
                    db 0, 0
                    db 0, 0
                    db 92h, 63h
                    db 94h, 63h
                    db 0, 0
                    db 0, 0
                    db 96h, 63h
                    db 0, 0
                    db 0, 0

arr_2A4C:           dw 5082h, 511Ah, 51B2h
                    dw 51BCh, 5254h, 52ECh
                    dw 52F6h, 5394h, 542Ch

word_2A5E:          dw ?                                    ; 2A5E
word_2A60:          dw ?                                    ; 2A60
word_2A62:          dw ?                                    ; 2A62

arr_2A64:           db 64h, 0
                    db 0E4h, 0
                    db 4, 0
                    db 4, 0
                    db 0A4h, 0
                    db 0E4h, 0
                    db 0A4h, 0
                    db 0A4h, 0
                    db 0E4h, 0
                    db 0A4h, 0
                    db 0E4h, 0
                    db 64h, 0
                    db 0E4h, 0
                    db 64h, 0
                    db 78h, 0
                    db 64h, 0
                    db 78h, 0
                    db 64h, 0
                    db 78h, 0
                    db 64h, 0
                    db 78h, 0
                    db 64h, 0
                    db 64h, 0
                    db 64h, 0
                    db 64h, 0
                    db 64h, 0

arr_2A98:           db 0, 0, 0, 0, 0, 0, 16, 0, 16, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

word_2AB2:          dw ?                                    ; 2AB2
                    dw ?                                    ; 2AB4
word_2AB6:          dw ?                                    ; 2AB6
word_2AB8:          dw ?                                    ; 2AB8
arr_2ABA:           dw 0Fh, 355h, 6AAh, 8                   ; 2ABA
arr_2AC2:           dw 0Fh, 355h, 6AAh, 8                   ; 2AC2
arr_2ACA:           dw 14h, 0, 0A00h, 4                     ; 2ACA
arr_2AD2:           dw 19h, 6AAh, 6AAh, 4                   ; 2AD2
arr_2ADA:           dw 1Eh, 0A00h, 0A00h, 2                 ; 2ADA
word_2AE2:          dw ?                                    ; 2AE2
word_2AE4:          dw ?                                    ; 2AE4
word_2AE6:          dw ?                                    ; 2AE6
word_2AE8:          dw ?                                    ; 2AE8
arr_2AEA:           db 0, 22, 13, 3, 4, 5, 6, 31, 8, 9, 10, 11, 12 ; 2AEA
word_2AF7:          dw ?                                    ; 2AF7
word_2AF9:          dw ?                                    ; 2AF9
                    db ?                                    ; 2AFB
word_2AFC:          dw ?                                    ; 2AFC
word_2AFE:          dw ?                                    ; 2AFE
byte_2B00:          db ?                                    ; 2B00
                    db ?                                    ; 2B01
word_2B02:          dw ?                                    ; 2B02
arr_2B04:           rb 32                                   ; 2B04
                    rb 256                                  ; 2B24
word_2C24:          dw ?                                    ; 2C24
arr_2C26:           rb 64                                   ; 2C26
byte_2C66:          db ?                                    ; 2C66
                    rb 7                                    ; 2C67
word_2C6E:          dw 0A580h                               ; 2C6E
                    dw 0BAB1h                               ; 2C70
                    dw 0C0BDh                               ; 2C72
                    dw 0D8h                                 ; 2C74
word_2C76:          dw ?                                    ; 2C76
word_2C78:          dw ?                                    ; 2C78
word_2C7A:          dw ?                                    ; 2C7A
word_2C7C:          dw ?                                    ; 2C7C
                    rw 30                                   ; 2C7E
arr_2CBA:           rw 28                                   ; 2CBA
arr_2CF2:           rw 28                                   ; 2CF2
                    rw 38                                   ; 2D2A

; struct word_2D76
word_2D76:          dw ?                                    ; 2D76
                    dw ?                                    ; 2D78
                    dw ?                                    ; 2D7A
word_2D7C:          dw ?                                    ; 2D7C
word_2D7E:          dw ?                                    ; 2D7E
word_2D80:          dw ?                                    ; 2D80
                    rw 7                                    ; 2D82..=2D8E
word_2D90:          rw 13                                   ; 2D90
word_2DAA:          dw ?                                    ; 2DAA
                    dw ?                                    ; 2DAC
word_2DAE:          dw ?                                    ; 2DAE
word_2DB0:          dw ?                                    ; 2DB0
word_2DB2:          dw ?                                    ; 2DB2
word_2DB4:          dw ?                                    ; 2DB4
                    dw ?                                    ; 2DB6
word_2DB8:          dw ?                                    ; 2DB8
                    rw 18                                   ; 2DBA
word_2DDE:          dw ?                                    ; 2DDE
                    rw 3                                    ; 2DE0
word_2DE6:          dw ?                                    ; 2DE6
                    rw 3                                    ; 2DE8
word_2DEE:          dw ?                                    ; 2DEE
                    rw 31                                   ; 2DF0
; -- struct word_2D76 ends here

word_2E2E:          dw ?                                    ; 2E2E
                    dw ?                                    ; 2E30
                    dw ?                                    ; 2E32
word_2E34:          dw ?                                    ; 2E34
                    rw 32                                   ; 2E36
word_2E76:          dw ?                                    ; 2E76
word_2E78:          dw ?                                    ; 2E78
word_2E7A:          dw ?                                    ; 2E7A
word_2E7C:          dw ?                                    ; 2E7C
word_2E7E:          db 70h, 8Eh, 0BEh                       ; 2E7E
byte_2E81:          db ?

; 183 bytes
arr_2E82:           db 0, 0, 0, 0, 10h, 10h, 10h, 1Ch, 1Ch, 1Ch, 1Eh, 0, 0, 1Ah
                    db 1Ah, 1Ah, 28h, 28h, 28h, 10h, 0Ah, 20h, 14h, 0Ch, 25h, 1Ah, 1Ah, 0, 28h, 28h
                    db 0, 0, 0, 0, 10h, 10h, 10h, 1Ch, 1Ch, 1Ch, 1Eh, 0, 0, 1Ah, 1Ah, 1Ah
                    db 28h, 28h, 28h, 10h, 0Ah, 20h, 14h, 0Ch, 25h, 1Ah, 1Ah, 0, 28h, 28h, 0, 0
                    db 0, 0, 0, 10h, 10h, 10h, 1Ch, 1Ch, 1Ch, 1Eh, 0, 0, 06h, 12h, 06h, 8
                    db 1Ch, 08h, 1Ah, 1Ah, 0, 28h, 28h, 0, 18h, 06h, 0, 24h, 08h, 0, 0, 00
                    db 0, 10h, 10h, 10h, 1Ch, 1Ch, 1Ch, 1Eh, 0, 0, 06h, 12h, 06h, 08h, 1Ch, 8
                    db 1Ah, 1Ah, 0, 28h, 28h, 0, 18h, 06h, 0, 24h, 08h, 0, 0, 0, 0, 00
                    db 10h, 10h, 10h, 1Ch, 1Ch, 1Ch, 1Eh, 0, 0, 1Ah, 1Ah, 0, 28h, 28h, 0, 6
                    db 12h, 06h, 08h, 1Ch, 08h, 1Ah, 1Ah, 1Ah, 28h, 28h, 28h, 0, 0, 0, 10h, 10h
                    db 10h, 1Ch, 1Ch, 1Ch, 1Eh, 0, 0, 1Ah, 1Ah, 0, 28h, 28h, 0, 06h, 12h, 6
                    db 08h, 1Ch, 08h, 1Ah, 1Ah, 1Ah, 28h, 28h, 28h

; 183 bytes
arr_2F39:           db 6, 0, 0, 0, 10h, 10h, 10h
                    db 1Ch, 1Ch, 1Ch, 1Eh, 0, 0, 1Ah, 1Ah, 1Ah, 28h, 28h, 28h, 10h, 0Ah, 20h, 14h
                    db 0Ch, 25h, 1Ah, 1Ah, 0, 28h, 28h, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 30h, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 06h, 0, 0, 0, 10h, 10h, 10h, 1Ch, 1Ch, 1Ch
                    db 1Eh, 0, 0, 06h, 12h, 06h, 08h, 1Ch, 08h, 1Ah, 1Ah, 0, 28h, 28h, 0, 18h
                    db 06h, 0, 24h, 08h, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30h, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    db 0, 0, 0, 06h, 0, 0, 0, 10h, 10h, 10h, 1Ch, 1Ch, 1Ch, 1Eh, 0, 0
                    db 1Ah, 1Ah, 0, 28h, 28h, 0, 06h, 12h, 06h, 08h, 1Ch, 08h, 1Ah, 1Ah, 1Ah, 28h
                    db 28h, 28h, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30h, 0, 0, 0, 0
                    db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

; 183 bytes
arr_2FF0:           db 8h, 0, 0, 0, 10h, 10h, 10h, 1Ch, 1Ch, 1Ch, 1Eh, 0, 0, 1Ah, 1Ah, 1Ah
                    db 28h, 28h, 28h, 10h, 0Ah, 20h, 14h, 0Ch, 25h, 1Ah, 1Ah, 0, 28h, 28h, 0, 18h
                    db 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h
                    db 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 08h, 0, 0
                    db 0, 10h, 10h, 10h, 1Ch, 1Ch, 1Ch, 1Eh, 0, 0, 06h, 12h, 06h, 08h, 1Ch, 08h
                    db 1Ah, 1Ah, 0, 28h, 28h, 0, 18h, 06h, 0, 24h, 08h, 0, 18h, 18h, 18h, 18h
                    db 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h
                    db 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 08h, 0, 0, 0, 10h, 10h
                    db 10h, 1Ch, 1Ch, 1Ch, 1Eh, 0, 0, 1Ah, 1Ah, 0, 28h, 28h, 0, 06h, 12h, 06h
                    db 08h, 1Ch, 08h, 1Ah, 1Ah, 1Ah, 28h, 28h, 28h, 18h, 18h, 18h, 18h, 18h, 18h, 18h
                    db 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h, 18h
                    db 18h, 18h, 18h, 18h, 18h, 18h, 18h

arr89_30A7:         db 0, 0, 0, 0, 0, 0, 0                  ; 30A7
                    db 0Ah, 0Ah, 0Ah, 0Ah, 0Ah
                    db 14h, 14h, 14h, 14h, 14h
                    db 1Eh, 1Eh, 1Eh, 1Eh, 1Eh
                    db 28h, 28h, 28h
                    db 32h, 32h, 32h
                    db 3Ch, 3Ch, 3Ch
                    db 46h, 46h, 46h
                    db 50h, 50h, 50h
                    db 5Ah, 5Ah, 5Ah
                    db 64h, 64h, 64h
                    db 6Eh, 6Eh, 6Eh
                    db 78h, 78h, 78h
                    db 82h, 82h, 82h
                    db 8Ch, 8Ch, 8Ch
                    db 96h, 96h, 96h
                    db 0A0h, 0A0h, 0A0h
                    db 0, 0, 0
                    db 0, 0, 0
                    db 0, 0, 0
                    db 0, 0, 0
                    db 0, 0, 0
                    db 0, 0, 0
                    db 0, 0, 0
                    db 0, 0, 0
                    db 0, 0, 0
                    db 0

arr5_3100:          db 0, 1, 2, 7, -1                       ; 3100
                    db ?                                    ; 3105
chr_bmp_ptr:        rw 6                                    ; 3106
                    rw 10                                   ; 3112

arr48_3126:         db 0, 0, 0
                    db 15h, 15h, 15h
                    db 2Ah, 2Ah, 2Ah
                    db 38h, 38h, 38h
                    db 20h, 0, 0
                    db 30h, 0, 0
                    db 0, 20h, 0
                    db 0, 15h, 9
                    db 9, 2Ah, 17h
                    db 31h, 2Ah, 9
                    db 18h, 15h, 9
                    db 21h, 18h, 9
                    db 2Ch, 24h, 9
                    db 0, 13h, 2Ah
                    db 0, 0Dh, 22h
                    db 0, 0, 0

arr4_3156:          db 63, 63, 63, 0                        ; 3156

res_key:            times 8 db ' '                          ; 315A
                    dw ?                                    ; 3162
arc_header:         rb 2816                                 ; 3164
arc_file_name:      db 'LOTUS.DAT', 0                       ; 3C64
arc_file_handle:    dw ?                                    ; 3C6E
word_3C70:          dw ?                                    ; 3C70
word_3C72:          dw ?                                    ; 3C72
word_3C74:          dw ?                                    ; 3C74
word_3C76:          dw ?                                    ; 3C76
arr_3C78:           dw 0, 6, 12h, 1Ah, 1Eh, 24h, 2Eh, 36h   ; 3C78
                    dw 0, 0CA00h, 1,  2800h, 1,  8600h, 1, 0E400h
                    dw 2, 0A200h, 2, 0A000h, 2, 0FE00h, 3,  5C00h
                    dw 3, 0BA00h, 4,  1800h, 4,  7200h, 4, 0D000h
                    dw 5,  2E00h, 5,  8C00h, 5, 0EA00h, 6,  4800h
                    dw 6, 0A600h, 7,   400h, 7,  6200h, 7, 0C000h
word_3CD8:          dw ?                                    ; 3CD8
word_3CDA:          dw ?                                    ; 3CDA
word_3CDC:          dw ?                                    ; 3CDC
word_3CDE:          dw ?                                    ; 3CDE
word_3CE0:          dw ?                                    ; 3CE0
word_3CE2:          dw ?                                    ; 3CE2
word_3CE4:          dw ?                                    ; 3CE4
word_3CE6:          dw ?                                    ; 3CE6
word_3CE8:          dw ?                                    ; 3CE8
word_3CEA:          dw ?                                    ; 3CEA
arr_3CEC:           rw 18                                   ; 3CEC
word_3D10:          dw ?                                    ; 3D10
word_3D12:          dw ?                                    ; 3D12
word_3D14:          dw 0F800h                               ; 3D14
                    dw 0E000h                               ; 3D16
                    dw 0D800h                               ; 3D18
                    dw 0FD00h                               ; 3D1A
                    dw 0FD00h                               ; 3D1C
                    dw 0C000h                               ; 3D1E
                    dw 0C000h                               ; 3D20
                    dw 0D000h                               ; 3D22
word_3D24:          dw 0F800h                               ; 3D24
                    dw 0B000h                               ; 3D26
                    dw 0A000h                               ; 3D28
                    dw 0FD00h                               ; 3D2A
                    dw 0FD00h                               ; 3D2C
                    dw 0C000h                               ; 3D2E
                    dw 0C000h                               ; 3D30
                    dw 0D000h                               ; 3D32
word_3D34:          dw 0F800h                               ; 3D34
word_3D36:          dw 0E000h                               ; 3D36
word_3D38:          dw 0D800h                               ; 3D38
word_3D3A:          dw 0FD00h                               ; 3D3A
word_3D3C:          dw 0FD00h                               ; 3D3C
word_3D3E:          dw 0C000h                               ; 3D3E
word_3D40:          dw 0C000h                               ; 3D40
word_3D42:          dw 0D000h                               ; 3D42
arr_3D44:           rb 10                                   ; 3D44
arr_3D4E:           db 18h                                  ; a
                    db 12h                                  ; b
                    db 17h                                  ; c
                    db 10h                                  ; d
                    db 16h                                  ; e
                    db 11h                                  ; f
                    db 0Ch                                  ; g
                    db 19h                                  ; h
                    db 0Eh                                  ; i
                    db 13h                                  ; j
                    db 1Ah                                  ; k
                    db 0Fh                                  ; l
                    db 6                                    ; m
                    db 0Dh                                  ; _
                    db 8                                    ; n
                    db 0Bh                                  ; o
                    db 3                                    ; p
                    db 5                                    ; q
                    db 1                                    ; r
                    db 9                                    ; s
                    db 15h                                  ; t
                    db 14h                                  ; u
                    db 4                                    ; v
                    db 2                                    ; w
                    db 0                                    ; x
                    db 7                                    ; y
                    db 0Ah                                  ; z
                    db 0                                    ; 3D69
byte_3D6A:          dw ?
word_3D6C:          dw 14h
word_3D6E:          dw ?
word_3D70:          dw ?
byte_3D72:          db ?
dos_vid_mode:       db ?                                    ; 3D73
byte_3D74:          dw ?
word_3D76:          dw ?
word_3D78:          dw ?
word_3D7A:          dw ?
byte_3D7C:          dw ?
word_3D7E:          dw ?
word_3D80:          dw ?
word_3D82:          dw ?
word_3D84:          dw ?
byte_3D86:          db ?
byte_3D87:          db ?

byte_3D88:          db ?                                    ; 3D88
byte_3D89:          rb 24                                   ; 3D89
byte_3DA1:          rb 3                                    ; 3DA1
byte_3DA4:          rb 44                                   ; 3DA4
byte_3DD0:          dw ?                                    ; 3DD0
byte_3DD2:          db ?                                    ; 3DD2
byte_3DD3:          dw ?                                    ; 3DD3
byte_3DD5:          db ?                                    ; 3DD5
byte_3DD6:          dw ?                                    ; 3DD6
byte_3DD8:          rb 48                                   ; 3DD8

word_3E08:          dw ?
word_3E0A:          dw ?
word_3E0C:          dw ?
byte_3E0E:          db ?
byte_3E0F:          db 1
byte_3E10:          dw ?
word_3E12:          dw ?
word_3E14:          dw ?
word_3E16:          dw ?
word_3E18:          dw ?
word_3E1A:          dw ?
word_3E1C:          dw 8000h
word_3E1E:          dw ?
word_3E20:          dw ?
word_3E22:          dw ?
byte_3E24:          db 0Fh
byte_3E25:          db ?
arr_3E26:           dw sub_D99E, sub_D9B4, sub_DAD1         ; 3E26
byte_3E2C:          db ?
byte_3E2D:          db ?
word_3E2E:          dw ?

word_3E30:          dw 0140h
word_3E32:          dw 64h
create_error:       db 'ERROR: Can''t create $', 0          ; 3E34
open_error:         db 'ERROR: Can''t open $', 0            ; 3E4A
read_error:         db 'ERROR: Read error in $', 0, 0       ; 3E5E
write_error:        db 'ERROR: Write error in $', 0         ; 3E76
close_error:        db 'ERROR: Can''t close $', 0, 0        ; 3E8E
err_str_ptr:        dw 0                                    ; 3EA4
memory_error:       db 'HELP! Memory full.', 0              ; 3EA6
word_3EB9:          dw 3EBCh                                ; 3EB9
byte_3EBB:          db 0                                    ; 3EBB
version_str:        db 'LOTUS III  Version 14/07/93', 0     ; 3EBC
word_3ED8:          dw ?                                    ; 3ED8
word_3EDA:          dw ?                                    ; 3EDA: -------------------------------
num_of_players:     dw ?                                    ; 3EDC: P1 or P1 + P2
race_type:          dw ?                                    ; 3EDE: TimeLimit, Competition
word_3EE0:          dw ?                                    ; 3EE0
word_3EE2:          dw ?                                    ; 3EE2
word_3EE4:          dw ?                                    ; 3EE4
word_3EE6:          dw ?                                    ; 3EE6
word_3EE8:          dw ?                                    ; 3EE8
word_3EEA:          dw ?                                    ; 3EEA
word_3EEC:          dw ?                                    ; 3EEC
rnd_3EEE:           rw 8                                    ; 3EEE
rnd_3EFE:           rw 8                                    ; 3EFE
arr_3F0E:           rw 16                                   ; 3F0E
arr_3F2E:           rb 12                                   ; 3F2E
word_3F3A:          dw ?                                    ; 3F3A, is a struct
word_3F3C:          dw ?                                    ; 3F3C
word_3F3E:          dw ?                                    ; 3F3E
                    dw ?                                    ; 3F40
word_3F42:          dw ?                                    ; 3F42
word_3F44:          dw ?                                    ; 3F44
word_3F46:          db ?                                    ; 3F46
                    db ?                                    ; 3F47
word_3F48:          dw ?                                    ; 3F48
                    dw ?                                    ; 3F4A
                    rb 8                                    ; 3F4C
word_3F54:          dw ?                                    ; 3F54
                    dw ?                                    ; 3F56
                    dw ?                                    ; 3F58
word_3F5A:          dw ?                                    ; 3F5A
word_3F5C:          rw 6                                    ; 3F5C
word_3F68:          dw ?                                    ; 3F68
word_3F6A:          dw ?                                    ; 3F6A
byte_3F6C:          db ?                                    ; 3F6C
byte_3F6D:          db ?                                    ; 3F6D
word_3F6E:          dw ?                                    ; 3F6E
byte_3F70:          dw ?                                    ; 3F70
p1_accel:           dw ?                                    ; 3F72: P1 acceleration
p1_gears:           dw ?                                    ; 3F74: P1 gears
                    rb 10                                   ; 3F76
word_3F80:          dw ?                                    ; 3F80
word_3F82:          rw 25                                   ; 3F82
word_3FB4:          dw ?                                    ; 3FB4
word_3FB6:          dw ?                                    ; 3FB6
word_3FB8:          dw ?                                    ; 3FB8
word_3FBA:          dw ?                                    ; 3FBA
word_3FBC:          dw ?                                    ; 3FBC
word_3FBE:          dw ?                                    ; 3FBE
word_3FC0:          dw ?                                    ; 3FC0
word_3FC2:          dw ?                                    ; 3FC2
                    rb 6                                    ; 3FC4
word_3FCA:          dw ?                                    ; 3FCA
                    rb 6                                    ; 3FCC
word_3FD2:          dw ?                                    ; 3FD2
                    rb 14                                   ; 3FD4
word_3FE2:          dw ?                                    ; 3FE2
                    rb 12                                   ; 3FE4
word_3FF0:          dw ?                                    ; 3FF0
                    rb 26                                   ; 3FF2
word_400C:          dw ?                                    ; 400C
                    rb 4                                    ; 400E
word_4012:          dw ?                                    ; 4012
                    dw ?                                    ; 4014
                    dw ?                                    ; 4016
word_4018:          dw ?                                    ; 4018
word_401A:          dw ?                                    ; 401A
word_401C:          dw ?                                    ; 401C
word_401E:          dw ?                                    ; 401E
                    dw ?                                    ; 4020
                    dw ?                                    ; 4022
                    dw ?                                    ; 4024
word_4026:          dw ?                                    ; 4026
word_4028:          dw ?                                    ; 4028
word_402A:          dw ?                                    ; 402A
                    rb 8                                    ; 402C
word_4034:          dw ?                                    ; 4034
word_4036:          dw ?                                    ; 4036
word_4038:          dw ?                                    ; 4038
                    dw ?                                    ; 403A
word_403C:          dw ?                                    ; 403C
word_403E:          dw ?                                    ; 403E
word_4040:          dw ?                                    ; 4040
word_4042:          dw ?                                    ; 4042
                    dw ?                                    ; 4044
                    dw ?                                    ; 4046
                    dw ?                                    ; 4048
                    dw ?                                    ; 404A
                    dw ?                                    ; 404C
word_404E:          dw ?                                    ; 404E
                    dw ?                                    ; 4050
                    dw ?                                    ; 4052
word_4054:          dw ?                                    ; 4054
word_4056:          dw ?                                    ; 4056
                    rb 10                                   ; 4058
word_4062:          dw ?                                    ; 4062
word_4064:          dw ?                                    ; 4064
byte_4066:          db ?                                    ; 4066
                    db ?                                    ; 4067
byte_4068:          db ?                                    ; 4068
                    db ?                                    ; 4069
byte_406A:          db ?                                    ; 406A
                    db ?                                    ; 406B
p2_accel:           dw ?                                    ; 406C: P2 acceleration
p2_gears:           dw ?                                    ; 406E: P2 gears
                    rb 10                                   ; 4070
word_407A:          dw ?                                    ; 407A
word_407C:          dw ?                                    ; 407C
                    rb 48                                   ; 407E
word_40AE:          dw ?                                    ; 40AE
word_40B0:          dw ?                                    ; 40B0
word_40B2:          dw ?                                    ; 40B2
word_40B4:          dw ?                                    ; 40B4
word_40B6:          dw ?                                    ; 40B6
word_40B8:          dw ?                                    ; 40B8
word_40BA:          dw ?                                    ; 40BA
word_40BC:          dw ?                                    ; 40BC
                    rb 6                                    ; 40BE
word_40C4:          dw ?                                    ; 40C4
                    rb 6                                    ; 40C6
word_40CC:          dw ?                                    ; 40CC
                    rb 14                                   ; 40CE
word_40DC:          dw ?                                    ; 40DC
                    rb 12                                   ; 40DE
word_40EA:          dw ?                                    ; 40EA
                    rb 26                                   ; 40EC
word_4106:          dw ?                                    ; 4106
                    dw ?                                    ; 4108
                    dw ?                                    ; 410A
word_410C:          dw ?                                    ; 410C
                    dw ?                                    ; 410E
                    dw ?                                    ; 4110
word_4112:          dw ?                                    ; 4112
word_4114:          dw ?                                    ; 4114
word_4116:          dw ?                                    ; 4116
word_4118:          dw ?                                    ; 4118
                    rb 6                                    ; 411A
word_4120:          dw ?                                    ; 4120
word_4122:          dw ?                                    ; 4122
word_4124:          dw ?                                    ; 4124
                    rb 8                                    ; 4126
arr_412E:           rb 80                                   ; 412E
arr_417E:           rb 96                                   ; 417E
word_41DE:          dw ?                                    ; 41DE
word_41E0:          dw ?                                    ; 41E0
                    rb 140                                  ; 41E2
arr_426E:           rb 4                                    ; 426E
arr_4272:           rb 4                                    ; 4272
arr_4276:           rb 4                                    ; 4276
arr_427A:           rb 4                                    ; 427A
arr_427E:           rb 120                                  ; 427E
word_42F6:          dw ?                                    ; 42F6
                    dw ?                                    ; 42F8
word_42FA:          dw ?                                    ; 42FA
                    dw ?                                    ; 42FC
word_42FE:          dw ?                                    ; 42FE
                    dw ?                                    ; 4300
word_4302:          dw ?                                    ; 4302
                    dw ?                                    ; 4304
word_4306:          dw ?                                    ; 4306
word_4308:          dw ?                                    ; 4308
                    rb 156                                  ; 430A
word_43A6:          dw ?                                    ; 43A6
                    times 16 db 0FCh                        ; 43A8
                    db 0FEh
                    rb 30
                    db 0FEh
                    times 29 db 0FCh
                    db 0FEh
                    rb 36
                    db 0FEh
                    times 33 db 0FCh
                    db 0FEh
                    rb 22
                    db 0FEh
                    times 20 db 0FCh
                    times 11 db 0FBh
                    db 0FCh, 0FDh, 0FEh, 0FFh
                    rb 34
                    db 0FFh, 0FEh, 0FDh, 0FCh
                    times 29 db 0FBh
                    db 0FCh, 0FDh, 0FEh, 0FFh
                    rb 20
                    db 0FFh, 0FEh, 0FDh, 0FCh
                    times 18 db 0FBh
                    times 6 db 0FCh
                    db 0FEh
                    rb 22
                    db 0FEh
                    times 4 db 0FCh
                    db 0FEh
                    rb 22
                    db 0FEh
                    times 6 db 0FCh
                    times 10 db 0F0h
                    db 0F2h, 0F4h, 0F6h, 0F8h, 0FAh, 0FCh, 0FDh, 0FEh, 0FFh
                    rb 26
                    db 0FFh, 0FEh, 0FDh, 0FCh, 0FAh, 0F8h, 0F6h, 0F4h, 0F2h
                    times 10 db 0F0h
                    times 16 db 0FCh
                    db 0FEh
                    rb 30
                    db 0FEh
                    times 30 db 0FCh
                    db 0FEh
                    rb 34
                    db 0FEh
                    times 34 db 0FCh
                    db 0FEh
                    rb 22
                    db 0FEh
                    times 32 db 0FCh
                    db 0FEh
                    rb 38
                    db 0FEh
                    times 17 db 0FCh
                    db 0FEh
                    rb 52
                    db 0FEh
                    times 21 db 0FCh
                    db 0FEh
                    rb 30
                    db 0FEh
                    times 16 db 0FCh

word_46E8:          dw ?                                    ; 46E8
word_46EA:          dw ?                                    ; 46EA
                    rb 190                                  ; 46EC
                    times 10 db 4                           ; 47AA
                    db 3, 3, 2, 2, 1, 1
                    rb 32
                    db 1, 1, 2, 2, 3, 3
                    times 28 db 4
                    db 3, 3, 2, 2, 1, 1
                    rb 16
                    db 1, 1, 2, 2, 3, 3
                    times 18 db 4
                    rb 64
                    db 16, 16, 16, 16, 16, 15, 14, 13, 12, 10, 8, 4, 3, 2, 1
                    rb 34
                    db 1, 2, 3, 4, 8, 10, 12, 13, 14, 15, 16, 16, 16, 16, 16
                    rb 384

word_4A2A:          dw ?                                    ; 4A2A
arr13_4A2C:         dw 4A60h, 4AAAh, 4AFEh, 4B38h, 4B8Ah, 4BD4h, 4C46h, 4C88h, 4CD2h, 4D24h, 4D5Eh, 4DB8h, 4E2Eh

arr13_4A46:         dw 40h, 4Ah, 30h, 48h, 40h, 68h, 38h, 40h, 48h, 30h, 50h, 6Ch, 40h

arr74_4A60:         db 0, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1
                    db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1
                    db 1, 1, 1, 1, 1, 1, 1, 1, 2, 1

arr84_4AAA:         db 0, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1
                    db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1
                    db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1
                    db 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1
                    db 1, 1, 2, 1

arr58_4AFE:         db 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2
                    db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1
                    db 1, 1, 1, 1, 1, 1, 1, 1, 2, 1

arr82_4B38:         db 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2
                    db 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
                    db 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
                    db 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
                    db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 2, 1

arr74_4B8A:         db 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1
                    db 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1
                    db 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1
                    db 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 1, 1, 1, 1, 1, 1, 1, 1, 2, 1

arr114_4BD4:        db 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2
                    db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2
                    db 1, 0, 0, 0, 0, 0, 0, 1, 2, 1, 2, 1, 1, 1, 1, 1
                    db 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1
                    db 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 2, 1

arr66_4C46:         db 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 2, 1

arr74_4C88:         db 0, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1
                    db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1
                    db 1, 1, 1, 1, 1, 1, 1, 1, 2, 1

arr82_4CD2:         db 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1
                    db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1
                    db 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1
                    db 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 2, 1

arr58_4D24:         db 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2
                    db 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2
                    db 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2
                    db 1, 1, 1, 1, 1, 1, 1, 1, 2, 1

arr90_4D5E:         db 0, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1
                    db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1
                    db 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1
                    db 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    db 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1
                    db 1, 1, 1, 1, 1, 1, 1, 1, 2, 1

arr118_4DB8:        db 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1
                    db 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1
                    db 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1
                    db 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1
                    db 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1
                    db 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1
                    db 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1, 2, 1
                    db 2, 1, 2, 1, 2, 1

arr74_4E2E:         db 2, 0, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
                    db 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2
                    db 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2
                    db 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0, 2
                    db 2, 2, 2, 2, 2, 2, 2, 2, 0, 2

word_4E78:          dw ?                                    ; 4E78

arr40_4E7A:         ; 4E7A: Forest
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 00, 0B0h, 00
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 00, 0B0h, 00
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 00, 0B0h, 00
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 00, 0B0h, 00
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 00, 0B0h, 00 
                    ; 4EA2: Night
                    db 010h, 0FFh, 090h, 0FFh, 000h, 000h, 070h, 000h
                    db 0F0h, 000h, 010h, 0FFh, 090h, 0FFh, 000h, 000h
                    db 070h, 000h, 0F0h, 000h, 010h, 0FFh, 090h, 0FFh
                    db 000h, 000h, 070h, 000h, 0F0h, 000h, 010h, 0FFh
                    db 090h, 0FFh, 000h, 000h, 070h, 000h, 0F0h, 000h
                    ; 4ECA: Fog
                    db 90h, 0FFh, 00h, 000h, 70h, 000h, 90h, 0FFh
                    db 00h, 000h, 70h, 000h, 90h, 0FFh, 00h, 000h
                    db 70h, 000h, 90h, 0FFh, 00h, 000h, 70h, 000h
                    db 90h, 0FFh, 00h, 000h, 70h, 000h, 90h, 0FFh
                    db 00h, 000h, 70h, 000h, 90h, 0FFh, 00h, 000h
                    ; 4EF2: Snow
                    db 40h, 0FFh, 0C0h, 0FFh, 40h, 0, 0C0h, 0
                    db 40h, 0FFh, 0C0h, 0FFh, 40h, 0, 0C0h, 0
                    db 40h, 0FFh, 0C0h, 0FFh, 40h, 0, 0C0h, 0
                    db 40h, 0FFh, 0C0h, 0FFh, 40h, 0, 0C0h, 0
                    db 40h, 0FFh, 0C0h, 0FFh, 40h, 0, 0C0h, 0
                    ; 4F1A: Desert
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 0, 0B0h, 0
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 0, 0B0h, 0
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 0, 0B0h, 0
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 0, 0B0h, 0
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 0, 0B0h, 0
                    ; 4F42: MotorWay
                    db 070h, 0, 0E0h, 0, 050h, 1, 070h, 0
                    db 0E0h, 0, 050h, 1, 070h, 0, 0E0h, 0
                    db 050h, 1, 070h, 0, 0E0h, 0, 050h, 1
                    db 070h, 0, 0E0h, 0, 050h, 1, 070h, 0
                    db 0E0h, 0, 050h, 1, 070h, 0, 0E0h, 0
                    ; 4F6A: Marsh
                    db 80h, 0FFh, 00h, 000h, 80h, 000h, 80h, 0FFh
                    db 00h, 000h, 80h, 000h, 80h, 0FFh, 00h, 000h
                    db 80h, 000h, 80h, 0FFh, 00h, 000h, 80h, 000h
                    db 80h, 0FFh, 00h, 000h, 80h, 000h, 80h, 0FFh
                    db 00h, 000h, 80h, 000h, 80h, 0FFh, 00h, 000h
                    ; 4F92: Storm
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 0, 0B0h, 0
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 0, 0B0h, 0
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 0, 0B0h, 0
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 0, 0B0h, 0
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 0, 0B0h, 0
                    ; 4FBA: Roadworks
                    db 40h, 0FFh, 0C0h, 0FFh, 40h, 0, 0C0h, 0
                    db 40h, 0FFh, 0C0h, 0FFh, 40h, 0, 0C0h, 0
                    db 40h, 0FFh, 0C0h, 0FFh, 40h, 0, 0C0h, 0
                    db 40h, 0FFh, 0C0h, 0FFh, 40h, 0, 0C0h, 0
                    db 40h, 0FFh, 0C0h, 0FFh, 40h, 0, 0C0h, 0
                    ; 4FE2: Rally
                    db 90h, 0FFh, 00h, 000h, 70h, 000h, 90h, 0FFh
                    db 00h, 000h, 70h, 000h, 90h, 0FFh, 00h, 000h
                    db 70h, 000h, 90h, 0FFh, 00h, 000h, 70h, 000h
                    db 90h, 0FFh, 00h, 000h, 70h, 000h, 90h, 0FFh
                    db 00h, 000h, 70h, 000h, 90h, 0FFh, 00h, 000h
                    ; 500A: Wind
                    db 20h, 0FFh, 0B0h, 0FFh, 50h, 0, 0E0h, 0
                    db 20h, 0FFh, 0B0h, 0FFh, 50h, 0, 0E0h, 0
                    db 20h, 0FFh, 0B0h, 0FFh, 50h, 0, 0E0h, 0
                    db 20h, 0FFh, 0B0h, 0FFh, 50h, 0, 0E0h, 0
                    db 20h, 0FFh, 0B0h, 0FFh, 50h, 0, 0E0h, 0
                    ; 5032: Futuristic
                    db 00h, 000h, 80h, 000h, 00h, 001h, 80h, 001h
                    db 80h, 0FEh, 00h, 0FFh, 80h, 0FFh, 00h, 000h
                    db 80h, 000h, 00h, 001h, 80h, 001h, 80h, 0FEh
                    db 00h, 0FFh, 80h, 0FFh, 00h, 000h, 80h, 000h
                    db 00h, 001h, 80h, 001h, 80h, 0FEh, 00h, 0FFh
                    ; 505A: Mountains
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 0, 0B0h, 0
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 0, 0B0h, 0
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 0, 0B0h, 0
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 0, 0B0h, 0
                    db 50h, 0FFh, 0C0h, 0FFh, 40h, 0, 0B0h, 0

arr_5082:           dw 19h, 19h, 1Eh, 1Eh, 23h, 23h, 28h, 28h, 2Ch, 30h, 34h, 38h, 3Ch, 40h, 44h, 48h, 4Bh, 4Eh, 51h, 54h, 56h, 58h, 5Ah, 5Ch, 5Eh, 5Fh, 60h, 60h, 60h, 60h, 5Fh, 5Eh, 5Ch, 5Ah, 58h, 56h, 54h, 51h, 4Eh, 4Bh, 48h, 44h, 40h, 3Ch, 38h, 34h, 30h, 2Ch, 28h, 24h, 20h, 1Ch, 18h, 14h, 10h, 0Ch, 8, 4, 0
                    ; 50F8
                    db 0FBh, 0FFh, 0F6h, 0FFh, 0F1h, 0FFh, 0ECh, 0FFh, 0E7h, 0FFh, 0E2h, 0FFh, 0D8h, 0FFh, 0C4h, 0FFh, 0B0h, 0FFh, 09Ch, 0FFh, 06Ah, 0FFh, 038h, 0FFh, 006h, 0FFh, 0D4h, 0FEh, 070h, 0FEh, 00Ch, 0FEh, 0A8h, 0FDh

; 152 bytes
arr_511A:           db 0FBh, 0FFh, 0FBh, 0FFh, 0FBh, 0FFh, 0FBh, 0FFh
                    db 0FBh, 0FFh, 0FBh, 0FFh, 0FBh, 0FFh, 0FBh, 0FFh
                    db 0F6h, 0FFh, 0F6h, 0FFh, 0F6h, 0FFh, 0F6h, 0FFh
                    db 0F6h, 0FFh, 0F6h, 0FFh, 0F6h, 0FFh, 0F6h, 0FFh
                    db 0F1h, 0FFh, 0F1h, 0FFh, 0F1h, 0FFh, 0F1h, 0FFh
                    db 0F1h, 0FFh, 0F1h, 0FFh, 0F1h, 0FFh, 0F1h, 0FFh
                    db 0ECh, 0FFh, 0ECh, 0FFh, 0ECh, 0FFh, 0ECh, 0FFh
                    db 0ECh, 0FFh, 0ECh, 0FFh, 0ECh, 0FFh, 0ECh, 0FFh
                    db 0E7h, 0FFh, 0E7h, 0FFh, 0E7h, 0FFh, 0E7h, 0FFh
                    db 0E2h, 0FFh, 0E2h, 0FFh, 0E2h, 0FFh, 0E2h, 0FFh
                    db 0D8h, 0FFh, 0D8h, 0FFh, 0D8h, 0FFh, 0D8h, 0FFh
                    db 0D3h, 0FFh, 0D3h, 0FFh, 0D3h, 0FFh, 0D3h, 0FFh
                    db 0CEh, 0FFh, 0CEh, 0FFh, 0C9h, 0FFh, 0C9h, 0FFh
                    db 0C4h, 0FFh, 0C4h, 0FFh, 0BFh, 0FFh, 0BFh, 0FFh
                    db 0BAh, 0FFh, 0B5h, 0FFh, 0B0h, 0FFh, 0ABh, 0FFh
                    db 0A6h, 0FFh, 0A1h, 0FFh, 09Ch, 0FFh, 097h, 0FFh
                    db 092h, 0FFh, 088h, 0FFh, 074h, 0FFh, 060h, 0FFh
                    db 04Ch, 0FFh, 038h, 0FFh, 006h, 0FFh, 0D4h, 0FEh
                    db 070h, 0FEh, 00Ch, 0FEh, 0A8h, 0FDh, 044h, 0FDh

; 10 bytes
arr_51B2:           db 55h, 3Dh, 55h, 64h, 80h, 96h, 0, 0C8h, 0, 0F8h

; 152 bytes
arr_51BC:           dw 19h, 19h, 1Eh, 1Eh
                    dw 23h, 23h, 28h, 28h
                    dw 2Ch, 30h, 34h, 38h
                    dw 3Ch, 40h, 44h, 48h
                    dw 4Bh, 4Eh, 51h, 54h
                    dw 56h, 58h, 5Ah, 5Ch
                    dw 5Eh, 5Fh, 60h, 60h
                    dw 60h, 60h, 5Eh, 5Ch
                    dw 5Ah, 56h, 52h, 4Eh
                    dw 4Ah, 46h, 41h, 3Ch
                    dw 37h, 32h, 2Dh, 28h
                    dw 23h, 1Eh, 19h, 14h
                    dw 0Fh, 0Ah, 05h, 00h
                    dw 0FFFAh, 0FFF4h, 0FFEEh, 0FFE8h 
                    dw 0FFE2h, 0FFD8h, 0FFCEh, 0FFC4h 
                    dw 0FFBAh, 0FFB0h, 0FFA6h, 0FF9Ch 
                    dw 0FF6Ah, 0FF38h, 0FED4h, 0FE70h 
                    dw 0FDA8h, 0FDA8h, 0FDA8h, 0FDA8h 
                    dw 0FDA8h, 0FDA8h, 0FDA8h, 0FDA8h 

; 152 bytes
arr_5254:           dw 0FFFBh, 0FFFBh, 0FFFBh, 0FFFBh 
                    dw 0FFFBh, 0FFFBh, 0FFFBh, 0FFFBh 
                    dw 0FFF6h, 0FFF6h, 0FFF6h, 0FFF6h 
                    dw 0FFF6h, 0FFF6h, 0FFF6h, 0FFF6h 
                    dw 0FFF1h, 0FFF1h, 0FFF1h, 0FFF1h 
                    dw 0FFF1h, 0FFF1h, 0FFF1h, 0FFF1h 
                    dw 0FFECh, 0FFECh, 0FFECh, 0FFECh 
                    dw 0FFECh, 0FFECh, 0FFECh, 0FFECh 
                    dw 0FFE7h, 0FFE7h, 0FFE7h, 0FFE7h 
                    dw 0FFE2h, 0FFE2h, 0FFE2h, 0FFE2h 
                    dw 0FFD8h, 0FFD8h, 0FFD8h, 0FFD8h 
                    dw 0FFCEh, 0FFCEh, 0FFCEh, 0FFCEh 
                    dw 0FFC4h, 0FFC4h, 0FFBAh, 0FFBAh 
                    dw 0FFB0h, 0FFB0h, 0FFA6h, 0FFA6h 
                    dw 0FF9Ch, 0FF88h, 0FF6Ah, 0FF38h 
                    dw 0FED4h, 0FE70h, 0FE0Ch, 0FDA8h 
                    dw 0FD44h, 0FD44h, 0FCE0h, 0FCE0h 
                    dw 0FC18h, 0FC18h, 0FC18h, 0FC18h 
                    dw 0FC18h, 0FC18h, 0FC18h, 0FC18h 

; 10 bytes
arr_52EC:           db 0, 03Ch, 0AAh, 68h, 0, 96h, 0, 0C3h, 0AAh, 0F1h

; 158 bytes
arr_52F6:           dw 19h, 19h, 1Eh, 1Eh
                    dw 23h, 23h, 28h, 28h
                    dw 2Ch, 30h, 34h, 38h
                    dw 3Ch, 40h, 44h, 48h
                    dw 4Bh, 4Eh, 51h, 54h
                    dw 56h, 58h, 5Ah, 5Ch
                    dw 5Eh, 5Fh, 60h, 60h
                    dw 60h, 60h, 5Fh, 5Dh
                    dw 5Bh, 58h, 55h, 52h
                    dw 4Fh, 4Bh, 47h, 43h
                    dw 3Fh, 3Bh, 36h, 32h
                    dw 2Dh, 29h, 24h, 20h
                    dw 1Bh, 17h, 13h, 0Eh
                    dw 09h, 04h
                    dw 0FFFFh, 0FFFAh, 0FFF5h, 0FFEEh, 0FFE7h 
                    dw 0FFE0h, 0FFD8h, 0FFD1h, 0FFC9h, 0FFC2h 
                    dw 0FFA6h, 0FF88h, 0FF4Ch, 0FF10h, 0FEA2h 
                    dw 0FE70h, 0FE0Ch, 0FDA8h, 0FDA8h, 0FDA8h 
                    dw 0FDA8h, 0FDA8h, 0FDA8h, 0FDA8h, 0FDA8h 

; 152 bytes
arr_5394:           dw 0FFFBh, 0FFFBh, 0FFFBh, 0FFFBh
                    dw 0FFFBh, 0FFFBh, 0FFFBh, 0FFFBh
                    dw 0FFF6h, 0FFF6h, 0FFF6h, 0FFF6h
                    dw 0FFF6h, 0FFF6h, 0FFF6h, 0FFF6h
                    dw 0FFF1h, 0FFF1h, 0FFF1h, 0FFF1h
                    dw 0FFF1h, 0FFF1h, 0FFF1h, 0FFF1h
                    dw 0FFECh, 0FFECh, 0FFECh, 0FFECh
                    dw 0FFECh, 0FFECh, 0FFECh, 0FFECh
                    dw 0FFE7h, 0FFE7h, 0FFE7h, 0FFE7h
                    dw 0FFE2h, 0FFE2h, 0FFE2h, 0FFE2h
                    dw 0FFD8h, 0FFD8h, 0FFD8h, 0FFD8h
                    dw 0FFCEh, 0FFCEh, 0FFCEh, 0FFCEh
                    dw 0FFC9h, 0FFC9h, 0FFC4h, 0FFC4h
                    dw 0FFBAh, 0FFBAh, 0FFB5h, 0FFB5h
                    dw 0FFABh, 0FF9Ch, 0FF88h, 0FF74h
                    dw 0FF60h, 0FF4Ch, 0FF38h, 0FED4h
                    dw 0FE70h, 0FE0Ch, 0FDA8h, 0FD44h
                    dw 0FCE0h, 0FC7Ch, 0FC18h, 0FC18h
                    dw 0FC18h, 0FC18h, 0FC18h, 0FC18h

; 10 bytes
arr_542C:           db 0AAh, 3Ch, 80h, 66h, 55h, 96h, 80h, 0C5h, 0D5h, 0F4h

arr_5436:           dw 032h, 032h, 03Ch
                    dw 03Ch, 046h, 046h
                    dw 050h, 050h, 05Ah
                    dw 064h, 06Eh, 078h
                    dw 082h, 08Ch, 096h
                    dw 0A0h, 0A5h, 0AAh
                    dw 0B4h, 0B9h, 0BEh
                    dw 0C3h, 0C8h, 0CDh
                    dw 0D2h, 0D7h, 0DCh
                    dw 0E1h, 0E6h, 0EBh
                    dw 0F0h, 0F5h, 0FAh
                    dw 0FFh
                    db 4, 1, 9, 1, 9, 1, 4, 1
                    dw 0FFh
                    dw 0FAh, 0F5h, 0F0h
                    dw 0EBh, 0E6h, 0E1h
                    dw 0DCh, 0D7h, 0D2h
                    dw 0CDh, 0C8h, 0C3h
                    dw 0BEh, 0B9h, 0B4h
                    dw 0AAh, 0A5h, 0A0h
                    dw 096h, 08Ch, 082h
                    dw 078h, 06Eh, 064h
                    dw 05Ah, 050h, 050h
                    dw 046h, 046h, 03Ch
                    dw 03Ch, 032h, 032h
                    dw 028h, 01Eh, 014h
                    dw 0Ah

word_54CE:          dw ?                                    ; 54CE

arr_5490:           ; 54D0: Forest (192 bytes)
                    dw 0230h, 0221h, 0CCCh, 0, 0340h, 0331h, 0331h, 0
                    dw 0347h, 0347h, 0347h, 0, 0347h, 0347h, 0347h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0230h, 0CCCh, 0CCCh, 0, 0340h, 0CCCh, 0CCCh, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    ; 5590: Snow (64 bytes)
                    dw 0DDDh, 0999h, 0888h, 0, 0BCEh, 078Ah, 0679h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0CCCh, 0BBBh, 0BBBh, 0, 0ABDh, 0BBBh, 0BBBh, 0
                    ; 55D0: Desert (64 bytes)
                    dw 0875h, 0764h, 0653h, 0, 0765h, 0654h, 0543h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0765h, 0654h, 0543h, 0, 0765h, 0654h, 0543h, 0
                    ; 5610: MotorWay (64 bytes)
                    dw 0142h, 0232h, 0CCCh, 0, 0152h, 0343h, 0343h, 0
                    dw 0, 0121h, 0888h, 0, 0, 0232h, 0232h, 0
                    dw 0232h, 0232h, 0232h, 0, 0232h, 0232h, 0232h, 0
                    dw 0142h, 0CCCh, 0CCCh, 0, 0152h, 0CCCh, 0CCCh, 0
                    ; 5650: Marsh (128)
                    dw 0032h, 0212h, 098Ah, 0, 0042h, 0323h, 0323h, 0
                    dw 0134h, 0134h, 0134h, 0, 0134h, 0134h, 0134h, 0
                    dw 0134h, 0212h, 098Ah, 0, 0134h, 0323h, 0323h, 0
                    dw 0032h, 098Ah, 098Ah, 0, 0042h, 098Ah, 098Ah, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    ; 56D0: Roadworks (64)
                    dw 0660h, 0666h, 0CCCh, 0, 0760h, 0766h, 0766h, 0
                    dw 0, 0444h, 0888h, 0, 0, 0544h, 0544h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0660h, 0CCCh, 0CCCh, 0, 0760h, 0CCCh, 0CCCh, 0
                    ; 5710: Rally (64)
                    dw 0430h, 0420h, 0520h, 0, 0530h, 0520h, 0420h, 0
                    dw 0054h, 0054h, 0054h, 0, 0054h, 0054h, 0054h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0430h, 0CCCh, 0CCCh, 0, 0530h, 0CCCh, 0CCCh, 0
                    ; 5750: Wind (64)
                    dw 0240h, 0343h, 0CCCh, 0, 0351h, 0454h, 0454h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0240h, 0CCCh, 0CCCh, 0, 0351h, 0CCCh, 0CCCh, 0
                    ; 5790: Futuristic (64)
                    dw 0340h, 0554h, 0443h, 0, 0350h, 0443h, 0554h, 0
                    dw 0, 0332h, 0221h, 0, 0, 0221h, 0332h, 0
                    dw 0340h, 0943h, 0732h, 0, 0350h, 0732h, 0943h, 0
                    dw 0340h, 0877h, 0111h, 0, 0350h, 0111h, 0877h, 0
                    ; 57D0: Mountains (64)
                    dw 0EEEh, 0CCCh, 0343h, 0, 0454h, 0CCCh, 0454h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0EEEh, 0CCCh, 0EEEh, 0, 0454h, 0CCCh, 0454h, 0
                    ; 5810: Fog (576)
                    dw 0230h, 0111h, 0CCCh, 0, 0242h, 0121h, 0121h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0230h, 0CCCh, 0CCCh, 0, 0242h, 0CCCh, 0CCCh, 0
                    dw 0230h, 0111h, 0CCCh, 0, 0242h, 0121h, 0121h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0230h, 0CCCh, 0CCCh, 0, 0242h, 0CCCh, 0CCCh, 0
                    dw 0341h, 0222h, 0BBBh, 0, 0353h, 0232h, 0232h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0341h, 0BBBh, 0BBBh, 0, 0353h, 0BBBh, 0BBBh, 0
                    dw 0341h, 0222h, 0AAAh, 0, 0353h, 0232h, 0232h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0341h, 0AAAh, 0AAAh, 0, 0353h, 0AAAh, 0AAAh, 0
                    dw 0452h, 0333h, 0999h, 0, 0464h, 0343h, 0343h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0452h, 0999h, 0999h, 0, 0464h, 0999h, 0999h, 0
                    dw 0452h, 0333h, 0999h, 0, 0464h, 0343h, 0343h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0452h, 0999h, 0999h, 0, 0464h, 0999h, 0999h, 0
                    dw 0564h, 0444h, 0888h, 0, 0565h, 0454h, 0454h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0564h, 0888h, 0888h, 0, 0565h, 0888h, 0888h, 0
                    dw 0665h, 0555h, 0777h, 0, 0666h, 0565h, 0565h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0665h, 0777h, 0777h, 0, 0666h, 0777h, 0777h, 0
                    dw 0666h, 0666h, 0666h, 0, 0666h, 0666h, 0666h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0666h, 0666h, 0666h, 0, 0666h, 0666h, 0666h, 0
                    ; 5A50: Night (576)
                    dw 0453h, 0554h, 0CCCh, 0, 0353h, 0555h, 0555h, 0
                    dw 0, 0554h, 0CCCh, 0, 0, 0555h, 0555h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0453h, 0CCCh, 0CCCh, 0, 0353h, 0CCCh, 0CCCh, 0
                    dw 0342h, 0554h, 0BBBh, 0, 0242h, 0555h, 0555h, 0
                    dw 0, 0554h, 0CCCh, 0, 0, 0555h, 0555h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0342h, 0BBBh, 0BBBh, 0, 0242h, 0BBBh, 0BBBh, 0
                    dw 0342h, 0443h, 0AAAh, 0, 0242h, 0444h, 0444h, 0
                    dw 0, 0554h, 0CCCh, 0, 0, 0555h, 0555h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0342h, 0AAAh, 0AAAh, 0, 0242h, 0AAAh, 0AAAh, 0
                    dw 0231h, 0443h, 0999h, 0, 0131h, 0444h, 0444h, 0
                    dw 0, 0554h, 0CCCh, 0, 0, 0555h, 0555h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0231h, 0999h, 0999h, 0, 0131h, 0999h, 0999h, 0
                    dw 0231h, 0332h, 0777h, 0, 0131h, 0333h, 0333h, 0
                    dw 0, 0554h, 0CCCh, 0, 0, 0555h, 0555h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0231h, 0777h, 0777h, 0, 0131h, 0777h, 0777h, 0
                    dw 0231h, 0332h, 0555h, 0, 0131h, 0333h, 0333h, 0
                    dw 0, 0554h, 0CCCh, 0, 0, 0555h, 0555h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0231h, 0555h, 0555h, 0, 0131h, 0555h, 0555h, 0
                    dw 0120h, 0221h, 0333h, 0, 0020h, 0222h, 0333h, 0
                    dw 0, 0554h, 0CCCh, 0, 0, 0555h, 0555h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0120h, 0333h, 0333h, 0, 0020h, 0333h, 0333h, 0
                    dw 0010h, 0110h, 0111h, 0, 0010h, 0111h, 0111h, 0
                    dw 0, 0554h, 0CCCh, 0, 0, 0555h, 0555h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0010h, 0222h, 0111h, 0, 0010h, 0222h, 0111h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0554h, 0CCCh, 0, 0, 0555h, 0555h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0, 0111h, 0, 0, 0, 0111h, 0, 0
                    ; 5C90: Storm (576)
                    dw 0012h, 0024h, 0CCCh, 0, 0010h, 0123h, 0123h, 0
                    dw 0037h, 0037h, 0037h, 0, 0037h, 0037h, 0037h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0012h, 0CCCh, 0CCCh, 0, 0010h, 0CCCh, 0CCCh, 0
                    dw 0012h, 0024h, 0BBCh, 0, 0010h, 0123h, 0123h, 0
                    dw 0037h, 0037h, 0037h, 0, 0037h, 0037h, 0037h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0012h, 0BBCh, 0BBCh, 0, 0010h, 0BBCh, 0BBCh, 0
                    dw 0012h, 0024h, 0ABCh, 0, 0010h, 0123h, 0123h, 0
                    dw 0037h, 0037h, 0037h, 0, 0037h, 0037h, 0037h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0012h, 0ABCh, 0ABCh, 0, 0010h, 0ABCh, 0ABCh, 0
                    dw 0012h, 0024h, 08ABh, 0, 0010h, 0123h, 0123h, 0
                    dw 0037h, 0037h, 0037h, 0, 0037h, 0037h, 0037h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0012h, 08ABh, 08ABh, 0, 0010h, 08ABh, 08ABh, 0
                    dw 0012h, 0024h, 079Ah, 0, 0010h, 0123h, 0123h, 0
                    dw 0037h, 0037h, 0037h, 0, 0037h, 0037h, 0037h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0012h, 079Ah, 079Ah, 0, 0010h, 079Ah, 079Ah, 0
                    dw 0012h, 0024h, 0689h, 0, 0010h, 0123h, 0123h, 0
                    dw 0037h, 0037h, 0037h, 0, 0037h, 0037h, 0037h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0012h, 0689h, 0689h, 0, 0010h, 0689h, 0689h, 0
                    dw 0012h, 0024h, 0578h, 0, 0010h, 0123h, 0123h, 0
                    dw 0037h, 0037h, 0037h, 0, 0037h, 0037h, 0037h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0012h, 0578h, 0578h, 0, 0010h, 0578h, 0578h, 0
                    dw 0012h, 0024h, 0467h, 0, 0010h, 0123h, 0123h, 0
                    dw 0037h, 0037h, 0037h, 0, 0037h, 0037h, 0037h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0012h, 0467h, 0467h, 0, 0010h, 0467h, 0467h, 0
                    dw 0012h, 0024h, 0356h, 0, 0010h, 0123h, 0123h, 0
                    dw 0037h, 0037h, 0037h, 0, 0037h, 0037h, 0037h, 0
                    dw 0, 0, 0, 0, 0, 0, 0, 0
                    dw 0012h, 0356h, 0356h, 0, 0010h, 0356h, 0356h, 0

arr_5ED0:           dw 00Eh, 012h, 017h, 01Bh, 01Fh, 024h, 027h, 02Dh
                    dw 030h, 034h, 039h, 03Eh, 041h, 044h, 048h, 04Ch
                    dw 051h, 057h, 05Dh, 060h, 064h, 068h, 06Ch, 070h
                    dw 076h, 079h, 07Dh, 081h, 086h, 08Bh, 08Fh, 094h
                    dw 098h, 09Ch, 0A1h, 0A5h, 0AAh, 0AEh, 0B3h, 0B8h
                    dw 0BCh, 0C0h, 0C4h, 0C8h, 0CCh, 0D0h, 0D5h, 0D9h
                    dw 0DEh, 0E2h, 0E6h, 0EAh, 0EEh, 0F3h, 0F7h, 0FBh

arr_5F40:           db -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 16, 16, 15, 15, 14, 14
                    db 13, 13, 13, 13, 12, 12, 12, 12, 11, 11, 11, 11, 10, 10, 10, 10
                    db 09, 09, 09, 09, 09, 09, 09, 09, 08, 08, 08, 08, 08, 08, 08, 08
                    db 07, 07, 07, 07, 07, 07, 07, 07, 06, 06, 06, 06, 06, 06, 06, 06
                    db 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05, 05
                    db 04, 04, 04, 04, 04, 04, 04, 04, 04, 04, 04, 04, 04, 04, 04, 04
                    db 03, 03, 03, 03, 03, 03, 03, 03, 03, 03, 03, 03, 03, 03, 03, 03
                    db 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02
                    db 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01
                    db 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01
                    db 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00
                    db 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00
                    db 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00
                    db 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00
                    db -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    db -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1

word_6040:          dw ?                                    ; 6040

arr_6042:           ; Forest
                    db 0, 97h, 85h, 88h, 89h, 8Ah, 80h, 0F0h, 0, 0, 0, 94h, 95h, 0, 98h, 99h, 0, 0, 0, 0, 0, 84h, 0, 90h
                    ; Night
                    db 0, 0, 0, 0C6h, 0C7h, 0C8h, 0BDh, 0F4h, 82h, 83h, 0C0h, 0C1h, 0C2h, 0, 0C4h, 0F5h, 0, 0, 0, 0, 0, 84h, 0, 92h
                    ; Fog
                    db 0, 0A9h, 0, 0AAh, 0ABh, 0ACh, 0A5h, 0F1h, 0, 0, 0A3h, 0A4h, 0EEh, 0, 0, 0, 0, 0, 0, 0, 0, 84h, 0, 91h
                    ; Snow
                    db 0, 0B0h, 0, 88h, 89h, 8Ah, 80h, 0F0h, 0, 0, 0F8h, 0ADh, 0, 0AFh, 0B0h, 0B1h, 0F2h, 0B3h, 0B4h, 0, 0, 0, 0, 90h
                    ; Desert
                    db 0, 0, 0, 88h, 89h, 8Ah, 0, 0, 0, 0, 0B5h, 0B6h, 0B7h, 0B8h, 0B9h, 0BAh, 0F3h, 0BCh, 0, 70h, 0, 0, 0, 90h
                    ; MotorWay
                    db 0, 0, 0, 88h, 89h, 8Ah, 80h, 0F0h, 82h, 83h, 9Ah, 9Bh, 9Ch, 9Dh, 9Eh, 9Fh, 0A0h, 0A1h, 0A2h, 0, 0, 84h, 0, 90h
                    ; Marsh
                    db 0, 97h, 85h, 88h, 89h, 8Ah, 80h, 0F0h, 0CDh, 0, 0C9h, 0CAh, 0CBh, 0CCh, 0CEh, 0, 0, 0, 0, 0, 0, 84h, 0, 90h
                    ; Storm
                    db 0, 97h, 85h, 88h, 89h, 8Ah, 80h, 0F0h, 0, 0, 0F9h, 0D0h, 0E8h, 0EFh, 8Dh, 0, 0, 0, 0, 6Dh, 71h, 0, 0, 90h
                    ; Roadworks
                    db 97h, 0, 0, 88h, 89h, 8Ah, 80h, 0F0h, 0, 083h, 0D1h, 0D3h, 0D4h, 0, 0D6h, 0D7h, 0D8h, 0F6h, 0D9h, 0, 0, 84h, 0, 90h
                    ; Rally
                    db 0, 0, 85h, 88h, 89h, 8Ah, 0, 0, 0, 0, 0E7h, 0, 0E9h, 0EAh, 0EBh, 0ECh, 0EDh, 0, 0, 0, 0, 84h, 0, 90h
                    ; Wind
                    db 0, 0, 0, 88h, 89h, 8Ah, 80h, 0F0h, 0, 0, 81h, 86h, 0, 0A6h, 0BBh, 0B2h, 0DAh, 0, 0, 0, 0, 84h, 0, 90h
                    ; Futuristic
                    db 0, 0, 0, 88h, 89h, 8Ah, 80h, 0F0h, 82h, 83h, 0DBh, 0DCh, 0DDh, 0DEh, 0, 0D2h, 0D5h, 0, 0, 0, 0, 84h, 0, 90h
                    ; Mountains
                    db 0, 0, 0, 88h, 89h, 8Ah, 0, 0, 0, 0, 96h, 0DFh, 0E2h, 0E3h, 0E4h, 0E5h, 0, 0, 0, 0, 0, 84h, 0, 90h

arr_617A:           db '`abcdefghijklnorstuv'

arr_618E:           ; Forest
                    dw 0000h, 0666h, 0222h, 0600h, 0B9Ch, 0CCCh, 0040h, 0A00h 
                    dw 0CBCh, 0444h, 0430h, 0347h, 0F2Fh, 0463h, 0252h, 097Bh 
                    ; Night
                    dw 0000h, 0666h, 0222h, 0600h, 0004h, 0CCCh, 0040h, 0A00h 
                    dw 0444h, 0444h, 0026h, 0720h, 0F0Fh, 0888h, 0248h, 0A40h 
                    ; Fog
                    dw 0000h, 0666h, 0222h, 0600h, 0F0Fh, 0CCCh, 0040h, 0A00h 
                    dw 0F0Fh, 0333h, 0111h, 0360h, 0F0Fh, 0555h, 0444h, 0320h 
                    ; Snow
                    dw 0000h, 0666h, 0222h, 0600h, 0ABDh, 0CCCh, 0040h, 0A00h 
                    dw 089Bh, 089Bh, 0048h, 0053h, 0F0Fh, 0ABDh, 006Ah, 0075h 
                    ; Desert
                    dw 0000h, 0666h, 0222h, 0600h, 08ACh, 0CCCh, 0040h, 0A00h 
                    dw 048Bh, 0444h, 0765h, 0760h, 0F0Fh, 0260h, 0986h, 0980h 
                    ; MotorWay
                    dw 0000h, 0666h, 0222h, 0600h, 089Ch, 0CCCh, 0040h, 0A00h 
                    dw 0ABCh, 0338h, 0444h, 0604h, 0F0Fh, 054Dh, 0660h, 0937h 
                    ; Marsh
                    dw 0000h, 0666h, 0222h, 0600h, 0768h, 0CCCh, 0040h, 0A00h 
                    dw 098Ah, 0534h, 0312h, 0134h, 0000h, 0756h, 0444h, 0356h 
                    ; Storm
                    dw 0000h, 0666h, 0222h, 0600h, 0111h, 0CCCh, 0040h, 0A00h 
                    dw 0333h, 0320h, 0360h, 0037h, 0F0Fh, 0530h, 0444h, 0059h 
                    ; Roadworks
                    dw 0000h, 0666h, 0222h, 0600h, 0CB9h, 0CCCh, 0040h, 0A00h 
                    dw 0A97h, 0860h, 0443h, 0038h, 0F0Fh, 0CA0h, 0887h, 004Ch 
                    ; Rally
                    dw 0000h, 0666h, 0222h, 0600h, 08CDh, 0CCCh, 0040h, 0A00h 
                    dw 05ACh, 0430h, 0252h, 0054h, 0F8Fh, 0550h, 0363h, 0387h
                    ; Wind
                    dw 0000h, 0666h, 0222h, 0600h, 0454h, 0CCCh, 0040h, 0A00h 
                    dw 0554h, 0555h, 0444h, 0454h, 0F0Fh, 0987h, 0747h, 0787h 
                    ; Futuristic
                    dw 0000h, 0666h, 0222h, 0600h, 0AABh, 0CCCh, 0040h, 0A00h 
                    dw 0889h, 026Ch, 0053h, 0445h, 0F8Fh, 047Ah, 0363h, 0FFFh 
                    ; Mountains
                    dw 0000h, 0666h, 0222h, 0600h, 078Ch, 0CCCh, 0040h, 0A00h 
                    dw 0ABCh, 0338h, 0554h, 0444h, 0FFFh, 054Dh, 0874h, 0558h 

word_632E:          dw 2                                    ; 632E, si
word_6330:          dw ?                                    ; 6330, es
                    dw ?                                    ; 6332
word_6334:          dw ?                                    ; 6334
word_6336:          dw ?                                    ; 6336
word_6338:          dw ?                                    ; 6338
word_633A:          dw 0C8h                                 ; 633A
track_num:          dw ?                                    ; 633C
word_633E:          dw ?                                    ; 633E
word_6340:          dw ?                                    ; 6340
word_6342:          dw ?                                    ; 6342
word_6344:          dw ?                                    ; 6344
word_6346:          dw ?                                    ; 6346
word_6348:          dw ?                                    ; 6348
word_634A:          dw ?                                    ; 634A
word_634C:          dw ?                                    ; 634C
word_634E:          dw ?                                    ; 634E
word_6350:          dw ?                                    ; 6350
word_6352:          dw ?                                    ; 6352
word_6354:          dw ?                                    ; 6354
word_6356:          dw ?                                    ; 6356
word_6358:          dw ?                                    ; 6358
word_635A:          dw ?                                    ; 635A
word_635C:          dw ?                                    ; 635C
word_635E:          dw ?                                    ; 635E
word_6360:          dw ?                                    ; 6360
word_6362:          dw ?                                    ; 6362
word_6364:          dw ?                                    ; 6364
word_6366:          dw ?                                    ; 6366
word_6368:          dw ?                                    ; 6368
word_636A:          dw ?                                    ; 636A
word_636C:          dw ?                                    ; 636C
word_636E:          dw ?                                    ; 636E
word_6370:          dw ?                                    ; 6370
word_6372:          dw ?                                    ; 6372
word_6374:          dw ?                                    ; 6374
word_6376:          dw ?                                    ; 6376
word_6378:          dw ?                                    ; 6378
word_637A:          dw ?                                    ; 637A
word_637C:          dw ?                                    ; 637C
word_637E:          dw ?                                    ; 637E
word_6380:          dw ?                                    ; 6380
word_6382:          dw ?                                    ; 6382
word_6384:          dw ?                                    ; 6384
word_6386:          dw ?                                    ; 6386
word_6388:          dw ?                                    ; 6388
word_638A:          dw ?                                    ; 638A
word_638C:          dw ?                                    ; 638C
word_638E:          dw ?                                    ; 638E
word_6390:          dw ?                                    ; 6390
word_6392:          dw ?                                    ; 6392
word_6394:          dw ?                                    ; 6394
word_6396:          dw ?                                    ; 6396
word_6398:          dw ?                                    ; 6398
word_639A:          dw ?                                    ; 639A
word_639C:          dw ?                                    ; 639C
word_639E:          dw ?                                    ; 639E
word_63A0:          dw ?                                    ; 63A0
word_63A2:          dw ?                                    ; 63A2
word_63A4:          dw ?                                    ; 63A4
word_63A6:          dw ?                                    ; 63A6
word_63A8:          dw ?                                    ; 63A8
word_63AA:          dw ?                                    ; 63AA
word_63AC:          dw ?                                    ; 63AC
word_63AE:          dw ?                                    ; 63AE
word_63B0:          dw ?                                    ; 63B0
word_63B2:          dw ?                                    ; 63B2
word_63B4:          dw ?                                    ; 63B4
playing_demo:       dw ?                                    ; 63B6
is_paused:          dw ?                                    ; 63B8
word_63BA:          dw ?                                    ; 63BA, unpacked data
word_63BC:          dw ?                                    ; 63BC
word_63BE:          dw ?                                    ; 63BE
dat_file_handle:    dw ?                                    ; 63C0
arr_63C2:           rw 512                                  ; 63C2
arr_67C2:           rw 128                                  ; 67C2
arr_68C2:           rw 128                                  ; 68C2
arr_69C2:           rw 128                                  ; 69C2
arr_6AC2:           rw 128                                  ; 6AC2
arr_6BC2:           rw 257                                  ; 6BC2
arr_6DC4:           rw 201                                  ; 6DC4
arr_6F56:           rb 256 * 3                              ; 6F56
palette2:           rb 256 * 3                              ; 7256
palette:            rb 256 * 3                              ; 7556
arr_7856:           rb 2304                                 ; 7856
tmp_file_buf:       rb 256                                  ; 8156
arr_8256:           rb 258                                  ; 8256
arr_8358:           rb 1704                                 ; 8358
                    rb 14166                                ; 8A00
arr_C156:           rb 1034                                 ; C156
arr_C560:           rb 8                                    ; C560
arr_C568:           rw 512                                  ; C568
; TODO: C968
