int ledPin = 13;


void setup() {
  pinMode(ledPin, OUTPUT);
  
  Serial2.begin(9600); // esp8266
  Serial.begin(9600);  // debug connection

  Serial.print("start");
  
  Serial2.println("AT+GMR\r\n");
}

void loop() { // run over and over
  if(Serial2.available()) {  // check if the esp is sending a message 
    while(Serial2.available()) {
      // The esp has data so display its output to the serial window 
      char c = Serial2.read(); // read the next character.
      Serial.write(c);
    }  
  } 
  
  if(Serial.available()) {
    // the following delay is required because otherwise the arduino will read the first letter of the command but not the rest
    // In other words without the delay if you use AT+RST, for example, the Arduino will read the letter A send it, then read the rest and send it
    // but we want to send everything at the same time.
    delay(1000);
    
    String command="";
    
    while(Serial.available()) {  // read the command character by character
      // read one character
      command+=(char)Serial.read();
    }

    blink(30);
    Serial2.println(command);
  }
}

void blink(int pause){
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(pause);              // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(pause);              // wait for a second
}
