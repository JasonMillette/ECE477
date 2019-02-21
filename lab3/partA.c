//ECE477 Lab3
//2/21/19
//Jason Millette, Spencer Goulette, Steven Ferrarese

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	FILE *ff;
	ff = fopen("prov/loadavg", "r");

	if (ff < 0)
	{
		printf("Error opening program\n");
		return 4;
	}

	float input = 0;
	char loadavg[6];
	while(1)
	{
		fopen(loadavg,5,ff);
		
		input = atof(loadavg);	
		
		printf("%s\n%lf\n", loadavg,input);
		if (input < 0.125)
			system("./led 0x01");
		else if (input < 0.25)
			system("./led 0x03");
		else if (input < 0.5)
			system("./led 0x07");
		else if (input < 1)
			system("./led 0x0F");
		else if (input < 2)
			system("./led 0x1F");
		else if (input < 4)
			system("./led 0x3F");
		else if (input < 8)
			system("./led 0x7F");
		else 
			sytem("./led 0xFF");
		
		sleep(10);
	}
	fclose(ff);
	return 0;
}




