#ifndef _STDIO_H
#define _STDIO_H
#include <stdio.h>
#endif

#ifndef _UTIL_DELAY_H
#define _UTIL_DELAY_H
#include <util/delay.h>
#endif

#include "usart.h"


uint16_t getGamepadState() ;
void initGamepad();
int myFunction(int, int);
void initUsart(uint32_t baudrate, uint8_t databits, Parity parity, uint8_t stopbits);
void usartPutchar(unsigned char c);
int usartGetchar(void);
void usartPutstring(char s[]);