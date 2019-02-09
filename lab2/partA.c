//Steven Ferrarese
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
void setuppins(char *pins[]);
void append(char * x, char * xx);
void unexportpins(char * pins[]);
void setDirection(char * pins[]);
int export(char *);
int unexport(char *);
int direction(char *, char*);
int value(char *, char *);
int main(int argc, char ** argv)
{
	if(argc > 2)
	{
		printf("Too many arguments\n");
		return 3;
	}
	else if (argc < 2)
	{
		printf("Not enought arguments\n");
		return 4;
	}	
	int result = 0;	
	char * pins[] = {"8","9","7","0","2","3","12","13"};
	if (((argv[1][0]== '0')&&(argv[1][1]=='x')))
	{
		result = strtol(argv[1],NULL,16);
	}
	else 
	{
		result = atoi(argv[1]);
	}
	
	//setup
	setuppins(pins);
	usleep(1000000);
	setDirection(pins);
	usleep(1000000);

	value(pins[0],"1");

	for(int i = 0; i < 8; i++)
	{
	
		if(result &(0x01 << i ))
		{
			printf("1");
			value(pins[i],"1");
		}
		else
		{
			printf("0");
			value(pins[i],"0");
		}
	} 

	unexportpins(pins);		

	return 0;
}
void setuppins(char *pins[])
{
	int x;

	for (x = 0; x < 8; x++)
	{
		export(pins[x]);
	}
}
void setDirection(char *pins[])
{
	int x;
	for (x = 0; x < 8 ;x++)
	{
		direction(pins[x],"out");
	}
}
void unexportpins(char *pins[])
{
	int x;
	for(x = 0; x < 8; x++)
	{
		unexport(pins[x]);
	}

}
//sets up gpio files directory 
int export(char * pin)
{
	char cmd [150] = "cd /sys/class/gpio && echo ";
	
	append(cmd, pin);
	append(cmd, " > export");	
	
	//makes call on command line
	system(cmd);
	return 0;
}
//deletes the gpio pin file directory
int unexport(char * pin)
{
	char cmd [150] = "cd /sys/class/gpio && echo ";

	append(cmd, pin);
	append(cmd, " > unexport");	
	
	//run on command line
	system(cmd);
	
	return 0;
}
//sets direction of the gpio pin
int direction(char * pin, char * dir)
{
	//path to file creation
	char loc[35] = "/sys/class/gpio/gpio\0";

	append(loc, pin);
	append(loc,"/direction");
	
	//open file
	int file = open(loc,O_WRONLY);
	
	if (file < 0)//file not found
	{
		printf("Error direction file not found\n");
		return 2;
	}

	//open file
	int x = write(file,dir,strlen(dir));
	//error checking
	if (x != strlen(dir))
	{
		printf("could not write direction\n");	
	}
	close(file);
	return 0;
}
//sets value of gpio pin
int value(char * pin, char * val)
{
	
	char loc[35] = "/sys/class/gpio/gpio\0";

	append(loc,pin);
	append(loc,"/value");
	//open file
	int file = open(loc,O_WRONLY);
	//error checking
	if (file < 0)//file not found
	{
		printf("Error value file not found\n");
		return 2;
	}
	
	// write vale to file
	int x = write(file,val,strlen(val));
	
	if (x != strlen(val))
	{
		printf("could not write value\n");	
		return 1;
	}
	//cloase the file
	close(file);
	return 0;
}
void append(char * x, char * xx)
{
	int len = strlen(xx);
	int len2 = strlen(x);
	int i;
	for(i = 0; i < len; i++)
	{
		x[len2+i] = xx[i];
	}
	x[len2+i] = '\0';
}
