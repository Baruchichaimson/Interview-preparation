#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Exc1.h"

/***************************
 Exercise:  WS8
 Date: 	    17/06/25
 Developer: Baruch Haimson
 Reviewer:  
 Status:    
***************************/


/*****ADD-FUNCTIONS*********/
void AddInt(Operator* op)
{ 
	*(int*)&op->value += 10; 
}
void AddFloat(Operator* op)
{ 
	*(float*)&op->value += 1.5f; 
}
void AddString(Operator* op)   
{ 
	char* str = (char*)op->value;
    const char* to_add = " append";

    size_t new_len = strlen(str) + strlen(to_add) + 1;
    char* new_str = realloc(str, new_len);
    assert(new_str != NULL);

    strcat(new_str, to_add);
    op->value = new_str; 
}


/*****PRINT-FUNCTIONS*********/
void PrintInt(Operator* op)    
{ 
	printf("Int: %d\n", *((int*)&op->value)); 
}
void PrintFloat(Operator* op)  
{ 
	printf("Float: %.2f\n", *((float*)&op->value)); 
}
void PrintString(Operator* op) 
{ 
    printf("String: %s\n", (char*)op->value); 
}


/*****CLEAR-FUNCTIONS*********/
void ClearInt(Operator* op)    
{ 
	*(int*)&op->value = 0; 
}
void ClearFloat(Operator* op)  
{ 
	*(float*)&op->value = 0.0f; 
}
void ClearString(Operator* op) 
{ 
    ((char*)op->value)[0] = '\0';
}


/*****INIT-FUNCTIONS*********/
void InitInt(Operator* element, int value)
{
    element->add = AddInt;
    element->print = PrintInt;
    element->clear = ClearInt;
    *(int*)&element->value = value;
}

void InitFloat(Operator* element, float value)
{
    element->add = AddFloat;
    element->print = PrintFloat;
    element->clear = ClearFloat;
    *(float*)&element->value = value;
}

void InitStr(Operator* element, const char* str)
{
    char* p = malloc(strlen(str) + 1);
    assert(p != NULL);
    strcpy(p, str);

    element->add = AddString;
    element->print = PrintString;
    element->clear = ClearString;
    element->value = p;
}


/*****PRINTALL & ADDALL & FREEALL FUNCTIONS*********/
void printAll(Operator* element, size_t size)
{
	size_t i;
    for (i = 0; i < size; ++i)
    {
        element[i].print(&element[i]);
    }
}

void addAll(Operator* element, size_t size)
{
	size_t i;
    for (i = 0; i < size; ++i)
    {
        element[i].add(&element[i]);
    }
}

void clearAll(Operator* element, size_t size)
{
	size_t i;
    for (i = 0; i < size; ++i)
    {
        element[i].clear(&element[i]);
    }
}

void freeAll(Operator* element, size_t size)
{
    size_t i;
    for (i = 0; i < size; ++i)
    {
        if (element[i].clear == ClearString)
        {
            free(element[i].value); 
        }
    }
}

