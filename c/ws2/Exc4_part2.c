#include <stdio.h>

void WhiteSpace(char* str)
{
    char* final = str;
    char* start = str;   
    while (*str)
    {
        if (*str == ' ' && *(str + 1) == ' ')
        {       
            str++;
            continue;
        }
        *final = *str;
        final++;
        str++;
    }
    *final = '\0';
    printf("After : \"%s\"\n", start);  
}

int main()
{
    char str[] = "This   is   a   test   string";
    printf("Before: \"%s\"\n", str);
    WhiteSpace(str);
    
    return 0;
}
