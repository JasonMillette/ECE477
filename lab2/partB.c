//Jason Millette
//ECE477 LAB2 blinking RGB LEDs
//2/9/18

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>


int main(int argc, char *argv[]) {
	//toggles LEDs on GPIO 1-7 based on user desired input from command line argument
	//-help or -h returns instructions on usage
	//input can be entered as intiger, binary, octal or hex values using c syntax
	
	int decimal, octal, hex, out;
	int mask = 0b00000001;
	
	if (argc < 2) {
		printf("partB needs a value to toggle LEDs, decimal, binary, octal or hex may be used.\n");
		return 1;
	}

	if (argc > 3) {
		printf("partB needs a value to toggle LEDs, decimal, binary, octal or hex may be used.\n");
		return 1;
	}

	//sets up wiringpi
	wiringPiSetup();
	pinMode(0,OUTPUT);
	pinMode(1,OUTPUT);
	pinMode(2,OUTPUT);
	pinMode(3,OUTPUT);
	pinMode(4,OUTPUT);
	pinMode(5,OUTPUT);
	pinMode(6,OUTPUT);
	pinMode(7,OUTPUT);

	//Parses input for desired LEDs
	sscanf(argv[1], "%d\n", &decimal);
	sscanf(argv[1], "0%o\n", &octal);
	sscanf(argv[1], "0x%x\n", &hex);
	printf("int = %d\noctal = %d\nhex = %d\n", decimal, octal, hex); // used for debugging sscanff()
	out = decimal + octal + hex; //sets one variable to be used for toggling LEDs

	
	//turns on LEDs
	//digitalWrite(pin, value);
	for (int i=0; i < 8; i++) {
		if (mask & out) {
			digitalWrite(i, LOW);
		}
		else {
			digitalWrite(i, HIGH);
		}

		mask = mask << 1;
	}

	while (1){;} //deadloop for debugging
	
	return 0;
}
