CC = gcc
CFLAGS = -02 -Wall -g

all:	partA partB

partA:		partA.o
		$(CC) -o partA partA.o

partA.o:	partA.c
		$(CC) $(CFLAGS) -c partA.c
		
partB:		partB.o
		$(CC) -o partB partB.o

partB.o:	partB.c
		$(CC) $(CFLAGS) -c partB.c
		
clean:
		rm -f *~ *.o partA partB
