#include "sensor.h"
#include "blynk_app.h"
#include <Wire.h>

// Definitions
ADS1115_WE adc(0x48);

int16_t rawMoistureValue[NUM_SENSORS];
float sensorValue[NUM_SENSORS] = {100, 100, 100, 100};
float sensorDry[NUM_SENSORS]   = {2200, 3720, 2215, 2200}; 
float sensorWet[NUM_SENSORS]   = {1020, 1200, 1070, 1035};


void checkADC(){
  Wire.begin(D2, D1);  // SDA, SCL

  if (!adc.init()) {
      Serial.println("ADS1115 not connected!");
  }else {
      Serial.println("ADS1115 connected");
  }
  adc.setVoltageRange_mV(ADS1115_RANGE_4096);
  adc.setCompareChannels(ADS1115_COMP_0_GND); // Default
  adc.setMeasureMode(ADS1115_SINGLE);
}

float readChannel(ADS1115_MUX channel) 
{
  adc.setCompareChannels(channel);
  adc.startSingleMeasurement();

  while (adc.isBusy()) {
    yield();
  }

  return adc.getResult_mV();
}

// Function to read the moisture sensor and send data to Blynk
void readSensors() {

  // Read raw values from moisture sensor
  rawMoistureValue[0] = readChannel(ADS1115_COMP_0_GND);
  rawMoistureValue[1] = readChannel(ADS1115_COMP_1_GND);
  rawMoistureValue[2] = readChannel(ADS1115_COMP_2_GND);
  rawMoistureValue[3] = readChannel(ADS1115_COMP_3_GND);

  // Map the raw value to a percentage
  for (int i = 0; i<NUM_SENSORS; i++){
    sensorValue[i] = (rawMoistureValue[i] - sensorDry[i]) * 100.0 / (sensorWet[i] - sensorDry[i]);
    sensorValue[i] = constrain(sensorValue[i], 0, 100);

    // Print formatted data: "Sensor 0 | Raw: 18500 | Moisture: 45%"
    Serial.printf("Sensor %d | Raw: %d mV | Moisture: %.1f%%\n", 
                  i + 1, rawMoistureValue[i], sensorValue[i]);
  }  

  Serial.printf("---------------------------------------------\n");
}


