//ECE477 Project DC motor control 
//4/20/19
//Jason Millette, Spencer Goulette, Steven Ferrarese

#include<stdio.h>
#include<string.h>
#include<wiringPi.h>
#include<softPwm.h>

int main() {
	//Turns DC motor based on user inputs
	//user chooses a speed 0 to 100, directly
	//related to the pwm. also a direction can
	//be chosen, otherwise it remains unchanged.
	
	//Initializes wiring Pi with the two outputs and one PWM
	wiringPiSetup();
	softPwmCreate(0, 0, 100); //Initialized GPIO pin 17 for pwm controll with a starting value of 0
	pinMode(1, OUTPUT); //Initializes enable line
	pinMode(2, OUTPUT); //Initializes direction line

	//Variables
	char userInput[6];
	int pwm;

	while(1) {
		//Asks for user input
		printf("Input: direction speed, ex:f69\nEnter quit to quit\n");
		scanf("%s", userInput);

		if (!(strcmp(userInput, "quit"))) { //checks for quit condition
			softPwmWrite(0, 0);	//turns off motor before exiting program
			return 0;
		}
		
		//reads in pwm value and checks for bounds
		sscanf(userInput, "%d\n", &pwm);
		if (pwm > 100) pwm = 100;
		if (pwm < 0) pwm = 0;

		if ((userInput[0] == 'f') || (userInput[0] == 'F')) {
			digitalWrite(2, HIGH);	//sets direction to forward
		} else if (userInput[0] == 'r' || (userInput[0] == 'R')) {
			digitalWrite(2, LOW);	//sets direction to reverse
		}
		
		//Sets GPIO pins based on user input with wiringpi
		digitalWrite(1, HIGH);	//enables motor 1
		softPwmWrite(0, pwm);	//sets pwm% PWM

		printf("\n\n");	//Adds newlines for easier to read output
	}

	return 0;
}
