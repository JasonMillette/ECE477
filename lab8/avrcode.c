#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#define __OPTIMIZE__ 2
#include <util/delay.h>
#include <math.h>

#define F_CPU 1000000UL

int serial_putchar(char, FILE*);
int serial_getchar(FILE *);
static FILE serial_stream = FDEV_SETUP_STREAM (serial_putchar, serial_getchar, _FDEV_SETUP_RW);

void init_serial(void);
void printInternalTemp(FILE *fp);
void update_clock_speed(void);
void init_ADC(void);
int read_ADC(void);

//main first calls update_clock_speed to make the adjustments to
//callibrate the clock. It then initializes UART communication with
//a raspberry pi. After the serial connection is made the ADC is
//initialized for the internal temp sensor.

int main()
{
  	update_clock_speed();  //adjust OSCCAL
	init_serial();
	init_ADC();

	//opens file for serial out
	FILE *fp;
	fp = stdout;

	while(1) {
		printInternalTemp(fp);
		_delay_ms(500);
	}
	
	//close file
	fclose(fp);

	return 0;
}

void init_serial(void) {
	//initializes the AVR USART for 1200 Baud with 8MHz clock
	
	UBRR0H=3;
	UBRR0L=80;
	UCSR0A = 1<<U2X0;
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);//8 bit, no parity and 2 stop
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);//enable Tx and Rx
	stdin =&serial_stream;
	stdout =&serial_stream;

}

void init_ADC(void) {
	//Initializes the ADC to use the internal 1.1V reference
	//and read the internal temperature sensor
	
	//MUX reset
	ADMUX = 0;

	//1.1V internal chosen as single input
	ADMUX |= (1<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);

	//internal temp sensor chosen as the reference voltage
	ADMUX |= (1<<REFS1)|(1<<REFS0);

	//the two MSB in ADCH, the 8 LSB in ADCL
	ADMUX |= (0<<ADLAR);

	//ADC enabled and prescaler set to 64
	//This is done so that 8MHz becomes 125kHz
	//So that the sampling is the most accurate
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);

	//ADC to finish init
	ADCSRA |= (1<<ADSC);
	while ((ADCSRA & (1<<ADSC)) != 0);	//waits for ADC to finish
	ADCSRA |= (1<<ADIF);	// Reset the flag

	return;
}

int read_ADC(void) {
	//Start ADC read
	ADCSRA |= (1<<ADSC);

	// Wait until ADC has been read
	while((ADCSRA & (1 << ADIF)) == 0);

	// Reset the flag
	ADCSRA |= (1<<ADIF);

	// Return ADC value
	return ADC;
}
//Example mosetly from class
void printInternalTemp(FILE *fp) {
	//Prints to serial out the internal temperature
	//usingn the internal temperature sensor
	//1.1V reference and ADC


	//Get value from the ADC
	float temperature = read_ADC();

	//Convert to F and print temperature
	fprintf(fp,"%f; ", (temperature-247)/1.22);

	return;
}

int serial_putchar(char val, FILE * fp) {
	//waits until UDR is empty and puts char

	while ((UCSR0A &(1<<UDRE0)) == 0 );
	UDR0 = val;
	return 0;

}

int serial_getchar(FILE *fp) {
	//waits until a char is avaailable and reads it 
	//if block read it will wait forever for a char
	//if multipe characters come at onces and not read they will be lost
	
	while((UCSR0A&(1<<RXC0)) == 0);// wait for char
	return UDR0;

}

void update_clock_speed(void) {
	//updating the clock speed 
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
