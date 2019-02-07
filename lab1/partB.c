// Jason Millette, Spencer Goulette, Steven Ferrarese
// 1/31/19
// ECE 477 Lab 1

#include <stdio.h>

int main(){
	// Int used to change color of prints
	int color = 30;
	
	// Two for loops to print Hello World based on the size of data types
	printf("Prints Hello World equal to the number of bytes in an int\n");
	for(int i = 0; sizeof(int) > i; i++)
	{
		color = 42.0 + i;	// Escape code used for color
		printf("\x1b[%dm""Hello World""\x1b[0m""\n", color);
	}

	printf("Prints Hello World equal to the number of bytes in a long\n");
	for(int i = 0; sizeof(long) > i; i++)
	{
		color = 42.0 + i;
		printf("\x1b[%dm""Hello World""\x1b[0m""\n", color);
	}
	
	return 0;
}
