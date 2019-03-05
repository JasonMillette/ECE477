//ECE477 Lab5
//AVR programming
//Jason Millette, Spencer Goulette, Steven Ferrarese

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<wiringPi.h>

int main() {
	//Uses wiringPi to detect the frequecny of a 100Hz square wave
	//coming from an AVR ATMEGA88 then adjustes the OSCCAL
	//register to callibrate the clock on the AVR.
	
	//setup wiring pi
	wiringPiSetup();

	//Set GPIO 3 for input
	pinMode(3, INPUT);

	//Inits internal pull down resistor
	//pullUpDnControl(3, PUD_DOWN);
	
	//Opening avr code
	FILE *ff;

	//Variables
	double time[2];
	double frequency, avgFreq = 0, totalTime = 0;
	int clock = 128;
	
	while(1) {

		//opens file
		ff = fopen("avrcode.c", "r+");
		if (ff < 0) { //error checking on file open
			printf("Error opening program\n");
			return 1;
		}

		for(int i = 0; i < 100; i++) {	//loop to average 100 samples
			if(digitalRead(3) == HIGH) { //Totals time high
				time[0] = micros(); //First time stamp
				while(digitalRead(3) == HIGH); //Waits for transition
				time[1] = micros(); //Second time stamp
				totalTime += (time[1] - time[0]); //subtracts time stamps for time high
			}
	
			if(digitalRead(3) == LOW) { //Totals time low
				time[0] = micros(); //First time stamp
				while(digitalRead(3) == LOW); //Waits for transition
				time[1] = micros(); //Second time stamp
				totalTime += (time[1] - time[0]); // subtracts time stamps for time low
			}
	
			frequency = (1/(totalTime*1E-6));  //Calculates frequency based on the period
			if (i != 0) //Throws out first value as it is almost always incorrect
				avgFreq += frequency;
			totalTime = 0;		//resetting total
		}

		frequency = avgFreq/99;	//Takes average then resets running total
		avgFreq = 0;
		printf("Frequency: %lf\n", frequency);

		//Adjusting clock
		if(frequency < 100.5)
			clock++;
		else if(frequency > 99.5)
			clock--;
		if(frequency > 99.5 && frequency < 100.5) {
			printf("Clock is now calibrated\n");
			fclose(ff);
			return 0;
		}

		if(clock > 255 || clock < 0) { //Clock bounds
			printf("Clock hit bounds\n");
			fclose(ff);
			return 1;
		}

		//changing avr code to adjust clock
		fprintf(ff, "int value = %d;\n", clock);
		fclose(ff);

		//recompiling and flashing the board
		system("make flash");
		sleep(5);// Allows child to finish

	}
	fclose(ff);
	return 0;
}
