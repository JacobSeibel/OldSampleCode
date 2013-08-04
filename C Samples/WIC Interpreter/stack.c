//
// stack.c - By Jacob Seibel
// (C) 2012
//

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void initializeStack(Stack* s){
    s->size = 0;
    //"clear" stack by setting size to 0
}

void stackPush(Stack *s, int x){
    if(s->size == STACK_SIZE){
        printf("Error: Don't push to full stack!\n");
        exit(0);
    }
    else{
        s->items[s->size++] = x;
    }
}

int stackPop(Stack *s){
    if(s->size == 0){
        printf("Error: Don't pull from empty stack!\n");
        exit(0);
    }
    else{
        return s->items[--s->size];
    }
}

