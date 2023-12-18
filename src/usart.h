#ifndef _USART_H
#define _USART_H

#ifndef _STDIO_H
#define _STDIO_H
#include <stdio.h>
#endif

#ifndef _AVR_INTERRUPT_H
#define _AVR_INTERRUPT_H
#include <avr/interrupt.h>
#endif

#ifndef _AVR_IO_H
#define _AVR_IO_H
#include <avr/io.h>
#endif

#ifndef _UTIL_DELAY_H
#define _UTIL_DELAY_H
#include <util/delay.h>
#endif


typedef enum Parity {
    EVEN=0b10,
    ODD=0b11,
    NONE=0b00,
    RESERVED=0b01
} Parity;

ISR(USART_RX_vect);
void initUsart(uint32_t baudrate, uint8_t databits, Parity parity, uint8_t stopbits);
int usartGetchar(void);
void usartPutchar(unsigned char c);
void usartPutstring(char s[]);
#endif