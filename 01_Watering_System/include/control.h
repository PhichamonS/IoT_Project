#ifndef CONTROL_H
#define CONTROL_H

void setupPumps();
void setPump(uint8_t pumpIndex, bool state);
void testPumpsSequential();

#endif