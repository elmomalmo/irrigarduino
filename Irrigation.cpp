#include "Irrigation.h"
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
  _pumping = true;
}

void Pump::stop() {
  digitalWrite(_pumpCtrlPin, LOW);
  _pumping = false;
}

// ============================================================

Soil::Soil(uint8_t sensorPin, uint8_t calibrationPin, uint8_t sensorPwrPin, uint8_t calibrationPwrPin) {
  _calibrationPin = calibrationPin;
  _sensorPin = sensorPin;

  _calibrationPwrPin = calibrationPwrPin;
  _sensorPwrPin = sensorPwrPin;
  
  _sensorReading = 0;
  _calibrationReading = 0;
  
  pinMode(_sensorPwrPin, OUTPUT);
  pinMode(_calibrationPwrPin, OUTPUT);
}

void Soil::_takeReading() {
  digitalWrite(_sensorPwrPin, HIGH);
  digitalWrite(_calibrationPwrPin, HIGH);
  _sensorReading = analogRead(_sensorPin);
  _calibrationReading = analogRead(_calibrationPin);
  digitalWrite(_sensorPwrPin, LOW);
  digitalWrite(_calibrationPwrPin, LOW);
}

boolean Soil::isTooDry() {
  _takeReading();
#ifdef DEBUG
  Serial.print("Calibration: ");
  Serial.println(_calibrationReading);
  Serial.print("Sensor: ");
  Serial.println(_sensorReading);
#endif
  return _sensorReading < _calibrationReading;
}

boolean Soil::isWetEnough() {
  _takeReading();
#ifdef DEBUG
  Serial.print("Calibration + Debounce: ");
  Serial.println(_calibrationReading + SOIL_DEBOUNCE);
  Serial.print("Sensor: ");
  Serial.println(_sensorReading);
#endif
    return _sensorReading > (_calibrationReading + SOIL_DEBOUNCE);
}

// ============================================================

Irrigation::Irrigation() :
  reservoir(RES_SENSOR_PIN),
  pump(PUMP_CTRL_PIN),
  soil(MOISTURE_SENSOR_PIN, MOISTURE_CALIB_SENSOR_PIN, MOISTURE_PWR_PIN, MOISTURE_CALIB_PWR_PIN) {
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
      }
  } else {
      if(!reservoirEmpty && soilTooDry) {
          pump.start();
      }
  }

  delay(10);
  digitalWrite(_indicatorPin, LOW);
}