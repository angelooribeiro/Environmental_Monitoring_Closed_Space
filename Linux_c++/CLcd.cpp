/*
 * CLcd.cpp
 *
 *  Created on: 31/01/2017
 *      Author: hacked
 */

#include "CLcd.h"

int fd;  // seen by all subroutines
struct sDisplay_args{
	CLcd *p_clcd;
	CValues *p_cvalues;
};

CLcd::CLcd() {
	//assign the fd for the i2c
	fd = wiringPiI2CSetup(I2C_ADDR);
	LcdInit(); // setup LCD
	//welcome message
	LcdLoc(LINE1);
	Typeln("Welcome to EMCS");
	LcdLoc(LINE2);
	Typeln("Connecting... ");
}

// clr lcd go home loc 0x80
void CLcd::ClrLcd(void)   {
  LcdByte(0x01, LCD_CMD);
  LcdByte(0x02, LCD_CMD);
}

// go to location on LCD
void CLcd::LcdLoc(int line)   {
  LcdByte(line, LCD_CMD);
}


// this allows use of any size string
void CLcd::Typeln(const char *s)   {
  while ( *s ) LcdByte(*(s++), LCD_CHR);
}

void CLcd::LcdByte(int bits, int mode)   {
  //Send byte to data pins
  // bits = the data
  // mode = 1 for data, 0 for command
  int bits_high;
  int bits_low;
  // uses the two half byte writes to LCD
  //prepare to send lower nibble to P0 to P3
  bits_high = mode | ((bits >> 4) & 0x0F);
  //prepare to send higher nibble to P0 to P3
  bits_low = mode | (bits&0x0F);

  // High bits
  wiringPiI2CReadReg8(fd, bits_high);
  LcdToggleEnable(bits_high);

  // Low bits
  wiringPiI2CReadReg8(fd, bits_low);
  LcdToggleEnable(bits_low);
}

void CLcd::LcdToggleEnable(int bits)   {
  // Toggle enable pin on LCD display
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits | ENABLE));
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
  delayMicroseconds(500);
}

// Initialise display
void CLcd::LcdInit()   {
	//configured in four bit mode
	LcdByte(0x33, LCD_CMD); // Initialise 3 -> 3
	LcdByte(0x32, LCD_CMD); // Initialise 2 -> 2
	LcdByte(0x28, LCD_CMD); // 4bit mode
	LcdByte(0x0E, LCD_CMD); // clear the screen
	LcdByte(0x01, LCD_CMD); // display on cursor on
	LcdByte(0x06, LCD_CMD); // Increment cursor
	LcdByte(0x80, LCD_CMD); // row 1 column 1
  delayMicroseconds(500);
}

