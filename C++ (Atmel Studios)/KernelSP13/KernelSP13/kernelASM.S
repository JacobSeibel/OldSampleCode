
/*
 * kernelASM.s
 *
 * Created: 4/11/2013 10:59:47 AM
 *  Author: Jacob Seibel
 */ 

 #define __SFR_OFFSET 0
 #include <avr/io.h>

	.section	.text
	.global k_next
	.global save
	.global k_schedule
	.global restore

	.extern stacks
	.extern k_thread_id
	.extern k_thread_mask
	.extern k_disable_status
	.extern k_suspend_status
	.extern k_delay_status

k_next:

save:
	//Callee save stuff
	push r2
	push r3
	push r4
	push r5
	push r6
	push r7
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	push r16
	push r17
	push r28
	push r29

	//Save calling thread's stack pointer
	ldi r30, lo8(stacks)
	ldi r31, hi8(stacks)
	
	//k_thread_id * 4
	lds r16, k_thread_id
	lsl r16
	lsl r16

	//stack + ^^^^
	add r30, r16
	adc r31, r1

	//store SP
	cli
	in r18, SPL
	in r19, SPH
	sei
	st Z+, r18
	st Z, r19

k_schedule:
	//Determine next thread to execute
	lds r16, k_disable_status
	lds r17, k_suspend_status
	lds r18, k_delay_status
	or r16, r17
	or r16, r18 //Or of all status bytes

scan:
	lds r24, k_thread_id // for mask
	lds r23, k_thread_id // for next id
	call bit2mask
	clc //clears carry flag
checkNext:
	rol r24
	brcc nowrap
	rol r24
	ldi r23, -1
nowrap:
	inc r23 //the next thread's id
	and r24, r16
	brne checkNext
	lds r20, k_thread_id
	sub r20, r23
	brie k_schedule

	//Store next thread's id
	sts k_thread_id, r23

	//Retrieve next thread's stack pointer, update
	ldi r30, lo8(stacks)
	ldi r31, hi8(stacks)

	//new thread id * 4 + 2
	mov r16, r23
	lsl r16
	lsl r16

	//stack + ^^^^^
	add r30, r16
	adc r31, r1

	//load next stack pointer
	ld r18, Z+
	ld r19, Z
	
	cli
	out SPL, r18
	out SPH, r19
	sei

restore:
	//Restore next thread's state from its stack
	

	//restore registers
	pop r29
	pop r28
	pop r17
	pop r16
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop r7
	pop r6
	pop r5
	pop r4
	pop r3
	pop r2

	//return to next thread
	ret
