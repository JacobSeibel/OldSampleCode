//The wikipedia array implementation of a stack.
#ifndef STACK_H_
#define STACK_H_

#define STACK_SIZE 20 //20 elements maximum in the stack.

typedef struct{
	int size;
	int items[STACK_SIZE];
} Stack;

//Function prototypes.
void initializeStack(Stack * s);
void stackPush(Stack * s, int x);
int stackPop(Stack * s);

#endif
