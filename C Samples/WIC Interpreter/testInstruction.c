#include "instructions.h"
#include "testInstruction.h"
#include <stdio.h>
#include <string.h>

void testInstruction(){

    printf("Initializing instruction table...\n");
    initialize();
    printf("Inserting nop instruction at address 0...\n");
    insertInstruction(0, "nop", "");
    printf("Using fetchOpcode at address 0...\n");
    if(strcmp(fetchOpcode(0), "nop") != 0){
        printf("Failure!  The nop instruction was not fetched!\n");
    }
    else{
        printf("Success!  The nop instruction was fetched!\n");
    }

    printf("Inserting 'pop A' instruction at address 1...\n");
    insertInstruction(1, "pop", "A");
    printf("Fetching operand at address 1...\n");
    if(strcmp(fetchOperand(1), "A") !=0){
        printf("Failure!  The operand 'A' was not fetched.\n");
    }
    else{
        printf("Success!  The operand 'A' was fetched!\n");
    }
    printf("Attempting to insert a nop at an invalid address...\n");
    insertInstruction(-1, "nop", "");
    
    printf("\nAll tests concluded.\n");
}
