#include "main.h"

int main(void){
  sei();
  initUsart(9600, 8, NONE, 1);
  initGamepad();

  while (1) {
      uint16_t gamepad = (uint16_t) getGamepadState();


      usartPutstring("\033[1;1H");
      usartPutstring("B  Y  Se St ↑  ↓  ←  →  A  X  ↖  ↗");
      _delay_ms(1);
      usartPutstring("\033[2;1H");
      for(int x = 0; x <12; x++) {
        usartPutchar((gamepad&(1<<x)?1:0)+48);
        usartPutstring("  "); 
      }
  }
}