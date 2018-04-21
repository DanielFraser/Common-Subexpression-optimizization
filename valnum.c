/**********************************************
        CS415  Project 3
        Spring  2018
        Student Version
**********************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "instrutil.h"
#include "valnum.h"
#include "symtab.h"

#define HASH_TABLE_SIZE 1000

static entry **RegTable;

//Done
int hash(char op, int r1, int r2) {
    int num = 0; //no op gets 1st quarter of array
    switch (op) {
        case '+':
            num = 1 * (HASH_TABLE_SIZE / 4); //gets 2nd
            break;
        case '-':
            num = 2 * (HASH_TABLE_SIZE / 4); //gets 3rd
            break;
        case '*':
            num = 3 * (HASH_TABLE_SIZE / 4); //gets 4th
            break;
    }

    return (((4 * r1) + r2) + num) % HASH_TABLE_SIZE;
}

//Done
//make constants have r2 = -1
void addEntry(char op, int r1, int r2, int r3, int offset) {
    if (op == '0') //we have a var
        r2 = offset;
    if (!lookupR(op, r1, r2)) {
        int hashV = hash(op, r1, r2);
        RegTable[hashV] = (entry *) malloc(sizeof(entry));
        RegTable[hashV]->op = op;
        RegTable[hashV]->r1 = r1;
        RegTable[hashV]->r2 = r2;
        RegTable[hashV]->r3 = r3;
    }
}

//Done
int modifyVar(int r1, int r2) {
    entry* a = findVar(r1, r2);
    if (!a) {
        addEntry('0', r1, r2, r2, r2);
    } else {
        a -> r1 = r1; //change to new reg
    }
}

//Done
entry *findVar(int r1, int r2) {
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        if (RegTable[i] != NULL) {
            if (RegTable[i]->op == '0' && RegTable[i]->r2 == r2) {
                if(r1 != 0)
                    RegTable[i]->r1 = r1;
                return RegTable[i];
            }
        }
    }
    return NULL;
}

//Done
entry *lookupR(char op, int r1, int r2) {
    int currentIndex;

    currentIndex = hash(op, r1, r2);
    if (RegTable[currentIndex])
        return RegTable[currentIndex];
    return NULL;
}

//Done
void InitVarHash() {

    if (!RegTable) {
        int i;

        RegTable = (entry **) malloc(sizeof(entry *) * HASH_TABLE_SIZE);
        for (i = 0; i < HASH_TABLE_SIZE; i++)
            RegTable[i] = NULL;
    }
}

void deleteEntries(int r1)
{

}