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
#include <math.h>


int serial_putchar(char, FILE*);
int serial_getchar(FILE *);
static FILE serial_stream = FDEV_SETUP_STREAM (serial_putchar, serial_getchar, _FDEV_SETUP_RW);

void init_serial(void);
void LED_and_voltage(void);
void update_clock_speed(void);
void init_ADC(void);
int read_ADC(void);

//main first calls update_clock_speed to make the adjustments to
//the oscillator calibration and then calls init_pwm to set up 
//a 100Hz 50% duty cycle square wave on OC1A (pin 15 on the 28 pin 
//DIP package).
//This a high_low program runnin on the AVR chip
//it sets up the seial communication for 1200 baud

int main()
{
  	update_clock_speed();  //adjust OSCCAL
	init_serial();
	_delay_ms(2000);
	
	// Lights up LEDs and calculates reference voltage
	LED_and_voltage();

	return 0;
}

//initializes the AVR USART for 1200 Baud with 8MHz clock
void init_serial(void)
{
	UBRR0H=3;
	UBRR0L=80;
	UCSR0A = 1<<U2X0;
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);//8 bit, no parity and 2 stop
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);//enable Tx and Rx
	stdin =&serial_stream;
	stdout =&serial_stream;

}

void init_ADC(void)
{
	// MUX reset
	ADMUX = 0;

	// 1.1V internal chosen as single input
	ADMUX |= (1<<MUX3)|(1<<MUX2)|(1<<MUX1);

	// AVcc chosen as the reference voltage
	ADMUX |= (1<<REFS0);

	// ADC enabled and prescaler set to 64
	// This is done so that 8MHz becomes 125kHz
	// So that the sampling is the most accurate
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);
}

int read_ADC(void)
{
	//Start ADC read
	ADCSRA |= (1<<ADSC);

	// Wait until ADC has been read
	while((ADCSRA & (1 << ADIF)) == 0);

	// Reset the flag
	ADCSRA |= (1<<ADIF);

	// Return ADC value
	return ADC;
}
//Examole mosetly from class
//High log game c
//randomly generates number and had User guess it and telling them lower or higher
//
void LED_and_voltage(void)
{
	FILE *fp, *fpr;
	
	fp = stdout;
	fpr = stdin;

	// Variables for LEDs and
	// supply calculation
	int guess = 0;
	float in = 1.1; // 1.1 internal input voltage
	float out = 0;
	float supply;
	unsigned int LEDdisplay = 0;
	int display = 0;

	DDRB |= 0xFF; // Direction data registor for D set to outputs

	init_ADC(); // Initialize the ADC
		
	while (1)//run forever
	{		
		// Inform user that the ADC is being read
		fprintf(fp,"\r\nReading ADC!");

		// Read ADC
		out = read_ADC();

		// Calculate the supply voltage
		supply = (in * 1024.0) / out;

		// Tell user what the power rail is
		fprintf(fp,"\r\nThe power rail is %f Volts", supply);

		// Assuming 5V max, convert to LEDs
		// with the highest LED being the eigth
		LEDdisplay = (unsigned int)(supply * 1.6);

		// Set a 1 for each LED based on 1.6*supply voltage
		// ex. 1V is first LED, 2V is second LED, and so on.
		for(int i = 0; i < LEDdisplay; i++)
		{
			display |= (1 << i);
		}		
	
		// Print voltage level
		fprintf(fp,"\r\nThe voltage level is %d", LEDdisplay);

		// Display Voltage Supply Level
		PORTB |= display;
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
