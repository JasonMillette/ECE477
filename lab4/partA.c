//ECE477 Lab4 partA
//2/28/19
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
	unsigned int lights = 0x001;
	
	/* Button status variables */
	int prevButtonA = 0;
	int prevButtonB = 0;
	
	wiringPiSetup();

	/* Makes Pin 8 and 9 Inputs and Pull Up */
	pinMode(8,INPUT);
	pinMode(9,INPUT);
	pullUpDnControl(8,PUD_UP);
	pullUpDnControl(9,PUD_UP);

	while(1)
	{
		/* Combines the lights number and with the string  to call the LED program */
		snprintf(buffer, sizeof(buffer), "./led %d", lights);
		system(buffer);

		/* Direction of LED movement */
		if(direction == 0)
		{
			lights <<= 1;
		}
		else
		{
			lights >>= 1;
		}
	
		/* Wraps LEDs around */
		if(lights > 0x80)
		{
			lights = 0x001;
		}
		else if(lights < 0x01)
		{
			lights = 0x080;
		}
	
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
				
				/* If not lowest delay, make lower */
				if(delay != 32)
				{
					delay >>= 1;
				}
				
				/* If lowest delay, change direction */
				else
				{
					direction = !direction;
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
				
				/* If not highest delay, make higher */
				if(delay != 1024)
				{
					delay <<= 1;
				}
				
				/* If highest delay, change direction */
				else
				{
					direction = !direction;
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
	}

	return 0;
}




