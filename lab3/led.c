// Lab 2
// Spencer Goulette, Jason Millette, Steven Ferrarese
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
int main(int argc, char ** argv)
{
	//error checking 
	if(argc > 2)//check amount of arguments
	{
		printf("Too many arguments\n");
		return 3;//exit program
	}
	else if (argc < 2)//not enought arguments
	{
		printf("Not enought arguments\n");
		return 4;//exit program
	}	
	
	int result,x;
	//setup wiringPi
	wiringPiSetup();
	for (int i = 0; i < 8; i++)
		pinMode(i,OUTPUT);
	
	//parse input for LED's
	//checks for leading 0 (hex or octal)
	if (argv[1][0] == '0')
	{
		if(argv[1][1] == 'x')//check for x (hex)
			sscanf(argv[1],"0x%X\n", &result);
		else//octal
			sscanf(argv[1], "0%o\n", &result);
	}
	else if (argv[1][0] == '-')//error check to see if negative number
	{
		printf("Error no negative numbers\n");
		return 2;//exit
	}	
	else 
		sscanf(argv[1],"%d\n",&result);
	

	//check if input is more than 8 bits
	if (result > 255)
	{
		printf("Error input too large\n");
		return 5;//exit
	}

	//turn on LED's based on value
	for(int i = 0; i < 8; i++)//once for each LED
	{
	
		if(result &(0x80 >> i ))//mask and see if bit in 1 or 0
		{
			printf("1");
			digitalWrite(i,HIGH);//LED on
		}
		else
		{
			printf("0");
			digitalWrite(i,LOW);//LED off
		}
	} 
	printf("\n");
	return 0;//no errors exit program
}
