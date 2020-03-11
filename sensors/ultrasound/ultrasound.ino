/*
 * Used Plug & Play connection scheme
 * 
 * https://github.com/JRodrigoTech/Ultrasonic-HC-SR04/wiki/Plug-&-Play
 * 
 *
 * 5 Trig PIN
 * 6 Echo PIN
*/

// defines pins numbers
const int trigPin = 5;
const int echoPin = 6;

// defines variables
long duration;
int distance;
int oldDistance = 0;


void setup() {
  Serial.begin(9600);

  // Plug & Play power
  pinMode(4, OUTPUT); // VCC pin
  pinMode(7, OUTPUT); // GND ping
  digitalWrite(4, HIGH); // VCC +5V mode  
  digitalWrite(7, LOW);  // GND mode

  // controls
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration*0.034/2;

  if (oldDistance != distance) {
    oldDistance = distance;

    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
  }

 delay(250); //delay 1/4 seconds
}
