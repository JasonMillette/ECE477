//ECE477 Lab5
//AVR programming
//Jason Millette, Spencer Goulette, Steven Ferrarese

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<wiringPi.h>

int main() {
	//Uses wiringPi to detect the frequecny of a 100Hz square wave
	//coming from an AVR ATMEGA88 then adjustes the EEPROM
	//to callibrate the clock on the AVR.
	
	//setup wiring pi
	wiringPiSetup();
	pinMode(3, INPUT); //Set GPIO 3 for input
	
	//Variables
	double frequency = 0, avgFreq = 0, totalTime = 0, time[2];
	int clock = 0, dir = 1;
	FILE *ff;
	
	while(1) {
		//changing avrcode.c to adjust clock
		ff = fopen("avrcode.c", "r+"); //opens file
		if (ff < 0) { //error checking on file open
			printf("Error opening program\n");
			return 1;
		}

		fprintf(ff, "int value = %d, dir = %d;\n", clock, dir); //Writes to file
		printf("\n\n\n**************************\nint value = %d, dir = %d;\nfreqeuncy: %lfHz\n**************************\n\n\n", clock, dir, frequency); //Writes to STDOUT for user
		fclose(ff);

		//recompiling and flashing the board
		system("make flash"); //Uses the MAKEFILE
		sleep(5); //Allows the system child to finish

		//finding frequency
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
		avgFreq = 0; //Resets average

		//Adjusting clock
		if(frequency > 99.5 && frequency < 100.5) { //Checks for clock tolerance with in 0.5%
			printf("Clock is now calibrated\nFrequency: %lfHz\neeprom0 = %d \t eeprom1 = %d \n", frequency, clock, dir);
			return 0;
		} else
			clock++;

		if(clock > 255 || clock < 0) { //Ensures the value will not exced one byte
			printf("Clock hit bounds\n");
			return 1;
		}

	}
	return 0;
}
