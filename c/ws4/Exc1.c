#include <stdio.h>
#include <stdlib.h>

int main()
{	
	char tav;
	system("stty -icanon -echo");
	while(1)
	{
		tav = getchar();
		switch(tav)
		{
			case 27:
				system("stty icanon echo");
				break;
			case 'A':
				printf("A-pressed\n");
				break;
			case 'T':
				printf("T-pressed\n");
				break;
			default:
				break;
		}
	}
	return 0;
}
