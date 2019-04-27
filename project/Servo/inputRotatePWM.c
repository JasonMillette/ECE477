#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

#define pin 4
#define per 200 // Keep as 200 for 20ms Period PWM

int main(void)
{
	int rotate = 6;	// Rotation variable

	printf("Raspberry Pi wiringPi test program \n");	// Intro print
	wiringPiSetup();	// Set up wiring Pi
	pinMode(pin, PWM_OUTPUT);	// Make pin chosen output

	digitalWrite(pin,0);	// Write a 0 to the pin

	softPwmCreate(pin,0,per);	// Create a 20ms Period PWM

	while(1)
	{
		printf("Enter Rotation between 6 and 25\n");	// Prompt User
		scanf("%d",&rotate);	// Get User input

		if(rotate >= 6 && rotate <= 25)	// Make sure user input is valid
		{
			softPwmWrite(pin,rotate);	// Change Duty cycle of PWM
			printf("20ms period PWM with %.2f%% positive Duty Cycle \n", (rotate/(float)per)*100);	// Print PWM and Duty Cycle
			delay(1000);	// Delay a second
		}
		else
		{
			printf("Invalid rotation number! \n");	// User input invalid
		}
	}
	return 0;
}
