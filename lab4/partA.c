//ECE477 Lab3 partA
//2/21/19
//Jason Millette, Spencer Goulette, Steven Ferrarese

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wiringPi.h>

int main()
{
	char buffer[12];
	unsigned long int delay = 0x400;
	int direction = 0;
	unsigned int lights = 0x001;
	int prevButtonA = 0;
	int prevButtonB = 0;

	wiringPiSetup();

	pinMode(8,INPUT);
	pinMode(9,INPUT);

	pullUpDnControl(8,PUD_UP);
	pullUpDnControl(9,PUD_UP);

	while(1)
	{
		snprintf(buffer, sizeof(buffer), "./led %d", lights);
		system(buffer);

		if(direction == 0)
		{
			lights <<= 1;
		}
		else
		{
			lights >>= 1;
		}
	
		if(lights > 0x80)
		{
			lights = 0x001;
		}
		else if(lights < 0x01)
		{
			lights = 0x080;
		}
	
		for(int i = 0; i < delay; i++)
		{
			usleep(1000);

			if(prevButtonA == 0 && digitalRead(8) == LOW) 
			{
				prevButtonA = 1;
				if(delay != 32)
				{
					delay >>= 1;
				}
				else
				{
					direction = !direction;
				}
			}
			else if(prevButtonA == 1 && digitalRead(8) == HIGH)
			{
				prevButtonA = 0;
			}

			if(prevButtonB == 0 && digitalRead(9) == LOW)
			{
				prevButtonB = 1;
				if(delay != 1024)
				{
					delay <<= 1;
				}
				else
				{
					direction = !direction;
				}
			}
			else if(prevButtonB == 1 && digitalRead(9) == HIGH)
			{
				prevButtonB = 0;
			}

			if(prevButtonA == 0 && prevButtonB == 0 && digitalRead(8) == LOW && digitalRead(9) == LOW)
			{
				return 0;
			}
		}
	}

	return 0;
}




