//Jason Millette
//ECE477 LAB2 blinking RGB LEDs
//2/9/18

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>


int main(int argc, char *argv[]) {
	//toggles LEDs on GPIO 1-15 based on user desired input from command line argument
	//the second argument chooses the color from red, blue or purple
	//input can be entered as intiger, binary, octal or hex values using c syntax
	
	//variables used
	int out, color = 0, color2 = 0;
	int mask = 0b00000001;
	
	//error checking on input arguments
	if (argc < 3) {
		printf("partB needs a value to toggle LEDs, decimal, binary, octal or hex may be used, as well as a color red, blue or purple.\n./partB value color\n");
		return 1;
	}

	if (argc > 4) {
		printf("partB needs a value to toggle LEDs, decimal, binary, octal or hex may be used, as well as a color red, blue or purple.\n./partB value color\n");
		return 1;
	}

	//sets up wiringpi pins for output
	wiringPiSetup();
	pinMode(0,OUTPUT);
	pinMode(1,OUTPUT);
	pinMode(2,OUTPUT);
	pinMode(3,OUTPUT);
	pinMode(4,OUTPUT);
	pinMode(5,OUTPUT);
	pinMode(6,OUTPUT);
	pinMode(7,OUTPUT);
	pinMode(8,OUTPUT);
	pinMode(9,OUTPUT);
	pinMode(10,OUTPUT);
	pinMode(11,OUTPUT);
	pinMode(12,OUTPUT);
	pinMode(13,OUTPUT);
	pinMode(14,OUTPUT);
	pinMode(15,OUTPUT);

	//Parses input for desired LEDs
	//checks which input method was used then saves the value to the int out
	if (argv[1][0] == '0') { //Checks for leading 0, for either hex or octal
		if (argv[1][1] == 'x') { //checks for x, for hex
			sscanf(argv[1], "0x%X\n", &out);
		}
		else 
			sscanf(argv[1], "0%o\n", &out);
	} else
		sscanf(argv[1], "%d\n", &out);

	//parses the second input for color choice
	//r for red, b for blue and p for purple
	if (argv[2][0] == 'b') { //checks for b in blue
		color = 0;
		color2 = 1;
	}
	else if (argv[2][0] == 'r') { //checks for r in red
		color = 1;
		color2 = 0;
	}
	else if (argv[2][0] == 'p') { //checks for p in purple
		color = 2;
	} else {
		printf("enter a color red, blue or purple\n./partB value color\n");
		return 2;
	}
	
	//turns on LEDs based on value of out
	//digitalWrite(pin, value);
	for (int i=0; i < 16; i+=2) { //runs through loop for every LED
		if ((mask & out) && (color != 2)) { //checks for non purple case and mask
			digitalWrite(i+color, LOW);
			digitalWrite(i+color2, HIGH);
		} else if (color != 2) {
			digitalWrite(i+color, HIGH);
			digitalWrite(i+color2, HIGH);
		}
		if ((mask & out) && (color == 2)) { //checks for purple case and mask
			digitalWrite(i+1, LOW);
			digitalWrite(i, LOW);
		} else if (color == 2) {
			digitalWrite(i+1, HIGH);
			digitalWrite(i, HIGH);
		}

		mask = mask << 1; //shifts mask to check for the next LED
	}

	return 0;
}
