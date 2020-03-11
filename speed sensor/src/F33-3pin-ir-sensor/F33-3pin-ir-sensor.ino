int encoder_pin_d0 = 3;

void setup() {
  Serial.begin(9600);

  pinMode(encoder_pin_d0, INPUT);
}

void loop() {
  int encoder_value_d0 = digitalRead(encoder_pin_d0);
  Serial.print("D0 = ");
  Serial.print(encoder_value_d0);

  Serial.print("\n");

  delay(250); //delay 1/4 seconds
}
