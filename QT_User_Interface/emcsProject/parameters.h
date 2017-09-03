#ifndef PARAMETERS_H
#define PARAMETERS_H
//POR GET AND SETS
class Parameters_last{
public:
    float co2;
    float temp_max;
    float temp_min;
    float hum_max;
    float hum_min;
    int sim;
    int id_parameter;
    float battery_level_xbee;
};
extern Parameters_last prm_last;

#endif // PARAMETERS_H
