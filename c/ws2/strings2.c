#include <stdio.h>
#include "strings2.h"
#include <assert.h>

int StrCmp (char string1[], char string2[])
{
    for (int i = 0;; i++)
    {
        if (string1[i] != string2[i])
        {
            return string1[i] < string2[i] ? -1 : 1;
        }

        if (string1[i] == '\0')
        {
            return 0;
        }
    }
}
