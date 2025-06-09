#include <stdio.h>
#include <stdlib.h>

void HandleKeyIfElse(char c)
{
    if (c == 'A')
        printf("A pressed\n");
    else if (c == 'T')
        printf("T pressed\n");
    else if (c == 27) 
    {
        system("stty icanon echo");
        printf("Exiting program...\n"); 
        exit(0);
    }
}

int main()
{
    char c;
    system("stty -icanon -echo");
    while (1)
    {    
        c = getchar();   
        HandleKeyIfElse(c);
    }	

    return 0;
}
