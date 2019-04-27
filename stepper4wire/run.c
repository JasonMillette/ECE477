//Steven Ferrarese
//ECE 477
//motor control for 4 wire stepper
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <unistd.h>

void turn(int step1);
int main(int argc, char ** argv)
{
	
	//setup wiringPi
	wiringPiSetup();
	//using pins 5-8
	//setup as output
	for (int i = 5; i <= 8; i++)
		pinMode(i,OUTPUT);

	//run function that turns stepper
	turn(atoi(argv[1]));	


	return 0;

}
void turn(int step1)
{	
	int x;
	int step = 0;

	//each time through the loop is a step
	for(int j = 0; j< step1; j++)
	{
		//use switch case to decide with setp to run
		switch(step)
		{
			case 0:
				digitalWrite(5,HIGH);
				digitalWrite(6,LOW);
				digitalWrite(7,LOW);
				digitalWrite(8,HIGH);
				break;

			case 1:
				digitalWrite(5,HIGH);
				digitalWrite(6,LOW);
				digitalWrite(7,HIGH);
				digitalWrite(8,LOW);
				break;
			case 2:
				digitalWrite(5,LOW);
				digitalWrite(6,HIGH);
				digitalWrite(7,HIGH);
				digitalWrite(8,LOW);
				break;

			case 3: 
				digitalWrite(5,LOW);
				digitalWrite(6,HIGH);
				digitalWrite(7,LOW);
				digitalWrite(8,HIGH);
				break;
	
			default:
				printf("error");
		}
		//delay
		usleep(4400);
		
		//increase step
		step ++;
		//reset if on step 4 
		if (step == 4)
			step = 0;
	}
}

