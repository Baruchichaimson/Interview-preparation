#ifndef __EXC1_H__
#define __EXC1_H__

#include <stddef.h>

/***************************
 Exercise:  WS8
 Date: 	    17/06/25
 Developer: Baruch Haimson
 Reviewer:  
 Status:    
***************************/
typedef struct Operator Operator;

typedef void (*AddFunc)(Operator* op);
typedef void (*PrintFunc)(Operator* op);
typedef void (*ClearFunc)(Operator* op);

struct Operator
{
    AddFunc add;
    PrintFunc print;
    ClearFunc clear;
    void* value;
};



void InitInt(Operator* element, int value);
void InitFloat(Operator* element, float value);
void InitStr(Operator* element, const char* str);


void printAll(Operator* element, size_t size);
void addAll(Operator* element, size_t size);
void clearAll(Operator* element, size_t size);
void freeAll(Operator* element, size_t size);

#endif 

