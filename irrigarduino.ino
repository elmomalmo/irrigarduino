/*
*/
#include "Irrigation.h"
#include <Wire.h>

Irrigation irrigation;

void setup();
void loop();

void setup()
{
    Wire.begin();
  irrigation.init();
}


/* Loop and print the time every second */
void loop()
{
  irrigation.pollIrrigationStatus();
  delay(2000);
}