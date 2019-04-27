//Steven Ferrarese
//2 wire stepper motor 
//motor control for lock
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <unistd.h>
#include <math.h>

void turn(int step);
int main(int argc, char ** argv)
{
	
	
	//setup wiring Pi	
	wiringPiSetup();
	//using pin 22 and 24 as ouputs
	pinMode(22,OUTPUT);//step 
	pinMode(24,OUTPUT);//direction output	
	
	//set direciton for direction to rotate motor
	if (atoi(argv[1]) == 0)	
		digitalWrite(24, HIGH);
	else 
		digitalWrite(24, LOW);

	//data sheet reconds delay between setting directiona and roating motor
	usleep(100);

	//rotate motor
	turn(atoi(argv[2]));
	

	return 0;
}
void turn(int step)
{	
	//each step is one irreration through loop
	for (int i = 0; i < step; i++)
	{
		//just putting motor high/low 
		usleep(2500);
		digitalWrite (22, HIGH);
		usleep(2500);
		digitalWrite (22, LOW);
	}
}
