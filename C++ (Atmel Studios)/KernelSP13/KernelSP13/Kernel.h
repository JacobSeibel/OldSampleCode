/*
 * Kernel_SP13.h
 *
 * Created: 3/21/2013 11:23:19 AM
 *  Author: efb
 */


#ifndef KERNEL_SP13_H_
#define KERNEL_SP13_H_

typedef	unsigned char byte;


#define MAX_THREADS		8
#define T0_STACKSIZE	128
#define T1_STACKSIZE	128
#define T2_STACKSIZE	128
#define T3_STACKSIZE	128
#define T4_STACKSIZE	128
#define T5_STACKSIZE	128
#define T6_STACKSIZE	128
#define T7_STACKSIZE	128


#define STACKS_MEMORY_SIZE   (T0_STACKSIZE+T1_STACKSIZE+T2_STACKSIZE+T3_STACKSIZE+\
						T4_STACKSIZE+T5_STACKSIZE+T6_STACKSIZE+T7_STACKSIZE)

#define T0_STACKOFFSET	(T0_STACKSIZE-1)
#define T1_STACKOFFSET	(T0_STACKOFFSET+T1_STACKSIZE)
#define T2_STACKOFFSET	(T1_STACKOFFSET+T2_STACKSIZE)
#define T3_STACKOFFSET	(T2_STACKOFFSET+T3_STACKSIZE)
#define T4_STACKOFFSET	(T3_STACKOFFSET+T4_STACKSIZE)
#define T5_STACKOFFSET	(T4_STACKOFFSET+T5_STACKSIZE)
#define T6_STACKOFFSET	(T5_STACKOFFSET+T6_STACKSIZE)
#define T7_STACKOFFSET	(T6_STACKOFFSET+T7_STACKSIZE)



#define T0_ID	0
#define T1_ID	1
#define T2_ID	2
#define T3_ID	3
#define T4_ID	4
#define T5_ID	5
#define T6_ID	6
#define T7_ID	7

// Stuff below this line is for C compilation only

#ifndef __ASSEMBLER__

typedef struct {
	byte *ps;
	byte *pbase;
} STACKCONTROL;

typedef union {
	void (*pthread)(void);
	byte ptr[2];
} THREADPTR;


//------------------------------------------
// Kernel Function Prototypes
//------------------------------------------
void k_init(void);
void k_new(byte threadID, THREADPTR newthread, byte beginDisabled);
void k_next(void);
byte bit2mask(byte bitnum);
void k_delay(unsigned int delay);
#endif // not __ASSEMBLER__

#endif /* KERNEL_SP13_H_ */
