#define pump 27  // relay control motor
void setup() {
  Serial.begin(9600);
  pinMode (pump, OUTPUT);

}

void loop() {
  digitalWrite(pump,HIGH);
  delay(4000);
  digitalWrite(pump,LOW);
  delay(2000);

}
