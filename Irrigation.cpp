#include "Irrigation.h"
#include "DS1302.h"
#include <Arduino.h>
#include "pins.h"

Reservoir::Reservoir(uint8_t sensorPin) {
  _sensorPin = sensorPin;
  pinMode(_sensorPin, INPUT);
}

boolean Reservoir::isNotEmpty() {
  return true; //TODO
}

// ============================================================

Pump::Pump(uint8_t pumpCtrlPin) {
  _pumpCtrlPin = pumpCtrlPin;
  _pumping = false;

  pinMode(_pumpCtrlPin, OUTPUT);
}

boolean Pump::isPumping() {
  return _pumping;
};

void Pump::start() {
  digitalWrite(_pumpCtrlPin, HIGH);
}

void Pump::stop() {
  digitalWrite(_pumpCtrlPin, LOW);
}

// ============================================================

Soil::Soil(uint8_t sensorPin, uint8_t thresholdPin) {
  _thresholdPin = thresholdPin;
  _sensorPin = sensorPin;
}

boolean Soil::isTooDry() {
  return true; //TODO
}

// ============================================================

Irrigation::Irrigation() :
  clock(CLOCK_CE_PIN, CLOCK_IO_PIN, CLOCK_SCLK_PIN),
  reservoir(RES_SENSOR_PIN),
  pump(PUMP_CTRL_PIN),
  soil(MOISTURE_SENSOR_PIN, MOISTURE_THRESH_PIN) {
}

void Irrigation::pollIrrigationStatus() {
  if(reservoir.isNotEmpty() && soil.isTooDry()) {
    if(!pump.isPumping()) {
      pump.start();
    }
  }
}
