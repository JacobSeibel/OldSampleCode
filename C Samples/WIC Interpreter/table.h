/*
 * table.h
 *
 *  Created on: Aug 11, 2011
 *      Author: Cory
 */

#ifndef TABLE_H_
#define TABLE_H_

#define TABLE_SIZE 100
//Define the structs used for the tables.
//table entries
typedef struct{
    char key[20];
    int value;
}tableEntry;

//table contains entries and the number of elements
typedef struct {
    tableEntry entry[TABLE_SIZE];
    int numElements;
} tableType;

//Function prototypes.
void store(tableType *Xtable, char *key, int val);
int retrieve(tableType *Xtable, char *key);
void initializeTable(tableType *Xtable);

#endif /* TABLE_H_ */
