//Jason Millette
//1/31/19
//Hello world program written for ECE477

#include<stdio.h>

int main(){
	// int used to change color of prints
	int color = 30;
	
	//Two for loops to print Hello World based on the size of data types
	printf("Prints Hello World equal to the number of bytes in an int\n");
	for(int i = 0; sizeof(int) > i; i++)
	{
		color = 30 + i;
		printf("\x1b[%dm""Hello World""\x1b[0m""\n", color);
	}

	printf("Prints Hello World equal to the number of bytes in a long\n")	
	for(int i = 0; sizeof(long) > i; i++)
	{
		color = 30 + i;
		printf("\x1b[%dm""Hello World""\x1b[0m""\n", color);
	}
	
	return 0;
}
