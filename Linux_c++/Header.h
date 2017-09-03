/*
 * Header.h
 *
 *  Created on: 24/01/2017
 *      Author: hacked
 */

#ifndef HEADER_H_
#define HEADER_H_

//Libraries
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <netdb.h>
#include <cstdlib>
#include <string.h>
#include <errno.h>      //number of last error
#include <array>
#include <mqueue.h>
#include <semaphore.h>
#include <pthread.h>		//Posix threads API
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include "wiringPi.h"		//wiringPi libraries
#include "softPwm.h"
#include "wiringSerial.h"
#include <wiringPiI2C.h>

//Include of all headers
#include "CXbee.h"
#include "CAlarm.h"
#include "CValues.h"
#include "CLcd.h"
#include "CWifi.h"

//Shared variables
extern mqd_t q_queue_sendwifi;
extern mqd_t q_queue_receivexbee;
extern mqd_t q_queue_display;
extern sem_t s_semaphore_createconnection;
extern sem_t s_semaphore_alarm;
extern sem_t s_semaphore_receivexbee;
extern sem_t s_semaphore_display;
extern sem_t s_semaphore_sendwifi;
extern sem_t s_semaphore_shutdown;
extern pthread_mutex_t m_mutex_parameters;

//Global defines
#define MAX_QUEUE_SIZE 	8192
#define BUFFER_SIZE 1024

//Global function
void SetupThread(int prio,pthread_attr_t *pthread_attr,struct sched_param *pthread_param);
#endif /* HEADER_H_ */
