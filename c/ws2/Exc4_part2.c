#include <stdio.h>
#include <ctype.h>
/**********
 Exercise: 	WS2
 Date: 		05/06/25
 Developer:     Baruch Haimson
 Reviewer: 	Tal Hindi
 Status: 	Approved
 **********/

void WhiteSpace(char* str)
{
    char* final = str;
    char* start = str;  
    while (isspace((unsigned char)*str)) 
    {
        str++;
    }
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
    if(str > final)
    {
    	final--;
    }
    *final = '\0';
    printf("After : \"%s\"\n", start);  
}

int main()
{
    char str[] = "  \t This   is   a   test   string   ";
    printf("Before: \"%s\"\n", str);
    WhiteSpace(str);
    
    return 0;
}
