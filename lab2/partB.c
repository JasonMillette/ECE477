//Jason Millette
//ECE477 LAB2 blinking RGB LEDs
//2/9/18

#include <stdio.h>
#include <string.h>

int export();
int unexport();
int direction(char *direction, char *pin);
int value(char *value, char *pin);
int pinSetup();

int main(int argc, char *argv[]) {
	//toggles LEDs on GPIO 1-7 based on user desired input from command line argument
	//-help or -h returns instructions on usage
	//input can be entered as intiger, binary, octal or hex values using c syntax
	
	if (argc < 2) {
		printf("partB needs a value to toggle LEDs, decimal, binary, octal or hex may be used.\n");
		return 1;
	}

	if (argc > 3) {
		printf("partB needs a value to toggle LEDs, decimal, binary, octal or hex may be used.\n");
		return 1;
	}

	return 0;
}

int export() {
	//using wiringpi to export all used GPIO pins
	//pins used are 0-7
	//add error checking
	
	system("cd /sys/class/gpio && echo 0 > export");
	system("cd /sys/class/gpio && echo 1 > export");
	system("cd /sys/class/gpio && echo 2 > export");
	system("cd /sys/class/gpio && echo 3 > export");
	system("cd /sys/class/gpio && echo 4 > export");
	system("cd /sys/class/gpio && echo 5 > export");
	system("cd /sys/class/gpio && echo 6 > export");
	system("cd /sys/class/gpio && echo 7 > export");

	return 0;
}

int unexport() {
	//using wiringpi to unexport all used GPIO pins
	//pins used are 0-7
	//add error checking
	
	system("cd /sys/class/gpio && echo 0 > unexport");
	system("cd /sys/class/gpio && echo 1 > unexport");
	system("cd /sys/class/gpio && echo 2 > unexport");
	system("cd /sys/class/gpio && echo 3 > unexport");
	system("cd /sys/class/gpio && echo 4 > unexport");
	system("cd /sys/class/gpio && echo 5 > unexport");
	system("cd /sys/class/gpio && echo 6 > unexport");
	system("cd /sys/class/gpio && echo 7 > unexport");
	system("cd /sys/class/gpio && echo 8 > unexport");

	return 0;
}
