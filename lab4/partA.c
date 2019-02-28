//ECE477 Lab3 partA
//2/21/19
//Jason Millette, Spencer Goulette, Steven Ferrarese

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	char buffer[12];
	int delay = 1024;
	int direction = 0;
	unsigned int lights = 0x01;

	wiringpisetup();

	pinmode(8,IN);
	pinmode(9,IN);

	while(1)
	{
		snprintf(buffer, sizeof(buffer), "./led %d", lights);
		system(buffer);
		
		usleep(1000 * delay);

		if(direction == 0)
		{
			lights <<= 1;
		}
		else
		{
			lights >>= 1;
		}
		
		if(lights > 0xFF)
		{
			lights = 0x01;
		}
		if(lights < 0x01)
		{
			lights = 0xFF;
		}

		if(button a)
		{
			if(delay != 32)
			{
				delay >>= 1;
			}
			else
			{
				direction != direction;
			}
		}
		if(button b)
		{
			if(delay != 1024)
			{
				delay <<= 1;
			}
			else
			{
				direction != direction;
			}
		}
		if(button a && button b)
		{
			return 0;
		}
	}

	return 0;
}




