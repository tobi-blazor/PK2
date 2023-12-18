#ifndef _GAMEPAD_H
#define _GAMEPAD_H

#ifndef _AVR_IO_H
#define _AVR_IO_H
#include <avr/io.h>
#endif

#ifndef _UTIL_DELAY_H
#define _UTIL_DELAY_H
#include <util/delay.h>
#endif

#define B 0x1
#define Y 0x2
#define Select 0x4
#define Start 0x8
#define Up 0x10
#define Down 0x20
#define Left 0x40
#define Right 0x80
#define A 0x100
#define X 0x200
#define ShoulderL 0x400
#define ShoulderR 0x800

#define LATCH PB5
#define MISO PB4
#define MOSI PB3


void initGamepad();
uint16_t getGamepadState();
#endif