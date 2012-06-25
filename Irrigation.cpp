#include "Irrigation.h"
#include <Arduino.h>
#include "pins.h"

#define DEBUG 1

uint8_t SOIL_DEBOUNCE = 50;

Reservoir::Reservoir(uint8_t sensorPin) {
  _sensorPin = sensorPin;
  pinMode(_sensorPin, INPUT);
}

boolean Reservoir::isEmpty() {
  return digitalRead(_sensorPin) == LOW;
}

// ============================================================

Pump::Pump(uint8_t pumpCtrlPin, uint8_t valveCtrlPin) {
  _pumpCtrlPin = pumpCtrlPin;
  _valveCtrlPin = valveCtrlPin;
  _pumping = false;

  pinMode(_pumpCtrlPin, OUTPUT);
  pinMode(_valveCtrlPin, OUTPUT);
}

boolean Pump::isPumping() {
  return _pumping;
};

void Pump::start() {
  digitalWrite(_pumpCtrlPin, HIGH);
  _pumping = true;
}

void Pump::stop() {
  digitalWrite(_pumpCtrlPin, LOW);
  _pumping = false;
}

void Pump::openValve() {
  digitalWrite(_valveCtrlPin, HIGH);
}

void Pump::closeValve() {
  digitalWrite(_valveCtrlPin, LOW);
}

// ============================================================

Soil::Soil(uint8_t sensorPin, uint8_t calibrationPin) {
  _calibrationPin = calibrationPin;
  _sensorPin = sensorPin;
}

boolean Soil::isTooDry() {
#ifdef DEBUG
  Serial.print("Calibration: ");
  Serial.println(analogRead(_calibrationPin));
  Serial.print("Sensor: ");
  Serial.println(analogRead(_sensorPin));
#endif
  return analogRead(_sensorPin) < analogRead(_calibrationPin);
}

boolean Soil::isWetEnough() {
#ifdef DEBUG
  Serial.print("Calibration + Debounce: ");
  Serial.println(analogRead(_calibrationPin) + SOIL_DEBOUNCE);
  Serial.print("Sensor: ");
  Serial.println(analogRead(_sensorPin));
#endif
    return analogRead(_sensorPin) > (analogRead(_calibrationPin) + SOIL_DEBOUNCE);
}

// ============================================================

Irrigation::Irrigation() :
  reservoir(RES_SENSOR_PIN),
  pump(PUMP_CTRL_PIN, VALVE_CTRL_PIN),
  soil(MOISTURE_SENSOR_PIN, MOISTURE_CALIB_PIN) {
    _indicatorPin = POLL_LED_PIN;
    _waterWarningPin = WATER_WRN_LED_PIN;
}

void Irrigation::init() {
  pinMode(_indicatorPin, OUTPUT);
  pinMode(_waterWarningPin, OUTPUT);
  
#ifdef DEBUG
  Serial.begin(9600);
#endif
}

void Irrigation::pollIrrigationStatus() {
    boolean reservoirEmpty = reservoir.isEmpty();
    boolean soilTooDry = soil.isTooDry();
    boolean soilWetEnough = soil.isWetEnough();
    boolean pumping = pump.isPumping();

    digitalWrite(_indicatorPin, HIGH);

  if(reservoirEmpty) {
#ifdef DEBUG
    Serial.println("The water reservoir is empty");
#endif
    digitalWrite(_waterWarningPin, HIGH);
  } else {
    digitalWrite(_waterWarningPin, LOW);
  }
  
  if(pumping) {
      if(reservoirEmpty || soilWetEnough) {
          pump.stop();

          pump.closeValve();
      }
  } else {
      if(!reservoirEmpty && soilTooDry) {
          pump.openValve();

          pump.start();
      }
  }

  delay(10);
  digitalWrite(_indicatorPin, LOW);
}
