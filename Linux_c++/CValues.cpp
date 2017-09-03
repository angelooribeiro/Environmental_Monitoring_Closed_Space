//
// Created by hacked on 03-12-2016.
//

#include "CValues.h"

//as to be global to allow the access to the address
char c_phone_number[9] = {0};    //to save the phone number

//constructor
CValues::CValues(){
    //initalizate the mutex for the parameters
    pthread_mutex_init(&mt_parameters, NULL);
    //insert the default values in the system
    m_systemvalues_t.f_max_CO2 = 1500.0;          //default max value of 1500ppm
    m_systemvalues_t.f_max_humidity = 80.0;       //default max relative humidity of 80%
    m_systemvalues_t.f_min_humidity = 20.0;       //defualt min relative humidity of 20%
    m_systemvalues_t.f_max_temperature = 30.0;    //defualt max temperature values of 30ºC
    m_systemvalues_t.f_min_temperature = 15.0;    //default min temperature values fo 15ºC
    m_systemvalues_t.f_battery_limit = 3.5;		//default voltage min of the battery
    for(int i = 0; i < 9; i++)
    	m_systemvalues_t.s_number[i] = 0x30+i;
}
/*
 * All the next functions compare the values and return the values of the result of comparation
*return 1 if upper alarm, 2 if downer, 0 if normal
*/
int CValues::iCompareTemperature(float f_temperature) {
	float f_temp_temperature_min = 0, f_temp_temperature_max =0;	//to get the temperature limits
	int state = 0;					//to notify if there is alarm or not

	//Enter critical section
    pthread_mutex_lock(&mt_parameters);
    f_temp_temperature_min = m_systemvalues_t.f_min_temperature;
    f_temp_temperature_min = m_systemvalues_t.f_max_temperature;
    //Exit critical section
    pthread_mutex_unlock(&mt_parameters);

    //upper alarm
    if(f_temperature > f_temp_temperature_max)
    	state  =  1;

    //downer alarm
    if(f_temperature < f_temp_temperature_min)
    	state = 2;

    //normal situation
    if( (f_temperature > f_temp_temperature_min) &&
    	(f_temperature < f_temp_temperature_max ) )
    	state = 0;

    return state;
}

int CValues::iCompareHumidity(float f_humidity) {
	float f_temp_humidity_min = 0, f_temp_humidity_max =0;	//to get the temperature limits
	int state = 0;					//to notify if there is alarm or not

	//Enter critical section
	pthread_mutex_lock(&mt_parameters);
	f_temp_humidity_min = m_systemvalues_t.f_min_humidity;
	f_temp_humidity_min = m_systemvalues_t.f_max_humidity;
	//Exit critical section
	pthread_mutex_unlock(&mt_parameters);

	 //upper alarm
	 if(f_humidity > f_temp_humidity_max){
	   	state  =  1;
	 }

	  //downer alarm
	  if(f_humidity < f_temp_humidity_min){
		  state = 2;
	  }

	  //normal situation
	  if( (f_humidity > f_temp_humidity_min) &&
	   	(f_humidity < f_temp_humidity_max ) ){
	   	state = 0;
	  }

	return state;
}

int CValues::iCompareBattery(float f_battery){
	float f_temp_battery_min = 0;	//to get the temperature limits
	int state = 0;					//to notify if there is alarm or not

	//Enter critical section
	pthread_mutex_lock(&mt_parameters);
	f_temp_battery_min = m_systemvalues_t.f_battery_limit;
	//Exit critical section
	pthread_mutex_unlock(&mt_parameters);

	//upper alarm
	if(f_battery < f_temp_battery_min){
		state  =  1;
	}
	//normal situation
	if(f_battery >= f_temp_battery_min){
		state = 0;
	}
	return state;
}

int CValues::iCompareCO2(float f_co2) {
	float f_temp_co2_max =0;	//to get the temperature limits
	int state = 0;					//to notify if there is alarm or not

	//Enter critical section
    pthread_mutex_lock(&mt_parameters);
    f_temp_co2_max = m_systemvalues_t.f_max_CO2;
    //Exit critical section
    pthread_mutex_unlock(&mt_parameters);

    //upper alarm
    if(f_co2 > f_temp_co2_max){
    	state  =  1;
	}
    //normal situation
    if(f_co2 < f_temp_co2_max){
    	state = 0;
    }
    return state;
}

//this function returns the phone number
char* CValues::sGetNumber(void){

    pthread_mutex_lock(&mt_parameters);
	for(int i = 0; i < 9; i++){
		c_phone_number[i] = m_systemvalues_t.s_number[i];
	}
    pthread_mutex_unlock(&mt_parameters);

    return (char*)c_phone_number; //return the phone number
}


/*
 * function that change the values of the parameters of
 * the system, if the parameter is passed as zero, the change will
 * not be made
 */
void CValues::vChangeValues(SValues m_changevalues_t) {

	//lock the struct
	pthread_mutex_lock(&mt_parameters);
	//change CO2
	if(m_changevalues_t.f_max_CO2 != 0)
	m_systemvalues_t.f_max_CO2 = m_changevalues_t.f_max_CO2;
	//change humidity minimum
	if(m_changevalues_t.f_max_humidity != 0)
	m_systemvalues_t.f_max_humidity = m_changevalues_t.f_max_humidity;
	//change humidity maximum
	if(m_changevalues_t.f_min_humidity != 0)
	m_systemvalues_t.f_min_humidity = m_changevalues_t.f_min_humidity;
	//change temperature maximum
	if(m_changevalues_t.f_max_temperature != 0)
	m_systemvalues_t.f_max_temperature = m_changevalues_t.f_max_temperature;
	//change temperature minimum
	if(m_changevalues_t.f_min_temperature != 0)
	m_systemvalues_t.f_min_temperature = m_changevalues_t.f_min_temperature;
	//change the phone number in the system
	if(m_changevalues_t.s_number[1] != 0)
	 for(int i = 0; i < 9; i++)
	    	m_systemvalues_t.s_number[i] = m_changevalues_t.s_number[i];
	//unlock
	pthread_mutex_unlock(&mt_parameters);
}

//destructor
CValues::~CValues(){

}
