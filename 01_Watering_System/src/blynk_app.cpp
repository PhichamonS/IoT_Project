#include "blynk_app.h"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WidgetRTC.h>
#include "secrets.h"
#include "sensor.h"
#include "control.h"

BlynkTimer timer;
WidgetRTC rtc;

int plantSelect = 0;
bool systemOn = false;
long onDuration = 0;
long lastWater[4] = {0, 0, 0, 0};
bool pumpOn[4] = {false, false, false, false};

void initBlynk()
{
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
  setSyncInterval(10 * 60);        // Sync interval in seconds (10 minutes)

}

void runBlynk()
{
  Blynk.run();
}

void blynkTimerSet(unsigned long interval, void (*func)()) {
  timer.setInterval(interval, func);
}

void runBlynkTimer() {
  timer.run();
}


// This function sends Arduino's uptime to Virtual Pin V0.
void uptime()
{
  Blynk.virtualWrite(V0, millis() / 1000);
}

void sendSensorToBlynk() {
  readSensors();
  Blynk.virtualWrite(V1, sensorValue[0]); 
  Blynk.virtualWrite(V2, sensorValue[1]); 
  Blynk.virtualWrite(V3, sensorValue[2]); 
  Blynk.virtualWrite(V4, sensorValue[3]); 
}

BLYNK_CONNECTED()
{
  // Synchronize unix-time on connection
  rtc.begin();
  Blynk.syncVirtual(V5);
  Blynk.syncVirtual(V6);
  Blynk.syncVirtual(V7);
  Blynk.syncVirtual(V8);
}


// ---------- Pump control from Blynk ----------
// V5 → Pump 1 (Index 0)
BLYNK_WRITE(V5) {
  if (param.asInt() == 1) {
    setPump(0, 1); 
    timer.setTimeout(15000L, []() {
      setPump(0, 0);
      Blynk.virtualWrite(V5, 0);
    });
  }
}

// V6 → Pump 2 (Index 1)
BLYNK_WRITE(V6) {
  if (param.asInt() == 1) {
    setPump(1, 1);
    timer.setTimeout(3000L, []() {
      setPump(1, 0);
      Blynk.virtualWrite(V6, 0);
    });
  }
}

// V7 → Pump 3 (Index 2)
BLYNK_WRITE(V7) {
  if (param.asInt() == 1) {
    setPump(2, 1);
    timer.setTimeout(3000L, []() {
      setPump(2, 0);
      Blynk.virtualWrite(V7, 0);
    });
  }
}

// V8 → Pump 4 (Index 3)
BLYNK_WRITE(V8) {
  if (param.asInt() == 1) {
    setPump(3, 1);
    timer.setTimeout(3000L, []() {
      setPump(3, 0);
      Blynk.virtualWrite(V8, 0);
    });
  }
}