void* CLcd::Display(void* args){

	char received_buffer[BUFFER_SIZE+1] = {0};	//buffer for the received message
	char temp_buffer[20] = {0};	//buffer for parse the values
	unsigned int prio = 1;
	int i_buffer_index = 0;
	int i_temp_index = 0;
	int i_test_result = 0;

	//receive the pointers for the objects
	sDisplay_args *thread_args = (sDisplay_args*)args;

	//To access the objects of the class
	CValues* values_c  = static_cast<CValues*>(thread_args->p_cvalues);
	CLcd* lcd_c = static_cast<CLcd*>(thread_args->p_clcd);

	for(;;){
		//wait until the semaphore is available
		sem_wait(&s_semaphore_display);
		//receive the message fromt the queue
		q_queue_display = mq_open("/q_queue_display", O_RDONLY);
		if( q_queue_receivexbee == (mqd_t) -1 )
			perror("In mq_open()");
		if( mq_receive(q_queue_display,
			received_buffer,8192, &prio) == -1)
			perror("In mq_receive()");
		if( mq_close(q_queue_display) == -1)
			perror("In mq_close()");

		//parse the message to send to the local system
		temp_buffer[0] = 'N';
		temp_buffer[1] = 'V';
		i_temp_index=2;
		while( (received_buffer[i_buffer_index++] != 'T') &&
					   (i_buffer_index < BUFFER_SIZE) );
		//find the terminator character == '+'
		while( (received_buffer[i_buffer_index] != 'H') &&
				(i_buffer_index < BUFFER_SIZE) )
				temp_buffer[i_temp_index++] = received_buffer[i_buffer_index++];
		i_buffer_index++;	//to jump over the leter
		while( (received_buffer[i_buffer_index] != 'C') &&
				(i_buffer_index < BUFFER_SIZE) )
				temp_buffer[i_temp_index++] = received_buffer[i_buffer_index++];
		i_buffer_index++;
		while( (received_buffer[i_buffer_index] != '+') &&
				(i_buffer_index < BUFFER_SIZE) )
				temp_buffer[i_temp_index++] = received_buffer[i_buffer_index++];

		//terminator character
		temp_buffer[i_temp_index] = '\0';

		//save the message in the queue to be sent on wifi
		q_queue_sendwifi = mq_open("/q_queue_sendwifi", O_WRONLY);
		if( q_queue_sendwifi == (mqd_t) -1 )
			perror("In mq_open()");
		if( mq_send(q_queue_sendwifi,
			temp_buffer,20, 1) == -1)
			perror("In mq_receive()");
		if( mq_close(q_queue_sendwifi) == -1)
			perror("In mq_close()");
		sem_post(&s_semaphore_sendwifi);

		//reset the variables
		i_buffer_index = 0;
		i_temp_index = 0;
		memset(temp_buffer, 0, sizeof(temp_buffer));


		/*
		 * Temperature
		 */
		//find the first value in the buffer
		while( (received_buffer[i_buffer_index++] != 'T') &&
			   (i_buffer_index < BUFFER_SIZE) );
		//find the terminator character == '+'
		while( (received_buffer[i_buffer_index] != '+') &&
				(i_buffer_index < BUFFER_SIZE) ){
			temp_buffer[i_temp_index++] = received_buffer[i_buffer_index++];
		}
		i_test_result = values_c->iCompareTemperature((float)atof(temp_buffer));
		//high temperature
		if(i_test_result == 1){
			//clear the second line to be ready to write warnings
			lcd_c->LcdLoc(LINE2);
			lcd_c->Typeln("                ");
			lcd_c->LcdLoc(LINE2);
			lcd_c->Typeln("High Temperature");
		}//low temperature
		if(i_test_result == 2){
			//clear the second line to be ready to write warnings
			lcd_c->LcdLoc(LINE2);
			lcd_c->Typeln("                ");
			lcd_c->LcdLoc(LINE2);
			lcd_c->Typeln("Low Temperature");
		}
		//clear the buffer
		memset(temp_buffer, 0, sizeof(temp_buffer));
		i_temp_index = 0; //restart the index


		/*
		 * Humidity
		 */
		while( (received_buffer[i_buffer_index++] != 'H') &&
			   (i_buffer_index < BUFFER_SIZE) );
		while( (received_buffer[i_buffer_index] != '+') &&
				(i_buffer_index < BUFFER_SIZE) ){
			temp_buffer[i_temp_index++] = received_buffer[i_buffer_index++];
		}
		//if is value of humidity out of limits
		i_test_result = values_c->iCompareHumidity( (float)atof(temp_buffer));
		if(i_test_result == 1){
			//clear the second line to be ready to write warnings
			lcd_c->LcdLoc(LINE2);
			lcd_c->Typeln("                ");
			lcd_c->LcdLoc(LINE2);
			lcd_c->Typeln("High Humidity");
			}
		if(i_test_result == 2){
			//clear the second line to be ready to write warnings
			lcd_c->LcdLoc(LINE2);
			lcd_c->Typeln("                ");
			lcd_c->LcdLoc(LINE2);
			lcd_c->Typeln("Low Humidity");
		}
		//clear the buffer
		memset(temp_buffer, 0, sizeof(temp_buffer));
		i_temp_index = 0; //restart the index


		/*
		 * CO2
		 */
		while( (received_buffer[i_buffer_index++] != 'C') &&
			   (i_buffer_index < BUFFER_SIZE) );
		while( (received_buffer[i_buffer_index] != '+') &&
				(i_buffer_index < BUFFER_SIZE) ){
			temp_buffer[i_temp_index++] = received_buffer[i_buffer_index++];
		}
		//if is a high value of CO2
		if( values_c->iCompareCO2( (float)atof(temp_buffer)) ){
			//clear line 2
			//clear the second line to be ready to write warnings
			lcd_c->LcdLoc(LINE2);
			lcd_c->Typeln("                ");
			lcd_c->LcdLoc(LINE2);
			lcd_c->Typeln("CO2 High");
		}
		//clear the buffer
		memset(temp_buffer, 0, sizeof(temp_buffer));
		i_temp_index = 0; //restart the index

		/*
		 * Battery
		 */
		while( (received_buffer[i_buffer_index++] != 'B') &&
			   (i_buffer_index < BUFFER_SIZE) );
		while( (received_buffer[i_buffer_index] != '\0') &&
				(i_buffer_index < BUFFER_SIZE) ){
			temp_buffer[i_temp_index++] = received_buffer[i_buffer_index++];
		}

		if( values_c->iCompareBattery( (float)atof(temp_buffer)) ){
			lcd_c->LcdLoc(LINE2);
			lcd_c->Typeln("                ");
			lcd_c->LcdLoc(LINE2);
			lcd_c->Typeln("Low Battery");
		}
		//clear the buffer
		memset(temp_buffer, 0, sizeof(temp_buffer));
		i_temp_index = 0; //restart the index


		/*
		 * Print actual values
		 */
		//restart of the variables
		i_buffer_index = 0;
		i_temp_index = 0;
		//parse of the message to print
		while(received_buffer[i_buffer_index++] != 'X');
		while(received_buffer[i_buffer_index] != 'B'){
			if( received_buffer[i_buffer_index] != '+'){
				temp_buffer[i_temp_index++] = received_buffer[i_buffer_index];
			}
			i_buffer_index++;
		}
		lcd_c->LcdLoc(LINE1);
		lcd_c->Typeln(temp_buffer);
		//clear the buffer
		memset(received_buffer, 0, sizeof(received_buffer));
		i_buffer_index = 0;
	}
	return NULL;
}


CLcd::~CLcd() {

}

