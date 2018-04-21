/**********************************************
        CS415  Project 3
        Spring  2018
        Student Version
**********************************************/

#ifndef VALNUM_H
#define VALNUM_H

#include <string.h>

typedef struct {
    char op; //+,-,*,0 - no op
    int r1; //var reg unless op exists
    int r2; //offset unless op exists
} entry;

/* INSERT WHATEVER YOU NEED FOR THE VALUE NUMBER HASH FUNCTION */
int hash(char, int, int);
int findOffset();
void InitVarHash();
void addEntry(char op, int r1, int r2, int offset);
entry* lookupR(char op, int r1, int r2);

#endif
