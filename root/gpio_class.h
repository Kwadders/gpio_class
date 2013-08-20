#ifndef GPIO_CLASS_H
#define GPIO_CLASS_H

#include <string>

using namespace std;
/*GPIO Class
 *Each Object instantiated from this class will control a GPIO pin
 *The GPIO pin number must be passed to the overloaded class constructor
*/
class GPIOClass
{
public:
	GPIOClass();			//Create a GPIO object to control a GPIO
	GPIOClass(string x); 		//Create a GPIO object that controls GPIOx, where x is pass to this contructor
	int export_gpio();		//exports GPIO
	int unexport_gpio();		//unexport GPIO
	int setdir_gpio(string dir);	//set GPIO Direction
	int setval_gpio(string val);	//Set GPIO value 
	int getval_gpio(string& val);	//Get GPIO Value  output
	string get_gpionum();		//return the number associated with the instance of an object
private:
	string gpionum;			//GPIO number associated with the instance of an object
};
#endif
