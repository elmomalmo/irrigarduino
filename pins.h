#ifndef PINS_h
#define PINS_h

// Pin for flashing on each polling cycle
uint8_t POLL_LED_PIN = 13;

// Digital input for whether there is water in the water butt
uint8_t RES_SENSOR_PIN = 12;

// Pin to switch the water pump on/off
uint8_t PUMP_CTRL_PIN = 11;

// A (preferably red LED) attached to this pin will be on when the water is low
uint8_t WATER_WRN_LED_PIN = 10;

// Pin to control a solenoid valve to prevent water leaving the tank through gravity
uint8_t VALVE_CTRL_PIN = 9;

// Analog input pin attached to a potentiometer to calibrate the moisture sensor
uint8_t MOISTURE_CALIB_PIN = A1;

// Analog input pin attached to pointer sensor
uint8_t MOISTURE_SENSOR_PIN = A0;

#endif