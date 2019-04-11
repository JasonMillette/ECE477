//ECE486 Lab6
//4/20/19
//Jason Millette, Spencer Goulette, Steven Ferrarese
//Credits, Bruce Segee
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void from_to(int ,int);
void setup_stdin(void);

int init(void);



 int main()
 { int fd1; //variables
   char buf[1000];
   setup_stdin();
   fd1=init();
   //Forks for reading from stdin and from UART
   if(fork()) from_to(fd1,1);
   else from_to(0,fd1);

   return 1;
 }

void setup_stdin(void)
//Sets up serial communication from stdin to the AVR
{ struct termios tc; //Creates termios structure
   tcgetattr(0, &tc); //gets the attributes of the terminal device and sets it to the structure
   tc.c_lflag &=~ICANON ; //disables canonical mode
   tc.c_lflag |=ECHO; //enables echo
   tcsetattr(0, TCSANOW, &tc); //writes out the attributes to the terminal device
}


void from_to(int f1, int f2)
//Sends data either to the AVR from stdin or from the AVR to stdout.
{  char c;
   while(1) if(read(f1,&c,1))write(f2,&c,1);  } //waits for input either from stdin or AVR

  int  init()
  {
    int fd1;
    struct termios tc;                // terminal control structure

    fd1 = open("/dev/ttyS0", O_RDWR|O_NOCTTY);  // really ought to check for error
    if(fd1 < 0) {
	    fprintf("Error opening terminal device\n");
	    return 1;
    }
    tcgetattr(fd1, &tc); //gets the attributes of the terminal device and sets it to the structure
    tc.c_iflag = IGNPAR; //sets flag to ingore the parity and framing errors 
    tc.c_oflag = 0; //clears all flags pertaining to how the system handles outputs
    tc.c_cflag = CSTOPB | CS8 | CREAD | CLOCAL; //8 bit chars enable receiver no modem status lines
    tc.c_lflag =0 ; //clears all flags pertaining to various terminal functions

    cfsetispeed(&tc, B1200); //Sets the input and output baud rates
    cfsetospeed(&tc, B1200);
    tcsetattr(fd1, TCSANOW, &tc); //writes out the attributes to the terminal device
  return fd1; //returns terminal device file
 }
