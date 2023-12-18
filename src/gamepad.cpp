#include "gamepad.h"


void initGamepad() {
  DDRB |= 1<<LATCH;   //LATCH OUT
  DDRB |= 1<<MOSI;    //CLK   OUT
  DDRB &= ~(1<<MISO); //DATA  IN

  PORTB |= 1<<MOSI;   //CLK   HIGH
}

uint16_t getGamepadState() {
  PORTB |= 1<<LATCH;  //LATCH HIGH
  _delay_us(12);
  PORTB &= ~(1<<LATCH);  //LATCH LOW
  

  // Bits holen
  uint16_t gamepad = 0;
  for(uint16_t i = 0; i<12; i++) {
    gamepad |= (PINB & (1<<MISO) ? 0 : 1) << i;
    _delay_us(6);
    PORTB &= ~(1<<MOSI);  //CLK LOW
    _delay_us(6);
    PORTB |= 1<<MOSI;     //CLK HIGH
  }
  return gamepad;
}