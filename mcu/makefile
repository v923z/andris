# makefile
MCU=atmega88p
MCU_DUDE=m88p
#F_CPU = 16000000L
#For baud rate settigns, see should give an error of 0.2%. See p. 162 of the Atmega8 manual
#BAUDRATE = 9600

# optimize for size:
#CDEFS = -D F_CPU=$(F_CPU) -D BAUDRATE=$(BAUDRATE)

#MCU=attiny44a
#MCU_DUDE=t44
F_CPU = 8000000L
CDEFS = -D F_CPU=$(F_CPU)

CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues $(CDEFS)
OBJCOPY=avr-objcopy
CC = avr-gcc
TARGET = display
OBJS = adc.o
#OBJS = 
SRCS = $(OBJS, .o=.c)

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).out display.h hardware.h
	$(OBJCOPY) -R .eeprom -O ihex $(TARGET).out $(TARGET).hex
	avr-size $(TARGET).hex
	
$(TARGET).out: main.c $(OBJS) display.h hardware.h
	$(CC) main.c -o $(TARGET).out $(CFLAGS) -Wl,-Map,$(TARGET).map $(OBJS) -lm

adc.o: adc.c adc.h
	$(CC) $(CFLAGS) -c adc.c

serial.o: serial.c serial.h
	$(CC) $(CFLAGS) -c serial.c

load88:
	sudo avrdude -p $(MCU_DUDE) -P usb -c avrisp2 -e -U flash:w:$(TARGET).hex -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m

dragon88:
	sudo avrdude -p $(MCU_DUDE) -P usb -c dragon_isp -e -U flash:w:$(TARGET).hex -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m

load44:
	sudo avrdude -p $(MCU_DUDE) -P usb -c avrisp2 -e -U flash:w:$(TARGET).hex -U lfuse:w:0xff:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m 

dragon44:
	sudo avrdude -p $(MCU_DUDE) -P usb -c dragon_isp -F -e -U flash:w:$(TARGET).hex -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m 
	
# --------------------
	
clean:
	rm *.o *.map *.out *.hex *.*~ -rf
