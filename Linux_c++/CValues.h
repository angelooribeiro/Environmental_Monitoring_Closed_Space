//
// Created by hacked on 03-12-2016.
//
#ifndef CVALUES_H
#define	CVALUES_H

#include "Header.h"
#include "CXbee.h"


/*
 *Struct to store the variables of the system
 */
struct SValues{
    float f_max_temperature;
    float f_min_temperature;
    float f_max_humidity;
    float f_min_humidity;
    float f_max_CO2;
    char s_number[9];
    float f_battery_limit;
} ;

class CValues{
private:
    //struct to store the parameters of the system
    pthread_mutex_t mt_parameters;
    SValues m_systemvalues_t;

public:
    CValues();
    ~CValues();
    //return 1 if upper alarm, 2 if downer, 0 if normal
    int iCompareTemperature(float f_temperature);
    int iCompareHumidity(float f_humidity);
    int iCompareCO2(float f_co2);
    int iCompareBattery(float f_battery);
    void vChangeValues(SValues m_changevalues_t);
    char* sGetNumber();
};

#endif
