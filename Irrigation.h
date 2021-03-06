#ifndef IRRIGATION_h
#define IRRIGATION_h 1

#include <Arduino.h>

class Reservoir {
private:
  uint8_t _sensorPin;
public:
  Reservoir(uint8_t sensorPin);
  boolean isEmpty();
};

class Pump {
public:
  Pump(uint8_t pumpControlPin);
  void start();
  void stop();
  boolean isPumping();
private:
  uint8_t _pumpCtrlPin;
  boolean _pumping;
};

class Soil {
public:
  Soil(uint8_t sensorPin, uint8_t calibrationPin, uint8_t sensorPwrPin, uint8_t calibrationPwrPin);
  boolean isTooDry();
  boolean isWetEnough();
private:
  void _takeReading();
  uint8_t _sensorPin;
  uint8_t _calibrationPin;
  uint8_t _sensorPwrPin;
  uint8_t _calibrationPwrPin;
  uint8_t _sensorReading;
  uint8_t _calibrationReading;
};

class Irrigation {
public:
  Irrigation();

  void init();

  /**
   * This method is intended to be run on every loop iteration. If the
   * conditions are right irrigation will running, if not then irrigation will
   * be ceased.
   */
  void pollIrrigationStatus();

private:
  uint8_t _indicatorPin;
  uint8_t _waterWarningPin;
  Reservoir reservoir;
  Pump pump;
  Soil soil;
};

#endif