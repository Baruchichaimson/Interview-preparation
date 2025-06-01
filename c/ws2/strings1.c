#include <stdio.h>
#include "strings1.h"
#include <assert.h>

size_t StrLen (const char* str)
{
    if (str == NULL)
    {
        return 0;
    }
    size_t len = 0;
    while (str[len])
    {
        len++;
    }
    return len;
}
