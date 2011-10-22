ARDUINO_HOME=/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/
CC=$(ARDUINO_HOME)bin/avr-gcc
CFLAGS=-Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
MCU=atmega168
F_CPU=16000000UL

OBJCOPY=$(ARDUINO_HOME)bin/avr-objcopy
BIN_FORMAT=ihex

PORT=/dev/tty.usbmodemfd131
BAUD=115200
PROTOCOL=stk500v1
PART=$(MCU)
AVRDUDE=$(ARDUINO_HOME)bin/avrdude -C $(ARDUINO_HOME)etc/avrdude.conf -F -V 

RM=rm -f

.PHONY: all
all: main.hex

main.hex: main.elf

main.elf: main.s

main.s: main.c

.PHONY: clean
clean:
	$(RM) main.elf main.hex main.s

.PHONY: upload
upload: main.hex
	$(AVRDUDE) -c $(PROTOCOL) -p $(PART) -P $(PORT) -b $(BAUD) -U flash:w:$<

%.elf: %.s ; $(CC) $(CFLAGS) -s -o $@ $<

%.s: %.c ; $(CC) $(CFLAGS) -S -o $@ $<

%.hex: %.elf ; $(OBJCOPY) -O $(BIN_FORMAT) -R .eeprom $< $@