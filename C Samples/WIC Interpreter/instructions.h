/*
 * instructions.h
 *
 *  Created on: Aug 11, 2011
 *      Author: Cory
 */

#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

//used in instruction.c and main
#define OPCODE_SIZE 5 
#define OPERAND_SIZE 20
#define ITABLE_SIZE 40

//Define the structs used for the instructionTable
//instruction
typedef struct{
    char opcode[OPCODE_SIZE];
    char operand[OPERAND_SIZE];
} instruction;

//instructionTable
typedef struct{
    instruction instructions[ITABLE_SIZE];
    int currentSize;
} instructionTable;

int hasOperand(char * opcode);
void insertInstruction(int address, char * opcode, char * operand);
char * fetchOpcode(int address);
char * fetchOperand(int address);
void initialize();
static instructionTable iTable;

//Function prototypes.
int nop(int);
int add(int);
int sub(int);
int mult(int);
int divide(int); //Evidently there is already a "div" function in the standard library.
int get(int);
int put(int);
int push(int);
int pop(int);
int not(int);
int and(int);
int or(int);
int testeq(int);
int testne(int);
int testlt(int);
int testle(int);
int testgt(int);
int testge(int);
int jump(int);
int jf(int);
int halt(int);

#endif /* INSTRUCTIONS_H_ */
