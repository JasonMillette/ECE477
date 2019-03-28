#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F_CPU 1000000UL
//#include <util/delay.h>


int serial_putchar(char, FILE*);
int serial_getchar(FILE *);
static FILE serial_stream = FDEV_SETUP_STREAM (serial_putchar, serial_getchar, _FDEV_SETUP_RW);

void init_serial(void);
void do_high_low(void);

//This code is distributed with no warranty expressed or implied.
//It does not contain any known bugs, but has not been tested.  
//What it is intended to do is use the first two bytes of eeprom
//as an offset and direction for adjusting the internal oscillator
//The first byte is an unsigned byte that is the amount to adjust 
//the OSCCAL register.  The next byte will be 0 or 1 depending on 
//whether the adjustment should be positive (0) or negative (1).
//The value 0xff is intentionally avoided to distinguish unprogrammed
//eeprom locations.

//main first calls update_clock_speed to make the adjustments to
//the oscillator calibration and then calls init_pwm to set up 
//a 100Hz 50% duty cycle square wave on OC1A (pin 15 on the 28 pin 
//DIP package).


int main()
{
	init_serial();
	//_delay_ms(2000);
	for(int i = 0; i < 100000;i++);
	while(1)
		do_high_low();

	return 0 ;

}

void init_serial(void)
{
	UBRR0H=0;
	UBRR0L=12;
	UCSR0A = 1<<U2X0;
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	stdin =&serial_stream;
	stdout =&serial_stream;

}

void do_high_low(void)
{
	FILE *fp, *fpr;
	int answer, guess;
	
	answer = rand()%10000;
	fp = stdout;
	fpr = stdin;

	fprintf(fp, "Welcome \r\n");
	fprintf(fp, "enter int \r\n");

	guess = answer+1;

	while (guess!=answer)
	{
		while (fscanf(fpr,"%d",&guess) != 1) fscanf(fpr, "%s*s");

		if(guess<answer) 
			fprintf(fp,"Too low, you need WEED");

		else if(guess > answer)
			fprintf(fp,"You got to High, you need some eye drops");

		else 
			fprintf(fp,"Congrats You acheieved the prefect level of WEEd");


	
	}

}

int serial_putchar(char val, FILE * fp)
{
	while ((UCSR0A &(1<<UDRE0)) == 0 );
	UDR0 = val;
	return 0;

}
int serial_getchar(FILE *fp)
{
	while((UCSR0A&(1<<RXC0)) == 0);
	return UDR0;

}
