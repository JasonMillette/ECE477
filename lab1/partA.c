// Jason Millette, Spencer Goulette, Steven Ferrarese
//1/31/19
//Hello world program written for ECE477

#include<stdio.h>

int main(){
	
	//Two for loops to print Hello World based on the size of data types
	printf("Prints Hello World equal to the number of bytes in an int\n");
	for(int i = 0; sizeof(int) > i; i++)	printf("Hello World\n");

	printf("Prints Hello World equal to the number of bytes in a long\n");
	for(int i = 0; sizeof(long) > i; i++)	printf("Hello World\n");
	
	return 0;
}
