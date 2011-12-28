#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "DS1302.h"
#include "HardwareSerial.h"

int main(void)
 {
    uint8_t ceBit = 5;
    uint8_t ioBit = 6;
    uint8_t sclkBit = 7;

    /* Create a DS1302 object */
    DS1302 rtc( & DDRD, &PORTD, &PIND, ceBit, ioBit, sclkBit);

    Serial.begin(9600);

    /* set PORTB for output*/
    DDRB = 0xFF;

    while (1)
    {
        /* set PORTB.6 high */
        PORTB = 0x20;

        _delay_ms(300);

        /* set PORTB.6 low */
        PORTB = 0x00;

        _delay_ms(300);

        /* set PORTB.6 high */
        PORTB = 0x20;

        _delay_ms(300);

        /* set PORTB.6 low */
        PORTB = 0x00;

        _delay_ms(1000);

        Serial.println();
    }

    return 1;
}