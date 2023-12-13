#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// put function declarations here:
enum Parity {
EVEN=0b10,
ODD=0b11,
NONE=0b00,
RESERVED=0b01
};

int myFunction(int, int);
void initUsart(uint32_t baudrate, uint8_t databits, Parity parity, uint8_t stopbits);
void usartPutchar(unsigned char c);
int usartGetchar(void);
void usartPutstring(char s[]);

ISR(USART_RX_vect) {
  usartPutchar(usartGetchar());
}

int main(void){
 sei();
  initUsart(9600, 8, NONE, 1);

  DDRD = 0b11111100;
  DDRC = 0b11111000;
  uint8_t i = 2;
  bool moveDown;

  while (1) {
      if (i >= 8)
        moveDown = true;
      else if (i == 2)
        moveDown = false;

      if (moveDown)
        PORTD = 0b00000000 ^ 0x01 << --i;
      else
        PORTD = 0b00000000 ^ 0x01 << i++;
      
      _delay_ms(20);
  
  }
}


 void initUsart(uint32_t baudrate, uint8_t databits, Parity parity, uint8_t stopbits) {
  UBRR0 = (F_CPU) / ((baudrate) * 16UL) - 1;
  UCSR0B = 0x98;
  uint8_t ucsrc;
  
  //1. UMSEL01 muss immer auf 0 gesetzt sein
  ucsrc |= 0b0 << UMSEL01;
  
  //2. UMSEL00 ist 0 bei asynchronen Schnittstellen und 1 bei synchronen
  ucsrc |= 0b0 << UMSEL00;

  //3. Parity 00 für Disabled, 01 für Reserved, 10 für Enable (Even-Parity) und 11 für Enable (Odd-Parity)
  ucsrc |= parity << UPM00;

  //4-5. USBS0 ist 0 bei einem Stop-Bit und 1 bei zwei Stop-Bits.
  if(stopbits == 1) {
    ucsrc |= 0b0 << USBS0;
  }else if (stopbits == 2) {
    ucsrc |= 0b1 << USBS0;
  }

  //6-7. UCSZ0 bestimmt die Datenbits 00 für 5-Bit, 01 für 6-Bit, 10 für 7-Bit und 11 für 8-Bit.
  switch(databits) {
    case 5:
      ucsrc |= 0b00 << UCSZ00;
      break;
    case 6:
      ucsrc |= 0b01 << UCSZ00;
      break;
    case 7:
      ucsrc |= 0b10 << UCSZ00;
      break;
    case 8:
      ucsrc |= 0b11 << UCSZ00;
      break;
  }

  //8. UCPOL0 wird nur bei synchroner Datenübertragung verwendet, um entweder bei 0 mit steigender- oder 1 mit fallender Flanke des externen Taktgeber Daten zu senden.
  UCSR0C = ucsrc;
 }

int usartGetchar(void) {
  //Testen ob neue eingabe da
  if(UCSR0A & (1 << RXC0)) {
    return UDR0;
  } else {
    return -1;
  }
}

void usartPutchar(unsigned char c) {
  //warten bis UDRE0 frei
  while(~UCSR0A & (1 << UDRE0));
  UDR0 = c;
}


void usartPutstring(char s[]) {
  for(int i = 0; s[i] !='\0'; i++) {
    usartPutchar(s[i]);
  }
}