CC = gcc

all: rotate inputRotatePWM inputRotateDegree

rotate:
	gcc -o rotate rotate.c -lwiringPi

inputRotatePWM:
	gcc -o inputRotatePWM inputRotatePWM.c -lwiringPi

inputRotateDegree:
	gcc -o inputRotateDegree inputRotateDegree.c -lwiringPi

clean:
	rm -f *~ *.o rotate inputRotatePWM inputRotateDegree
