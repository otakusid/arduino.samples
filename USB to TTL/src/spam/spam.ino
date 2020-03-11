/*
 * spam to serial port some message. allow to debug connection issues
 * 
 * AVR AtmegaXXX microcontrollers comes with a default 1 MHz internal oscillator. 
 * this can cause difference betwen baud rate that you configure in serial lybrary
 * and actual baud rate of connection
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 7); // RX, TX

void setup() {
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}


void loop() {
  mySerial.println("ololo"); 

  delay(100);
}

