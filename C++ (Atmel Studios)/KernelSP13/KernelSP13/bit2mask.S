
/*
 * bit2maskASM.s
 *
 *  Author: Jacob Seibel
 */ 
 #define __SFR_OFFSET 0
 #include <avr/io.h>

		.section .text
		.global bit2mask
bit2mask:

		clr r0
		tst r24
		breq isZero
		inc r0
begin:
		tst r24
		breq finish
		lsl r0
		dec r24
		jmp begin
		
isZero:
		inc r0
		
finish:
		clr r24
		add r24, r0
		ret
	

