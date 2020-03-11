#include <SharpIR.h>

#define sensorPin A0
#define model 1080

SharpIR SharpIR(sensorPin, model);

void setup() {
  Serial.begin(9600);

  pinMode(sensorPin, INPUT);
}

void loop() {
  int analog_port_data = analogRead(sensorPin);
  Serial.print("A0 data:  ");
  Serial.println(analog_port_data);

  // 5V/1024 = 0.0048828125
  float volts = analog_port_data * 0.0048828125; // convert data recieved from port to voltage producer by sensor
  Serial.print("volts:    ");
  Serial.println(volts);
  
  Serial.println("=============================");

  unsigned long start_time = millis();  // takes the time before the loop on the library begins 

  int distance = SharpIR.distance();  // this returns the distance to the object you're measuring

  Serial.print("Mean distance: ");  // returns it to the serial monitor
  Serial.println(distance);
  
  unsigned long mesurement_time = millis() - start_time;  // the following gives you the time taken to get the measurement
  Serial.print("Time taken (ms): ");
  Serial.println(mesurement_time);

  delay(100);
}
