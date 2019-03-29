int value = 5, dir = 1;
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
//#include <avr/sleep.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#define __OPTIMIZE__ 2
#define F_CPU 1000000UL
#include <util/delay.h>


int serial_putchar(char, FILE*);
int serial_getchar(FILE *);
static FILE serial_stream = FDEV_SETUP_STREAM (serial_putchar, serial_getchar, _FDEV_SETUP_RW);

void init_serial(void);
void do_high_low(void);
void update_clock_speed(void);

//main first calls update_clock_speed to make the adjustments to
//the oscillator calibration and then calls init_pwm to set up 
//a 100Hz 50% duty cycle square wave on OC1A (pin 15 on the 28 pin 
//DIP package).
//This a high_low program runnin on the AVR chip
//it sets up the seial communication for 1200 baud

int main()
{
	//eeprom_write_byte((void *)0, value);
  	//eeprom_write_byte((void *)1, dir);
  	update_clock_speed();  //adjust OSCCAL
	init_serial();
	_delay_ms(2000);
	
	while(1)//do forever
		do_high_low();

	return 0 ;

}

//initializes the AVR USART for 1200 Baud with 8MHz clock
void init_serial(void)
{
	UBRR0H=828>>8;
	UBRR0L=127;
	UCSR0A = 1<<U2X0;
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);//8 bit, no parity and 2 stop
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);//enable Tx and Rx
	stdin =&serial_stream;
	stdout =&serial_stream;

}
//Examole mosetly from class
//High log game c
//randomly generates number and had User guess it and telling them lower or higher
//
void do_high_low(void)
{
	FILE *fp, *fpr;
	int answer, guess;
	
	answer = rand()%10000;
	fp = stdout;
	fpr = stdin;

	//print out to tell user game has starteed
	fprintf(fp, "\r\nWelcome to the High low Game!! \r\n");
		
	fprintf(fp, "Enter an int between 0 and 10000: \r\n");

	while (guess!=answer)//go till user gets correct answer
	{
		
		while (fscanf(fpr,"%d",&guess) != 1) //get answer from user
			fscanf(fpr,"%*s");		
		if(guess<answer) 
			fprintf(fp,"\r\nToo low!! Try again\r\n");

		else if(guess > answer)
			fprintf(fp,"\r\nYou got to High! Try again\r\n");
		else 
			fprintf(fp,"\r\nCongrats You got it!\r\n");
	}

}
//waits until UDR is empty and puts char
int serial_putchar(char val, FILE * fp)
{
	while ((UCSR0A &(1<<UDRE0)) == 0 );
	UDR0 = val;
	return 0;

}
//waits until a char is avaailable and reads it 
//if block read it will wait forever for a char
//if multipe characters come at onces and not read they will be lost
int serial_getchar(FILE *fp)
{
	while((UCSR0A&(1<<RXC0)) == 0);// wait for char
	return UDR0;

}
//updating the clock speed 
void update_clock_speed(void)
{
  char temp;
  temp=eeprom_read_byte((void *)1); //read oscillator offset sign 
                                    //0 is positive 1 is  negative
                                    //erased reads as ff (so avoid that)
  if(temp==0||temp==1)      //if sign is invalid, don't change oscillator
  {
      if(temp==0)
	  {
	     temp=eeprom_read_byte((void *)0);
		 if(temp != 0xff) OSCCAL+=temp;
	  }
	  else
	  {
	     temp=eeprom_read_byte((void *)0);
		 if(temp!=0xff) OSCCAL -=temp;
	  }
  }
}
