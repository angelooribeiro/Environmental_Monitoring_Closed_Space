//
// Created by hacked on 06-12-2016.
//

#include "CXbee.h"

using namespace std;

//struct for the timer
struct itimerval itv;
//value of the serial port
static int i_fd;

//Used to control the acess to the queue q_queue_receivexbee
sem_t s_semaphore_receivexbee;
/*
 * Constructor
 */
CXbee::CXbee(){

	//Initialize the serial port
	vInitUart();

	//struc for the attributes of the queue
	struct mq_attr mq_attrb;
	// initialize the queue attributes
	mq_attrb.mq_flags = 0;		/* Flags: 0 or O_NONBLOCK */
	mq_attrb.mq_maxmsg = 20;	/* Max. # of messages on queue */
	mq_attrb.mq_msgsize = BUFFER_SIZE;		/* Max. message size (bytes) */
	mq_attrb.mq_curmsgs = 0;	/* # of messages currently in queue */

	if( mq_open("/q_queue_receivexbee", O_CREAT | O_RDWR | O_EXCL,
			S_IRWXU | S_IRWXG, &mq_attrb) == (mqd_t)-1)
	std::cout << "Error opening queue send receive xbee" << std::endl;

	//Initialize an signal that will trigger the read of data
    signal(SIGALRM, CXbee::bReceiveXbee);
    //to generate the signal every 2 secounds
    itv.it_interval.tv_sec = 2;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 2;
    itv.it_value.tv_usec = 0;
    //start
    setitimer(ITIMER_REAL, &itv, NULL);
}

/*
 * Initialize the serial port
 */
void CXbee::vInitUart(void){
    //Initialize the serial port and assign the usb terminal value to the fd
    if( (i_fd = serialOpen("/dev/ttyAMA0" ,9600)) < 0 ){
        //indicates the failure to connect
        cerr << "Unable to open Serial port to Xbee" << endl;
        exit(1);
    }
}

/*
 * Behaviour of the threat receive xbee
 */
void* CXbee::ParseMessage(void* args){
	//buffer to save the received message
	char received_buffer[BUFFER_SIZE+1] = {0};
	//used to auxiliate the parsing of each value
	char temp_buffer[10] = {0};
	//to run the buffer
	int i_buffer_index = 0;	//to run the buffer_index
	int i_temp_index = 0; //to run the temp_buffer

	int i_was_high = 10;
	int i_is_high = 0;

	//To access the objects of the class
	CValues* values_c = static_cast<CValues*>(args);
	unsigned int prio = 1;

	for(;;){
		//wait the semaphore until a new value is available
		sem_wait(&s_semaphore_receivexbee);

		//once the value is available read the queue
		q_queue_receivexbee = mq_open("/q_queue_receivexbee", O_RDONLY);
		if( q_queue_receivexbee == (mqd_t) -1 )
			perror("In mq_open()");
		if( mq_receive(q_queue_receivexbee,
			received_buffer,8192, &prio) == -1)
			perror("In mq_receive()");
		if( mq_close(q_queue_receivexbee) == -1)
			perror("In mq_close()");

		i_buffer_index = 0;
		//run the buffer to find the start character
		while( (received_buffer[i_buffer_index] != 'C') &&
			 (received_buffer[i_buffer_index] != '\n') &&
			 (i_buffer_index  < 63) ) i_buffer_index++;

		//to be tolerant to errors
		if((i_buffer_index < BUFFER_SIZE) &&
		  (received_buffer[i_buffer_index] != '\n')){

			i_temp_index = 0;//clear the temporary variables
			i_buffer_index++; //to jump over the letter
			//pass the value to another buffer to allow the conversion

			for(int i = 0; i<10; i++)
				temp_buffer[i] = '0';

			//find the terminator character == '+'
			while( (received_buffer[i_buffer_index] != '+') )
				temp_buffer[i_temp_index++] = received_buffer[i_buffer_index++];

			//if is a high value of CO2 post the semaphore to the thread alarm
			if( values_c->iCompareCO2( (float)atof(temp_buffer)) ){
				//To filter the possible noise
				if(i_is_high == 10)
					sem_post(&s_semaphore_alarm);

				i_was_high = 20;
				//If the alarm is already set do not set it again
				(i_is_high>=10) ? (i_is_high = 11) : (i_is_high++);

			} //If the value goes to low
			else{
				if(i_was_high == 1){
					//clear the flag to the next upper limit
					i_is_high = 0;
				}
				//if the value goes down that the limit
				(i_is_high<=1) ? (i_is_high = 0) : (i_is_high--);
			}
		}
		//Send the data to the thread display
		q_queue_display = mq_open("/q_queue_display", O_WRONLY);
		if( q_queue_display == (mqd_t) -1 )
			perror("In mq_open()");
		if( mq_send(q_queue_display,
			received_buffer,BUFFER_SIZE, 1) == -1)
			perror("In mq_receive()");
		if( mq_close(q_queue_display) == -1)
			perror("In mq_close()");
		std::cout << "inside" << std::endl;
		//clear the buffer
		memset(received_buffer, 0, sizeof(received_buffer));
		sem_post(&s_semaphore_display);
	}
	return NULL;
}


/*
 * Activated by the signal that comes from the timer
 * Save on the Queue the received values
 */
void CXbee::bReceiveXbee(int signum)
{
	char c_xbee_buffer[BUFFER_SIZE+1] = {0};
	int i_index = 0;

    if (serialDataAvail(i_fd))              					//If exists data available on the UART
    {
        do {
        	c_xbee_buffer[i_index++] = serialGetchar(i_fd);		//read the received character
        }while( ((c_xbee_buffer[i_index-2] != '\r') &&
        		(c_xbee_buffer[i_index-1] != '\n')) ||
				(i_index < 2));			//while there is data not the terminator character
        c_xbee_buffer[i_index] = '\n';							//Insert the terminator character

        fflush(stdin);											//clear the stdin

        q_queue_receivexbee = mq_open("/q_queue_receivexbee", O_WRONLY);
        if(q_queue_receivexbee == (mqd_t) -1)
        	perror("In mq_open()");
        if(mq_send(q_queue_receivexbee, c_xbee_buffer, BUFFER_SIZE, 1) == -1)
        	perror("In mq_receive()");
        if(mq_close(q_queue_receivexbee) == -1)
        	perror("In mq_close()");
        //clear the buffer
        memset(c_xbee_buffer, 0, sizeof(c_xbee_buffer));
		//post the semaphore to allow thread to execute
        sem_post(&s_semaphore_receivexbee);
    }

}

/*
 * Close the serial port connection
 */
void CXbee::vCloseUart(void){
	serialClose(i_fd);
}

/*
 * Destructor
 */
CXbee::~CXbee()
{
    //Close the serial port
    vCloseUart();
}
