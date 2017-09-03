//Libraries
#include <DHT.h>
#include <MQ135.h>

//Constants
#define DHTPIN 2           // what pin we're connected to
#define DHTTYPE DHT22     // DHT 22  (AM2302)

//Declare the sensor as input in ADC0
MQ135 gasSensor = MQ135(0);

//Function to convert from float to string
char * floatToString(char * outstr, float value, int places, int minwidth=0, bool rightjustify=false);

//// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

//Variables
int battery_pin = 1;    //ADC1 to the battery
char data[10] = {0};    //auxiliar for the floatToString
float battery_level = 0.0;  //level of the battery
float hum = 0.0;  //Stores humidity value
float temp = 0.0; //Stores temperature value
float co2_concentration = 0.0; //Store the value of the concetration of CO2

//Setup for the system
void setup()
{
    Serial.begin(9600);
    dht.begin();
}

//Infinite loop
void loop()
{
  
  /******************************Acquisition Phase**************************************/
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Read the value of co2 and get this in ppm
    co2_concentration = gasSensor.getPPM();
    co2_concentration = co2_concentration * 40.0;
    //read the value of the battery
    battery_level = analogRead(battery_pin);
    //convert to volts
    battery_level = battery_level*(5.0/1023.0);
    //Multiply for two because of the resistor divider
    
 /*****************************Print values****************************************/   
    //Command of Values
    
    //Print Temperature
    Serial.print("NVXT");
    Serial.print(floatToString(data, temp,1) );
    Serial.print("+H");
    //Print humidity
    Serial.print(floatToString(data, hum ,1 ));
    Serial.print("+C");
    //Print CO2 in PPM
    Serial.print( floatToString(data, co2_concentration,1));
    Serial.print("+B");
    Serial.println( floatToString(data, battery_level,1));
    
    //Wait to the next available values of the DHT22
    delay(2000); //Delay 2 sec.
}


char * floatToString(char * outstr, float value, int places, int minwidth=0, bool rightjustify=false) {
    // this is used to write a float value to string, outstr.  oustr is also the return value.
    int digit;
    float tens = 0.1;
    int tenscount = 0;
    int i;
    float tempfloat = value;
    int c = 0;
    int charcount = 1;
    int extra = 0;
    // make sure we round properly. this could use pow from <math.h>, but doesn't seem worth the import
    // if this rounding step isn't here, the value  54.321 prints as 54.3209

    // calculate rounding term d:   0.5/pow(10,places)  
    float d = 0.5;
    if (value < 0)
        d *= -1.0;
    // divide by ten for each decimal place
    for (i = 0; i < places; i++)
        d/= 10.0;    
    // this small addition, combined with truncation will round our values properly 
    tempfloat +=  d;

    // first get value tens to be the large power of ten less than value    
    if (value < 0)
        tempfloat *= -1.0;
    while ((tens * 10.0) <= tempfloat) {
        tens *= 10.0;
        tenscount += 1;
    }

    if (tenscount > 0)
        charcount += tenscount;
    else
        charcount += 1;

    if (value < 0)
        charcount += 1;
    charcount += 1 + places;

    minwidth += 1; // both count the null final character
    if (minwidth > charcount){        
        extra = minwidth - charcount;
        charcount = minwidth;
    }

    if (extra > 0 and rightjustify) {
        for (int i = 0; i< extra; i++) {
            outstr[c++] = ' ';
        }
    }

    // write out the negative if needed
    if (value < 0)
        outstr[c++] = '-';

    if (tenscount == 0) 
        outstr[c++] = '0';

    for (i=0; i< tenscount; i++) {
        digit = (int) (tempfloat/tens);
        itoa(digit, &outstr[c++], 10);
        tempfloat = tempfloat - ((float)digit * tens);
        tens /= 10.0;
    }

    // if no places after decimal, stop now and return

    // otherwise, write the point and continue on
    if (places > 0)
    outstr[c++] = '.';


    // now write out each decimal place by shifting digits one by one into the ones place and writing the truncated value
    for (i = 0; i < places; i++) {
        tempfloat *= 10.0; 
        digit = (int) tempfloat;
        itoa(digit, &outstr[c++], 10);
        // once written, subtract off that digit
        tempfloat = tempfloat - (float) digit; 
    }
    if (extra > 0 and not rightjustify) {
        for (int i = 0; i< extra; i++) {
            outstr[c++] = ' ';
        }
    }


    outstr[c++] = '\0';
    return outstr;
}

