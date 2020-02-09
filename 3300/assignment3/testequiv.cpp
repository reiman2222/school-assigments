
#include <cstdio>
#include "equiv.h"
using namespace std;


int main(int argc, char** argv)
{
	
	char input;
	int x, y;
	int size = 12;
	ER test;
	test = newER(size);
	
	printf("Enter letter to test program(0 to stop).\n"
		"T for together, C for combine, S for show ER, L for leader.\n");
	
	scanf("%c", &input);
	
	while(input != '0')
	{
		if(input == 'T')
		{
			printf("enter 2 numbers to check.\n");
			scanf("%i", &x);
			scanf("%i", &y);
			if(together(test, x, y))
			{
				printf("True\n\n");
			}
			else
			{
				printf("False\n\n");
			}
		}
		else if(input == 'C')
		{
			printf("enter 2 numbers to combine.\n");
			scanf("%i", &x);
			scanf("%i", &y);
			combine(test, x, y);
			printf("Combined.\n");
			
		}
		else if(input == 'S')
		{
			showER(test, size);
		}
		else if(input == 'L')
		{
			printf("enter number to see leader.\n");
			scanf("%i", &x);
			printf("Leader is: %i\n", leader(test, x));
		}
			
		printf("Enter a letter.\n");
		scanf("%c", &input);
	}
	
	destroyER(test);
	
	return 0;
}