/*
 * CWifi.cpp
 *
 *  Created on: 01/02/2017
 *      Author: hacked
 */

#include "CWifi.h"

volatile static int socket_fd;

CWifi::CWifi() {
    sem_post(&s_semaphore_createconnection);
}


void* CWifi::CreateConnection(void* args){
    struct hostent* host;
	struct sockaddr_in addr;

	for(;;){
		//wait the semaphore that enables the send of data
		sem_wait(&s_semaphore_createconnection);
		//get the server ip
		host = gethostbyname("192.168.43.164");
		//create the socket and connect
		if((socket_fd = socket(PF_INET, SOCK_STREAM, 0))< 0)
			std::cout << "error socket" << std::endl;
		memset(&addr, 0, sizeof(addr));       // create & zero struct
		addr.sin_family = AF_INET;        		//select the Internet protocol
		addr.sin_port =  htons(1234);                       //assign the port to the socket
		addr.sin_addr.s_addr = *(long*)(host->h_addr_list[0]);  //set the address

		//connect and test the connection
		if ( connect(socket_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
			std::cout << "No connection" << std::endl;
	}

	return NULL;
}

void* CWifi::SendWifi(void* args){

	//buffer to read the queue and send using the socket
	char send_buffer[BUFFER_SIZE + 1] = {0};
	unsigned int prio = 1;
	int i_send_result = 0 ;
	for(;;){
		//wait the semaphore
		sem_wait(&s_semaphore_sendwifi);
		//read the queue
		q_queue_sendwifi = mq_open("/q_queue_sendwifi", O_RDONLY);
		if( q_queue_sendwifi == (mqd_t) -1 )
			perror("In mq_open()");
		if( mq_receive(q_queue_sendwifi,
			send_buffer,8192, &prio) == -1)
			perror("In mq_receive()");
		if( mq_close(q_queue_receivexbee) == -1)
			perror("In mq_close()");
		//send the message using TCP
		i_send_result = send(socket_fd,send_buffer,strlen(send_buffer),0);
	    //clear the buffer
	    memset(send_buffer, 0, sizeof(send_buffer));

	    //the system was not able to send
	    if(i_send_result == 0)
		//post semaphore to execute thread send wifi
		sem_post(&s_semaphore_createconnection);
	}
	return NULL;
}

void* CWifi::ReceiveWifi(void* args){
	//buffer to read the messages
	char received_buffer[1000] = {0};
	//cast to allow the access to change the parameters
	CValues* values_c = static_cast<CValues*>(args);

	for(;;){
		SValues s_newvalues;

	//while there is messages
	int size = strlen(received_buffer);
	while( read(socket_fd,received_buffer,size) > 0){
		for(int i = 0; received_buffer[i] != '\0'; i++)
			std::cout << received_buffer[i];
		std::cout << std::endl;
		//start the parse
	    //if is a message to shutdown the system
	    if( (received_buffer[0] == 'B') && (received_buffer[1] == 'O') )
	    	sem_post(&s_semaphore_shutdown);

	    //if is a message with new values
	    if(received_buffer[0] == 'N') {
	    	if(received_buffer[1] == 'T'){
	    		//high temperature
	    		if(received_buffer[2] == 'H'){
	    			//clear the letters
	    			for(int i = 0; i < 3; i++)
	    				received_buffer[i] = '0';
	    			//actualize the struct
	    			s_newvalues.f_max_temperature = (float)atof(received_buffer);
	    			//change the values
	    			values_c->vChangeValues(s_newvalues);
	    			goto END;
	    		}
	    		//low temperature
	    		if(received_buffer[2] == 'L'){
	    			//clear the letters
	    			for(int i = 0; i < 3; i++)
	    				received_buffer[i] = '0';
	    			s_newvalues.f_min_temperature = (float)atof(received_buffer);
	    			values_c->vChangeValues(s_newvalues);
	    			goto END;
	    		}

	    	}
	    	if(received_buffer[1] == 'H'){
	    		if(received_buffer[2] == 'H'){
	    			//clear the letters
	    			for(int i = 0; i < 3; i++)
	    				received_buffer[i] = '0';
	    			//actualize the struct
	    			s_newvalues.f_max_humidity = (float)atof(received_buffer);
	    			//change the values
	    			values_c->vChangeValues(s_newvalues);
	    			goto END;
	    		}
	    		if(received_buffer[2] == 'L'){
	    			//clear the letters
	    			for(int i = 0; i < 3; i++)
	    				received_buffer[i] = '0';
	    			s_newvalues.f_min_humidity = (float)atof(received_buffer);
	    			values_c->vChangeValues(s_newvalues);
	    			goto END;
	    		}

	    	}
	    	if(received_buffer[1] == 'C'){
    			//clear the letters
    			for(int i = 0; i < 2; i++)
    				received_buffer[i] = '0';
    			//actualize the struct
    			s_newvalues.f_max_CO2 = (float)atof(received_buffer);
    			//change the values
    			values_c->vChangeValues(s_newvalues);
    			goto END;

	    	}
	    	if(received_buffer[1] == 'N'){
	    		//copy the new number for the string
	    		for(int i = 2; i < 11; i++)
	    		    s_newvalues.s_number[i-2] = received_buffer[0];
    			//change the values
    			values_c->vChangeValues(s_newvalues);
    			goto END;
	    	}
	    }
	  }
    END:memset(received_buffer,0,sizeof(received_buffer));
}
	return NULL;
}

CWifi::~CWifi() {

}

