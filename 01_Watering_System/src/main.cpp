#include <Arduino.h>
#include "blynk_app.h"
#include "sensor.h"
#include "control.h"

// Pin Configuration
constexpr uint8_t PUMP_PINS[4] = {D3, D4, D5, D6};

// Setup
void setup(){
  Serial.begin(115200);

  delay(100);

  Serial.println();
  Serial.println("BOOTING...");
  Serial.println(ESP.getResetReason());

  initBlynk();
  checkADC();                               // Initialize ADS1115
  setupPumps();
  
  // Run the test once at startup
  testPumpsSequential();

  // Timer
  blynkTimerSet(10000L, sendSensorToBlynk);
  blynkTimerSet(10000L, uptime);
  // timer.setInterval(10000L, control);       // for control, run every 10s

  Serial.println("Setup Complete");
}

// // This function is called every time the Virtual Pin 4 state changes
// BLYNK_WRITE(V4)
// {
//   int water_status = param.asInt();
//   digitalWrite(D3, water_status);
// }


void loop()
{
  runBlynk();
  runBlynkTimer();

}

