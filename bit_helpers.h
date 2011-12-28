#ifndef BIT_HELPERS_h
#define BIT_HELPERS_h

#include <stdint.h>
#include <avr/io.h>

#ifdef __cplusplus
extern "C"{
#endif

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1

#define true 0x1
#define false 0x0

#define LSBFIRST 0
#define MSBFIRST 1

void digitalSetBit(volatile uint8_t *reg, uint8_t bit, uint8_t value);
uint8_t digitalReadBit(volatile uint8_t *reg, uint8_t bit);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
