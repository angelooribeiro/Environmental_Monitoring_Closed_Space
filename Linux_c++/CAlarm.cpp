/*
 * CGsm.cpp
 *
 *  Created on: 31/01/2017
 *      Author: hacked
 */

#include "CAlarm.h"

struct sAlert_args{
	CValues *p_cvalues;
	CAlarm *p_calarm;
};

void CAlarm::vGetButtonState(void)
{
    sem_post(&s_semaphore_shutdown);
}

void func(void) {};

CAlarm::CAlarm() {

	//initialization of the member variables
	mb_buzzer_state = 0;
	mb_button_state = 0;
	//Initialization of the wiringpi
    if(wiringPiSetup() < 0){        //if the setup fails
        std::cerr << "wiringPi fail" << std::endl;
        return;
    }

	//defined as GPIO26 in the wiring Pi library
	softPwmCreate (26,0,4);		//Initialize the port as output
	softPwmWrite (26, 0);		//change the state of the port do deactivated

	//Configuration of the port as an interrupt
    if ( (wiringPiISR(21, INT_EDGE_RISING, &vGetButtonState )) < 0 ) {
            fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
            return;
    }
}

//Behaviour for thread alert
void* CAlarm::Alert(void* args)
{
	char message[BUFFER_SIZE+1] = "BF\0";

	//To access the objects of the classes
	CValues* CValues_Instance = static_cast<CValues*>(args);

	//array to save the number
	char c_phone_number[9] = {0};
	char * p_phone_number = NULL;

	for(;;){

		//If is possible acquire the semaphore
		sem_wait(&s_semaphore_alarm);

		std::cout << "alarm activated" << std::endl;
		//Is a situation of alarm
		  softPwmWrite(26, 2);   	//activate the buzzer
		//get the phone number
		p_phone_number = CValues_Instance->sGetNumber();
		for(int i = 0; i < 9; i++)
		//move to the next position but reads the old content
			c_phone_number[i] = *(p_phone_number)++;
			/*
			 *
			 * Send the alert using GSM
			 * Place the code here
			 *
			 *
			 */
		//Send the data to the thread display
		q_queue_sendwifi = mq_open("/q_send_wifi", O_WRONLY);
		if( q_queue_display == (mqd_t) -1 )
			perror("In mq_open()");
		if( mq_send(q_queue_sendwifi,
			message,BUFFER_SIZE, 1) == -1)
			perror("In mq_receive()");
		if( mq_close(q_queue_sendwifi) == -1)
			perror("In mq_close()");
		//clear the buffer
		memset(message, 0, strlen(message));
		sem_post(&s_semaphore_sendwifi);
	} //end for

}

//Behaviour for thread alert
void* CAlarm::AlertOff(void* args)
{
	char message[BUFFER_SIZE+1] = "BF\0";
	for(;;){

		//If is possible acquire the semaphore
		sem_wait(&s_semaphore_shutdown);
		  softPwmWrite(26, 0);   	//shutdown buzzer
	} //end for

	//Send the data to the thread display
	q_queue_sendwifi = mq_open("/q_send_wifi", O_WRONLY);
	if( q_queue_display == (mqd_t) -1 )
		perror("In mq_open()");
	if( mq_send(q_queue_sendwifi,
		message,BUFFER_SIZE, 1) == -1)
		perror("In mq_receive()");
	if( mq_close(q_queue_sendwifi) == -1)
		perror("In mq_close()");
	//clear the buffer
	memset(message, 0, strlen(message));
	sem_post(&s_semaphore_sendwifi);
	return NULL;
}

CAlarm::~CAlarm() {

}

