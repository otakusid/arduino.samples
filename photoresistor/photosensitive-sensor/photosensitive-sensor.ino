int inPin = 7;   // pushbutton connected to digital pin 7
int val = 0;     // variable to store the read value

void setup() {
  Serial.begin(9600);
  
  pinMode(inPin, INPUT);      // sets the digital pin 7 as input
}

void loop() {
  val = digitalRead(inPin);   // read the input pin

  Serial.print(val);
  Serial.print("\n");
}
