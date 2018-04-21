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
    int r3; //result of op
} entry;

/* INSERT WHATEVER YOU NEED FOR THE VALUE NUMBER HASH FUNCTION */
int hash(char, int, int);
void InitVarHash();
void addEntry(char op, int r1, int r2, int r3, int offset);
entry* lookupR(char op, int r1, int r2);
int modifyVar(int r1, int r2);
entry *findVar(int r1, int r2);
void deleteEntries(int r1);
#endif
