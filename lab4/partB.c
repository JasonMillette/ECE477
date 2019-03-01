//ECE477 Lab3 partA
//2/21/19
//Jason Millette, Spencer Goulette, Steven Ferrarese

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wiringPi.h>

int main()
{
	/* Buffer for string combine */
	char buffer[12];
	
	/* LED variables */
	unsigned long int delay = 0x400;
	int direction = 0;
	unsigned int lights = 0x0FF;/* indicating ready for player to start game */
	
	/* Button status variables */
	int prevButtonA = 0;
	int prevButtonB = 0;
	
	wiringPiSetup();

	/* Makes Pin 8 and 9 Inputs and Pull Up */
	pinMode(8,INPUT);
	pinMode(9,INPUT);
	pullUpDnControl(8,PUD_UP);
	pullUpDnControl(9,PUD_UP);

	/*lights = 0xFF or all LED's on indicats ready for player to start game */
	while(1)
	{
		/* Combines the lights number and with the string  to call the LED program */
		snprintf(buffer, sizeof(buffer), "./led %d", lights);
		system(buffer);

		/* Check button presses and delay */
		for(int i = 0; i < delay; i++)
		{
			/* 1 ms delay */
			usleep(1000);

			/* If button A pressed */
			if(prevButtonA == 0 && digitalRead(8) == LOW) 
			{
				/* prevButtonA to get single press */
				prevButtonA = 1;
				
				
				/* change direction if LED is on players side */
				if (lights == 0x01)
				{
					direction = !direction;
				}
				/* For starting new game*/
				else if(lights == 0xFF)
				{

					direction = 0;
					lights = 0x01;
				}
				/* Button pressed at wrong time, player losses  */
				else
				{
					lights = 0xFF;
				}
				
			}
			
			/* If button A not pressed */
			else if(prevButtonA == 1 && digitalRead(8) == HIGH)
			{
				prevButtonA = 0;
			}

			/* If button B pressed */
			if(prevButtonB == 0 && digitalRead(9) == LOW)
			{
				/* prevButtonB to get single input */
				prevButtonB = 1;
				
				/* Change direction if LED is on players side*/
				if(lights == 0x80)
				{
					direction = !direction;
				}
				/* for starting new game*/ 
				else if(lights == 0xFF)
				{
					direction = 1;
					lights = 0x80;
				}
				/* Button pressed at wrong time, player losses */
				else
				{
					lights = 0xFF;
				}
			}
			
			/* If button B not pressed */
			else if(prevButtonB == 1 && digitalRead(9) == HIGH)
			{
				prevButtonB = 0;
			}

			/* If both button A and B are pressed */
			if(prevButtonA == 0 && prevButtonB == 0 && digitalRead(8) == LOW && digitalRead(9) == LOW)
			{
				return 0;
			}
		}

		/* Direction of LED movement */
		if((direction == 0)&&(lights != 0xFF))
		{
			lights <<= 1;
		}
		else if (lights != 0xFF)
		{
			lights >>= 1;
		}
		/*make sure lights is not greater than 255 or less then 0, indicating ready for player to start game */
		if ((lights > 0xFF)||(lights == 0x00))
			lights = 0xFF;
	}

	return 0;
}




