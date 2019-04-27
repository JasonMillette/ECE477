#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

#define pin 4
#define per 200 // Keep as 200 for 20ms Period PWM

int main(void)
{
	printf("Raspberry Pi wiringPi test program \n");	// Intro print
	wiringPiSetup();	// Set up wiring Pi
	pinMode(pin, PWM_OUTPUT);	// Make pin chosen output

	digitalWrite(pin,0);	// Write a 0 to the pin

	softPwmCreate(pin,0,per);	// Create a 20ms Period PWM

	for(int i = (int)(per*.03); i <= (int)(per*.13); i++)
	{
		softPwmWrite(pin,i);	// Change Duty Cycle of PWM
		printf("20 ms period PWM with %.2f%% positive Duty Cycle \n", (i/(float)per)*100);	// Print Period and duty cycle
		delay(1000);	// Wait a second
	}
	return 0;
}
