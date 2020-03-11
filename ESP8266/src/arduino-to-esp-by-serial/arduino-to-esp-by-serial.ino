#include <SoftwareSerial.h>

int ledPin = 13;
int rxPin = 10;
int txPin = 11;

SoftwareSerial debugPort(rxPin, txPin, false); // RX, TX

void setup() {
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600); // esp8266
  debugPort.begin(9600);  // debug connection

  debugPort.print("start");
  
  Serial.println("AT+GMR\r\n");
}

void loop() { // run over and over
  if(Serial.available()) {  // check if the esp is sending a message 
    while(Serial.available()) {
      // The esp has data so display its output to the serial window 
      char c = Serial.read(); // read the next character.
      debugPort.write(c);
    }  
  } 
  
  if(debugPort.available()) {
    // the following delay is required because otherwise the arduino will read the first letter of the command but not the rest
    // In other words without the delay if you use AT+RST, for example, the Arduino will read the letter A send it, then read the rest and send it
    // but we want to send everything at the same time.
    delay(1000);
    
    String command="";
    
    while(debugPort.available()) {  // read the command character by character
      // read one character
      command+=(char)Serial.read();
    }

    //command += "\r\n";
    command = "AT\r\n";
    blink(30);
    debugPort.println(command); // send the read character to the debug
    //delay(30);
    Serial.println(command);
    //sendData(command, 0, true);
  }
}

void blink(int pause){
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(pause);              // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(pause);              // wait for a second
}

String sendData(String command, const int timeout, boolean debug) {
  // Send AT commands to debug
  String response = "";
  debugPort.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (debugPort.available())
    {
      // The esp has data so display its output to the serial window
      char c = debugPort.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
