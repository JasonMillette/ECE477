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
void do_math_game(void);
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
	
	//forever
	while(1)
		do_math_game();

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
void do_math_game(void)
{
	FILE *fp, *fpr;
	int answer = 1, guess = 50, score = 0;
	
	fp = stdout;
	fpr = stdin;
	
	//tell user game has started 
	fprintf(fp, "Welcome to the Math Game!! \r\n");
		
	while (guess!=answer*answer)//run till user gets correct answer
	{
		//get random number for game
		answer = rand()%25; wil
		fprintf(fp,"\r\nWhat is %d squared: ", answer);
		while (fscanf(fpr,"%d",&guess) != 1) 
			fscanf(fpr,"%*s");//get input from user
		
		//see if correct anser and keep track of score 
		
		if(guess==(answer*answer)) 
		{
			score ++;//keep track of score
			fprintf(fp,"\r\nCorrect you are smart, Score %d",score);
		}
		else if ((guess > 625)||(guess < 0))//max is 625 for 25^2 
			fprintf(fp, "\r\nNumber needs to be between 0 and 625, Try again!");
		else 
			fprintf(fp,"WRONG Play again!!\r\n");
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
