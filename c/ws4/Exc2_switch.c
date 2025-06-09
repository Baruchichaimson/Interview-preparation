#include <stdio.h>
#include <stdlib.h>

void HandleKeySwitch(char c)
{
    switch (c)
    {
        case 'A': 
        	printf("A pressed\n");
                break;
        case 'T': 
                printf("T pressed\n"); 
                break;
        case 27:  
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
        HandleKeySwitch(c);
    }	

    return 0;
}
