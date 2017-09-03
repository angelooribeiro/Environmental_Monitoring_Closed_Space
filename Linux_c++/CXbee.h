//
// Created by hacked on 06-12-2016.
//

#ifndef EMBEDDED_PROJECT_CXBEE_H
#define EMBEDDED_PROJECT_CXBEE_H

#include "Header.h"

class CXbee{
private:
	void vInitUart();					//to initialize the UART
	void vCloseUart();					//to close the UART
    static void bReceiveXbee(int signum);  		//Receive the info from the XBee and make it available for the parse function

public:
    CXbee();                               		//Constructor that initialize the Serial Port
    ~CXbee();                              		//Deinitialize the Serial Port
    static void * ParseMessage(void* args);		//Behaviour for the Thread tReceiveXbee
}; //CXbee


#endif //EMBEDDED_PROJECT_CXBEE_H
