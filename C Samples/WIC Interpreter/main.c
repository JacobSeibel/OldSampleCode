#include "instructions.h"
#include "stack.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testStack.h"
#include "testTable.h"

void runProgram();

void main(int argc, char *argv[]){

    char *filename = argv[1];
    FILE *fp;

    if(strcmp(filename, "-s") == 0){
        testStack();
        exit(0);
    }
    if(strcmp(filename, "-t") == 0){
        testTable();
        exit(0);
    }
    if(strcmp(filename, "-i") == 0){
        testInstruction();
        exit(0);
    }


    if(argc == 1){
        printf("Proper use: wi <filename.wic>\n");
        exit(0);
    }
    else if((fp = fopen(filename, "r")) == NULL)
    {
        printf("Error opening file.  File doesn't exist.\n");
        exit(0);
    }
    
    initialize();

    char opcode[OPCODE_SIZE];
    char operand[OPERAND_SIZE];
    int address = 0;
    while(fscanf(fp, "%s", opcode) != EOF){
        if(hasOperand(opcode)){
            if(fscanf(fp, "%s", operand) == EOF){
                insertInstruction(address, opcode, operand);
                address++;
                break;
            }
        }
        if(!validOp(opcode)){
            if(fscanf(fp, "%s", operand) != EOF && strcmp(operand, "label") == 0){
                char temp[OPERAND_SIZE];
                strcpy(temp, operand);
                strcpy(operand, opcode);
                strcpy(opcode, temp);
            }
            else{
                printf("Invalid opcode: %s\n", opcode);
                exit(0);
            }
        }
        else if(hasOperand(opcode) == 0){
            strcpy(operand, "");
        }
        insertInstruction(address, opcode, operand);
        address++;
        //discard the rest of the line
        while(fgetc(fp) != '\n'){};
    }
    fclose(fp);

    runProgram();
}

void runProgram(){
    int pc = 0;
    char lastOp[OPCODE_SIZE];
    int haltHit = 0;
    while(!haltHit){
        if(strcmp(fetchOpcode(pc), "nop") == 0){
            pc = nop(pc);
        }
        if(strcmp(fetchOpcode(pc), "add") == 0){
            pc = add(pc);
        }

        if(strcmp(fetchOpcode(pc), "sub") == 0){
            pc = sub(pc);
        }

        if(strcmp(fetchOpcode(pc), "mult") == 0){
            pc = mult(pc);
        }
        if(strcmp(fetchOpcode(pc), "div") == 0){
            pc = divide(pc);
        }
        if(strcmp(fetchOpcode(pc), "get") == 0){
            pc = get(pc);
        }
        if(strcmp(fetchOpcode(pc), "put") == 0){
            pc = put(pc);
        }
        if(strcmp(fetchOpcode(pc), "push") == 0){
            pc = push(pc);
        }
        if(strcmp(fetchOpcode(pc), "pop") == 0){
            pc = pop(pc);
        }
        if(strcmp(fetchOpcode(pc), "not") == 0){
            pc = not(pc);
        }
        if(strcmp(fetchOpcode(pc), "and") == 0){
            pc = and(pc);
        }
        if(strcmp(fetchOpcode(pc), "or") == 0){
            pc = or(pc);
        }
        if(strcmp(fetchOpcode(pc), "tsteq") == 0){
            pc = testeq(pc);
        }
        if(strcmp(fetchOpcode(pc), "tstne") == 0){
            pc = testne(pc);
        }
        if(strcmp(fetchOpcode(pc), "tstlt") == 0){
            pc = testlt(pc);
        }
        if(strcmp(fetchOpcode(pc), "tstle") == 0){
            pc = testle(pc);
        }
        if(strcmp(fetchOpcode(pc), "tstgt") == 0){
            pc = testgt(pc);
        }
        if(strcmp(fetchOpcode(pc), "tstge") == 0){
            pc = testge(pc);
        }
        if(strcmp(fetchOpcode(pc), "j") == 0){
            pc = jump(pc);
        }
        if(strcmp(fetchOpcode(pc), "jf") == 0){
            pc = jf(pc);
        }
        if(strcmp(fetchOpcode(pc), "halt") == 0){
            haltHit = 1;
            pc = halt(pc);
        }
    }
}

int validOp(char opcode[OPCODE_SIZE]){
    if(hasOperand(opcode) || strcmp(opcode, "nop") == 0 || strcmp(opcode, "add")
      == 0 || strcmp(opcode, "sub") == 0 || strcmp(opcode, "mult") == 0 ||
      strcmp(opcode, "div") == 0 || strcmp(opcode, "not") == 0 ||
      strcmp(opcode, "and") == 0 || strcmp(opcode, "or") == 0 ||
      strcmp(opcode, "tsteq") == 0 || strcmp(opcode, "tstne") == 0 ||
      strcmp(opcode, "tstlt") == 0 || strcmp(opcode, "tstle") == 0 ||
      strcmp(opcode, "tstgt") == 0 || strcmp(opcode, "tstge") == 0 ||
      strcmp(opcode, "halt") == 0){
        return 1;
    }
    return 0;
}
