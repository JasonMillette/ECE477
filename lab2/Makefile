CC = gcc
CFLAGS = -Wall -g

all:	partA partB

partA:		partA.o
		$(CC) -o partA partA.o

partA.o:	partA.c
		$(CC) $(CFLAGS) -c partA.c
		
partB:		
		gcc partB.c -o partB -lwiringPi

clean:
		rm -f *~ *.o partA partB
