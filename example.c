#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "usb_keyboard.h"

#define CPU_PRESCALE(n)  (CLKPR = 0x80, CLKPR = (n))

void send_key(char c) {
  if(c >= 'a' && c <= 'z') {
    int keycode = c - 'a' + KEY_A;
    usb_keyboard_press(keycode, 0);
  }
  else if(c >= 'A' && c <= 'Z') {
    int keycode = c - 'A' + KEY_A;
    usb_keyboard_press(keycode, KEY_SHIFT);
  }
  else if(c == ' ') {
    usb_keyboard_press(KEY_SPACE, 0);
  }
  else if(c == '.') {
    usb_keyboard_press(KEY_PERIOD, 0);
  }
  else if(c == ',') {
    usb_keyboard_press(KEY_COMMA, 0);
  }
  else if(c == '!') {
    usb_keyboard_press(KEY_1, KEY_SHIFT);
  }
  else if(c == '?') {
    usb_keyboard_press(KEY_SLASH, KEY_SHIFT);
  }
  else if(c == '\n') {
    usb_keyboard_press(KEY_ENTER, 0);
  }
  return;
}

void type_message(char* msg) {
  char* c;
  for(c = msg; *c; c++)
    send_key(*c);
}

int main(void) {
  // set for 16 MHz clock
  CPU_PRESCALE(0);

  // Initialize USB, wait for host to respond
  usb_init();
  while (!usb_configured()) /* wait */ ;
  // Give the host another second to init drivers
  _delay_ms(500);

  usb_keyboard_press(KEY_SPACE, KEY_GUI);
  _delay_ms(200);
  type_message("TextEdit\n");
  _delay_ms(600);
  
  type_message("Now is the time for all good men to come to the aid of their country.\n");
  type_message("The quick brown fox jumps over the lazy dog.\n");

  return 0;
}
