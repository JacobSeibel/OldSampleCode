#include "table.h"
#include <stdio.h>
#include "testTable.h"

void testTable(){
    printf("Creating symbol table...\n");
    tableType Xtable;
    printf("Initializing symbol table...\n");
    initializeTable(&Xtable);
    printf("Retrieving from empty symbol table...\n");
    int test = retrieve(&Xtable, "test");
    if(test == -999){
        printf("Success!  Error thrown!\n");
    }
    else{
        printf("Failure!  Retrieved %d instead of -999.\n", test);
    }
    printf("Storing to empty symbol table...\n");
    store(&Xtable, "test", 1337);
    printf("Retrieving value with key 'test'...\n");
    test = retrieve(&Xtable, "test");
    if(test == 1337){
        printf("Success!  1337 retrieved!\n");
    }
    else{
        printf("Failure!  Retrieved %d instead of 1337!\n", test);
    }
    printf("Storing to occupied symbol table, new key...\n");
    store(&Xtable, "test2", 1234);
    printf("Retrieving value with key 'test2'...\n");
    test = retrieve(&Xtable, "test2");
    if(test == 1234){
        printf("Success!  1234 retrieved!\n");
    }
    else{
        printf("Failure!  Retrieved %d instead of 1234!\n", test);
    }
    printf("Storing to used key...\n");
    store(&Xtable, "test", 4321);
    printf("Retrieving new value with key 'test'...\n");
    test = retrieve(&Xtable, "test");
    if(test == 4321){
        printf("Success!  4321 retrieved!\n");
    }
    else{
        printf("Failure!  Retrieved %d instead of 4321!\n", test);
    }
    printf("Retrieving value with a key that doesn't exist...\n");
    test = retrieve(&Xtable, "blah");
    if(test == -999){
        printf("Success!  Error thrown!\n");
    }
    else{
        printf("Failure!  Retrieved %d instead of -999.", test);
    }
    printf("Filling symbol table...\n");
    store(&Xtable, "test3", 3);
    store(&Xtable, "test4", 4);
    store(&Xtable, "test5", 5);
    store(&Xtable, "test6", 6);
    store(&Xtable, "test7", 7);
    store(&Xtable, "test8", 8);
    store(&Xtable, "test9", 9);
    store(&Xtable, "test10", 10);
    store(&Xtable, "test11", 11);
    store(&Xtable, "test12", 12);
    store(&Xtable, "test13", 13);
    store(&Xtable, "test14", 14);
    store(&Xtable, "test15", 15);
    store(&Xtable, "test16", 16);
    store(&Xtable, "test17", 17);
    store(&Xtable, "test18", 18);
    store(&Xtable, "test19", 19);
    printf("Attempting to overfill symbol table...\n");
    store(&Xtable, "test20", 20);
    printf("Success!  Error thrown!\n");
    printf("\nAll tests complete!\n");

}
