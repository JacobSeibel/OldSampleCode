#include "instructions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "stack.h"
#include <ctype.h>

static Stack stack;
static tableType table;

int hasOperand(char *opcode){
    if((strcmp(opcode, "get")) == 0 || (strcmp(opcode, "put")) == 0 ||
       (strcmp(opcode, "push")) == 0 || (strcmp(opcode, "pop")) == 0 ||
       (strcmp(opcode, "j")) == 0 || (strcmp(opcode, "jf")) == 0 || 
       (strcmp(opcode, "label")) == 0){
        return 1;
    }
    return 0;
}

void insertInstruction(int address, char *opcode, char *operand){
    if(address > ITABLE_SIZE || address < 0){
        printf("Invalid address.  The address is not contained in the table.\n");
        exit(0);
    }
    
    iTable.currentSize++;
    if(strcmp(opcode, "label") == 0){
        store(&table, operand, address);
        strcpy(iTable.instructions[address].opcode, "nop");
    }
    else{
        strcpy(iTable.instructions[address].opcode, opcode);
    }
    strcpy(iTable.instructions[address].operand, operand);
}

char * fetchOpcode(int address){
    if(address > iTable.currentSize || address < 0){
        printf("Invalid address.  The address is not contained in the table.");
        exit(0);
    }
    
    return iTable.instructions[address].opcode;
}

char * fetchOperand(int address){
    if(address > iTable.currentSize || address < 0){
        printf("Invalid address.  The address is not contained in the table.");
        exit(0);
    }
    
    return iTable.instructions[address].operand;
}

void initialize(){
    iTable.currentSize = 0;
    initializeTable(&table);
    initializeStack(&stack);
}

//OPCODE IMPLEMENTATIONS:

int pop(int pc){
    char * operand = fetchOperand(pc);
    int var = stackPop(&stack);
    store(&table, operand, var);
    return pc + 1;
}

int push(int pc){
    char * operand = fetchOperand(pc);
    if(isdigit(operand[0])){
        stackPush(&stack, atoi(operand));
    }
    else{
        int var = retrieve(&table, operand);
        stackPush(&stack, var);
    }
    return pc + 1;
}

int nop(int pc){
    return pc + 1;
}

int add(int pc){
    int rop = stackPop(&stack);
    int lop = stackPop(&stack);
    stackPush(&stack, lop + rop);
    return pc + 1;
}

int sub(int pc){
    int rop = stackPop(&stack);
    int lop = stackPop(&stack);
    stackPush(&stack, lop - rop);
    return pc + 1;
}

int mult(int pc){
    int rop = stackPop(&stack);
    int lop = stackPop(&stack);
    stackPush(&stack, lop * rop);
    return pc + 1;
}

int divide(int pc){
    int rop = stackPop(&stack);
    int lop = stackPop(&stack);
    if(rop == 0){
        printf("Only Chuck Norris can divide by zero, sorry.\n");
        exit(0);
    }
    stackPush(&stack, lop / rop);
    return pc + 1;
}

int get(int pc){
    char varName[OPERAND_SIZE];
    strcpy(varName, fetchOperand(pc));
    printf("enter %s >  ", varName);
    int var;
    char input[20];
    scanf("%s", input);
    var = atoi(input);
    store(&table, varName, var);
    return pc + 1;
}

int put(int pc){
    char varName[OPERAND_SIZE];
    strcpy(varName, fetchOperand(pc));
    int var = retrieve(&table, varName);
    printf("%d\n", var);
    return pc + 1;
}

int not(int pc){
    int var = stackPop(&stack);
    stackPush(&stack, !var);
    return pc + 1;
}

int and(int pc){
    int rop = stackPop(&stack);
    int lop = stackPop(&stack);
    stackPush(&stack, lop && rop);
    return pc + 1;
}

int or(int pc){
    int rop = stackPop(&stack);
    int lop = stackPop(&stack);
    stackPush(&stack, lop || rop);
    return pc + 1;
}

int testeq(int pc){
    int var = stackPop(&stack);
    if(var == 0)
        stackPush(&stack, 1);
    else
        stackPush(&stack, 0);
    return pc + 1;
}

int testne(int pc){
    int var = stackPop(&stack);
    if(var != 0)
        stackPush(&stack, 1);
    else
        stackPush(&stack, 0);
    return pc + 1;
}

int testlt(int pc){
    int var = stackPop(&stack);
    if(var < 0)
        stackPush(&stack, 1);
    else
        stackPush(&stack, 0);
    return pc + 1;
}

int testle(int pc){
    int var = stackPop(&stack);
    if(var <= 0)
        stackPush(&stack, 1);
    else
        stackPush(&stack, 0);
    return pc + 1;
}

int testgt(int pc){
    int var = stackPop(&stack);
    if(var > 0)
        stackPush(&stack, 1);
    else
        stackPush(&stack, 0);
    return pc + 1;
}

int testge(int pc){
    int var = stackPop(&stack);
    if(var >= 0)
        stackPush(&stack, 1);
    else
        stackPush(&stack, 0);
    return pc + 1;
}

int jump(int pc){
    char labelName[OPERAND_SIZE];
    strcpy(labelName, fetchOperand(pc));
    return retrieve(&table, labelName);
}

int jf(int pc){
    char labelName[OPERAND_SIZE];
    strcpy(labelName, fetchOperand(pc));
    int condition = stackPop(&stack);
    if(condition){
        return pc + 1;
    }
    else{
        return retrieve(&table, labelName);
    }
}

int halt(int pc){
    return pc + 1;
}

