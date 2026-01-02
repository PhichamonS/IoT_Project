#ifndef SENSOR_H
#define SENSOR_H

#include <ADS1115_WE.h>

// Constants
constexpr int NUM_SENSORS = 4;

// Public variables 
extern int16_t rawMoistureValue[NUM_SENSORS];
extern float sensorValue[NUM_SENSORS];
extern float sensorDry[NUM_SENSORS];
extern float sensorWet[NUM_SENSORS];

// Public functions
void checkADC();
void readSensors();
float readChannel(ADS1115_MUX channel);

#endif