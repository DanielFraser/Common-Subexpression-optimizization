/**********************************************
        CS415  Project 3
        Spring  2018
        Student Version
**********************************************/

#ifndef VALNUM_H
#define VALNUM_H

#include <string.h>

typedef struct {
    char op; //+,-,*,v,c
    int r1; //var reg unless op exists
    int r2; //offset unless op exists
    int r3; //result of op
} entry;

typedef struct A {
    int reg; //+,-,*,v,c
    struct A *next;
} node;

/* INSERT WHATEVER YOU NEED FOR THE VALUE NUMBER HASH FUNCTION */
int hash(char, int, int);

void InitVarHash();

void addEntry(char, int, int, int);

entry *lookupR(char, int, int);

int modifyVar(int, int);

entry *findVar(int);

void deleteEntries(int);

void addVar(int, int);

#endif
