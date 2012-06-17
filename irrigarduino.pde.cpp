/*
*/
#include <stdio.h>
#include <string.h>
#include <Irrigation.h>
#include <Arduino.h>

Irrigation irrigation;

void setup();
void loop();

void setup()
{
  irrigation.init();
}


/* Loop and print the time every second */
void loop()
{
  irrigation.pollIrrigationStatus();
  delay(2000);
}
