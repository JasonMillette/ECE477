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
	//int value and string
	int input = 0;
	char line[256];
	size_t * xx ;
	while(1) //infinite loop to check value every ten seconds and call led function
	{
		
		
		ff = fopen("/proc/stat", "r");//open file	
		if(ff < 0)//error check on file open
		{
			printf("error opening program\n");
			return 4;//end program
		}
		
		for (int i = 0; i < 11 ; i++)//go to 11th line and save it
			fgets(line, sizeof(line),ff);
	
		fclose(ff);//close file
		
		sscanf(line, "procs_running %d", &input);//get number of processing running from line
		printf("%s  %d\n",line,input);//print out output


		//print the number of process running 
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
		
		sleep(10);//delay 10 seconds
	}
	return 0;
}




