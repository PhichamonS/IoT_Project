
#include <Arduino.h>
#include "control.h"

#define PUMP_ON  HIGH
#define PUMP_OFF LOW

// Pump GPIO mapping
static const uint8_t pumpPins[4] = {D0, D5, D6, D7};

void setupPumps() {
  for (int i = 0; i < 4; i++) {
    // IMPORTANT: Set to HIGH before defining as OUTPUT 
    // to prevent pumps from "blasting" on at startup.
    if (i == 0) {
        digitalWrite(pumpPins[i], !PUMP_OFF); 
    }else{
        digitalWrite(pumpPins[i], PUMP_OFF); 
    }
    pinMode(pumpPins[i], OUTPUT);
  }
}

void setPump(uint8_t pumpIndex, bool state) {
  if (pumpIndex >= 4) return;
  // If state is true, send PUMP_ON (LOW), else send PUMP_OFF (HIGH)
  if (pumpIndex == 0) {
    digitalWrite(pumpPins[pumpIndex], state ? PUMP_OFF : PUMP_ON);
  }else{
    digitalWrite(pumpPins[pumpIndex], state ? PUMP_ON : PUMP_OFF);
  }
  
}

// JUMP START TEST FUNCTION
// This tests each pump individually for 2 seconds
void testPumpsSequential() {
  Serial.println("Starting Pump Test Sequence...");
  
  for (int i = 0; i < 4; i++) {
    Serial.printf("Testing Pump %d (Pin %d)...\n", i + 1, pumpPins[i]);
    
    setPump(i, true);  // Turn pump ON
    delay(1000);       // Let it run for 2 seconds
    setPump(i, false); // Turn pump OFF
    
    delay(500);        // Short pause before next pump to let batteries recover
    }
}


