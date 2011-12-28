#include "bit_helpers.h"


void digitalSetBit(volatile uint8_t *reg, uint8_t bit, uint8_t value) {
  if(value == LOW) {
    *reg &= ~(1 << bit);
  } else {
    *reg |= (1 << bit);
  } 
}

uint8_t digitalReadBit(volatile uint8_t *reg, uint8_t bit) {
  if(*reg & (1 << bit)) {
    return HIGH;
  } else {
    return LOW;
  }
}
