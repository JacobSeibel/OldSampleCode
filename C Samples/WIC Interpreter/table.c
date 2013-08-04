#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void store(tableType *Xtable, char *key, int val){
    int i;
    tableEntry *currentEntry;
    for(i = 0; i <= Xtable->numElements; i++){
        if(Xtable->numElements == TABLE_SIZE){
            printf("The symbol table is full!\n");
            break;
        }
        currentEntry = &(Xtable->entry[i]);
        //If the key is already in the table, just change val
        if(strcmp(key, currentEntry->key) == 0){
            currentEntry->value = val;
        }
        //If the first empty member of the table is reached, add here.
        if(i == Xtable->numElements){
            currentEntry->value = val;
            strcpy(currentEntry->key, key);
            Xtable->numElements++;
            break;
        }
    }
}

int retrieve(tableType *Xtable, char *key){
    int i;
    tableEntry *currentEntry;
    for(i = 0; i <=Xtable->numElements; i++){
        currentEntry = &(Xtable->entry[i]);
        //If the key is a match to one in the table, return value
        if(strcmp(key, (char*)currentEntry->key) == 0){
            return currentEntry->value;
        }
    }
    printf("It appears this key does not exist in the table!\n");
    return -999;
}

void initializeTable(tableType *Xtable){
    Xtable->numElements = 0;
}
