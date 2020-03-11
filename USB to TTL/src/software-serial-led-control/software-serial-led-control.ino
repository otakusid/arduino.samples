/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

String input_string;

void setup() {
  pinMode(13, OUTPUT);
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");  
}

void loop() { // run over and over
  if (mySerial.available()) {
    char c = mySerial.read();  //gets one byte from serial buffer
    input_string += c;       //compose string

    //byte my_port_data = mySerial.read();
    //Serial.write(my_port_data);
    //mySerial.write(my_port_data); // send data back to see what you type in terminal (todo: make optional)
  }
  if (input_string.length() > 0) {
      Serial.println(input_string); //see what was received
      mySerial.println(input_string);

      if (input_string == "l") {
        blink(500);
      }

      input_string = "";
  }
}

void blink(int pause){
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(pause);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(pause);              // wait for a second
}
