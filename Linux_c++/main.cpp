
//
// Created by hacked on 09-12-2016.
//

#include "Header.h"


/*Queues Declaration
*Queue for sent information on using WiFi
*Used by thread receivexbee and alertoff
*/
mqd_t q_queue_sendwifi;
//Establish communication to the thread ReceiveXbee
mqd_t q_queue_receivexbee;
//Establish communication to the thread Display
mqd_t q_queue_display;

//Semaphores Declaration
//to allow the thread display execute
sem_t s_semaphore_display;
//Used by thread alarm, posted by thread RecebeXbee
sem_t s_semaphore_alarm;
//to shut down the alarm
sem_t s_semaphore_shutdown;
//Used in thread create connection
sem_t s_semaphore_createconnection;
//used to enable a send using wifi
sem_t s_semaphore_sendwifi;

//Mutex Declaration
//Manage the acess to parameters
pthread_mutex_t m_mutex_parameters;


/*
 * Structs to pass the arguments to the thread
 */
struct sDisplay_args{
	CLcd *p_clcd;
	CValues *p_cvalues;
};

void SetupThread(int prio,pthread_attr_t *pthread_attr,struct sched_param *pthread_param)
{
    // Calculate and/or assign priority value to sched_param structure
    pthread_param-> sched_priority = prio;

    //scheduling policy
    pthread_attr_setschedpolicy (pthread_attr,SCHED_RR);

    //set scheduling param
    pthread_attr_setschedparam(pthread_attr,pthread_param);

    //set scheduling attributes to be determined by attributes object
    pthread_attr_setinheritsched(pthread_attr, PTHREAD_EXPLICIT_SCHED);
}

void vInitializeSynchronization(void);

int main(){

	//Initialize all the synchronization objects of the system
	vInitializeSynchronization();

	//Instances of the Classes
    CValues * p_cvalues_instance = new CValues;
    CXbee * p_cxbee_instance = new CXbee;
    CAlarm * p_calarm_instance = new CAlarm;
    CLcd * p_clcd_instance = new CLcd;
    CWifi * p_cwifi_instance = new CWifi;

    //Structs to be passed as arguments to the threads
    sDisplay_args sdisplay_args;
    sdisplay_args.p_clcd = p_clcd_instance;
    sdisplay_args.p_cvalues = p_cvalues_instance;

    //Declaration of the threads
    pthread_t tReceiveXbee;
    pthread_t tAlarm;
    pthread_t tDisplay;
    pthread_t tSendWifi;
	pthread_t tCreateConnection;
	pthread_t tReceiveWifi;
	pthread_t tAlarmOff;

    //Initialization of the threads
    pthread_attr_t thread_attr;
    int thread_policy;
    struct sched_param thread_param;
    pthread_attr_init (&thread_attr);
    pthread_attr_getschedpolicy (&thread_attr, &thread_policy);
    pthread_attr_getschedparam (&thread_attr, &thread_param);


    //Creation of threads
    SetupThread(90,&thread_attr,&thread_param);
    if(pthread_create(&tAlarm, &thread_attr, &CAlarm::Alert, &p_cvalues_instance) ){
    	std::cout << "Error:unable to create thread Alarm," << std::endl;
   		return -1;
    }

    SetupThread(80,&thread_attr,&thread_param);
    if(pthread_create(&tReceiveXbee, &thread_attr, &CXbee::ParseMessage, &p_cvalues_instance) ){
    	 std::cout << "Error:unable to create thread ReceiveXbee," << std::endl;
    	 return -1;
    }

    SetupThread(70,&thread_attr,&thread_param);
    if(pthread_create(&tDisplay, &thread_attr, &CLcd::Display, &sdisplay_args) ){
    	std::cout << "Error:unable to create thread SendWifi," << std::endl;
   		return -1;
    }

    SetupThread(70,&thread_attr,&thread_param);
    if(pthread_create(&tSendWifi, &thread_attr, &CWifi::SendWifi, NULL) ){
    	return -1;
    	std::cout << "Error:unable to create thread SendWifi," << std::endl;
    }
    SetupThread(60,&thread_attr,&thread_param);
    if(pthread_create(&tReceiveWifi, &thread_attr, &CWifi::ReceiveWifi,&p_cvalues_instance) ){
    	std::cout << "Error:unable to create thread ReceiveWifi," << std::endl;
    	return -1;
    }

    SetupThread(60,&thread_attr,&thread_param);
    if(pthread_create(&tAlarmOff, &thread_attr, &CAlarm::AlertOff, NULL) ){
    	std::cout << "Error:unable to create thread ReceiveWifi," << std::endl;
    	return -1;
    }

    SetupThread(50,&thread_attr,&thread_param);
    if(pthread_create(&tCreateConnection, &thread_attr, &CWifi::CreateConnection, NULL) ){
    	std::cout << "Error:unable to create thread CreateConnection," << std::endl;
    	return -1;
    }

    //detach of the threads
    pthread_detach(tReceiveXbee);
    pthread_detach(tAlarm);
    pthread_detach(tDisplay);
    pthread_detach(tSendWifi);
    pthread_detach(tReceiveWifi);
    pthread_detach(tCreateConnection);

    while(1);
    //delete the instances created
    delete p_cvalues_instance;
    delete p_cxbee_instance;
    delete p_calarm_instance;
    delete p_clcd_instance;
    delete p_cwifi_instance;

    mq_unlink("/q_queue_sendwifi");
    mq_unlink("/q_queue_receivexbee");
	mq_unlink("/q_queue_alarm");
	//mq_unlink();
    return 0;
}


void vInitializeSynchronization(void){
	/* Synchronization objects initialization
	*Initialize Queues
	*O_CREATI if the files do not exist, creates it
 	*if created fail
	*Read write by owner and group
	*/

	//struct for the attributes of the queue
	struct mq_attr mq_attrb;
	// initialize the queue attributes
	mq_attrb.mq_flags = 0;		/* Flags: 0 or O_NONBLOCK */
	mq_attrb.mq_maxmsg = 100;	/* Max. # of messages on queue */
	mq_attrb.mq_msgsize = BUFFER_SIZE;		/* Max. message size (bytes) */
	mq_attrb.mq_curmsgs = 0;	/* # of messages currently in queue */

	if( mq_open("/q_queue_display", O_CREAT | O_RDWR | O_EXCL,
			S_IRWXU | S_IRWXG, &mq_attrb) == (mqd_t)-1)
		std::cout << "Error opening queue display" << std::endl;

	if( mq_open("/q_queue_sendwifi",  O_CREAT | O_RDWR | O_EXCL,
			S_IRWXU | S_IRWXG, &mq_attrb) == (mqd_t)-1)
		std::cout << "Error opening queue send wifi" << std::endl;

	//Initialize Semaphore
	//Not shared between processes, initial value = 0
	sem_init (&s_semaphore_createconnection,0,0);
	sem_init (&s_semaphore_alarm, 0, 0);
	sem_init (&s_semaphore_receivexbee, 0, 0);
	sem_init (&s_semaphore_display, 0, 0);
	sem_init (&s_semaphore_shutdown, 0, 0);
	sem_init (&s_semaphore_sendwifi, 0, 0);
	//Initialize Mutex
	m_mutex_parameters = PTHREAD_MUTEX_INITIALIZER;

}
