#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

#define pin 4
#define per 200 // Keep as 200 for 20ms Period PWM

int main(void)
{
	int rotate = 6;	// Rotation variable
	int degree = -90;

	printf("Raspberry Pi wiringPi test program \n");	// Intro print
	wiringPiSetup();	// Set up wiring Pi
	pinMode(pin, PWM_OUTPUT);	// Make pin chosen output

	digitalWrite(pin,0);	// Write a 0 to the pin

	softPwmCreate(pin,0,per);	// Create a 20ms Period PWM

	while(1)
	{
		printf("Enter Degrees between -90 and 90: \n");	// Prompt User
		scanf("%d",&degree);	// Get User input

		if(degree >= -90 && degree <= 90)	// Make sure user input is valid
		{
			if(degree <= 0)
			{
				rotate = (int)((degree + 90) * 8.0 / 90 + 6);
			}
			else
			{
				rotate = (int)(degree * 11.0 / 90 + 14);
			}

			softPwmWrite(pin,rotate);	// Change Duty cycle of PWM
			printf("20ms period PWM with %.2f%% positive Duty Cycle \n", (rotate/(float)per)*100);	// Print PWM and Duty Cycle
			delay(1000);	// Delay a second
		}
		else
		{
			printf("Invalid Degrees! \n");	// User input invalid
		}
	}
	return 0;
}
