#include <iostream> 	//allow for reading in/out from a file
#include <unistd.h>
#include <errno.h> 	//allow error handling
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include "gpio_class.h"

using namespace std;
///DEBUG DEFINES
//#define TEST_LEDS


#define RED_LED 	"17"
#define AMBER_LED	"18"
#define	GREEN_LED	"22"

//Traffic light state machine defines
#define STATE_GREEN		0
#define	STATE_AMBER		1
#define STATE_RED		2
#define STATE_AMBER_FLASHING	3

#define TICK	1 //state machine tick time

#define LED_ON	"1"
#define LED_OFF	"0"

//main
int main (void)
{
	string inputstate;
	int cycles, i, State;

	//Create new GPIO object to be attacted to GPIO 17
	GPIOClass* RedLed = new GPIOClass(RED_LED);
	GPIOClass* AmberLed = new GPIOClass(AMBER_LED);
	GPIOClass* GreenLed = new GPIOClass(GREEN_LED);

	//export GPIO 17
	RedLed->export_gpio();
	AmberLed->export_gpio();
	GreenLed->export_gpio();

	//reset # of cycles to count from 0
        cycles = 0;
	i = 0;	//reset loop counter

	RedLed->setdir_gpio("out"); 	//Set Red LED pin as output
	AmberLed->setdir_gpio("out");	//Set Amber LED pin as output
	GreenLed->setdir_gpio("out");	//Set Green LED pin as output

	cout << "***TRAFFIC LIGHT SYSTEM***"<<endl;

	inputstate = "0";
	State = STATE_GREEN;

	while(1)
	{
		//clear screen
		cout << "\033[2J\033[1;1H";
#ifdef TEST_LEDS
		while(1)
		{
                        RedLed->setval_gpio(LED_ON);
                        AmberLed->setval_gpio(LED_ON);
                        GreenLed->setval_gpio(LED_ON);
		}
#endif

        	RedLed->setval_gpio(LED_OFF);
        	AmberLed->setval_gpio(LED_OFF);
        	GreenLed->setval_gpio(LED_OFF);

		//inputstate = (inputstate == "0")?"1":"0";
		switch(State)
		{
		case STATE_GREEN:
			GreenLed->setval_gpio(LED_ON);
			cout<<"\n\nGREEN"<<endl;
			State = STATE_AMBER;
			sleep(10*TICK);
			break;
		case STATE_AMBER:
                         AmberLed->setval_gpio(LED_ON);
                        cout<<"\nAMBER"<<endl;
			State = STATE_RED;
			sleep(2*TICK);
			break;
		case STATE_RED:
                        RedLed->setval_gpio(LED_ON);
                        cout<<"RED"<<endl;
			State = STATE_AMBER_FLASHING;
			sleep(5*TICK);
			break;
		case STATE_AMBER_FLASHING:
			i=0;
			while(i++<5)
			{
				usleep(500000);
				cout << "\033[2J\033[1;1H";
				cout<<"\nAMBER FLASHING"<<endl;
				AmberLed->setval_gpio(LED_ON);
				usleep(500000);
				cout <<"\033[2J\033[1;1H";
				cout<<"\nAMBER"<<endl;
				AmberLed->setval_gpio(LED_OFF);
			}
			State = STATE_GREEN;
			break;
		default:
			cout <<"ERROR:INVALID STATE"<<endl;
			State = STATE_RED; //Reset state machine
			sleep(2);
			break;
		}
	}
}
