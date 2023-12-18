#include "main.h"

int main(void){
  sei();
  initUsart(9600, 8, NONE, 1);
  initGamepad();

  while (1) {
      uint16_t gamepad = (uint16_t) getGamepadState();

      _delay_ms(5);

      for(int x = 0; x <16; x++) {
        usartPutchar((gamepad&(1<<x)?1:0)+48);
      }
      usartPutchar('\n');
  }
}