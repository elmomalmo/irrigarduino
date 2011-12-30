/*
Example sketch for interfacing with the DS1302 timekeeping chip.

Copyright (c) 2009, Matt Sparks
All rights reserved.

http://quadpoint.org/projects/arduino-ds1302
*/
#include <stdio.h>
#include <string.h>
#include <DS1302.h>
#include <Irrigation.h>
#include <Arduino.h>

/* Set the appropriate digital I/O pin connections */
uint8_t CE_PIN   = 5;
uint8_t IO_PIN   = 6;
uint8_t SCLK_PIN = 7;

/* Create buffers */
char buf[50];
char day[10];

/* Create a DS1302 object */
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);
Irrigation irrigation;

void print_time()
{
  /* Get the current time and date from the chip */
  Time t = rtc.time();

  /* Name the day of the week */
  memset(day, 0, sizeof(day));  /* clear day buffer */
  switch (t.day) {
    case 1:
      strcpy(day, "Sunday");
      break;
    case 2:
      strcpy(day, "Monday");
      break;
    case 3:
      strcpy(day, "Tuesday");
      break;
    case 4:
      strcpy(day, "Wednesday");
      break;
    case 5:
      strcpy(day, "Thursday");
      break;
    case 6:
      strcpy(day, "Friday");
      break;
    case 7:
      strcpy(day, "Saturday");
      break;
  }

  /* Format the time and date and insert into the temporary buffer */
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day,
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  /* Print the formatted string to serial so we can see the time */
  Serial.println(buf);
}

void setup();
void loop();

void setup()
{
}


/* Loop and print the time every second */
void loop()
{
  irrigation.pollIrrigationStatus();
}
