#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "usb_keyboard.h"
#include "uart.h"
#include "char_to_keys.h"

#define CPU_PRESCALE(n)  (CLKPR = 0x80, CLKPR = (n))

void send_key(char c) {
  usb_keyboard_press(keys[c], modifiers[c]);
}

void type_message(char* msg) {
  char* c;
  for(c = msg; *c; c++)
    send_key(*c);
}

int main(void) {
  // set for 16 MHz clock
  CPU_PRESCALE(0);

  // Initialize USB
  usb_init();

  // While we wait for the host to respond, initialize the
  // bluetooth modem
  uart_init(115200);

  while (!usb_configured()) /* wait */ ;
  // Give the host another half a second to init drivers
  _delay_ms(500);

  while(1) {
    if(uart_available()) {
      char c = uart_getchar();
      send_key(c);
    }
  }

  return 0;
}
