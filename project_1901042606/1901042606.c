#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdint.h>   /* Standard types */
#include <sys/ioctl.h>
#include <getopt.h>

/* Emre YILMAZ 1901042606 GTU */

int main(){

	
	
	int portName = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY); //Open communication with arduino

	/*struct termios options;
	tcgetattr(portName, &options);
	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);
	options.c_cflag |= (CLOCAL | CREAD);
	tcsetattr(portName, TCSANOW, &options);

	//8 bit characters
	options.c_cflag &= ~CSIZE; // Mask the character size bits 
	options.c_cflag |= CS8;    // Select 8 data bits 
	
	//No parity
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;*/

	printf("## WELCOME TO GTU ARDUINO LAB ##\n## EMRE YILMAZ ##\n## PLEASE SELECT FROM THE FOLLOWING ##\n## MENU:\n(1) TURN ON LED ON ARDUINO\n(2) TURN OFF LED ON ARDUINO\n(3) FLASH ARDUINO LED 3 TIMES\n(4) SEND A NUMBER TO ARDUINO TO COMPUTE SQUARE BY ARDUINO\n(5) BUTTON PRESS COUNTER\n(0) EXIT");
	
	while(1)
	{

		printf("\nPLEASE SELECT:\n");
		char choose[1]; // String will keep the user's 'Menu Choice'
		scanf("%s",choose); // Take input from user for menu choice
	
		if(strcmp(choose,"0")==0) // CASE Choice '0'
		{
			printf("\nGOOD BYE!");
			return 1;
		}
	
		else if (strcmp(choose,"1")==0) // CASE: Choice '1'
		{
			write(portName,"1",1); // Sending the choice(1) to Arduino
			printf("LED IS TURNED ON!\n"); // Information message
		}
	
		else if (strcmp(choose,"2")==0) // CASE: CHOICE '2'
		{
			write(portName,"2",1); // Sending the choice (2) to Arduino
			printf("LED IS TURNED OFF!\n"); // Information message
		}
	
		else if (strcmp(choose,"3")==0) // CASE: CHOICE '3'
		{
			write(portName,"3",1); // Sending the choice (3) to Arduino
			printf("LED IS FLASHING 3 TIMES!\n"); // INFORMATION MESSAGE
		}
	
		else if  (strcmp(choose,"4")==0) // CASE: CHOICE '4'
		{	
			write(portName,"4",1); // Sending the choice (4) to Arduino
			printf("Enter your number, please: \n");
			char number[3]; // This array will keep the number to be squared 
			scanf("%s",number); // Take input(number to be squared) from user
			char answer[5]; // This array will keep the answer that come from arduino(square of user's input)
			
			sleep(1); // WAIT 2 SEC.				
			write(portName,number,3); // Sending the user's number to Arduino(to be squared)				
			sleep(3); // WAIT 3 SEC.
			read(portName, answer, 5); // Reading the number that come from Arduino(calculated answer)
			printf("Square of your number: %s\n",answer); // Information message
			memset(answer,0,strlen(answer)); //cleaning
			sleep(1);
			
		}
		else if  (strcmp(choose,"5")==0) // CASE: CHOICE '5'
		{	
			int ct = 0; // This variable counts the button press
			int choice = 0; // This variable indicates 'button counting' will go on or not.
			while(choice==0)
			{
			
			sleep(1/10); // WAIT 1 SEC.
			write(portName,"5",1); // Sending the choice (5) to Arduino
			char answer[2]; // This array keeps the answer of arduino.
			sleep(4); // WAIT 2 SEC.
			read(portName,answer,2); // Reading the answer that come from Arduino. If answer is "1", it means button is pressed. If answer is "0", it means button is not pressed.
			if(answer[0] == '1')
			{
				ct++; // If button pressed, increase ct.
			}
	
			if(answer[0] == '0'); // If button is not pressed, do nothing.
	
			printf("BUTTON COUNTER => %d\n",ct); // Information message
			printf("DO YOU WANT TO STOP(1) OR GO ON(0) ?\n"); 		
			scanf("%d",&choice);
			memset(answer,0,strlen(answer)); //cleaning
	
			}		
		}
	
		else
		{
			printf("Please enter a valid number.\n");
			continue;		
		}
	}
	close(portName);
}
