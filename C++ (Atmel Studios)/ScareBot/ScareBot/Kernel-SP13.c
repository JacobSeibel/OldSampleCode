/*
 * Kernel_SP13.c
 *
 * Created: 3/21/2013 11:20:51 AM
 *  Author: W7F10S11
 */

#include <avr/io.h>
#include <util/atomic.h>
#include "Kernel-SP13.h"


//--------------------------------------
//   Stack control
//--------------------------------------
STACKCONTROL stacks[MAX_THREADS];

//--------------------------------------
//   Allocate Thread Delay Counters
//--------------------------------------
volatile unsigned int k_thread_delay[MAX_THREADS];  // NOTE that these are UNSIGNED to allow for up to 65535 tick delays

//--------------------------------------
//   Allocate Thread Status Variables
//--------------------------------------
unsigned long k_longtime;	// system tick counter
byte k_thread_id;			// ID of running thread
byte k_thread_mask;			// Mask corresponding to running thread
byte k_disable_status;
byte k_suspend_status;
volatile byte k_delay_status;
byte k_mbox_status;

//--------------------------------------
//   Allocate Thread Stacks
//--------------------------------------
byte thread_stacks[STACKS_MEMORY_SIZE];

//--------------------------------------
//   Local functions
//--------------------------------------
static void initSystemTimer(void);


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
    k_disable_status = 0xFE;
    k_suspend_status = 0;
    k_delay_status = 0;
    k_thread_id = 0;
    k_thread_mask = 0x01;

    // Save calling function's return address on thread 0 stack
    // (The calling function becomes "Thread 0" when k_init() returns)
	byte *pReturn = (byte *)SP;
	*stacks[0].ps-- = pReturn[4];  // ret addr low
	*stacks[0].ps-- = pReturn[3];    // ret addr high
 // NOTE: The following two lines were necessary on my system because code generated 
 //       for k_init() pushed r28 and r29 on the stack on entry to the function. This
 //       was not done on prior versions of the kernel and dev tools.
	*stacks[0].ps-- = pReturn[2];    // r28 
	*stacks[0].ps-- = pReturn[1];    // r29
	
	// Update SP register so that when this function returns it will point to thread 0 stack base...
	// and calling function will resume as if normal call-return sequence.
	SP = (int)(stacks[0].ps);

	// initialize system timer
	initSystemTimer();

	// enable interrupts
    sei();

}

/*--------------------------------------------------------------------------------------
   Function:       k_new

   Description:    Creates a new thread by associating a function pointer with a 
                   specified thread ID and stack. The thread may be created in 
                   either an enabled or disabled state as specified by the isEnabled
                   parameter. A thread may replace itself by another thread (or restart itself) by
                   specifying its own ID for this function. If ID ofthe calling thread is specified
                   then this function does not return to the caller but jumps to the kernel scheduler. 
                   In this case the new (replacement) thread will be scheduled according to its
                   status.

   Input:          int tid - the ID of the thread to be created/replaced (a number between 0 and 7)
                   PTHREAD pthread - a pointer to a function (PTHREAD type - see kernel.h)
                   byte isEnabled - 1=thread initially enabled, 0=thread initially disabled.

   Returns:        none
   

---------------------------------------------------------------------------------------*/

void k_new(byte tid, PTHREAD pthread, byte isEnabled)
{
   PTU u; //a union that gives access to a thread pointer a byte at a time
     
   // Get stack base pointer for this thread ID
   byte *psb = stacks[tid].pbase;
   

   // Copy return address of thread onto its stack
   u.pthread = pthread;
   *psb-- = u.addr[0];
   *psb-- = u.addr[1];
   psb -= THREAD_CONTEXT_SIZE;


   // Save new stack pointer in this thread's stack pointer save area.
   // If the current thread is being replaced, this new stack pointer
   // will take effect after rescheduling (below)
   stacks[tid].ps = psb;

   byte tmask = bit2mask8(tid);
   if(isEnabled){
      k_disable_status &= ~tmask;
   }
   else {
      k_disable_status |= tmask;
   }
   
   //-------------------------------------------------------------------
   // If this is not the current thread just return to calling thread   
   //-------------------------------------------------------------------
   if(tid != k_getTID()){
      return;      
   }
   
   //-------------------------------------------------------------------
   // If the calling thread is being replaced/reinitialized
   // then go to rescheduling loop. 
   // NOTE: A call is OK here--modifying the stack below where
   // it has just been initialized 
   //-------------------------------------------------------------------
   k_schedule();
   
}



/*-------------------------------------------------------------------------------------
	Function: initSystemTimer
	
	Description:

--------------------------------------------------------------------------------------*/

static void initSystemTimer()
{
	TCNT0 = 0;
	OCR0A = 250;     //Set compare match count to 125 (2 msec tick)
	TIMSK0 = _BV(OCIE0A);             // Enable Timer0 Compare-Match interrupt
	//At 16MHz this gives 250 count for 1 msec interval
	TCCR0A = 0x02;	// CTC mode
	TCCR0B = 0x03;   // fclk/64  (16MHz/256 is input clock)
}

/*--------------------------------------------------------------------------------------
   Function:       k_delay

   Description:    Delays the calling thread by the specified number of system "ticks" 
                   by loading the thread's delay value and setting its delay status bit
                   to '1'. The kernel timer decrements the delay values each system tick
                   tick and clears the delay status bits of any that reach zero.
   

   Input:          none

   Returns:        Does not return, but enters scheduling loop.
   

---------------------------------------------------------------------------------------*/
void k_delay(int ticks)
{
   ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
   {
      k_thread_delay[k_getTID()] = ticks;
      k_delay_status |= k_thread_mask;
   }
   k_next();
}

/*--------------------------------------------------------------------------------------
   Function:       k_gtime

   Description:    Returns current value of the 'k_longtime' system tick counter.
                   Access to the system tick counter must be atomic since it involves
                   reading a multi-byte value that is written by an interrupt handler.
                   The k_longtime counter is incremented each system tick. The 32-bit
                   counter will overflow after (2**32) * (tick_period) seconds. For 
                   example, if the tick interval is 1msec, then it will overflow in
                   about 49 days. Ifthis kind of overflow will affect thread timing,
                   it is the responsibility of each thread to check the value returned
                   to make sure that if overflow occurs, the timing of the thread 
                   does not cause a failure.

   Input:          none
                  

   Returns:        long time - a copy of the system tick counter (32 bits)
   

---------------------------------------------------------------------------------------*/
unsigned long k_gtime(){
   long val;
   ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
      val = k_longtime;
   }
   return val;
}
/*--------------------------------------------------------------------------------------
   Interrupt Service Routine:   TIMER0_COMP_vect


   Description: This interrupt is triggered every 1 msec based on TIMER0 COMPARE MATCH.
                The ISR decrements the first NUM_THREADS delay values and resets 
                (to zero) the k_delay_status bits if each thread whose counter reaches
                zero. If a thread is delayed and its counter reaches zero, then it
                is made READY and may be scheduled to run.

----------------------------------------------------------------------------------------*/
ISR(TIMER0_COMPA_vect)
{

   // Increment system counter
   k_longtime++;

   char msk = 0x01;  // start with thread 0

   unsigned int *pdelay = k_thread_delay;
   //decrement delays
   for(char i = 0; i < NUM_THREADS; i++){
      (*pdelay)--;
      if(*pdelay == 0){
         k_delay_status &= ~msk;
      }
      msk <<= 1;
      pdelay++;
   }
   
}

