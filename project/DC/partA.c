//ECE477 Project DC motor control 
//4/20/19
//Jason Millette, Spencer Goulette, Steven Ferrarese

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wiringPi.h>

int main() {
	//Turns DC motor based on command line inputs
	
	//Initializes wiring Pi with the two outputs and one PWM
	wiringPiSetup();


	//Variables
	char userInput[6];

	while(1) {
		//Asks for user input
		printf("direction speed, ex: f 69\n");
		scanf();
		
		//Sets GPIO pins based on user input with wiringpi
	}

	return 0;
}
