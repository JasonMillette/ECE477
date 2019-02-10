//Steven Ferrarese
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
	if (((argv[1][0]== '0')&&(argv[1][1]=='x')))//if input is in hex
	{
		result = strtol(argv[1],NULL,16);
	}
	else 
	{
		result = atoi(argv[1]);//if a number
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
	return 0;//no errors exit program
}
