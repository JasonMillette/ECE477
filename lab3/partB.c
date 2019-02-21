//ECE477 Lab3
//2/21/19
//Jason Millette, Spencer Goulette, Steven Ferrarese

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	//Opening /proc/loadavg to read the 1 minute load average
	FILE *ff;
	ff = fopen("/proc/stat", "r");
	if (ff < 0) //error checking on file open
	{
		printf("Error opening program\n");
		return 4;
	}

	//float value and string
	float input = 0;
	char loadavg[1000];

	while(1) //infinite loop to check value every ten seconds and call led function
	{
		fgets(loadavg, 1000, ff); //gets the first 5 characters of the file
		sscanf(loadavg, "proc_running %lf", &input);	//Converts string to float
		
		printf("process running %lf\n",input); //Prints variables for debugging
	
		//Different cases for loadavg
		fgets(loadavg,5,ff);
		
		input = atof(loadavg);	
		
		printf("%s\n%lf\n", loadavg,input);
		if (input == 1)
			system("./led 0x01");
		else if (input == 2)
			system("./led 0x03");
		else if (input == 3)
			system("./led 0x07");
		else if (input == 4)
			system("./led 0x0F");
		else if (input == 5)
			system("./led 0x1F");
		else if (input == 6)
			system("./led 0x3F");
		else if (input == 7)
			system("./led 0x7F");
		else if (input == 8)
			system("./led 0xFF");
		
		sleep(10);
	}
	fclose(ff);
	return 0;
}




