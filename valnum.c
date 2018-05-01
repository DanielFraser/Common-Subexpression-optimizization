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
node *head = NULL;

//Done
int hash(char op, int r1, int r2) {
    int num = 0; //num is to reduce amount of collisions
    switch (op) {
        case '+':
            num = 10;
            break;
        case '-':
            num = 20;
            break;
        case '*':
            num = 30;
            break;
    }

    if(op == '+' || op == '*')
    {
        int a = (((4 * r1) + r2) + num) % HASH_TABLE_SIZE;
        int b = (((4 * r2) + r1) + num) % HASH_TABLE_SIZE;
        if(a<b)
            return a;
        return b;
    }
    return (((4 * r1) + r2) + num) % HASH_TABLE_SIZE;
}

//Done
//make constants have r2 = -1
void addEntry(char op, int r1, int r2, int r3) {

    if (!lookupR(op, r1, r2)) {
        int hashV = hash(op, r1, r2), i;
        for (i = hashV; i < HASH_TABLE_SIZE; i++) { //keep looping until we find an empty slot
            if (RegTable[i] == NULL) {
                RegTable[i] = (entry *) malloc(sizeof(entry));
                RegTable[i]->op = op;
                RegTable[i]->r1 = r1;
                RegTable[i]->r2 = r2;
                RegTable[i]->r3 = r3;
                return;
            }
        }
    }
}

void addVar(int offset, int r3) {
    deleteEntries(offset); //remove any if necessary
    int hashnum = hash('v', offset, 2), i;
    for (i = hashnum; i < HASH_TABLE_SIZE; i++) { //keep looping until we find an empty slot
        if (RegTable[i] == NULL) {
            RegTable[i] = (entry *) malloc(sizeof(entry));
            RegTable[i]->op = 'v';
            RegTable[i]->r1 = -1;
            RegTable[i]->r2 = offset;
            RegTable[i]->r3 = r3;
            return;
        }
    }
}

//Done
entry *findVar(int offset) {
    int i;
    if (offset >= 0) {
        for (i = hash('v', offset, 2); i < HASH_TABLE_SIZE; i++) {
            if (RegTable[i] != NULL) {
                if (RegTable[i]->op == 'v' && RegTable[i]->r2 == offset) {
                    return RegTable[i];
                }
            }
        }
    }
    return NULL;
}

//Done
entry *lookupR(char op, int r1, int r2) {
    int currentIndex;
    int i;
    currentIndex = hash(op, r1, r2);
    for (i = currentIndex; i < HASH_TABLE_SIZE; i++) {
        if (RegTable[i] != NULL) {
            if (RegTable[i]->op == op && RegTable[i]->r1 == r1 && RegTable[i]->r2 == r2) {
                return RegTable[i];
            } else if ((op == '+' || op == '*') && RegTable[i]->op == op && RegTable[i]->r1 == r2 &&
                       RegTable[i]->r2 == r2) {

                return RegTable[i];
            }
        }
    }
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

void startList(int reg) {
    head = malloc(sizeof(node));
    head->reg = reg;
    head->next = NULL;
}

int indexOf(char op, int r1, int r2, int r3) {
    node *cursor = head;
    while (cursor->next) {
        if (op != 'v' && op != 'c') {
            if (r1 == cursor->reg || r2 == cursor->reg)
                return 1;
            cursor = cursor->next;
        }
    }
    return 0;
}

void push(int reg) {
    node *temp = malloc(sizeof(node));
    temp->reg = reg;
    temp->next = NULL;
    node *cursor = head;
    if (head) {
        while (cursor->next)
            cursor = cursor->next;
        cursor->next = temp;
    } else {
        head = temp;
    }
}

void deleteVar(int offset) {
    int i;
    for (i = hash('v', offset, 2); i < HASH_TABLE_SIZE; i++) {
        if (RegTable[i] != NULL) {
            if (RegTable[i]->op == 'v' && RegTable[i]->r2 == offset) {
                RegTable[i] = NULL;
                return;
            }
        }
    }
}

void deleteEntries(int r1) {
    int done = 0, changes = 0;
    entry *a = findVar(r1);
    if (a) {
        push(a->r3);
        int i, reg;
        deleteVar(r1); //remove from hashtable
        for (i = 0; i < HASH_TABLE_SIZE; i++)
            //make sure its not a constant or var (since we use r1 and r2 different things)
            if (RegTable[i] && indexOf(RegTable[i]->op, RegTable[i]->r1, RegTable[i]->r2, RegTable[i]->r3)) {
                push(RegTable[i]->r3);
                RegTable[i] = NULL;
                changes = 1;
            }
    }
}