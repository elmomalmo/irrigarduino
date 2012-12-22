#ifndef IRRIGATION_h
#define IRRIGATION_h

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
  Pump(uint8_t pumpControlPin, uint8_t valveControlPin);
  void start();
  void stop();
  boolean isPumping();
  void openValve();
  void closeValve();
private:
  uint8_t _pumpCtrlPin;
  boolean _pumping;
  uint8_t _valveCtrlPin;
};

class Soil {
public:
  Soil(uint8_t sensorPin, uint8_t calibrationPin);
  boolean isTooDry();
private:
  uint8_t _sensorPin;
  uint8_t _calibrationPin;
  uint8_t _consecutiveReadingCount;
  boolean _lastReadingTooDry;
  boolean _soilToDry;
  void _debounceRaeading(boolean);
};

// The number of consequitive readings required to trigger a switch.
extern uint8_t CONSEQ_READING_THRESH;

// How long to wait between each reading
extern uint8_t READING_PERIOD;

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
