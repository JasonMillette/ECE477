all:
	avr-gcc -Wl,-u,vfprintf -lprintf_flt -lm -mmcu=atmega88 avrcool.c
	avr-objcopy -j .text -j .data -O ihex a.out a.hex

fuse:
	sudo avrdude -C ~/avrdude_gpio.conf -c pi_1 -p atmega88 -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m

flash:
	avr-gcc -Wl,-u,vfprintf -lprintf_flt -lm -mmcu=atmega88 avrcode.c
	avr-objcopy -j .text -j .data -O ihex a.out a.hex
	sudo avrdude -C ~/avrdude_gpio.conf -c pi_1 -p atmega88 -U flash:w:a.hex:i

terminal:
	sudo avrdude -C ~/avrdude_gpio.conf -c pi_1 -p atmega88 -t

clean: 
	rm -rf a.hex a.out
