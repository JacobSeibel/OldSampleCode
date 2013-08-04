/*
 * main.c
 *
 * Created: 3/21/2013 11:23:58 AM
 *  Author: efb
 */ 

#include <avr/io.h>
#include "Kernel.h"

//--------------------------------
// Thread prototypes
//--------------------------------
void thread0(void);
void thread1(void);
void thread2(void);
void thread3(void);

//------------------------------------------------------------------------------
// Function: main
//
// Description: Initializes Kernel then creates 4 threads where each blinks
//              a different LED at its own rate. The last thread created
//              (thread 0) replaces 'main'.
//
//   Threads use the following resources:
//
//   thread0 - PORTB bit 2  (Arduino pin 10)
//   thread1 - PORTB bit 3  (Arduino pin 11)
//   thread2 - PORTB bit 4  (Arduino pin 12)
//   thread3 - PORTB bit 5  (Arduino pin 13)
// 
//------------------------------------------------------------------------------
int main(void)
{
	//DDRB |= 0x04;
	//PORTB ^= 0x04;
	
	
	k_init();
	k_new(T3_ID, (THREADPTR)thread3, 0);
	k_new(T2_ID, (THREADPTR)thread2, 0);
	k_new(T1_ID, (THREADPTR)thread1, 0);
	k_new(T0_ID, (THREADPTR)thread0, 0);  // This replaces 'main' 
	
	while(1);  // should not get here at all

}

//
// Uncomment the following #define if you want to use the Simulator because k_delay takes too long in simulation.
// Just make sure to comment out again if you download to real hardware otherwise your LEDs will
// look like they are always ON.
//
//  #define k_delay k_next
//

void thread0() {
	DDRB |= 0x04;  // set PB.2 for OUTPUT
	while(1)
	{
		PORTB ^= 0x04;
		//k_next();
		k_delay(1);
	}
}
void thread1() {
	DDRB |= 0x08;  // set PB.3 for OUTPUT
	while(1)
	{
		PORTB ^= 0x08;
		//k_next();
		k_delay(1);
	}
}
void thread2() {
	DDRB |= 0x10;  // set PB.4 for OUTPUT
	while(1)
	{
		PORTB ^= 0x10;
		//k_next();
		k_delay(1);
	}
}
void thread3() {
	DDRB |= 0x20;  // set PB.5 for OUTPUT
	while(1)
	{
		PORTB ^= 0x20;
		//k_next();
		k_delay(1);
	}
}