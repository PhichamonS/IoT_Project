#ifndef BLYNK_APP_H
#define BLYNK_APP_H

#define BLYNK_TEMPLATE_ID   "TMPL4iiNHqDK9"
#define BLYNK_TEMPLATE_NAME "Automate watering system"

extern int plantSelect;
extern bool systemOn;
extern long onDuration;
extern long lastWater[4];
extern bool pumpOn[4];

void initBlynk();
void runBlynk();
void uptime();
void sendSensorToBlynk();

// Timer API (wrappers)
void blynkTimerSet(unsigned long interval, void (*func)());
void runBlynkTimer();

#endif