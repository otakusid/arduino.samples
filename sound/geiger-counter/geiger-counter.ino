// Geiger Counter - simulated sound effect
// Connections:
// Arduino Pin 10 is toggled to create audio sound effect and goes to LM386 amp
// Arduino Pin 9 is the activate button, which must have a pull-up resistor on it
// An LED (which is optional) can connect to Pin 8 (and needs a current-limiting resistor and connection to ground)

// FINAL port on 5/25/2012


#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>
// #include "iocompat2.h"     Not needed in Arduino environment
// #include "pin_macros.h"    Not needed in Arduino environment

#define INIT_TIMER_COMP 0xffff

#define LOWBYTE(val)  ((uint8_t)((val) & 0xff))
#define HIGHBYTE(val) ((uint8_t)(((val) & 0xff00) >> 8))

#define B_DATA_PORT_MASK (_BV(DDB0))

int foo(void) {
  return 2;
}

void toggle_b2(void) {
  PORTB ^= _BV(PORTB2);
}

void led_out (uint8_t val) {
  unsigned char tval;

  tval = PORTB & _BV(PORTB2);
  tval |= ~val & B_DATA_PORT_MASK;
  PORTB = tval;
}

void stop_timer1 (void) {
  TCCR1B = TCCR1B & ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
}

void start_timer1 (void) {
  TCCR1B |= _BV(WGM12);
  TCCR1B |= _BV(CS12); /* clock prescale divide by 8 */  // Original non-Arduino value was CS11, in Arduino environment, set to (CS12), which is 256.

}

ISR (TIMER1_OVF_vect) {
  led_out(0x1);
}

void set_compare_timer1 (uint16_t val) {
  OCR1AH = HIGHBYTE(val);
  OCR1AL = LOWBYTE(val);
}

typedef enum {
	UP,
	DOWN,
} SVAL;

#define INITSHIFT 0


int sit = (5<<INITSHIFT);
int shift = INITSHIFT;

ISR (TIMER1_COMPA_vect) {
  static unsigned int delay = 0;
	static SVAL state = DOWN;
  int in = PINB;

  cli();
  stop_timer1();
  toggle_b2();

  if (in & 0x2) {
    state = DOWN;
    led_out(0);
  } else {
    state = UP;
    led_out(1);
  }

  delay = (rand() & 0xDEA8);  // Maximum length of the delay between clicks, a random number. Original value was 0xffff (65536).

  if (delay < 0x40) {
	   delay = 0x40;
  }


	if (sit-- <= 0) {
		switch (shift) {
	    case 0:
        if (state == UP) {
          shift = 2;
          sit = (5);
        } else {
          shift = 0;
          sit = 1;
        }
			break;
	    case 1:
	    case 2:
        if (state == UP) {
          shift = 3;
          sit = 1;
        } else {
          sit = 1;
          shift = 0;
        }
			break;
	    case 3:
	    case 4:
        if (state == UP) {
          sit = 1;
          shift = 3;
        } else {
          sit = (10);
          shift = 1;
        }
      break;
	  }
  }

	if (shift == 0) {
		set_compare_timer1(delay<<2);
	} else {
		set_compare_timer1(delay>>shift);
	}

  start_timer1();
  led_out(shift);
  sei();
}

void ioinit (void) {
  DDRB = B_DATA_PORT_MASK | _BV(DDB2);
  PORTB = 0;
  TCCR1A = 0;
  TCCR1B = 0;

  set_compare_timer1(0x4000);

  TCCR1A = 0;
  TCCR1B |=    _BV(WGM12);
  TCCR1B |= _BV(CS11);
}

#define JVAL 100000;

int main (void) {
  ioinit ();
  srandom(0x12345678);
  set_sleep_mode(SLEEP_MODE_IDLE);

  TIMSK1 = _BV (OCIE1A);

  cli();
  sei ();
  sleep_enable();
  sei();

  for (;;) {
	  sleep_cpu();
  }

  return (0);
}
