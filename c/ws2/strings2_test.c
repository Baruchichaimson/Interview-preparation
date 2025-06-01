#include <stdio.h>
#include <assert.h>
#include "strings2.h"

int main()
{
    char* s1 = "baruch haimson";
    char* s2 = "baruch haimson";
    char* s3 = "baruch iaimson";
    char* s4 = "baruch aimson";

    assert(StrCmp(s1, s2) == 0);
    assert(StrCmp(s1, s3) == -1); 
    assert(StrCmp(s1, s4) == 1);   

    printf("All StrCmp tests passed successfully!\n");

    return 0;
}
