/*
 * CWifi.h
 *
 *  Created on: 01/02/2017
 *      Author: hacked
 */

#ifndef CWIFI_H_
#define CWIFI_H_

#include "Header.h"

class CWifi {
private:
public:
	CWifi();
	~CWifi();
	static void * CreateConnection(void* args);
	static void * SendWifi(void* args);
	static void * ReceiveWifi(void* args);
};

#endif /* CWIFI_H_ */
