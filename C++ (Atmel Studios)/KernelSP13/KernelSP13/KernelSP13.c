/*
 * Kernel_SP13.c
 *
 * Created: 3/21/2013 11:20:51 AM
 *  Author: W7F10S11
 */


#include <avr/io.h>
#include <util/atomic.h>
#include "Kernel.h"


//--------------------------------------
//   Stack control
//--------------------------------------
STACKCONTROL stacks[MAX_THREADS];

//--------------------------------------
//   Allocate Thread Delay Counters
//--------------------------------------
volatile unsigned int k_thread_delay[MAX_THREADS];

//--------------------------------------
//   Allocate Thread Status Variables
//--------------------------------------
volatile byte k_thread_id = 0xff;   // ID of running thread
byte k_thread_mask = 0;  // Mask corresponding to running thread
byte k_disable_status = 0;
byte k_suspend_status = 0;
volatile byte k_delay_status = 0x01;

//--------------------------------------
//   Allocate Thread Stacks
//--------------------------------------
byte thread_stacks[STACKS_MEMORY_SIZE];

//--------------------------------------
//   Local functions
//--------------------------------------
static void init_System_Timer();


/*----------------------------------------------------------------
	k_init

-----------------------------------------------------------------*/
void k_init()
{
    // disable interrupts
    cli();


	// initialize thread stack pointers
	stacks[T0_ID].pbase = thread_stacks+T0_STACKOFFSET;
	stacks[T0_ID].ps = thread_stacks+T0_STACKOFFSET;
	stacks[T1_ID].pbase = thread_stacks+T1_STACKOFFSET;
	stacks[T1_ID].ps = thread_stacks+T1_STACKOFFSET;
	stacks[T2_ID].pbase = thread_stacks+T2_STACKOFFSET;
	stacks[T2_ID].ps = thread_stacks+T2_STACKOFFSET;
	stacks[T3_ID].pbase = thread_stacks+T3_STACKOFFSET;
	stacks[T3_ID].ps = thread_stacks+T3_STACKOFFSET;
	stacks[T4_ID].pbase = thread_stacks+T4_STACKOFFSET;
	stacks[T4_ID].ps = thread_stacks+T4_STACKOFFSET;
	stacks[T5_ID].pbase = thread_stacks+T5_STACKOFFSET;
	stacks[T5_ID].ps = thread_stacks+T5_STACKOFFSET;
	stacks[T6_ID].pbase = thread_stacks+T6_STACKOFFSET;
	stacks[T6_ID].ps = thread_stacks+T6_STACKOFFSET;
	stacks[T7_ID].pbase = thread_stacks+T7_STACKOFFSET;
	stacks[T7_ID].ps = thread_stacks+T7_STACKOFFSET;

	// initialize thread status variables
    k_disable_status = 0xFF;
    k_suspend_status = 0;
    k_delay_status = 0;
    k_thread_id = 0;
    k_thread_mask = 0x01;

    // Save calling function's return address on thread 0 stack
    // (The calling function becomes "Thread 0" when k_init() returns)
    byte * stackptr = (byte *) (SP);
	byte topReturn = *++stackptr;
	byte bottomReturn = *++stackptr;
	
	*stacks[T0_ID].ps = bottomReturn;
	stacks[T0_ID].ps--;
	*stacks[T0_ID].ps = topReturn;
	stacks[T0_ID].ps--;
	
	SP = (uint16_t) stacks[T0_ID].ps;

	// initialize system timer
	init_System_Timer();

	// enable interrupts
    sei();

}
static void init_System_Timer()
{
	// 125*256/16000000 = 2ms
	TCCR0A = 0x2;	//Compare with OCR0A
	OCR0A = 0xFA;	//OCR0A is set with 125
	TCCR0B |= 0x03;	//Prescaler divides by 256
	TIMSK0 |= 0x02;	//Enable OCR0A interrupt
	
}

void k_new(byte threadID, THREADPTR newthread, byte beginDisabled){
	//Local pointer to top of stack
	byte * stackTop = stacks[threadID].pbase;
	
	//Put the function pointer on the thread's stack
	stackTop[0] = newthread.ptr[0];
	stackTop[-1] = newthread.ptr[1];
	
	//Set the threads stack pointer to make room for all the registers
	stacks[threadID].ps = &(stacks[threadID].pbase[-20]);
	
	//If beginDisabled is true, set disable bit for thread to 1
	//Else, set disable bit for thread to 0
	if(beginDisabled){
		k_disable_status |= 1 << threadID;
	}
	else{
		k_disable_status &= ~(1 << threadID);
	}
	
	//Not suspended or delayed
	k_suspend_status &= ~(1 << threadID);
	k_delay_status &= ~(1 << threadID);
	
	if(k_thread_id == threadID){
		k_schedule();
	}
}

void k_delay(unsigned int delay){
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		k_delay_status = k_delay_status | bit2mask(k_thread_id);
		k_thread_delay[k_thread_id] = delay;
	}	
	k_next();
}

ISR(TIMER0_COMPA_vect){
	int i = 0;
	for(i = 0; i < MAX_THREADS; i++){
		//If the thread delay is greater than 0, decrement
		if(k_thread_delay[i] > 0){
			k_thread_delay[i]--;
		}
		//If the thread delay is 0, reset delay status for that thread to 0
		else{
			k_delay_status = k_delay_status & !bit2mask(i);
		}
	}
}