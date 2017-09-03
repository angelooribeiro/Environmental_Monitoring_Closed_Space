/*
 * CGsm.h
 *
 *  Created on: 31/01/2017
 *      Author: hacked
 */

#ifndef CALARM_H_
#define CALARM_H_

#include "Header.h"

class CAlarm {
private:
    bool mb_buzzer_state;
    bool mb_button_state;
    void vChangeButtonState();


public:
	CAlarm();
	~CAlarm();
	static void vGetButtonState(void);
    static void * Alert(void* args);	//Behaviour for the Thread tAlert
    static void * AlertOff(void* args);	//Behaviour for the Thread tAlertOff
};

#endif /* CALARM_H_ */
