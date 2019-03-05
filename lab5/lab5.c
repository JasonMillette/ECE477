//ECE477 Lab5
//AVR programming
//Jason Millette, Spencer Goulette, Steven Ferrarese

#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
#include<wiringPi.h>

int main() {
	//setup wiring pi
	wiringPiSetup();

	//Set GPIO 3 for input
	pinMode(3, INPUT);

	//Inits internal pull down resistor
	pullUpDnControl(3, PUD_DOWN);
	
	//Opening avr code
	FILE *ff;
	ff = fopen("avrcode.c", "w");
	if (ff < 0) { //error checking on file open
		printf("Error opening program\n");
		return 1;
	}

	double time[2];
	double totalTime = 0;
	int clock = 128;
	double frequency;
	char line = "int value = 128;";
	
	while(1) {
		if(digitalRead(3) == HIGH) { //Totals time high
			time[0] = micros(); //First time stamp
			while(digitalRead(3) == HIGH);
			time[1] = micros(); //Second time stamp
			totalTime += (time[1] - time[0]);
		}

		if(digitalRead(3) == LOW) { //Totals time low
			time[0] = micros(); //First time stamp
			while(digitalRead(3) == LOW);
			time[1] = micros(); //Second time stamp
			totalTime += (time[1] - time[0]);
		}
		frequency = (1/totalTime*1E-6);
		printf("Frequency: %lf\n",frequency);
		totalTime = 0;

		//Adjusting clock
		if(frequency < 100)
			clock++;
		else
			clock--;
		//creating string
		fscanf(line, "int value = %d;", clock);
		fwrite(ff, line, 16);


	}
	return 0;
}
