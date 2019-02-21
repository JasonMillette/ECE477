CC = gcc
CFLAGS = -Wall -g

all:	led partA

led:
		gcc led.c -o led -lwiringPi

partA:		
		gcc partA.c -o partA -lwiringPi

clean:
		rm -f *~ *.o led partA
