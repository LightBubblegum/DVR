                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.8.0 #10562 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module main
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main
                                     12 	.globl _assert_failed
                                     13 ;--------------------------------------------------------
                                     14 ; ram data
                                     15 ;--------------------------------------------------------
                                     16 	.area DATA
                                     17 ;--------------------------------------------------------
                                     18 ; ram data
                                     19 ;--------------------------------------------------------
                                     20 	.area INITIALIZED
                                     21 ;--------------------------------------------------------
                                     22 ; Stack segment in internal ram 
                                     23 ;--------------------------------------------------------
                                     24 	.area	SSEG
      FFFFFF                         25 __start__stack:
      FFFFFF                         26 	.ds	1
                                     27 
                                     28 ;--------------------------------------------------------
                                     29 ; absolute external ram data
                                     30 ;--------------------------------------------------------
                                     31 	.area DABS (ABS)
                                     32 
                                     33 ; default segment ordering for linker
                                     34 	.area HOME
                                     35 	.area GSINIT
                                     36 	.area GSFINAL
                                     37 	.area CONST
                                     38 	.area INITIALIZER
                                     39 	.area CODE
                                     40 
                                     41 ;--------------------------------------------------------
                                     42 ; interrupt vector 
                                     43 ;--------------------------------------------------------
                                     44 	.area HOME
      008000                         45 __interrupt_vect:
      008000 82 00 80 07             46 	int s_GSINIT ; reset
                                     47 ;--------------------------------------------------------
                                     48 ; global & static initialisations
                                     49 ;--------------------------------------------------------
                                     50 	.area HOME
                                     51 	.area GSINIT
                                     52 	.area GSFINAL
                                     53 	.area GSINIT
      008007                         54 __sdcc_gs_init_startup:
      008007                         55 __sdcc_init_data:
                                     56 ; stm8_genXINIT() start
      008007 AE 00 00         [ 2]   57 	ldw x, #l_DATA
      00800A 27 07            [ 1]   58 	jreq	00002$
      00800C                         59 00001$:
      00800C 72 4F 00 00      [ 1]   60 	clr (s_DATA - 1, x)
      008010 5A               [ 2]   61 	decw x
      008011 26 F9            [ 1]   62 	jrne	00001$
      008013                         63 00002$:
      008013 AE 00 00         [ 2]   64 	ldw	x, #l_INITIALIZER
      008016 27 09            [ 1]   65 	jreq	00004$
      008018                         66 00003$:
      008018 D6 80 23         [ 1]   67 	ld	a, (s_INITIALIZER - 1, x)
      00801B D7 00 00         [ 1]   68 	ld	(s_INITIALIZED - 1, x), a
      00801E 5A               [ 2]   69 	decw	x
      00801F 26 F7            [ 1]   70 	jrne	00003$
      008021                         71 00004$:
                                     72 ; stm8_genXINIT() end
                                     73 	.area GSFINAL
      008021 CC 80 04         [ 2]   74 	jp	__sdcc_program_startup
                                     75 ;--------------------------------------------------------
                                     76 ; Home
                                     77 ;--------------------------------------------------------
                                     78 	.area HOME
                                     79 	.area HOME
      008004                         80 __sdcc_program_startup:
      008004 CC 80 24         [ 2]   81 	jp	_main
                                     82 ;	return from main will return to caller
                                     83 ;--------------------------------------------------------
                                     84 ; code
                                     85 ;--------------------------------------------------------
                                     86 	.area CODE
                                     87 ;	main.c: 36: void main(void)
                                     88 ;	-----------------------------------------
                                     89 ;	 function main
                                     90 ;	-----------------------------------------
      008024                         91 _main:
                                     92 ;	main.c: 39: while (1)
      008024                         93 00102$:
      008024 20 FE            [ 2]   94 	jra	00102$
                                     95 ;	main.c: 43: }
      008026 81               [ 4]   96 	ret
                                     97 ;	main.c: 54: void assert_failed(u8* file, u32 line)
                                     98 ;	-----------------------------------------
                                     99 ;	 function assert_failed
                                    100 ;	-----------------------------------------
      008027                        101 _assert_failed:
                                    102 ;	main.c: 60: while (1)
      008027                        103 00102$:
      008027 20 FE            [ 2]  104 	jra	00102$
                                    105 ;	main.c: 63: }
      008029 81               [ 4]  106 	ret
                                    107 	.area CODE
                                    108 	.area CONST
                                    109 	.area INITIALIZER
                                    110 	.area CABS (ABS)
